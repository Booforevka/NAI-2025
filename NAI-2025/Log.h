#pragma once
#include "stdafx.h"

namespace Log     
{
	struct LOG		
	{
		wchar_t logfile[PARM_MAX_SIZE]; 
		std::ofstream* stream;			
	};

	static const LOG INITLOG{ L"", NULL }; 
	LOG getlog(wchar_t logfile[]); 
	void WriteForbidden(LOG log, In::IN in);		
	void WriteLine(LOG log, char* c, ...); 
	void WriteLine(LOG log, wchar_t* c, ...); 
	void WriteLog(LOG log); // вывести в протокол заголовок
	void WriteParm(LOG log, Parm::PARM parm); // вывести в протокол информацию о входных параметрах
	void WriteIn(LOG log, In::IN in); // вывести в протокол информацикю о входном потоке
	void WriteError(LOG log, Error::ERROR error); //вывести в протокол информацию об ошибке 
	void Close(LOG log);
}