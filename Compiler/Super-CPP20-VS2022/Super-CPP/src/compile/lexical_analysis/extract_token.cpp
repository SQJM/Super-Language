#include <super/compile/lexical_analysis/extract_token.h>
#include <fstream>
#include <algorithm>
#include <super/keyword.h>
#include <iostream>
#include <super/tool/string.h>
#include <super/compile/global_data.h>

namespace Super::Compile::LexicalAnalysis
{
	void ExtractToken::AddTokens(size_t line, size_t column, Super::Type::TokenName& tokenName, std::ostringstream& v)
	{
		std::string value = v.str();
		if (value.size() > 0 && !value.empty())
		{
			if (tokenName == Super::Type::TokenName::String || tokenName == Super::Type::TokenName::Char)
			{
				goto end;
			}

			if (isDefineName)
			{
				isLineToOneToken = true;
				isDefineName = false;
				tokenName = Super::Type::TokenName::DefineName;
				goto end;
			}
			else if (isSetDefineName)
			{
				isSetDefineName = false;
				tokenName = Super::Type::TokenName::DefineName;
				goto end;
			}
			else if (isLineToOneToken)
			{
				tokenName = Super::Type::TokenName::DefineValue;
				goto end;
			}

			if (Super::Keyword::Contains(value, Super::Keyword::TypeKeywords))
			{
				tokenName = Super::Type::TokenName::TypeKeywords;
			}
			else if (Super::Keyword::Contains(value, Super::Keyword::PreprocessingInstructions))
			{
				tokenName = Super::Type::TokenName::PreprocessingInstructions;
				if (value == "#define")
				{
					isDefineName = true;
					goto end;
				}
				else if (
					value == "#undef"
					|| value == "#ifdef"
					|| value == "#ifndef"
					)
				{
					isSetDefineName = true;
					goto end;
				}
			}
			else if (Super::Keyword::Contains(value, Super::Keyword::Modifier))
			{
				tokenName = Super::Type::TokenName::ModifierKeyword;
			}
			else if (Super::Keyword::Contains(value, Super::Keyword::Other))
			{
				tokenName = Super::Type::TokenName::OtherKeywords;
			}
			else if (Super::Keyword::Contains(value, Super::Keyword::ControlFlow))
			{
				tokenName = Super::Type::TokenName::ControlFlowKeywords;
			}
		end:
			tokens.emplace_back(line + 1, column, tokenName, value);
			tokenName = Super::Type::TokenName::None;
			v.str("");
		}
	}

	void ExtractToken::ClearNullToken()
	{
		tokens.erase(std::remove_if(tokens.begin(), tokens.end(), [](const Super::Type::Token& token)
			{
				return token.name == Super::Type::TokenName::Null;
			}),
			tokens.end());
	}

	ExtractToken::ExtractToken(const std::string& inputFilePath)
	{
		std::vector<std::string> data = Super::Compile::GlobalData::FileDataList[inputFilePath];
		std::string line;

		std::ostringstream temp;
		bool escape = false;
		bool isStringOrCharStart = false;
		int state = 0; // 0:普通代码 1:字符串
		bool upString = false;
		bool isContinueLineToOneToken = false;
		Super::Type::TokenName tokenName = Super::Type::TokenName::None;

		// 提取 Token
		for (size_t i = 0; i < data.size(); i++)
		{
			std::vector<char> lineData(data[i].begin(), data[i].end());
			if (lineData.empty())
			{
				continue;
			}
			size_t lineLength = lineData.size();
			lineData[lineLength-1] = '\n';
			for (size_t j = 0; j < lineLength; j++)
			{
				char c = lineData[j];
				if (isLineToOneToken)
				{
					if (isContinueLineToOneToken)
					{
						isContinueLineToOneToken = false;
						continue;
					}
					if (c == '\\' && lineData[j+1] == '\n')
					{
						isContinueLineToOneToken = true;
						continue;
					}
					else if (!isContinueLineToOneToken && c == '\n')
					{
						AddTokens(i, j, tokenName, temp);
						isLineToOneToken = false;
						break;
					}
					temp << c;
					continue;
				}
				if (isStringOrCharStart)
				{
					isStringOrCharStart = false;
				}
				if (upString && !Super::Tool::String::IsWhitespace(c))
				{
					if (!Super::Keyword::Contains(c, Super::Keyword::SplitSymbols))
					{
						SUPER_ERROR_A(inputFilePath, "100000", Super::Type::Token(i + 1, j, tokenName, ""));
					}
					else
					{
						upString = false;
					}
				}

				if (state == 0 && (c == '"' || c == '\''))
				{
					state = 1;
					isStringOrCharStart = true;
				}

				if (c == '\n')
				{
					if (isStringOrCharStart)
					{
						SUPER_ERROR_A(inputFilePath, "100000", Super::Type::Token(i + 1, j, tokenName, ""));
					}
					AddTokens(i, j, tokenName, temp);
					upString = false;
					break;
				}
				else if (state != 1 && Super::Tool::String::IsWhitespace(c))
				{
					AddTokens(i, j, tokenName, temp);
					continue;
				}
				else if (state == 0 && Super::Keyword::Contains(lineData[j], Super::Keyword::SplitSymbols))
				{
					AddTokens(i, j, tokenName, temp);
					tokenName = Super::Type::TokenName::Symbols;
					temp << c;
					continue;
				}
				else if (tokenName == Super::Type::TokenName::Symbols && !Super::Keyword::Contains(lineData[j], Super::Keyword::SplitSymbols))
				{
					AddTokens(i, j, tokenName, temp);
					temp << c;
					continue;
				}

				if (state == 1 && isStringOrCharStart && c == '"')
					tokenName = Super::Type::TokenName::String;
				else if (state == 1 && isStringOrCharStart && c == '\'')
					tokenName = Super::Type::TokenName::Char;

				if (escape)
				{
					temp << c;
					escape = false;
				}
				else
				{
					if (state == 0)
					{
						temp << c;
					}
					else if (state == 1)
					{
						if (c == '\\' && !escape)
						{ // 遇到转义符
							escape = true;
						}
						else if (!isStringOrCharStart && (c == '"' || c == '\'') && !escape)
						{ // 遇到字符串结束
							state = 0;
							upString = true;
						}
						temp << c;
					}
				}
			}
		}
	}

	std::vector<Super::Type::Token> ExtractToken::GetTokenStream() const
	{
		return tokens;
	}
}