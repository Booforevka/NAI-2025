#pragma once
#include "stdafx.h"
#include "Out.h"
#include "LA.h"
#include <fstream>

namespace CodeGeneration
{
	void GenerateCode(LA::LEX& lex, Out::OUT& out);
	void HeadOut(Out::OUT& out);
	void ConstOut(Out::OUT& out, LA::LEX& lex);
	void DataOut(Out::OUT& out, LA::LEX& lex);
	void CodeOut(Out::OUT& out, LA::LEX& lex);
	void FunctionsOut(Out::OUT& out, LA::LEX& lex);
	void ExpressionHandler(std::ofstream& stream, LA::LEX& lex, int startpos, int endpos);
	void ProcessBlock(Out::OUT& out, LA::LEX& lex, int start, int end, int paramCount = 0);

	bool isReservedWord(const char* id);
	std::string SafeName(const char* id);
	IT::IDDATATYPE GetExpressionType(LA::LEX& lex, int start, int end);
	int FindSemicolon(LA::LEX& lex, int start);
	int FindBlockEnd(LA::LEX& lex, int start);
}
