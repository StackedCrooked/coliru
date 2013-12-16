#include <iostream>

using byte = unsigned char;
using bitset_t = unsigned long long;

#define U8(V)   ((byte) (V))
#define U64(V)  ((bitset_t) (V))

using color_t = bool;
using colored_piece_t = byte;
using piece_t = byte;
using plate_t = piece_t[8][8];

#define WHITE   0
#define BLACK   1

#define EMPTY               U8(0)
#define KING                U8(1)
#define QUEEN               U8(2)
#define BISHOP              U8(3)
#define KNIGHT              U8(4)
#define ROOK                U8(5)
#define PAWN                U8(6)

#define PIECE(Piece, Color) (U8((Piece) | ((Color) == BLACK ? 1 << 3 : 0)))
#define PIECE_OF(Piece)     ((Piece) & 0x7)
#define COLOR_OF(Piece)     (((Piece) >> 3) & 1)

class bitboard
{
public:
    bitboard() : value_{0} { }
    bitboard(bitset_t value) : value_{value} { }
    bitboard(const bitboard& b) : value_{b.value_} { }
    
    bitset_t value() const { return value_; }
    void value(bitset_t value) { value_ = value; }
    
    void set_at(int index) { value_ |= (U64(1) << index); }
    
    static bitboard empty()    { return { 0}; }
    static bitboard universe() { return {-1}; }
    
    bitboard operator|(const bitboard b) const { return { value_ | b.value_ }; }
    bitboard operator&(const bitboard b) const { return { value_ & b.value_ }; }
    bitboard operator*(const bitboard b) const { return { value_ * b.value_ }; }
    bitboard operator<<(const byte b) const { return { value_ << b }; }
    bitboard operator>>(const byte b) const { return { value_ >> b }; }

private:
    bitset_t value_;
};

inline std::ostream&
operator<<(std::ostream& o, bitboard b)
{
    bitset_t value = b.value();
    bitset_t mask = 0x8000000000000000;
    
    for (int i = 0; i < 64; ++i)
    {
        if (value & mask)
            o << '1';
        else
            o << '.';
        if (i % 8 == 7)
            o << std::endl;
        else
            o << ' ';
        mask >>= 1;
    }
    
    return o;
}

class board
{
public:
    board() {}
    
    board(const board& board)
    {
        for (int line = 0; line < 8; ++line)
            for (int file = 0; file < 8; ++file)
                plate_[line][file] = board.plate_[line][file];
    }
    
    static board initial()
    {
        board b;
        
#define SET_SYM(Line, Column, Piece)    \
    b.plate_[Line][Column] = Piece;     \
    b.plate_[Line][7 - Column] = Piece;

#define SET_PAWNS(Line, Color)                      \
    for (int file = 0; file < 8; ++file)            \
        b.plate_[Line][file] = PIECE(PAWN, Color);
        
        SET_SYM(0, 0, PIECE(ROOK  , WHITE));
        SET_SYM(0, 1, PIECE(KNIGHT, WHITE));
        SET_SYM(0, 2, PIECE(BISHOP, WHITE));
        
        b.plate_[0][3] = PIECE(KING , WHITE);
        b.plate_[0][4] = PIECE(QUEEN, WHITE);
        
        SET_PAWNS(1, WHITE);
        
        for (int line = 2; line < 6; ++line)
            for (int file = 0; file < 8; ++file)
                b.plate_[line][file] = EMPTY;
        
        SET_PAWNS(6, BLACK);
        
        SET_SYM(7, 0, PIECE(ROOK  , BLACK));
        SET_SYM(7, 1, PIECE(KNIGHT, BLACK));
        SET_SYM(7, 2, PIECE(BISHOP, BLACK));
        
        b.plate_[7][3] = PIECE(KING , BLACK);
        b.plate_[7][4] = PIECE(QUEEN, BLACK);
        
#undef SET_SYM
#undef SET_PAWNS

        return b;
    }
    
    static board empty()
    {
        board b;
        
        for (int line = 0; line < 8; ++line)
            for (int file = 0; file < 8; ++file)
                b.plate_[line][file] = EMPTY;
        
        return b;
    }
    
    colored_piece_t get(int line, int file) const { return plate_[line][file]; }
    void set(int line, int file, colored_piece_t piece) { plate_[line][file] = piece; }

private:
    plate_t plate_;
};

class bitboardset
{    
public:
    bitboardset()
    : pieces_{
        {0x1000000000000010},
        {0x0800000000000008},
        {0x2400000000000024},
        {0x4200000000000042},
        {0x8100000000000081},
        {0x00ff00000000ff00},
      },
      colors_{
        {0x000000000000ffff},
        {0xffff000000000000},
      }
    { }
    
    bitboardset(const board& b)
    {
        for (int line = 0; line < 8; ++line)
            for (int file = 0; file < 8; ++file)
            {
                colored_piece_t clr_piece = b.get(line, file);
                if (clr_piece == EMPTY)
                    continue;
                
                int index = 8 * line + (7 - file);
                pieces_[PIECE_OF(clr_piece) - 1].set_at(index);
                colors_[COLOR_OF(clr_piece)].set_at(index);
            }
    }
    
