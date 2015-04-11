#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>

struct user {
    std::string name;
    float time;
    
    friend std::istream &operator>>(std::istream &is, user &r) { 
        std::getline(is, r.name, ':');
        is >> r.time;
        is.ignore(100, '\n');
        return is;
    }
    
    friend std::ostream &operator<<(std::ostream &os, user const &r) { 
        return os << r.name << ": " << (int)r.time;
    }
};

int main () {
    std::ifstream file("input.txt");

    std::vector<user> users{std::istream_iterator<user>(file), std::istream_iterator<user>()};

    std::sort(users.begin(), users.end(), [](user const &a, user const &b){ return a.time < b.time; });
    std::copy(users.rbegin(), users.rend(), std::ostream_iterator<user>(std::cout, "\n"));
}
