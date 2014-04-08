#include <memory>
#include <vector>

class Foo
{
public:
     explicit operator bool() const
     { printf("Bool\n"); return true; }
     
     operator int() const
     { printf("int\n"); return 0; }
     
     bool operator ()() const
     { printf("()\n"); return false; }
};

int main()
{
    Foo foo;
    if(foo)
    {
        printf("yes\n");
    }
    else
    {
        printf("no\n");
    }
    
    return 0;
}