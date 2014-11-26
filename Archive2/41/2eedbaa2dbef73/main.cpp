    #include <tr1/array>
    
    template<typename T>                struct plus_one_trait;
    template<typename T, std::size_t N> struct plus_one_trait< std::tr1::array<T,N> > {
        const static std::size_t value = N+1;
    };
    
    struct test {
        template<typename T, std::size_t N>
        void do_stuff( const std::tr1::array<T,N>& array
                     , std::size_t s = plus_one_trait< std::tr1::array<T,N> >::value ) {}
    };
    
    int main() {
        std::tr1::array<char,32> charr;
        test t;
        t.do_stuff(charr);
    }