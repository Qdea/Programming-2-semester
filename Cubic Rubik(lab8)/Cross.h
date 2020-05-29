#pragma once
#include "Cubic.h"
#include <string>

namespace cross {
    const int idx[5][4][2] = {
        {{ 1, 4 }, { 1, 5 }, { 1, 3 }, { 1, 2 }},
        {{ 7, 1 }, { 5, 5 }, { 3, 3 }, { 1, 0 }},
        {{ 5, 1 }, { 5, 2 }, { 3, 4 }, { 5, 0 }},
        {{ 1, 1 }, { 5, 3 }, { 3, 5 }, { 7, 0 }},
        {{ 3, 1 }, { 5, 4 }, { 3, 2 }, { 3, 0 }}
    };
    const std::string moves[5][4][4] = {
        {{"UUFF", "URR", "BB", "UUULL"},{"UUUFF", "UURR", "UBB", "LL"},{"UFF", "RR", "UUUBB", "UULL"},{"FF", "UUURR", "UUBB", "ULL"}},
        {{"UUURRRFR", "FRRRFFF", "UUURBBBRRR", "FFFLF"},{"LDLLL", "UUFUU", "LLLULBB", "L"},{"RRRDDDR", "RRR", "RUUURRRBB", "RUURRRLL"},{"FFFDRRRDDD", "FFFRRR", "FFUUURBBBRRR", "FL"}},
        {{"RRRFR", "UFRRRFFF", "RBBBRRR", "UFFFLF"},{"F", "FFFUUUFRR", "RRBBBRR", "FFFUFLL"},{"RRFRR", "BUBBBRR", "BBB", "RRRUFFFLF"},{"RFRRR", "RRUFRRRFFF", "RRRBBBR", "RRUFFFLF"}},
        {{"URRRFR", "BBBRB", "URBBBRRR", "BLLLBBB"},{"RRRURFF", "R", "RRRUUURBB", "RRRUURLL"},{"LUUULLLFF", "LUULLLRR", "LULLLBB", "LLL"},{"BBURRRFR", "BRBBB", "BBURBBBRRR", "BBBLLLB"}},
        {{"LFLLL", "UUUFRRRFFF", "LLLBL", "UUUFFFLF"},{"LLFFFLL", "LUUUFRRRFFF", "B", "LUUUFFFLF"},{"FFF", "FUUUFFFRR", "FUUFFFBB", "FUFFFLL"},{"LLLFFFL", "LLUFRRRFFF", "LBLLL", "LLUFFFLF"}}
    };
    const int idx0[4][3][2] = { {{7, 2}, {1, 2}, {7, 1}}, {{7, 5}, {1, 5}, {3, 1}}, {{7, 3}, {1, 3}, {5, 1}}, {{7, 4}, {1, 3}, {1, 1}} };
    const std::string moves0[4] = { "FF", "LL", "RR", "BB" };
}

class Cross {
private:
    static int checkCross(Cubic&);
    static void solveEdge(Cubic&);
public:
    static void solveCross(Cubic&);
};
