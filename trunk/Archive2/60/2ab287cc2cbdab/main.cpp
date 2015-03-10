struct Base {
    int value;
    
    Base() {}
    
    template <typename... Args>
    void var(Args... args) {}
};

template <typename F>
struct Derived : public Base {
    Derived() {
        Base::var<int,int,int>(1,2,3);
    }
};

int main()
{
    Derived<int> d;

    return 0;  
}
