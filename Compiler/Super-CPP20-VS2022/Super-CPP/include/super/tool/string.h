#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <iomanip>
#include <algorithm>
#include <unicode/ucnv.h> 
#include <unicode/unistr.h>
#include <unicode/uchar.h>
#include <super/type/token.h>

namespace Super::Tool::String
{
    std::string ConvertEncoding(const std::string& input, const char* fromCode, const char* toCode);
	std::string ListToStringWithLineNumbers(const std::vector<std::string>& lines);
	std::string DictionaryStringToString(const std::unordered_map<std::string, std::string>& map);
	std::string TokenToString(const std::vector<Super::Type::Token>& tokens);
	size_t GetDisplayWidth(const std::string& str);
	bool IsWhitespace(char c);
	bool IsWhitespace(std::string str);
}