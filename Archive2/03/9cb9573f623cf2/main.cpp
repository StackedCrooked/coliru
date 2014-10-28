#include <sstream>
#include <iostream>

int main() {
    std::istringstream ss("hello wello");
    std::string str;
    ss >> str;
    std::cout << str << '\n';
    std::cout << "peaking into: [" << (char)ss.peek() << "]\n";
    // this one should fail
    int x;
    ss >> x;
    std::cout << x << '\n';
    std::cout << "peaking into: [" << (char)ss.peek() << "]\n";
    // maybe you can clear it?
    ss.clear();
    ss.sync();
    std::cout << "peaking into: [" << (char)ss.peek() << "]\n";
    // cool
    ss >> str;
    std::cout << str << '\n';
    std::cout << "peaking into: [" << (char)ss.peek() << "]\n";
}