#include <super/type/token_name.h>

namespace Super::Type
{
	const std::string TokenNameToString(TokenName name)
    {
        switch (name)
        {
        case None: return "None";
        case Null: return "Null";
        case TypeKeywords: return "TypeKeywords";
        case ModifierKeyword: return "ModifierKeyword";
        case OtherKeywords: return "OtherKeywords";
        case ControlFlowKeywords: return "ControlFlowKeywords";
        case PreprocessingInstructions: return "PreprocessingInstructions";
        case DefineName: return "DefineName";
        case DefineValue: return "DefineValue";
        case DefinePro: return "DefinePro";
        case Symbols: return "Symbols";
        case UpperNumberSymbols: return "UpperNumberSymbols";
        case String: return "String";
        case Char: return "Char";
        case VarName: return "VarName";
        case FunctionName: return "FunctionName";
        case Pointer: return "Pointer";
        case PriorityParenthesesLeft: return "PriorityParenthesesLeft";
        case PriorityParenthesesRight: return "PriorityParenthesesRight";
        case DeclarationFunctionalParenthesesLeft: return "DeclarationFunctionalParenthesesLeft";
        case DeclarationFunctionalParenthesesRight: return "DeclarationFunctionalParenthesesRight";
        case DefinitionFunctionalParenthesesLeft: return "DefinitionFunctionalParenthesesLeft";
        case DefinitionFunctionalParenthesesRight: return "DefinitionFunctionalParenthesesRight";
        case CallFunctionParenthesesLeft: return "CallFunctionParenthesesLeft";
        case CallFunctionParenthesesRight: return "CallFunctionParenthesesRight";
        case KeywordCallsFunctionParenthesesLeft: return "KeywordCallsFunctionParenthesesLeft";
        case KeywordCallsFunctionParenthesesRight: return "KeywordCallsFunctionParenthesesRight";
        default: return "Unknown";
        }
    }
}