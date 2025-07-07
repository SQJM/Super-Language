#include <super/error.h>
#include <super/compile/global_data.h>
#include <super/tool/string.h>

namespace Super::Error
{
	std::unordered_map<std::string, std::string> A = {
		{"000000", "不能使用内置关键字作为宏"},
		{"000010", "不完整的宏定义"},
		{"000020", "不能使用内置关键字作为宏来解除"},
		{"000030", "不完整的解除宏定义"},
		{"000040", "不能使用内置关键字作为宏条件"},
		{"000050", "不完整的宏条件"},
		{"000060", "错误消息必须是字符串"},
		{"000070", "错误消息没有可输出字符串"},
		{"000080", "消息必须是字符串"},
		{"000090", "消息没有可输出字符串"},
		{"000100", "包含汇编文件路径必须是字符串"},
		{"000110", "没有汇编文件路径"},
		{"000120", "导入高级宏 *.sdp 文件路径必须是字符串"},
		{"000130", "没有导入高级宏 *.sdp 文件路径"},
		{"000140", "不能使用变量名作为宏"},
		{"000150", "不能使用自定义类型名字作为宏"},

		{"100000", "字符串双引号没有对齐"},
		{"100010", "字符串双引号没有对齐"},

		{"200000", "左括号缺少匹配的右括号"},
		{"200010", "右括号缺少匹配的左括号"},
		{"200020", "左花括号缺少匹配的右花括号"},
		{"200030", "右花括号缺少匹配的左花括号"},
		{"200040", "左中括号缺少匹配的右中括号"},
		{"200050", "右中括号缺少匹配的左中括号"},

		{"400000", "类型后面缺少名字"},
		{"400010", "类型后面重复类型"},
		{"400020", "符号不连续"},
		{"400030", "修饰关键字不能放在类型关键字后面"},
		{"400040", "多个变量名"},
		{"400050", "变量的声明不允许此符号"}
	};
	
	std::string AddIndicate(const std::string& file, const Super::Type::Token& token)
	{
		std::string head = std::to_string(token.line) + ":" + std::to_string(token.column) + "│";
		auto& lines = Super::Compile::GlobalData::FileDataList[file];
		std::string body = lines[token.line - 1];
		size_t width = head.size() + Super::Tool::String::GetDisplayWidth(body.substr(0, token.column));
		std::string indicate = std::string(width, '~') + "^";
		return head + body + "\n" + indicate;
	}

	std::exception NewError(const std::string& file, const std::string& msg, const Super::Type::Token& token)
	{
		return std::runtime_error(AddIndicate(file, token) + "\n" + msg);
	}

	std::exception NewError(const std::string& file, const std::string& msg, const std::vector<Super::Type::Token>& tokens)
	{
		std::ostringstream result;
		for (const auto& token : tokens)
		{
			result << AddIndicate(file, token) << "\n";
		}
		return std::runtime_error(result.str() + msg);
	}

	std::exception NewError(const std::string& msg)
	{
		return std::runtime_error(msg);
	}
}