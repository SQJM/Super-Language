#pragma once
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>

namespace Super::Info
{
	const std::wstring VersionBuildType = L"preview";
	const std::wstring Version = L"1.0.0";
	const int VersionCode = 100;
	const std::wstring BuildDate =
		[]()
		{
			std::time_t now = std::time(nullptr);
			std::tm now_tm;
			localtime_s(&now_tm, &now);
			std::wostringstream oss;
			oss << std::put_time(&now_tm, L"%Y/%m/%d %H:%M:%S");
			return oss.str();
		}();

	std::wstring GetVersionInfo();
}