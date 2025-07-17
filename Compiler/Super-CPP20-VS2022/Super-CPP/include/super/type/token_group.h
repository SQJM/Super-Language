#pragma once  
#include <string>  
#include <vector>  
#include <super/type/Token.h>  
#include <super/type/token_grup_name.h>  

namespace Super::Type::TokenGroup
{  

	class Base
	{
	public:
		Super::Type::TokenGroupName name = TokenGroupName::None;
	};

	class ModifierBase
	{
	public:
		std::vector<std::wstring> modifier;
	};

	// 变量声明修饰符
	class VariableDeclarationModifier : public ModifierBase
	{};

	// 变量定义修饰符
	class VariableDefinitionModifier : public ModifierBase
	{};

	// 功能声明修饰符
	class FunctionDeclarationModifier : public ModifierBase
	{};

	// 功能定义修饰符
	class FunctionDefinitionModifier : public ModifierBase
	{};

	// 功能调用修饰符
	class FunctionCallModifier : public ModifierBase
	{};

	// 变量声明
	class VariableDeclaration : public Base, public VariableDeclarationModifier
	{

	};

	// 变量定义
	class VariableDefinition : public Base, public VariableDefinitionModifier
	{

	};

	// 功能声明
	class FunctionDeclaration : public Base, public FunctionDeclarationModifier
	{

	};

	// 功能定义
	class FunctionDefinition : public Base, public FunctionDefinitionModifier
	{

	};

	// 功能调用
	class FunctionCall : public Base, public FunctionCallModifier
	{

	};

	// 表达式
	class Expression : public Base
	{

	};

	// 功能形参声明
	class FunctionParameterDeclaration : public VariableDeclaration
	{

	};

	// 功能形参定义
	class FunctionParameterDefinition : public Base, public VariableDefinitionModifier
	{

	};

	// 命名空间作用域
	class NamespaceScope : public Base
	{};

	// 作用域
	class Scope : public Base
	{

	};

	// 类作用域
	class ClassScope : public Base, public ModifierBase
	{};

	// 枚举作用域
	class EnumScope : public Base, public ModifierBase
	{};

	// 结构体作用域
	class StructScope : public Base, public ModifierBase
	{};

	// 联合体作用域
	class UnionScope : public Base, public ModifierBase
	{};
	
	// 作用域赋值
	class ScopeAssignment : public Base
	{};

	// 控制流 if
	class ControlFlowIf : public Base
	{};

	// 控制流 for
	class ControlFlowFor : public Base
	{};

	// 控制流 for in
	class ControlFlowForIn : public Base
	{};

	// 控制流 while
	class ControlFlowWhile : public Base
	{};

	// 控制流 do while
	class ControlFlowDoWhile : public Base
	{};

	// 控制流 switch
	class ControlFlowSwitch : public Base
	{};

	// 控制流 loop
	class ControlFlowLoop : public Base
	{};

	// 异常处理
	class ExceptionHandling : public Base
	{};

	// 模块
	class Module : public Base
	{};

	// 导出
	class Export : public Base
	{
	};

	// 导出范围
	class Exports : public Base
	{
	};

	// 导入
	class Import : public Base
	{
	};

	// 数组符号
	class ArraySymbol : public Base
	{};

	// 指针符号
	class PointerSymbol : public Base
	{};

	// 取地址符号
	class AddressOfSymbol : public Base
	{};

	// 类实例化
	class ClassInstantiation : public Base
	{};

	// new
	class New : public Base
	{};

	// auto_new
	class AutoNew : public Base
	{};

	// delete
	class Delete : public Base
	{};

	// usint
	class Using : public Base
	{};

	// throw
	class Throw : public Base
	{};

	// sizeof
	class Sizeof : public Base
	{};

	// type_name
	class TypeName : public Base
	{};

	// template
	class Template : public Base
	{};

	// type_cast
	class TypeCast : public Base
	{};

	// direct_cast
	class DirectCast : public Base
	{};

	// class_cast
	class ClassCast : public Base
	{};
}