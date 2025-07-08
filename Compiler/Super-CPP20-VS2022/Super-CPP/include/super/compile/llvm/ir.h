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
        std::wstring _inputFilePath;
        std::vector<Super::Type::Token> _tokens;
        Super::Type::AST _ast;

    public:
        IR(const std::wstring& inputFile);
        std::wstring Data();
    };
}