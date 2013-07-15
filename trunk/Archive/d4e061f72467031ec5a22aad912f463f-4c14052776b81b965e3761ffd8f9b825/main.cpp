#include <iostream>

using namespace std;

template <typename tag>
void func(const tag&);

struct First{};
First first;

template <>
void func(const First&){
    cout << "funcFirst" << endl;
}

struct Second{};
Second second;

template <>
void func(const Second&){
    cout << "funcSecond" << endl;
}

struct Third{};
Third third;

void func(const Third&){
    cout << "funcThird" << endl;
}

int main()
{
    func(first);
    func(second);
    func(third);
}
