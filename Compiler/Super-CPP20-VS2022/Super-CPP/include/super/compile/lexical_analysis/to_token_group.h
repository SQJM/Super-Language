#pragma once
#include <string>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <super/type/token.h>
#include <super/type/token_group.h>
#include <super/type/token_grup_name.h>
#include <functional>

namespace Super::Compile::LexicalAnalysis
{
	class ToTokenGroup
	{
	public:
		std::unordered_map<std::wstring, std::function<void(size_t& i)>> StateDispose;
		std::unordered_map<std::wstring, std::function<void(size_t& i)>> SymbolStateDispose;

		ToTokenGroup(const std::wstring& inputFilePath, std::vector<Super::Type::Token>& tokens);

		Super::Type::TokenGroup ToTokenGroupData();
	private:
		Super::Type::TokenGroup tokenGroup;
		std::wstring _inputFilePath;
		std::vector<Super::Type::Token> _tokens;

		void init();
	};
}