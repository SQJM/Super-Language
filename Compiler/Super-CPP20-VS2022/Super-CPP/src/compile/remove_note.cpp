#include <super/compile/remove_note.h>
#include <sstream>
#include <iostream>

namespace Super::Compile
{
	RemoveNote::RemoveNote(const std::wstring& fileData)
	{
        short state = 0; // 0:普通代码 1:单行注释 2:多行注释 3:字符串
        bool escape = false;
        std::wistringstream iss(fileData);
        std::wstring line;
        while (std::getline(iss, line, L'\n'))
        {
            std::wstring newLine;
            line += L" ";
            for (size_t i = 0; i < line.size(); ++i)
            {
                wchar_t c = line[i];
                if (c == L'\n')
                {
                    continue;
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
                        state = 3; // 进入字符串状态
                    }
                    else if (c == L';')
                    {
                        if (i + 1 < line.size() && line[i + 1] == L'-')
                        {
                            state = 2; // 进入多行注释状态
                        }
                        else
                        {
                            state = 1; // 进入单行注释状态
                        }
                        continue;
                    }
                    newLine += c;
                }
                else if (state == 1)
                {
                    state = 0;
                    break;
                }
                else if (state == 2)
                {
                    if (c == L'\\') escape = true; // 遇到转义符
                    else if (!escape && c == L'-' && i + 1 < line.size() && line[i + 1] == L';')
                    {
                        state = 0; // 遇到多行注释结束
                    }
                }
                else if (state == 3)
                { // 字符串状态
                    if (c == L'\\' && !escape) escape = true; // 遇到转义符
                    else if ((c == L'\'' || c == L'"') && !escape) state = 0; // 遇到字符串结束
                    newLine += c;
                }
            }
            if (state == 2)
            {
                _data.emplace_back(L"");
            }
            if (state != 1 && state != 2)
            {
                _data.emplace_back(newLine);
            }
        }
	}

	std::vector<std::wstring> RemoveNote::GetData() const
	{
		return _data;
	}
}