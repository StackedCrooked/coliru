#include <set>
#include <iostream>
#include <cstdlib>

class NewDeleteMismatchDetector {
    static std::set<void*> nonarrays;
    static std::set<void*> arrays;
 public:
    static void* operator new(std::size_t sz)
    {   
        return *nonarrays.insert(::operator new(sz)).first;
    }
    static void* operator new[](std::size_t sz)
    {   
        return *arrays.insert(::operator new[](sz)).first;
    }
    static void operator delete(void* ptr)
    {   
        if(nonarrays.erase(ptr)) {
            ::operator delete(ptr);
        } else {
            std::cerr << "attempting to delete a pointer that was not allocated with new\n";
            std::abort();
        }
    }
    static void operator delete[](void* ptr)
    {   
        if(arrays.erase(ptr)) {
            ::operator delete[](ptr);
        } else {
            std::cerr << "attempting to delete[] a pointer that was not allocated with new[]\n";
            std::abort();
        }
    }
};
std::set<void*> NewDeleteMismatchDetector::nonarrays;
std::set<void*> NewDeleteMismatchDetector::arrays;

class Foo : public NewDeleteMismatchDetector
{
};

int main()
{
    Foo* f = new Foo;
    delete f; // ok

    Foo* f2 = new Foo[10];
    delete[] f2; // ok

    Foo* f3 = new Foo[10];
    delete f3; // abort
}