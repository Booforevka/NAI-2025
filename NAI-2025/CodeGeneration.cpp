#include "CodeGeneration.h"
#include <stack>
#include <set>
#include <string>
#include <iostream>
#include <map>

namespace CodeGeneration {

	static int cycleCounter = 0;

	bool isReservedWord(const char* id) {
		static const char* reserved[] = {
		"byte", "word", "dword", "ptr", "offset",
		"eax", "ebx", "ecx", "edx", "esi", "edi", "ebp", "esp",
		"al", "ah", "bl", "bh", "cl", "ch", "dl", "dh",
		"ax", "bx", "cx", "dx", "si", "di", "bp", "sp",
		"mod", "even", "odd", "near", "far", "proc", "endp",
		"segment", "assume", "end", "db", "dw", "dd", "equ",
		"start", "code", "data", "stack", "const"
		};

		for (int i = 0; i < sizeof(reserved) / sizeof(reserved[0]); i++) {
			if (_stricmp(id, reserved[i]) == 0) {
				return true;
			}
		}
		return false;
	}

	std::string SafeName(const char* id) {
		if (isReservedWord(id)) {
			return std::string("v_") + id;
		}
		return std::string(id);
	}

	void HeadOut(Out::OUT& out) {
		*out.stream << ".586P\n";
		*out.stream << ".model flat, stdcall\n";
		*out.stream << "includelib libucrt.lib\n";
		*out.stream << "includelib kernel32.lib\n";
		*out.stream << "includelib ../Debug/LIB.lib\n\n";

		*out.stream << "; Прототипы внешних функций\n";
		*out.stream << "ExitProcess PROTO :DWORD\n";
		*out.stream << "SetConsoleCP PROTO :DWORD\n";
		*out.stream << "SetConsoleOutputCP PROTO :DWORD\n\n";

		*out.stream << "; Прототипы стандартных функций NAI-2025\n";
		*out.stream << "nabs PROTO :SDWORD\n";
		*out.stream << "npow PROTO :SDWORD, :SDWORD\n";
		*out.stream << "outint PROTO :SDWORD\n";
		*out.stream << "outchar PROTO :DWORD\n";
		*out.stream << "outstr PROTO :DWORD\n";
		*out.stream << "outbool PROTO :DWORD\n";
		*out.stream << "outnewline PROTO\n\n";

		*out.stream << ".stack 4096\n\n";
	}

	void ConstOut(Out::OUT& out, LA::LEX& lex) {
		*out.stream << ".const\n";

		for (int i = 0; i < lex.idTable.size; i++) {
			if (lex.idTable.table[i].idtype == IT::L) {
				std::string safeName = SafeName(lex.idTable.table[i].id);
				*out.stream << "\t" << safeName;

				switch (lex.idTable.table[i].iddatatype) {
				case IT::INT:
					*out.stream << " SDWORD " << lex.idTable.table[i].value.vint;
					break;
				case IT::CH:
					*out.stream << " BYTE " << (unsigned int)lex.idTable.table[i].value.vchar;
					break;
				case IT::STR:
					*out.stream << " BYTE \"" << lex.idTable.table[i].value.vstr.str << "\", 0";
					break;
				case IT::BOOL:
					*out.stream << " BYTE " << (lex.idTable.table[i].value.vbool ? "1" : "0");
					break;
				}
				*out.stream << "\n";
			}
		}
		*out.stream << "\n";
	}

	void DataOut(Out::OUT& out, LA::LEX& lex) {
		*out.stream << ".data\n";

		
		for (int i = 0; i < lex.idTable.size; i++) {
			if (lex.idTable.table[i].idtype != IT::V) {
				continue;
			}

			
			std::string varName = std::string(lex.idTable.table[i].id);
			if (varName.find("Main") != 0) {
				
				continue;
			}

			
			std::string safeName = SafeName(lex.idTable.table[i].id);
			*out.stream << "\t" << safeName;

			switch (lex.idTable.table[i].iddatatype) {
			case IT::INT:
			case IT::BOOL:
				*out.stream << " SDWORD 0";
				break;
			case IT::CH:
				*out.stream << " BYTE 0";
				break;
			case IT::STR:
				*out.stream << " DWORD ?";
				break;
			}
			*out.stream << "\n";
		}
		*out.stream << "\n\n";
	}

