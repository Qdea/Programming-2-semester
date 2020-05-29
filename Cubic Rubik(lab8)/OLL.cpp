#include "OLL.h"
#include "Cubic.h"
#include <iostream>
#include <string>

void OLL::solveOLL(Cubic& cube) {
    if (!checkEdges(cube)) {
        int state = findEdges(cube);
        while (state == 0) {
            cube.moves("U");
            state = findEdges(cube);
        }
        solveCase(cube, state);
    }
    if (!checkOLL(cube)) {
        int state = findState(cube);
        while (state == 0) {
            cube.moves("U");
            state = findState(cube);
        }
        solveCase(cube, state);
    }

}

int OLL::checkOLL(Cubic& cube) {
    for (int i = 0; i < 9; ++i) {
        if (cube.cubies[i][1] != 1)
            return 0;
    }
    return 1;
}

void OLL::solveCase(Cubic& cube, int state) {
    switch (state) {
    case 1:
        cube.moves("FRURRRUUUFFF");
        solveOLL(cube);
        break;
    case 2:
        cube.moves("BULUUULLLBBB");
        solveOLL(cube);
        break;
    case 3:
        cube.moves("FRURRRUUUFFFBULUUULLLBBB");
        solveOLL(cube);
        break;
    case 4:
        cube.moves("RURRRURUURRR");
        break;
    case 5:
        cube.moves("RRRUUURUUURRRUUR");
        break;
    case 6:
        cube.moves("FRURRRUUURURRRUUURURRRUUUFFF");
        break;
    case 7:
        cube.moves("RUURRUUURRUUURRUUR");
        break;
    case 8:
        cube.moves("RRDRRRUURDDDRRRUURRR");
        break;
    case 9:
        cube.moves("LFRRRFFFLLLFRFFF");
        break;
    case 10:
        cube.moves("FFFLFRRRFFFLLLFR");
        break;
    }
}

int OLL::findState(Cubic& cube) {
    int topLayer[9];
    int redSide[3];
    int greenSide[3];
    int orangeSide[3];
    int blueSide[3];

    for (int i = 0; i < 9; ++i)
        topLayer[i] = cube.cubies[i][1] == 1 ? 1 : 0;

    for (int i = 0; i < 3; ++i) {
        redSide[i] = cube.cubies[i][2] == 1 ? 1 : 0;
        greenSide[i] = cube.cubies[i][3] == 1 ? 1 : 0;
        orangeSide[i] = cube.cubies[i][4] == 1 ? 1 : 0;
        blueSide[i] = cube.cubies[i][5] == 1 ? 1 : 0;
    }

    if (topLayer[0] != 1 && topLayer[1] == 1 && topLayer[2] != 1 && topLayer[3] == 1 && topLayer[4] == 1 && topLayer[5] == 1 && topLayer[6] == 1 && topLayer[7] == 1 && topLayer[8] != 1 && redSide[2] == 1 && greenSide[2] == 1 && orangeSide[2] == 1)
        return 4;
    
    if (topLayer[0] == 1 && topLayer[1] == 1 && topLayer[2] != 1 && topLayer[3] == 1 && topLayer[4] == 1 && topLayer[5] == 1 && topLayer[6] != 1 && topLayer[7] == 1 && topLayer[8] != 1 && redSide[0] == 1 && greenSide[0] == 1 && orangeSide[0] == 1)
        return 5;
    
    if (topLayer[0] != 1 && topLayer[1] == 1 && topLayer[2] != 1 && topLayer[3] == 1 && topLayer[4] == 1 && topLayer[5] == 1 && topLayer[6] != 1 && topLayer[7] == 1 && topLayer[8] != 1 && redSide[0] == 1 && redSide[2] == 1 && orangeSide[0] == 1 && orangeSide[2] == 1)
        return 6;

    if (topLayer[0] != 1 && topLayer[1] == 1 && topLayer[2] != 1 && topLayer[3] == 1 && topLayer[4] == 1 && topLayer[5] == 1 && topLayer[6] != 1 && topLayer[7] == 1 && topLayer[8] != 1 && redSide[2] == 1 && orangeSide[0] == 1 && blueSide[0] == 1 && blueSide[2] == 1)
        return 7;
    
    if (topLayer[0] == 1 && topLayer[1] == 1 && topLayer[2] == 1 && topLayer[3] == 1 && topLayer[4] == 1 && topLayer[5] == 1 && topLayer[6] != 1 && topLayer[7] == 1 && topLayer[8] != 1 && redSide[0] == 1 && redSide[2] == 1)
        return 8;
    
    if (topLayer[0] != 1 && topLayer[1] == 1 && topLayer[2] == 1 && topLayer[3] == 1 && topLayer[4] == 1 && topLayer[5] == 1 && topLayer[6] != 1 && topLayer[7] == 1 && topLayer[8] == 1 && redSide[0] == 1 && orangeSide[2] == 1)
        return 9;
    
    if (topLayer[0] != 1 && topLayer[1] == 1 && topLayer[2] == 1 && topLayer[3] == 1 && topLayer[4] == 1 && topLayer[5] == 1 && topLayer[6] == 1 && topLayer[7] == 1 && topLayer[8] != 1 && redSide[2] == 1 && blueSide[0] == 1)
        return 10;

    return 0;
}

int OLL::findEdges(Cubic& cube) {

    int topLayer[9];

    for (int i = 0; i < 9; ++i)
        topLayer[i] = cube.cubies[i][1] == 1 ? 1 : 0;

    if (topLayer[3] == 1 && topLayer[4] == 1 && topLayer[5] == 1)
        return 1;
    
    if (topLayer[5] == 1 && topLayer[7] == 1)
        return 2;
    
    if (topLayer[1] != 1 && topLayer[3] != 1 && topLayer[5] != 1 && topLayer[7] != 1)
        return 3;
    
    return 0;
}

int OLL::checkEdges(Cubic& cube) {
    return (cube.cubies[1][1] != 1 || cube.cubies[3][1] != 1 || cube.cubies[5][1] != 1 || cube.cubies[7][1] != 1) ? 0 : 1;
}
