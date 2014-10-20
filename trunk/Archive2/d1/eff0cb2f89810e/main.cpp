#include <iostream>
#include <string>
#include <cstdlib>

namespace Sandbox {
    class A {
    public:
        A (int i) : _x (i) { }
    private:
        int _x;
    };

    class B {
    public:
        B (const char* m) : _m (m), _a (std::atoi (m)) { }

        /*
         * This one shall be supported.
         */ 
        operator const A& () {
            return _a;
        }
    private:
        /*
         * This one shall be not supported.
         * If this one is disabled both desired and undesired conversions pass the compilation.
         */ 
        operator A& ();

        const std::string _m;
        const A _a;
    };
}

int main () {
    Sandbox::A a (1973);
    Sandbox::B b ("1984");

    /*
     * This is the undesirable cast and it shall fail to compile.
     */
    (Sandbox::A&)b;
    /*
     * This is the desirable cast and it shall pass the compilation.
     */
    (const Sandbox::A&)b;

    return 0;
}