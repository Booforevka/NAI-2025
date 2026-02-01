#include "stdafx.h"
#include "SA.h"

namespace SA
{
    const char* getTypeName(IT::IDDATATYPE type) {
        switch (type) {
        case IT::INT: return "int";
        case IT::STR: return "str";
        case IT::CH: return "char";
        case IT::BOOL: return "bool";
        default: return "неизвестный";
        }
    }

    std::string getCurrentFunctionScope(LA::LEX& lex, int pos)
    {
        for (int i = pos; i >= 0; i--)
        {
            if (lex.lexTable.table[i].lexema[0] == LEX_FUNC ||
                lex.lexTable.table[i].lexema[0] == LEX_MAINFUNC)
            {
                int idIdx = lex.lexTable.table[i].idxTI;
                if (idIdx != LT_TI_NULLIDX && idIdx < lex.idTable.size)
                {
                    return std::string(lex.idTable.table[idIdx].id);
                }
            }
        }
        return "";
    }

    bool startSA(LA::LEX& lex)
    {
        
        for (int i = 0; i < lex.lexTable.size; i++)
        {
            if (lex.lexTable.table[i].lexema[0] == LEX_ID)
            {
                int idIdx = lex.lexTable.table[i].idxTI;

                if (idIdx != LT_TI_NULLIDX && idIdx < lex.idTable.size)
                {
                    
                    if (lex.idTable.table[idIdx].idtype == IT::F ||
                        lex.idTable.table[idIdx].idtype == IT::SF)
                    {
                       

                        
                        bool isDeclaration = false;

                        
                        for (int j = i - 1; j >= std::max(0, i - 5); j--)
                        {
                            char lexch = lex.lexTable.table[j].lexema[0];

                            
                            if (lexch == LEX_FUNC)
                            {
                                isDeclaration = true;
                                
                                break;
                            }

                            
                            if (lexch == LEX_SEMICOLON || lexch == LEX_EQUAL ||
                                lexch == LEX_LEFTBRACE || lexch == LEX_RIGHTBRACE)
                            {
                                
                                break;
                            }
                        }

                        if (!isDeclaration)
                        {
                            
                            checkFunctionCall(lex, i);
                        }
                    }
                }
            }
        }

        
        if (!checkFunctionDeclaration(lex)) return false;
        if (!checkDuplicateVariables(lex)) return false;
        if (!checkLibraryConflicts(lex)) return false;
        if (!checkVariableDeclaration(lex)) return false;
        if (!checkFunctionReturnType(lex)) return false;
        if (!checkCycleCondition(lex)) return false;
        if (!checkUnaryOperations(lex)) return false;

        
        for (int i = 0; i < lex.lexTable.size; i++)
        {
            if (lex.lexTable.table[i].lexema[0] == LEX_EQUAL)
            {
                if (i > 0 && i + 1 < lex.lexTable.size)
                {
                    int leftIdx = lex.lexTable.table[i - 1].idxTI;
                    int rightIdx = i + 1;

                    if (!checkTypes(lex, leftIdx, rightIdx))
                    {
                        throw ERROR_THROW_IN(720, lex.lexTable.table[i].sn, 0);
                    }
                }
            }

            if (lex.lexTable.table[i].lexema[0] == LEX_OPERATION)
            {
                if (!checkOperation(lex, i))
                {
                    throw ERROR_THROW_IN(721, lex.lexTable.table[i].sn, 0);
                }

                if (!checkArithmeticTypes(lex, i))
                {
                    throw ERROR_THROW_IN(721, lex.lexTable.table[i].sn, 0);
                }
            }

            if (lex.lexTable.table[i].lexema[0] == LEX_COMPARISON)
            {
                if (!checkComparisonTypes(lex, i))
                {
                    throw ERROR_THROW_IN(727, lex.lexTable.table[i].sn, 0);
                }
            }
        }

        std::cout << "=== Семантический анализ завершен успешно! ===" << std::endl;
        return true;
    }




