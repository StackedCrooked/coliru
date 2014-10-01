#include <iostream>
#include <type_traits>

using namespace std;

// a class initialised with an int that can't do it
struct A
{
    A(int a) : _a(a) {  }
    void report() const { std::cout << _a << std::endl; }
private:
    int _a;
};

// a class initialised with a string that can do it
struct B
{
    B(std::string s) : _b (move(s)) {  }
    void report() const { std::cout << _b << std::endl; }
    void do_it() { std::cout << "B did it with " << _b <<"!" << std::endl; }
private:
    string _b;
};

// a class initialised with an int that can do it
struct D
{
    D(int d) : _d(d) {  }
    void report() const { std::cout << _d << std::endl; }
    void do_it() { std::cout << "D did it with " << _d <<"!" << std::endl; }
private:
    int _d;
};

// a class initialised with a string that can't do it
struct E
{
    E(std::string s) : _e(move(s)) { }
    void report() const { std::cout << _e << std::endl; }
private:
    string _e;
};

// a function enabled only if T::do_it is a member function pointer
// the bool is there just to make this function more attractive to the compiler
// than the next one, below
template<class T>
auto do_it(T* t, bool)
-> typename std::enable_if<std::is_member_function_pointer<decltype(&T::do_it)>::value, void>::type
{
    t->do_it();
}

// a catch-all function called when do_it<T> is not valid
// the ... is less attractive to the compiler when do_it<T>(T&, bool) is available
template<class T>
void do_it(T*, ...)
{
}

// a compound class derived from any number of classes - I am so lazy I work hard at
// being lazy.
template<class...Templates>
struct C : public Templates...
{
    // construct from a parameter pack of arbitrary arguments
    // constructing each base class with one argument from the pack
    template<class...Args>
    C(Args&&...args)
    : Templates(std::forward<Args>(args))...
    {

    }

private:
    using expander = int[];
public:
    // disptach T::do_it for each valid T in base class list
    void do_it() {
        expander{ 0, (::do_it<Templates>(this, true), 0)...};
    }

    // dispatch T::report, which must exist for each base class
    void report() const {
        cout << "-- all base classes reporting:" << endl;
        expander{ 0, (Templates::report(), 0)...};
        cout << "-- all base classes reported" << endl;
    }
};

int main()
{
    C<A,B, D, E> c(10, "hello", 7, "goodbye");
    c.report(); // all base classes must report
    c.do_it(); // all base classes that can do_it, must.

   return 0;
}