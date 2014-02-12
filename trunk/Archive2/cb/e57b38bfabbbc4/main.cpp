    #include <iostream>
     
    template<typename T, typename U>
    T const& min(T const& x, U const& y)
    {
    return x < y ? x : y;
    }
     
    int main()
    {
    std::cout << ::min(10.9, -9);
     
    return 0;
    }