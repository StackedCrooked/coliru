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
    std::cout << x[0]++ << "\n";
    std::cout << x[1]++ << "\n";
    std::cout << x[2]++ << "\n";

    X const& y = x;
    std::cout << y[0] << "\n";
    std::cout << y[1] << "\n";
    std::cout << y[2] << "\n";
}
