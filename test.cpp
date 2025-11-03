#include <iostream>
#include <cassert>
#include <string>
#include "tic.hpp"
using namespace std;
int main() {
    // Tests start conditions
    {
        game g;
        assert(g.winner == '0');
        assert(g.p1 == true);
    }

    // Tests turns alternating
    {
        game g;
        g.set("a1");
        assert(g.p1 == false);
        
        g.set("b2");
        assert(g.p1 == true);
    }

    // Tests row win
    {
        game g;
        g.set("a1");
        g.set("a2");
        g.set("b1");
        g.set("b2");
        g.set("c1");
        assert(g.winner == 'X');
    }

    // Tests column win
    {
        game g;
        g.set("a1");
        g.set("b1");
        g.set("a2");
        g.set("b2");
        g.set("a3");
        assert(g.winner == 'X');
    }

    // Tests diagonals win
    {
        game g;
        g.set("a1");
        g.set("a2");
        g.set("b2");
        g.set("b1");
        g.set("c3");
        assert(g.winner == 'X');
    }
    {
        game g;
        g.set("c1");
        g.set("a1");
        g.set("b2");
        g.set("a2");
        g.set("a3");
        assert(g.winner == 'X');
    }
    
    // Tests draw
    {
        game g;
        g.set("a1");
        g.set("a2");
        g.set("a3");
        g.set("b1");
        g.set("b3");
        g.set("b2");
        g.set("c1");
        g.set("c3");
        g.set("c2");
        assert(g.winner == '-');
        //tests new functions for battle mode
        g.reset();
        g.set("a1");
        g.set("b2");
        g.set("c3");
        g.set("b1");
        g.set("b3");
        assert(g.swap("b1","b2")==false);

        g.swap("b3","b2");
        assert(g.winner != '-');
        g.reset();
        g.set("a1");
        g.set("b2");
        g.set("c3");
        g.set("b1");
        g.set("b3");
        assert(g.move("a1","b2")==false);
        assert(g.move("a1","c1")==true);
    }
    
    cout << endl << "All tests completed successfully!" <<endl;
}