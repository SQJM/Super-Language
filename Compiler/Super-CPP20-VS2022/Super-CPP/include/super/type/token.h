#pragma once
#include <string>
#include <vector>
#include <super/type/token_name.h>
#include <super/type/token_grammar_name.h>

namespace Super::Type
{
	struct Token
	{
		int line;
		int column;
		TokenName name;
		TokenGrammarName gName;
		std::wstring value;
		Token(int l, int c, TokenName n, const std::wstring& v) : line(l), column(c), name(n), value(v) {}
	};
}