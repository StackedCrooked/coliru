#include <cassert>
#include <tuple>

enum { invalid = -1 };
using SomeId = int;   // or any regular type with op== and op<
using SomeData = int; // or any regular type with op== and op<

struct MyFlag
{
    SomeId source_id; // INVALID_ID by default
    SomeData data;    // regular type

    friend bool operator==(MyFlag const& a, MyFlag const& b) 
    { return std::tie(a.source_id, a.data) == std::tie(b.source_id, b.data); }
     
    friend bool operator!=(MyFlag const& a, MyFlag const& b) 
    { return !(a == b); }
     
    friend bool operator<(MyFlag const& a, MyFlag const& b) 
    { return std::tie(a.source_id, a.data) < std::tie(b.source_id, b.data); }
     
    // similarly define >=, >, and <= in terms of !(a < b), (b < a) and !(b < a)
    
    friend bool id_equal_to(MyFlag const& a, MyFlag const& b)
    { return a.source_id == b.source_id; }    
};

int main()
{    
    auto const id = 0;
    auto const data_A = 1;
    auto const data_B = 2;
    
    MyFlag flag_a { id, data_A };
    MyFlag flag_b { id, data_B };
    
    assert( flag_a != flag_b );
    assert( id_equal_to(flag_a, flag_b) );
    assert( flag_a.data != flag_b.data );
    
    MyFlag flag = flag_b;
    assert( flag != flag_a );
    assert( id_equal_to(flag, flag_a) );
    assert( flag.data != flag_a.data );
    
    auto const id_x = invalid;
    const MyFlag flag_x = { id_x, data_A };
    flag = flag_x;
    assert( flag != flag_a );
    assert( id_equal_to(flag, flag_x) );
    assert( !id_equal_to(flag, flag_a) );
    assert( flag.data == flag_a.data );    
}
