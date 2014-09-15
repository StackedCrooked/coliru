#include <iostream>
using namespace std;

template <typename T>
class Base {
    public:
        Base (const T& t) : value(t) {}
        void printValue () {
            cout << value << endl;
        }

    protected:
        T value;
};

template <typename T>
class Derived: public Base<T> {
    public:
        Derived (const T& t) : Base<T>(t) {}

        void setValue (const T& t) {
            this->value = t;
        }
};

template <>
class Derived<int> : public Base<int> {
    public:
        Derived(const int& t) : Base<int>(t) {}
        void increment () {
            this->value++;
        }
};

int main()
{
    Derived<int> d(42);
    d.increment();
}