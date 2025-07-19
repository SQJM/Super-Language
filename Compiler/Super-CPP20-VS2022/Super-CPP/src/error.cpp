#include <super/error.h>
#include <super/compile/global_data.h>
#include <super/tool/string.h>
#include <super/info.h>

namespace Super::Error
{
#define def(c, str) {L##c, L##str}
	std::unordered_map<std::wstring, std::wstring> CODE = 
	{
		def("000000", "不能使用该名作为宏"),
		def("000010", "不能使用该名解除宏定义或条件"),
		def("000020", "不能使用内置关键字作为宏条件"),
		def("000030", "文件路径必须是字符串"),
		def("000040", "使用了这个预处理指令但是他需要后续的代码"),
		def("000050", "不能使用变量名作为宏"),
		def("000060", "不能使用自定义类型名字作为宏"),
		def("000070", "无效的文件路径"),
		def("000080", "一个 SDEF 文件只能有一个前缀定义"),
		def("000090", "SDEF 文件里面只能包含预处理指令关键字"),
		def("000100", "无法取消一个不存在的导入"),
		
		def("100000", "字符串双引号没有对齐"),
		def("100010", "字符串双引号后面不是连接符号"),
		def("100020", "这个关键字不允许这样使用"),
		def("100030", "文件不存在"),
		def("100040", "没有提取到 Token"),

		def("200000", "左括号缺少匹配的右括号"),
		def("200010", "右括号缺少匹配的左括号"),
		def("200020", "左花括号缺少匹配的右花括号"),
		def("200030", "右花括号缺少匹配的左花括号"),
		def("200040", "左中括号缺少匹配的右中括号"),
		def("200050", "右中括号缺少匹配的左中括号"),

		def("300000", "禁止 2 个文件之间互相导入"),

		def("400000", "类型后面缺少名字"),
		def("400010", "类型后面重复类型"),
		def("400020", "符号不连续"),
		def("400030", "修饰关键字不能放在类型关键字后面"),
		def("400040", "多个变量名"),
		def("400050", "变量的声明不允许此符号"),
		def("400060", "未知符号"),
		def("400060", "未知 Token")
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