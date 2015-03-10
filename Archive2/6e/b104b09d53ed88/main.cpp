template <typename T>
struct Base {
    T value;
    
    Base() {}
    
    template <typename... Args>
    void var(Args... args) {}
};

template <typename F>
struct Derived : public Base<F> {
    template <typename... Args>
    void forward_var(Args... args) {
        Base<F>::var(args...);
    }
    
    Derived() {
        forward_var<int,int,int>(1,2,3);
        
    }
};

int main()
{
    Derived<int> d;

    return 0;  
}
