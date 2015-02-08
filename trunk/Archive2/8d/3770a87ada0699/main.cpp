#include <cstdint>
#include <iostream>
using std::cout;
using std::endl;

typedef unsigned char  uchar;   //!< unsigned char
typedef unsigned short ushort;  //!< unsigned short
typedef unsigned int   uint;    //!< unsigned integer

typedef std::int8_t    int8;
typedef std::int16_t   int16;
typedef std::int32_t   int32;
typedef std::int64_t   int64;

typedef std::uint8_t   uint8;   //!< 8-bit unsigned integer
typedef std::uint16_t  uint16;  //!< 16-bit unsigned integer
typedef std::uint32_t  uint32;  //!< 32-bit unsigned integer
typedef std::uint64_t  uint64;  //!< 64-bit unsigned integer

typedef uint8          byte;

# define LIKELY(COND)   __builtin_expect((COND), 1)
# define UNLIKELY(COND) __builtin_expect((COND), 0)

class IP4 {
public:
  constexpr explicit
  IP4(uint32 addr, uint16 port=0) noexcept
  : addr_(addr)
  , port(port)
  {}
  __attribute__((used))
  friend bool operator<=(const IP4& lhs, const IP4& rhs) noexcept {
    bool result;
    __asm__(
    "cmpw %1, %2\n\t"
    "sbbl %3, %4\n\t"
    "setae %0"
    :"=rm,rm"(result)
    :"ir,rm"(lhs.port),"rm,r"(rhs.port),"g,g"(lhs.addr_),"r,r"(rhs.addr_)
    :"cc");
    return result;
  }
private:
  uint32 addr_;
public:
  uint16 port;
};

int main() {
  IP4 a{0x7f000002, 0};
  IP4 b{0x7f000002, 1};
  cout << std::boolalpha << (a <= b) << endl;
  return 0;
}
