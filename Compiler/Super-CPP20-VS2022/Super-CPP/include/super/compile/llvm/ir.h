#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <filesystem>
#include <super/type/token.h>
#include <super/type/ast.h>

namespace Super::Compile::LLVM
{
    class IR
    {
    private:
        std::string _inputFilePath;
        std::vector<Super::Type::Token> _tokens;
        Super::Type::AST _ast;

    public:
        IR(const std::string& inputFile);
        std::string Data();
    };
}