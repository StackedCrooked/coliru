struct X{
    int f(){ return 0; }
    auto g() -> decltype(f()) { return f(); }
};

int main(){}