#include <super/compile/project_config.h>
#include <super/tool/string.h>

namespace Super::Project
{
	ProjectConfigData ProjectConfig;

	void ReplaceImportPathString(std::wstring& str, bool isModue)
	{
		if (isModue)
		{

		}
		else
		{
			for (auto& it : ProjectConfig.ProjectImportPathStringMacro)
			{
				Super::Tool::String::ReplaceAll(str, it.first, it.second);
			}
		}
	}

}