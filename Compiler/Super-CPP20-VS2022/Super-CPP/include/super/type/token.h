#pragma once
#include <super/type/token_name.h>
#include <string>
namespace Super::Type
{
	struct Token
	{
		size_t line;
		size_t column;
		TokenName name;
		std::string value;
	};
}