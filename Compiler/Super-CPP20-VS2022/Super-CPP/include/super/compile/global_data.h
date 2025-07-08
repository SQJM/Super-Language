#pragma once
#include <unordered_map>
#include <string>

namespace Super::Compile::GlobalData
{
    class SDP_Data
    {};

    class SPM_Data
    {};

    struct CurrentFileCompileData
    {
        std::unordered_map<std::wstring, std::wstring> Define;

        CurrentFileCompileData();
    };

    extern SDP_Data SDP;
    extern SPM_Data SPM;
    extern std::unordered_map<std::wstring, CurrentFileCompileData> FileCompileDataList;
    extern std::unordered_map<std::wstring, std::vector<std::wstring>> FileDataList;
}