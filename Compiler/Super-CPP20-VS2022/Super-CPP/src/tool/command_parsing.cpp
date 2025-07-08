#include <super/tool/command_parsing.h>

namespace Super::Tool
{
	CommandParsing::CommandParsing(const std::vector<std::wstring>& args, const std::vector<std::pair<std::wstring, std::type_index>>& argvType)
		: _argvType(argvType), _commands(), _options()
	{
		auto result = ParseArguments(args);
		_commands = std::move(result.first);
		_options = std::move(result.second);

		SetCallback(L"help", [&](const std::vector<std::wstring>& args, const std::map<std::wstring, std::wstring>& options)
			{
				PrintHelp();
				return 0;
			}, L"显示帮助信息", L"");
	}

	void CommandParsing::SetCallback(const std::wstring& name, std::function<int(const std::vector<std::wstring>&, const std::map<std::wstring, std::wstring>&)> fn, const std::wstring& helpText, const std::wstring& paramFormat)
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
				std::wcerr << ex.what() << std::endl;
			}
		}
		return -1;
	}

	std::pair<std::map<std::wstring, std::vector<std::wstring>>, std::map<std::wstring, std::wstring>> CommandParsing::ParseArguments(const std::vector<std::wstring>& args)
	{
		std::map<std::wstring, std::vector<std::wstring>> commands;
		std::map<std::wstring, std::wstring> options;

		for (size_t i = 0; i < args.size(); ++i)
		{
			if (args[i].starts_with(L'-'))
			{
				if (args[i].starts_with(L"--"))
				{
					std::wstring key = args[i].substr(2);
					std::wstring value = L"";
					if (i + 1 < args.size() && !args[i + 1].starts_with(L'-'))
					{
						value = args[i + 1];
						++i;
					}
					options[key] = value;
				}
				else
				{
					std::wstring key = args[i].substr(1);
					std::vector<std::wstring> values;
					while (i + 1 < args.size() && !args[i + 1].starts_with(L'-'))
					{
						values.push_back(args[i + 1]);
						++i;
					}
					commands[key] = values;
				}
			}
			else
			{
				std::wcerr << L"无效的参数: " << args[i] << std::endl;
			}
		}

		return { commands, options };
	}

	int CommandParsing::InvokeCallback(const std::wstring& name, const std::vector<std::wstring>& value, const std::map<std::wstring, std::wstring>& options)
	{
		if (auto it = _callbacks.find(name); it != _callbacks.end())
		{
			return it->second.fn(value, options);
		}
		else
		{
			throw std::out_of_range(std::string("未找到名为 '") + std::string(name.begin(), name.end()) + "' 的回调");
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
			std::wcout << L"-" << name << std::wstring(maxNameLength - name.size(), L' ') << L"         " << callback.helpText << (callback.paramFormat.size() > 0 ? L"\n>" : L"") << callback.paramFormat << std::endl;
		}
	}
}