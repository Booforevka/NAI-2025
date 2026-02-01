#include "stdafx.h"
#include "PolishNotation.h"
#include <stack>

namespace PN
{
	
	int getPriority(char op)
	{
		switch (op)
		{
		case '~':          
			return 1;
		case '*':           
			return 2;
		case '+':           
		case '-':           
			return 3;
		case '&':           
		case '|':           
			return 4;
		case '=':           
		case '!':           
		case '>':           
		case '<':           
			return 5;
		default:
			return 999;
		}
	}

	bool PolishNotation(int lextable_pos, LT::LexTable& lextable, IT::IdTable& idtable)
	{
		std::stack<LT::Entry> stack;
		std::queue<LT::Entry> queue;
		LT::Entry temp;
		int lexTable_size = lextable.size;
		int pos = lextable_pos;
		int countLex = 0;
		int semicolonIndex = 0;

		
		for (int i = pos; i < lexTable_size && lextable.table[i].lexema[0] != LEX_SEMICOLON; i++)
		{
			semicolonIndex = i;
			countLex++;
		}

		LT::Entry* new_mas = new LT::Entry[countLex];
		char currentLexem;
		char stackLexem;

		
		for (int i = pos; i <= semicolonIndex; i++)
		{
			currentLexem = lextable.table[i].lexema[0];

			
			if (currentLexem == LEX_ID && i + 1 <= semicolonIndex &&
				lextable.table[i + 1].lexema[0] == LEX_LEFTTHESIS)
			{
				stack.push(lextable.table[i]);
			}
			
			else if (currentLexem == LEX_ID || currentLexem == LEX_LITERAL)
			{
				queue.push(lextable.table[i]);
			}
			
			else if (currentLexem == LEX_LEFTTHESIS)
			{
				stack.push(lextable.table[i]);
			}
			
			else if (currentLexem == LEX_RIGHTTHESIS)
			{
				
				while (!stack.empty() && stack.top().lexema[0] != LEX_LEFTTHESIS)
				{
					queue.push(stack.top());
					stack.pop();
				}
				if (!stack.empty())
				{
					stack.pop(); 
				}

				
				if (!stack.empty() && stack.top().lexema[0] == LEX_ID)
				{
					int idx = stack.top().idxTI;
					if (idx != LT_TI_NULLIDX && idx < idtable.size)
					{
						
						if (idtable.table[idx].idtype == IT::F || idtable.table[idx].idtype == IT::SF)
						{
							queue.push(stack.top());
							stack.pop();
						}
					}
				}
			}
			
			
			else if (currentLexem == LEX_OPERATION || currentLexem == LEX_COMPARISON || currentLexem == LEX_TILDE)
			{
				char currentOp;
				if (currentLexem == LEX_OPERATION || currentLexem == LEX_COMPARISON)
				{
					currentOp = lextable.table[i].lexema[1];

			
					if (currentOp == '-' && i > pos) {
						char prevLexem = lextable.table[i - 1].lexema[0];
						if (prevLexem == LEX_LEFTTHESIS || prevLexem == LEX_COMMA) {
			
							queue.push(lextable.table[i]);
							continue;  
						}
					}
				}
				else
				{
					currentOp = '~';
				}

				
				while (!stack.empty())
				{
					stackLexem = stack.top().lexema[0];

					if (stackLexem == LEX_LEFTTHESIS)
						break;

					char stackOp;
					if (stackLexem == LEX_OPERATION || stackLexem == LEX_COMPARISON)
					{
						stackOp = stack.top().lexema[1];
					}
					else if (stackLexem == LEX_TILDE)
					{
						stackOp = '~';
					}
					else
					{
						break;
					}

					if (getPriority(stackOp) <= getPriority(currentOp))
					{
						queue.push(stack.top());
						stack.pop();
					}
					else
					{
						break;
					}
				}

				stack.push(lextable.table[i]);
			}
			
			else if (currentLexem == LEX_COMMA)
			{
				while (!stack.empty() && stack.top().lexema[0] != LEX_LEFTTHESIS)
				{
					queue.push(stack.top());
					stack.pop();
				}
			}
		}

		
		while (!stack.empty())
		{
			if (stack.top().lexema[0] != LEX_LEFTTHESIS &&
				stack.top().lexema[0] != LEX_RIGHTTHESIS)
			{
				queue.push(stack.top());
			}
			stack.pop();
		}

		
		int idx = 0;
		while (!queue.empty())
		{
			new_mas[idx++] = queue.front();
			queue.pop();
		}

		
		for (int i = 0; i < idx; i++)  
		{
			lextable.table[pos + i] = new_mas[i];
		}

		if (idx < countLex)
		{
			int shift = countLex - idx;
			for (int i = semicolonIndex + 1; i < lexTable_size; i++)
			{
				lextable.table[i - shift] = lextable.table[i];
			}
			lextable.size -= shift;
		}
		delete[] new_mas;
		return true;
	}

