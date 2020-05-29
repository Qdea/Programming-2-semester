#pragma once
#include "Cubic.h"

class OLL
{
public:
    static void solveOLL(Cubic&);
private:
    static int findState(Cubic&);
    static int findEdges(Cubic&);
    static void solveCase(Cubic&, int);
    static int checkOLL(Cubic&);
    static int checkEdges(Cubic&);
};
