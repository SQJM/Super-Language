#pragma once
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

namespace Super::Keyword
{
	bool Contains(const std::wstring& str, const std::vector<std::wstring>& keywords);
	bool Contains(const wchar_t& c, const std::vector<std::wstring>& keywords);

	// 修饰符关键字
	const std::vector<std::wstring> Modifier =
	{
		L"constexpr",
		L"static",
		L"private",
		L"public",
		L"protected",
		L"virtual",
		L"friend",
		L"operator",
		L"await",
		L"async",
		L"inline",
		L"const",
		L"unsigned"
	};

	// 其他关键字
	const std::vector<std::wstring> Other =
	{
		L"using",
		L"new",
		L"auto_new",
		L"delete",
		L"throw",
		L"sizeof",
		L"type_name",
		L"namespace",
		L"this",
		L"module",
		L"exports",
		L"export",
		L"template",
		L"import",
		L"type_cast",
		L"direct_cast",
		L"class_cast",
		L"null",
		L"nullptr"
	};

	// 类型关键字
	const std::vector<std::wstring> TypeKeywords =
	{
		L"void",
		L"bool",
		L"char",
		L"wchar",
		L"short",
		L"int",
		L"half",
		L"float",
		L"double",
		L"typedef",
		L"class",
		L"union",
		L"struct",
		L"enum"
	};

	// 控制流关键字
	const std::vector<std::wstring> ControlFlow =
	{
		L"if",
		L"else",
		L"elif",
		L"while",
		L"for",
		L"do",
		L"loop",
		L"switch",
		L"case",
		L"break",
		L"result",
		L"match_ok",
		L"match_err",
		L"match_finally",
		L"continue",
		L"return"
	};

	// 预处理指令
	const std::vector<std::wstring> PreprocessingInstructions =
	{
		L"#define",
		L"#undef",
		L"#ifdef",
		L"#ifndef",
		L"#endif",
		L"#error",
		L"#message",
		L"#include_asm",
		L"#import_sdp",
		L"import_def",
		L"#if",
		L"#elif",
		L"#else"
	};

	// 高级宏
	const std::vector<std::wstring> DefinePro =
	{
		L"#define_pro",
		L"#edit",
		L"#get",
		L"#type",
		L"#error",
		L"#message",
		L"#export"
	};

	// 数字字符
	const std::vector<std::wstring> Number =
	{
		L"0",
		L"1",
		L"2",
		L"3",
		L"4",
		L"5",
		L"6",
		L"7",
		L"8",
		L"9"
	};

	// 符号枚举类
	enum class SymbolsEnum
	{
		Dollar = '$',
		DoubleQuote = '"',
		SingleQuote = '\'',
		Exclamation = '!',
		Hyphen = '-',
		Plus = '+',
		Slash = '/',
		Asterisk = '*',
		Equals = '=',
		Backslash = '\\',
		LeftBracket = '[',
		RightBracket = ']',
		LeftBrace = '{',
		RightBrace = '}',
		Dot = '.',
		Colon = ':',
		Question = '?',
		LeftParenthesis = '(',
		RightParenthesis = ')',
		Pipe = '|',
		Caret = '^',
		Ampersand = '&',
		Percent = '%',
		LessThan = '<',
		GreaterThan = '>',
		Comma = ',',
		Semicolon = ';',
		WaveLine = '~',
		At = '@',
		Hash = '#',
		Underscore = '_'
	};

	// 符号
	const std::vector<std::wstring> Symbols =
	{
		L"$",
		L"\"",
		L"'",
		L"!",
		L"-",
		L"+",
		L"/",
		L"*",
		L"=",
		L"\\",
		L"[",
		L"]",
		L"{",
		L"}",
		L".",
		L":",
		L"?",
		L"(",
		L")",
		L"|",
		L"^",
		L"&",
		L"%",
		L"<",
		L">",
		L",",
		L";",
		L"~",
		L"@"
	};

	// 连接符号
	const std::vector<std::wstring> ConnectSymbols =
	{
		L"+"
	};

	// 分割符号
	const std::vector<std::wstring> SplitSymbols =
	{
		L"-",
		L"+",
		L"/",
		L"*",
		L"|",
		L"^",
		L"&",
		L"%",
		L"~"
	};

	// 字符串后面允许的字符
	const std::vector<std::wstring> StringAfterTheSymbols =
	{
		L"+",
		L"|",
		L"&",
		L"(",
		L")",
		L"[",
		L";",
		L"\r",
		L"\n",
		L" ",
		L"\0"
	};

	// 特殊符号
	const std::vector<std::wstring> SpecialSymbols =
	{
		L"#",
		L"_"
	};

	// 大写字母枚举类
	enum class UpperCaseLetters
	{
		A = 'A', B = 'B', C = 'C', D = 'D', E = 'E',
		F = 'F', G = 'G', H = 'H', I = 'I', J = 'J',
		K = 'K', L = 'L', M = 'M', N = 'N', O = 'O',
		P = 'P', Q = 'Q', R = 'R', S = 'S', T = 'T',
		U = 'U', V = 'V', W = 'W', X = 'X', Y = 'Y',
		Z = 'Z'
	};

	// 小写字母枚举类
	enum class LowerCaseLetters
	{
		a = 'a', b = 'b', c = 'c', d = 'd', e = 'e',
		f = 'f', g = 'g', h = 'h', i = 'i', j = 'j',
		k = 'k', l = 'l', m = 'm', n = 'n', o = 'o',
		p = 'p', q = 'q', r = 'r', s = 's', t = 't',
		u = 'u', v = 'v', w = 'w', x = 'x', y = 'y',
		z = 'z'
	};

	// 辅助函数：检查字符是否为字母
	inline bool IsLetter(wchar_t c)
	{
		return std::isalpha(c);
	}

	// 辅助函数：检查字符是否为数字
	inline bool IsNumber(wchar_t c)
	{
		return std::isdigit(c);
	}

	// 辅助函数：检查字符是否为特定符号
	inline bool IsSymbol(const std::wstring& c, std::vector<std::wstring> cs)
	{
		return std::find(cs.begin(), cs.end(), c) != cs.end();
	}
}