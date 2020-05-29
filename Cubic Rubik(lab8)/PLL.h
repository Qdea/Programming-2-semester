#pragma once
#include "Cubic.h"

class PLL
{
public:
    static void solvePLL(Cubic&);
private:
    static void adjustUFace(Cubic&);
    static void solveCorners(Cubic&);
    static int checkCorners(Cubic&);
    static int checkEdges(Cubic&);
    static void solveEdges(Cubic&);
};
