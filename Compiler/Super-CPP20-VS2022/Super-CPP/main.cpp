#pragma warning(disable:4819)
#pragma warning(disable:4267)

#include <iostream>
#include <vector>
#include <typeindex>
#include <map>
#include <super/compile/llvm/ir.h>
#include <super/tool/command_parsing.h>
#include <super/tool/string.h>
#include <super/info.h>
#include <super/tool/log.h>
#include <unicode/unistr.h>

static std::vector<std::wstring> ArgsToWString(int argc, char* argv[])
{
    std::vector<std::wstring> args;
    for (int i = 1; i < argc; ++i)
    {
        icu::UnicodeString ustr = icu::UnicodeString::fromUTF8(argv[i]);
        std::wstring warg(ustr.length(), L'\0');
        ustr.extract(0, ustr.length(), &warg[0]);
        args.push_back(warg);
    }
    return args;
}

static int CP_Info(const std::vector<std::wstring>& args, const std::map<std::wstring, std::wstring>& options)
{
	std::wcout << Super::Info::GetVersionInfo() << std::endl;
	return 0;
}

static int CP_O(const std::vector<std::wstring>& args, const std::map<std::wstring, std::wstring>& options)
{
	std::wstring outFile = args[0];
	std::wofstream outFileStream(outFile, std::ios::trunc);

	for (size_t i = 1; i < args.size(); ++i)
	{
		outFileStream << Super::Compile::LLVM::IR(args[i]).Data();
	}
	return 0;
}

int main(int argc, char* argv[])
{
	std::locale::global(std::locale("chs"));
	std::wcout.imbue(std::locale());

	Super::Tool::Logger::Instance().SetLogLevel(Super::Tool::LogLevel::Debug);
	Super::Tool::Logger::Instance().SetLogFile(L"super-build.log");

	std::vector<std::wstring> args = ArgsToWString(argc, argv);
	std::vector<std::pair<std::wstring, std::type_index>> argvType =
	{
		{L"file_path", typeid(std::wstring)},
		{L"file_path...", typeid(std::vector<std::wstring>)}
	};

	Super::Tool::CommandParsing cp(args, argvType);

	cp.SetCallback(L"info", CP_Info, L"Super 信息");

	cp.SetCallback(L"o", CP_O, L"编译 *.sp,... 文件为 *.o", L"-o <outFile:file_path> <inputFile:file_path...>");

	try
	{
		CP_O({ L"out.o", L"C:\\Users\\sqjm\\Desktop\\Super-Language\\Compiler\\Super-CPP20-VS2022\\x64\\Debug\\test\\doc\\a.sp" }, {});
		return cp.ExitCode();
	}
	catch (const std::exception& ex)
	{
		std::wcerr << ex.what() << std::endl;
	}
	return -2;
}