#include <iostream>

template<char...cs> struct compile_time_string 
{static constexpr char str[sizeof...(cs)+1] = {cs...,'\0'};};
template<char...cs>
const char compile_time_string<cs...>::str[sizeof...(cs)+1];



template<char...cs, class...Ts> 
compile_time_string<cs...> build_compile_time_format_string(compile_time_string<cs...>);
template<char...cs, class...Ts> 
auto build_compile_time_format_string(compile_time_string<cs...>,int,Ts...args)
-> decltype(build_compile_time_format_string(compile_time_string<cs...,'%','d',' '>(),args...));
template<char...cs, class...Ts> 
auto build_compile_time_format_string(compile_time_string<cs...>,const char*,Ts...args)
-> decltype(build_compile_time_format_string(compile_time_string<cs...,'%','s',' '>(),args...));
template<char...cs, class...Ts> 
auto build_compile_time_format_string(compile_time_string<cs...>,double,Ts...args)
-> decltype(build_compile_time_format_string(compile_time_string<cs...,'%','f',' '>(),args...));

template<class...Ts>
constexpr const char* build_compile_time_format_string()
{
    using compile_time_string = decltype(build_compile_time_format_string(compile_time_string<>(),std::declval<Ts>()...));
    return compile_time_string::str;
}
    

template<typename T, class...Args>
int println(T arg, Args...args) {
    constexpr const char* formatString = build_compile_time_format_string<Args...>();
    std::cout << formatString;
    return 1;
}

int main() {
    println(nullptr, 2, "HI", -3.4);
}