#include <string>
#include <sstream>

struct stringFromIntInt {
    template <typename F> stringFromIntInt(F f) : storage(new _storage<F>(f)) { }

    ~stringFromIntInt() { delete storage; }

    std::string operator()(int a, int b) {
        return storage->call(a, b);
    }

  private:
    stringFromIntInt(stringFromIntInt const&);
    stringFromIntInt& operator=(stringFromIntInt const&);

    struct base { 
        virtual std::string call(int, int) = 0;
        virtual ~base() {}
    };
    template <typename F> struct _storage : base {
        _storage(F f) : f(f) {}
        F f;
        std::string call(int a, int b) { return f(a,b); }
    };

    base *storage;
};

struct AddX {
    template <typename> struct  result { typedef std::string type; };

    std::string operator()(int a, int b) const { 
        std::ostringstream oss;
        oss << (a + b);
        return oss.str();
    }
};

std::string free_function_addx(int a, int b) {
    std::ostringstream oss;
    oss << (a + b);
    return oss.str();
}

#include <iostream>

int main() {
    AddX adder;
    stringFromIntInt foo1(adder);
    stringFromIntInt foo2(free_function_addx);

    std::cout << "foo1(1, 999): " << foo1(1, 999) << "\n";
    std::cout << "foo2(2, 998): " << foo2(2, 998) << "\n";
}
