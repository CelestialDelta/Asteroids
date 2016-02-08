#include "..\Public\shader_resource.h"

/*
=====================================

SHADER RESOURCE

=====================================
*/

ShaderResource::ShaderResource(void)
	: Resource(), _source()
{
}

ShaderResource::ShaderResource(const std::string& path)
	: Resource(), _source()
{
	load(path);
}

ShaderResource::~ShaderResource()
{
}

bool ShaderResource::load(const std::string& path)
{
	std::ifstream		input;
	std::stringstream	resolver;
	try 
	{
		input.open(path);
		resolver << input.rdbuf();
		input.close();
		_source = resolver.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Failed to load shader from: \"" << path << "\"" << std::endl;
		return false;
	}
	_path = HashString(path);
	_isLoaded = true;
	return true;
}

void ShaderResource::unload()
{
	Resource::unload();
	_source.clear();
}

const std::string& ShaderResource::getSource() const
{
	return _source;
}

/*
=====================================

SHADER RESOURCE FACTORY

=====================================
*/

ShaderResourceFactory::~ShaderResourceFactory(void)
{
}

bool ShaderResourceFactory::supports(const std::string& path)
{
	std::string extension = clipExtension(path);
	return extension == "vert" || extension == "frag";
}

Resource* ShaderResourceFactory::load(const std::string& path)
{
	if (supports(path))
	{
		Resource* resource = new ShaderResource(path);
		return (ShaderResource*)resource;
	}
}