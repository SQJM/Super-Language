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

    struct CallbackInfo {
        std::function<int(const std::vector<std::string>&, const std::map<std::string, std::string>&)> fn;
        std::string helpText;
        std::string paramFormat;
        CallbackInfo() = default;
        CallbackInfo(std::function<int(const std::vector<std::string>&, const std::map<std::string, std::string>&)> f, std::string h, std::string p)
            : fn(std::move(f)), helpText(std::move(h)), paramFormat(std::move(p)) {}
    };

	class CommandParsing
	{
	public:
		CommandParsing(const std::vector<std::string>& args, const std::vector<std::pair<std::string, std::type_index>>& argvType);
		void SetCallback(const std::string& name, std::function<int(const std::vector<std::string>&, const std::map<std::string, std::string>&)> fn, const std::string& helpText, const std::string& paramFormat = "");
		int ExitCode();

	private:
		std::vector<std::pair<std::string, std::type_index>> _argvType;
		std::map<std::string, CallbackInfo> _callbacks;
		std::map<std::string, std::vector<std::string>> _commands;
		std::map<std::string, std::string> _options;

		static std::pair<std::map<std::string, std::vector<std::string>>, std::map<std::string, std::string>> ParseArguments(const std::vector<std::string>& args);
		int InvokeCallback(const std::string& name, const std::vector<std::string>& value, const std::map<std::string, std::string>& options);
		void PrintHelp();
	};

}