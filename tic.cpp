#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <algorithm>
#include "tic.hpp"

using namespace std;

string currentArea;
string pname;
string archetype;
char symbol;
char esym;
bool secret = false;
int health;
int defense;
int attack;
int balance;


void playNormalGame(game &current) {
    current.reset();
    current.p1set('X');
    current.p2set('O');

    while (current.winner == '0') {
        current.display();
        cout << "Player " << (current.p1 ? "1" : "2") << " move: ";
        string cmove;
        getline(cin >> ws, cmove);

        if (!(cmove.length()==2 &&
              (tolower(cmove[0])=='a'||tolower(cmove[0])=='b'||tolower(cmove[0])=='c') &&
              (cmove[1]=='1'||cmove[1]=='2'||cmove[1]=='3'))) {
            cout << "Invalid move, try again.\n";
            continue;
        }

        current.set(cmove);
        current.checkWin();
    }

    current.display();
    if (current.winner == '-') {
        cout << "It's a draw!\n";
    } else {
        cout << "Player " << (current.winner == 'X' ? "1" : "2") << " wins!\n";
    }
}

void playBattleGame(game &current, const string &arch1, const string &arch2) {
    current.reset();
    int totalMoves = 0;

    while (current.winner == '0') {
        current.display();
        bool canSpecial = (totalMoves >= 2);

        char curSym = current.p1 ? current.p1s : current.p2s;
        cout << "Player " << (current.p1 ? "1" : "2")
             << " (" << curSym << ") ";

        if (canSpecial) {
            cout << " choose action: (1) Place  (2) Special\n";
            cout << "Enter choice: ";

        } else {
            cout << " Place only (special unavailable until 2 moves done)\n";
        }
        string action;
        if(canSpecial){
        getline(cin >> ws, action);}
        else {action = "1";}

        if (action == "1" || action == "place" || action == "P" || action == "p") {
            cout << "Enter move (e.g. a1): ";
            string mv;
            getline(cin >> ws, mv);

            if (!(mv.length()==2 &&
                  (tolower(mv[0])=='a'||tolower(mv[0])=='b'||tolower(mv[0])=='c') &&
                  (mv[1]=='1'||mv[1]=='2'||mv[1]=='3'))) {
                cout << "Invalid move input. Try again.\n";
                continue;
            }
            current.set(mv);
            totalMoves++;
        }
        else if (canSpecial && (action == "2" || action == "special" || action == "S" || action == "s")) {
            if (current.p1) {
                if (arch1 == "Paladin") {
                    cout << "Select space to move from: "<<endl;
                    string f, t;
                    getline(cin >> ws, f);
                    cout << "Select space to move to: "<<endl;
                    getline(cin >> ws, t);
                    if (!current.move(f, t)) {
                        cout << "Invalid move. Try again.\n";
                        continue;
                    }
                } else {
                    cout << "Select first space to swap: ";
                    string s1, s2;
                    getline(cin >> ws, s1);
                    cout << "Select second space to swap: ";
                    getline(cin >> ws, s2);
                    if (!current.swap(s1, s2)) {
                        cout << "Invalid swap. Try again.\n";
                        continue;
                    }
                }
            } else {
                if (arch2 == "Paladin") {
                    cout << "Select space to move from: ";
                    string f, t;
                    getline(cin >> ws, f);
                    cout << "Select space to move to: ";
                    getline(cin >> ws, t);
                    if (!current.move(f, t)) {
                        cout << "Invalid move. Try again.\n";
                        continue;
                    }
                } else {
                    cout << "Select first space to swap: \n";
                    string s1, s2;
                    getline(cin >> ws, s1);
                    cout << "Select second space to swap: \n";
                    getline(cin >> ws, s2);
                    if (!current.swap(s1, s2)) {
                        cout << "Invalid swap. Try again.\n";
                        continue;
                    }
                }
            }
        }
        else {
            cout << "Invalid choice. Try again.\n";
            continue;
        }

        current.checkWin();
    }  

    current.display();
    if (current.winner == '-') {
        cout << "It's a draw!\n";
    } else {
        cout << "Player " << (current.winner == current.p1s ? "1" : "2") << " wins!\n";
    }
}



bool abilityTriggers() {
    return (rand() % 10) < 3;
}

