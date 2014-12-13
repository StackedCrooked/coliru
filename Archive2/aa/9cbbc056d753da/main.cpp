#include <iostream>
#include <string>
#include <vector>

enum tileType {
    no_player,
    o_player,
    x_player
};

struct Board {
    int tl, tm, tr;
    int ml, mm, mr;
    int bl, bm, br;
    Board (int tl, int tm, int tr, int ml, int mm, int mr, int bl, int bm, int br)
        : tl(tl), tm(tm), tr(tr), ml(ml), mm(mm), mr(mr), bl(bl), bm(bm), br(br) { }
    std::ostream& operator<<(std::ostream& os, const Board& b) {
        os << b.tl << ' ' << b.tm << std::endl;
        return os;
    }
};

int main()
{
    Board b(no_player, no_player, no_player, no_player, no_player, no_player, no_player, no_player, no_player);
    std::cout << b << std::endl;
}