    bool checkDuplicateVariables(LA::LEX& lex)
    {
        std::map<std::string, std::string> declaredVars;

        for (int i = 0; i < lex.idTable.size; i++)
        {
            if (lex.idTable.table[i].idtype == IT::V ||
                lex.idTable.table[i].idtype == IT::P)
            {
                std::string varName = lex.idTable.table[i].id;

                if (declaredVars.find(varName) != declaredVars.end())
                {
                    std::cout << "Ошибка: повторное объявление переменной "
                        << varName << std::endl;
                    throw ERROR_THROW(711);
                }

                declaredVars[varName] = varName;
            }
        }
        return true;
    }

    bool checkLibraryConflicts(LA::LEX& lex)
    {
        const char* libFunctions[] = { "abs", "pow", "nabs", "npow" };

        for (int i = 0; i < lex.idTable.size; i++)
        {
            if (lex.idTable.table[i].idtype == IT::V ||
                lex.idTable.table[i].idtype == IT::F)
            {
                std::string name = lex.idTable.table[i].id;

                size_t pos = name.find_last_of('.');
                if (pos != std::string::npos)
                {
                    name = name.substr(pos + 1);
                }

                for (int j = 0; j < 4; j++)
                {
                    if (name == libFunctions[j] && lex.idTable.table[i].idtype != IT::SF)
                    {
                        std::cout << "Ошибка: конфликт имени '" << name
                            << "' с функцией стандартной библиотеки" << std::endl;
                        throw ERROR_THROW(713);
                    }
                }
            }
        }
        return true;
    }

    IT::IDDATATYPE getExpressionType(LA::LEX& lex, int startIdx)
    {
        int currentIdx = startIdx;

        // Проверка на операции сравнения
        while (currentIdx < lex.lexTable.size &&
            lex.lexTable.table[currentIdx].lexema[0] != LEX_SEMICOLON &&
            lex.lexTable.table[currentIdx].lexema[0] != LEX_COMMA &&
            lex.lexTable.table[currentIdx].lexema[0] != LEX_RIGHTTHESIS)
        {
            if (lex.lexTable.table[currentIdx].lexema[0] == LEX_COMPARISON)
            {
                return IT::BOOL;
            }
            currentIdx++;
        }

        // Проверка на вызов функции
        currentIdx = startIdx;
        while (currentIdx < lex.lexTable.size &&
            lex.lexTable.table[currentIdx].lexema[0] != LEX_SEMICOLON &&
            lex.lexTable.table[currentIdx].lexema[0] != LEX_COMMA &&
            lex.lexTable.table[currentIdx].lexema[0] != LEX_RIGHTTHESIS)
        {
            if (lex.lexTable.table[currentIdx].lexema[0] == LEX_ID)
            {
                int idIdx = lex.lexTable.table[currentIdx].idxTI;
                if (idIdx != LT_TI_NULLIDX && idIdx < lex.idTable.size)
                {
                    if (lex.idTable.table[idIdx].idtype == IT::F ||
                        lex.idTable.table[idIdx].idtype == IT::SF)
                    {
                        return lex.idTable.table[idIdx].iddatatype;
                    }
                }
            }
            currentIdx++;
        }

        // Проверка на побитовую инверсию
        currentIdx = startIdx;
        while (currentIdx < lex.lexTable.size &&
            lex.lexTable.table[currentIdx].lexema[0] != LEX_SEMICOLON &&
            lex.lexTable.table[currentIdx].lexema[0] != LEX_COMMA &&
            lex.lexTable.table[currentIdx].lexema[0] != LEX_RIGHTTHESIS)
        {
            if (lex.lexTable.table[currentIdx].lexema[0] == LEX_TILDE)
            {
                return IT::INT;
            }
            currentIdx++;
        }

        // Проверка литералов и переменных
        currentIdx = startIdx;
        while (currentIdx < lex.lexTable.size &&
            lex.lexTable.table[currentIdx].lexema[0] != LEX_SEMICOLON &&
            lex.lexTable.table[currentIdx].lexema[0] != LEX_COMMA &&
            lex.lexTable.table[currentIdx].lexema[0] != LEX_RIGHTTHESIS)
        {
            if (lex.lexTable.table[currentIdx].lexema[0] == LEX_ID ||
                lex.lexTable.table[currentIdx].lexema[0] == LEX_LITERAL)
            {
                int idIdx = lex.lexTable.table[currentIdx].idxTI;
                if (idIdx != LT_TI_NULLIDX && idIdx < lex.idTable.size)
                {
                    if (lex.idTable.table[idIdx].idtype != IT::F &&
                        lex.idTable.table[idIdx].idtype != IT::SF)
                    {
                        return lex.idTable.table[idIdx].iddatatype;
                    }
                }
            }
            currentIdx++;
        }

        return IT::INT;
    }

