#include <iostream>
#include <tuple>
#include <vector>
#include <unordered_map>
#include <unordered_set>


#define YELLOW  1
#define BLUE    2
#define GREEN   4
#define ORANGE  8
#define RED     16
#define MAX_COLOURS 5



using uchar = unsigned char;
using uint = unsigned int;
using Move = std::tuple<char, uint, uint>;



// from Boost. see http://www.boost.org/doc/libs/1_57_0/doc/html/hash/reference.html
template<typename T> void hash_combine(size_t & seed, T const& v);

inline std::size_t hash_value(char c) { return c; }
inline std::size_t hash_value(unsigned char c) { return c; }
inline std::size_t hash_value(uint u) { return u; }

std::size_t hash_value(const std::tuple<char, uint, uint>& t) {
    size_t seed = 0;
    hash_combine(seed, std::get<0>(t));
    hash_combine(seed, std::get<1>(t));
    hash_combine(seed, std::get<2>(t));
    return seed;
}

template<typename T>
void hash_combine(size_t & seed, T const& v)
{
    seed ^= hash_value(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template<typename It>
std::size_t hash_range(It first, It last)
{
    size_t seed = 0;
    for(; first != last; ++first)
    {
        hash_combine(seed, *first);
    }
    return seed;
}



struct Block
{
    Block() : Block(0, 0, 0, 0)
    {}

    Block(uchar c) : Block(c, c, c, c)
    {}

    Block(uchar a, uchar b, uchar c, uchar d) : top(a), right(b), bottom(c), left(d)
    {
        full = a | b | c | d;
    }

    bool operator==(const Block& other) const
    {
        return  (top == other.top) &&
                (left == other.left) &&
                (bottom == other.bottom) &&
                (right == other.right);
    }

    bool operator!=(const Block& other) const
    {
        return  !(*this == other);
    }

    inline bool has(int colour) const
    {
        return (full & colour);
    }

    inline void del(uchar colour)
    {
        full &= ~colour;
    }

    friend std::size_t hash_value(Block const& b)
    {
        //return b.full;
        // take care on order
        size_t seed = 0;
        hash_combine(seed, b.top);
        hash_combine(seed, b.bottom);
        hash_combine(seed, b.right);
        hash_combine(seed, b.left);
        return seed;
    }
/*
        void clear()
        {
            top = 0;
            right = 0;
            bottom = 0;
            left = 0;
        }
*/
    uchar top;
    uchar right;
    uchar bottom;
    uchar left;
    uchar full;
};


template <unsigned M>
class Board : private std::array<Block, M*M>
{
public:

    using std::array<Block,M*M>::array;
    using std::array<Block,M*M>::size;
    using std::array<Block,M*M>::begin;
    using std::array<Block,M*M>::end;
    using std::array<Block,M*M>::operator[];
    using std::array<Block,M*M>::operator=;


    friend bool operator==(const Board<M>& b1, const Board<M>& b2) {
        return std::equal(b1.begin(), b1.end(), b2.begin());
    }

    friend bool operator!=(const Board<M>& b1, const Board<M>& b2) {
        return !(b1 == b2);
    }

    inline size_t side() const
    {
        return M;
    }

    bool row_moved(unsigned row)
    {
        using std::swap;

        Board & b = *this;

        unsigned row_start = row * side();
        unsigned x = M - 1;
        while(x > 0)
        {
            swap(b[row_start + x], b[row_start + x - 1]);
            --x;
        }

        return true;
    }

    bool col_moved(unsigned col)
    {
        using std::swap;

        Board & b = *this;

        unsigned x = size() - side();
        while(x > 0)
        {
            swap(b[col + x], b[col + x - side()]);
            x -= side();
        }

        return true;
    }

    inline bool colBlocked(unsigned j) const
    {
        return columns[j];
    }

    inline bool rowBlocked(unsigned i) const
    {
        return rows[i];
    }

    void blockRows(const std::vector<unsigned>& rs)
    {
        for(int elem : rs)
            rows[elem - 1] = true;
    }

    void blockColumns(const std::vector<unsigned>& cols)
    {
        for(int elem : cols)
            columns[elem - 1] = true;
    }

private:
    bool columns[M] = {false};
    bool rows[M] = {false};
};


namespace std
{
    template <unsigned M>
    struct hash<Board<M>>
    {
        size_t operator()(const Board<M>& b) const
        {
            return hash_range(b.begin(), b.end());
        }
    };
/*
    template <>
    struct hash<std::vector<Move>>
    {
        size_t operator()(const std::vector<Move>& v) const
        {
            return hash_range(v.begin(), v.end());
        }
    };
*/
}


void debug_block(const Block & b)
{
    std::cout << "(" << (int)b.top << " " << (int)b.right << " " << (int)b.bottom << " " << (int)b.left << ")";
}

template <unsigned M>
void debug_board(const Board<M> & board)
{
    for(uint i = 0; i < board.size(); i++)
    {
        std::cout << (int) board[i].full << " ";
        if((i+1) % board.side() == 0)
            std::cout << std::endl;
    }
    std::cout << std::endl;
}

template <unsigned M>
void simulate(Board<M> board, std::vector<Move>& moves)
{
    int k = 0;
    debug_board(board);
    for(auto & mv : moves)
    {
        char axis = std::get<0>(mv);
        int i = std::get<1>(mv);
        int j = std::get<2>(mv);
        std::cout << "MOVE " << ++k << " (" << axis << ',' << i << ',' << j << ')' << std::endl;

        if (axis == 'r') {
            board.row_moved(i,j);
        }
        else if (axis == 'c') {
            board.col_moved(i,j);
        }
        debug_board(board);
    }
    std::cout << "END" << std::endl << std::endl;
}

template <unsigned M>
bool check_fill(Board<M>& board, uchar value)
{
    const uint bSize = board.size();
    const uint bSide = board.side();

    uint I = 0;
    std::vector<uint> zeroes;
    for(I = 0; I < bSize; ++I)
    {
        if(board[I].has(value))
        {
            zeroes.push_back(I);
            break;
        }
    }

    while(zeroes.size() > 0)
    {
        const uint i = zeroes.back();
        zeroes.pop_back();

        const uint x = i % bSide;
        const uint y = i / bSide;

        board[i].del(value);

        // left
        if(x > 0 && board[i - 1].has(value) && (board[i].left & board[i - 1].right & value))
            zeroes.push_back(i - 1);
        // right
        if(x < (bSide - 1) && board[i + 1].has(value) && (board[i].right & board[i + 1].left & value))
            zeroes.push_back(i + 1);
        // up
        if(y > 0 && board[i - bSide].has(value) && (board[i].top & board[i - bSide].bottom & value))
            zeroes.push_back(i - bSide);
        // down
        if(y < (bSide - 1) && board[i + bSide].has(value) && (board[i].bottom & board[i + bSide].top & value))
            zeroes.push_back(i + bSide);
    }

    for(uint i = I + 1; i < bSize; i++)
    {
        if(board[i].has(value))
        {
            return false;
        }
    }

    return true;
}

/* passage par copie obligatoire */
template <unsigned M>
bool solution(Board<M> board, int colours)
{
    for(int colour = 0; colour < MAX_COLOURS; colour++)
    {
        int colourShifted = 1 << colour;
        if(colourShifted & colours)
        {
            if(!check_fill(board, colourShifted))
            {
                return false;
            }
        }
    }
    return true;
}

unsigned solutions = 0;
unsigned checkedGrids = 0;
std::unordered_map<Board<5>, int> cache;

template <unsigned M>
void check_solution(Board<M>& board, std::vector<Move>& moves, int remaining_moves, int colours)
{
    ++checkedGrids;

    if(solution(board, colours))
    {
        ++solutions;

        std::cout << "SOLUTION FOUND :" << std::endl;
        //debug_board(board);
/*
        std::cout << std::endl;
        for(auto & move : moves)
        {
            std::cout << std::get<0>(move) << " " << std::get<1>(move) << " " << std::get<2>(move) << std::endl;
        }
        std::cout << std::endl;
*/
    }
    else if (remaining_moves > 0)
    {

        auto cached = cache.find(board);
        if(cached != cache.end() && cached->second >= remaining_moves)
            return;
        cache[board] = remaining_moves;

        const uint j = std::get<1>(moves.back());
        const char axis = std::get<0>(moves.back());

        moves.emplace_back('*', -1, -1); // placeholder

        for(uint i = 0; i < board.side(); i++)
        {
            // assign current row/col
            std::get<1>(moves.back()) = i;

            auto gridR = board;
            std::get<0>(moves.back()) = 'r';
            for(uint move = 1; !board.rowBlocked(i) && move < board.side(); ++move)
            {
                gridR.row_moved(i); // rotate one by one

                // don't move twice on the same axis
                if(axis != 'r' || j != i)
                {
                    // assign current rotation
                    std::get<2>(moves.back()) = move;
                    check_solution(gridR, moves, remaining_moves - 1, colours);
                }
            }

            auto gridC = board;
            std::get<0>(moves.back()) = 'c';
            for(uint move = 1; !board.colBlocked(i) && move < board.side(); ++move)
            {
                gridC.col_moved(i); // rotate one by one

                // don't move twice on the same axis
                if(axis != 'c' || j != i)
                {
                    // assign current rotation
                    std::get<2>(moves.back()) = move;
                    check_solution(gridC, moves, remaining_moves - 1, colours);
                }
            }
        }

        moves.pop_back();
    }
}

int main()
{
    Board<5> board = {
        Block(GREEN),   Block(RED),     Block(GREEN),   Block(RED),     Block(GREEN),
        Block(RED),     Block(GREEN),   Block(BLUE),    Block(GREEN),   Block(RED),
        Block(GREEN),   Block(BLUE),    Block(GREEN),   Block(BLUE),    Block(GREEN),
        Block(RED),     Block(GREEN),   Block(BLUE),    Block(GREEN),   Block(RED),
        Block(GREEN),   Block(RED),     Block(GREEN),   Block(RED),     Block(GREEN),
    };

    //std::copy(v.begin(),v.end(),board.begin());
    int mask = GREEN | RED | BLUE;

    board.blockColumns({ 1, 5 });
    board.blockRows({ 1, 5 });

/*
    Board<4> board =
    {
        Block(GREEN),   Block(ORANGE),  Block(GREEN),   Block(ORANGE),
        Block(BLUE),    Block(BLUE),    Block(BLUE),    Block(BLUE),
        Block(BLUE),    Block(YELLOW),  Block(RED),     Block(BLUE),
        Block(BLUE),    Block(RED),     Block(YELLOW),  Block(BLUE)
    };
    int mask = GREEN | RED | BLUE | ORANGE | YELLOW;
*/


#define MAX_DEPTH   6

    auto moves = std::vector<Move>();
    moves.reserve(MAX_DEPTH+1);
    moves.emplace_back('*',-1,-1); // hack

    check_solution(board, moves, MAX_DEPTH, mask);
    std::cout << checkedGrids << " checked grids" << std::endl;
    std::cout << solutions << " solutions" << std::endl;
    std::cout << cache.size() << " grids in cache" << std::endl;

    return 0;
}
