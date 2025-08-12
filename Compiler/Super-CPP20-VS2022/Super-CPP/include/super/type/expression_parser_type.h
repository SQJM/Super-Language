#pragma once
#include <vector>
#include <super/type/super_var.h>
#include <variant>

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
		std::wstring value;
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

	enum class ComparisonOperatorSymbol
	{
		equal,          // ==
		not_equal,      // !=
		greater,        // >
		less,           // <
		greater_equal,  // >=
		less_equal,     // <=
		logical_and,    // &&
		logical_or      // ||
	};

	struct OperationUnit
	{
		size_t index;
		std::vector<Unit> left;
		bool target_left; // 使用上一个计算结果作为左值
		OperationSymbol up_target; // 上级运算符
		std::vector<Unit> right;
		OperationSymbol os;
	};

	struct ExpressionQueue
	{
		// 正常计算队列
		std::stack<Super::Type::ExpressionParser::OperationUnit> _normalQueue;
		// 乘除队列
		std::stack<Super::Type::ExpressionParser::OperationUnit> _multiplyDivideQueue;
		// 括号队列
		std::stack<Super::Type::ExpressionParser::OperationUnit> _bracketQueue;
	};

	struct Expression
	{
	private:
		enum class DataType
		{
			Queue,
			Symbol
		};

		std::vector<std::variant<ExpressionQueue, ComparisonOperatorSymbol>> data;

	public:
		void addQueue(ExpressionQueue value)
		{
			data.emplace_back(value);
		}

		void addSymbol(ComparisonOperatorSymbol value)
		{
			data.emplace_back(value);
		}

		void printData() const
		{
			for (const auto& item : data)
			{
				std::visit(
					[](auto&& arg)
					{
						using T = std::decay_t<decltype(arg)>;
						if constexpr (std::is_same_v<T, ExpressionQueue>)
						{
							;
						}
						else if constexpr (std::is_same_v<T, ComparisonOperatorSymbol>)
						{
							;
						}
					}, item);
			}
		}
	};
}