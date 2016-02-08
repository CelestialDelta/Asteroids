//#include "context.hpp"
//
//Context::Context()
//	: window(new Window(this)), resourceCache(new ResourceCache(this))
//{
//	if (!initGLFW())
//	{
//		terminate("GLFW");
//	}
//	else if (!initWindow())
//	{
//		terminate("Window");
//	}
//	else if (!initGL())
//	{
//		terminate("OpenGL");
//	}
//	else if(!initResourceCache())
//	{
//		terminate("ResourceCache");
//	}
//	else if (!initShader())
//	{
//		terminate("Shader");
//	}
//	else if (!initWorld())
//	{
//		terminate("World");
//	}
//	else if (!initPlayer())
//	{
//		terminate("Player");
//	}
//}
//
//Context::~Context()
//{
//	delete resourceCache;
//	delete window;
//	delete world;
//}
//
//GLboolean Context::initGLFW()
//{
//	if (glfwInit())
//	{
//		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//		return GL_TRUE;
//	}
//	else
//	{
//		return GL_FALSE;
//	}
//}
//
//GLboolean Context::initWindow()
//{
//	GLboolean success = window->create(800, 600, "Asteroids");
//	if (success)
//	{
//		glViewport(0, 0, 800, 600);
//		window->setClearColour(Colours::Black);
//		return GL_TRUE;
//	}
//	else
//	{
//		return GL_FALSE;
//	}
//}
//
//GLboolean Context::initGL()
//{
//	glewExperimental = GL_TRUE;
//	if (glewInit() == GLEW_OK)
//	{
//		glEnable(GL_BLEND);
//		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//		glViewport(0, 0, 800, 600);
//		return GL_TRUE;
//	}
//	else
//	{
//		return GL_FALSE;
//	}
//}
//
//GLboolean Context::initResourceCache()
//{
//	resourceCache->registerFactory(new ImageResourceFactory);
//	resourceCache->registerFactory(new ShaderResourceFactory);
//
//	resourceCache->load(HashString("player.png"));
//	/*resourceCache->load(HashString("small_asteroid.png"));
//	resourceCache->load(HashString("medium_asteroid.png"));
//	resourceCache->load(HashString("large_asteroid.png"));
//	resourceCache->load(HashString("space_background.png"));*/
//
//	resourceCache->load(HashString("vertex.vertex"));
//	resourceCache->load(HashString("fragment.fragment"));
//	return GL_TRUE;
//}
//
//GLboolean Context::initShader()
//{
//	ShaderResource* vertex = resourceCache->load<ShaderResource>(HashString("vertex.vertex"));
//	ShaderResource* fragment = resourceCache->load<ShaderResource>(HashString("fragment.fragment"));
//	shader = new Shader(vertex->shaderSource(), fragment->shaderSource());
//	glm::mat4 projection = glm::ortho(0.0f, 800.f, 600.f, 0.0f, -1.0f, 1.0f);
//	shader->bind();
//	shader->setInteger("image", 0);
//	shader->setMatrix4("projection", projection);
//	return GL_TRUE;
//}
//
//GLboolean Context::initWorld()
//{
//	world = new World(this);
//	return GL_TRUE;
//}
//
//GLboolean Context::initPlayer()
//{
//	ImageResource* image = resourceCache->load<ImageResource>(HashString("player.png"));
//	Texture texture(image);
//	Sprite sprite(texture);
//	sprite.setShader(*shader);
//	sprite.setPosition(200, 200);
//	sprite.setDimensions(45, 45);
//	sprite.setColour(Colours::White);
//	player = new Player(this, sprite, glm::vec2(150, 150), .010);
//	world->add(player);
//	return GL_TRUE;
//}
//
//void Context::terminate(const String& object)
//{
//	std::cout << "Game terminated due to \"" << object << "\" failing to load." << std::endl;
//	system("PAUSE");
//	system(0);
//}