#include <boost/ptr_container/ptr_vector.hpp>

struct X {
    X(int i) : _i(i)         { std::cout << __PRETTY_FUNCTION__ << "(" << i << ")" << "\n"; }
    X(X && x) : _i(x._i)     { std::cout << __PRETTY_FUNCTION__ << "(" << x << ")" << "\n"; }
    X(X const& x) : _i(x._i) { std::cout << __PRETTY_FUNCTION__ << "(" << x << ")" << "\n"; }
    ~X()                     { std::cout << __PRETTY_FUNCTION__ << "\n"; }

    void* operator new(size_t n) {
         std::cout << __PRETTY_FUNCTION__ << "(" << n << ")" << "\n";
         return ::operator new(n);
    }

    void operator delete(void* px) {
         std::cout << __PRETTY_FUNCTION__ << "\n";
         return ::operator delete(static_cast<X*>(px));
    }

    X& operator=(X const& x) { 
        _i = x._i;
        std::cout << __PRETTY_FUNCTION__ << "(" << x << ")" << "\n"; 
        return *this;
    }

    X& operator=(X && x) { 
        _i = x._i;
        std::cout << __PRETTY_FUNCTION__ << "(" << x << ")" << "\n"; 
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, X const& x) {
        return os << "X[" << x._i << "]";
    }
    private: int _i;
};

int main()
{
    boost::ptr_vector<X> v;
    v.push_back(new X(1));
    v.push_back(new X(2));
    v.push_back(new X(3));
    v.push_back(new X(4));

    for (auto& p : v)
        std::cout << p << " ";

    std::cout << "\n===============================\nswapping v[1] and v[2]:\n";

    using std::swap;
    swap(v[1], v[2]);

    std::cout << "\n===============================\n";

    for (auto& p : v)
        std::cout << p << " ";
}
