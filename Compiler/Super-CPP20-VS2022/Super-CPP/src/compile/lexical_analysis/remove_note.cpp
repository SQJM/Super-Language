#include <super/compile/lexical_analysis/remove_note.h>
#include <sstream>
#include <iostream>

namespace Super::Compile::LexicalAnalysis
{
	RemoveNote::RemoveNote(const std::string& fileData)
	{
		short state = 0; // 0:普通代码 1:单行注释 2:多行注释 3:字符串
		bool escape = false;
		std::istringstream iss(fileData);
		std::string line;
		int inn = 0;
		while (std::getline(iss, line, '\n'))
		{
			std::string newLine;
			line += " ";
			for (size_t i = 0; i < line.size(); ++i)
			{
				char c = line[i];
				if (c == '\r')
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
					if (c == '"' || c == '\'')
					{
						state = 3; // 进入字符串状态
					}
					else if (c == ';')
					{
						if (i + 1 < line.size() && line[i + 1] == '-')
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
					if (c == '\\') escape = true; // 遇到转义符
					else if (!escape && c == '-' && i + 1 < line.size() && line[i + 1] == ';')
					{
						state = 0; // 遇到多行注释结束
					}
				}
				else if (state == 3)
				{ // 字符串状态
					if (c == '\\' && !escape) escape = true; // 遇到转义符
					else if ((c == '\'' || c == '"') && !escape) state = 0; // 遇到字符串结束
					newLine += c;
				}
			}
			if (state == 2)
			{
				_data.emplace_back("");
			}
			if (state != 1 && state != 2)
			{
				_data.emplace_back(newLine);
			}
		}
	}

	std::vector<std::string> RemoveNote::GetData() const
	{
		return _data;
	}
}