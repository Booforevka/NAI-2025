#include "stdafx.h"
#include "LT.h"
#include "Error.h"

namespace LT
{
	LexTable Create(int size)
	{
		if (size > LT_MAXSIZE)
		{
			throw ERROR_THROW(106);  
		}

		LexTable lextable;
		lextable.maxsize = size;
		lextable.size = 0;
		lextable.table = new Entry[size];

		return lextable;
	}

	void Add(LexTable& lextable, Entry entry)
	{
		if (lextable.size >= lextable.maxsize)
		{
			throw ERROR_THROW(107);  
		}

		lextable.table[lextable.size] = entry;
		lextable.size++;
	}

	Entry GetEntry(LexTable& lextable, int n)
	{
		if (n < 0 || n >= lextable.size)
		{
			throw ERROR_THROW(107);  
		}

		return lextable.table[n];
	}

	void Delete(LexTable& lextable)
	{
		delete[] lextable.table;
		lextable.table = nullptr;
		lextable.size = 0;
		lextable.maxsize = 0;
	}
	void PrintLexTable(LexTable& lextable, const wchar_t* in)
	{
		ofstream* streamToLexem = new ofstream;
		streamToLexem->open(in);
		if (streamToLexem->is_open())
		{
			(*streamToLexem) << "--------- Таблица лексем ---------\n";

			int num_string = -1;  

			for (int i = 0; i < lextable.size; i++)
			{
				
				if (num_string != lextable.table[i].sn)
				{
					num_string = lextable.table[i].sn;
					(*streamToLexem) << '\n' << num_string << ".\t";
				}

				
				(*streamToLexem) << lextable.table[i].lexema[0];

				
				if (lextable.table[i].lexema[0] == '@' && lextable.table[i].idxTI != LT_TI_NULLIDX)
				{
					(*streamToLexem) << lextable.table[i].idxTI;
				}
			}
		}
		else
			throw ERROR_THROW(128);
		streamToLexem->close();
		delete streamToLexem;
	}

}