void battleEnemy(Enemy e) {
    game g;
    g.p1set(symbol);
    g.p2set(esym);
    
    cout << endl << "\t=== The Battle Begins ===" << endl;
    cout << pname << " HP: " << health << " | " << e.name << " HP: " << e.health << endl << endl;
    
    while (health > 0 && e.health > 0) {
        g.reset();
        int totalMoves = 0;
        
        cout << "--- New Round ---" << endl;
        
        while (g.winner == '0') {
            g.display();
            bool canSpecial = (totalMoves >= 2);
            
            if (g.p1) {
                char curSym = g.p1s;
                cout << pname << " (" << curSym << ")";
                
                if (canSpecial) {
                    cout << " choose action: (1) Place  (2) Special\n";
                    cout << "Enter choice: ";
                } else {
                    cout << " (special unavailable until 2 moves)\n";
                }
                
                string action;
                if (canSpecial) {
                    getline(cin >> ws, action);
                } else {
                    action = "1";
                }
                
                if (action == "1" || action == "place" || action == "P" || action == "p") {
                    cout << "Enter move: ";
                    string mv;
                    getline(cin >> ws, mv);
                    
                    if (!(mv.length() == 2 &&
                          (tolower(mv[0]) == 'a' || tolower(mv[0]) == 'b' || tolower(mv[0]) == 'c') &&
                          (mv[1] == '1' || mv[1] == '2' || mv[1] == '3'))) {
                        cout << "Invalid move input. Try again.\n";
                        continue;
                    }
                    
                    int col = tolower(mv[0]) - 'a';
                    int row = mv[1] - '1';
                    
                    if (g.getCell(row, col) != '-') {
                        cout << "That space is already taken. Try again.\n";
                        continue;
                    }
                    
                    g.set(mv);
                    totalMoves++;
                }
                else if (canSpecial && (action == "2" || action == "special" || action == "S" || action == "s")) {
                    if (archetype == "Paladin") {
                        cout << "Select space to move from: ";
                        string f, t;
                        getline(cin >> ws, f);
                        cout << "Select space to move to: ";
                        getline(cin >> ws, t);
                        if (!g.move(f, t)) {
                            cout << "Invalid move. Try again.\n";
                            continue;
                        }
                    } else {
                        cout << "Select first space to swap: ";
                        string s1, s2;
                        getline(cin >> ws, s1);
                        cout << "Select second space to swap: ";
                        getline(cin >> ws, s2);
                        if (!g.swap(s1, s2)) {
                            cout << "Invalid swap. Try again.\n";
                            continue;
                        }
                    }
                }
                else {
                    cout << "Invalid choice. Try again.\n";
                    continue;
                }
            }
            else {
                cout << e.name << " is thinking..." << endl;
                
                bool usedSpecial = false;
                
                if (e.bspecial && abilityTriggers() && canSpecial) {
                    cout << e.name << " uses Double Strike!" << endl;
                    
                    for (int moveCount = 0; moveCount < 2; moveCount++) {
                        vector<string> moves;
                        for (char c = 'a'; c <= 'c'; c++) {
                            for (char r = '1'; r <= '3'; r++) {
                                moves.push_back(string() + c + r);
                            }
                        }
                        
                        vector<string> valid;
                        for (string m : moves) {
                            int col = m[0] - 'a';
                            int row = m[1] - '1';
                            if (g.getCell(row, col) == '-') {
                                valid.push_back(m);
                            }
                        }
                        
                        if (!valid.empty()) {
                            string mv = valid[rand() % valid.size()];
                            g.set(mv);
                            cout << "  -> Strike " << (moveCount + 1) << " at " << mv << "!" << endl;
                        }
                    }
                    usedSpecial = true;
                }

                else if (!e.special.empty() && abilityTriggers() && canSpecial) {
                    cout << e.name << " uses a special ability!" << endl;
                    int i = rand() % e.special.size();
                    e.special[i](g, rand() % 3, rand() % 3);
                    usedSpecial = true;
                }
                
                if (!usedSpecial) {
                    vector<string> moves;
                    for (char c = 'a'; c <= 'c'; c++) {
                        for (char r = '1'; r <= '3'; r++) {
                            moves.push_back(string() + c + r);
                        }
                    }
                    
                    vector<string> valid;
                    for (string m : moves) {
                        int col = m[0] - 'a';
                        int row = m[1] - '1';
                        if (g.getCell(row, col) == '-') {
                            valid.push_back(m);
                        }
                    }
                    
                    if (!valid.empty()) {
                        string mv = valid[rand() % valid.size()];
                        g.set(mv);
                        cout << e.name << " places at " << mv << "\n";
                        totalMoves++;
                    }
                }
            }
            
            g.checkWin();
        }
        
        g.display();
        
        if (g.winner == symbol) {
            int dmg = max(0, attack - e.defense);
            e.health -= dmg;
            cout << "\n" << pname << " wins the round! You deal " << dmg 
                 << " damage to " << e.name << "!\n";
        }
        else if (g.winner == esym) {
            int dmg = max(0, e.attack - defense);
            health -= dmg;
            cout << "\n" << e.name << " wins the round and deals " 
                 << dmg << " damage to you!\n";
        }
        else {
            cout << "\nThe round was a draw. No damage dealt.\n";
        }
        
        cout << "\n" << pname << " HP: " << health 
             << " | " << e.name << " HP: " << e.health << "\n\n";
    }
    
    if (health <= 0) {
        cout << "\n*** You were defeated by " << e.name << "! ***\n";
        cout << "Your journey ends here...\n";
        currentArea = "Choosing";
    } else {
        cout << "\n*** You defeated " << e.name << "! ***\n";
        int goldReward = e.attack + e.defense;
        balance += goldReward;
        cout << "Gold gained: " << goldReward << "\n";
    }
}

