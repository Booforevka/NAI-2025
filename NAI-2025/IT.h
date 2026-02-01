#pragma once

#define ID_MAXSIZE		30	
#define TI_MAXSIZE		4096
#define TI_INT_DEFAULT	0x00000000	
#define TI_CHAR_DEFAULT	0x00	
#define TI_BOOL_DEFAULT	0x00	
#define TI_STR_DEFAULT	0x00	
#define TI_NULLIDX		0xffffffff	
#define TI_STR_MAXSIZE	255		

namespace IT		
{
	enum IDDATATYPE { INT = 1, STR = 2, CH = 3, BOOL = 4 };	

	enum IDTYPE { V = 1, F = 2, P = 3, L = 4, SF = 5 };		
	// V  - переменная
	// F  - функция
	// P  - параметр функции
	// L  - литерал
	// SF - стандартная функция (abs, pow)

	struct Entry		
	{
		int			idxfirstLE;			
		char		id[ID_MAXSIZE];		
		IDDATATYPE	iddatatype;			
		IDTYPE		idtype;				

		union
{
    int vint;
    struct
    {
        char str[TI_STR_MAXSIZE];  
        int len;
    } vstr;  
    char vchar;
    bool vbool;
} value;
			
	};

	struct IdTable				
	{
		int maxsize;			
		int size;			
		Entry* table;		
	};

	IdTable Create(			
		int size			
	);

	void Add(				
		IdTable& idtable,	
		Entry entry			
	);

	Entry GetEntry(			
		IdTable& idtable,	
		int n				
	);

	int IsId(				
		IdTable& idtable,	
		char id[ID_MAXSIZE]	
	);

	int search(				
		IdTable& idtable,	
		Entry entry	
	);

	void Delete(IdTable& idtable);	
};
