#pragma once

namespace Super::Type::SuperVar
{
	enum class Type
	{
		Byte,		// 比特 1位
		Char,		// 字符 8位 支持的修饰符:signed,unsigned
		WChar,		// 宽字符 16位 支持的修饰符:signed,unsigned
		Short,		// 短整型 16位 支持的修饰符:signed,unsigned
		Int,		// 整型 32位 支持的修饰符:signed,unsigned,long
		Half,       // 半精度浮点数 16位 支持的修饰符:signed,unsigned
		Float,      // 单精度浮点数 32位 支持的修饰符:signed,unsigned
		Double,     // 双精度浮点数 64位 支持的修饰符:signed,unsigned,long
		Class,      // 类
		Union,      // 联合体
		Struct,     // 结构体
		Enum,       // 枚举
		UserDefine  // 用户自定义类型
	};

	struct Var
	{
		Type type;
		std::wstring name;
		bool isUnsigned; // 是否为无符号类型
		short longSize; // long 修饰数量
		void* value;
	};
}