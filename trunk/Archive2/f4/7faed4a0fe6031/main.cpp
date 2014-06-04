struct HasBuzz
{
    void buzz() const {}
};

struct NoBuzz {};

template <typename T>
auto foo(T&& t)
    -> decltype(void(t.buzz()), void())
{
    t.buzz();
}

void foo(NoBuzz const&){}

int main()
{
    foo(HasBuzz{});
    foo(NoBuzz{});
}
