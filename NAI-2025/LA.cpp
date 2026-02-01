#include "stdafx.h"
#include"Log.h"
LT::LexTable lextab = LT::Create(LT_MAXSIZE - 1);
IT::IdTable idtab = IT::Create(TI_MAXSIZE - 1);


bool keyMy(char word[]) {
	FST::FST fstMy(word, 3,
		FST::NODE(1, FST::RELATION('m', 1)),
		FST::NODE(1, FST::RELATION('y', 2)),
		FST::NODE()
	);
	return FST::execute(fstMy);
}

bool typeInt(char word[]) {
	FST::FST fstInt(word, 4,
		FST::NODE(1, FST::RELATION('i', 1)),
		FST::NODE(1, FST::RELATION('n', 2)),
		FST::NODE(1, FST::RELATION('t', 3)),
		FST::NODE()
	);
	return FST::execute(fstInt);
}

bool typeChar(char word[]) {
	FST::FST fstChar(word, 5,
		FST::NODE(1, FST::RELATION('c', 1)),
		FST::NODE(1, FST::RELATION('h', 2)),
		FST::NODE(1, FST::RELATION('a', 3)),
		FST::NODE(1, FST::RELATION('r', 4)),
		FST::NODE()
	);
	return FST::execute(fstChar);
}

bool typeStr(char word[]) {
	FST::FST fstStr(word, 4,
		FST::NODE(1, FST::RELATION('s', 1)),
		FST::NODE(1, FST::RELATION('t', 2)),
		FST::NODE(1, FST::RELATION('r', 3)),
		FST::NODE()
	);
	return FST::execute(fstStr);
}

bool typeBool(char word[]) {
	FST::FST fstBool(word, 5,
		FST::NODE(1, FST::RELATION('b', 1)),
		FST::NODE(1, FST::RELATION('o', 2)),
		FST::NODE(1, FST::RELATION('o', 3)),
		FST::NODE(1, FST::RELATION('l', 4)),
		FST::NODE()
	);
	return FST::execute(fstBool);
}

bool keyFunc(char word[]) {
	FST::FST fstFunc(word, 5,
		FST::NODE(1, FST::RELATION('F', 1)),
		FST::NODE(1, FST::RELATION('u', 2)),
		FST::NODE(1, FST::RELATION('n', 3)),
		FST::NODE(1, FST::RELATION('c', 4)),
		FST::NODE()
	);
	return FST::execute(fstFunc);
}

bool keyReturn(char word[]) {
	FST::FST fstReturn(word, 7,
		FST::NODE(1, FST::RELATION('r', 1)),
		FST::NODE(1, FST::RELATION('e', 2)),
		FST::NODE(1, FST::RELATION('t', 3)),
		FST::NODE(1, FST::RELATION('u', 4)),
		FST::NODE(1, FST::RELATION('r', 5)),
		FST::NODE(1, FST::RELATION('n', 6)),
		FST::NODE()
	);
	return FST::execute(fstReturn);
}

bool keyMain(char word[]) {
	FST::FST fstMain(word, 5,
		FST::NODE(1, FST::RELATION('M', 1)),
		FST::NODE(1, FST::RELATION('a', 2)),
		FST::NODE(1, FST::RELATION('i', 3)),
		FST::NODE(1, FST::RELATION('n', 4)),
		FST::NODE()
	);
	return FST::execute(fstMain);
}

bool keyOut(char word[]) {
	FST::FST fstOut(word, 4,
		FST::NODE(1, FST::RELATION('O', 1)),
		FST::NODE(1, FST::RELATION('U', 2)),
		FST::NODE(1, FST::RELATION('T', 3)),
		FST::NODE()
	);
	return FST::execute(fstOut);
}

bool keyCycle(char word[]) {
	FST::FST fstCycle(word, 6,
		FST::NODE(1, FST::RELATION('C', 1)),
		FST::NODE(1, FST::RELATION('y', 2)),
		FST::NODE(1, FST::RELATION('c', 3)),
		FST::NODE(1, FST::RELATION('l', 4)),
		FST::NODE(1, FST::RELATION('e', 5)),
		FST::NODE()
	);
	return FST::execute(fstCycle);
}

bool literalTrue(char word[]) {
	FST::FST fstTrue(word, 5,
		FST::NODE(1, FST::RELATION('t', 1)),
		FST::NODE(1, FST::RELATION('r', 2)),
		FST::NODE(1, FST::RELATION('u', 3)),
		FST::NODE(1, FST::RELATION('e', 4)),
		FST::NODE()
	);
	return FST::execute(fstTrue);
}

bool literalFalse(char word[]) {
	FST::FST fstFalse(word, 6,
		FST::NODE(1, FST::RELATION('f', 1)),
		FST::NODE(1, FST::RELATION('a', 2)),
		FST::NODE(1, FST::RELATION('l', 3)),
		FST::NODE(1, FST::RELATION('s', 4)),
		FST::NODE(1, FST::RELATION('e', 5)),
		FST::NODE()
	);
	return FST::execute(fstFalse);
}

