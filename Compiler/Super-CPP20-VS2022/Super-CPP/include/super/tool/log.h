#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <mutex>

namespace Super::Tool
{

	enum class LogLevel
	{
		Trace, Debug, Info, Warning, Error, Fatal
	};

	class Logger
	{
	public:
		static Logger& Instance();

		void SetLogLevel(LogLevel level);
		void SetLogFile(const std::wstring& filename);

		void Log(LogLevel level, const std::wstring& msg);

		// 流式接口
		class LogStream;
		LogStream operator()(LogLevel level);

	private:
		Logger();
		~Logger();
		LogLevel minLevel;
		std::wofstream file;
		std::mutex mtx;
	};

	class Logger::LogStream
	{
	public:
		LogStream(Logger& logger, LogLevel level);
		~LogStream();

		template<typename T>
		LogStream& operator<<(const T& val)
		{
			ss << val;
			return *this;
		}
		LogStream& operator<<(const std::wstring& val);

	private:
		Logger& logger;
		LogLevel level;
		std::wostringstream ss;
	};

}