    #include <iostream>
    #include <typeinfo>

    class base
    {
    private:
        struct inner { char c_; };
        inner i_;
    public:
        virtual ~base() {}
        base(char c) : i_{c} {}
    protected:
        inner f() { return i_; }
    };

    class derived : public base
    {
    public:
        using base::base;
        void g()
        {
            // base::inner i = f(); Produces compilation failure, OK.
            auto i = f();            // Compiles!
            std::cout << i.c_ << '\n';
            std::cout << typeid(i).name() << '\n';
        }
    };

    int main()
    {
        derived d('a');
        d.g();
    }