bool funcAbs(char word[]) {
	FST::FST fstAbs(word, 4,
		FST::NODE(1, FST::RELATION('a', 1)),
		FST::NODE(1, FST::RELATION('b', 2)),
		FST::NODE(1, FST::RELATION('s', 3)),
		FST::NODE()
	);
	return FST::execute(fstAbs);
}

bool funcPow(char word[]) {
	FST::FST fstPow(word, 4,
		FST::NODE(1, FST::RELATION('p', 1)),
		FST::NODE(1, FST::RELATION('o', 2)),
		FST::NODE(1, FST::RELATION('w', 3)),
		FST::NODE()
	);
	return FST::execute(fstPow);
}

bool literalInteger(char word[]) {
	FST::FST fst(word, 2,
		FST::NODE(20,
			FST::RELATION('0', 0), FST::RELATION('1', 0), FST::RELATION('2', 0),
			FST::RELATION('3', 0), FST::RELATION('4', 0), FST::RELATION('5', 0),
			FST::RELATION('6', 0), FST::RELATION('7', 0), FST::RELATION('8', 0),
			FST::RELATION('9', 0), FST::RELATION('0', 1), FST::RELATION('1', 1),
			FST::RELATION('2', 1), FST::RELATION('3', 1), FST::RELATION('4', 1),
			FST::RELATION('5', 1), FST::RELATION('6', 1), FST::RELATION('7', 1),
			FST::RELATION('8', 1), FST::RELATION('9', 1)),
		FST::NODE()
	);
	return FST::execute(fst);
}

bool identif(char word[]) {
	FST::FST idenf(word, 2,
		FST::NODE(120,
			FST::RELATION('a', 1), FST::RELATION('a', 0),
			FST::RELATION('b', 1), FST::RELATION('b', 0),
			FST::RELATION('c', 1), FST::RELATION('c', 0),
			FST::RELATION('d', 1), FST::RELATION('d', 0),
			FST::RELATION('e', 1), FST::RELATION('e', 0),
			FST::RELATION('f', 1), FST::RELATION('f', 0),
			FST::RELATION('g', 1), FST::RELATION('g', 0),
			FST::RELATION('h', 0), FST::RELATION('h', 1),
			FST::RELATION('i', 0), FST::RELATION('i', 1),
			FST::RELATION('j', 0), FST::RELATION('j', 1),
			FST::RELATION('k', 0), FST::RELATION('k', 1),
			FST::RELATION('l', 0), FST::RELATION('l', 1),
			FST::RELATION('m', 0), FST::RELATION('m', 1),
			FST::RELATION('n', 0), FST::RELATION('n', 1),
			FST::RELATION('o', 0), FST::RELATION('o', 1),
			FST::RELATION('p', 0), FST::RELATION('p', 1),
			FST::RELATION('q', 0), FST::RELATION('q', 1),
			FST::RELATION('r', 0), FST::RELATION('r', 1),
			FST::RELATION('s', 0), FST::RELATION('s', 1),
			FST::RELATION('t', 0), FST::RELATION('t', 1),
			FST::RELATION('u', 0), FST::RELATION('u', 1),
			FST::RELATION('v', 0), FST::RELATION('v', 1),
			FST::RELATION('w', 0), FST::RELATION('w', 1),
			FST::RELATION('x', 0), FST::RELATION('x', 1),
			FST::RELATION('y', 0), FST::RELATION('y', 1),
			FST::RELATION('z', 0), FST::RELATION('z', 1),
			FST::RELATION('A', 1), FST::RELATION('A', 0),
			FST::RELATION('B', 1), FST::RELATION('B', 0),
			FST::RELATION('C', 1), FST::RELATION('C', 0),
			FST::RELATION('D', 1), FST::RELATION('D', 0),
			FST::RELATION('E', 1), FST::RELATION('E', 0),
			FST::RELATION('F', 1), FST::RELATION('F', 0),
			FST::RELATION('G', 1), FST::RELATION('G', 0),
			FST::RELATION('H', 0), FST::RELATION('H', 1),
			FST::RELATION('I', 0), FST::RELATION('I', 1),
			FST::RELATION('J', 0), FST::RELATION('J', 1),
			FST::RELATION('K', 0), FST::RELATION('K', 1),
			FST::RELATION('L', 0), FST::RELATION('L', 1),
			FST::RELATION('M', 0), FST::RELATION('M', 1),
			FST::RELATION('N', 0), FST::RELATION('N', 1),
			FST::RELATION('O', 0), FST::RELATION('O', 1),
			FST::RELATION('P', 0), FST::RELATION('P', 1),
			FST::RELATION('Q', 0), FST::RELATION('Q', 1),
			FST::RELATION('R', 0), FST::RELATION('R', 1),
			FST::RELATION('S', 0), FST::RELATION('S', 1),
			FST::RELATION('T', 0), FST::RELATION('T', 1),
			FST::RELATION('U', 0), FST::RELATION('U', 1),
			FST::RELATION('V', 0), FST::RELATION('V', 1),
			FST::RELATION('W', 0), FST::RELATION('W', 1),
			FST::RELATION('X', 0), FST::RELATION('X', 1),
			FST::RELATION('Y', 0), FST::RELATION('Y', 1),
			FST::RELATION('Z', 0), FST::RELATION('Z', 1),
			FST::RELATION('0', 1), FST::RELATION('1', 1),
			FST::RELATION('2', 1), FST::RELATION('3', 1),
			FST::RELATION('4', 1),
			FST::RELATION('5', 1), FST::RELATION('6', 1),
			FST::RELATION('7', 1),
			FST::RELATION('8', 1), FST::RELATION('9', 1),
			FST::RELATION('_', 1), FST::RELATION('_', 0)),
		FST::NODE()
	);
	return FST::execute(idenf);
}

