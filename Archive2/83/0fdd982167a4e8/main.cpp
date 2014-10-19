class A
{
    int foo() {return 1;}
    void goo( decltype(((A*)nullptr)->foo()) i) {}
};