game::game() {
    reset();
}

void game::p1set(char s) {
    p1s = s;
}

void game::p2set(char s) {
    p2s = s;
}

void game::display() {
    cout << "\n\t a \t b \t c\n";
    for (int i = 0; i < 3; i++) {
        cout << i+1 << "\t";
        for (int j = 0; j < 3; j++) {
            cout << " " << pboard[i][j] << "\t";
        }
        cout << "\n\n";
    }
}

void game::checkWin() {
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] != '-') && board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
            winner = board[i][0];
            return;
        }
        if ((board[0][i] != '-') && board[0][i] == board[1][i] && board[0][i] == board[2][i]) {
            winner = board[0][i];
            return;
        }
    }
    if ((board[0][0] != '-') && board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
        winner = board[0][0];
        return;
    }
    if ((board[0][2] != '-') && board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
        winner = board[0][2];
        return;
    }
    if (counter == 9 && winner == '0') {
        winner = '-';  
    }
}

void game::set(string input) {
    int col, row;
    if (tolower(input[0]) == 'a') col = 0;
    else if (tolower(input[0]) == 'b') col = 1;
    else col = 2;
    row = (input[1] - '0') - 1;

    char mark = p1 ? p1s : p2s;
    char real = p1 ? 'X' : 'O';

    board[row][col] = real;
    pboard[row][col] = mark;

    p1 = !p1;
    counter++;
}

bool game::swap(string m1, string m2) {
    int col1, row1, col2, row2;
    char move1, move2;

    col1 = tolower(m1[0]) - 'a';
    col2 = tolower(m2[0]) - 'a';

    row1 = m1[1] - '1';
    row2 = m2[1] - '1';

    if ((board[row1][col1] != '-' && board[row2][col2] != '-') && 
        (board[row1][col1] != board[row2][col2]) &&
        (row1 >= 0 && row1 < 3 && row2 >= 0 && row2 < 3 && 
         col1 >= 0 && col1 < 3 && col2 >= 0 && col2 < 3)) {

        move1 = board[row1][col1];
        board[row1][col1] = board[row2][col2];
        board[row2][col2] = move1;

        move1 = pboard[row1][col1];
        pboard[row1][col1] = pboard[row2][col2];
        pboard[row2][col2] = move1;

        p1 = !p1;

        checkWin();
        return true;
    }
    else {
        cout << endl << "invalid move try again" << endl;
        return false;
    }
}

