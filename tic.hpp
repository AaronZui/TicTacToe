#ifndef TIC_HPP
#define TIC_HPP

#include <string>
#include <functional>
#include <vector>
using namespace std;

class game {
private:
    char board[3][3];
    char pboard[3][3];

public:
    int counter;
    bool p1;
    char winner;
    char p1s, p2s;

    game();
    void reset();
    void p1set(char s);
    void p2set(char s);
    void display();
    bool move(string m1, string m2);
    bool swap(string m1, string m2);
    void set(string input);
    void checkWin();
    char getCell(int row, int col) const { return board[row][col]; }
    bool smash(int m1, int m2);
    bool rotate(int m1, int m2);
    bool flip(int m1, int m2);
    bool swapsym(int m1, int m2);
    bool blind(int m1, int m2);
};

struct Enemy {
    string name;
    int health;
    int attack;
    int defense;
    vector<function<bool(game& g, int m1, int m2)>> special;
    bool bspecial = false;
};

bool abilityTriggers();
void playNormalGame(game &current);
void playBattleGame(game &current, const string &arch1, const string &arch2);
int playAdventureGame();

extern string currentArea;
extern string pname;
extern string archetype;
extern char symbol;
extern char esym;
extern bool secret;
extern int health;
extern int defense;
extern int attack;
extern int balance;

void save();
void load();
void battleEnemy(Enemy e);

#endif