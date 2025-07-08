#include <super/info.h>
#include <string>

namespace Super::Info
{
	std::wstring GetVersionInfo()
	{
		return
			L"Version: " + Version + L"\n" +
			L"Version Code: " + std::to_wstring(VersionCode) + L"\n" +
			L"Build Type: " + VersionBuildType + L"\n" +
			L"Build Date: " + BuildDate + L"\n" +
			L"Short: " + VersionBuildType.substr(0, 1) + std::to_wstring(VersionCode).substr(0, 2);
	}
}