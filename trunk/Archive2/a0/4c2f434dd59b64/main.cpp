//Here's a little C++1y solution --- I think I LOVE C++1y.

    #include <utility>
    
    template<int N>
    struct c_string
    {
        int length;
        char str[N+1];
        
        constexpr explicit c_string(int p_length)
            : length(p_length), str{}
        {}
    };
    
    template<int M>
    constexpr auto make_c_string(char const (&str)[M])
    {
        c_string<M-1> ret{M-1};
        for(int i = 0; i < M; ++i)
        {
            ret.str[i] = str[i];
        }
        return ret;
    }
    
    template<int N, int M>
    constexpr auto join(c_string<N> const& x, c_string<M> const& y)
    {
        c_string<N+M> ret{x.length + y.length};
        
        for(int i = 0; i < x.length; ++i)
        {
            ret.str[i] = x.str[i];
        }
        for(int i = 0; i < y.length; ++i)
        {
            ret.str[i+x.length] = y.str[i];
        }
        
        ret.str[N+M] = '\0';
        
        return ret;
    }
    
    template<int N, int M>
    constexpr auto operator+(c_string<N> const& x, c_string<M> const& y)
    {
        return join(x, y);
    }
    
    
    template<class T>
    constexpr void c_swap(T& x, T& y)
    {
        T tmp( std::move(x) );
        x = std::move(y);
        y = std::move(tmp);
    }
    
    // from http://en.cppreference.com/w/cpp/algorithm/reverse
    template<class I>
    constexpr void reverse(I beg, I end)
    {
        while(beg != end && beg != --end)
        {
            c_swap(*beg, *end);
            ++beg;
        }
    }

//Now the `constexpr itoa`:

    #include <limits>
    
    template<class T>
    constexpr auto c_abs(T x)
    {
        return x < T{0} ? -x : x;
    }
    
    template<class T>
    constexpr auto ntoa(T n)
    {
        c_string< std::numeric_limits<T>::digits10 + 1 > ret{0};
        int pos = 0;
        
        T cn = n;
        do
        {
            ret.str[pos] = '0' + c_abs(cn % 10);
            ++pos;
            cn /= 10;
        }while(cn != T{0});
        
        if(n < T{0})
        {
            ret.str[pos] = '-';
            ++pos;
        }
        
        ret.str[pos] = '\0';
        ret.length = pos;
        
        reverse(ret.str, ret.str+ret.length);
        return ret;
    }

//We can then simplify the usage:

    #include <type_traits>
    
    // not supported by the libstdc++ at coliru
    //template<class T, class = std::enable_if_t< std::is_arithmetic<T>{} >>
    template<class T, class = typename std::enable_if<std::is_arithmetic<T>{}>::type>
    constexpr auto to_c_string(T p)
    {
        return ntoa(p);
    }
    template<int N>
    constexpr auto to_c_string(char const (&str)[N])
    {
        return make_c_string(str);
    }
    
    template<class T, class U, class... TT>
    constexpr auto to_c_string(T&& p0, U&& p1, TT&&... params)
    {
        return   to_c_string(std::forward<T>(p0))
               + to_c_string(std::forward<U>(p1), std::forward<TT>(params)...);
    }

//And a usage example:

    #include <iostream>
    
    int main()
    {
        constexpr auto res = to_c_string(42," is the solution, or is it ",-21,"?");
        
        std::cout << res.str;
    }