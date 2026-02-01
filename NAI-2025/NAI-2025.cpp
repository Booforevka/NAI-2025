#include "stdafx.h"

int wmain(int argc, wchar_t* argv[])
{
    setlocale(LC_ALL, "rus");
    Log::LOG log = Log::INITLOG;
    Parm::PARM parm;
    Out::OUT out = Out::INITOUT;
    In::IN in;

    try
    {
        parm = Parm::getparm(argc, argv);
        in = In::getin(parm.in);


        out = Out::getout(parm.out);
        log = Log::getlog(parm.log);

        cout << "====== ЛЕКСИЧЕСКИЙ АНАЛИЗ ======" << endl;
        LA::LEX lexTables = LA::LA(parm, in);
        LA::PrintTables(log, lexTables.idTable, lexTables.lexTable);
        cout << "Лексический анализ завершен!" << endl;

        cout << "====== СИНТАКСИЧЕСКИЙ АНАЛИЗ ======" << endl;
        MFST::Mfst mfst(lexTables.lexTable, GRB::getGreibach());

        
        bool syntaxSuccess = mfst.start(log);

        if (!syntaxSuccess)
        {
            
            cout << "\n====== ТРАНСЛЯЦИЯ ПРЕРВАНА ИЗ-ЗА СИНТАКСИЧЕСКИХ ОШИБОК ======" << endl;
            Log::WriteLine(log, (char*)"\n====== ТРАНСЛЯЦИЯ ПРЕРВАНА ======\n");
            Log::Close(log);
            Out::CloseOut(out);
            
            return -1; 
        }
        mfst.printrules(log);
        cout << "Синтаксический анализ завершен успешно!" << endl;


       
        PN::startPolish(lexTables, log);
        cout << "====== СЕМАНТИЧЕСКИЙ АНАЛИЗ ======" << endl;
        SA::startSA(lexTables);

        cout << "====== ГЕНЕРАЦИЯ КОДА ======" << endl;
        CodeGeneration::GenerateCode(lexTables, out);

        cout << "\n=== ТРАНСЛЯЦИЯ ЗАВЕРШЕНА! ===" << endl;
        Log::Close(log);
        Out::CloseOut(out);
    }
    catch (Error::ERROR e)
    {
        if (e.inext.col == 0)
        {
            cout << "Ошибка " << e.id << " строка " << e.inext.line + 1 << ": " << e.message << endl;
        }
        else if (e.inext.line == 0)
        {
            cout << "Ошибка " << e.id;
        }
        else
        {
        cout << "Ошибка " << e.id <<" строка " << e.inext.line + 1 <<" позиция " << e.inext.col << ": " << e.message << endl;
        }
        if (log.stream) Log::Close(log);
        if (out.stream) Out::CloseOut(out);
        system("pause");
        return -1;
    }

    system("pause");
    return 0;
}