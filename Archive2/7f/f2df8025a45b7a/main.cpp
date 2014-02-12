// noble_card.h
#include <string>

class noble_card
{
public: 
    std::string name;
    int id;
    int vp;

    noble_card(int _vp);
};

// noble_card.cpp

noble_card::noble_card(int _vp): vp(_vp) {}

// board.h
// #include "noble_card.h"
#include <deque>

class board
{
public: 
    std::deque<noble_card> line;
};

// board.cpp (not necessary for your current impl)
// #include "board.h"

// main.cpp

int main()
{
    board b;
    for (unsigned i = 0; i < 12; ++i) {
        b.line.emplace_back(i);
    }
}