	IT::IDDATATYPE GetExpressionType(LA::LEX& lex, int start, int end) {
		for (int i = start; i <= end; i++) {
			char lexem = lex.lexTable.table[i].lexema[0];
			if (lexem == 'i' || lexem == 'l') {
				int idx = lex.lexTable.table[i].idxTI;
				if (idx != LT_TI_NULLIDX && idx < lex.idTable.size) {
					return lex.idTable.table[idx].iddatatype;
				}
			}
		}
		return IT::INT;
	}

	int FindSemicolon(LA::LEX& lex, int start) {
		for (int i = start; i < lex.lexTable.size; i++) {
			if (lex.lexTable.table[i].lexema[0] == ';') {
				return i;
			}
		}
		return -1;
	}

	int FindBlockEnd(LA::LEX& lex, int start) {
		int braceCount = 1;
		for (int i = start + 1; i < lex.lexTable.size; i++) {
			if (lex.lexTable.table[i].lexema[0] == '{') {
				braceCount++;
			}
			else if (lex.lexTable.table[i].lexema[0] == '}') {
				braceCount--;
				if (braceCount == 0) {
					return i;
				}
			}
		}
		return -1;
	}

	std::string GetVarAddress(IT::Entry& entry, std::map<int, int>& stackOffsets, int idTableIdx) {
		if (stackOffsets.find(idTableIdx) != stackOffsets.end()) {
			int offset = stackOffsets[idTableIdx];
			if (offset > 0) {
				return "[ebp+" + std::to_string(offset) + "]";  
			}
			else {
				return "[ebp" + std::to_string(offset) + "]";   
			}
		}
		return SafeName(entry.id);  
	}

	void ExpressionHandler(std::ofstream& stream, LA::LEX& lex, int startpos, int endpos,
		std::map<int, int>& stackOffsets) {

		int stackDepth = 0; 

		for (int i = startpos; i <= endpos; i++) {
			char lexem = lex.lexTable.table[i].lexema[0];

			if (lexem == 'i' || lexem == 'l') {
				int idx = lex.lexTable.table[i].idxTI;
				if (idx != LT_TI_NULLIDX && idx < lex.idTable.size) {
					IT::Entry& entry = lex.idTable.table[idx];

					
					if (entry.idtype == IT::F || entry.idtype == IT::SF) {
						std::string funcName = SafeName(entry.id);
						if (entry.idtype == IT::SF) {
							if (strcmp(entry.id, "abs") == 0) {
								stream << "\tcall nabs\n";
							}
							else if (strcmp(entry.id, "pow") == 0) {
								stream << "\tcall npow\n";
							}
						}
						else if (entry.idtype == IT::F) {
							stream << "\tcall " << funcName << "\n";
						}
						stream << "\tpush eax\n";
						stackDepth++; 
						continue;
					}

					std::string varAddr = GetVarAddress(entry, stackOffsets, idx);

					
					if (entry.iddatatype == IT::CH && entry.idtype == IT::L) {
						stream << "\tmovsx eax, BYTE PTR " << varAddr << "\n";
						stream << "\tpush eax\n";
					}
					
					else if (entry.iddatatype == IT::STR && entry.idtype == IT::L) {
						stream << "\tpush offset " << varAddr << "\n";
					}
					
					else {
						
						if (entry.iddatatype == IT::BOOL && entry.idtype == IT::L) {
							stream << "\tmovzx eax, BYTE PTR " << varAddr << "\n";
						}
						
						else if (entry.iddatatype == IT::BOOL && entry.idtype == IT::V) {
							stream << "\tmov eax, " << varAddr << "\n";  
						}
						else {
							stream << "\tmov eax, " << varAddr << "\n";
						}
						stream << "\tpush eax\n";
					}
					stackDepth++; 
				}
			}
			else if (lexem == 'v') {
				char operation = lex.lexTable.table[i].lexema[1];

				
				bool isUnary = (stackDepth == 1 && operation == '-');

				if (isUnary) {
					
					stream << "\tpop eax\n";
					stream << "\tneg eax\n";
					stream << "\tpush eax\n";
					
				}
				else {
					
					stream << "\tpop ebx\n";
					stream << "\tpop eax\n";
					switch (operation) {
					case '+': stream << "\tadd eax, ebx\n"; break;
					case '-': stream << "\tsub eax, ebx\n"; break;
					case '*': stream << "\timul ebx\n"; break;
					case '&': stream << "\tand eax, ebx\n"; break;
					case '|': stream << "\tor eax, ebx\n"; break;
					}
					stream << "\tpush eax\n";
					stackDepth -= 1; 
				}
			}
			else if (lexem == '~') {
				stream << "\tpop eax\n";
				stream << "\tnot eax\n";
				stream << "\tpush eax\n";
				
			}
			else if (lexem == 'b') {
				char comparison = lex.lexTable.table[i].lexema[1];
				stream << "\tpop ebx\n";
				stream << "\tpop eax\n";
				stream << "\tcmp eax, ebx\n";
				stream << "\tmov eax, 0\n";
				switch (comparison) {
				case '<': stream << "\tsetl al\n"; break;
				case '>': stream << "\tsetg al\n"; break;
				case '=': stream << "\tsete al\n"; break;
				case '!': stream << "\tsetne al\n"; break;
				}
				stream << "\tmovzx eax, al\n";
				stream << "\tpush eax\n";
				stackDepth -= 1; 
			}
		}
	}


