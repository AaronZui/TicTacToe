#ifndef TIC_HPP
#define TIC_HPP

#include <iostream>
#include <string>
using namespace std;
class game {
private:
    char board[3][3];
    char pboard[3][3];
    char p1s;
    char p2s;

public:
    int counter = 0;
    bool p1 = true;
    char winner = '0';
    void p1set(char s);
    void p2set(char s);
    game();
    void display();
    void checkWin();
    void set(string input);
    void reset();
    bool swap(string m1, string m2);
    bool move(string m1, string m2);
};

#endif