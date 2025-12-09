#include <iostream>
#include <string>
#include "tic.hpp"

using namespace std;

int main() {
    cout << "Welcome to TicTacToe\n";
    bool playing = true;

    while (playing) {
        game current;

        string mode;
        while (true) {
            cout << "\nChoose mode:\n";
            cout << "  1. Regular\n";
            cout << "  2. Battle\n";
            cout << "  3. Adventure\n";
            cout << "Enter 1, 2, or 3: ";
            getline(cin >> ws, mode);

            if (mode == "1" || mode == "Regular" || mode == "regular" || mode == "r" || mode == "R") {
                playNormalGame(current);
                break;
            }
            else if (mode == "2" || mode == "Battle" || mode == "battle" || mode == "b" || mode == "B") {

                cout << "Player 1 choose symbol: ";
                char s1;
                cin >> ws;
                cin >> s1;
                current.p1set(s1);

                cout << "Player 2 choose symbol: ";
                char s2;
                cin >> ws;
                cin >> s2;
                current.p2set(s2);

                string arch1, arch2;

                while (true) {
                    cout << "Player 1 choose archetype (Paladin or Alchemist): ";
                    getline(cin >> ws, arch1);
                    if (arch1 == "Paladin" || arch1 == "paladin" || arch1 == "1" || arch1 == "p" || arch1 == "P") {
                        arch1 = "Paladin";
                        break;
                    }
                    else if (arch1 == "Alchemist" || arch1 == "alchemist" || arch1 == "2" || arch1 == "a" || arch1 == "A") {
                        arch1 = "Alchemist";
                        break;
                    }
                    else {
                        cout << "Invalid archetype. Please choose Paladin or Alchemist.\n";
                    }
                }

                while (true) {
                    cout << "Player 2 choose archetype (Paladin or Alchemist): ";
                    getline(cin >> ws, arch2);
                    if (arch2 == "Paladin" || arch2 == "paladin" ||
                        arch2 == "1" || arch2 == "p" || arch2 == "P") {
                        arch2 = "Paladin";
                        break;
                    }
                    else if (arch2 == "Alchemist" || arch2 == "alchemist" ||
                             arch2 == "2" || arch2 == "a" || arch2 == "A") {
                        arch2 = "Alchemist";
                        break;
                    }
                    else {
                        cout << "Invalid archetype. Please choose Paladin or Alchemist.\n";
                    }
                }

                playBattleGame(current, arch1, arch2);
                break;
            }
            else if(mode == "3" || mode == "Adventure" || mode == "adventure" || mode == "a" || mode == "A"){
                
                cout << "Player 1 choose symbol: ";
                char s1;
                cin >> ws;
                cin >> s1;
                current.p1set(s1);


                string arch1;

                while (true) {
                    cout << "Player 1 choose archetype (Paladin or Alchemist): ";
                    getline(cin >> ws, arch1);
                    if (arch1 == "Paladin" || arch1 == "paladin" || arch1 == "1" || arch1 == "p" || arch1 == "P") {
                        arch1 = "Paladin";
                        break;
                    }
                    else if (arch1 == "Alchemist" || arch1 == "alchemist" || arch1 == "2" || arch1 == "a" || arch1 == "A") {
                        arch1 = "Alchemist";
                        break;
                    }
                    else {
                        cout << "Invalid archetype. Please choose Paladin or Alchemist.\n";
                    }
                }

                playAdventureGame(current, arch1, "Special");
                break;
            } 
            else{
                cout << "Invalid mode selected. Please try again.\n";
            }
        }

        cout << "\nPlay again? (y/n): ";
        string again;
        getline(cin >> ws, again);
        if (!(again == "y" || again == "Y" || again == "yes" || again == "Yes")) {
            playing = false;
        }
    }

    cout << "Thanks for playing!\n";
    return 0;
}
