#include <super/info.h>
#include <string>

namespace Super::Info
{
	std::string GetVersionInfo()
	{
		return
			"Version: " + Version + "\n" +
			"Version Code: " + std::to_string(VersionCode) + "\n" +
			"Build Type: " + VersionBuildType + "\n" +
			"Build Date: " + BuildDate + "\n" +
			"Short: " + VersionBuildType.substr(0, 1) + std::to_string(VersionCode).substr(0, 2);
	}
}