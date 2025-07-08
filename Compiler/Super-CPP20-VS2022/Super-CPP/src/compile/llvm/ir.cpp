#include <super/compile/llvm/ir.h>
#include <super/compile/global_data.h>
#include <super/compile/lexical_analysis/extract_token.h>
#include <super/tool/string.h>
#include <super/compile/remove_note.h>
#include <iostream>
#include <super/compile/lexical_analysis/parenthesis.h>
#include <super/compile/lexical_analysis/to_token_group.h>
#include <super/tool/file.h>

namespace Super::Compile::LLVM
{
	IR::IR(const std::wstring& inputFile)
	{
		if (!std::filesystem::exists(inputFile))
		{
			throw std::runtime_error("文件不存在");
		}
		_inputFilePath = std::filesystem::absolute(inputFile).wstring();
		Super::Compile::GlobalData::FileCompileDataList[_inputFilePath] = {};
		std::wstring fileContent = Super::Tool::File::ReadFileAllContent(_inputFilePath);

		// 去除注释
		Super::Compile::GlobalData::FileDataList[_inputFilePath] =
			Super::Compile::RemoveNote(fileContent).GetData();

		//std::wcout << Tool::String::ListToStringWithLineNumbers(Super::Compile::GlobalData::FileDataList[_inputFilePath]) << std::endl;

		// 词法分析
		std::vector<Super::Type::Token> tokens = Super::Compile::LexicalAnalysis::ExtractToken(_inputFilePath).GetTokenStream();

		if (tokens.empty())
		{
			throw std::runtime_error("没有提取到 Token");
		}

		// 括号匹配
		Super::Compile::LexicalAnalysis::Parenthesis(_inputFilePath, tokens);

		//std::wcout << Super::Tool::String::TokenToString(tokens) << std::endl;

		// 转 Token 组
		Super::Type::TokenGroup tg = Super::Compile::LexicalAnalysis::ToTokenGroup(_inputFilePath, tokens).ToTokenGroupData();

		//std::wcout << L"Define List\n" << Super::Tool::String::DictionaryStringToString(Super::Compile::GlobalData::FileCompileDataList[_inputFilePath].Define) << std::endl;
	}

	std::wstring IR::Data()
	{
		std::wstring head = L"; ModuleID = '" + _inputFilePath + L"'\n";
		return head + _ast.GetString();
	}
}