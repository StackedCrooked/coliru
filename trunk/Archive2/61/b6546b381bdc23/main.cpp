#include <iostream>
#include <memory>
 
struct Foo { int i; };
void foo_deleter(Foo * p)
{
    std::cout << "foo_deleter called!\n";
    delete p;
}
 
int main()
{
    std::shared_ptr<int> aptr;
 
    {
        // create a shared_ptr that owns a Foo and a deleter
        auto foo_p = new Foo;
        std::shared_ptr<Foo> r(foo_p, foo_deleter);
        aptr = std::shared_ptr<int>(r, &r->i); // aliasing ctor
        // aptr is now pointing to an int, but managing the whole Foo
    } // r gets destroyed (deleter not called)
 
    // obtain pointer to the deleter:
    if(auto del_p = std::get_deleter<void(*)(Foo*)>(aptr))
    {
        std::cout << "shared_ptr<int> owns a deleter\n";
        if(*del_p == foo_deleter)
            std::cout << "...and it equals &foo_deleter\n";
    } else
        std::cout << "The deleter of shared_ptr<int> is null!\n";
} // deleter called here