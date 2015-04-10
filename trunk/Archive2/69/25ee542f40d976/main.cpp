#include <iostream>
#include <type_traits>
using namespace std;

struct My_type
{
    void show () { 
        cout << "void show ()" << endl;
    }
    void show () const { 
        cout << "void show () const" << endl;
    }
};

template<class T>
struct MyTypeWrapper : std::remove_cv_t<T> {
    using Base = std::remove_cv_t<T>;
    using Base::Base;

    T&       get()       { return ref; }
    T const& get() const { return ref; }
    ~MyTypeWrapper() { ref.show(); }
private:
    T& ref = static_cast<T&>(*this);
};

int main()
{
    MyTypeWrapper<My_type> mt;
    MyTypeWrapper<My_type const> cmt;
}