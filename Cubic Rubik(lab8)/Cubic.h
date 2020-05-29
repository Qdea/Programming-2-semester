#pragma once
#include <string>
#include <vector>

class Cubic
{
private: 
    void X(int side, int n);
public:
    int count = 0;
    int saving = 0;
    int cubies[9][6];
    std::vector <int> moveList;
    std::vector <int> signList;
    Cubic();
    void solve(bool isPrint);
    void saveMove(int move, int n);
    void moves(std::string);
    void load();
    void output(bool isFile);
    void R(int);
    void L(int);
    void U(int);
    void D(int);
    void F(int);
    void B(int);
};
