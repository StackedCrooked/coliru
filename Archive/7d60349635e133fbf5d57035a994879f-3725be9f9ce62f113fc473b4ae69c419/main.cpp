#include <algorithm>
#include <array>
#include <iostream>
#include <set>
#include <deque>

typedef int pos_t;
static const char Empty = '.';

enum direction : int { N = -10, S = 10, E = 1, W = -1, None = 0 };

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

struct move
{
    direction           taken = None;
    std::array<direction, 5> steps { { N, S, E, W, None } };
    const direction* next;

    move() : next(begin(steps))
    {
        std::random_shuffle(begin(steps), end(steps)-1);
    }
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
        while (*pending.next)
        {
            // random untried direction
            pending.taken = *pending.next++;

            // validate new position
            auto nw = pos + pending.taken;
            bool valid = 
                (nw>=0) && (nw<(int)board.size()) && // within bounds?
                board[nw]==Empty &&                  // unvisited?
                // detect moving across the edge using invariant: 
                // INV: only col/row allowed to change
                ((pos%10 == nw%10) != (pos/10 == nw/10));

            // return if valid/no candidates
            if (valid)
                return valid;
        }
        return false;
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

 :)
 