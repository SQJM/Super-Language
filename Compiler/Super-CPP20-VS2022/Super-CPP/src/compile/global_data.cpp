#include <super/compile/global_data.h>

namespace Super::Compile::GlobalData
{
	SDP_Data SDP;
	SPM_Data SPM;
	std::unordered_map<std::wstring, CurrentFileCompileData> FileCompileDataList;
	std::unordered_map<std::wstring, std::vector<std::wstring>> FileDataList;

	CurrentFileCompileData::CurrentFileCompileData() = default;
}