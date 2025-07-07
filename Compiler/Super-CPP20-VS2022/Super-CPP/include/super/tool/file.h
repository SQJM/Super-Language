#pragma once
#include <string>
namespace Super::Tool::File
{
	std::string ReadFileAllContent(const std::string& filePath);
	std::string DetectAndConvertToUTF8(const std::string& filePath);
}