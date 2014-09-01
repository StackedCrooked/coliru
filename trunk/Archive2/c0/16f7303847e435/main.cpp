#include <iostream>
    template<class T, T... Ints>
    struct integer_seq {
        static constexpr std::size_t size() { return sizeof...(Ints); }
    };
    
    template<class T, T... Current>
    struct seq_holder {
        using next = seq_holder<T, Current..., sizeof...(Current)>;
        using intseq_type = integer_seq<T, Current...>;
    };
    
    template<class T, int Len>
    struct seq_builder{
        static_assert(Len > 0, "Length must be nonnegative");
        using type = typename seq_builder<T, Len-1>::type::next;
    };
    
    template<class T>
    struct seq_builder<T, 0>{
        using type = seq_holder<T>;
    };
    
    template<class T, T length>
    using make_int_sequence = typename seq_builder<T, length>::type::intseq_type;
    
    template<int FIRST, int LAST, class = make_int_sequence<int, LAST+1-FIRST>>
    struct Foo;
    
    template<int FIRST, int LAST, int... SEQ>
    struct Foo<FIRST, LAST, integer_seq<int, SEQ...>>
    {
        static constexpr int array[sizeof...(SEQ)] = {(FIRST+SEQ)...};
    };
    
    template<int FIRST, int LAST, int... SEQ>
    constexpr int Foo<FIRST, LAST, integer_seq<int, SEQ...>>::array[sizeof...(SEQ)];

int main(){
    for(int i : Foo<5, 10>::array) {
        std::cout << i << '\t';
    }
    std::cout << std::endl;
}