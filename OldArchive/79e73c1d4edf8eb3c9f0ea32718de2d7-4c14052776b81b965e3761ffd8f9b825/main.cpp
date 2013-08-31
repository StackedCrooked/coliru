#include <iostream>

using namespace std;

template <typename en>
void func(const en&){}

struct First{};
First first;
struct Second{};
Second second;

template <>
void func(const First&){
    cout << "funcFirst" << endl;
}

template <>
void func(const Second&){
    cout << "funcSecond" << endl;
}

int main()
{
    func(first);
    func(second);
}
