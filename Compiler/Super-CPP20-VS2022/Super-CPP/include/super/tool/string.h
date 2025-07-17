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
	std::wstring ListToStringWithLineNumbers(const std::vector<std::wstring>& lines);
	std::wstring DictionaryStringToString(const std::unordered_map<std::wstring, std::wstring>& map);
	std::wstring TokenToString(const std::vector<Super::Type::Token>& tokens);
	bool IsWhitespace(wchar_t c);
	bool IsWhitespace(std::wstring str);
	std::string WStringToEncoded(const std::wstring& input, const char* toCode);
	size_t GetDisplayLength(const std::wstring& str);
	std::wstring RemoveFirstAndLastChar(const std::wstring& str);
}