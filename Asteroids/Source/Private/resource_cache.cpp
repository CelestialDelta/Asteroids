#include "..\Public\resource_cache.h"

/*
=====================================

RESOURCE CACHE

=====================================
*/

ResourceCache::ResourceCache(void)
	: _cache(), _factories()
{
}

ResourceCache::~ResourceCache(void)
{
	while (!_factories.empty())
	{
		delete _factories.back();
		_factories.pop_back();
	}
	for (CacheItr itr = _cache.begin(); itr != _cache.end(); itr++)
	{
		delete (*itr).second;
	}
}

void ResourceCache::preload(const HashString& path)
{
	CacheItr found = _cache.find(path);
	if (found == _cache.end())
	{
		for each(ResourceFactory* factory in _factories)
		{
			if (factory->supports(path.getString()))
			{
				Resource* resource = factory->load(path.getString());
				_cache[path] = resource;
			}
		}
	}
}

void ResourceCache::unload(const HashString& file)
{
	CacheItr resource = _cache.find(file);
	if (resource != _cache.end())
	{
		_cache.erase(resource);
	}
}

void ResourceCache::registerFactory(ResourceFactory* factory)
{
	_factories.push_back(factory);
}

bool ResourceCache::supportsFactory(ResourceFactory* factory)
{
	for each(ResourceFactory* fac in _factories)
	{
		if (fac == factory)
		{
			return true;
		}
	}
	return false;
}