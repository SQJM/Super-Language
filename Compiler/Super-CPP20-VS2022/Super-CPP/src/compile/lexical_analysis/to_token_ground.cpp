#include <super/compile/lexical_analysis/to_token_group.h>
#include <super/error.h>

namespace Super::Compile::LexicalAnalysis
{

	namespace ToTokenGroupRule
	{
		std::unordered_map<std::wstring, std::vector<std::wstring>> StateDispose =
			{
				{L"import", {L""}}};

		std::unordered_map<std::wstring, std::vector<std::wstring>> SymbolStateDispose =
			{};
	}

	const std::vector<std::wstring> Keyword =
		{
			L"delete",
			L"throw",
			L"sizeof",
			L"type_name",
			L"module",
			L"exports",
			L"export",
			L"template",
			L"import",
			L"type_cast",
			L"direct_cast",
			L"class_cast",
			L"null",
			L"nullptr",
			L"typedef",
			L"#include_asm",
			L"#import_sdp",
			L"#define_pro"};

	ToTokenGroup::ToTokenGroup(const std::wstring &inputFilePath, std::vector<Super::Type::Token> &tokens)
	{
		_tokens = tokens;
		for (size_t i = 0; i < tokens.size(); i++)
		{
			Super::Type::Token token = tokens[i];
			std::wstring value = token.value;
			if (token.name == Super::Type::TokenName::None)
			{
			}
			else if (token.name == Super::Type::TokenName::Symbols)
			{
				if (ToTokenGroupRule::SymbolStateDispose.find(value) == ToTokenGroupRule::SymbolStateDispose.end())
				{
					SUPER_ERROR_THROW_CODE(inputFilePath, L"400060", token)
				}
				// ToTokenGroupRule::SymbolStateDispose[value](i);
			}
			else if (token.name == Super::Type::TokenName::String)
			{
				std::wclog << L"没有使用的字符串";
				continue;
			}
			else
			{
				if (ToTokenGroupRule::SymbolStateDispose.find(value) == ToTokenGroupRule::SymbolStateDispose.end())
				{
					SUPER_ERROR_THROW_CODE(inputFilePath, L"400070", token)
				}

				if (IsMemberScope(value))
				{
				}
				else if (IsNamespaceScope(value))
				{
				}
				else if (IsCallFunction(value))
				{
				}
				else if (IsDeclarationVar(value))
				{
				}
				else if (IsDeclarationFunction(value))
				{
				}
				else if (IsDefineVar(value))
				{
				}
				else if (IsDefineFunction(value))
				{
				}
				else if (IsDefineScope(value))
				{
				}
				else if (IsControlFlow(value))
				{
				}
				else if (Keyword.end() != std::ranges::find(Keyword, value))
				{
				}
				else
				{
					SUPER_ERROR_THROW_CODE(inputFilePath, L"100020", token)
				}
			}
		}
	}

	Super::Type::TokenGroup::Scope ToTokenGroup::ToTokenGroupData()
	{
		return scope;
	}

	bool ToTokenGroup::IsMemberScope(const std::wstring &value)
	{
		return value == L"class" || value == L"struct" || value == L"union" || value == L"enum";
	}

	bool ToTokenGroup::IsNamespaceScope(const std::wstring &value)
	{
		return value == L"namespace";
	}

	bool ToTokenGroup::IsCallFunction(const std::wstring &value)
	{
		return false;
	}

	bool ToTokenGroup::IsDeclarationVar(const std::wstring &value)
	{
		return false;
	}

	bool ToTokenGroup::IsDeclarationFunction(const std::wstring &value)
	{
		return false;
	}

	bool ToTokenGroup::IsDefineVar(const std::wstring &value)
	{
		return false;
	}

	bool ToTokenGroup::IsDefineFunction(const std::wstring &value)
	{
		return false;
	}

	bool ToTokenGroup::IsDefineScope(const std::wstring &value)
	{
		return false;
	}

	bool ToTokenGroup::IsControlFlow(const std::wstring &value)
	{
		return value == L"if" || value == L"while" || value == L"for" || value == L"do" || value == L"loop" || value == L"switch" || value == L"result" || value == L"if_return";
	}

}