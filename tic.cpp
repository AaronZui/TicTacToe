#include "tic.hpp"
#include <cctype>
#include <string>
using namespace std;
game::game() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = '-';
            pboard[i][j] = '-';

        }
    }
    
}
void game::p1set(char s)
{
    p1s = s;
}
void game::p2set(char s)
{
    p2s = s;
}

void game::display() {
    cout << "\t a \t b \t c" << endl;
    for (int i = 0; i < 3; i++) {
        cout << i + 1 << "\t";
        for (int j = 0; j < 3; j++) {
            cout << " " << pboard[i][j] << "\t";
        }
        cout << endl << endl;
    }
}

void game::checkWin() {
    counter++;
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == 'X' || board[i][0] == 'O') && board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
            winner = board[i][0];
            return;
        }
        if ((board[0][i] == 'X' || board[0][i] == 'O') && board[0][i] == board[1][i] && board[0][i] == board[2][i]) {
            winner = board[0][i];
            return;
        }
    }
    if ((board[0][0] == 'X' || board[0][0] == 'O') && board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
        winner = board[0][0];
        return;
    }
    if ((board[0][2] == 'X' || board[0][2] == 'O') && board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
        winner = board[0][2];
        return;
    }
    if (counter == 9 && winner == '0') {
        winner = '-';
    }
}

void game::set(string input) {
    int col, row;

    if (tolower(input[0]) == 'a') {
        col = 0;
    } else if (tolower(input[0]) == 'b') {
        col = 1;
    } else {
        col = 2;
    }

    row = (input[1] - '0') - 1;

    if (p1) {
        board[row][col] = 'X';
        pboard[row][col] = p1s;
        p1 = false;
    } else {
        board[row][col] = 'O';
        pboard[row][col] = p2s;

        p1 = true;
    }

    checkWin();
}
void game::reset() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = '-';
            pboard[i][j] = '-';
        }
    }
    counter = 0;
    winner = '0';
    p1 = true;
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

        if(p1){p1=false;}
        else if(!p1){p1=true;}

        counter--;
        checkWin();
        return true;
    }
    else{
        cout <<endl<< "invalid move try again"<<endl;
        return false;
        }
}
bool game::move(string m1, string m2) {
    int col1, row1, col2, row2;
    char move1, pmove1;

    col1 = tolower(m1[0]) - 'a';
    col2 = tolower(m2[0]) - 'a';

    row1 = m1[1] - '1';
    row2 = m2[1] - '1';

    if (((row1 == row2) != (col1 == col2)) && board[row1][col1] != '-'&& board[row2][col2] == '-' && (row1 >= 0 && row1 < 3 && row2 >= 0 && row2 < 3 && col1 >= 0 && col1 < 3 && col2 >= 0 && col2 < 3)) {

        move1 = board[row1][col1];
        pmove1 = pboard[row1][col1];

        board[row1][col1] = '-';
        pboard[row1][col1] = '-';
        board[row2][col2] = move1;
        pboard[row2][col2] = pmove1;

        if(p1){p1=false;}
        else if(!p1){p1=true;}

        counter--;
        checkWin();
        return true;

    }
    else {cout << endl<<"invalid move try again"<<endl;
    return false;}
}
