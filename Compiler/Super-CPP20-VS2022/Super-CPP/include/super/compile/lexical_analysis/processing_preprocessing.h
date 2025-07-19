#pragma once
#include <string>
#include <vector>
#include <super/type/token.h>

namespace Super::Compile::LexicalAnalysis
{
	class ProcessingPreprocessing
	{
	public:
		ProcessingPreprocessing(const std::wstring& inputFilePath, std::vector<Super::Type::Token>& tokens, std::wstring parentFile = L"");

	private:
	};
}