#include <super/tool/string.h>
#include <super/type/token_name.h>

namespace Super::Tool::String
{
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

	std::wstring ListToStringWithLineNumbers(const std::vector<std::wstring>& lines)
	{
		size_t maxLineLength = std::to_wstring(lines.size()).length();
		std::wstring result;
		for (size_t i = 0; i < lines.size(); ++i)
		{
			if (i > 0)
			{
				result += L"\n";
			}
			result +=
				std::wstring(maxLineLength - std::to_wstring(i + 1).length(), L' ')
				+ std::to_wstring(i + 1) + L"│"
				+ lines[i];
		}
		return result;
	}

	std::wstring DictionaryStringToString(const std::unordered_map<std::wstring, std::wstring>& map)
	{
		int maxKeyLength = 0;
		for (const auto& item : map)
		{
			maxKeyLength = std::max(maxKeyLength, static_cast<int>(item.first.length()));
		}
		std::wstring result;
		for (const auto& item : map)
		{
			result += item.first + std::wstring(maxKeyLength - item.first.length(), L' ') + L" = " + item.second + L"\n";
		}
		return result;
	}

	std::wstring TokenToString(const std::vector<Super::Type::Token>& tokens)
	{
		int maxNameLength = 0;
		for (const auto& item : tokens)
		{
			maxNameLength = std::max(maxNameLength, static_cast<int>(Super::Type::TokenNameToString(item.name).size()));
		}
		std::wstring result;
		for (const auto& item : tokens)
		{
			result +=
				std::to_wstring(item.line) + L":" + std::to_wstring(item.column) + L"\t"
				+ Super::Type::TokenNameToString(item.name)
				+ std::wstring(maxNameLength - Super::Type::TokenNameToString(item.name).size(), L' ')
				+ L"\t" + item.value + L"\n";
		}
		return result;
	}

	bool IsWhitespace(wchar_t c)
	{
		UChar32 uchar = static_cast<UChar32>(c);

		return u_isWhitespace(uchar);
	}

	bool IsWhitespace(std::wstring str)
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

	std::string WStringToEncoded(const std::wstring& input, const char* toCode)
	{
		icu::UnicodeString ustr(input.c_str());
		// 先获取需要的字节数
		int32_t requiredSize = ustr.extract(0, ustr.length(), nullptr, toCode);
		std::string result(requiredSize, '\0');
		ustr.extract(0, ustr.length(), &result[0], toCode);
		return result;
	}

	size_t GetDisplayLength(const std::wstring& str)
	{
		size_t length = 0;
		for (auto& c : str)
		{
			UChar32 u = static_cast<UChar32>(c);
			int width = u_getIntPropertyValue(u, UCHAR_EAST_ASIAN_WIDTH);
			length += (width == U_EA_WIDE || width == U_EA_FULLWIDTH) ? 2 : 1;
		}
		return length;
	}

	std::wstring RemoveFirstAndLastChar(const std::wstring& str)
	{
		if (str.length() > 1)
		{
			return str.substr(1, str.length() - 2);
		}
		return L"";
	}
}