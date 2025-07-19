#include <super/compile/lexical_analysis/extract_token.h>
#include <fstream>
#include <algorithm>
#include <super/keyword.h>
#include <iostream>
#include <super/tool/string.h>
#include <super/compile/global_data.h>

namespace Super::Compile::LexicalAnalysis
{
	void ExtractToken::AddTokens(size_t line, size_t column, Super::Type::TokenName &tokenName, std::wostringstream &v)
	{
		std::wstring value = v.str();
		if (value.size() > 0 && !value.empty())
		{
			if (tokenName == Super::Type::TokenName::String || tokenName == Super::Type::TokenName::Char)
			{
				goto end;
			}

			if (isDefineName)
			{
				if (tokenName != Super::Type::TokenName::None)
				{
					SUPER_ERROR_THROW_CODE(inputFilePath, L"000000", Super::Type::Token(line + 1, column, tokenName, L""));
				}
				isLineToOneToken = true;
				isDefineName = false;
				goto end;
			}
			else if (isSetDefineName)
			{
				if (tokenName != Super::Type::TokenName::None)
				{
					SUPER_ERROR_THROW_CODE(inputFilePath, L"000010", Super::Type::Token(line + 1, column));
				}
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
				if (value == L"#define")
				{
					isDefineName = true;
					goto end;
				}
				else if (
					value == L"#undef" || value == L"#ifdef" || value == L"#ifndef")
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
			v.str(L"");
		}
	}

	void ExtractToken::ClearNullToken()
	{
		tokens.erase(std::remove_if(tokens.begin(), tokens.end(), [](const Super::Type::Token &token)
									{ return token.name == Super::Type::TokenName::Null; }),
					 tokens.end());
	}

	void ExtractToken::ProcessStrings(size_t &l, size_t &i, const std::vector<wchar_t> &lineData, std::wostringstream &temp, const Super::Type::TokenName &tokenName) const
	{
		bool escape = false;
		i++;
		for (; i < lineData.size(); i++)
		{
			wchar_t c = lineData[i];

			if (c == L'\n' && (temp.str().size() == 0 || temp.str().empty()))
			{
				SUPER_ERROR_THROW_CODE(inputFilePath, L"100000", Super::Type::Token(l + 1, i));
			}

			if (escape)
			{
				temp << c;
				escape = false;
			}
			else
			{
				if (c == L'\\' && !escape)
				{
					// 遇到转义符
					escape = true;
				}
				else if ((c == L'"' || c == L'\'') && !escape)
				{
					if (i + 1 < lineData.size() &&
						Super::Keyword::StringAfterTheSymbols.end() == std::ranges::find(Super::Keyword::StringAfterTheSymbols, std::wstring(1, lineData[i + 1])))
					{
						SUPER_ERROR_THROW_CODE(inputFilePath, L"100010", Super::Type::Token(l + 1, i + 1));
					}
					temp << c;
					return;
				}
				temp << c;
			}
		}
	}

	ExtractToken::ExtractToken(const std::wstring &path)
	{
		inputFilePath = path;
		std::vector<std::wstring> data = Super::Compile::GlobalData::FileDataList[inputFilePath];
		std::wstring line;
		std::wostringstream temp;
		Super::Type::TokenName tokenName = Super::Type::TokenName::None;

		// 提取 Token
		for (size_t i = 0; i < data.size(); i++)
		{
			std::vector<wchar_t> lineData(data[i].begin(), data[i].end());
			if (lineData.empty())
			{
				continue;
			}

			size_t lineLength = lineData.size();
			lineData.emplace_back(L'\n');
			for (size_t j = 0; j < lineLength; j++)
			{
				wchar_t c = lineData[j];
				if (isLineToOneToken)
				{
					if (c == L'\\' && lineData[j + 1] == L'\n')
					{
						continue;
					}
					else if (c == L';')
					{
						AddTokens(i, j, tokenName, temp);
						isLineToOneToken = false;
						temp << L";";
						tokenName = Super::Type::TokenName::Symbols;
						AddTokens(i, j, tokenName, temp);
						break;
					}
					temp << c;
					continue;
				}

				if (c == L'"' || c == L'\'')
				{
					if (lineData[j + 1] == L'\n')
					{
						SUPER_ERROR_THROW_CODE(inputFilePath, L"100000", Super::Type::Token(i + 1, j + 1));
					}
					AddTokens(i, j, tokenName, temp);
					temp << c;
					if (c == L'"')
						tokenName = Super::Type::TokenName::String;
					else if (c == L'\'')
						tokenName = Super::Type::TokenName::Char;
					ProcessStrings(i, j, lineData, temp, tokenName);
					continue;
				}

				if (c == L'\n')
				{
					AddTokens(i, j, tokenName, temp);
					break;
				}
				else if (Super::Tool::String::IsWhitespace(c))
				{
					AddTokens(i, j, tokenName, temp);
					continue;
				}
				else if (Super::Keyword::Contains(lineData[j], Super::Keyword::Symbols))
				{
					AddTokens(i, j, tokenName, temp);
					tokenName = Super::Type::TokenName::Symbols;
					temp << c;
					continue;
				}
				else if (tokenName == Super::Type::TokenName::Symbols && !Super::Keyword::Contains(lineData[j], Super::Keyword::Symbols))
				{
					AddTokens(i, j, tokenName, temp);
					temp << c;
					continue;
				}

				temp << c;
			}
		}

		const std::vector<std::wstring> Symbols =
			{
				L"-",
				L"+",
				L"/",
				L"*",
				L".",
				L"|",
				L"^",
				L"&",
				L",",
				L"{"};
		for (size_t i = 0; i < tokens.size(); i++)
		{
			if (tokens[i].value == L";" && i + 1 < tokens.size() && Symbols.end() != std::ranges::find(Symbols, tokens[i + 1].value))
			{
				tokens[i] = Super::Type::GetNullToken();
			}
		}
		ClearNullToken();
	}

	std::vector<Super::Type::Token> ExtractToken::GetTokenStream() const
	{
		return tokens;
	}
}