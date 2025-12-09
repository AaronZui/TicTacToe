#include <iostream>
#include <string>
#include "tic.hpp"

using namespace std;

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

    if ((board[row1][col1] != '-' && board[row2][col2] != '-') && (board[row1][col1] != board[row2][col2])&&(row1 >= 0 && row1 < 3 && row2 >= 0 && row2 < 3 && col1 >= 0 && col1 < 3 && col2 >= 0 && col2 < 3)) {

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
    else{
        cout <<endl<< "invalid move try again"<<endl;
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

    p1 = !p1;
    return true;
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
void computerMove(){}
void battleLoop(){}
void playAdventureGame(game &current, const string &arch1, const string &arch2){

};