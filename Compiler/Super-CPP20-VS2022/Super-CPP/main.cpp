#pragma warning(disable:4819)

#include <iostream>
#include <vector>
#include <typeindex>
#include <map>
#include <super/compile/llvm/ir.h>
#include <super/tool/command_parsing.h>
#include <super/tool/string.h>
#include <super/info.h>

static int CP_Info(const std::vector<std::string>& args, const std::map<std::string, std::string>& options)
{
	std::cout << Super::Info::GetVersionInfo() << std::endl;
	return 0;
}

static int CP_O(const std::vector<std::string>& args, const std::map<std::string, std::string>& options)
{
	std::string outFile = args[0];
	std::ofstream outFileStream(outFile, std::ios::trunc);

	for (size_t i = 1; i < args.size(); ++i)
	{
		outFileStream << Super::Compile::LLVM::IR(args[i]).Data();
	}
	return 0;
}

int main(int argc, char* argv[])
{
	std::vector<std::string> args(argv + 1, argv + argc);
	std::vector<std::pair<std::string, std::type_index>> argvType =
	{
		{"file_path", typeid(std::string)},
		{"file_path...", typeid(std::vector<std::string>)}
	};

	Super::Tool::CommandParsing cp(args, argvType);

	cp.SetCallback("info", CP_Info, "Super 信息");

	cp.SetCallback("o", CP_O, "编译 *.sp,... 文件为 *.o", "-o <outFile:file_path> <inputFile:file_path...>");

	try
	{
		return cp.ExitCode();
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
	}
	return 0;
}