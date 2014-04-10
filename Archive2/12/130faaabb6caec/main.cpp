namespace N {
    struct T {};
    auto f = [](const T&) {};
    
    template <int N>
    void g(const T&) {}
}

int main()
{
    f((N::T()));
    g<3>((N::T()));
}