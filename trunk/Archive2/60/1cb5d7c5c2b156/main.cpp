    #include <sstream>
    #include <string>

    int main() {
        std::stringstream ss("");
        std::string s;
        ss >> s;
        ss.exceptions(std::ios::failbit); // throws on all tested implementations
    }
