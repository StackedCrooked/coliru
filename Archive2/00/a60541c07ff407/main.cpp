#include <iostream>

constexpr auto get_str(void)
-> const char(&)[4] {   
    return { 'T', 'E', 'S', 'T' };
}

constexpr int sum(const char(&str)[4]){
    return str[0] + str[1] + str[2] + str[3];
}

int main(void){

    constexpr int s = sum(get_str());

    std::cout << s << std::endl;

    return 0;
}