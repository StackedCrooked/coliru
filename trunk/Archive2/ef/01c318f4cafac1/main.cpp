#include <iostream>
#include <functional>

template<class Func>
void print_1(Func f)
{
    std::cout << "Print_1: " << f() << '\n';
}


void print_2(const std::function<int()>& f)
{
    std::cout << "Print_2: " << f() << '\n';
}


class IFunc {
    public:
        virtual int operator() () const = 0;
};

void print_3(const IFunc& f)
{
    std::cout << "Print_3: " << f() << '\n';
}

int main()
{
    class F {
        public:
            F(int data) : data_(data) {}
            int operator() () { return data_; }
        private:
            int data_;
    };
    F f(10);
    print_1(f);
    print_2(f);
    
    class F3 : public IFunc {
        public:
            F3(int data) : data_(data) {}
            virtual int operator() () const { return data_; }
        private:
            int data_;
    };
    F3 f3(10);
    print_3(f3);
}