    bool checkVariableDeclaration(LA::LEX& lex)
    {
        for (int i = 0; i < lex.lexTable.size; i++)
        {
            if (lex.lexTable.table[i].lexema[0] == LEX_ID)
            {
                int idIdx = lex.lexTable.table[i].idxTI;

                if (idIdx == LT_TI_NULLIDX || idIdx >= lex.idTable.size)
                {
                    std::cout << "Ошибка: использование необъявленной переменной (строка "
                        << lex.lexTable.table[i].sn << ")" << std::endl;
                    throw ERROR_THROW_IN(710, lex.lexTable.table[i].sn, 0);
                }
            }
        }
        return true;
    }

    bool checkArithmeticTypes(LA::LEX& lex, int idx)
    {
        if (idx == 0 || idx >= lex.lexTable.size - 1) return true;

        char operation = lex.lexTable.table[idx].lexema[1];
        int leftIdx = lex.lexTable.table[idx - 1].idxTI;
        int rightIdx = lex.lexTable.table[idx + 1].idxTI;

        auto checkOperand = [&](int opIdx, const char* side) {
            if (opIdx != LT_TI_NULLIDX && opIdx < lex.idTable.size)
            {
                IT::IDDATATYPE type = lex.idTable.table[opIdx].iddatatype;

                if (type == IT::STR)
                {
                    std::cout << "Ошибка: использование строк в арифметических операциях (строка "
                        << lex.lexTable.table[idx].sn << ")" << std::endl;
                    throw ERROR_THROW_IN(723, lex.lexTable.table[idx].sn, 0);
                }

                if (type == IT::CH)
                {
                    std::cout << "Ошибка: недопустимая арифметическая операция над char (строка "
                        << lex.lexTable.table[idx].sn << ")" << std::endl;
                    throw ERROR_THROW_IN(729, lex.lexTable.table[idx].sn, 0);
                }

                if (type == IT::BOOL)
                {
                    std::cout << "Ошибка: попытка выполнить арифметическую операцию над bool (строка "
                        << lex.lexTable.table[idx].sn << ")" << std::endl;
                    throw ERROR_THROW_IN(731, lex.lexTable.table[idx].sn, 0);
                }
            }
            };

        checkOperand(leftIdx, "левый");
        checkOperand(rightIdx, "правый");

        return true;
    }

    bool checkCycleCondition(LA::LEX& lex)
    {
        for (int i = 0; i < lex.lexTable.size; i++)
        {
            if (lex.lexTable.table[i].lexema[0] == LEX_CYCLE)
            {
                int conditionStart = -1;
                for (int j = i + 1; j < lex.lexTable.size && j < i + 20; j++)
                {
                    if (lex.lexTable.table[j].lexema[0] == LEX_THREEPTS)
                    {
                        conditionStart = j + 1;
                        break;
                    }
                }

                if (conditionStart != -1 && conditionStart < lex.lexTable.size)
                {
                    IT::IDDATATYPE condType = getExpressionType(lex, conditionStart);

                    if (condType != IT::INT)
                    {
                        std::cout << "Ошибка: неверный тип в условии цикла (строка "
                            << lex.lexTable.table[i].sn << ")" << std::endl;
                        throw ERROR_THROW_IN(724, lex.lexTable.table[i].sn, 0);
                    }
                }
            }
        }
        return true;
    }

