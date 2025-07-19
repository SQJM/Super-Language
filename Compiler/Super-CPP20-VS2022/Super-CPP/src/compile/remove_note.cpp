#include <super/compile/remove_note.h>
#include <sstream>
#include <iostream>
#include <ranges>
#include <algorithm>
#include <super/tool/string.h>

// 符号
const std::vector<wchar_t> Symbols =
{
	L'$',
	L'!',
	L'-',
	L'+',
	L'/',
	L'*',
	L'=',
	L'\\',
	L'[',
	L'{',
	L'.',
	L':',
	L'?',
	L'(',
	L'|',
	L'^',
	L'&',
	L'%',
	L'<',
	L',',
	L'~',
	L'@'
};

namespace Super::Compile
{
	RemoveNote::RemoveNote(const std::wstring& fileData)
	{
		short state = 0; // 0:普通代码 1:多行注释 2:字符串
		bool escape = false;
		std::wstring line;
		wchar_t upChar = L'\0';

		// 统一换行符为 LF
		std::wstring unifiedFileData = Super::Tool::String::UnifyLineEndings(fileData);

		std::wistringstream unifiedIss(unifiedFileData);

		while (std::getline(unifiedIss, line, L'\n'))
		{
			std::wstring newLine;
			size_t size = line.size();
			for (size_t i = 0; i < size; ++i)
			{
				wchar_t c = line[i];

				if (!Super::Tool::String::IsWhitespace(c))
				{
					upChar = c; // 记录上一个非空白字符
				}

				if (escape)
				{
					newLine += c;
					escape = false;
				}
				else if (state == 0)
				{
					if (c == L'"' || c == L'\'')
					{
						state = 2; // 进入字符串状态
					}
					else if (c == L';')
					{
						if (i + 1 < line.size() && line[i + 1] == L'-')
						{
							state = 1; // 进入多行注释状态
						}
						else
						{
							break; // 进入单行注释状态
						}
						continue;
					}
					newLine += c;
				}
				else if (state == 1)
				{
					if (c == L'\\') escape = true; // 遇到转义符
					else if (!escape && c == L'-' && i + 1 < size && line[i + 1] == L';')
					{
						state = 0; // 遇到多行注释结束
					}
				}
				else if (state == 2)
				{ 
					// 字符串状态
					if (c == L'\\' && !escape && i + 1 < size - 1) escape = true; // 遇到转义符
					else if ((c == L'\'' || c == L'"') && !escape) state = 0; // 遇到字符串结束
					newLine += c;
				}
			}

			if (state != 1 && newLine != L"" && newLine != L";")
			{
				if (Symbols.end() == std::ranges::find(Symbols, upChar))
				{
					newLine += L";";
				}
				_data.emplace_back(newLine);
			}
			else
			{
				_data.emplace_back(L"");
			}
		}
	}

	std::vector<std::wstring> RemoveNote::GetData() const
	{
		return _data;
	}
}