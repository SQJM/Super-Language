#pragma once
#include <string>
#include <unordered_map>

namespace Super::Project
{
	struct ProjectConfigData
	{
		std::wstring ProjectName;
		// 项目导入路径字符串宏
		std::unordered_map<std::wstring, std::wstring> ProjectImportPathStringMacro;
		ProjectConfigData() = default;
	};

	extern ProjectConfigData ProjectConfig;

	void ReplaceImportPathString(std::wstring& str, bool isModue);
}