namespace LA
{
	struct Flags {
		bool typedata_flags = false;
		bool function_flags = false;
		bool thesis_flags = false;
		bool ident_flags = false;
		bool declare_flags = false;
		bool static_fun_flags = false;
		bool kavichka_flag = false;
		bool main_flag = false;
	};

	void paste(int line, char ch);

	int FindIdentifier(const char* name, const char* scope) {
		// 1. Поиск с префиксом области видимости
		char fullName[512];
		strcpy_s(fullName, sizeof(fullName), scope);
		strcat_s(fullName, sizeof(fullName), name);

		for (int i = 0; i < idtab.size; i++) {
			if (strcmp(idtab.table[i].id, fullName) == 0) {
				return i;
			}
		}

		// 2. Поиск без префикса (для вызовов функций и глобальных переменных)
		for (int i = 0; i < idtab.size; i++) {
			if (strcmp(idtab.table[i].id, name) == 0) {
				return i;
			}
		}

		return -1;
	}


	void processWord(char* bufferWord, int line, int& pr, Flags& flags, int& type, int& countL,
		char* wordFuncName, char* wordFuncParam, int i)
	{
		if (strlen(bufferWord) == 0) return;

		pr++;

		if (keyMy(bufferWord))
		{
			paste(line, LEX_DECLARE);
			flags.declare_flags = true;
		}
		else if (typeInt(bufferWord))
		{
			paste(line, LEX_TYPE);
			flags.typedata_flags = true;
			type = 0;
		}
		else if (typeChar(bufferWord))
		{
			paste(line, LEX_TYPE);
			flags.typedata_flags = true;
			type = 1;
		}
		else if (typeStr(bufferWord))
		{
			paste(line, LEX_TYPE);
			flags.typedata_flags = true;
			type = 2;
		}
		else if (typeBool(bufferWord))
		{
			paste(line, LEX_TYPE);
			flags.typedata_flags = true;
			type = 3;
		}
		else if (keyFunc(bufferWord))
		{
			paste(line, LEX_FUNC);
			flags.function_flags = true;
		}
		else if (keyReturn(bufferWord))
		{
			paste(line, LEX_RETURN);
		}
		else if (keyMain(bufferWord))
		{
			strcpy_s(wordFuncName, 512, bufferWord);
			paste(line, LEX_MAINFUNC);
			flags.main_flag = true;
		}
		else if (keyOut(bufferWord))
		{
			paste(line, LEX_OUT);
		}
		else if (keyCycle(bufferWord))
		{
			paste(line, LEX_CYCLE);
		}
		else if (literalTrue(bufferWord))
		{
			paste(line, LEX_LITERAL);
			char L[10] = "L";
			char l[10];
			IT::Entry buff;
			memset(&buff, 0, sizeof(IT::Entry));
			buff.idxfirstLE = pr;
			_itoa_s(countL, l, sizeof(l), 10);
			strcat_s(L, sizeof(L), l);
			strcpy_s(buff.id, sizeof(buff.id), L);
			buff.iddatatype = IT::BOOL;
			buff.idtype = IT::L;
			buff.value.vbool = true;
			IT::Add(idtab, buff);
			
			lextab.table[lextab.size - 1].idxTI = idtab.size - 1;
			countL++;
		}
		else if (literalFalse(bufferWord))
		{
			paste(line, LEX_LITERAL);
			char L[10] = "L";
			char l[10];
			IT::Entry buff;
			memset(&buff, 0, sizeof(IT::Entry));
			buff.idxfirstLE = pr;
			_itoa_s(countL, l, sizeof(l), 10);
			strcat_s(L, sizeof(L), l);
			strcpy_s(buff.id, sizeof(buff.id), L);
			buff.iddatatype = IT::BOOL;
			buff.idtype = IT::L;
			buff.value.vbool = false;
			IT::Add(idtab, buff);
			
			lextab.table[lextab.size - 1].idxTI = idtab.size - 1;
			countL++;
		}
		else if (literalInteger(bufferWord)) {
			paste(line, LEX_LITERAL);
			char L[10] = "L";
			char l[10];
			IT::Entry buff;
			memset(&buff, 0, sizeof(IT::Entry));
			buff.idxfirstLE = pr;
			itoa(countL, l, sizeof(l));
			strcat_s(L, sizeof(L), l);
			strcpy_s(buff.id, sizeof(buff.id), L);
			buff.iddatatype = IT::INT;
			buff.idtype = IT::L;

			
			if (strlen(bufferWord) > 1 && bufferWord[0] == '0') {
				throw ERROR_THROW_IN(144, line, i);
			}

			buff.value.vint = atoi(bufferWord);

			
			if (buff.value.vint < -128 || buff.value.vint > 127) {
				throw ERROR_THROW_IN(127, line, 0);
			}

			IT::Add(idtab, buff);
			lextab.table[lextab.size - 1].idxTI = idtab.size - 1;
			countL++;
			pr++;
		}

		else if (funcAbs(bufferWord) || funcPow(bufferWord))
		{
			flags.static_fun_flags = true;
			strcpy_s(wordFuncParam, 512, bufferWord);

			
			int existingIdx = FindIdentifier(bufferWord, "");
			if (existingIdx != -1) {
				LT::Entry entry;
				entry.lexema[0] = LEX_ID;
				entry.lexema[1] = '\0';
				entry.sn = line;
				entry.idxTI = existingIdx;
				LT::Add(lextab, entry);
				return;  
			}

			paste(line, LEX_ID);

			
			IT::Entry buff;
			memset(&buff, 0, sizeof(IT::Entry));
			buff.idxfirstLE = pr;
			strcpy_s(buff.id, sizeof(buff.id), bufferWord);
			buff.iddatatype = IT::INT;
			buff.idtype = IT::SF;  
			buff.value.vint = 0;
			IT::Add(idtab, buff);
			lextab.table[lextab.size - 1].idxTI = idtab.size - 1;

			flags.ident_flags = false;
			}

		else if (identif(bufferWord))
		{
			if (strlen(bufferWord) > ID_MAXSIZE) {
				throw ERROR_THROW_IN(124, line, i);
			}

			
			if (keyMy(bufferWord) || typeInt(bufferWord) || typeChar(bufferWord) ||
				typeStr(bufferWord) || typeBool(bufferWord) || keyFunc(bufferWord) ||
				keyReturn(bufferWord) || keyMain(bufferWord) || keyOut(bufferWord) ||
				keyCycle(bufferWord)) {
				throw ERROR_THROW_IN(133, line, i);
			}

			int existingIdx = FindIdentifier(bufferWord, wordFuncName);

			flags.ident_flags = true;

			
			if (existingIdx != -1) {
				LT::Entry entry;
				entry.lexema[0] = LEX_ID;
				entry.lexema[1] = '\0';
				entry.sn = line;
				entry.idxTI = existingIdx;
				LT::Add(lextab, entry);
				flags.ident_flags = false;
				return;
			}

			bool isDeclarationContext = (flags.function_flags || flags.static_fun_flags ||
				flags.typedata_flags || flags.declare_flags);

			if (!isDeclarationContext) {
				
				
				throw ERROR_THROW_IN(710, line, 0);
			}

			
			paste(line, LEX_ID);

			if (flags.function_flags && !flags.thesis_flags &&
				!funcAbs(bufferWord) && !funcPow(bufferWord))
			{
				strcpy_s(wordFuncParam, 512, bufferWord);
				strcpy_s(wordFuncName, 512, bufferWord);
			}
			}

		else
		{
			throw ERROR_THROW_IN(113, line, i);
		}

		
		if (flags.function_flags && !flags.static_fun_flags &&
			!flags.thesis_flags && flags.ident_flags)
		{
			IT::Entry buff;
			memset(&buff, 0, sizeof(IT::Entry));
			buff.idxfirstLE = pr;
			strcpy_s(buff.id, sizeof(buff.id), bufferWord);

			switch (type)
			{
			case 0: buff.iddatatype = IT::INT; break;
			case 1: buff.iddatatype = IT::CH; break;
			case 2: buff.iddatatype = IT::STR; break;
			case 3: buff.iddatatype = IT::BOOL; break;
			}

			buff.idtype = IT::F;
			buff.value.vint = 0;
			IT::Add(idtab, buff);
			
			lextab.table[lextab.size - 1].idxTI = idtab.size - 1;
			flags.ident_flags = false;
			flags.declare_flags = false;
		}

		
		if (flags.static_fun_flags && !flags.thesis_flags)
		{
			int k = 0;
			for (int j = 0; j < idtab.size; j++)
			{
				if (strcmp(idtab.table[j].id, bufferWord) == 0)
				{
					k++;
				}
			}
			if (k == 0)
			{
				IT::Entry buff;
				memset(&buff, 0, sizeof(IT::Entry));
				buff.idxfirstLE = pr;
				strcpy_s(buff.id, sizeof(buff.id), bufferWord);
				buff.iddatatype = IT::INT;
				buff.idtype = IT::SF;  
				buff.value.vint = 0;
				IT::Add(idtab, buff);
				lextab.table[lextab.size - 1].idxTI = idtab.size - 1;
			}
			else
			{
				
				for (int j = 0; j < idtab.size; j++)
				{
					if (strcmp(idtab.table[j].id, bufferWord) == 0)
					{
						lextab.table[lextab.size - 1].idxTI = j;
						break;
					}
				}
			}
			flags.ident_flags = false;
		}

		
		if (flags.ident_flags && (flags.function_flags || flags.static_fun_flags) &&
			flags.thesis_flags && flags.typedata_flags)
		{
			IT::Entry buff;
			memset(&buff, 0, sizeof(IT::Entry));
			buff.idxfirstLE = pr;
			char w[512];

			if (strlen(wordFuncName) + strlen(bufferWord) >= 512)
			{
				throw ERROR_THROW_IN(114, line, i);
			}

			strcpy_s(w, sizeof(w), wordFuncName);
			strcat_s(w, sizeof(w), bufferWord);
			strcpy_s(buff.id, sizeof(buff.id), w);

			switch (type)
			{
			case 0: buff.iddatatype = IT::INT; break;
			case 1: buff.iddatatype = IT::CH; break;
			case 2: buff.iddatatype = IT::STR; break;
			case 3: buff.iddatatype = IT::BOOL; break;
			}

			buff.idtype = IT::P;
			buff.value.vint = 0;
			
			IT::Add(idtab, buff);
			lextab.table[lextab.size - 1].idxTI = idtab.size - 1;
			flags.ident_flags = false;
			flags.typedata_flags = false;
			flags.declare_flags = false;  
		}

		
		if (flags.ident_flags && !flags.function_flags &&
			!flags.static_fun_flags && flags.typedata_flags)
		{
			IT::Entry buff;
			memset(&buff, 0, sizeof(IT::Entry));
			buff.idxfirstLE = pr;
			char w[512];

			if (strlen(wordFuncName) + strlen(bufferWord) >= 512)
			{
				throw ERROR_THROW_IN(114, line, i);
			}

			strcpy_s(w, sizeof(w), wordFuncName);
			strcat_s(w, sizeof(w), bufferWord);
			strcpy_s(buff.id, sizeof(buff.id), w);

			switch (type)
			{
			case 0: buff.iddatatype = IT::INT; break;
			case 1: buff.iddatatype = IT::CH; break;
			case 2: buff.iddatatype = IT::STR; break;
			case 3: buff.iddatatype = IT::BOOL; break;
			}

			buff.idtype = IT::V;
			buff.value.vint = 0;
			IT::Add(idtab, buff);
			
			lextab.table[lextab.size - 1].idxTI = idtab.size - 1;
			flags.ident_flags = false;
			flags.typedata_flags = false;
			flags.declare_flags = false;
		}

		flags.ident_flags = false;
	}

