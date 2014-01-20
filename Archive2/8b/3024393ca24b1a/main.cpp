#include <iostream>

using namespace std;

struct michael {
    void talk() {cout << "michael talk" << endl;}
    void sing() {cout << "michael sing" << endl;}
};

struct mom {
    void talk() {cout << "mom talk" << endl;}
};

template <bool b>
struct MAKE_NOISE {
    template <typename T>
    static void make_noise(T t) {t.talk();}
};

template <>
struct MAKE_NOISE<true> {
    template <typename T>
    static void make_noise(T t) {t.sing();}
};

template <typename T>
struct SINGS {
    static const bool val = false;
};

template <>
struct SINGS<michael> {
    static const bool val = true;
};

template <typename T>
void noise(T t) {
    MAKE_NOISE<SINGS<T>::val>::make_noise(t);
}

int main() {    
    noise(michael());
    noise(mom());
}