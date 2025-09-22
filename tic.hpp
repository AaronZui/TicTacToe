#ifndef TIC_HPP
#define TIC_HPP

#include <iostream>
#include <string>

class game {
private:
    char board[3][3];
    int counter = 0;

public:
    bool p1 = true;
    char winner = '0';

    game();
    void display();
    void checkWin();
    void set(std::string input);
    void reset();
};

#endif