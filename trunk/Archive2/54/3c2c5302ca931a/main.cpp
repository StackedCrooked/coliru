    #include <iostream>
    #include <sstream>
    
    int main()
    {
        {
            std::istringstream iss("1");
            std::cout << static_cast<bool>(iss) << iss.good() << iss.fail() << iss.bad() << iss.eof() << '\n';
            unsigned int u;
            iss >> u;
            std::cout << static_cast<bool>(iss) << iss.good() << iss.fail() << iss.bad() << iss.eof() << '\n';
        }
        {
            std::istringstream iss("-1");
            unsigned int u;
            iss >> u;
            std::cout << static_cast<bool>(iss) << iss.good() << iss.fail() << iss.bad() << iss.eof() << '\n';
        }
    }