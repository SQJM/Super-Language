#include <super/type/token_name.h>

namespace Super::Type
{
	const std::wstring TokenNameToString(TokenName name)
    {
        switch (name)
        {
        case None: return L"None";
        case Null: return L"Null";
        case TypeKeywords: return L"TypeKeywords";
        case ModifierKeyword: return L"ModifierKeyword";
        case OtherKeywords: return L"OtherKeywords";
        case ControlFlowKeywords: return L"ControlFlowKeywords";
        case PreprocessingInstructions: return L"PreprocessingInstructions";
        case DefineName: return L"DefineName";
        case DefineValue: return L"DefineValue";
        case DefinePro: return L"DefinePro";
        case Symbols: return L"Symbols";
        case UpperNumberSymbols: return L"UpperNumberSymbols";
        case String: return L"String";
        case Char: return L"Char";
        case VarName: return L"VarName";
        case FunctionName: return L"FunctionName";
        case Pointer: return L"Pointer";
        case PriorityParenthesesLeft: return L"PriorityParenthesesLeft";
        case PriorityParenthesesRight: return L"PriorityParenthesesRight";
        case DeclarationFunctionalParenthesesLeft: return L"DeclarationFunctionalParenthesesLeft";
        case DeclarationFunctionalParenthesesRight: return L"DeclarationFunctionalParenthesesRight";
        case DefinitionFunctionalParenthesesLeft: return L"DefinitionFunctionalParenthesesLeft";
        case DefinitionFunctionalParenthesesRight: return L"DefinitionFunctionalParenthesesRight";
        case CallFunctionParenthesesLeft: return L"CallFunctionParenthesesLeft";
        case CallFunctionParenthesesRight: return L"CallFunctionParenthesesRight";
        case KeywordCallsFunctionParenthesesLeft: return L"KeywordCallsFunctionParenthesesLeft";
        case KeywordCallsFunctionParenthesesRight: return L"KeywordCallsFunctionParenthesesRight";
        default: return L"Unknown";
        }
    }
}