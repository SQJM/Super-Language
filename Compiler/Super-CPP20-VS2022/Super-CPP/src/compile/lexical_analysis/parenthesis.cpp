#include <super/compile/lexical_analysis/parenthesis.h>
#include <super/error.h>
#include <stdexcept>
#include <iostream>
#include <stack>
#include <unordered_map>
#include <sstream>

namespace Super::Compile::LexicalAnalysis
{

    void Parenthesis(const std::wstring& inputFilePath, std::vector<Super::Type::Token>& tokens)
    {
        std::stack<Super::Type::Token> stack;
        std::unordered_map<std::wstring, std::wstring> bracketPairs = {
            { L")", L"(" },
            { L"}", L"{" },
            { L"]", L"[" }
        };
        std::unordered_map<std::wstring, std::wstring> errorMessages = {
            { L"(", L"200000" },
            { L")", L"200010" },
            { L"[", L"200040" },
            { L"]", L"200050" },
            { L"{", L"200020" },
            { L"}", L"200030" }
        };

        for (const auto& token : tokens)
        {
            const std::wstring& str = token.value;
            if (str == L")" || str == L"}"|| str == L"]")
            {
                if (stack.empty())
                {
                    SUPER_ERROR_THROW_A(inputFilePath, errorMessages[str], token);
                }
                else
                {
                    auto& expected = bracketPairs[str];
                    if (stack.top().value != expected)
                    {
                        SUPER_ERROR_THROW_A(inputFilePath, errorMessages[str], token);
                    }
                    stack.pop();
                }
            }
            else if (str == L"(" || str == L"{" || str == L"[")
            {
                stack.push(token);
            }
        }

        if (!stack.empty())
        {
            while (!stack.empty())
            {
                const auto& token = stack.top();
                SUPER_ERROR_A(inputFilePath, errorMessages[token.value], token);
                stack.pop();
            }
            exit(0);
        }
    }

}