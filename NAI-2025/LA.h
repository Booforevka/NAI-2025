#pragma once
#include "IT.h"
#include "LT.h"
#include "In.h"
#include "FST.h"
#include "Error.h"
#include "Parm.h"

namespace LA {

    struct LEX {
        LT::LexTable lexTable;
        IT::IdTable idTable;
    };
    void PrintTables(Log::LOG log, IT::IdTable& idtab, LT::LexTable& lextab);
    LEX LA(Parm::PARM parm, In::IN in);
}
