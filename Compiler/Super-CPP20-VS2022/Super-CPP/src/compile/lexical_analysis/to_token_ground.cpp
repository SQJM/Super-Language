#include <super/compile/lexical_analysis/to_token_group.h>
#include <super/error.h>

namespace Super::Compile::LexicalAnalysis
{
	ToTokenGroup::ToTokenGroup(const std::wstring& inputFilePath, std::vector<Super::Type::Token>& tokens)
	{
		_tokens = tokens;
		init();
		for (size_t i = 0; i < tokens.size(); i++)
		{
			Super::Type::Token token = tokens[i];
			std::wstring value = token.value;
			if (token.name == Super::Type::TokenName::None)
			{

			}
			else if (token.name == Super::Type::TokenName::Symbols)
			{
				if (SymbolStateDispose.find(value) == SymbolStateDispose.end())
				{
					SUPER_ERROR_THROW_A(inputFilePath, L"400060", token)
				}
				SymbolStateDispose[value](i);
			}
			else if (token.name == Super::Type::TokenName::String)
			{
				std::wclog << L"没有使用的字符串";
				continue;
			}
			else
			{
				if (SymbolStateDispose.find(value) == SymbolStateDispose.end())
				{
					SUPER_ERROR_THROW_A(inputFilePath, L"400070", token)
				}
				StateDispose[value](i);
			}
		}
	}

	Super::Type::TokenGroup ToTokenGroup::ToTokenGroupData()
	{
		return tokenGroup;
	}

	void ToTokenGroup::init()
	{
		StateDispose[L""] = [](size_t& i)
			{

			};


		SymbolStateDispose[L""] = [](size_t& i)
			{

			};
	}
}