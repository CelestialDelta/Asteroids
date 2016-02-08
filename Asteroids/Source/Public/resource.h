#pragma once

/*OpenGL Libraries*/
#include <GL\glew.h>

/*Custom Library*/
#include "hash_string.h"

/*
=====================================

RESOURCE

=====================================
*/

class Resource
{
public:
	Resource						(void);
	virtual ~Resource				(void);
	virtual bool load				(const std::string&) = 0;
	virtual void unload				(void);

	uint32_t getHashed				(void) const;
	const std::string& getPath		(void) const;
	bool isLoaded					(void) const;

protected:
	bool			_isLoaded;
	HashString		_path;
};

/*
=====================================

RESOURCE FACTORY

=====================================
*/

class ResourceFactory
{
public:
	virtual ~ResourceFactory			(void);
	virtual bool supports				(const std::string&) = 0;
	virtual Resource* load				(const std::string&) = 0;
};