    #include <iostream>
    
    signed int s1 = -4;
    unsigned int u1 = 2;
    
    signed long int s2 = -4;
    unsigned int u2 = 2;
    
    signed long long int s3 = -4;
    unsigned long int u3 = 2;
    
    int main()
    {
        std::cout << (s1 + u1) << "\n"; // 4294967294
        std::cout << (s2 + u2) << "\n"; // -2 
        std::cout << (s3 + u3) << "\n"; // 18446744073709551614  
    }