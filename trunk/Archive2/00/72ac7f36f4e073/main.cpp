struct X {
    struct values { int a,b,c; } _v;

  private:
    template <typename This> 
        static auto& do_indexer(This& that, int i) {
            switch (i) {
                case 0: return that._v.a;
                case 1: return that._v.b;
                case 2: return that._v.c;
            }
            throw "OOPS"; // TODO
        }

  public:
    int &      operator[](int i)       { return do_indexer(*this, i); }
    int const& operator[](int i) const { return do_indexer(*this, i); }

    X(values v) : _v(v) {}
};

#include <iostream>
#include <typeinfo>

int main()
{
    X x {{ 7,42,-9 }};
    std::cout << typeid(x[0]).name() << "\t" << x[0]++ << "\n";
    std::cout << typeid(x[1]).name() << "\t" << x[1]++ << "\n";
    std::cout << typeid(x[2]).name() << "\t" << x[2]++ << "\n";

    X const& y = x;
    std::cout << typeid(y[0]).name() << "\t" << y[0] << "\n";
    std::cout << typeid(y[1]).name() << "\t" << y[1] << "\n";
    std::cout << typeid(y[2]).name() << "\t" << y[2] << "\n";
}
