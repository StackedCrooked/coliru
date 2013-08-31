#include <string>

template<class func_type> 
void generate(std::string& word, int length, const func_type& func) {
    for(char i='a'; i<='z'; ++i) {
        bool used = false;
        for(char c : word) {
            if (c==i) {
                used = true;
                break;
            }
        }
        if (used) continue;
        word.push_back(i);
        if (length==1) func(word);
        else generate(word, length-1, func);
        word.pop_back();
    }
}
template<class func_type> 
void generate(int length, const func_type& func) {
    std::string word;
    generate(word, length, func);
}

#include <iostream>
int main() 
{
    generate(3, [](const std::string&s){std::cout << s << '\n';});
}