#include <iostream>
#include <algorithm>
#include <cstring>

template <typename CharT, size_t Ndest>
void cp(CharT (&dest)[Ndest], CharT const *src){
    auto f = src, l = src + std::strlen(src);
    *(std::reverse_copy(f, l, dest)) = '\0';
}

#include <iostream>

int main()
{
    char str1[]   = "ppC";
    char str2[10] = "Witaj";

    std::cout << "Napis str2 "<< str2 << std::endl;
    cp(str2, str1);
    std::cout << "Napis str2 "<< str2 << std::endl;
    cp(str2,"CJP");
    std::cout << "Napis str2 "<< str2 << std::endl;
    return 0;
}
