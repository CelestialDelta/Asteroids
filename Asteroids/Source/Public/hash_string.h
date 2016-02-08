#pragma once

/*OpenGL Libraries*/
#include <GL\glew.h>

/*Standard Library*/
#include <string>

/*
=====================================

HASH STRING

=====================================
*/

class HashString
{
public:
	HashString							(void);
	HashString							(const std::string& string);

	void hash							(const std::string& string);
	const std::string& getString		(void) const;
	uint32_t getHashed					(void) const;
	void clear							(void);

	bool isEmpty						(void) const;

	bool operator<						(const HashString&);
	friend bool operator<				(const HashString&, const HashString&);
	bool operator==						(const HashString&);
private:
	uint32_t		_hash;
	std::string		_string;
};