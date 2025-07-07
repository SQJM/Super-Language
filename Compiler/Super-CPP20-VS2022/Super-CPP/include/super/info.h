#pragma once
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>

namespace Super::Info
{
	const std::string VersionBuildType = "preview";
	const std::string Version = "1.0.0";
	const int VersionCode = 100;
	const std::string BuildDate =
		[]()
		{
			std::time_t now = std::time(nullptr);
			std::tm now_tm;
			localtime_s(&now_tm, &now);
			std::ostringstream oss;
			oss << std::put_time(&now_tm, "%Y/%m/%d %H:%M:%S");
			return oss.str();
		}();

	std::string GetVersionInfo();
}