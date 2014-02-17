#include <iostream>
#include <memory>
#include <utility>

using namespace std;


//http://en.cppreference.com/w/cpp/utility/forward

struct A {
public: // if switch struct --> class
    A(int&& n)                  { cout << "rvalue Construct overload, n=" << n << endl; }
    A(const int& n)             { cout << "lvalue Construct overload, n=" << n << endl; }
    //+2: unused
    A& operator=(int&& n)       { cout << "rvalue Assigning overload, n=" << n << endl; return *this; }
    A& operator=(const int& n)  { cout << "lvalue Assigning overload, n=" << n << endl; return *this; }
    
    A(void) {}
};
 
class B {
public:
    template<class T1, class T2, class T3>
    B(T1&& t1, T2&& t2, T3&& t3) :
        a1_(forward<T1>(t1)),
        a2_(forward<T2>(t2)),
        a3_(forward<T3>(t3))
    {}
    
private:
    A a1_, a2_, a3_;
};

template<class T, class... U>
unique_ptr<T> make_unique(U&&... u)
{
    return unique_ptr<T>(new T(forward<U>(u)...));
}
 

// http://stackoverflow.com/questions/12030538/calling-a-function-for-each-variadic-template-argument-and-an-array

struct X : A {
public:
    X(void) { cout << "yep yep" << endl; }
};

template<class T>
void f(X& p1, T const& p2){ cout << p2 << endl; }

void g(X const*, unsigned){}

template<unsigned... Indices>
struct indices{
  using next = indices<Indices..., sizeof...(Indices)>;
};
template<unsigned N>
struct build_indices{
  using type = typename build_indices<N-1>::type::next;
};
template <>
struct build_indices<0>{
  using type = indices<>;
};
template<unsigned N>
using IndicesFor = typename build_indices<N>::type;

template<unsigned N, unsigned... Is, class... Args>
void f_them_all(X (&xs)[N], indices<Is...>, Args... args){
  int unused[] = {(f(xs[Is], args), 1)...};
  (void)unused;
}

template<class... Args>
void h(Args... args){
  static constexpr unsigned nargs = sizeof...(Args);
  X xs[nargs];
  f_them_all(xs, IndicesFor<nargs>(), args...);
  g(xs, nargs);
}


int main(void)
{
    h(1,2,3,4,5);
    return EXIT_SUCCESS;
    
    cout << 'A' << endl;
    auto pA(make_unique<A>(2));                 // rvalue
    int i = 1;
    pA = make_unique<A>(i);                     // lvalue
 
    cout << 'B' << endl;
    auto pB(make_unique<B>(i, i++, move(i)));   // rvalue, lvalue, rvalue
}
