#include <super/error.h>
#include <super/compile/global_data.h>
#include <super/tool/string.h>
#include <super/info.h>

namespace Super::Error
{
	std::unordered_map<std::wstring, std::wstring> A = 
	{
		{L"000000", L"不能使用内置关键字作为宏"},
		{L"000010", L"不完整的宏定义"},
		{L"000020", L"不能使用内置关键字作为宏来解除"},
		{L"000030", L"不完整的解除宏定义"},
		{L"000040", L"不能使用内置关键字作为宏条件"},
		{L"000050", L"不完整的宏条件"},
		{L"000060", L"错误消息必须是字符串"},
		{L"000070", L"错误消息没有可输出字符串"},
		{L"000080", L"消息必须是字符串"},
		{L"000090", L"消息没有可输出字符串"},
		{L"000100", L"包含汇编文件路径必须是字符串"},
		{L"000110", L"没有汇编文件路径"},
		{L"000120", L"导入高级宏 *.sdp 文件路径必须是字符串"},
		{L"000130", L"没有导入高级宏 *.sdp 文件路径"},
		{L"000140", L"不能使用变量名作为宏"},
		{L"000150", L"不能使用自定义类型名字作为宏"},

		{L"100000", L"字符串双引号没有对齐"},
		{L"100010", L"字符串双引号后面不允许连接该字符串"},
		{L"100020", L"这个关键字不允许这样使用"},

		{L"200000", L"左括号缺少匹配的右括号"},
		{L"200010", L"右括号缺少匹配的左括号"},
		{L"200020", L"左花括号缺少匹配的右花括号"},
		{L"200030", L"右花括号缺少匹配的左花括号"},
		{L"200040", L"左中括号缺少匹配的右中括号"},
		{L"200050", L"右中括号缺少匹配的左中括号"},

		{L"400000", L"类型后面缺少名字"},
		{L"400010", L"类型后面重复类型"},
		{L"400020", L"符号不连续"},
		{L"400030", L"修饰关键字不能放在类型关键字后面"},
		{L"400040", L"多个变量名"},
		{L"400050", L"变量的声明不允许此符号"},
		{L"400060", L"未知符号"},
		{L"400070", L"未知 Token"}
	};

	void NewError(const std::wstring& file, const std::wstring& msg, const Super::Type::Token& token)
	{
		std::wstring head = std::to_wstring(token.line) + L":" + std::to_wstring(token.column) + L'│';
		auto& lines = Super::Compile::GlobalData::FileDataList[file];
		std::wstring body = lines[token.line - 1];
		size_t width = head.size() + Super::Tool::String::GetDisplayLength(body.substr(0, token.column)) - 1;
		std::wstring indicate(width, L'~');
		indicate += L"^";

		std::wcerr << head << body << L"\n" << indicate;
		std::wcerr << L"\n" + msg + L"\nSuper " + Super::Info::Version << std::endl;
	}
}