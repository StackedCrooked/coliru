template<class... Visitors>
class Visited: public Visitors...
{
    public:
        template<class... Args>
        Visited(const Args&... args) : Visitors(args)... {}
};

struct A {};
struct B {};
struct C {};

int main()
{
    A a;
    B b;
    C c;
    Visited<A,B,C> v(a, b, c);
}
