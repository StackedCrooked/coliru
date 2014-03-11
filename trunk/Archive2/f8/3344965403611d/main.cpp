    #include <array>
    
    constexpr int f()
    {
        return printf("a side effect!\n");
    }
    
    int main()
    {
        std::array<int, f()> a;
 
    }