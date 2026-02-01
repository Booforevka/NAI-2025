#include "stdafx.h"
#include "Log.h"
#include "Error.h"

namespace Log {

	LOG getlog(wchar_t logfile[]) {

		LOG log;

		log.stream = new ofstream;
		log.stream->open(logfile);

		if (!log.stream->is_open()) {
			throw 
				(112);
		}

		wcscpy_s(log.logfile, logfile);
		return log;
	}

	void WriteLine(LOG log, char* c, ...) {

		string result;
		const char* str = c;
		va_list args;
		va_start(args, c);

		while (str && str[0] != '\0') {
			result += str;
			str = va_arg(args, const char*);
		}

		va_end(args);

		*(log.stream) << result << std::endl;
	}

	void WriteLine(LOG log, wchar_t* c, ...) {

		std::wstring result;
		const wchar_t* wstr = c;

		va_list args;
		va_start(args, c);

		while (wstr && wstr[0] != L'\0') {
			result += wstr;
			wstr = va_arg(args, const wchar_t*);
		}

		va_end(args);

		size_t len = 0;
		wcstombs_s(&len, nullptr, 0, result.c_str(), result.length() + 1);
		if (len == 0) return;
		char* cstr = new char[len];
		size_t converted = 0;
		wcstombs_s(&converted, cstr, len, result.c_str(), _TRUNCATE);

		*(log.stream) << cstr << std::endl;

		delete[] cstr;  
	}

	void WriteLog(LOG log) {

		time_t t = time(nullptr);
		tm localTime;
		localtime_s(&localTime, &t);
		char timeStr[PARM_MAX_SIZE];
		strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", &localTime);
		*(log.stream) << "---- Протокол ------ " << timeStr << "-------------" << endl;
	}

	void WriteParm(LOG log, Parm::PARM parm) {
		char buff[PARM_MAX_SIZE];
		size_t tsize = 0;
		*log.stream << "----Параметры----" << endl;
		wcstombs_s(&tsize, buff, parm.log, PARM_MAX_SIZE);  
		*log.stream << "-log: " << buff << endl;
		wcstombs_s(&tsize, buff, parm.out, PARM_MAX_SIZE);  
		*log.stream << "-out: " << buff << endl;
		wcstombs_s(&tsize, buff, parm.in, PARM_MAX_SIZE); 
		*log.stream << "-in: " << buff << endl;
	}

	void WriteIn(LOG log, In::IN in) {
		*log.stream << "---- Исходные данные " << endl;
		*log.stream << "Количество символов: " << in.size << endl;
		*log.stream << "Проигнорировано: " << in.ignore << endl;
		*log.stream << "Количество строк: " << in.lines << endl;
	}

	void WriteError(LOG log, Error::ERROR error) {
		if (log.stream) {
			*log.stream << " ----	Ошибка	---- " << endl;
			*log.stream << "Ошибка " << error.id << ": " << error.message << endl;
			if (error.inext.line != -1)
			{
				*log.stream << "Строка: " << error.inext.line << endl << "Столбец: " << error.inext.col << endl << endl;
			}
		}
		else {
			cout << "Ошибка " << error.id << ": " << error.message << ", строка" << error.inext.line << ", позиция" << error.inext.col << endl;
		}
	}

	void WriteForbidden(LOG log, In::IN in) {
		if (in.error_size) {
			*log.stream << "Запрещенные символы символы заменены символом '^'" << endl;
			for (int i = 0; i < in.error_size; i++) {
				*log.stream << "запрещенный символ '" << in.forbiddenChar[i] << "' на строке " << in.errorLine[i] << " на позиции " << in.errorCol[i] << endl;
			}
		}
	}

	void Close(LOG log) {
		log.stream->close();
		delete log.stream;
	}
}