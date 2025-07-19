#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <super/type/token.h>

namespace Super::Compile::SDEF
{
	class AnalysisSDEFFile
	{
	public:
		AnalysisSDEFFile(const std::wstring& importFilePath, const std::wstring& inputFilePath);
		std::unordered_map<std::wstring, std::wstring> GetDefineList();
	private:
		std::wstring _importFilePath;
		std::vector<Super::Type::Token> _tokens;
	};
}