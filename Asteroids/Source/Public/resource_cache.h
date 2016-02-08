#pragma once

/*OpenGL Libraries*/
#include <GL\glew.h>

/*Standard Library*/
#include <map>
#include <vector>

/*Custom Library*/
#include "..\Public\image_resource.h"
#include "..\Public\shader_resource.h"

/*
=====================================

RESOURCE CACHE

=====================================
*/

class ResourceCache
{
public:
	typedef std::map<HashString, Resource*>					Cache;
	typedef std::map<HashString, Resource*>::iterator		CacheItr;
	typedef std::vector<ResourceFactory*>					Factories;
	typedef std::vector<ResourceFactory*>::iterator			FactoryItr;

	ResourceCache					(void);
	~ResourceCache					(void);

	template<typename T>
	T* load							(const HashString& path);
	void preload					(const HashString& path);
	void unload						(const HashString& path);

	void registerFactory			(ResourceFactory* factory);
	bool supportsFactory			(ResourceFactory* factory);
private:
	Cache			_cache;
	Factories		_factories;
};

//=================================================================================================

template<typename T>
T* ResourceCache::load(const HashString& path)
{
	CacheItr resource = _cache.find(path);
	if (resource != _cache.end())
	{
		return (T*)resource->second;
	}
	else
	{
		for each(ResourceFactory* factory in _factories)
		{
			if (factory->supports(path.getString()))
			{
				Resource* resource = factory->load(path.getString());
				_cache[path] = resource;
				return (T*)resource;
			}
		}
	}
	return nullptr;
}