	void ProcessBlock(Out::OUT& out, LA::LEX& lex, int start, int end, int paramCount,
		std::map<int, int>& stackOffsets);

	
	void ProcessBlock(Out::OUT& out, LA::LEX& lex, int start, int end, int paramCount) {
		std::map<int, int> emptyMap;
		ProcessBlock(out, lex, start, end, paramCount, emptyMap);
	}

	void ProcessBlock(Out::OUT& out, LA::LEX& lex, int start, int end, int paramCount,
		std::map<int, int>& stackOffsets) {
		int i = start;
		while (i <= end) {
			char lexem = lex.lexTable.table[i].lexema[0];



			if (lexem == 'd') {

				int declEnd = i;
				bool hasInit = false;
				int equalPos = -1;

				while (declEnd <= end && lex.lexTable.table[declEnd].lexema[0] != ';') {
					if (lex.lexTable.table[declEnd].lexema[0] == '=') {
						hasInit = true;
						equalPos = declEnd;
					}
					declEnd++;
				}

				if (hasInit && equalPos != -1) {

					int varPos = -1;
					for (int j = i; j < equalPos; j++) {
						if (lex.lexTable.table[j].lexema[0] == 'i') {
							varPos = j;
							break;
						}
					}

					if (varPos != -1) {
						int idIdx = lex.lexTable.table[varPos].idxTI;
						if (idIdx != LT_TI_NULLIDX && idIdx < lex.idTable.size) {
							IT::Entry& varEntry = lex.idTable.table[idIdx];
							std::string varAddr = GetVarAddress(varEntry, stackOffsets, idIdx);
							*out.stream << "; " << varEntry.id << " = ... (инициализация)\n";


							int exprStart = equalPos + 1;
							int exprEnd = declEnd - 1;

							ExpressionHandler(*out.stream, lex, exprStart, exprEnd, stackOffsets);
							*out.stream << "\tpop eax\n";

							if (varEntry.iddatatype == IT::INT || varEntry.iddatatype == IT::BOOL) {
								*out.stream << "\tmov " << varAddr << ", eax\n";
							}
							else if (varEntry.iddatatype == IT::CH) {
								*out.stream << "\tmov " << varAddr << ", al\n";
							}
							else if (varEntry.iddatatype == IT::STR) {
								*out.stream << "\tmov " << varAddr << ", eax\n";
							}
						}
					}
				}


				i = declEnd + 1;
				continue;
			}



			if (lexem == 'i' && i + 1 <= end && lex.lexTable.table[i + 1].lexema[0] == '=') {
				int idIdx = lex.lexTable.table[i].idxTI;
				if (idIdx != LT_TI_NULLIDX && idIdx < lex.idTable.size) {
					IT::Entry& varEntry = lex.idTable.table[idIdx];

					if (varEntry.idtype == IT::L || varEntry.idtype == IT::F || varEntry.idtype == IT::SF) {
						while (i <= end && lex.lexTable.table[i].lexema[0] != ';') {
							i++;
						}
						i++;
						continue;
					}

					std::string varAddr = GetVarAddress(varEntry, stackOffsets, idIdx);
					*out.stream << "; " << varEntry.id << " = ...\n";

					int exprStart = i + 2;
					int exprEnd = exprStart;
					while (exprEnd <= end && lex.lexTable.table[exprEnd].lexema[0] != ';') {
						exprEnd++;
					}
					exprEnd--;

					ExpressionHandler(*out.stream, lex, exprStart, exprEnd, stackOffsets);
					*out.stream << "\tpop eax\n";

					if (varEntry.iddatatype == IT::INT || varEntry.iddatatype == IT::BOOL) {
						*out.stream << "\tmov " << varAddr << ", eax\n";
					}
					else if (varEntry.iddatatype == IT::CH) {
						*out.stream << "\tmov " << varAddr << ", al\n";
					}
					else if (varEntry.iddatatype == IT::STR) {
						*out.stream << "\tmov " << varAddr << ", eax\n";
					}

					i = exprEnd + 2;
					continue;
				}
			}

			if (lexem == 'o') {
				int exprStart = i + 1;
				int exprEnd = exprStart;
				while (exprEnd <= end && lex.lexTable.table[exprEnd].lexema[0] != ';') {
					exprEnd++;
				}
				exprEnd--;
				*out.stream << "\tpush ecx\n";
				*out.stream << "; OUT выражение\n";

				IT::IDDATATYPE outputType = IT::INT;
				if (exprStart == exprEnd) {
					if (lex.lexTable.table[exprStart].lexema[0] == 'i' ||
						lex.lexTable.table[exprStart].lexema[0] == 'l') {
						int outIdx = lex.lexTable.table[exprStart].idxTI;
						if (outIdx != LT_TI_NULLIDX && outIdx < lex.idTable.size) {
							IT::Entry& entry = lex.idTable.table[outIdx];
							outputType = entry.iddatatype;
						}
					}
				}

				if (outputType == IT::CH && exprStart == exprEnd) {
					int outIdx = lex.lexTable.table[exprStart].idxTI;
					if (outIdx != LT_TI_NULLIDX && outIdx < lex.idTable.size) {
						IT::Entry& entry = lex.idTable.table[outIdx];
						std::string varAddr = GetVarAddress(entry, stackOffsets, outIdx);

						if (entry.idtype == IT::V || entry.idtype == IT::P) {
							*out.stream << "\tmovzx eax, BYTE PTR " << varAddr << "\n";
						}
						else if (entry.idtype == IT::L) {
							*out.stream << "\tmovsx eax, BYTE PTR " << varAddr << "\n";
						}
						*out.stream << "\tpush eax\n";
					}
				}
				else if (outputType == IT::BOOL && exprStart == exprEnd) {
					int outIdx = lex.lexTable.table[exprStart].idxTI;
					if (outIdx != LT_TI_NULLIDX && outIdx < lex.idTable.size) {
						IT::Entry& entry = lex.idTable.table[outIdx];
						std::string varAddr = GetVarAddress(entry, stackOffsets, outIdx);

						if (entry.idtype == IT::L) {
							*out.stream << "\tmovzx eax, BYTE PTR " << varAddr << "\n";
						}
						else {
							*out.stream << "\tmov eax, " << varAddr << "\n";
						}
						*out.stream << "\tpush eax\n";
					}
				}
				else {
					ExpressionHandler(*out.stream, lex, exprStart, exprEnd, stackOffsets);
					*out.stream << "\tpop eax\n";
					*out.stream << "\tpush eax\n";
				}

				switch (outputType) {
				case IT::CH:
					*out.stream << "\tcall outchar\n";
					break;
				case IT::STR:
					*out.stream << "\tcall outstr\n";
					break;
				case IT::BOOL:
					*out.stream << "\tcall outbool\n";
					break;
				default:
					*out.stream << "\tcall outint\n";
					break;
				}

				*out.stream << "\tcall outnewline\n";
				*out.stream << "\tpop ecx\n";
				i = exprEnd + 2;
				continue;
			}



			if (lexem == 'r') {
				*out.stream << "; return\n";
				int exprStart = i + 1;
				int exprEnd = exprStart;
				while (exprEnd <= end && lex.lexTable.table[exprEnd].lexema[0] != ';') {
					exprEnd++;
				}
				exprEnd--;

				ExpressionHandler(*out.stream, lex, exprStart, exprEnd, stackOffsets);
				*out.stream << "\tpop eax\n";

				*out.stream << "\tmov esp, ebp\n";
				*out.stream << "\tpop ebp\n";
				if (paramCount > 0) {
					*out.stream << "\tret " << (paramCount * 4) << "\n";
				}
				else {
					*out.stream << "\tret\n";
				}
				i = exprEnd + 2;
				continue;
			}


			if (lexem == 'c') {
				int currentCycle = cycleCounter++;
				std::string cycleLabel = "Cycle_" + std::to_string(currentCycle);
				std::string endLabel = "EndCycle_" + std::to_string(currentCycle);

				int startIdx = -1, endIdx = -1, braceStart = -1;

				if (i + 1 <= end) {
					char nextChar = lex.lexTable.table[i + 1].lexema[0];
					if (nextChar == 'l' || nextChar == 'i') {
						startIdx = lex.lexTable.table[i + 1].idxTI;
					}
				}

				for (int k = i; k <= end && k < i + 10; k++) {
					if (lex.lexTable.table[k].lexema[0] == '.') {
						if (k + 1 <= end) {
							char nextLex = lex.lexTable.table[k + 1].lexema[0];
							if (nextLex == 'i' || nextLex == 'l') {
								endIdx = lex.lexTable.table[k + 1].idxTI;
							}
						}
					}
					if (lex.lexTable.table[k].lexema[0] == '{') {
						braceStart = k;
						break;
					}
				}

				int braceCount = 1;
				int braceEnd = -1;
				for (int k = braceStart + 1; k <= end; k++) {
					if (lex.lexTable.table[k].lexema[0] == '{') braceCount++;
					if (lex.lexTable.table[k].lexema[0] == '}') {
						braceCount--;
						if (braceCount == 0) {
							braceEnd = k;
							break;
						}
					}
				}

				if (startIdx != -1 && endIdx != -1 && braceStart != -1 && braceEnd != -1) {
					IT::Entry& startEntry = lex.idTable.table[startIdx];
					IT::Entry& endEntry = lex.idTable.table[endIdx];

					std::string cycleVar = "";
					int cycleVarIdx = -1;
					for (int k = i - 1; k >= start; k--) {
						if (lex.lexTable.table[k].lexema[0] == 'i') {
							int varIdx = lex.lexTable.table[k].idxTI;
							if (varIdx != LT_TI_NULLIDX && varIdx < lex.idTable.size) {
								IT::Entry& entry = lex.idTable.table[varIdx];
								if (entry.idtype == IT::V && entry.iddatatype == IT::INT) {
									std::string name = std::string(entry.id);
									if (name.length() > 0 && name.back() == 'i') {
										cycleVar = GetVarAddress(entry, stackOffsets, varIdx);
										cycleVarIdx = varIdx;
										break;
									}
								}
							}
						}
					}

					*out.stream << "\n";
					std::string startAddr = GetVarAddress(startEntry, stackOffsets, startIdx);
					std::string endAddr = GetVarAddress(endEntry, stackOffsets, endIdx);

					// Инициализация счетчика
					*out.stream << "\tmov eax, " << startAddr << "\n";
					*out.stream << "\tmov ecx, eax\n";

					// *** ИСПРАВЛЕНИЕ: Проверка условия ДО входа в цикл ***
					*out.stream << "\tmov eax, " << endAddr << "\n";
					*out.stream << "\tcmp ecx, eax\n";
					*out.stream << "\tjg " << endLabel << "\n";  // Если start > end, пропустить цикл

					// Метка начала цикла
					*out.stream << cycleLabel << ":\n";

					if (!cycleVar.empty()) {
						*out.stream << "\tmov " << cycleVar << ", ecx\n";
					}

					ProcessBlock(out, lex, braceStart + 1, braceEnd - 1, paramCount, stackOffsets);

					*out.stream << "\tinc ecx\n";
					*out.stream << "\tmov eax, " << endAddr << "\n";
					*out.stream << "\tcmp ecx, eax\n";
					*out.stream << "\tjle " << cycleLabel << "\n";
					*out.stream << endLabel << ":\n";

					i = braceEnd + 1;
					continue;
				}
			}
			i++;
		}
	}


