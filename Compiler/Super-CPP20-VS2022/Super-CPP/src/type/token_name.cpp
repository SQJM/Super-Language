#include <super/type/token_name.h>

namespace Super::Type
{
	const std::wstring TokenNameToString(TokenName name)
    {
        switch (name)
        {
        case TokenName::None: return L"None";
        case TokenName::Null: return L"Null";
        case TokenName::TypeKeywords: return L"TypeKeywords";
        case TokenName::ModifierKeyword: return L"ModifierKeyword";
        case TokenName::OtherKeywords: return L"OtherKeywords";
        case TokenName::ControlFlowKeywords: return L"ControlFlowKeywords";
        case TokenName::PreprocessingInstructions: return L"PreprocessingInstructions";
        case TokenName::DefineName: return L"DefineName";
        case TokenName::DefineValue: return L"DefineValue";
        case TokenName::DefinePro: return L"DefinePro";
        case TokenName::Symbols: return L"Symbols";
        case TokenName::String: return L"String";
        case TokenName::Char: return L"Char";
        case TokenName::VarName: return L"VarName";
        case TokenName::FunctionName: return L"FunctionName";
        case TokenName::Pointer: return L"Pointer";
        case TokenName::PriorityParenthesesLeft: return L"PriorityParenthesesLeft";
        case TokenName::PriorityParenthesesRight: return L"PriorityParenthesesRight";
        case TokenName::DeclarationFunctionalParenthesesLeft: return L"DeclarationFunctionalParenthesesLeft";
        case TokenName::DeclarationFunctionalParenthesesRight: return L"DeclarationFunctionalParenthesesRight";
        case TokenName::DefinitionFunctionalParenthesesLeft: return L"DefinitionFunctionalParenthesesLeft";
        case TokenName::DefinitionFunctionalParenthesesRight: return L"DefinitionFunctionalParenthesesRight";
        case TokenName::CallFunctionParenthesesLeft: return L"CallFunctionParenthesesLeft";
        case TokenName::CallFunctionParenthesesRight: return L"CallFunctionParenthesesRight";
        case TokenName::KeywordCallsFunctionParenthesesLeft: return L"KeywordCallsFunctionParenthesesLeft";
        case TokenName::KeywordCallsFunctionParenthesesRight: return L"KeywordCallsFunctionParenthesesRight";
        default: return L"Unknown";
        }
    }
}