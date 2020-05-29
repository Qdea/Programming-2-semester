#pragma once
#include "Cubic.h"

class Edges
{
public:
    static void solveEdges(Cubic& cube);
private:
    static void solveEdge(Cubic& cube);
    static int checkEdges(Cubic& cube);
};
