    #include <iostream>
    #include <sstream>
    
    int main()
    {
        std::istringstream iss("-89");
        std::cout << static_cast<bool>(iss) << iss.good() << iss.fail() << iss.bad() << iss.eof() << '\n';
        unsigned int u;
        iss >> u;
        std::cout << static_cast<bool>(iss) << iss.good() << iss.fail() << iss.bad() << iss.eof() << '\n';
        std::cout << u << std::endl;
        std::cout << static_cast<int>(u) << std::endl;
        
        return 0;
    }
    