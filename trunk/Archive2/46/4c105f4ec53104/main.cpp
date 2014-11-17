    #include <sstream>
    #include <string>

    int main() {
        std::stringstream ss("");
        ss.exceptions(std::ios::failbit);
        std::string s;
        ss >> s; // not throwing an exception under libc++
    }
