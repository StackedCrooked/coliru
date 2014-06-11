#include <iostream>

template<char...cs> struct compile_time_string 
{static constexpr char str[sizeof...(cs)+1] = {cs...,'\0'};};
template<char...cs>
const char compile_time_string<cs...>::str[sizeof...(cs)+1];

template<char...cs> struct compile_time_stringbuilder 
{typedef compile_time_string<cs...> string;};
//remove leading spaces from stringbuilder
template<char...cs> struct compile_time_stringbuilder<' ', cs...>
{typedef typename compile_time_stringbuilder<cs...>::string string;};



template<char...cs, class...Ts> 
compile_time_stringbuilder<cs...,'\n'> concatenate_compile_time_format_string(compile_time_stringbuilder<cs...>);
template<char...cs, class...Ts> 
auto concatenate_compile_time_format_string(compile_time_stringbuilder<cs...>,int,Ts...args)
-> decltype(concatenate_compile_time_format_string(compile_time_stringbuilder<cs...,' ','%','d'>(),args...));
template<char...cs, class...Ts> 
auto concatenate_compile_time_format_string(compile_time_stringbuilder<cs...>,const char*,Ts...args)
-> decltype(concatenate_compile_time_format_string(compile_time_stringbuilder<cs...,' ','%','s'>(),args...));
template<char...cs, class...Ts> 
auto concatenate_compile_time_format_string(compile_time_stringbuilder<cs...>,double,Ts...args)
-> decltype(concatenate_compile_time_format_string(compile_time_stringbuilder<cs...,' ','%','f'>(),args...));

template<class...Ts>
constexpr const char* build_compile_time_format_string()
{
    using compile_time_stringbuilder = decltype(concatenate_compile_time_format_string(compile_time_stringbuilder<>(),std::declval<Ts>()...));
    using compile_time_string = typename compile_time_stringbuilder::string;
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