    bool checkComparisonTypes(LA::LEX& lex, int idx)
    {
        if (idx == 0 || idx >= lex.lexTable.size - 1) return true;

        int leftIdx = lex.lexTable.table[idx - 1].idxTI;
        int rightIdx = lex.lexTable.table[idx + 1].idxTI;

        if (leftIdx != LT_TI_NULLIDX && leftIdx < lex.idTable.size &&
            rightIdx != LT_TI_NULLIDX && rightIdx < lex.idTable.size)
        {
            IT::IDDATATYPE leftType = lex.idTable.table[leftIdx].iddatatype;
            IT::IDDATATYPE rightType = lex.idTable.table[rightIdx].iddatatype;

            if (leftType != rightType)
            {
                std::cout << "Ошибка: операции сравнения требуют одинаковых типов (строка "
                    << lex.lexTable.table[idx].sn << ")" << std::endl;
                return false;
            }
        }
        return true;
    }

    bool checkTypes(LA::LEX& lex, int leftIdx, int rightIdx)
    {
        if (leftIdx == LT_TI_NULLIDX || leftIdx >= lex.idTable.size)
            return false;

        IT::IDDATATYPE leftType = lex.idTable.table[leftIdx].iddatatype;
        IT::IDDATATYPE exprType = getExpressionType(lex, rightIdx);

        if (leftType != exprType)
        {
            std::cout << "Ошибка: несоответствие типов при присваивании (левая часть: "
                << (int)leftType << ", правая часть: " << (int)exprType << ")" << std::endl;
            return false;
        }

        return true;
    }

    bool checkOperation(LA::LEX& lex, int idx)
    {
        char operation = lex.lexTable.table[idx].lexema[1];

        if (operation == '&' || operation == '|')
        {
            if (idx > 0 && idx + 1 < lex.lexTable.size)
            {
                int leftIdx = lex.lexTable.table[idx - 1].idxTI;
                int rightIdx = lex.lexTable.table[idx + 1].idxTI;

                auto checkBitwiseOperand = [&](int opIdx) {
                    if (opIdx != LT_TI_NULLIDX && opIdx < lex.idTable.size)
                    {
                        if (lex.idTable.table[opIdx].iddatatype != IT::INT)
                        {
                            std::cout << "Ошибка: побитовые операции допустимы только для типа int (строка "
                                << lex.lexTable.table[idx].sn << ")" << std::endl;
                            throw ERROR_THROW_IN(726, lex.lexTable.table[idx].sn, 0);
                        }
                    }
                    };

                checkBitwiseOperand(leftIdx);
                checkBitwiseOperand(rightIdx);
            }
        }

        return true;
    }

