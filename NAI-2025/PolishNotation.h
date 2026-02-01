#pragma once
#include "LA.h"

namespace PN
{
	bool startPolish(LA::LEX& lex, Log::LOG log);
	bool PolishNotation(int lextable_pos, LT::LexTable& lextable, IT::IdTable& idtable);
}
