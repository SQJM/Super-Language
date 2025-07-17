#include <super/compile/lexical_analysis/processing_preprocessing.h>
#include <super/compile/global_data.h>

namespace Super::Compile::LexicalAnalysis
{
	struct BuiltInMacro
	{
		size_t index;
		std::wstring name;
	};

	ProcessingPreprocessing::ProcessingPreprocessing(const std::wstring& inputFilePath, std::vector<Super::Type::Token>& tokens)
	{
		for (size_t i = 0; i < tokens.size(); i++)
		{
			Super::Type::Token token = tokens[i];

			if (!Super::Compile::GlobalData::FileCompileDataList[inputFilePath].Define.empty() &&
				token.name == Super::Type::TokenName::None)
			{

			}
			else if (token.name != Super::Type::TokenName::PreprocessingInstructions)
			{
				continue;
			}

			if (token.value == L"#include_asm")
			{

			}
			else if (token.value == L"#import_sdp")
			{

			}
			else if (token.value == L"#define")
			{

			}
			else if (token.value == L"#ifdef")
			{

			}
			else if (token.value == L"#ifndef")
			{

			}
			else if (token.value == L"#if")
			{

			}
			else if (token.value == L"#error")
			{
			}
			else if (token.value == L"#message")
			{

			}
		}

		// 替换所有内置编译信息宏
		// TODO: 如果编译信息宏被定义了，则不替换
	}
}