template <class T1, class T2>
class Foo{
public:
     Foo(T1 i, T2 j) {}
};

class Bar1 {};
class Bar2 {};

Bar1 bar1;
Bar2 bar2;

Foo<Bar1, Bar2> foo(bar1, bar2);

int main()
{}
