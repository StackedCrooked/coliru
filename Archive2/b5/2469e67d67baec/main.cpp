    #include <iostream>
    
    int main()
    {
       double a = 1, b = 1e100, c= 1e100, d= 1, c2 = .1, d2 = -.1, b2 = 1;
       
       std::cout << ( a + b2 + c2 + d2 - c2 == a + b2 + c2 + (d2 - c2)) << "\n"
        << ( a + b2 + c + d - c == a + b2 + d) << "\n"
        << ( a == a + b -b);
    }