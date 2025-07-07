#include <super/keyword.h>
#include <iostream>

namespace Super::Keyword {
	bool Contains(const std::string& str, const std::vector<std::string>& keywords)
	{
		for (size_t i = 0; i < keywords.size(); i++)
		{
			if (keywords[i] == str)
			{
				return true;
			}
		}
		return false;
	}

	bool Contains(const char& c, const char keywords[])
	{
		for (size_t i = 0; keywords[i] != '\0'; ++i)
		{
			if (keywords[i] == c)
			{
				return true;
			}
		}
		return false;
	}
} 