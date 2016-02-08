#include "../Public/hash_string.h"

HashString::HashString(void)
	: _hash(), _string()
{
}

HashString::HashString(const std::string& string)
{
	hash(string);
}

void HashString::hash(const std::string& string)
{
	_string = string;
	size_t len = string.length();
	const char* key = string.c_str();

	while (len-- != 0)
	{
		_hash += *key++;
		_hash += (_hash << 10);
		_hash ^= (_hash >> 6);
	}

	_hash += (_hash << 3);
	_hash ^= (_hash >> 1);
	_hash += (_hash << 15);
}

const std::string& HashString::getString(void) const
{
	return _string;
}

uint32_t HashString::getHashed(void) const
{
	return _hash;
}

void HashString::clear()
{
	_hash = 0;
	_string.clear();
}

bool HashString::isEmpty(void) const
{
	return !_string.empty();
}

bool HashString::operator<(const HashString& other)
{
	return _hash < other._hash;
}

bool operator<(const HashString& first, const HashString& second)
{
	return first.getHashed() < second.getHashed();
}

bool HashString::operator==(const HashString& other)
{
	return _hash == other._hash;
}