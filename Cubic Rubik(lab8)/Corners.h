#pragma once
#include "Cubic.h"
#include <string>

namespace corners
{
    const int idx[4][6][2] = {
        {{0, 0}, {6, 2}, {8, 5}, {6, 1}, {0, 2}, {2, 5}},
        {{2, 0}, {8, 2}, {6, 3}, {8, 1}, {2, 2}, {0, 3}},
        {{6, 0}, {8, 4}, {6, 5}, {0, 1}, {2, 4}, {0, 5}},
        {{8, 0}, {8, 3}, {6, 4}, {2, 1}, {2, 3}, {0, 4}}
    };
    const std::string moves[4] = { "FUFFF", "RURRR", "LULLL", "BUBBB" };
}

class Corners
{
public:
    static void solveCorners(Cubic&);
private:

    static int checkCorners(Cubic&);
    static int checkBottomLayer(Cubic& cube);
};
