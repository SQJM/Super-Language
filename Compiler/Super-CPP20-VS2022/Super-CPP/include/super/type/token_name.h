#pragma once
#include <string>

namespace Super::Type
{
	enum class TokenName
	{
		None,
		Null,
		// 类型关键字
		TypeKeywords,
		// 修饰符关键字
		ModifierKeyword,
		// 其他关键字
		OtherKeywords,
		// 控制流关键字
		ControlFlowKeywords,
		// 预处理指令
		PreprocessingInstructions,
		// 宏名字
		DefineName,
		// 宏定义的值
		DefineValue,
		// 高级宏
		DefinePro,
		// 符号
		Symbols,
		// 上标数字
		UpperNumberSymbols,
		// 字符串
		String,
		// 字符
		Char,
		// 变量名
		VarName,
		// 功能名
		FunctionName,
		// 指针
		Pointer,
		// 优先级括号
		PriorityParenthesesLeft,
		PriorityParenthesesRight,
		// 声明功能括号
		DeclarationFunctionalParenthesesLeft,
		DeclarationFunctionalParenthesesRight,
		// 定义功能括号
		DefinitionFunctionalParenthesesLeft,
		DefinitionFunctionalParenthesesRight,
		// 调用功能括号
		CallFunctionParenthesesLeft,
		CallFunctionParenthesesRight,
		// 关键字调用功能括号
		KeywordCallsFunctionParenthesesLeft,
		KeywordCallsFunctionParenthesesRight
	};

	const std::wstring TokenNameToString(TokenName name);
}