    bitboard all_pieces() const
    {
        return colors_[WHITE] | colors_[BLACK];
    }
    
    bitboard rook_mask_at(byte line, byte file) const
    {
        return {rook_mask_[8 * line + (7 - file)]};
    }
    
    byte rook_shift_at(byte line, byte file) const
    {
        return {magic_shift_rook_[8 * line + (7 - file)]};
    }
    
    void print(std::ostream& o) const
    {
        o << "Pieces:" << std::endl;
        o << " - King:" << std::endl;
        o << pieces_[0];
        o << " - Queens:" << std::endl;
        o << pieces_[1];
        o << " - Bishops:" << std::endl;
        o << pieces_[2];
        o << " - Knights:" << std::endl;
        o << pieces_[3];
        o << " - Rooks:" << std::endl;
        o << pieces_[4];
        o << " - Pawns:" << std::endl;
        o << pieces_[5] << std::endl;
        
        o << "Colors: " << std::endl;
        o << " - Whites:" << std::endl;
        o << colors_[0];
        o << " - Blacks:" << std::endl;
        o << colors_[1];
        
        o << "Customs: " << std::endl;
        o << " - All pieces:" << std::endl;
        o << all_pieces();
        o << " - C3 Rook Mask:" << std::endl;
        o << rook_mask_at(2, 2);
        o << " - Rook occupancy:" << std::endl;
        o << (all_pieces() & rook_mask_at(2, 2));
        o << " - Array index:" << std::endl;
        o << (((all_pieces() & rook_mask_at(2, 2)) * bitboard{0b0110100000100000100000001000000000000100000000000010001000000000}) >> rook_shift_at(2, 2));
    }

private:
    bitboard pieces_[6];
    bitboard colors_[2];
    
    constexpr static bitset_t rook_mask_[64] = {
        0x000101010101017eL, 0x000202020202027cL, 0x000404040404047aL, 0x0008080808080876L, 0x001010101010106eL, 0x002020202020205eL, 0x004040404040403eL, 0x008080808080807eL,
        0x0001010101017e00L, 0x0002020202027c00L, 0x0004040404047a00L, 0x0008080808087600L, 0x0010101010106e00L, 0x0020202020205e00L, 0x0040404040403e00L, 0x0080808080807e00L,
        0x00010101017e0100L, 0x00020202027c0200L, 0x00040404047a0400L, 0x0008080808760800L, 0x00101010106e1000L, 0x00202020205e2000L, 0x00404040403e4000L, 0x00808080807e8000L,
        0x000101017e010100L, 0x000202027c020200L, 0x000404047a040400L, 0x0008080876080800L, 0x001010106e101000L, 0x002020205e202000L, 0x004040403e404000L, 0x008080807e808000L,
        0x0001017e01010100L, 0x0002027c02020200L, 0x0004047a04040400L, 0x0008087608080800L, 0x0010106e10101000L, 0x0020205e20202000L, 0x0040403e40404000L, 0x0080807e80808000L,
        0x00017e0101010100L, 0x00027c0202020200L, 0x00047a0404040400L, 0x0008760808080800L, 0x00106e1010101000L, 0x00205e2020202000L, 0x00403e4040404000L, 0x00807e8080808000L,
        0x007e010101010100L, 0x007c020202020200L, 0x007a040404040400L, 0x0076080808080800L, 0x006e101010101000L, 0x005e202020202000L, 0x003e404040404000L, 0x007e808080808000L,
        0x7e01010101010100L, 0x7c02020202020200L, 0x7a04040404040400L, 0x7608080808080800L, 0x6e10101010101000L, 0x5e20202020202000L, 0x3e40404040404000L, 0x7e80808080808000L
    };

    constexpr static bitset_t bishop_mask_[64] = {
        0x40201008040200L, 0x00402010080400L, 0x00004020100a00L, 0x00000040221400L, 0x00000002442800L, 0x00000204085000L, 0x00020408102000L, 0x02040810204000L,
        0x20100804020000L, 0x40201008040000L, 0x004020100a0000L, 0x00004022140000L, 0x00000244280000L, 0x00020408500000L, 0x02040810200000L, 0x04081020400000L,
        0x10080402000200L, 0x20100804000400L, 0x4020100a000a00L, 0x00402214001400L, 0x00024428002800L, 0x02040850005000L, 0x04081020002000L, 0x08102040004000L,
        0x08040200020400L, 0x10080400040800L, 0x20100a000a1000L, 0x40221400142200L, 0x02442800284400L, 0x04085000500800L, 0x08102000201000L, 0x10204000402000L,
        0x04020002040800L, 0x08040004081000L, 0x100a000a102000L, 0x22140014224000L, 0x44280028440200L, 0x08500050080400L, 0x10200020100800L, 0x20400040201000L,
        0x02000204081000L, 0x04000408102000L, 0x0a000a10204000L, 0x14001422400000L, 0x28002844020000L, 0x50005008040200L, 0x20002010080400L, 0x40004020100800L,
        0x00020408102000L, 0x00040810204000L, 0x000a1020400000L, 0x00142240000000L, 0x00284402000000L, 0x00500804020000L, 0x00201008040200L, 0x00402010080400L,
        0x02040810204000L, 0x04081020400000L, 0x0a102040000000L, 0x14224000000000L, 0x28440200000000L, 0x50080402000000L, 0x20100804020000L, 0x40201008040200L     
    };
    
