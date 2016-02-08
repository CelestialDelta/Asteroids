#include "..\Public\utility.h"

std::string clipExtension(const std::string& path)
{
	for (size_t i = path.length() - 1; i >= 0; i--)
	{
		if (path[i] == '.')
		{
			return path.substr(i + 1, path.npos);
		}
	}
	return std::string();
}