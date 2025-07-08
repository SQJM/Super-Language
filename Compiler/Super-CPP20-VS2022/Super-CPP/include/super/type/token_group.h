#pragma once
#include <string>
#include <vector>
#include <super/type/Token.h>
#include <super/type/token_grup_name.h>

namespace Super::Type
{
	struct TokenGroup
	{
		Super::Type::TokenGroupName name = TokenGroupName::None;
		std::vector<Token> tokens = {};
	};
}