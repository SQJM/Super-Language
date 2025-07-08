#pragma once
#include <vector>
#include <iosfwd>
#include <sstream>
#include <super/type/token.h>
#include <super/error.h>
#include <super/type/token_name.h>

namespace Super::Compile::LexicalAnalysis
{
	class ExtractToken
	{
	private:
		std::wstring inputFilePath;
		std::vector<Super::Type::Token> tokens;
		bool isDefineName = false;
		bool isSetDefineName = false;
		bool isLineToOneToken = false;

		void AddTokens(size_t line, size_t column, Super::Type::TokenName& tokenName, std::wostringstream& value);
		void ClearNullToken();
		void ProcessStrings(size_t& l, size_t& i, const std::vector<wchar_t>& lineData, std::wostringstream& temp, const Super::Type::TokenName& tokenName);

	public:
		ExtractToken(const std::wstring& path);
		std::vector<Super::Type::Token> GetTokenStream() const;
	};
}

