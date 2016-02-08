#pragma once

/*OpenGL Libraries*/
#include <GL\glew.h>

/*Standard Library*/
#include <iostream>
#include <fstream>
#include <sstream>

/*Custom Library*/
#include "resource.h"
#include "utility.h"

/*
=====================================

SHADER RESOURCE

=====================================
*/

class ShaderResource : public Resource
{
public:
	ShaderResource						(void);
	ShaderResource						(const std::string& path);
	virtual ~ShaderResource				(void) override;

	virtual bool load					(const std::string& path) override;
	virtual void unload					(void) override;

	const std::string& getSource		(void) const;

private:
	std::string _source;
};

/*
=====================================

SHADER RESOURCE FACTORY

=====================================
*/

class ShaderResourceFactory : public ResourceFactory
{
public:
	virtual ~ShaderResourceFactory		(void) override;
	virtual bool supports				(const std::string& path) override;
	virtual Resource* load				(const std::string& path) override;
};