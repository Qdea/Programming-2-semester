#include "Cross.h"
#include "Cubic.h"
using namespace cross;

void Cross::solveCross(Cubic& cube) {
    int i = 0;
    while (checkCross(cube)) {
        solveEdge(cube);
        i++;
        if (i > 100)
            throw -4;
    }
}

int Cross::checkCross(Cubic& cube) {
    return (!cube.cubies[1][0] && !cube.cubies[3][0] && !cube.cubies[5][0] && !cube.cubies[7][0] && cube.cubies[7][2] == 2 
        && cube.cubies[7][3] == 3 && cube.cubies[7][4] == 4 && cube.cubies[7][5] == 5) ? 0 : 1;
}

void Cross::solveEdge(Cubic& cube) {
    for (int side = 0; side < 6; ++side)
        for (int edge = 1; edge < 9; edge += 2)
            if (cube.cubies[edge][side] == 0)
                if (side) {
                    int a = side - 1;
                    int b = (edge - 1) / 2;
                    int c = idx[a][b][0];
                    int d = idx[a][b][1];
                    int e = cube.cubies[c][d] - 2;
                    cube.moves(moves[a][b][e]);
                }
                else {
                    int a = (edge - 1) / 2;
                    int b0 = idx0[a][0][0];
                    int b1 = idx0[a][0][1];
                    int c0 = idx0[a][1][0];
                    int c1 = idx0[a][1][1];
                    int d0 = idx0[a][2][0];
                    int d1 = idx0[a][2][1];
                    if (cube.cubies[b0][b1] != b1) {
                        while (cube.cubies[c0][c1] == 0 || cube.cubies[d0][d1] == 0)
                            cube.moves("U");
                        cube.moves(moves0[a]);
                    }
                }
}
