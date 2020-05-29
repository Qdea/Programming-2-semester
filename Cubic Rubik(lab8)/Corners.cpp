#include "Corners.h"
#include "Cubic.h"
using namespace corners;

void Corners::solveCorners(Cubic& cube) {
    while (checkBottomLayer(cube))
        for (int i = 0; i < 4; i++) {
            int a0 = idx[i][0][0];
            int a1 = idx[i][0][1];
            int b0 = idx[i][1][0];
            int b1 = idx[i][1][1];
            int c0 = idx[i][2][0];
            int c1 = idx[i][2][1];
            if (cube.cubies[a0][a1] == 0 || cube.cubies[b0][b1] == 0 || cube.cubies[c0][c1] == 0) {
                a0 = idx[i][3][0];
                a1 = idx[i][3][1];
                b0 = idx[i][4][0];
                b1 = idx[i][4][1];
                c0 = idx[i][5][0];
                c1 = idx[i][5][1];
                while (cube.cubies[a0][a1] == 0 || cube.cubies[b0][b1] == 0 || cube.cubies[c0][c1] == 0)
                    cube.moves("U");
                cube.moves(moves[i]);
            }
        }

    while (checkCorners(cube)) {
        if (cube.cubies[8][1] == 0) {
            if (cube.cubies[2][2] == 2) { //red and blue
                cube.moves("UFUUFFFUUUFUFFF");
            }
            else if (cube.cubies[2][2] == 3) { //green and red
                cube.moves("RUURRRUUURURRR");
            }
            else if (cube.cubies[2][2] == 4) { //orange and green
                cube.moves("UUUBUUBBBUUUBUBBB");
            }
            else if (cube.cubies[2][2] == 5) { //orange and blue
                cube.moves("UULUUULLLUULULLL");
            }
        }
        else if (cube.cubies[0][3] == 0) {
            if (cube.cubies[2][2] == 2) { //red green
                cube.moves("RURRR");
            }
            else if (cube.cubies[2][2] == 3) { //green orange
                cube.moves("UUUBUBBB");
            }
            else if (cube.cubies[2][2] == 4) { //orange blue
                cube.moves("UULULLL");
            }
            else if (cube.cubies[2][2] == 5) { //red blue
                cube.moves("UFUFFF");
            }
        } 
        else if (cube.cubies[2][2] == 0) {
            if (cube.cubies[0][3] == 2) { //blue red
                cube.moves("ULLLUUUL");
            }
            else if (cube.cubies[0][3] == 3) { //red green
                cube.moves("FFFUUUF");
            }
            else if (cube.cubies[0][3] == 4) { //orange green
                cube.moves("URRRUUUR");
            }
            else if (cube.cubies[0][3] == 5) { //orange blue
                cube.moves("UUBBBUUUB");
            }

        } 
        else
            cube.moves("U");
    }
}

int Corners::checkCorners(Cubic& cube) {
    return (!cube.cubies[0][0] && !cube.cubies[2][0] && !cube.cubies[6][0] && !cube.cubies[8][0]) ? 0 : 1;
}

int Corners::checkBottomLayer(Cubic& cube) {
    return ((cube.cubies[0][0] && cube.cubies[2][0] && cube.cubies[6][0] && cube.cubies[8][0]
        && cube.cubies[6][2] && cube.cubies[8][2] && cube.cubies[6][3] && cube.cubies[8][3]
        && cube.cubies[6][4] && cube.cubies[8][4] && cube.cubies[6][5] && cube.cubies[8][5])
        || (!cube.cubies[0][0] && !cube.cubies[2][0] && !cube.cubies[6][0] && !cube.cubies[8][0])) ? 0 : 1;
}
