#include <iostream>

extern "C"
{
	
	int __stdcall nabs(int a) {
		return (a < 0) ? -a : a;
	}

	
	int __stdcall npow(int exponent, int base ) {
		if (exponent == 0) {
			return 1;
		}

		int result = 1;
		int exp = (exponent < 0) ? -exponent : exponent;

		for (int i = 0; i < exp; i++) {
			result *= base;
		}

		if (exponent < 0) {
			return 0;
		}

		return result;
	}

	
	void __stdcall outint(int n) {
		if ( -128 > n|| n > 127)
		{
			std::cout << "Int вышел за диапазон";
		}
		else
		{
		std::cout << n;
		}
	}

	// Функция OUT для вывода строк (str)
	void __stdcall outstr(char* str) {
		std::cout << str;
	}

	// Функция OUT для вывода символов (char)
	void __stdcall outchar(char ch) {
		std::cout << ch;
	}

	// Функция OUT для вывода булевых значений (bool)
	void __stdcall outbool(bool b) {
		if (b) {
			std::cout << "true";
		}
		else {
			std::cout << "false";
		}
	}

	
	void __stdcall outnewline() {
		std::cout << std::endl;
	}
}
