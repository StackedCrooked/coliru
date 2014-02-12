    // noble_card.h
    #include <string>
    
    class noble_card
    {
    public: // single section of public stuff (are you sure you don't need private data?)
        std::string name; // never do: "using namespace std;" in a header!
        int id;
        int vp;
    
        noble_card(int _vp);
        // compiler-generated default constructor is just fine here
    };
    
    // noble_card.cpp
    
    noble_card::noble_card(int _vp): vp(_vp) {} // initialize member in initializer-list
    
    // board.h
    // #include "noble_card.h"
    #include <deque>
    
    class board
    {
    public: // single section of public stuff (are you sure you don't need private data?)
        std::deque<noble_card> line; // never do: "using namespace std;" in a header!
        // compiler generated default constructor and destructor are just fine here
    };
    
    // board.cpp (not necessary for your current impl)
    // #include "board.h" // takes care of "noble_card.h"
    
    // main.cpp
    
    int main()
    {
        board b;
        for (unsigned i = 0; i < 12; ++i) { 
            b.line.emplace_back(i); // C++11 allows you to construct-in-place
        }
    }