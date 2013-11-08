#include <iostream>

namespace my_matrix_library
{
    template<int N, int M>
    struct matrix
    {
        static constexpr int R() { return N; }
        static constexpr int C() { return M; }
        int data[N][M];
    };
    
    template<class T>
    T operator+(T l, T const& r)
    {
        static_assert(std::is_base_of<matrix<T::R(), T::C()>, T>{}, "name lookup error; template too greedy");
        
        for(int i = 0; i < l.R(); ++i)
        {
            for(int j = 0; j < l.C(); ++j)
            {
                l.data[i][j] += r.data[i][j];
            }
        }
        
        return l;
    }
    
    template<int N, int M>
    void print(matrix<N, M> const& p)
    {
        for(int i = 0; i < p.R(); ++i)
        {
            for(int j = 0; j < p.C(); ++j)
            {
                std::cout << p.data[i][j] << ", ";
            }
            std::cout << "\n";
        }
    }
    
    template<int N>
    struct vector : matrix<1, N>
    {
        template<class... T>
        vector(T&&... args) : matrix<1,N>{{{args...}}} {}
        
        // not sure why I need those; the above is NOT considered a move- or copy-ctor o.O
        vector(vector&) = default;
        vector(vector&&) = default;
        
        void special() { std::cout << "I'm a vector!\n"; }
    };
}

int main()
{
    my_matrix_library::vector<5> v0 = {1,2,3,4,5};
    my_matrix_library::vector<5> v1 = {5,4,3,2,1};
    
    auto v2 = v0 + v1;
    v2.special();
    
    print(v2);
}