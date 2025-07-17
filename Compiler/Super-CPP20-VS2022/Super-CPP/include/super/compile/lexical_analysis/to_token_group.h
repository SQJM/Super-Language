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
	namespace ToTokenGroupRule
	{
		extern std::unordered_map<std::wstring, std::vector<std::wstring>> StateDispose;
		extern std::unordered_map<std::wstring, std::vector<std::wstring>> SymbolStateDispose;
	}

	class ToTokenGroup
	{
	public:
		ToTokenGroup(const std::wstring& inputFilePath, std::vector<Super::Type::Token>& tokens);

		Super::Type::TokenGroup::Scope ToTokenGroupData();
	private:
		Super::Type::TokenGroup::Scope scope;
		std::wstring _inputFilePath;
		std::vector<Super::Type::Token> _tokens;

		bool IsMemberScope(const std::wstring& value);
		bool IsNamespaceScope(const std::wstring& value);
		bool IsCallFunction(const std::wstring& value);
		bool IsDeclarationVar(const std::wstring& value);
		bool IsDeclarationFunction(const std::wstring& value);
		bool IsDefineVar(const std::wstring& value);
		bool IsDefineFunction(const std::wstring& value);
		bool IsDefineScope(const std::wstring& value);
		bool IsControlFlow(const std::wstring& value);
	};
}