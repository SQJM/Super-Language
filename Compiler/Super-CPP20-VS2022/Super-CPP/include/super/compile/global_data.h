#pragma once
#include <unordered_map>
#include <string>
#include <super/type/token.h>

namespace Super::Compile::GlobalData
{
    struct SDP_Data
    {
        Super::Type::Token ImportKeyword;
        Super::Type::Token ImportFilePath;
        std::wstring ExportPrefix;

        SDP_Data(Super::Type::Token _1 = Super::Type::Token(0,0), Super::Type::Token _2 = Super::Type::Token(0, 0), std::wstring _3 = L"") : ImportKeyword(_1), ImportFilePath(_2), ExportPrefix(_3) {}
    };

    struct SPM_Data
    {
        Super::Type::Token ImportKeyword;
        Super::Type::Token ImportFilePath;
		std::wstring ModuleName;

        SPM_Data(Super::Type::Token _1 = Super::Type::Token(0, 0), Super::Type::Token _2 = Super::Type::Token(0, 0), std::wstring _3 = L"") : ImportKeyword(_1), ImportFilePath(_2), ModuleName(_3)
        {}
    };

    struct CurrentFileCompileData
    {
        std::unordered_map<std::wstring, std::wstring> Define;

        // 导入的模块
        std::vector<std::vector<Super::Type::Token>> ImportModuleList;

        // 高级宏
        SDP_Data sdp;

        CurrentFileCompileData();
    };

    extern SDP_Data SDP; 
    extern SPM_Data SPM;
    extern std::unordered_map<std::wstring, std::unordered_map<std::wstring, std::wstring>> SDEF;

    extern std::unordered_map<std::wstring, CurrentFileCompileData> FileCompileDataList;
    extern std::unordered_map<std::wstring, std::vector<std::wstring>> FileDataList;
}