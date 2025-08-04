#include <super/compile/lexical_analysis/processing_preprocessing.h>
#include <super/compile/global_data.h>
#include <super/error.h>
#include <iostream>
#include <super/tool/string.h>
#include <super/compile/project_config.h>
#include <filesystem>
#include <super/compile/SDEF/sdef_analysis.h>
#include <stack>

namespace Super::Compile::LexicalAnalysis
{
	struct BuiltInMacro
	{
		size_t index;
		std::wstring name;
	};

	static void BatchProductionSetNull(bool boolean, std::vector<Super::Type::Token>& tokens, size_t i)
	{
		int count = 1;
		for (; i < tokens.size(); i++)
		{
			Super::Type::Token token = tokens[i];

			if (token.value == L"#ifdef" || token.value == L"#ifndef" || token.value == L"#if")
			{
				count++;
			}
			else if (token.value == L"#endif")
			{
				count--;
			}

			if (!boolean || count == 0)
			{
				tokens[i] = Super::Type::GetNullToken();
			}

			if (count == 0)
			{
				tokens[i + 1] = Super::Type::GetNullToken();
				break;
			}
		}
	}

	static void LogicalRecursion(const std::wstring& inputFilePath, std::vector<Super::Type::Token>& tokens, size_t i)
	{
		Super::Type::Token token = tokens[i];
		Super::Type::Token nextToken = tokens[i + 1];

		bool isCondition = false;

		if (token.value == L"#ifdef" || token.value == L"#ifndef")
		{
			std::unordered_map<std::wstring, std::wstring>* ds = &Super::Compile::GlobalData::FileCompileDataList[inputFilePath].Define;
			if (token.value == L"#ifdef")
			{
				isCondition = ds->find(nextToken.value) != ds->end();
			}
			else if (token.value == L"#ifndef")
			{
				isCondition = ds->find(nextToken.value) == ds->end();
			}
			ds = nullptr;
			tokens[i] = Super::Type::GetNullToken();
			tokens[i + 1] = Super::Type::GetNullToken();
			tokens[i + 2] = Super::Type::GetNullToken();
			BatchProductionSetNull(isCondition, tokens, i + 3);
		}
		else if (token.value == L"#if")
		{
			// == != > < >= <=
		}
	}

	ProcessingPreprocessing::ProcessingPreprocessing(const std::wstring& inputFilePath, std::vector<Super::Type::Token>& tokens, std::wstring parentFile)
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
			else if (i + 1 >= tokens.size())
			{
				SUPER_ERROR_THROW_CODE(inputFilePath, L"000130", token)
			}

			Super::Type::Token nextToken = tokens[i + 1];

			if (token.value == L"#import" || token.value == L"#unimport")
			{
				if (nextToken.name != Super::Type::TokenName::String)
				{
					SUPER_ERROR_THROW_CODE(inputFilePath, L"000030", nextToken)
				}
				std::wstring file = Super::Tool::String::RemoveFirstAndLastChar(nextToken.value);
				if (parentFile == file)
				{
					SUPER_ERROR_THROW_CODE(inputFilePath, L"300000", nextToken)
				}
				if (file.empty() || file.size() == 5)
				{
					SUPER_ERROR_THROW_CODE(inputFilePath, L"000070", nextToken)
				}
				SetNull({ i, i + 1 }, tokens);
				bool isModulePath = false;
				if (file.at(0) == L':')
				{
					file = file.substr(1);
					isModulePath = true;
				}
				else if (file.at(0) == L'.' && file.at(1) == L'/')
				{
					std::filesystem::path filePath = inputFilePath;
					file = filePath.parent_path().wstring() + file.substr(1);
				}
				Super::Project::ReplaceImportPathString(file, isModulePath);
				if (token.value == L"#import")
				{
					if (Super::Compile::GlobalData::SDEF.find(inputFilePath) == Super::Compile::GlobalData::SDEF.end())
					{
						Super::Compile::SDEF::AnalysisSDEFFile(file, inputFilePath);
					}
					for (const auto& pair : Super::Compile::GlobalData::SDEF[inputFilePath])
					{
						Super::Compile::GlobalData::FileCompileDataList[parentFile].Define[pair.first] = pair.second;
					}
				}
				else if (token.value == L"#unimport")
				{
					if (Super::Compile::GlobalData::SDEF.find(inputFilePath) == Super::Compile::GlobalData::SDEF.end())
					{
						SUPER_ERROR_THROW_CODE(inputFilePath, L"100100", token)
					}
					for (const auto& pair : Super::Compile::GlobalData::SDEF[inputFilePath])
					{
						Super::Compile::GlobalData::FileCompileDataList[parentFile].Define.erase(pair.first);
					}
				}
			}
			else if (token.value == L"#define")
			{
				if (i + 2 < tokens.size() && tokens[i + 2].name == Super::Type::TokenName::DefineValue)
				{
					Super::Compile::GlobalData::FileCompileDataList[inputFilePath].Define[nextToken.value] = tokens[i + 2].value;
				}
				else
				{
					Super::Compile::GlobalData::FileCompileDataList[inputFilePath].Define[nextToken.value] = L"";
				}
			}
			else if (token.value == L"#ifdef" || token.value == L"#ifndef" || token.value == L"#if")
			{
				LogicalRecursion(inputFilePath, tokens, i);
			}
			// TODO: 我希望如果开启 DEBUG 模式的话下面的输出可以带上 文件,行号
			else if (token.value == L"#error")
			{
				if (nextToken.name != Super::Type::TokenName::String)
				{
					SUPER_ERROR_THROW_CODE(inputFilePath, L"000060", nextToken)
				}
				std::wcerr << "ERROR: " << Super::Tool::String::RemoveFirstAndLastChar(nextToken.value) << std::endl;
				SetNull({ i, i + 1 }, tokens);
			}
			else if (token.value == L"#message")
			{
				if (nextToken.name != Super::Type::TokenName::String)
				{
					SUPER_ERROR_THROW_CODE(inputFilePath, L"000080", nextToken)
				}
				std::wcout << "MESSAGE: " << Super::Tool::String::RemoveFirstAndLastChar(nextToken.value) << std::endl;
				SetNull({ i, i + 1 }, tokens);
			}
			else if (token.value == L"#elif" || token.value == L"#else" || token.value == L"#endif")
			{
				SUPER_ERROR_THROW_CODE(inputFilePath, L"100020", token)
			}
		}

		// 替换所有内置编译信息宏
		// TODO: 如果编译信息宏被定义了，则不替换

		ClearNullToken(tokens);
	}

	void ProcessingPreprocessing::LogicalEndMatching(const std::wstring& inputFilePath, std::vector<Super::Type::Token>& tokens)
	{
		std::stack<Super::Type::Token> stack;

		for (const auto& token : tokens)
		{
			const std::wstring& str = token.value;

			if (str == L"#endif")
			{
				if (stack.empty())
				{
					SUPER_ERROR_THROW_CODE(inputFilePath, L"300010", token);
				}
				else
				{
					stack.pop();
				}
			}
			else if (str == L"#ifdef" || str == L"#ifndef" || str == L"#if")
			{
				stack.push(token);
			}
		}

		if (!stack.empty())
		{
			while (!stack.empty())
			{
				const auto& token = stack.top();
				SUPER_ERROR_CODE_CACHE(inputFilePath, L"", token);
				stack.pop();
			}
			SUPER_ERROR_CACHE_OUT
		}
	}
}