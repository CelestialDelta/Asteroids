#include "Source\Public\game.h"
#include "Source\Public\world.h"

/*
=====================================================================

TODO LIST

=====================================================================
*/

//CREATE A POOL FOR STATES TO REFER TO;
//CREATE A POOL FOR PROJECTILES TO REFER TO;

#ifndef DEBUG
int main(void)
{
	Game game;
	game.init();

	return 0;
}
#endif

#ifdef DEBUG
int main(void)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLFW_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLFW_VERSION_MAJOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	Window window;
	window.create(800, 600, "Asteroids");

	glewExperimental = GL_TRUE;
	glewInit();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	ResourceCache cache;
	cache.registerFactory(new ShaderResourceFactory);
	cache.registerFactory(new ImageResourceFactory);
	ImageResource* img = new ImageResource("Resource/Images/player.png");
	ImageResource* laser = new ImageResource("Resource/Images/laser.png");
	ShaderResource* vert = new ShaderResource("Resource/Shaders/vertex.vert");
	ShaderResource* frag = new ShaderResource("Resource/Shaders/fragment.frag");
	Shader shader(vert->getSource(), frag->getSource());
	glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
	shader.bind();
	shader.setInteger("image", 0);
	shader.setMatrix4("projection", projection);

	//Texture texture(img);
	//Sprite sprite(texture);
	ImageResource* aster = new ImageResource("Resource/Images/asteroid.png");
	Texture as(aster);
	AsteroidGenerator ag(shader, as);

	ImageResource* back = new ImageResource("Resource/Images/space_background.png");
	Texture space(back);
	World world(shader, space, ag);

	Texture text(img);
	Player player(&window, &world, shader, text, Texture(laser));
	world.include(&player);

	float delta = 0.f;
	float lastFrame = 0.f;

	/*Asteroid* asteroid = new Asteroid(&world, shader, as, Asteroid::SMALL);
	world.include(asteroid);
	asteroid->getWorld()->remove(asteroid);*/

	while (!glfwWindowShouldClose(window.getRawWindow()))
	{
		float currentFrame = glfwGetTime();
		delta = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glClear(GL_COLOR_BUFFER_BIT);

		world.handle(delta);
		world.update(delta);
		world.draw();

		window.swapBuffers();
		window.pollEvents();
	}
	glfwTerminate();
	return 0;
}
#endif