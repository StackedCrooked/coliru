    #include <iostream>

    template<typename D>
    class Base {
    public:
        void test() {
            std::cout << "Base::test()" << std::endl;
        }

        void test2() {
            (static_cast<D*>(this))->test();
        }
    };

    class Derived : public Base<Derived> {
    public:
        void test() {
            std::cout << "Derived::test()" << std::endl;
        }
    };

    int main() {
        Derived d;
        d.test2();
        return 0;
    }
