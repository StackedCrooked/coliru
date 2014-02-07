    int main()
    {
        constexpr int x1 =  1 << 33 ; //Assuming 32-bit int
        constexpr int x2 =  1 << -1 ;
        constexpr int x3 =  -1 << 1 ;
        constexpr int x4 =  1 >> 33 ; //Assuming 32-bit int
        constexpr int x5 =  1 >> -1 ;
    }