	bool startPolish(LA::LEX& lex, Log::LOG log)  
	{
		try
		{
			std::cout << "\n====== ПОЛЬСКАЯ ЗАПИСЬ ======\n";
			*log.stream << "\n====== ПОЛЬСКАЯ ЗАПИСЬ ======\n";

			for (int i = 0; i < lex.lexTable.size; i++)
			{
				char lexem = lex.lexTable.table[i].lexema[0];

				
				if (lexem == LEX_EQUAL)
				{
					if (i + 1 < lex.lexTable.size)
					{
						
						*log.stream << "Преобразование строки " << lex.lexTable.table[i].sn << ": ";

						
						*log.stream << "ДО: ";
						for (int k = i + 1; k < lex.lexTable.size &&
							lex.lexTable.table[k].lexema[0] != LEX_SEMICOLON; k++)
						{
							
							*log.stream << lex.lexTable.table[k].lexema[0] << " ";
						}

						PolishNotation(i + 1, lex.lexTable, lex.idTable);

						
						
						*log.stream << "| ПОСЛЕ: ";
						for (int k = i + 1; k < lex.lexTable.size &&
							lex.lexTable.table[k].lexema[0] != LEX_SEMICOLON; k++)
						{
							
							*log.stream << lex.lexTable.table[k].lexema[0] << " ";
						}
						
						*log.stream << "\n";
					}
				}
				
				else if (lexem == LEX_RETURN)
				{
					if (i + 1 < lex.lexTable.size &&
						lex.lexTable.table[i + 1].lexema[0] != LEX_SEMICOLON)
					{
						
						*log.stream << "Преобразование строки " << lex.lexTable.table[i].sn << " (return): ";

						
						
						*log.stream << "ДО: ";
						for (int k = i + 1; k < lex.lexTable.size &&
							lex.lexTable.table[k].lexema[0] != LEX_SEMICOLON; k++)
						{
							
							*log.stream << lex.lexTable.table[k].lexema[0] << " ";
						}

						PolishNotation(i + 1, lex.lexTable, lex.idTable);


						
						*log.stream << "| ПОСЛЕ: ";
						for (int k = i + 1; k < lex.lexTable.size &&
							lex.lexTable.table[k].lexema[0] != LEX_SEMICOLON; k++)
						{
							
							*log.stream << lex.lexTable.table[k].lexema[0] << " ";
						}
						
						*log.stream << "\n";
					}
				}
				
				else if (lexem == LEX_OUT)
				{
					if (i + 1 < lex.lexTable.size &&
						lex.lexTable.table[i + 1].lexema[0] != LEX_SEMICOLON)
					{
						
						*log.stream << "Преобразование строки " << lex.lexTable.table[i].sn << " (OUT): ";

						
						
						*log.stream << "ДО: ";
						for (int k = i + 1; k < lex.lexTable.size &&
							lex.lexTable.table[k].lexema[0] != LEX_SEMICOLON; k++)
						{
							
							*log.stream << lex.lexTable.table[k].lexema[0] << " ";
						}

						PolishNotation(i + 1, lex.lexTable, lex.idTable);

						
						
						*log.stream << "| ПОСЛЕ: ";
						for (int k = i + 1; k < lex.lexTable.size &&
							lex.lexTable.table[k].lexema[0] != LEX_SEMICOLON; k++)
						{
							
							*log.stream << lex.lexTable.table[k].lexema[0] << " ";
						}
						
						*log.stream << "\n";
					}
				}
			}

			return true;
		}
		catch (...)
		{
			std::cout << "Ошибка при построении польской записи" << std::endl;
			return false;
		}
	}
}
