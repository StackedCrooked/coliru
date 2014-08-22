#include <iostream>

using std::cout; using std::endl;

template <class T>
struct do_get {
    static T get(int i) { cout << "base" << endl; return T(); }
};

template <>
struct do_get<bool> {
    static bool get(int i) {cout << "bool" << endl; return false; }
};

template <class T>
struct do_get<T*> {
    static T* get(int i) { cout << "pointer" << endl; return nullptr;}
};

template <class T>
T Get(int i) { return do_get<T>::get(i); }

int main(int argc, const char* argv[])
{
    Get<int>(10);
    Get<bool>(20);
    Get<int *>(30);

    return 0;
}