bool game::move(string m1, string m2) {
    int c1 = tolower(m1[0]) - 'a';
    int r1 = m1[1] - '1';
    int c2 = tolower(m2[0]) - 'a';
    int r2 = m2[1] - '1';

    if (r1<0||r1>2||c1<0||c1>2||r2<0||r2>2||c2<0||c2>2) return false;
    if (board[r1][c1] == '-' || board[r2][c2] != '-') return false;
    
    if (!((r1 == r2) ^ (c1 == c2))) return false;

    board[r2][c2] = board[r1][c1];
    pboard[r2][c2] = pboard[r1][c1];

    board[r1][c1] = '-';
    pboard[r1][c1] = '-';

    return true;
}

bool game::blind(int m1, int m2) {
    for (int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if (pboard[i][j] == symbol || pboard[i][j] == esym) {
                pboard[i][j] = '?';
            }
        }
    }
    return true;
}

bool game::flip(int m1, int m2) {
    rotate(m1, m2);
    rotate(m1, m2);
    return true;
}

bool game::swapsym(int m1, int m2) {
    char temp = symbol;
    symbol = esym;
    esym = temp;
    return true;
}

bool game::rotate(int m1, int m2) {
    char temp[3][3];
    char ptemp[3][3];
    
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            temp[c][2 - r] = board[r][c];
            ptemp[c][2 - r] = pboard[r][c];
        }
    }
    
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            board[r][c] = temp[r][c];
            pboard[r][c] = ptemp[r][c];
        }
    }
    
    return true;
}

bool game::smash(int m1, int m2) {
    if (m1 < 0 || m1 > 2 || m2 < 0 || m2 > 2) return false;
    
    if (board[m1][m2] == 'X') {
        pboard[m1][m2] = esym;
        board[m1][m2] = 'O';
        p1 = !p1;
        return true;
    }
    return false;
}

void game::reset() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            board[i][j] = '-';
            pboard[i][j] = '-';
        }
    counter = 0;
    winner = '0';
    p1 = true;
}

void save() {
    ofstream save("save.txt", ios::out | ios::trunc);
    if (!save) {
        cout << "Progress failed to save...\n";
        return;
    }

    save << currentArea << endl;
    save << pname << endl;
    save << archetype << endl;
    save << health << endl;
    save << defense << endl;
    save << attack << endl;
    save << balance << endl;
    save << (secret ? 1 : 0) << endl;

    cout << "Game saved.\n";
}

void load() {
    ifstream save("save.txt");
    if (!save) {
        cout << "No save found — starting new game.\n";
        currentArea = "Choosing";
        return;
    }

    string temp;
    getline(save, currentArea);
    getline(save, pname);
    getline(save, archetype);

    if (!getline(save, temp)) return;
    health = stoi(temp);

    if (!getline(save, temp)) return;
    defense = stoi(temp);

    if (!getline(save, temp)) return;
    attack = stoi(temp);

    if (!getline(save, temp)) return;
    balance = stoi(temp);

    if (!getline(save, temp)) return;
    secret = (stoi(temp) != 0);

    cout << "Save loaded. Welcome back, " << pname << "!\n";
}

