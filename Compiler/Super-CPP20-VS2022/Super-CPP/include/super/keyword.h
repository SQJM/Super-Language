#pragma once
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

namespace Super::Keyword
{
	bool Contains(const std::string& str, const std::vector<std::string>& keywords);
	bool Contains(const char& c, const char keywords[]);

	// 修饰符关键字
	const std::vector<std::string> Modifier =
	{
		"constexpr", "static", "private", "public", "protected",
		"virtual", "friend", "operator", "await", "async",
		"inline", "const", "unsigned"
	};

	// 其他关键字
	const std::vector<std::string> Other =
	{
		"using", "new", "auto_new", "delete", "throw", "sizeof",
		"type_name", "namespace", "this", "module", "exports",
		"export", "template", "import", "type_cast", "direct_cast",
		"class_cast", "null", "nullptr"
	};

	// 类型关键字
	const std::vector<std::string> TypeKeywords =
	{
		"void", "bool", "char", "wchar", "short", "int", "half",
		"float", "double", "typedef", "class", "union", "struct",
		"enum"
	};

	// 控制流关键字
	const std::vector<std::string> ControlFlow =
	{
		"if", "else", "elif", "while", "for", "do", "loop",
		"switch", "case", "break", "result", "match_ok",
		"match_err", "match_finally", "continue", "return",
		"if_return"
	};

	// 预处理指令
	const std::vector<std::string> PreprocessingInstructions =
	{
		"#define", "#undef", "#ifdef", "#ifndef", "#endif",
		"#error", "#message", "#include_asm", "#import_sdp"
	};

	// 高级宏
	const std::vector<std::string> DefinePro =
	{
		"#define_pro", "#edit", "#get", "#type", "#error",
		"#message", "#export"
	};

	// 数字字符
	const char Number[] =
	{
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
	};

	// 符号枚举类
	enum class Symbols
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

	// 分割符号
	const char SplitSymbols[] =
	{
		'!', '-', '+', '/', '*', '=', '\\', '[', ']',
		'{', '}', '.', ':', '?', '(', ')', '|', '^',
		'&', '%', '<', '>', ',', ';', '~', '@', '$'
	};

	// 特殊符号
	const char SpecialSymbols[] =
	{ '#', '_' };

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
	inline bool IsLetter(char c)
	{
		return std::isalpha(static_cast<unsigned char>(c));
	}

	// 辅助函数：检查字符是否为数字
	inline bool IsNumber(char c)
	{
		return std::isdigit(static_cast<unsigned char>(c));
	}

	// 辅助函数：检查字符是否为特定符号
	inline bool IsSymbol(char c)
	{
		return std::find(std::begin(SplitSymbols), std::end(SplitSymbols), c) != std::end(SplitSymbols);
	}
}