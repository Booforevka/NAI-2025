#include "stdafx.h"
#include "GRB.h"

namespace GRB
{
    Rule::Chain::Chain(short psize, GRBALPHABET s, ...)
    {
        size = psize;
        nt = new GRBALPHABET[size];

        int* p = (int*)&s;
        for (int i = 0; i < psize; i++)
        {
            nt[i] = (GRBALPHABET)p[i];
        }
    }

    char* Rule::Chain::getCChain(char* b)
    {
        for (int i = 0; i < size; i++)
        {
            b[i] = GRB::Rule::Chain::alphabet_to_char(nt[i]);
        }
        b[size] = '\0';
        return b;
    }

    Rule::Rule(GRBALPHABET pnn, int iderror, short psize, Chain c, ...)
    {
        nn = pnn;
        this->iderror = iderror;
        size = psize;
        chains = new Chain[size];

        Chain* p = &c;
        for (int i = 0; i < size; i++)
        {
            chains[i] = p[i];
        }
    }

    char* Rule::getCRule(char* b, short nchain)
    {
        char buf[200];
        b[0] = GRB::Rule::Chain::alphabet_to_char(nn);
        b[1] = '-';
        b[2] = '>';
        b[3] = '\0';
        chains[nchain].getCChain(buf);
        strcat_s(b, sizeof(buf) + 5, buf);
        return b;
    }

    short Rule::getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j)
    {
        short rc = -1;
        while (j < size && chains[j].nt[0] != t)
        {
            j++;
        }

        if (j < size)
        {
            rc = j;
            pchain = chains[rc];
        }

        return rc;
    }

    Greibach::Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottomT, short psize, Rule r, ...)
    {
        startN = pstartN;
        stbottomT = pstbottomT;
        size = psize;
        rules = new Rule[size];

        Rule* p = &r;
        for (int i = 0; i < size; i++)
        {
            rules[i] = p[i];
        }
    }

    short Greibach::getRule(GRBALPHABET pnn, Rule& prule)
    {
        short rc = -1;
        short i = 0;

        while (i < size && rules[i].nn != pnn)
        {
            i++;
        }

        if (i < size)
        {
            prule = rules[i];
            rc = i;
        }

        return rc;
    }

    Rule Greibach::getRule(short n)
    {
        Rule rc;
        if (n < size)
        {
            rc = rules[n];
        }
        return rc;
    }

    Greibach greibach(
        NS('S'),
        TS('$'),
        5,  

        
        Rule(NS('S'), GRB_ERROR_SERIES + 0,
            3,
            Rule::Chain(4, TS('m'), TS('{'), NS('N'), TS('}')),
            Rule::Chain(9, TS('t'), TS('f'), TS('i'), TS('('), TS(')'), TS('{'), NS('N'), TS('}'), NS('S')),            
            Rule::Chain(10, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('}'), NS('S'))   
        ),

        // Правило N: тело функции/блока
        Rule(NS('N'), GRB_ERROR_SERIES + 1,
            21,
            Rule::Chain(4, TS('d'), TS('t'), TS('i'), TS(';')),
            Rule::Chain(5, TS('d'), TS('t'), TS('i'), TS(';'), NS('N')),
            Rule::Chain(6, TS('d'), TS('t'), TS('i'), TS('='), NS('E'), TS(';')),
            Rule::Chain(7, TS('d'), TS('t'), TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
            Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
            Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
            Rule::Chain(3, TS('r'), NS('E'), TS(';')),
            Rule::Chain(4, TS('r'), NS('E'), TS(';'), NS('N')),
            Rule::Chain(3, TS('o'), NS('E'), TS(';')),
            Rule::Chain(4, TS('o'), NS('E'), TS(';'), NS('N')),
            Rule::Chain(7, TS('c'), TS('l'), TS('.'), TS('l'), TS('{'), NS('N'), TS('}')),
            Rule::Chain(8, TS('c'), TS('l'), TS('.'), TS('l'), TS('{'), NS('N'), TS('}'), NS('N')),
            Rule::Chain(7, TS('c'), TS('l'), TS('.'), TS('i'), TS('{'), NS('N'), TS('}')),
            Rule::Chain(8, TS('c'), TS('l'), TS('.'), TS('i'), TS('{'), NS('N'), TS('}'), NS('N')),
            Rule::Chain(7, TS('c'), TS('i'), TS('.'), TS('l'), TS('{'), NS('N'), TS('}')),
            Rule::Chain(8, TS('c'), TS('i'), TS('.'), TS('l'), TS('{'), NS('N'), TS('}'), NS('N')),
            Rule::Chain(7, TS('c'), TS('i'), TS('.'), TS('i'), TS('{'), NS('N'), TS('}')),
            Rule::Chain(8, TS('c'), TS('i'), TS('.'), TS('i'), TS('{'), NS('N'), TS('}'), NS('N')),
            Rule::Chain(3, TS('i'), TS(';'), NS('N')),  
            Rule::Chain(3, TS('o'), TS(';'), NS('N')),  
            Rule::Chain(1, NS('E'))
        ),

        
        Rule(NS('E'), GRB_ERROR_SERIES + 2,
            16,
            Rule::Chain(1, TS('i')),                         
            Rule::Chain(1, TS('l')),                         
            Rule::Chain(3, TS('i'), TS('b'), TS('i')),       
            Rule::Chain(3, TS('i'), TS('b'), TS('l')),       
            Rule::Chain(3, TS('l'), TS('b'), TS('i')),       
            Rule::Chain(3, TS('l'), TS('b'), TS('l')),       
            Rule::Chain(3, TS('i'), TS('v'), TS('i')),       
            Rule::Chain(3, TS('i'), TS('v'), TS('l')),       
            Rule::Chain(3, TS('l'), TS('v'), TS('i')),       
            Rule::Chain(3, TS('l'), TS('v'), TS('l')),       
            Rule::Chain(2, TS('~'), TS('i')),                
            Rule::Chain(2, TS('~'), TS('l')),                
            Rule::Chain(2, TS('v'), TS('l')),                 
            Rule::Chain(2, TS('v'), TS('i')),                 
            Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')), 
            Rule::Chain(3, TS('i'), TS('('), TS(')'))         
        ),


        
        Rule(NS('W'), GRB_ERROR_SERIES + 3,
            6,
            Rule::Chain(1, TS('i')),
            Rule::Chain(1, TS('l')),
            Rule::Chain(3, TS('i'), TS(','), NS('W')),
            Rule::Chain(3, TS('l'), TS(','), NS('W')),
            Rule::Chain(2, TS('v'), TS('l')),     
            Rule::Chain(2, TS('v'), TS('i'))
        ),

        // Правило F: параметры объявления функции
        Rule(NS('F'), GRB_ERROR_SERIES + 4,
            2,
            Rule::Chain(2, TS('t'), TS('i')),
            Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F'))
        )
    );

    Greibach getGreibach()
    {
        
        return greibach;
    }

}