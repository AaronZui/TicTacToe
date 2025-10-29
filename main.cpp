#include <iostream>
#include <string>
#include "tic.hpp"
#include <vector>

using namespace std;

string cmove;
game current;
string moves;
string sym1;
string sym2;
string again;
bool playing = true;
string mode;
string archetype1, archetype2;
string action;
string carch;
string s1,s2;
int main() 
{   
    cout << "Welcome to TicTacToe";
    while (playing == true)
    {
        moves.clear();
        current.reset();
    cout<< endl<<"Would you like to play normal or battle mode \n1.Regular \n2.Battle";
    while (true)
    {
        cin>>ws;
        getline(cin, mode);
        if(mode == "1" || mode == "Regular" || mode == "regular" || mode == "r" || mode == "R" || mode == "2" || mode == "Battle" || mode == "battle" ||mode == "b" || mode == "B")
        {break;}
        else{cout<<endl<<"Invalid input try again";}
    }
    if (mode == "1" || mode == "Regular" || mode == "regular" || mode == "r" || mode == "R")
    {
        current.p1set('X');
        current.p2set('O');

        
        
        while (current.winner == '0') 
        {
            current.display();
            if (current.p1 == true) {
                cout << endl << "Player 1 input move: ";
            }
            else {
                cout << endl << "Player 2 input move: ";
            }

            while (true) {
                cin >> ws;
                getline(cin, cmove);
                if (cmove.length() == 2 &&
                    (tolower(cmove[0]) == 'a' || tolower(cmove[0]) == 'b' || tolower(cmove[0]) == 'c') &&
                    (cmove[1] == '1' || cmove[1] == '2' || cmove[1] == '3') &&
                    moves.find(cmove) == string::npos) 
                    {
                    current.set(cmove);
                    moves += cmove;
                    cmove.clear();
                    current.checkWin();
                    current.display();
                    break;
                }
                else {
                    cout << endl << "Invalid move, try again" << endl;
                }
         }
        }

        current.display();
        if (current.winner == '-') {
            cout << "It's a draw!" << endl;
        }
        else 
        {
            cout << "Player " << (current.winner == 'X' ? "1" : "2") << " wins!" << endl;
        }
        cout<<"Would you like to play again? \n1.yes \n2.no";
        while(true)
        {
        cin>>ws;
        getline(cin,again);
        if (again == "Yes" ||again == "Y" ||again == "1"||again == "yes" ||again == "y")
        {
            break;
        }
        else
        {
            if (again == "no"||again == "No"||again == "N"||again == "n"||again == "2")
            {
                playing = false;
            }
        }
        }
    }

    //battle mode
    else{
    cout<< "player 1 select symbol"<<endl;
    while (true){
        cin >> ws;
        getline(cin, sym1);
        if (sym1.length()==1)
        {
            current.p1set(sym1[0]);
            break;
        }
    }
    cout<<endl<<"player 2 select symbol"<<endl;
    while (true)
    {
        cin >> ws;
        getline(cin, sym2);
        if (sym2.length()==1)
        {
            current.p2set(sym2[0]);
            break;

        }
    }
    cout<< "player 1 select archetype (Paladin or Alchemist)"<<endl;
    while (true){
        cin >> ws;
        getline(cin, archetype1);
        if (archetype1=="Paladin"||archetype1== "paladin"||archetype1=="1"||archetype1 == "p"|| archetype1 == "P")
        {
            archetype1 = "1";
            break;
        }
        else if (archetype1 == "Alchemist" || archetype1 == "alchemist"|| archetype1=="2"||archetype1 == "a"||archetype1 == "A"){
            archetype1 = "2";
            break;
        }
    }
    cout<< "player 2 select archetype (Paladin or Alchemist)"<<endl;
    while (true){
        cin >> ws;
        getline(cin, archetype2);
        if (archetype2=="Paladin"||archetype2== "paladin"||archetype2=="1"||archetype2 == "p"|| archetype2 == "P")
        {
            archetype2 = "1";
            break;
        }
        else if (archetype2 == "Alchemist" || archetype2 == "alchemist"|| archetype2=="2"||archetype2 == "a"||archetype2 == "A"){
            archetype2 = "2";
            break;
        }
        cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
        }
    while (current.winner == '0') 
        {
            while (current.counter <2)
            {
                current.display();
            if (current.p1 == true) {
                cout << endl << "Player 1 input move: ";
            }
            else {
                cout << endl << "Player 2 input move: ";
            }

            while (true) {
                cin >> ws;
                getline(cin, cmove);
                if (cmove.length() == 2 &&
                    (tolower(cmove[0]) == 'a' || tolower(cmove[0]) == 'b' || tolower(cmove[0]) == 'c') &&
                    (cmove[1] == '1' || cmove[1] == '2' || cmove[1] == '3') &&
                    moves.find(cmove) == string::npos) 
                    {
                    current.set(cmove);
                    moves += cmove;
                    cmove.clear();
                    break;}

            }}
            
            current.display();
            if (current.p1 == true) {
                cout << endl << "Player 1 input action \n1.Place \n2.Special";
                
            }
            else {
                cout << endl << "Player 2 input action \n1.Place \n2.Special";
            }
            while (true)
            {
                cin >> ws;
                getline(cin, action);
                if (action == "1"||action == "place"||action == "Place"||action == "p"||action == "P"){
                    while (true) {
                cin >> ws;
                getline(cin, cmove);
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
                else 
                {
                    cout << endl << "Invalid move, try again" << endl;
                }
                }
                }
                else if(action == "2"||action == "Special"||action == "special"||action == "s"||action == "S"){
                    if (current.p1 == true)
                    {
                        while (current.p1 == true)
                        {
                            if(archetype1 == "1")
                            {
                                cout<<endl<<"Select the space you would like to move: "<<endl;
                                cin>>ws;
                                getline(cin,s1);
                                cout<<endl<< "select where you would like to move it to: "<<endl;
                                cin>>ws;
                                getline(cin,s2);
                                if(current.move(s1,s2) == true){
                                    moves.erase(moves.find(s1), 2);
                                    moves+=s2;
                                    break;
                                }

                            }
                            else if(archetype1=="2"){
                                 cout<<endl<<"Select the space you would like to swap: "<<endl;
                                cin>>ws;
                                getline(cin,s1);
                                cout<<endl<< "select what you want to swap it with: "<<endl;
                                cin>>ws;
                                getline(cin,s2);
                                if(current.swap(s1,s2) == true){break;}
                            }
                        }
                        
                    }
                    
                }
                if (current.p1 == false)
                    {
                        while (current.p1 == false)
                        {
                            if(archetype2 == "1")
                            {
                                cout<<endl<<"Select the space you would like to move: "<<endl;
                                cin>>ws;
                                getline(cin,s1);
                                cout<<endl<< "select where you would like to move it to: "<<endl;
                                cin>>ws;
                                getline(cin,s2);
                                if(current.move(s1,s2) == true){break;
                                    moves.erase(moves.find(s1), 2);
                                    moves+=s2;
                                }

                            }
                            else if(archetype2=="2"){
                                 cout<<endl<<"Select the space you would like to swap: "<<endl;
                                cin>>ws;
                                getline(cin,s1);
                                cout<<endl<< "select what you want to swap it with: "<<endl;
                                cin>>ws;
                                getline(cin,s2);
                                if(current.swap(s1,s2) == true){break;}
                            }
                        }
                        
                    }
                    
                }
            }
            
            
        }

        current.display();
        if (current.winner == '-') {
            cout << "It's a draw!" << endl;
        }
        else 
        {
            cout << "Player " << (current.winner == 'X' ? "1" : "2") << " wins!" << endl;
        }
        cout<<"Would you like to play again? \n1.yes \n2.no";
        while(true)
        {
        cin>>ws;
        getline(cin,again);
        if (again == "Yes" ||again == "Y" ||again == "1"||again == "yes" ||again == "y")
        {
            break;
        }
        else
        {
            if (again == "no"||again == "No"||again == "N"||again == "n"||again == "2")
            {
                playing = false;
            }
        }
        }
    }
}