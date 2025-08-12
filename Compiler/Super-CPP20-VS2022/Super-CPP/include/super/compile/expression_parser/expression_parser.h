#pragma once
#include <string>
#include <vector>
#include <super/type/token.h>
#include <super/type/expression_parser_type.h>
#include <stack>

namespace Super::Compile::ExpressionParser
{
	class Parser
	{
	public:
		Parser(const std::wstring& inputFilePath, std::vector<Super::Type::Token>& tokens);
	private:
		std::wstring _inputFilePath;

		Super::Type::ExpressionParser::Expression _expression;
	};
}