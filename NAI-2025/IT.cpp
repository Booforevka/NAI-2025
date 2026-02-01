#include "stdafx.h"
#include "IT.h"
#include "Error.h"

namespace IT
{
	IdTable Create(int size)
	{
		if (size > TI_MAXSIZE)
		{
			throw ERROR_THROW(117);  
		}

		IdTable idtable;
		idtable.maxsize = size;
		idtable.size = 0;
		idtable.table = new Entry[size];

		return idtable;
	}

	void Add(IdTable& idtable, Entry entry)
	{
		if (idtable.size >= idtable.maxsize)
		{
			throw ERROR_THROW(118);  // Превышен размер таблицы идентификаторов
		}

		idtable.table[idtable.size] = entry;
		idtable.size++;
	}

	Entry GetEntry(IdTable& idtable, int n)
	{
		if (n < 0 || n >= idtable.size)
		{
			throw ERROR_THROW(118);  // Недопустимый индекс в таблице идентификаторов
		}

		return idtable.table[n];
	}

	int IsId(IdTable& idtable, char id[ID_MAXSIZE])
	{
		for (int i = 0; i < idtable.size; i++)
		{
			if (strcmp(idtable.table[i].id, id) == 0)
			{
				return i;
			}
		}
		return TI_NULLIDX;
	}

	int search(IdTable& idtable, Entry entry)
	{
		for (int i = 0; i < idtable.size; i++)
		{
			if (strcmp(idtable.table[i].id, entry.id) == 0)
			{
				return i;
			}
		}
		return -1;
	}

	void Delete(IdTable& idtable)
	{
		delete[] idtable.table;
		idtable.table = nullptr;
		idtable.size = 0;
		idtable.maxsize = 0;
	}
}
