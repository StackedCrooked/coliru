#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

int string_size_check(const std::vector<std::string> &v, unsigned int size){
    return std::count_if(v.begin(), v.end(), [size] (std::string &s)->bool { return s.size() > size; });
}

int main() {
    std::vector<std::string> v = { "abc", "abcd", "abcde", "abcdef", "abcdefg", "abcdefg" };
    std::cout << string_size_check(v, 6);
}