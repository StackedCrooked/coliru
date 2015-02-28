#include<iostream>
#include<vector>
#include<string>
#include<memory>

int main() {
    std::vector<std::string> v;

    v.push_back("abc");

//    std::string& x = v[0];
    std::unique_ptr<std::string> xp(v.data());
    std::cout << x << std::endl;
    
    v.push_back("b");

   std::cout << x;
}