int playAdventureGame() {
    srand(time(0));
    load();

    if (currentArea.empty()) {
        currentArea = "Choosing";
    }

    while (currentArea == "Choosing") {
        cout << "\n========================================\n";
        cout << "  QUEST FOR THE OLDEST ROCK\n";
        cout << "========================================\n\n";
        cout << "Welcome, brave adventurer! Before we begin, tell me your name: ";

        while (true) {
            getline(cin, pname);
            cout << "Your name is '" << pname << "'. Is this correct? (yes/no): ";
            string confirm;
            getline(cin, confirm);
            if (confirm == "yes" || confirm == "Yes" || confirm == "y") {
                break;
            }
            cout << "Please enter your name again: ";
        }

        while (true) {
            cout << "\nChoose a symbol for your battles (single character): ";
            string S;
            getline(cin, S);
            if (S.length() == 1) {
                symbol = S[0];
                esym = (symbol == 'O') ? 'X' : 'O';
                break;
            }
        }

        while (true) {
            cout << "\nChoose your class:\n";
            cout << "  1) Paladin - Can move pieces\n";
            cout << "  2) Alchemist - Can swap opponent pieces\n";
            cout << "Enter choice (1/2 or Paladin/Alchemist): ";
            getline(cin, archetype);
            if (archetype == "Paladin" || archetype == "paladin" || archetype == "1" || archetype == "p") {
                archetype = "Paladin";
                break;
            } else if (archetype == "Alchemist" || archetype == "alchemist" || archetype == "2" || archetype == "a") {
                archetype = "Alchemist";
                break;
            } else {
                cout << "Invalid choice. Please choose Paladin or Alchemist.\n";
            }
        }

        balance = 5;
        health = 50;
        defense = 5;
        attack = 10;

        cout << "\n===============================\n";
        cout << "THE STORY BEGINS\n";
        cout << "===================================\n\n";
        cout << "Long ago in a far off town your story begins\n";
        cout << "You, " << pname << " the " << archetype << ", \n";
        cout << "had a crazy agrument with the towns #1 trouble maker he says the stone he has is the oldest there has ever been.\n\n";
        
        cout << "You know he is lying, there are some real old stones out there and you seen him pick it up.\n";
        cout << "The gather you're life savings of 5 gold and head out to disprove this oaf.\n\n";
        
        cout << "At the village shop, you see:\n";
        cout << "  1) Steel Helmet (+5 defense) - 5 gold\n";
        cout << "  2) Steel Sword (+5 attack) - 5 gold\n";
        cout << "  3) Health Potion (+10 health) - 5 gold\n";
        cout << "  4) Save your gold\n";

        while (true) {
            cout << "\nWhat would you like to buy? ";
            string c;
            getline(cin, c);
            if (c == "1" || c == "Steel Helmet") {
                balance = 0;
                defense += 5;
                cout << "\nYou place the helmet on your head.\n";
                currentArea = "1";
                break;
            } else if (c == "2" || c == "Steel Sword") {
                balance = 0;
                attack += 5;
                cout << "\nYou wield the Steel Sword. Attack increased!\n";
                currentArea = "1";
                break;
            } else if (c == "3" || c == "Health Potion") {
                balance = 0;
                health += 10;
                cout << "\nYou drink the Health Potion. Health increased!\n";
                currentArea = "1";
                break;
            } else if (c == "4") {
                cout << "\nYou save your gold.\n";
                currentArea = "1";
                break;
            } else {
                cout << "Invalid option, try again.\n";
            }
        }

        save();

    }

    if (currentArea == "1") {
        cout << "\n===============================\n";
        cout << "THE Village path\n";
        cout << "===============================\n\n";
        cout << "You start heading down the village path, and you see a rock that looks fairly old, it hasn't moved in forever so you pick it up.\n";
        cout << "It's not a rock, its a pebble, but not only is it a pebble, but an angry one at that, it was fine where it was but now its mad.\n\n";
        
        Enemy pebble;
        pebble.name = "angry pebble";
        pebble.health = 15;
        pebble.attack = 5;
        pebble.defense = 2;
        
    
        pebble.special.push_back([](game& g, int m1, int m2) -> bool {
            cout << "The pebble spins, rotating the board!\n";
            return g.rotate(m1, m2);
        });
        
        battleEnemy(pebble);
        
        if (health > 0) {
            cout<<"You smite the meschivious pebble, it was certainly old but its not really a rock its just a pebble.";
            currentArea = "2";
            save();
        }
    }

    if (currentArea == "2") {
        cout << "\n=========================\n";
        cout << "THE STONE\n";
        cout << "=========================\n\n";
        cout << "You continue down the path and you are attacked by one of the cobblestones\n\n";
        
        Enemy Cobble;
        Cobble.name = "Cobble Stone";
        Cobble.health = 25;
        Cobble.attack = 8;
        Cobble.defense = 6;
        
        Cobble.special.push_back([](game& g, int m1, int m2) -> bool {
            cout << "The \n";
            return g.swapsym(m1, m2);
        });
        
        battleEnemy(Cobble);
        
        if (health > 0) {
            cout << "\nYou destroy the stone before you are able to check how old it is but you're sure the man in the village had an older one\n";
            currentArea = "2.1";
            save();
        }
    }

    if (currentArea == "2.1") {
        cout << "\n=========================\n";
        cout << "TRAVELING MERCHANT\n";
        cout << "=========================\n\n";
        cout << "You meet a traveling merchant on the road.\n";
        cout << "Current Gold: " << balance << "\n\n";
        cout << "The merchant offers:\n";
        cout << "  1) Greater Health Potion (+20 HP) - 10 gold\n";
        cout << "  2) Sharpening Stone (+5 Attack) - 12 gold\n";
        cout << "  3) Shield (+5 Defense) - 12 gold\n";
        cout << "  4) Continue without buying\n";

        while (true) {
            cout << "\nWhat would you like? ";
            string c;
            getline(cin, c);
            if (c == "1") {
                if (balance >= 10) {
                    balance -= 10;
                    health += 20;
                    cout << "\nHealth restored!\n";
                } else {
                    cout << "\nNot enough gold!\n";
                    continue;
                }
            } else if (c == "2") {
                if (balance >= 12) {
                    balance -= 12;
                    attack += 5;
                    cout << "\nYou consume the stone and you feel your mind sharpen!\n";
                } else {
                    cout << "\nNot enough gold!\n";
                    continue;
                }
            } else if (c == "3") {
                if (balance >= 12) {
                    balance -= 12;
                    defense += 5;
                    cout << "\nYour defenses grow stronger!\n";
                } else {
                    cout << "\nNot enough gold!\n";
                    continue;
                }
            } else if (c == "4") {
                cout << "\nYou bid the merchant farewell.\n";
            } else {
                cout << "Invalid choice.\n";
                continue;
            }
            break;
        }
        
        currentArea = "3";
        save();
    }

    if (currentArea == "3") {
        cout << "\n===================================\n";
        cout << "THE BATTLE OF THE BEGINING\n";
        cout << "===================================\n\n";
        cout << "The man from the village had followed you, he knows what you are doing and he doesn;t like it\n";
        cout << "\n\n";
        
        Enemy man;
        man.name = "Village man";
        man.health = 30;
        man.attack = 15;
        man.defense = 5;
        
        man.special.push_back([](game& g, int m1, int m2) -> bool {
            cout << "The man throws sand in your eye\n";
            return g.blind(m1, m2);
        });
        
        man.special.push_back([](game& g, int m1, int m2) -> bool {
            cout << "The man flips out\n";
            return g.flip(m1, m2);
        });
        
        battleEnemy(man);
        
        if (health > 0) {
            cout << "\nThe man runs off, no stone left behind this time.\n";
            cout << "But their is a ring, will you put it on\n";
            cout<< "    1) Yes(-3 defense)\n    2) No";
            while(true){
                string choice;
                getline(cin, choice);
                if(choice == "1"){
                    cout<<"You feel strange\n";
                    secret = true;
                    break;
                }
                else if(choice == "2"){
                    cout<<"\nYou leave that junk where you found it if he comes back for it he can have it.\n";
                    break;
                }
                else{cout<<"invalid selection try again.";}
            }
            
            currentArea = "3.1";
            save();
        }
    }

    if (currentArea == "3.1") {
        cout << "\n=============================\n";
        cout << "THE ROCK CONCERT\n";
        cout << "=============================\n\n";
        cout << "You find yourself around among many new rocks, they are cold and you are alone\n";
        cout << "What do you do?\n";
        cout << "  1) Lift the rocks (+10 Attack, -5 HP)\n";
        cout << "  2) Run into the rocks (+10 Defense, -5 HP)\n";
        cout << "  3) Rest on the rocks (+25 HP)\n";
        cout << "  4) Leave the rocks untouched\n";

        while (true) {
            cout << "\nYour choice: ";
            string c;
            getline(cin, c);
            if (c == "1") {
                attack += 10;
                health -= 5;
                cout << "\nYou get stronger lifting the rocks but one falls on you, that kind of hurt.\n";
                break;
            } else if (c == "2") {
                defense += 10;
                health -= 5;
                cout << "\nYou ram into the rocks till your body aches, the conditioning will pay off though.\n";
                break;
            } else if (c == "3") {
                health += 25;
                cout << "\nSleep is importand for recover, you feel a lot better.\n";
                break;
            } else if (c == "4") {
                cout << "\nYou leave the rocks alone, they aren't involved in this venture.\n";
                break;
            } else {
                cout << "Invalid choice.\n";
            }
        }
        
        currentArea = "4";
        save();
    }

    if (currentArea == "4") {
        cout << "\n====================\n";
        cout << "THE OLDEST QUARRY\n";
        cout << "====================\n\n";
        cout << "A miner sees you on entering and he knows you aren't supposed to be there.\n";
        cout << "You try to explain your mission but he looks at you like you are insane.\n\n";
        
        Enemy miner;
        miner.name = "miner";
        miner.health = 40;
        miner.attack = 14;
        miner.defense = 10;
        
        miner.special.push_back([](game& g, int m1, int m2) -> bool {
            cout << "The miner spins to gain momentum.\n";
            return g.rotate(m1, m2);
        });
        
        miner.special.push_back([](game& g, int m1, int m2) -> bool {
            cout << "The miner swings his pickaxe.\n";
            return g.smash(m1, m2);
        });
        
        battleEnemy(miner);
        
        if (health > 0) {
            cout << "\nThe miner is willing to listen to reason after the battle.\n";
            cout << "You traverse deeper into the quarry.\n";
            currentArea = "4.1";
            save();
        }
    }

    
    if (currentArea == "4.1") {
        cout << "\n========================================\n";
        cout << "THE CAVES OF THE QUARRY\n";
        cout << "========================================\n\n";
        cout << "At the bottom of the quarry there are two caves\n";
        cout << ":\n\n";
        cout << "  1) The old mine (man made)\n";
        cout << "  2) The Skull Cavern (almost a pit, doesn't seem like much of a cave more of a death trap)\n\n";

        while (true) {
            cout << "Which path do you choose? ";
            string choice;
            getline(cin, choice);
            if (choice == "1") {
                cout<<"\n You walk into the old mine and know you are getting close to the end of your journey.\n";
                currentArea = "5.0";
                save();
                break;
            }
                else if (choice == "2") {
                cout<<"\n You leap down Skull Cavern and you prepare for the worst.\n";
                currentArea = "5.1";
                save();
                break;
            }
                else{cout<<"\nInvalid selction try again\n";}
            }
        }
        while(currentArea == "5.1"){
            cout << "\n======================\n";
            cout << "Skull Cavern\n";
            cout << "======================\n\n";
            cout<<"\n\nStrolling through the abyss you find a cursed shopkeeper\n";
            cout << "Current Gold: " << balance << "\n\n";
            cout << "The merchant offers:\n";
            cout << "  1) Greatest Health Potion (+100 HP) - 50 gold\n";
            cout << "  2) Blade of Agony (+75 Attack) - 100 gold\n";
            cout << "  3) Chestplate of Indestructability (+ 40 Defense) - 100 gold\n";
            cout << "  4) Continue\n";
            while (true) {
            cout << "\nWhat would you like? ";
            string c;
            getline(cin, c);
            if (c == "1") {
                if (balance >= 50) {
                    balance -= 10;
                    health += 20;
                    cout << "\nYou are reborn!\n";
                } else {
                    cout << "\nNot enough gold!\n";
                    continue;
                }
            } else if (c == "2") {
                if (balance >= 100) {
                    balance -= 12;
                    attack += 5;
                    cout << "\nYour blade will not be bested!\n";
                } else {
                    cout << "\nNot enough gold!\n";
                    continue;
                }
            } else if (c == "3") {
                if (balance >= 100) {
                    balance -= 100;
                    defense += 40;
                    cout << "\nYour can't feel pain!\n";
                } else {
                    cout << "\nNot enough gold!\n";
                    continue;
                }
            } else if (c == "4") {
                cout << "\nYou bid the merchant farewell.\n";
                break;
            } else {
                cout << "Invalid choice.\n";
                continue;
            }
        }
        
        currentArea = "6.1";
        save();
    }
    
        while(currentArea == "5.0"){
            if (attack<15){
                attack = 15;
            }
            cout << "\n======================\n";
            cout << "THE OLD MINES\n";
            cout << "======================\n\n";
            cout << "If you were an old rock this is probably where you'd be, the oldest rock must be up ahead.\n";
            cout << "By some twist of fate a tyranosourus lies ahead gaurding a really old rock, he will not make this easy.\n";
            Enemy Rex;
            Rex.name = "T-Rex";
            Rex.health = 200;
            Rex.attack = 30;
            Rex.defense = 10;
            Rex.special.push_back([](game& g, int m1, int m2) -> bool {
            cout << "The T-rex runs on the wall\n";
            return g.rotate(m1, m2);
            });
            Rex.special.push_back([](game& g, int m1, int m2) -> bool {
            cout << "The T-rex slams into you\n";
            return g.smash(m1, m2);
            });
            Rex.special.push_back([](game& g, int m1, int m2) -> bool {
            cout << "The T-rex flips the corridor\n";
            return g.flip(m1, m2);
            });
            Rex.bspecial = true;
            battleEnemy(Rex);
        
            if (health > 0) {
                cout << "\nYou have Bested the monstrosity, you take the rock from the cave and head home.\n";
                currentArea = "end1";
               save();
        }
    
        }

        while(currentArea =="end1"){
             cout << "With your new rock the man from the village hangs his head at your arrival, everyone likes your new rock.\n";
             cout << "While you have beat the man you their was greater glory out there in the cavern below but this will do for now.\n";
             cout << "The end, would you like to play again?\n1) Yes \n2) No\n";
             string c;
             if(c == "1" || c == "y"|| c == "yes"|| c == "Y"|| c == "Yes"){
             cout<<"Good luck\n";
             currentArea = "Choosing";
             save();}
             else {cout<<"thanks for playing";
            return 0;
            }

        }
        while (currentArea == "6.1")
        {
            cout << "\n=========================\n";
                cout << "THE CAVERN AHEAD\n";
                cout << "=========================\n\n";
            if (secret == false){
                
                cout<< "It's been a long journey but when you get into the cavern there is a door that is closed\n";
                cout<< "To make it worse you can't climb out.\n";
                cout<<"This is the bad ending\n";
                currentArea = "Choosing";
                save();
                return 0;
            }
            else{
                cout<< "There is a door ahead that opens infront of you.\n";
                cout<< "You go through the door and there is nothing but void.\n";
                currentArea = "7";
                save();
            }

        }
while(currentArea == "7"){
    cout << "\n==========================\n";
    cout << "THE SPACE BEFORE TIME\n";
    cout << "==========================\n\n";
    cout<< "An infinitely compact universe lies before you, the oldest rock ever one may say.\n";
    cout<< "What happens when an immovable object is acted on by an unstopable force?\n";
    cout<< "Time to find out";
if (defense < 70){
    defense = 70;
}
if(defense > 100){
    defense =99;
}

    health += balance;
    Enemy Universe;
    Universe.bspecial = true;
    Universe.name = "The Universe";
    Universe.health = 1000;
    Universe.defense = 1;
    Universe.attack = 100;
    Universe.special.push_back([](game& g, int m1, int m2) -> bool {
            cout << "The Universe flips reality\n";
            return g.flip(m1, m2);
            });
    Universe.special.push_back([](game& g, int m1, int m2) -> bool {
            cout << "The Universe turns reality\n";
            return g.rotate(m1, m2);
            });
    Universe.special.push_back([](game& g, int m1, int m2) -> bool {
            cout << "The Universe turns reality\n";
            return g.rotate(m1, m2);
            });
    Universe.special.push_back([](game& g, int m1, int m2) -> bool {
            cout << "The Universe smashes reality\n";
            return g.smash(m1, m2);
            });
    Universe.special.push_back([](game& g, int m1, int m2) -> bool {
            cout << "The Universe destroys light;\n";
            return g.blind(m1, m2);
            });
    battleEnemy(Universe);

}
if (health > 0) {
        cout << "\nYou have gained the strength to move the universe, you now have the oldest rock in your possession.\n";
        cout<< "You won't make it back to the village because it is now part of your rock but you know you won\n";
        currentArea = "end2";
               save();
        }   
if (currentArea == "end2"){
    cout<< "It's been a long journey but it is now time to rest.\n";
    cout<< "after a few billion years of rest maybe you'll brag about your awesome stone to show off in the village\n";
    cout<<"thanks for playing\n";
    cout<<"Would you like to play again\n 1) Yes \n2) No";
    string s;
    getline(cin, s);
    if(s == "yes" || s == "Yes"|| s == "y"|| s == "Y"|| s == "1"){cout<<"Have fun\n";
    currentArea="Choosing";
    save();}
    else{cout<< "Goodbye";
    return 0;}
}
        
}


