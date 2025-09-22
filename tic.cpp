#include "tic.hpp"
using namespace std;
game::game() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = '-';
        }
    }
}

void game::display() {
    cout << "\t a \t b \t c" << endl;
    for (int i = 0; i < 3; i++) {
        cout << i + 1 << "\t";
        for (int j = 0; j < 3; j++) {
            cout << " " << board[i][j] << "\t";
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
        p1 = false;
    } else {
        board[row][col] = 'O';
        p1 = true;
    }

    checkWin();
}

void game::reset() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = '-';
        }
    }
    counter = 0;
    winner = '0';
    p1 = true;
}