#include <super/keyword.h>
#include <iostream>

namespace Super::Keyword
{
	bool Contains(const std::wstring& str, const std::vector<std::wstring>& keywords)
	{
		for (const auto& keyword : keywords)
		{
			if (str == keyword)
			{
				return true;
			}
		}
		return false;
	}

	bool Contains(const wchar_t& c, const std::vector<std::wstring>& keywords)
	{
		std::wstring str(1, c);
		return Contains(str, keywords);
	}
}