	LEX LA(Parm::PARM parm, In::IN in)
	{
		Flags flags;
		char symbol;
		int line = 0;
		char wordFuncParam[512] = "";
		char wordFuncName[512] = "";
		char bufferWord[512] = "";
		int k = 0;
		int countL = 0;
		int type = 0;
		int pr = 0;

		
		char prevLexema = '\0';
		for (int i = 0; i < in.size; i++)
		{
			symbol = in.text[i];

			if (symbol == '\n')
			{
				
				if (k > 0 && !flags.kavichka_flag)
				{
					bufferWord[k] = '\0';
					processWord(bufferWord, line, pr, flags, type, countL, wordFuncName, wordFuncParam, i);
					memset(bufferWord, '\0', sizeof(bufferWord));
					k = 0;
				}
				line++;
				continue;
			}

			if ((symbol == ' ' || symbol == '\t') && !flags.kavichka_flag)
			{
				if (k > 0)
				{
					bufferWord[k] = '\0';
					processWord(bufferWord, line, pr, flags, type, countL, wordFuncName, wordFuncParam, i);
					memset(bufferWord, '\0', sizeof(bufferWord));
					k = 0;
				}
				continue;
			}

			if (symbol == '\'' || symbol == '\"')
			{
				if (!flags.kavichka_flag)
				{
					// *** ИСПРАВЛЕНИЕ: сначала обработать накопленное слово ***
					if (k > 0)
					{
						bufferWord[k] = '\0';
						processWord(bufferWord, line, pr, flags, type, countL, wordFuncName, wordFuncParam, i);
						memset(bufferWord, '\0', sizeof(bufferWord));
						k = 0;
					}

					flags.kavichka_flag = true;
					bufferWord[k++] = symbol;  // Теперь начинаем новый буфер с кавычки
				}
				else
				{
					bufferWord[k++] = symbol;
					bufferWord[k] = '\0';
					flags.kavichka_flag = false;

					if (bufferWord[0] == '\'')
					{
						
						if (k == 2)
						{
							throw ERROR_THROW_IN(139, line, i);
						}

						if (k != 3)
						{
							throw ERROR_THROW_IN(123, line, i);
						}

						paste(line, LEX_LITERAL);
						char L[10] = "L";
						char l[10];
						IT::Entry buff;
						memset(&buff, 0, sizeof(IT::Entry));
						buff.idxfirstLE = pr;
						_itoa_s(countL, l, sizeof(l), 10);
						strcat_s(L, sizeof(L), l);
						strcpy_s(buff.id, sizeof(buff.id), L);
						buff.iddatatype = IT::CH;
						buff.idtype = IT::L;
						buff.value.vchar = bufferWord[1];
						IT::Add(idtab, buff);
						lextab.table[lextab.size - 1].idxTI = idtab.size - 1;
						countL++;
						pr++;
					}
					else
					{
						
						if (k == 2)
						{
							throw ERROR_THROW_IN(138, line, i);
						}

						if (k - 2 > TI_STR_MAXSIZE)
						{
							throw ERROR_THROW_IN(124, line, i);
						}

						paste(line, LEX_LITERAL);
						char L[10] = "L";
						char l[10];
						IT::Entry buff;
						memset(&buff, 0, sizeof(IT::Entry));
						buff.idxfirstLE = pr;
						_itoa_s(countL, l, sizeof(l), 10);
						strcat_s(L, sizeof(L), l);
						strcpy_s(buff.id, sizeof(buff.id), L);
						buff.iddatatype = IT::STR;
						buff.idtype = IT::L;
						buff.value.vstr.len = k - 2;

						for (int j = 1; j < k - 1; j++)
						{
							buff.value.vstr.str[j - 1] = bufferWord[j];
						}
						buff.value.vstr.str[k - 2] = '\0';

						IT::Add(idtab, buff);
						lextab.table[lextab.size - 1].idxTI = idtab.size - 1;
						countL++;
						pr++;
					}

					memset(bufferWord, '\0', sizeof(bufferWord));
					k = 0;
				}
				continue;
			}


			if (flags.kavichka_flag)
			{
				bufferWord[k++] = symbol;
				continue;
			}


			if (!flags.kavichka_flag && i + 1 < in.size && symbol == '=' && in.text[i + 1] == '=')
			{
				if (k > 0)
				{
					bufferWord[k] = '\0';
					processWord(bufferWord, line, pr, flags, type, countL, wordFuncName, wordFuncParam, i);
					memset(bufferWord, '\0', sizeof(bufferWord));
					k = 0;
				}

				LT::Entry entry;
				entry.lexema[0] = LEX_COMPARISON;
				entry.lexema[1] = '=';
				entry.lexema[2] = '\0';
				entry.sn = line;
				entry.idxTI = LT_TI_NULLIDX;
				LT::Add(lextab, entry);
				i++;
				pr++;
				continue;
			}

			if (!flags.kavichka_flag && i + 1 < in.size && symbol == '!' && in.text[i + 1] == '=')
			{
				if (k > 0)
				{
					bufferWord[k] = '\0';
					processWord(bufferWord, line, pr, flags, type, countL, wordFuncName, wordFuncParam, i);
					memset(bufferWord, '\0', sizeof(bufferWord));
					k = 0;
				}

				LT::Entry entry;
				entry.lexema[0] = LEX_COMPARISON;
				entry.lexema[1] = '!';
				entry.lexema[2] = '\0';
				entry.sn = line;
				entry.idxTI = LT_TI_NULLIDX;
				LT::Add(lextab, entry);
				i++;
				pr++;
				continue;
			}

			if (!flags.kavichka_flag && i + 2 < in.size &&
				symbol == '.' && in.text[i + 1] == '.' && in.text[i + 2] == '.')
			{
				if (k > 0)
				{
					bufferWord[k] = '\0';
					processWord(bufferWord, line, pr, flags, type, countL, wordFuncName, wordFuncParam, i);
					memset(bufferWord, '\0', sizeof(bufferWord));
					k = 0;
				}

				LT::Entry entry;
				entry.lexema[0] = LEX_THREEPTS;
				entry.lexema[1] = '\0';
				entry.sn = line;
				entry.idxTI = LT_TI_NULLIDX;
				LT::Add(lextab, entry);

				i += 2;
				pr++;
				continue;
			}

			if (symbol == '(' || symbol == ')' || symbol == '{' || symbol == '}' ||
				symbol == ';' || symbol == ',' || symbol == '=' || symbol == '+' ||
				symbol == '-' || symbol == '*' || symbol == '&' || symbol == '|' ||
				symbol == '~' || symbol == '>' || symbol == '<' || symbol == '/')
			{
				if (k > 0)
				{
					bufferWord[k] = '\0';
					processWord(bufferWord, line, pr, flags, type, countL, wordFuncName, wordFuncParam, i);
					memset(bufferWord, '\0', sizeof(bufferWord));
					k = 0;
				}

				char nextSymbol = (i + 1 < in.size) ? in.text[i + 1] : '\0';

				if (symbol == '=' && nextSymbol == '=')
				{
					LT::Entry entry;
					entry.lexema[0] = LEX_COMPARISON;
					entry.lexema[1] = '=';
					entry.lexema[2] = '=';
					entry.lexema[3] = '\0';
					entry.sn = line;
					entry.idxTI = LT_TI_NULLIDX;
					LT::Add(lextab, entry);
					pr++;
					i++;
					continue;
				}
				else if (symbol == '!' && nextSymbol == '=')
				{
					LT::Entry entry;
					entry.lexema[0] = LEX_COMPARISON;
					entry.lexema[1] = '!';
					entry.lexema[2] = '=';
					entry.lexema[3] = '\0';
					entry.sn = line;
					entry.idxTI = LT_TI_NULLIDX;
					LT::Add(lextab, entry);
					pr++;
					i++;
					continue;
				}
				else if (symbol == '<' && nextSymbol == '=')
				{
					LT::Entry entry;
					entry.lexema[0] = LEX_COMPARISON;
					entry.lexema[1] = '<';
					entry.lexema[2] = '=';
					entry.lexema[3] = '\0';
					entry.sn = line;
					entry.idxTI = LT_TI_NULLIDX;
					LT::Add(lextab, entry);
					pr++;
					i++;
					continue;
				}
				else if (symbol == '>' && nextSymbol == '=')
				{
					LT::Entry entry;
					entry.lexema[0] = LEX_COMPARISON;
					entry.lexema[1] = '>';
					entry.lexema[2] = '=';
					entry.lexema[3] = '\0';
					entry.sn = line;
					entry.idxTI = LT_TI_NULLIDX;
					LT::Add(lextab, entry);
					pr++;
					i++;
					continue;
				}

				if (symbol == '(')
				{
					paste(line, LEX_LEFTTHESIS);
					flags.thesis_flags = true;
				}
				else if (symbol == ')')
				{
					paste(line, LEX_RIGHTTHESIS);
					flags.thesis_flags = false;
					flags.static_fun_flags = false;
					flags.function_flags = false;
					strcpy_s(wordFuncParam, "");
				}
				else if (symbol == '{')
				{
					paste(line, LEX_LEFTBRACE);
				}
				else if (symbol == '}')
				{
					
					paste(line, LEX_RIGHTBRACE);
				}
				else if (symbol == ';')
				{
					paste(line, LEX_SEMICOLON);
				}
				else if (symbol == ',')
				{
					paste(line, LEX_COMMA);
				}
				else if (symbol == '=')
				{
					paste(line, LEX_EQUAL);
				}
				else if (symbol == '+' || symbol == '-' || symbol == '*' ||
					symbol == '&' || symbol == '|')
				{
					LT::Entry entry;
					entry.lexema[0] = LEX_OPERATION;
					entry.lexema[1] = symbol;
					entry.lexema[2] = '\0';
					entry.sn = line;
					entry.idxTI = LT_TI_NULLIDX;
					LT::Add(lextab, entry);
				}
				else if (symbol == '~')
				{
					paste(line, LEX_TILDE);
				}
				else if (symbol == '>' || symbol == '<')
				{
					LT::Entry entry;
					entry.lexema[0] = LEX_COMPARISON;
					entry.lexema[1] = symbol;
					entry.lexema[2] = '\0';
					entry.sn = line;
					entry.idxTI = LT_TI_NULLIDX;
					LT::Add(lextab, entry);
				}

				pr++;
				continue;
			}

			bufferWord[k++] = symbol;
		}

		if (k > 0)
		{
			bufferWord[k] = '\0';
			processWord(bufferWord, line, pr, flags, type, countL, wordFuncName, wordFuncParam, in.size - 1);
		}
		if (flags.kavichka_flag)
		{
			throw ERROR_THROW_IN(137, line, in.size - 1);
		}
		
		LEX tables;
		tables.idTable = idtab;
		tables.lexTable = lextab;

		return tables;
	}