    bool checkFunctionCall(LA::LEX& lex, int idx)
    {
        int funcIdx = lex.lexTable.table[idx].idxTI;

        if (funcIdx == LT_TI_NULLIDX || funcIdx >= lex.idTable.size)
        {
            throw ERROR_THROW_IN(703, lex.lexTable.table[idx].sn, 0);
        }

        if (lex.idTable.table[funcIdx].idtype != IT::F &&
            lex.idTable.table[funcIdx].idtype != IT::SF)
        {
            throw ERROR_THROW_IN(703, lex.lexTable.table[idx].sn, 0);
        }

        
        std::vector<IT::IDDATATYPE> actualParamTypes;
        int i = idx - 1;

        while (i >= 0)
        {
            char lexch = lex.lexTable.table[i].lexema[0];

            
            if (lexch == LEX_EQUAL || lexch == LEX_SEMICOLON ||
                lexch == LEX_LEFTBRACE || lexch == LEX_RIGHTBRACE ||
                lexch == LEX_RETURN || lexch == LEX_OUT)
            {
                break;
            }

            
            if (lexch == LEX_OPERATION || lexch == LEX_TILDE)
            {
                i--;
                continue;
            }

            
            if (lexch == LEX_ID || lexch == LEX_LITERAL)
            {
                int paramIdx = lex.lexTable.table[i].idxTI;
                if (paramIdx != LT_TI_NULLIDX && paramIdx < lex.idTable.size)
                {
                    
                    if (lex.idTable.table[paramIdx].idtype != IT::F &&
                        lex.idTable.table[paramIdx].idtype != IT::SF)
                    {
                        actualParamTypes.insert(actualParamTypes.begin(),
                            lex.idTable.table[paramIdx].iddatatype);
                    }
                }
            }

            i--;
        }

        std::string funcName = lex.idTable.table[funcIdx].id;

        
        if (lex.idTable.table[funcIdx].idtype == IT::SF)
        {
            if (funcName == "abs")
            {
                
                if (actualParamTypes.size() != 1)
                {
                    throw ERROR_THROW_IN(701, lex.lexTable.table[idx].sn, 0);
                }
                if (actualParamTypes[0] != IT::INT)
                {
                    throw ERROR_THROW_IN(702, lex.lexTable.table[idx].sn, 0);
                }
                return true;
            }
            else if (funcName == "pow")
            {
                
                if (actualParamTypes.size() != 2)
                {
                    throw ERROR_THROW_IN(701, lex.lexTable.table[idx].sn, 0);
                }
                if (actualParamTypes[0] != IT::INT || actualParamTypes[1] != IT::INT)
                {
                    throw ERROR_THROW_IN(702, lex.lexTable.table[idx].sn, 0);
                }
                return true;
            }
        }

        
        std::vector<std::pair<int, IT::IDDATATYPE>> formalParams;

        for (int i = 0; i < lex.idTable.size; i++)
        {
            if (lex.idTable.table[i].idtype == IT::P)
            {
                std::string paramName = lex.idTable.table[i].id;
                if (paramName.find(funcName) == 0)
                {
                    formalParams.push_back({ i, lex.idTable.table[i].iddatatype });
                }
            }
        }

        
        if (actualParamTypes.size() != formalParams.size())
        {
            throw ERROR_THROW_IN(701, lex.lexTable.table[idx].sn, 0);
        }

        
        for (size_t i = 0; i < actualParamTypes.size(); i++)
        {
            if (actualParamTypes[i] != formalParams[i].second)
            {
                throw ERROR_THROW_IN(702, lex.lexTable.table[idx].sn, 0);
            }
        }

        return true;
    }