	void FunctionsOut(Out::OUT& out, LA::LEX& lex) {
		for (int i = 0; i < lex.idTable.size; i++) {
			if (lex.idTable.table[i].idtype == IT::SF) continue;
			if (lex.idTable.table[i].idtype != IT::F) continue;

			std::string funcName = lex.idTable.table[i].id;
			std::string safeName = SafeName(funcName.c_str());

			
			std::vector<int> paramIndices;
			std::vector<int> localVarIndices;
			std::map<int, int> stackOffsets;

			for (int j = 0; j < lex.idTable.size; j++) {
				std::string varName = std::string(lex.idTable.table[j].id);
				if (varName.find(funcName) == 0 && varName != funcName) {
					if (lex.idTable.table[j].idtype == IT::P) {
						paramIndices.push_back(j);
					}
					else if (lex.idTable.table[j].idtype == IT::V) {
						localVarIndices.push_back(j);
					}
				}
			}

			

			for (size_t p = 0; p < paramIndices.size(); p++) {
				stackOffsets[paramIndices[p]] = 8 + (paramIndices.size() - 1 - p) * 4;
			}

			for (size_t l = 0; l < localVarIndices.size(); l++) {
				stackOffsets[localVarIndices[l]] = -((int)(l + 1) * 4);
			}

			*out.stream << "\n" << safeName << " PROC\n";
			*out.stream << "\tpush ebp\n";
			*out.stream << "\tmov ebp, esp\n";

			if (localVarIndices.size() > 0) {
				*out.stream << "\tsub esp, " << (localVarIndices.size() * 4) << " ; locals\n";
			}

			int funcStart = lex.idTable.table[i].idxfirstLE;
			int braceCount = 0;
			int bodyStart = -1, bodyEnd = -1;

			for (int k = funcStart; k < lex.lexTable.size; k++) {
				if (lex.lexTable.table[k].lexema[0] == '{') {
					if (braceCount == 0) bodyStart = k + 1;
					braceCount++;
				}
				else if (lex.lexTable.table[k].lexema[0] == '}') {
					braceCount--;
					if (braceCount == 0) {
						bodyEnd = k - 1;
						break;
					}
				}
			}

			if (bodyStart != -1 && bodyEnd != -1) {
				ProcessBlock(out, lex, bodyStart, bodyEnd, paramIndices.size(), stackOffsets);
			}

			
			bool hasReturn = false;
			for (int k = bodyStart; k <= bodyEnd; k++) {
				if (lex.lexTable.table[k].lexema[0] == 'r') {
					hasReturn = true;
					break;
				}
			}
			if (!hasReturn) {
				*out.stream << "\txor eax, eax\n";
				*out.stream << "\tmov esp, ebp\n";
				*out.stream << "\tpop ebp\n";
				if (paramIndices.size() > 0) {
					*out.stream << "\tret " << (paramIndices.size() * 4) << "\n";
				}
				else {
					*out.stream << "\tret\n";
				}
			}

			*out.stream << safeName << " ENDP\n";
		}
	}

