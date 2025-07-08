#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <regex>
#include <functional>
#include <stdexcept>
#include <algorithm>
#include <typeindex>

namespace Super::Tool
{

	struct CallbackInfo
	{
		std::function<int(const std::vector<std::wstring>&, const std::map<std::wstring, std::wstring>&)> fn;
		std::wstring helpText;
		std::wstring paramFormat;
		CallbackInfo() = default;
		CallbackInfo(std::function<int(const std::vector<std::wstring>&, const std::map<std::wstring, std::wstring>&)> f, std::wstring h, std::wstring p)
			: fn(std::move(f)), helpText(std::move(h)), paramFormat(std::move(p))
		{}
	};

	class CommandParsing
	{
	public:
		CommandParsing(const std::vector<std::wstring>& args, const std::vector<std::pair<std::wstring, std::type_index>>& argvType);
		void SetCallback(const std::wstring& name, std::function<int(const std::vector<std::wstring>&, const std::map<std::wstring, std::wstring>&)> fn, const std::wstring& helpText, const std::wstring& paramFormat = L"");
		int ExitCode();

	private:
		std::vector<std::pair<std::wstring, std::type_index>> _argvType;
		std::map<std::wstring, CallbackInfo> _callbacks;
		std::map<std::wstring, std::vector<std::wstring>> _commands;
		std::map<std::wstring, std::wstring> _options;

		static std::pair<std::map<std::wstring, std::vector<std::wstring>>, std::map<std::wstring, std::wstring>> ParseArguments(const std::vector<std::wstring>& args);
		int InvokeCallback(const std::wstring& name, const std::vector<std::wstring>& value, const std::map<std::wstring, std::wstring>& options);
		void PrintHelp();
	};

}