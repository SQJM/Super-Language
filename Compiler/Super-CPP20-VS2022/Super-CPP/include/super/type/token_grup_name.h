#pragma once
#include <string>

namespace Super::Type
{
	enum class TokenGroupName
	{
		None,
		// 作用域
		Scope,
		// 语句
		Statement,
		// 表达式
		Expression,
		// 表达式语句
		ExpressionStatement,
		// 成员作用域
		MemberScope,
		// 命名空间作用域
		NamespaceScope,
	};
}