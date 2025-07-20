#include <super/compile/SDEF/sdef_analysis.h>
#include <filesystem>
#include <super/tool/file.h>
#include <super/tool/string.h>
#include <super/compile/global_data.h>
#include <super/compile/remove_note.h>
#include <super/compile/lexical_analysis/extract_token.h>
#include <iostream>
#include <super/compile/lexical_analysis/processing_preprocessing.h>
#include <super/compile/lexical_analysis/parenthesis.h>

namespace Super::Compile::SDEF
{
	AnalysisSDEFFile::AnalysisSDEFFile(const std::wstring& importFilePath, const std::wstring& inputFilePath)
	{
		if (!std::filesystem::exists(importFilePath))
		{
			SUPER_ERROR_THROW_CODE_NONE(importFilePath, L"100030");
		}
		_importFilePath = std::filesystem::absolute(importFilePath).wstring();
		Super::Compile::GlobalData::SDEF[_importFilePath] = {};
		std::wstring fileContent = Super::Tool::File::ReadFileAllContent(_importFilePath);

		// 去除注释
		Super::Compile::GlobalData::FileDataList[_importFilePath] =
			Super::Compile::RemoveNote(fileContent).GetData();

		std::wcout << Tool::String::ListToStringWithLineNumbers(Super::Compile::GlobalData::FileDataList[_importFilePath]) << std::endl;

		// 提取 Token
		_tokens = Super::Compile::LexicalAnalysis::ExtractToken(_importFilePath).GetTokenStream();

		if (_tokens.empty())
		{
			SUPER_ERROR_THROW_CODE_NONE(importFilePath, L"100040");
		}

		// 括号匹配
		Super::Compile::LexicalAnalysis::Parenthesis(_importFilePath, _tokens);

		// 预处理指令处理
		Super::Compile::LexicalAnalysis::ProcessingPreprocessing(_importFilePath, _tokens, inputFilePath);

		std::wcout << Super::Tool::String::TokenToString(_tokens) << std::endl;
	}
}