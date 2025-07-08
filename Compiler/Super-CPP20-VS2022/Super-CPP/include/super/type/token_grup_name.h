#pragma once
#include <string>

namespace Super::Type
{
	enum class TokenGroupName
	{
		None,
		// 声明
		Declaration,
		// 调用
		Call,
		// 定义
		Definition,
		// 控制流
		ControlFlow,
		// 作用域
		Scope,
		// 自增语句
		AutoIncrementStatement,
		// 自减语句
		AutoDecrementStatement,
	};
}