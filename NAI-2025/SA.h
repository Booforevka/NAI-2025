#pragma once
#include "LA.h"
#include <algorithm>
namespace SA
{
	bool startSA(LA::LEX& lex);  
    bool checkTypes(LA::LEX& lex, int leftIdx, int rightIdx);
    bool checkOperation(LA::LEX& lex, int idx);
    bool checkFunctionCall(LA::LEX& lex, int idx);
    bool checkFunctionDeclaration(LA::LEX& lex);
    bool checkVariableDeclaration(LA::LEX& lex);
    bool checkFunctionReturnType(LA::LEX& lex);
    bool checkCycleCondition(LA::LEX& lex);
    bool checkArithmeticTypes(LA::LEX& lex, int idx);
    bool checkDuplicateVariables(LA::LEX& lex);
    bool checkLibraryConflicts(LA::LEX& lex);
    bool checkComparisonTypes(LA::LEX& lex, int idx);
    bool checkUnaryOperations(LA::LEX& lex);
    IT::IDDATATYPE getExpressionType(LA::LEX& lex, int startIdx);

}
