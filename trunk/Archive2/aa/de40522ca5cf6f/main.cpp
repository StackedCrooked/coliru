#include <utility>
#include <tuple>

struct evil {
    evil&& operator*(){return std::move(*this);}
    evil operator+(){return *this;}
    evil const& operator!(){return *this;}
    evil& operator~(){return *this;}
};
int main() {
    evil e;
    auto&  a0 = !e;
    auto&& b0 = !e;
    static_assert( std::is_same< decltype(a0), decltype(b0) >{}, "fail" );
    //auto&  a1 = *e;
    auto&& b1 = *e;
    //static_assert( std::is_same< decltype(a1), decltype(b1) >{}, "fail" );
    //auto&  a2 = +e;
    auto&& b2 = +e;
    //static_assert( std::is_same< decltype(a2), decltype(b2) >{}, "fail" );
    auto&  a3 = ~e;
    auto&& b3 = ~e;
    static_assert( std::is_same< decltype(a3), decltype(b3) >{}, "fail" );
    
    (void)std::tie(a0, /*a1, a2,*/ a3, b0, b1, b2, b3);
}