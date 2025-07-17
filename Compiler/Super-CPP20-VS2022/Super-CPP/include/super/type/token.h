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

		Token(int l, int c, TokenName n = TokenName::None, std::wstring v = L"", TokenGrammarName g = TokenGrammarName::None)
			: line(l), column(c), name(n), gName(g), value(v)
		{}
	};

	inline Token GetNoneToken()
	{
		return Token(0, 0, TokenName::None, L"");
	}

	inline Token GetNullToken()
	{
		return Token(0, 0, TokenName::Null, L"");
	}
}