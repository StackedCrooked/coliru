template <typename T>
struct Base {
    T value;
    
    Base() {}
    
    template <typename... Args>
    void var(Args... args) {}
};

template <typename F>
struct Derived : public Base<F> {
    Derived() {
        Base<F>::var(1,2,3);
    }
};

int main()
{
    Derived<int> d;

    return 0;  
}
