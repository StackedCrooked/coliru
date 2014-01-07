#include <iostream>
using namespace std;

struct michael {
    void speak() {cout << "michael speak" << endl;}
    void sing() {cout << "michael sing" << endl;}
};

struct david {
    void speak() {cout << "david speak" << endl;}
};

template <bool b>
struct NOISE {
    template <typename T> 
    static void make_noise(T t) {t.speak();} 
};

template <>
struct NOISE<true> {
    template <typename T>
    static void make_noise(T t) {t.sing();}
};

template <typename T> 
struct SINGER {
    static const bool val = false;
};

template <> 
struct SINGER<michael> {
    static const bool val = true;
};

template <typename T>
void make_noise(T t) {
    NOISE<SINGER<T>::val>::make_noise(t);
}

int main() {
    make_noise(david());
    make_noise(michael());
}