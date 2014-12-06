#include <memory>
#include <vector>
#include <algorithm>
#include <iostream>
//#include <iterator>

 class Foo
 {
     public:
        ~Foo()
        {
            std::cout << "Foo dtor" << std::endl;
        }
 };

typedef std::unique_ptr<Foo> Ptr;
typedef std::vector<Ptr> Vector;

class Bar
{
    public:
        void add(Foo * foo)
        {
            m_v.push_back(Ptr(foo));
        }
        
    private:
        Vector m_v;
};

int main()
{
    // Ptr p1(new Foo);

    // std::cout << "Foo exists: " << static_cast<bool>(p1) << std::endl;
    // Vector v;
    // v.push_back(std::move(p1));
    // v.clear();
    // std::cout << "Foo exists: " << static_cast<bool>(p1) << std::endl; //foo is gone
    
    Foo * rawPtr = new Foo;
    {
        Bar bar;
    	bar.add(rawPtr);
    }
    std::cout << "foo is gone, can't use rawPtr" << std::endl;
}
