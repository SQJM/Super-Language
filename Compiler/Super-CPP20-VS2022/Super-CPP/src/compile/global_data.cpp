#include <super/compile/global_data.h>

namespace Super::Compile::GlobalData
{
	SDP_Data SDP;
	SPM_Data SPM;
	std::unordered_map<std::string, CurrentFileCompileData> FileCompileDataList;
	std::unordered_map<std::string, std::vector<std::string>> FileDataList;

	CurrentFileCompileData::CurrentFileCompileData() = default;
}