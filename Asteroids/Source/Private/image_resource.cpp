#include "..\Public\image_resource.h"

/*
=====================================

IMAGE RESOURCE

=====================================
*/

ImageResource::ImageResource(void)
	: Resource(), _image(nullptr), _size()
{
	load("Resource/Images/default.png");
}

ImageResource::ImageResource(const std::string& path)
	: Resource(), _image(nullptr), _size()
{
	if (!load(path))
	{
		std::cout << "Failed to load image from: \"" << path << "\""<< std::endl;
	}
}

ImageResource::~ImageResource(void)
{
	if (_image)
	{
		SOIL_free_image_data(_image);
	}
}

bool ImageResource::load(const std::string& path)
{
	_image = SOIL_load_image(path.c_str(),
		&_size.x, &_size.y, 0, SOIL_LOAD_RGBA);
	if (_image)
	{
		_path = HashString(path);
		_isLoaded = true;
		return true;
	}
	return false;
}

void ImageResource::unload(void)
{
	Resource::unload();
	_size = glm::ivec2();
	if (_image)
	{
		SOIL_free_image_data(_image);
	}
}

unsigned char* ImageResource::getRawImage(void) const
{
	return _image;
}

glm::ivec2 ImageResource::getSize(void) const
{
	return _size;
}

/*
=====================================

IMAGE RESOURCE FACTORY

=====================================
*/

ImageResourceFactory::~ImageResourceFactory(void)
{
}

bool ImageResourceFactory::supports(const std::string& path)
{
	std::string extension = clipExtension(path);
	return extension == "png" || extension == "jpg";
}

Resource* ImageResourceFactory::load(const std::string& path)
{
	if (supports(path))
	{
		Resource* resource = new ImageResource(path);
		return (ImageResource*)resource;
	}
}