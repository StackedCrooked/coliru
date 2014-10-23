class A
{
  public:
    virtual ~A() {}
};
class B : public A
{
  public:
    virtual ~B() {}
};
class C : public A
{
  public:
    virtual ~C() {}
};
template <typename T>
class AList
{
  public:
    void add(T* x){}
    // ...
};
template <typename T>
class E
{
  public:
    E(A* ptr) { /*...*/ }
    // ...
};

int main() {
    AList< E<A*> > list;
    list.add(E(new B));
    list.add(E(new C));
}