#include <super/tool/string.h>

namespace Super::Tool::String
{
	// 通用转换函数
	std::string ConvertEncoding(const std::string& input, const char* fromCode, const char* toCode)
	{
		UErrorCode status = U_ZERO_ERROR;
		UConverter* fromConv = ucnv_open(fromCode, &status);
		if (U_FAILURE(status)) throw std::runtime_error("打开源编码失败");

		UConverter* toConv = ucnv_open(toCode, &status);
		if (U_FAILURE(status))
		{
			ucnv_close(fromConv);
			throw std::runtime_error("打开目标编码失败");
		}

		// 先转成UChar（UTF-16）
		int32_t ulen = ucnv_toUChars(fromConv, nullptr, 0, input.c_str(), input.length(), &status);
		status = U_ZERO_ERROR;
		std::vector<UChar> ustr(ulen + 1);
		ucnv_toUChars(fromConv, ustr.data(), ulen + 1, input.c_str(), input.length(), &status);

		// 再从UChar转到目标编码
		status = U_ZERO_ERROR;
		int32_t outlen = ucnv_fromUChars(toConv, nullptr, 0, ustr.data(), ulen, &status);
		status = U_ZERO_ERROR;
		std::vector<char> outstr(outlen + 1);
		ucnv_fromUChars(toConv, outstr.data(), outlen + 1, ustr.data(), ulen, &status);

		ucnv_close(fromConv);
		ucnv_close(toConv);

		return std::string(outstr.data(), outlen);
	}

	std::string ListToStringWithLineNumbers(const std::vector<std::string>& lines)
	{
		size_t maxLineLength = std::to_string(lines.size()).length();
		std::string result;
		for (size_t i = 0; i < lines.size(); ++i)
		{
			if (i > 0)
			{
				result += "\n";
			}
			result += 
				std::string(maxLineLength - std::to_string(i + 1).length(), ' ') 
				+ std::to_string(i + 1) + "│" 
				+ Tool::String::ConvertEncoding(lines[i], "utf-8", "gbk");
		}
		return result;
	}

	std::string DictionaryStringToString(const std::unordered_map<std::string, std::string>& map)
	{
		int maxKeyLength = 0;
		for (const auto& item : map)
		{
			maxKeyLength = std::max(maxKeyLength, static_cast<int>(item.first.length()));
		}
		std::string result;
		for (const auto& item : map)
		{
			result += item.first + std::string(maxKeyLength - item.first.length(), ' ') + " = " + item.second + "\n";
		}
		return result;
	}

	std::string TokenToString(const std::vector<Super::Type::Token>& tokens)
	{
		int maxNameLength = 0;
		for (const auto& item : tokens)
		{
			maxNameLength = std::max(maxNameLength, static_cast<int>(Super::Type::TokenNameToString(item.name).size()));
		}
		std::string result;
		for (const auto& item : tokens)
		{
			result +=
				std::to_string(item.line) + ":" + std::to_string(item.column) + "\t"
				+ Super::Type::TokenNameToString(item.name)
				+ std::string(maxNameLength - Super::Type::TokenNameToString(item.name).size(), ' ')
				+ "\t" + item.value + "\n";
		}
		return ConvertEncoding(result,"utf8","gbk");
	}

	size_t String::GetDisplayWidth(const std::string& str)
	{
		size_t width = 0;
		for (char c : str)
		{
			UChar32 uchar = static_cast<UChar32>(c);
			if (uchar >= 0x4E00 && uchar <= 0x9FFF)
			{
				width += 2;
			}
			else
			{
				width += 1;
			}
		}
		return width;
	}

	bool IsWhitespace(char c)
	{
		UChar32 uchar = static_cast<UChar32>(c);

		return u_isWhitespace(uchar);
	}


	bool IsWhitespace(std::string str)
	{
		for (auto& c : str)
		{
			UChar32 uchar = static_cast<UChar32>(c);
			if (u_isWhitespace(uchar))
			{
				return false;
			}
		}
		return true;
	}
}