#include <algorithm>
#include <array>

template<typename T, size_t N, size_t M=N>
struct matrix {
    typedef std::array<T, M> row_type;
    std::array<row_type, N> cells;

    row_type*       begin()       { return cells.begin(); }
    row_type*       end()         { return cells.end();   }
    row_type const* begin() const { return cells.begin(); }
    row_type const* end()   const { return cells.end();   }
};

template<size_t N, typename T=int>
T test()
{
    using std::begin;
    using std::end;
    typedef matrix<T, N, N*3+2> Mtx;
    Mtx the_matrix;

    size_t next_gen {};
    auto gen = [&](){ return next_gen++ * 3.14; };

    for(auto& row : the_matrix)
        std::generate(begin(row), end(row), gen);

    return std::accumulate(
            begin(the_matrix), end(the_matrix), T{},  
            [](T accum, typename Mtx::row_type& row) 
            { 
                return accum + std::accumulate(begin(row), end(row), T{}); 
            });
}

#include <iostream>
#include <string>

int main()
{
    std::cout << test<3, int>()    << "\n";
    std::cout << test<3, double>() << "\n";
}
