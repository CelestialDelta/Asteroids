#include "..\Public\resource.h"

Resource::Resource(void)
	: _isLoaded(false), _path()
{
}

Resource::~Resource(void)
{
}

void Resource::unload(void)
{
	_isLoaded = false;
	_path.clear();
}

uint32_t Resource::getHashed(void) const
{
	return _path.getHashed();
}

const std::string& Resource::getPath(void) const
{
	return _path.getString();
}

bool Resource::isLoaded() const
{
	return _isLoaded;
}

/*
=====================================

RESOURCE FACTORY

=====================================
*/

ResourceFactory::~ResourceFactory(void)
{
}