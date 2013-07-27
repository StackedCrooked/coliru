#include <functional>
#include <random>
#include <array>
#include <iostream>
#include <set>
#include <deque>

typedef int pos_t;
static const char Empty = '.';

enum direction : int { None, N = -10, S = 10, E = 1, W = -1 };

std::ostream& operator<<(std::ostream& os, direction d) {
    switch(d) {
        case N : return os << 'N';
        case S : return os << 'S';
        case E : return os << 'E';
        case W : return os << 'W';
        default: break;
    };
    return os << "?";
}

direction random_direction()
{
    static const std::array<direction, 4> steps { { N, S, E, W } };
    static auto gen = std::bind(std::uniform_int_distribution<int>(0,steps.size()), std::mt19937(time(NULL)));
    return steps[gen()];
}

struct move
{
    direction taken = None;
    std::set<direction> tried;
};

int main()
{
    std::vector<char> board(100, Empty);

    pos_t pos    = 0;
    char station = 'A';
    board[pos]   = station++;

    // generate moves
    std::deque<move> history {}; // start with an empty move
    move pending {};

    auto select = [&] () -> bool
    { 
        auto& taken = pending.taken;
        auto& tried = pending.tried;

        pos_t nw;

        do
        {
            // random untried direction
            do    taken        = random_direction();
            while (end(tried) != tried.find(taken));

            // calculate new position
            nw = pos + taken;

            // validate new position
            bool valid = 
                (nw>=0) && (nw<(int)board.size()) && // within bounds?
                board[nw]==Empty &&                  // unvisited?
                // detect moving across the edge using invariant: 
                // INV: only col/row allowed to change
                (!(pos%10 - nw%10) != !(pos/10 - nw/10));

            // mark tried
            tried.insert(taken);

            // return if valid/no candidates
            if (valid || 4 == tried.size())
                return valid;

        } while (true); // try another direction
    };

    auto display = [&] {
        for(auto row = begin(board); row<end(board); row+=10)
            std::cout << std::string(row, row+10) << "\n";
    };

    auto apply = [&] () mutable {
        std::cout << pending.taken;

        pos        += pending.taken;
        board[pos]  = station++;

        history.emplace_back();
        std::swap(pending, history.back());
        //display();
    };

    auto backtrack = [&] () mutable {
        std::swap(pending, history.back());
        history.pop_back();
        std::cout << "[-" << pending.taken << "]";

        board[pos]  = (--station, Empty);
        pos        -= pending.taken;
        //display();
    };

    // game loop
    std::cout << "\nGenerating: ";

    while (station<='Z')
        select()? apply() : backtrack();

    std::cout << "\nResulting board: \n";

    display();
}
