#include "..\Public\texture.h"

Texture::Texture()
	: _texture(nullptr), _ID(0), _internalFormat(GL_RGBA), _imageFormat(GL_RGBA),
	_wrapS(GL_REPEAT), _wrapT(GL_REPEAT), _filterMin(GL_LINEAR), _filterMag(GL_LINEAR)
{
}

Texture::Texture(ImageResource* texture)
	: _texture(nullptr), _ID(0), _internalFormat(GL_RGBA), _imageFormat(GL_RGBA),
	_wrapS(GL_REPEAT), _wrapT(GL_REPEAT), _filterMin(GL_LINEAR), _filterMag(GL_LINEAR)
{
	load(texture);
}

Texture::~Texture(void)
{
	if (_texture)
	{
		_texture = nullptr;
	}
}

bool Texture::load(ImageResource* texture)
{
	if(texture->isLoaded())
	{
		glGenTextures(1, &_ID);
		glBindTexture(GL_TEXTURE_2D, _ID);
		glTexImage2D(GL_TEXTURE_2D, 0, _internalFormat,
			texture->getSize().x, texture->getSize().y, 0,
			_imageFormat, GL_UNSIGNED_BYTE, texture->getRawImage());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _wrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _wrapT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _filterMag);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _filterMin);
		glBindTexture(GL_TEXTURE_2D, 0);
		_texture = texture;
		return true;
	}
	return false;
}

void Texture::unload(void)
{
	_ID =				0;
	_internalFormat =	0;
	_imageFormat =		0;
	_wrapS =			0;
	_wrapT =			0;
	_filterMin =		0;
	_filterMag =		0;
}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, _ID);
}

glm::ivec2 Texture::getSize(void) const
{
	return _texture->getSize();
}