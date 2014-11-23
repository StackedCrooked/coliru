#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <functional>
#include <chrono>
#include <set>
#include <algorithm>
#include <sys/time.h>
#include <sys/time.h>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
    std::string zahlen_base = "+-*/";
do{
    std::cout<<zahlen_base<<std::endl;

} while (std::next_permutation(zahlen_base.begin(), zahlen_base.end()));
}