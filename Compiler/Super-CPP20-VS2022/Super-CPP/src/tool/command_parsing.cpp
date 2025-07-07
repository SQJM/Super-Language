#include <super/tool/command_parsing.h>

namespace Super::Tool
{
	CommandParsing::CommandParsing(const std::vector<std::string>& args, const std::vector<std::pair<std::string, std::type_index>>& argvType)
		: _argvType(argvType), _commands(), _options()
	{
		auto result = ParseArguments(args);
		_commands = std::move(result.first);
		_options = std::move(result.second);

		SetCallback("help", [&](const std::vector<std::string>& args, const std::map<std::string, std::string>& options)
			{
				PrintHelp();
				return 0;
			}, "显示帮助信息", "");
	}

	void CommandParsing::SetCallback(const std::string& name, std::function<int(const std::vector<std::string>&, const std::map<std::string, std::string>&)> fn, const std::string& helpText, const std::string& paramFormat)
	{
		if (name.empty() || !fn || helpText.empty())
			throw std::invalid_argument("参数无效");

		_callbacks[name] = CallbackInfo(fn, helpText, paramFormat);
	}

	int CommandParsing::ExitCode()
	{
		for (const auto& arg : _commands)
		{
			try
			{
				return InvokeCallback(arg.first, arg.second, _options);
			}
			catch (const std::out_of_range& ex)
			{
				std::cerr << ex.what() << std::endl;
			}
		}
		return -1;
	}

	std::pair<std::map<std::string, std::vector<std::string>>, std::map<std::string, std::string>> CommandParsing::ParseArguments(const std::vector<std::string>& args)
	{
		std::map<std::string, std::vector<std::string>> commands;
		std::map<std::string, std::string> options;

		for (size_t i = 0; i < args.size(); ++i)
		{
			if (args[i].starts_with('-'))
			{
				if (args[i].starts_with("--"))
				{
					std::string key = args[i].substr(2);
					std::string value = "";
					if (i + 1 < args.size() && !args[i + 1].starts_with('-'))
					{
						value = args[i + 1];
						++i;
					}
					options[key] = value;
				}
				else
				{
					std::string key = args[i].substr(1);
					std::vector<std::string> values;
					while (i + 1 < args.size() && !args[i + 1].starts_with('-'))
					{
						values.push_back(args[i + 1]);
						++i;
					}
					commands[key] = values;
				}
			}
			else
			{
				std::cerr << "无效的参数: " << args[i] << std::endl;
			}
		}

		return { commands, options };
	}

	int CommandParsing::InvokeCallback(const std::string& name, const std::vector<std::string>& value, const std::map<std::string, std::string>& options)
	{
		if (auto it = _callbacks.find(name); it != _callbacks.end())
		{
			return it->second.fn(value, options);
		}
		else
		{
			throw std::out_of_range(std::string("未找到名为 '") + name + "' 的回调");
		}
	}

	void CommandParsing::PrintHelp()
	{
		size_t maxNameLength = 0;
		for (const auto& [name, callback] : _callbacks)
		{
			maxNameLength = std::max(maxNameLength, name.size());
		}

		for (const auto& [name, callback] : _callbacks)
		{
			std::cout << "-" << name << std::string(maxNameLength - name.size(), ' ') << "         " << callback.helpText << (callback.paramFormat.size() > 0 ? "\n>" : "") << callback.paramFormat << std::endl;
		}
	}
}