	void paste(int line, char ch)
	{
		LT::Entry entry;
		std::memset(entry.lexema, '\0', sizeof(char) * 2);
		entry.lexema[0] = ch;
		entry.lexema[1] = '\0';
		entry.sn = line;

		if (ch != LEX_ID)
		{
			entry.idxTI = LT_TI_NULLIDX;
		}
		else
		{
			entry.idxTI = idtab.size;
		}

		LT::Add(lextab, entry);
	}

	void PrintTables(Log::LOG log, IT::IdTable& idtab, LT::LexTable& lextab)
	{
		
		*log.stream << "\n====== ТАБЛИЦА ИДЕНТИФИКАТОРОВ ======\n";
		*log.stream << "------------------------------------------------------------------------------\n";
		*log.stream << std::setw(4) << "#" << " | ";
		*log.stream << std::setw(15) << "Имя" << " | ";
		*log.stream << std::setw(10) << "Тип данных" << " | ";
		*log.stream << std::setw(12) << "Тип ID" << " | ";
		*log.stream << std::setw(6) << "Строка" << " | ";
		*log.stream << std::setw(12) << "Значение" << "\n";
		*log.stream << "------------------------------------------------------------------------------\n";

		for (int i = 0; i < idtab.size; i++) {
			*log.stream << std::setw(4) << std::setfill('0') << i << std::setfill(' ') << " | ";
			*log.stream << std::setw(15) << std::left << idtab.table[i].id << std::right << " | ";

			switch (idtab.table[i].iddatatype) {
			case IT::INT: *log.stream << std::setw(10) << "int"; break;
			case IT::CH: *log.stream << std::setw(10) << "char"; break;
			case IT::STR: *log.stream << std::setw(10) << "str"; break;
			case IT::BOOL: *log.stream << std::setw(10) << "bool"; break;
			}
			*log.stream << " | ";

			switch (idtab.table[i].idtype) {
			case IT::F: *log.stream << std::setw(12) << "функция"; break;
			case IT::P: *log.stream << std::setw(12) << "параметр"; break;
			case IT::L: *log.stream << std::setw(12) << "литерал"; break;
			case IT::V: *log.stream << std::setw(12) << "переменная"; break;
			case IT::SF: *log.stream << std::setw(12) << "ст.функ."; break;
			}
			*log.stream << " | ";
			*log.stream << std::setw(6) << idtab.table[i].idxfirstLE << " | ";

			*log.stream << std::setw(12) << std::left;
			switch (idtab.table[i].iddatatype) {
			case IT::INT: *log.stream << idtab.table[i].value.vint; break;
			case IT::CH: *log.stream << idtab.table[i].value.vchar; break;
			case IT::BOOL: *log.stream << (idtab.table[i].value.vbool ? "true" : "false"); break;
			case IT::STR: *log.stream << idtab.table[i].value.vstr.str; break;
			}
			*log.stream << std::right << "\n";
		}
		*log.stream << "------------------------------------------------------------------------------\n\n";

		
		*log.stream << "====== ТАБЛИЦА ЛЕКСЕМ ======\n";
		*log.stream << "-------------------------------------------------------\n";
		*log.stream << std::setw(4) << "#" << " | ";
		*log.stream << std::setw(15) << "Лексема" << " | ";
		*log.stream << std::setw(10) << "Строка" << " | ";
		*log.stream << std::setw(12) << "Индекс в ТИ" << "\n";
		*log.stream << "-------------------------------------------------------\n";

		for (int i = 0; i < lextab.size; i++) {
			*log.stream << std::setw(4) << std::setfill('0') << i << std::setfill(' ') << " | ";

			
			*log.stream << std::setw(15) << std::left << lextab.table[i].lexema[0];
			*log.stream << std::right << " | ";

			
			*log.stream << std::setw(10) << lextab.table[i].sn << " | ";

			
			if (lextab.table[i].idxTI == LT_TI_NULLIDX) {
				*log.stream << std::setw(12) << "-";
			}
			else {
				*log.stream << std::setw(12) << lextab.table[i].idxTI;
			}
			*log.stream << "\n";
		}
		*log.stream << "-------------------------------------------------------\n\n";

		
		*log.stream << "====== ОБРАБОТАННАЯ СТРОКА ======\n";
		int current_line = -1;
		for (int i = 0; i < lextab.size; i++) {
			if (current_line != lextab.table[i].sn) {
				if (current_line != -1) {
					*log.stream << "\n";
				}
				current_line = lextab.table[i].sn;
				*log.stream << std::setw(3) << std::setfill('0') << current_line << std::setfill(' ') << ": ";
			}
			*log.stream << lextab.table[i].lexema[0];
		}
		*log.stream << "\n\n";
	}



}
