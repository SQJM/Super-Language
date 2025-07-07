#pragma once
#include <vector>
#include <iosfwd>
#include <sstream>
#include <super/type/token.h>
#include <super/error.h>

namespace Super::Compile::LexicalAnalysis
{
    class ExtractToken
    {
    private:
        std::vector<Super::Type::Token> tokens;
        bool isDefineName = false;
        bool isSetDefineName = false;
        bool isLineToOneToken = false;

        void AddTokens(size_t line, size_t column, Super::Type::TokenName& tokenName, std::ostringstream& value);
        void ClearNullToken();

    public:
        ExtractToken(const std::string& inputFilePath);
        std::vector<Super::Type::Token> GetTokenStream() const;
    };
}

