#include <iostream>
#include <array>
#include <cstdint>

#define REPORT(caption, expr) do {\
    do_report(caption, [](T x, T y) -> bool { return (expr); }, #expr); } while (false)

template <typename T> struct driver {
    static void run() {
        std::cout << "\n" << __PRETTY_FUNCTION__ << "\n";

        // the only two correct implementations:
        REPORT("MASTER"  , (x>3) && (x>y+1));
        REPORT("GOLF"    , x>3&x>y+1);
        REPORT("lookup"  , "000000000000000000000000111000111100"[x*6+y]-'0');

        // failing sometimes:
        REPORT("question", (x>3)&(x-y>1));
        REPORT("orlp0"   , x>3&x-y>1);
        REPORT("orlp2"   , ~y+x>2>>y);
        REPORT("orlp3"   , x*x-y*y>9);
        REPORT("orlp4"   , ~y>x/~3*x);
        REPORT("orlp5"   , -3>>y>y-x);
        REPORT("orlp6"   , ~y+x<<y>2);

        // failing always
        REPORT("orlp1"   , -x<~y>4>x);
    }
private:
    static void do_report(std::string const& caption, bool (*f)(T,T), char const* expression) {
        std::string r;
        for (T x = 0; x < 6; ++x) for (T y = 0; y < 6; ++y) r += f(x, y)?'1':'0';
        bool const correct = "000000000000000000000000111000111100" == r;
        std::cout << (correct?"OK\t":"ERR\t") << r << "\t" << caption << "\t" << expression << "\n";
    }
};


int main() {
    driver<int8_t>::run();
    driver<int16_t>::run();
    driver<int32_t>::run();
    driver<int64_t>::run();

    driver<uint8_t>::run();
    driver<uint16_t>::run();
    driver<uint32_t>::run();
    driver<uint64_t>::run();
}
