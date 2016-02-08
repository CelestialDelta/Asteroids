#pragma once

/*OpenGL Libraries*/
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <SOIL.h>

/*Standard Library*/
#include <iostream>

/*Custom Libraries*/
#include "resource.h"
#include "utility.h"

/*
=====================================

IMAGE RESOURCE

=====================================
*/

class ImageResource : public Resource
{
public:
	ImageResource					(void);
	ImageResource					(const std::string& path);
	virtual ~ImageResource			(void) override;

	virtual bool load				(const std::string& path) override;
	virtual void unload				(void) override;

	unsigned char* getRawImage		(void) const;
	glm::ivec2 getSize				(void) const;
private:
	unsigned char*		_image;
	glm::ivec2			_size;
};

/*
=====================================

IMAGE RESOURCE FACTORY

=====================================
*/

class ImageResourceFactory : public ResourceFactory
{
public:
	virtual ~ImageResourceFactory		(void) override;
	virtual bool supports				(const std::string& path) override;
	virtual Resource* load				(const std::string& path) override;
};