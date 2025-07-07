#include <super/compile/lexical_analysis/parenthesis.h>
#include <super/error.h>
#include <stdexcept>
#include <iostream>
#include <stack>
#include <unordered_map>
#include <sstream>

namespace Super::Compile::LexicalAnalysis
{

    void Parenthesis(const std::string& inputFilePath, std::vector<Super::Type::Token>& tokens)
    {
        std::stack<Super::Type::Token> stack;
        std::unordered_map<std::string, std::string> bracketPairs = {
            { ")", "(" },
            { "}", "{" },
            { "]", "[" }
        };
        std::unordered_map<std::string, std::string> errorMessages = {
            { "(", "200000" },
            { ")", "200010" },
            { "[", "200020" },
            { "]", "200030" },
            { "{", "200040" },
            { "}", "200050" }
        };

        for (const auto& token : tokens)
        {
            const std::string& str = token.value;
            if (str == ")" || str == "}"|| str == "]")
            {
                if (stack.empty())
                {
                    SUPER_ERROR_A(inputFilePath, errorMessages[str], token);
                }
                else
                {
                    auto& expected = bracketPairs[str];
                    if (stack.top().value != expected)
                    {
                        SUPER_ERROR_A(inputFilePath, errorMessages[str], token);
                    }
                    stack.pop();
                }
            }
            else if (str == "(" || str == "{" || str == "[")
            {
                stack.push(token);
            }
        }

        if (!stack.empty())
        {
            std::ostringstream result;
            while (!stack.empty())
            {
                const auto& token = stack.top();
                stack.pop();
                std::cout<<
					"Error: " << token.value << " at line " << token.line << ", column " << token.column << std::endl;
                auto& msg = Super::Error::A[errorMessages[token.value]];
                result << Super::Error::AddIndicate(inputFilePath, token) << "\n"
                    << msg << "\n";
            }
            SUPER_ERROR_MSG(result.str());
        }
    }

}