#include <iostream>
#include <string>
#include "tic.hpp"
#include <vector>

using namespace std;

string cmove;
game current;
string moves;

int main() {
    cout << "Welcome to TicTacToe" << endl;
    while (current.winner == '0') {
        current.display();
        if (current.p1 == true) {
            cout << endl << "Player 1 input move: ";
        }
        else {
            cout << endl << "Player 2 input move: ";
        }

        while (true) {
            cin >> cmove;
            if (cmove.length() == 2 &&
                (tolower(cmove[0]) == 'a' || tolower(cmove[0]) == 'b' || tolower(cmove[0]) == 'c') &&
                (cmove[1] == '1' || cmove[1] == '2' || cmove[1] == '3') &&
                moves.find(cmove) == string::npos) 
                {
                current.set(cmove);
                moves += cmove;
                cmove.clear();
                break;
            }
            else {
                cout << endl << "Invalid move, try again" << endl;
                cmove.clear();
            }
        }
    }

    current.display();
    if (current.winner == '-') {
        cout << "It's a draw!" << endl;
    }
    else {
        cout << "Player " << (current.winner == 'X' ? "1" : "2") << " wins!" << endl;
    }

    return 0;
}