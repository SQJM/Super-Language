#include <super/tool/file.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unicode/ucsdet.h>
#include <unicode/ucnv.h>
#include <unicode/unistr.h>
#include <unicode/ustream.h>

namespace Super::Tool::File
{
    std::wstring ReadFileAllContent(const std::wstring& filePath)
    {
        std::wifstream file(filePath, std::ios::binary);
        if (!file.is_open())
        {
            throw std::runtime_error("无法打开文件");
        }

        std::wstringstream buffer;
        buffer << file.rdbuf();
        file.close();
        return buffer.str();
    }
}