    bool checkFunctionReturnType(LA::LEX& lex)
    {
        std::map<std::string, bool> functionsWithReturn;
        std::map<std::string, IT::IDDATATYPE> functionTypes;
        std::map<std::string, int> functionStartPos;
        std::map<std::string, int> functionEndPos;

        
        for (int i = 0; i < lex.idTable.size; i++)
        {
            if (lex.idTable.table[i].idtype == IT::F)
            {
                std::string funcName = lex.idTable.table[i].id;
                functionTypes[funcName] = lex.idTable.table[i].iddatatype;
                functionsWithReturn[funcName] = false;
            }
        }

        
        for (int i = 0; i < lex.lexTable.size; i++)
        {
            if (lex.lexTable.table[i].lexema[0] == LEX_FUNC)
            {
                if (i + 1 < lex.lexTable.size &&
                    lex.lexTable.table[i + 1].lexema[0] == LEX_ID)
                {
                    int funcIdIdx = lex.lexTable.table[i + 1].idxTI;
                    if (funcIdIdx != LT_TI_NULLIDX && funcIdIdx < lex.idTable.size)
                    {
                        std::string funcName = lex.idTable.table[funcIdIdx].id;

                        int braceCount = 0;
                        int startPos = -1;
                        int endPos = -1;

                        for (int j = i + 1; j < lex.lexTable.size; j++)
                        {
                            if (lex.lexTable.table[j].lexema[0] == LEX_LEFTBRACE)
                            {
                                if (braceCount == 0) startPos = j;
                                braceCount++;
                            }
                            else if (lex.lexTable.table[j].lexema[0] == LEX_RIGHTBRACE)
                            {
                                braceCount--;
                                if (braceCount == 0)
                                {
                                    endPos = j;
                                    break;
                                }
                            }
                        }

                        if (startPos != -1 && endPos != -1)
                        {
                            functionStartPos[funcName] = startPos;
                            functionEndPos[funcName] = endPos;
                        }
                    }
                }
            }
            else if (lex.lexTable.table[i].lexema[0] == LEX_MAINFUNC)
            {
                std::string funcName = "Main";
                functionTypes[funcName] = IT::INT;
                functionsWithReturn[funcName] = false;

                int braceCount = 0;
                int startPos = -1;
                int endPos = -1;

                for (int j = i + 1; j < lex.lexTable.size; j++)
                {
                    if (lex.lexTable.table[j].lexema[0] == LEX_LEFTBRACE)
                    {
                        if (braceCount == 0) startPos = j;
                        braceCount++;
                    }
                    else if (lex.lexTable.table[j].lexema[0] == LEX_RIGHTBRACE)
                    {
                        braceCount--;
                        if (braceCount == 0)
                        {
                            endPos = j;
                            break;
                        }
                    }
                }

                if (startPos != -1 && endPos != -1)
                {
                    functionStartPos[funcName] = startPos;
                    functionEndPos[funcName] = endPos;
                }
            }
        }

        
        for (int i = 0; i < lex.lexTable.size; i++)
        {
            if (lex.lexTable.table[i].lexema[0] == LEX_RETURN)
            {
                std::string currentFunc;

                for (auto& funcPair : functionStartPos)
                {
                    std::string funcName = funcPair.first;
                    int start = funcPair.second;
                    int end = functionEndPos[funcName];

                    if (i > start && i < end)
                    {
                        currentFunc = funcName;
                        functionsWithReturn[funcName] = true;
                        break;
                    }
                }

                if (currentFunc.empty()) continue;

                if (i + 1 < lex.lexTable.size &&
                    lex.lexTable.table[i + 1].lexema[0] != LEX_SEMICOLON)
                {
                    IT::IDDATATYPE funcType = functionTypes[currentFunc];
                    IT::IDDATATYPE returnType = getExpressionType(lex, i + 1);

                    if (funcType != returnType)
                    {
                        std::cout << "Ошибка: тип возвращаемого значения не соответствует типу функции "
                            << currentFunc << " (ожидается тип " << (int)funcType
                            << ", получен тип " << (int)returnType
                            << ") (строка " << lex.lexTable.table[i].sn << ")" << std::endl;
                        throw ERROR_THROW_IN(700, lex.lexTable.table[i].sn, 0);
                    }
                }
            }
        }

        
        for (auto& pair : functionsWithReturn)
        {
            std::string funcName = pair.first;
            bool hasReturn = pair.second;

            if (funcName == "Main") continue;

            if (functionTypes.find(funcName) != functionTypes.end() && !hasReturn)
            {
                std::cout << "Ошибка: функция '" << funcName
                    << "' с типом возврата не возвращает значение" << std::endl;
                throw ERROR_THROW(704);
            }
        }

        return true;
    }

