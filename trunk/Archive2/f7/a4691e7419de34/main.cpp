// http://stackoverflow.com/questions/28652334/how-can-i-read-and-reset-bits-of-char
#include <cstdint>

#include <iostream>
#include <sstream>
#include <iomanip>

#include <array>
#include <memory>

enum class Reg {
    r0 = 0,
    r1,
    r2,
};

enum class Opcode {
    Add = 2,
    Sub = 3,
    Mul = 4,
    Div = 5,
};

class Byte {
    uint8_t _bits{0};
public:
    Byte() = default;
    Byte( int x ) : _bits(x) {}
    friend std::ostream & operator<< ( std::ostream & o, Byte const& b ) {
        std::stringstream ss;
        ss << "0x" << std::hex << std::setw(2) << std::setfill('0') << unsigned(b._bits);
        return o << ss.str();
    }
};

template< size_t NBYTES >
struct InstructionBase {
    std::array<Byte,NBYTES> _bytes;
public:
    template<typename ...T>
    InstructionBase(T&&...t):_bytes{ std::forward<T>(t)... } {}
    Byte operator[] ( size_t x ) const { return _bytes[x]; }
};

struct Inst_Add : public InstructionBase<2> {
    Inst_Add( Reg r, int8_t imm ) : InstructionBase{ (unsigned(Opcode::Add)<<5) | (unsigned(r)<<0 ), imm } {}
};

template < typename T >
class PhysicalMemory {
    static constexpr size_t MEM_SIZE = size_t(1) << 17;  // power of 2, 128 KB
    using Dram = std::array<T,MEM_SIZE>;
    std::unique_ptr<Dram> _raw{new Dram};
    Dram & _mem = *_raw;
public:
    template< size_t N >
    void store ( size_t adr, InstructionBase<N> const& inst ) {
        for(size_t i=0; i<N; ++i) _mem[adr+i] = inst[i];
    }
    T & operator[] ( size_t x ) { return _mem[x]; }
};


int main(int argc, const char* argv[]) {
    PhysicalMemory<Byte> mem;
    mem.store( 3, Inst_Add( Reg::r1, -7 ) );
    for(size_t i=0; i<10; ++i)
        std::cerr << i << ":" << mem[i] << std::endl;
    return 0;
}