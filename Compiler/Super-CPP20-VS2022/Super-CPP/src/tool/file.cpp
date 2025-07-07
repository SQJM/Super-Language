#include <super/tool/file.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <unicode/ucsdet.h>
#include <unicode/ucnv.h>
#include <unicode/unistr.h>
#include <unicode/ustream.h>

namespace Super::Tool::File
{
    std::string ReadFileAllContent(const std::string& filePath)
    {
        std::ifstream file(filePath, std::ios::binary);
        if (!file.is_open())
        {
            throw std::runtime_error("无法打开文件");
        }

        std::vector<char> fileData((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
        return std::string(fileData.begin(), fileData.end());
    }

    std::string DetectAndConvertToUTF8(const std::string& filePath)
    {
        std::ifstream file(filePath, std::ios::binary);
        if (!file.is_open())
        {
            throw std::runtime_error("无法打开文件");
        }

        std::vector<char> fileData((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();

        // 创建一个检测器
        UErrorCode status = U_ZERO_ERROR;
        UCharsetDetector* detector = ucsdet_open(&status);
        if (U_FAILURE(status))
        {
            throw std::runtime_error("无法创建字符集检测器");
        }

        // 提供数据给检测器
        ucsdet_setText(detector, fileData.data(), fileData.size(), &status);

        // 获取检测结果
        const UCharsetMatch* match = ucsdet_detect(detector, &status);
        if (U_FAILURE(status) || match == nullptr)
        {
            ucsdet_close(detector);
            throw std::runtime_error("无法检测文件编码");
        }

        // 获取检测到的编码
        const char* detectedCharset = ucsdet_getName(match, &status);
        if (U_FAILURE(status))
        {
            ucsdet_close(detector);
            throw std::runtime_error("无法获取检测到的编码");
        }

        // 关闭检测器
        ucsdet_close(detector);

        // 打开转换器
        UConverter* converter = ucnv_open(detectedCharset, &status);
        if (U_FAILURE(status))
        {
            throw std::runtime_error("无法打开转换器");
        }

        // 转换为UTF-16
        int32_t u16Length = fileData.size() * 2; // 假设最大长度
        std::vector<UChar> u16Buffer(u16Length);
        ucnv_toUChars(converter, u16Buffer.data(), u16Length, fileData.data(), fileData.size(), &status);
        if (U_FAILURE(status))
        {
            ucnv_close(converter);
            throw std::runtime_error("无法将文件内容转换为UTF-16");
        }

        // 转换为UTF-8
        int32_t u8Length = u16Length * 3; // 假设最大长度
        std::vector<char> u8Buffer(u8Length);
        ucnv_fromUChars(converter, u8Buffer.data(), u8Length, u16Buffer.data(), u16Length, &status);
        if (U_FAILURE(status))
        {
            ucnv_close(converter);
            throw std::runtime_error("无法将文件内容转换为UTF-8");
        }

        ucnv_close(converter);

        return std::string(u8Buffer.begin(), u8Buffer.begin() + u8Length);
    }

}