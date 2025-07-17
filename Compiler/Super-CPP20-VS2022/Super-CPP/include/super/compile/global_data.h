#pragma once
#include <unordered_map>
#include <string>
#include <super/type/token.h>

namespace Super::Compile::GlobalData
{
    class SDP_Data
    {};

    class SPM_Data
    {};

    struct CurrentFileCompileData
    {
        std::unordered_map<std::wstring, std::wstring> Define;

        // 导入的模块
		Super::Type::Token ImportModuleKeyword;
        std::vector<Super::Type::Token> ImportModuleNamespace;

		// 导入的高级宏
        Super::Type::Token ImportSDPKeyword;
        Super::Type::Token ImportSDPFilePath;

		// 导入的汇编文件
		Super::Type::Token ImportASMKeyword;
		Super::Type::Token ImportASMFilePath;

        CurrentFileCompileData();
    };

    extern SDP_Data SDP;
    extern SPM_Data SPM;
    extern std::unordered_map<std::wstring, CurrentFileCompileData> FileCompileDataList;
    extern std::unordered_map<std::wstring, std::vector<std::wstring>> FileDataList;
}