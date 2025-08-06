#pragma once
#include <vector>

namespace Super::Type::ExpressionParser
{
	enum class UnitType
	{
		number, // 0 - 9
		symbol, // + - * / | = & ^ ! ~ > < ()[] . " ' %
		ptr,
		address,
		var,
		visit,
		fn,
		arr,
		define,
		define_pro
	};

	struct Unit
	{
		size_t id;
		wchar_t value;
		UnitType type;
	};

	enum class OperationSymbol
	{
		add,            // +
		subtract,       // -
		multiply,       // *
		division,       // /
		equal,          // ==
		not_equal,      // !=
		greater,        // >
		less,           // <
		greater_equal,  // >=
		less_equal,     // <=
		negation,       // -
		logical_and,    // &&
		logical_or,     // ||
		logical_not,    // !
		bitwise_and,    // &
		bitwise_or,     // |
		bitwise_xor,    // ^
		bitwise_not,    // ~
		left_shift,     // <<
		right_shift,    // >>
		assignment,     // =
		add_assignment  // +=
	};

	struct OperationUnit
	{
		size_t index;
		std::vector<Unit> left;
		bool target_left;
		OperationSymbol up_target;
		std::vector<Unit> right;
		OperationSymbol os;
	};

	enum class ResultType
	{
		Byte,
		Char,
		Wchar,
		Short,
		Int,
		Half,
		Float,
		Double,
		UserDefine
	};

	struct Result
	{
		ResultType rt;
		std::wstring user_define_type;
		void* value = nullptr; // 指向实际值的指针
	};
}