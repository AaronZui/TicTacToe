#ifndef TIC_HPP
#define TIC_HPP

#include <string>
using namespace std;

class game {
private:
    char board[3][3];
    char pboard[3][3];

public:
    char p1s;
    char p2s;
    int counter;
    bool p1;
    char winner;

    game();
    void p1set(char s);
    void p2set(char s);
    void display();
    void checkWin();
    void set(string input);
    void reset();
    bool swap(string m1, string m2);
    bool move(string m1, string m2);
};

void playNormalGame(game &current);
void playBattleGame(game &current, const string &arch1, const string &arch2);
void playAdventureGame(game &current, const string &arch1, const string &arch2);

#endif
