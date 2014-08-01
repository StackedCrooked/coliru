template <class A, template <A*> class B, A* ptr>
struct Foo : B<ptr> {};

template <class, class AA, template <AA*> class BB, AA* ptr>
using Bar = Foo<AA, BB, ptr>;

class MyClass {} myClass_instance;
template <MyClass*> class MyTemplateClass {};

int main()
{
    Bar<int, MyClass, MyTemplateClass, &myClass_instance> x;
    (void)x;
}
