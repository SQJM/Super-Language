#pragma once
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
#include <sstream>
#include <super/type/token.h>

namespace Super::Compile::LexicalAnalysis
{
	void Parenthesis(const std::string& inputFilePath, std::vector<Super::Type::Token>& tokens);
}