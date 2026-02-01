#pragma once

#define LEXEMA_FIXSIZE	2		// фиксированный размер лексемы
#define LT_MAXSIZE		4096	// максимальное количество строк в таблице лексем
#define LT_TI_NULLIDX	0xffffffff	// нет элемента таблицы идентификаторов

#define LEX_TYPE		't'	// лексема дл€ типов данных (int, char, str, bool)
#define LEX_LITERAL		'l'	// лексема дл€ литерала
#define LEX_ID			'i'	// лексема дл€ идентификатора
#define LEX_FUNC		'f'	// лексема дл€ Func
#define LEX_MAINFUNC	'm'	// лексема дл€ Main
#define LEX_DECLARE		'd'	// лексема дл€ my (объ€вление)
#define LEX_RETURN		'r'	// лексема дл€ return
#define LEX_OUT			'o'	// лексема дл€ OUT (вывод)
#define LEX_CYCLE		'c'	// лексема дл€ Cycle (цикл)
#define LEX_SEMICOLON	';'	// ;
#define LEX_COMMA		','	// ,
#define LEX_LEFTBRACE	'{'	// {
#define LEX_RIGHTBRACE	'}'	// }
#define LEX_LEFTTHESIS	'('	// (
#define LEX_RIGHTTHESIS	')'	// )
#define LEX_OPERATION	'v'	// операции (+, -, *, &, |)
#define LEX_EQUAL		'='	// =
#define LEX_COMPARISON	'b'	// операторы сравнени€ (>, <, ==, !=)
#define LEX_TILDE		'~'	// ~ (побитовое Ќ≈)
#define LEX_THREEPTS	'.'	// ... (диапазон дл€ цикла)

namespace LT		// таблица лексем
{
	struct Entry	// строка таблицы лексем
	{
		char lexema[LEXEMA_FIXSIZE + 1];	// лексема (символ или последовательность)
		int sn;								// номер строки в исходном тексте
		int idxTI;							// индекс в таблице идентификаторов или LT_TI_NULLIDX
	};

	struct LexTable		// экземпл€р таблицы лексем
	{
		int maxsize;	// Ємкость таблицы лексем < LT_MAXSIZE
		int size;		// текущий размер таблицы лексем < maxsize
		Entry* table;	// массив строк таблицы лексем
	};

	LexTable Create(		// создать таблицу лексем
		int size			// Ємкость таблицы лексем < LT_MAXSIZE
	);

	void Add(				// добавить строку в таблицу лексем
		LexTable& lextable,	// экземпл€р таблицы лексем
		Entry entry			// строка таблицы лексем
	);

	Entry GetEntry(			// получить строку таблицы лексем
		LexTable& lextable,	// экземпл€р таблицы лексем
		int n				// номер получаемой строки
	);

	void Delete(LexTable& lextable);	// удалить таблицу лексем (освободить пам€ть)

	void PrintLexTable(LexTable& lextable, const wchar_t* filename);
};
