#pragma once

#include <GL\glew.h>

#include <initializer_list>
#include <vector>

#include "hash_string.hpp"

struct ResourceLocation
{
	template<typename... Args>
	ResourceLocation(Args&&... locs)
		: _hashed()
	{
		//Understand this line -> http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4295.html
		(void)std::initializer_list<int>{(locations.push_back(std::forward<Args>(locs)), void(), 0)...};
		hash();
	}

	GLboolean isEmpty() const
	{
		if (!locations.empty())
			return GL_FALSE;
		else
			return GL_TRUE;
	}

	void clear() { locations.clear(); }
	GLuint size() const { return locations.size(); }
	HashString hashed() const { return _hashed; }
	void hash() 
	{ 

		std::string concated;
		for each(std::string loc in locations)
			concated += loc;

		_hashed.hash(concated);
	
	}

	std::vector<std::string> locations;
	HashString _hashed;
};