    constexpr static byte magic_shift_rook_[64] = {
        52, 53, 53, 53, 53, 53, 53, 52,
        53, 54, 54, 54, 54, 54, 54, 53,
        53, 54, 54, 54, 54, 54, 54, 53,
        53, 54, 54, 54, 54, 54, 54, 53,
        53, 54, 54, 54, 54, 54, 54, 53,
        53, 54, 54, 54, 54, 54, 54, 53,
        53, 54, 54, 54, 54, 54, 54, 53,
        52, 53, 53, 53, 53, 53, 53, 52
    };
    
    constexpr static byte magic_shift_bishop_[64] = {
        58, 59, 59, 59, 59, 59, 59, 58,
        59, 59, 59, 59, 59, 59, 59, 59,
        59, 59, 57, 57, 57, 57, 59, 59,
        59, 59, 57, 55, 55, 57, 59, 59,
        59, 59, 57, 55, 55, 57, 59, 59,
        59, 59, 57, 57, 57, 57, 59, 59,
        59, 59, 59, 59, 59, 59, 59, 59,
        58, 59, 59, 59, 59, 59, 59, 58
    };
};

inline std::ostream&
operator<<(std::ostream& o, const board& b)
{
    static char pieces_char[] = { ' ', 'K', 'Q', 'B', 'N', 'R', 'P' };
    static char colors_char[] = { ' ', '-' };
    
    
#define PRINT_LINE()                            \
    o << "+---";                                \
    for (int file = 0; file <= 8; ++file)       \
        o << "+---";                            \
    o << '+' << std::endl;

#define PRINT_COLUMNS()                         \
    o << "|   |";                               \
    for (char file = 'A'; file <= 'H'; ++file)  \
        o << ' ' << file << " |";               \
    o << "   |" << std::endl;
    
    PRINT_LINE();
    PRINT_COLUMNS();    
    PRINT_LINE();
    
    for (int line = 7; line >= 0; --line)
    {
        o << "| " << (line + 1) << " |";
        
        for (int file = 0; file < 8; ++file)
        {
            colored_piece_t clr_piece = b.get(line, file);
            char piece_char = pieces_char[PIECE_OF(clr_piece)];
            char color_char = colors_char[COLOR_OF(clr_piece)];
            if (piece_char == ' ' && (line + file) % 2 == 1)
                piece_char = '.';
            o << color_char << piece_char << color_char << '|';
        }
        
        o << " " << (line + 1) << " |";
        
        o << std::endl;
        PRINT_LINE();
    }
    
    PRINT_COLUMNS();
    PRINT_LINE();

#undef PRINT_LINE
#undef PRINT_COLUMNS
}

class state
{
public:
    state()
    : board_{board::initial()}
    { }
    
    state(const board& board)
    : board_{board},
      bitboards_{board}
    { }
    
    void print(std::ostream& o) const
    {
        o << "Board :" << std::endl;
        o << board_;
        bitboards_.print(o);
    }

private:
    board board_;
    bitboardset bitboards_;
};

inline std::ostream&
operator<<(std::ostream& o, const state& s)
{
    s.print(o);
    return o;
}

int
main()
{
    board b = board::empty();
    
    b.set(0, 4, PIECE(ROOK, WHITE));
    b.set(0, 5, PIECE(KING, WHITE));
    b.set(1, 1, PIECE(PAWN, WHITE));
    b.set(1, 2, PIECE(PAWN, WHITE));
    b.set(2, 2, PIECE(ROOK, WHITE));
    b.set(2, 5, PIECE(KNIGHT, BLACK));
    b.set(2, 6, PIECE(PAWN, WHITE));
    b.set(2, 7, PIECE(PAWN, WHITE));
    b.set(3, 0, PIECE(PAWN, WHITE));
    b.set(3, 2, PIECE(PAWN, BLACK));
    b.set(3, 3, PIECE(KNIGHT, WHITE));
    b.set(3, 5, PIECE(KNIGHT, WHITE));
    b.set(3, 6, PIECE(BISHOP, BLACK));
    b.set(4, 3, PIECE(PAWN, BLACK));
    b.set(5, 0, PIECE(PAWN, BLACK));
    b.set(6, 5, PIECE(PAWN, BLACK));
    b.set(6, 6, PIECE(PAWN, BLACK));
    b.set(6, 7, PIECE(PAWN, BLACK));
    b.set(7, 0, PIECE(ROOK, BLACK));
    b.set(7, 2, PIECE(ROOK, BLACK));
    b.set(7, 7, PIECE(KING, BLACK));
    
    state st{b};
    std::cout << st;
}
