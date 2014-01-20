#include <array>
#include <iostream>

enum class piece_t
{
   EMPTY = 0, PAWN, ROOK, BISHOP, KNIGHT, QUEEN, KING
};

static const size_t WIDTH = 8, HEIGHT = 8;
struct board_t : std::array<piece_t, WIDTH*HEIGHT>
{
    board_t()
    {
        for (size_t y = 0; y < HEIGHT; y++)
            for (size_t x = 0; x < WIDTH; x++)
                operator()(x,y) = piece_t::EMPTY;
    }
    
    piece_t& operator()(size_t x, size_t y)
    {
        return operator[](x + y*WIDTH);
    }
    
    const piece_t& operator()(size_t x, size_t y) const
    {
        return operator[](x + y*WIDTH);
    }
};

std::ostream& operator<<(std::ostream& os, const piece_t& piece)
{
    switch (piece) {
        case piece_t::KING:   return (os << 'K');
        case piece_t::QUEEN:  return (os << 'Q');
        case piece_t::KNIGHT: return (os << 'N');
        case piece_t::BISHOP: return (os << 'B');
        case piece_t::ROOK:   return (os << 'R');
        case piece_t::PAWN:   return (os << 'P');
        case piece_t::EMPTY:  return (os << ' ');
        default:              return (os << '?');
    }
}

std::ostream& operator<<(std::ostream& os, const board_t& board)
{
    os << '+' << std::string(WIDTH, '-') << '+' << '\n';
    for (size_t y = 0; y < HEIGHT; y++) {
        os << '|';
        for (size_t x = 0; x < WIDTH; x++)
            os << board(x, y);
        os << '|' << '\n';
    }
    os << '+' << std::string(WIDTH, '-') << '+' << '\n';
    return os;
}

int main()
{
   board_t b;
   b(3, 5) = piece_t::KING;
   b(6, 4) = piece_t::KNIGHT;
   std::cout << b << std::endl;
   // etc.
}