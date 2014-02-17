#include <iostream>
#include <vector>
#include <algorithm>

template<class Arg>
bool checkStrings(std::vector<std::string> &v, Arg const& arg)
{   
    bool ret = std::find(v.begin(), v.end(), arg) != v.end(); 
    std::cout << arg << " " << std::boolalpha << ret << std::endl;
    return ret;
}

template<class...Args>
bool checkStrings(std::vector<std::string> &v, Args const&... args) {
    std::vector<bool> tf { checkStrings(v, args)... };
    return std::all_of(tf.begin(), tf.end(), [] (bool i) { return i; });
}

int main(void)
{
    std::vector<std::string> v {"hello", "world", "blah"};
    std::cout << std::boolalpha << checkStrings(v, "hello", "world", "blah", "baz") << std::endl;
}
