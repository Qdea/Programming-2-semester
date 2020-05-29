#include "PLL.h"
#include "Cubic.h"
#include <iostream>

void PLL::solvePLL(Cubic& cube) {
    adjustUFace(cube);
    int i = 0;
    while (!checkCorners(cube)) {
        solveCorners(cube);
        adjustUFace(cube);
        i++;
        if (i > 100)
            throw -5;
    }

    i = 0;
    while (!checkEdges(cube)) {
        solveEdges(cube);
        i++;
        if (i > 100)
            throw -6;
    }
}

void PLL::adjustUFace(Cubic& cube) {
    while (cube.cubies[2][5] != 5 || cube.cubies[0][2] != 2) {
        cube.moves("U");
    }
}

void PLL::solveEdges(Cubic& cube) {
    if (cube.cubies[1][2] == 5 && cube.cubies[1][3] == 2 && cube.cubies[1][4] == 4 && cube.cubies[1][5] == 3) {
        cube.moves("RRURURRRUUURRRUUURRRURRR");
    }
    else if (cube.cubies[1][2] == 3 && cube.cubies[1][3] == 5 && cube.cubies[1][4] == 4 && cube.cubies[1][5] == 2) {
        cube.moves("RUUURURURUUURRRUUURR");
    }
    else if (cube.cubies[1][2] == 4 && cube.cubies[1][3] == 5 && cube.cubies[1][4] == 2 && cube.cubies[1][5] == 3) {
        cube.moves("RRLLDRRLLUURRLLDRRLL");
    }
    else if (cube.cubies[1][2] == 3 && cube.cubies[1][3] == 2 && cube.cubies[1][4] == 5 && cube.cubies[1][5] == 4) {
        cube.moves("URRRUUURUUURURUUURRRURURRUUURRRU");
    }
    else {
        cube.moves("RRURURRRUUURRRUUURRRURRR");
        adjustUFace(cube);
        cube.moves("RRLLDRRLLUURRLLDRRLL");
        cube.moves("RRURURRRUUURRRUUURRRURRR");
        adjustUFace(cube);
    }
}

void PLL::solveCorners(Cubic& cube) {
    if (cube.cubies[2][2] == 4 && cube.cubies[0][3] == 5 && cube.cubies[2][3] == 2
        && cube.cubies[0][4] == 3 && cube.cubies[2][4] == 3 && cube.cubies[0][5] == 4) {
        cube.moves("RRRFRRRBBRFFFRRRBBRR");
    }
    else if (cube.cubies[2][2] == 4 && cube.cubies[0][3] == 5 && cube.cubies[2][3] == 3
        && cube.cubies[0][4] == 4 && cube.cubies[2][4] == 2 && cube.cubies[0][5] == 3) {
        cube.moves("RBBBRRRFRBRRRFFLLLBLFLLLBBBL");
    }
    else {
        cube.moves("RRRFRRRBBRFFFRRRBBRR");
    }
}

int PLL::checkCorners(Cubic& cube) {
    if (cube.cubies[0][2] != 2 || cube.cubies[2][2] != 2 || cube.cubies[0][3] != 3 || cube.cubies[2][3] != 3 || cube.cubies[0][4] != 4 || cube.cubies[2][4] != 4 || cube.cubies[0][5] != 5 || cube.cubies[2][5] != 5) {
        return 0;
    }
    else
        return 1;
}

int PLL::checkEdges(Cubic& cube) {
    if (cube.cubies[1][2] == 2 && cube.cubies[1][3] == 3 && cube.cubies[1][4] == 4 && cube.cubies[1][5] == 5) {
        return 1;
    }
    else {
        return 0;
    }
}
