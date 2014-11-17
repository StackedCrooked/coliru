    #include <sstream>
    #include <string>
    #include <iostream>

    int main() {
        std::stringstream ss("");
        std::string s;
        ss >> s;
        std::cout << ss.fail() << '\n'; // prints '1' for all tested implementations
    }