	void CodeOut(Out::OUT& out, LA::LEX& lex) {
		*out.stream << ".code\n";
		FunctionsOut(out, lex);

		*out.stream << "\nmain PROC\n";
		*out.stream << "\tInvoke SetConsoleCP, 1251\n";
		*out.stream << "\tInvoke SetConsoleOutputCP, 1251\n\n";

		int mainPos = -1;
		for (int i = 0; i < lex.lexTable.size; i++) {
			if (lex.lexTable.table[i].lexema[0] == 'm') {
				mainPos = i;
				break;
			}
		}

		if (mainPos != -1) {
			int braceCount = 0;
			int bodyStart = -1, bodyEnd = -1;

			for (int k = mainPos; k < lex.lexTable.size; k++) {
				if (lex.lexTable.table[k].lexema[0] == '{') {
					if (braceCount == 0) bodyStart = k + 1;
					braceCount++;
				}
				else if (lex.lexTable.table[k].lexema[0] == '}') {
					braceCount--;
					if (braceCount == 0) {
						bodyEnd = k - 1;
						break;
					}
				}
			}

			if (bodyStart != -1 && bodyEnd != -1) {
				ProcessBlock(out, lex, bodyStart, bodyEnd, 0);
			}
		}

		*out.stream << "\n\tpush 0\n";
		*out.stream << "\tcall ExitProcess\n";
		*out.stream << "main ENDP\n";
		*out.stream << "end main\n";
	}

	void GenerateCode(LA::LEX& lex, Out::OUT& out) {
		cycleCounter = 0;
		HeadOut(out);
		ConstOut(out, lex);
		DataOut(out, lex);
		CodeOut(out, lex);
	}

} 
