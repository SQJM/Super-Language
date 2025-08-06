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

		// 正常计算队列
		std::stack<Super::Type::ExpressionParser::OperationUnit> _normalQueue;
		// 乘除队列
		std::stack<Super::Type::ExpressionParser::OperationUnit> _multiplyDivideQueue;
		// 括号队列
		std::stack<Super::Type::ExpressionParser::OperationUnit> _bracketQueue;
	};
}