#define _CRT_SECURE_NO_WARNINGS
#include "Cubic.h"
#include "Cross.h"
#include "Corners.h"
#include "Edges.h"
#include "OLL.h"
#include "PLL.h"
#include <iostream>
#include <string>

int const idx0[9] = { 6, 3, 0, 7, 4, 1, 8, 5, 2 };
int const sides[4][3] = { { 0, 1, 2 }, { 2, 5, 8 }, { 8, 7, 6 }, { 6, 3, 0 } };
int const rotation[6][2][4] = {
    { { 2, 5, 4, 3 }, { 2, 2, 2, 2 } },
    { { 2, 3, 4, 5 }, { 0, 0, 0, 0 } },
    { { 0, 3, 1, 5 }, { 0, 3, 2, 1 } },
    { { 0, 4, 1, 2 }, { 1, 3, 1, 1 } },
    { { 1, 3, 0, 5 }, { 0, 1, 2, 3 } },
    { { 0, 2, 1, 4 }, { 3, 3, 3, 1 } } };

Cubic::Cubic()
{
    memset(cubies, 0, sizeof(cubies));
    for (int sticker = 0; sticker < 9; ++sticker)
        for (int side = 0; side < 6; ++side)
            cubies[sticker][side] = side;
}

void Cubic::moves(std::string sequence) {
    size_t sequenceLength = sequence.length();
    for (size_t i = 0; i < sequenceLength; ++i) {
        switch (sequence[i]) {
        case 'U': U(1); break;
        case 'D': D(1); break;
        case 'R': R(1); break;
        case 'L': L(1); break;
        case 'F': F(1); break;
        case 'B': B(1); break;
        }
    }
}

void Cubic::load() {
    FILE* fp = NULL;
    if ((fp = freopen("cubic.in.txt", "r", stdin)) == NULL) {
        return;
    }
    char c[54];
    char colors[6] = { 'B', 'G', 'W', 'O', 'Y', 'R' };
    int sides[6][9] = {
        {0, 1, 2, 3, 4, 5, 6, 7, 8},
        {27, 18, 9, 28, 19, 10, 29, 20, 11},
        {12, 13, 14, 21, 22, 23, 30, 31, 32},
        {17, 26, 35, 16, 25, 34, 15, 24, 33},
        {44, 43, 42, 41, 40, 39, 38, 37, 36},
        {45, 46, 47, 48, 49, 50, 51, 52, 53}
    };
    for (int i = 0; i < 54; i++) {
        std::cin >> c[i];
    }
    for (int i = 0; i < 6; i++) {
        int q = sides[i][4];
        int side = 0;
        for (int k = 0; k < 6; k++) {
            if (c[q] == colors[k]) {
                side = k;
                break;
            }
        }
        for (int j = 0; j < 9; j++) {
            int p = sides[i][j];
            for (int k = 0; k < 6; k++) {
                if (c[p] == colors[k]) {
                    cubies[j][side] = k;
                    break;
                }
            }
        }
    }

    if (fp != NULL) {
        fclose(fp);
        freopen("CONIN$", "r", stdin);
    }

    solve(false);
    bool ok = true;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 6; j++) {
            if (cubies[i][j] != j) {
                ok = false;
                break;
            }
        }
        if (!ok) break;
    }
    if (!ok) {
        throw -2;
    }
}

void Cubic::output(bool isFile) {
    char matrix[4][3] = { {-1, 2, -1}, {5, 0, 3}, {-1, 4, -1}, {-1, 1, -1} };
    char colors[6] = { 'B', 'G', 'W', 'O', 'Y', 'R' };
    FILE* fp = NULL;
    if (isFile && (fp = freopen("cubic.out.txt", "w", stdout)) == NULL) {
        return;
    }
    std::cout << std::endl;
    for (int y = 0; y < 4; y++) {
        for (int i = 0; i < 27; i += 0) {
            for (int x = 0; x < 3; x++) {
                for (int j = 0; j < 3; j++) {
                    int k = matrix[y][x];
                    if (k >= 0) {
                        int p = i - x * 3 - (i / 9) * 6;
                        if (k == 5) {
                            p = 2 - p / 3 + (p % 3) * 3;
                        }
                        else
                            if (k == 3) {
                                p = 8 - (2 - p / 3 + (p % 3) * 3);
                            }
                            else
                                if (k == 4) {
                                    p = 8 - p;
                                }
                        std::cout << colors[cubies[p][k]];
                    }
                    else {
                        std::cout << ' ';
                    }
                    ++i;
                }
                std::cout << ' ';
            }
            if (i % 9 == 0) {
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
    }
    if (fp != NULL) {
        fclose(fp);
        freopen("CONOUT$", "w", stdout);
    }
}

void Cubic::solve(bool isPrint)
{
    count = 0;
    saving = 1;
    moveList.clear();
    signList.clear();
    Cross::solveCross(*this);
    Corners::solveCorners(*this);
    Edges::solveEdges(*this);
    OLL::solveOLL(*this);
    PLL::solvePLL(*this);
    saving = 0;

    if (isPrint) {
        std::cout << std::endl;
        for (int i = 0; i < moveList.size(); i++) {
            switch (moveList[i])
            {
            case 0: std::cout << "Y"; break;
            case 1: std::cout << "W"; break;
            case 2: std::cout << "B"; break;
            case 3: std::cout << "G"; break;
            case 4: std::cout << "R"; break;
            case 5: std::cout << "O"; break;
            }
            std::cout << signList[i] << " ";
        }
    }
}

void Cubic::saveMove(int move, int n)
{
    if (saving) {
        count++;
        if (count > 2000) {
            throw -1;
        }
        int m = -1;
        if (moveList.size() > 0) {
            m = moveList.back();
        }
        if (moveList.size() > 0 && m == move) {
            int sign = signList.back();
            signList.pop_back();
            sign += n;
            sign %= 4;
            if (sign == 0) {
                moveList.pop_back();
            }
            else {
                signList.push_back(sign);
            }
        }
        else {
            moveList.push_back(move);
            signList.push_back(n % 4);
        }
    }
}

void Cubic::X(int side, int n)
{
    int newCubies[9][6];
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 6; ++j)
            newCubies[i][j] = cubies[i][j];

    if (n >= 0) {
        for (int x = 0; x < n; ++x) {
            for (int i = 0; i < 4; ++i) {
                int j = (i + 1) % 4;
                for (int k = 0; k < 3; ++k) {
                    int a = rotation[side][0][i];
                    int b = rotation[side][0][j];
                    int c = sides[rotation[side][1][i]][k];
                    int d = sides[rotation[side][1][j]][k];
                    newCubies[c][a] = cubies[d][b];
                }
            }

            for (int i = 0; i < 9; ++i)
                newCubies[i][side] = cubies[idx0[i]][side];

            for (int i = 0; i < 9; ++i) {
                for (int j = 0; j < 6; ++j) {
                    cubies[i][j] = newCubies[i][j];
                }
            }
        }
    }
}

void Cubic::R(int n) { saveMove(5, n); X(3, n); }
void Cubic::L(int n) { saveMove(4, n); X(5, n); }
void Cubic::U(int n) { saveMove(3, n); X(1, n); }
void Cubic::D(int n) { saveMove(2, n); X(0, n); }
void Cubic::F(int n) { saveMove(1, n); X(2, n); }
void Cubic::B(int n) { saveMove(0, n); X(4, n); }
