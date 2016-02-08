#pragma once

/*OpenGL Libraries*/
#include <GL\glew.h>

/*Custom Library*/
#include "image_resource.h"

class Texture
{
public:
	Texture					(void);
	Texture					(ImageResource* texture);
	~Texture				(void);

	bool load				(ImageResource* texture);
	void unload				(void);
	void bind				(void) const;

	glm::ivec2 getSize		(void) const;
private:
	ImageResource* _texture;

	GLuint _ID;

	GLuint _internalFormat;
	GLuint _imageFormat;
	GLuint _wrapS;
	GLuint _wrapT;
	GLuint _filterMin;
	GLuint _filterMag;
};