    bool checkUnaryOperations(LA::LEX& lex)
    {
        for (int i = 0; i < lex.lexTable.size; i++)
        {
            
            if (lex.lexTable.table[i].lexema[0] == LEX_TILDE)
            {
                if (i + 1 < lex.lexTable.size)
                {
                    char nextLex = lex.lexTable.table[i + 1].lexema[0];

                    if (nextLex == 'i' || nextLex == 'l')
                    {
                        int operandIdx = lex.lexTable.table[i + 1].idxTI;

                        if (operandIdx != LT_TI_NULLIDX && operandIdx < lex.idTable.size)
                        {
                            IT::IDDATATYPE operandType = lex.idTable.table[operandIdx].iddatatype;

                            if (operandType != IT::INT)
                            {
                                std::cout << "Ошибка: побитовая инверсия (~) применима только к типу int (строка "
                                    << lex.lexTable.table[i].sn << ")" << std::endl;
                                throw ERROR_THROW_IN(728, lex.lexTable.table[i].sn, 0);
                            }
                        }
                    }
                }
            }

            
            if (lex.lexTable.table[i].lexema[0] == LEX_OPERATION &&
                lex.lexTable.table[i].lexema[1] == '-')
            {
                bool isUnary = false;

                if (i == 0)
                {
                    isUnary = true;
                }
                else
                {
                    char prevLex = lex.lexTable.table[i - 1].lexema[0];

                    if (prevLex == LEX_OPERATION || prevLex == LEX_LEFTTHESIS ||
                        prevLex == LEX_COMMA || prevLex == LEX_EQUAL)
                    {
                        isUnary = true;
                    }
                }

                if (isUnary && i + 1 < lex.lexTable.size)
                {
                    char nextLex = lex.lexTable.table[i + 1].lexema[0];

                    if (nextLex == 'i' || nextLex == 'l')
                    {
                        int operandIdx = lex.lexTable.table[i + 1].idxTI;

                        if (operandIdx != LT_TI_NULLIDX && operandIdx < lex.idTable.size)
                        {
                            IT::IDDATATYPE operandType = lex.idTable.table[operandIdx].iddatatype;

                            if (operandType == IT::CH)
                            {
                                std::cout << "Ошибка: унарный минус неприменим к типу char (строка "
                                    << lex.lexTable.table[i].sn << ")" << std::endl;
                                throw ERROR_THROW_IN(729, lex.lexTable.table[i].sn, 0);
                            }

                            if (operandType == IT::STR)
                            {
                                std::cout << "Ошибка: унарный минус неприменим к типу str (строка "
                                    << lex.lexTable.table[i].sn << ")" << std::endl;
                                throw ERROR_THROW_IN(723, lex.lexTable.table[i].sn, 0);
                            }

                            if (operandType == IT::BOOL)
                            {
                                std::cout << "Ошибка: унарный минус неприменим к типу bool (строка "
                                    << lex.lexTable.table[i].sn << ")" << std::endl;
                                throw ERROR_THROW_IN(731, lex.lexTable.table[i].sn, 0);
                            }
                        }
                    }
                }
            }
        }
        return true;
    }

    bool checkFunctionDeclaration(LA::LEX& lex)
    {
        bool hasMain = false;

        for (int i = 0; i < lex.lexTable.size; i++)
        {
            if (lex.lexTable.table[i].lexema[0] == LEX_MAINFUNC)
            {
                hasMain = true;
                break;
            }
        }

        for (int i = 0; i < lex.idTable.size; i++)
        {
            if (lex.idTable.table[i].idtype == IT::F)
            {
                for (int j = i + 1; j < lex.idTable.size; j++)
                {
                    if (lex.idTable.table[j].idtype == IT::F &&
                        strcmp(lex.idTable.table[i].id, lex.idTable.table[j].id) == 0)
                    {
                        std::cout << "Ошибка: дублирование функции "
                            << lex.idTable.table[i].id << std::endl;
                        throw ERROR_THROW(132);
                    }
                }
            }
        }

        if (!hasMain)
        {
            std::cout << "Ошибка: функция Main не объявлена" << std::endl;
            throw ERROR_THROW(131);
        }

        return true;
    }
}
