#include <iostream>
#include <memory>

class Something
{
    class Something_private;
    std::unique_ptr<Something_private> something;
public:
    Something();
    ~Something();
    int work_a();
    int work_b(const char *str);
};

int main()
{
    Something something;
    
    int x= something.work_a();
    
    std::cout << x << std::endl;
    
    return 0;
}

// Another  File:

class Something::Something_private
{
    int x;
    public:
    Something_private():x(0){}
    inline int work_a() { return ++x; }
};

Something::Something():
    something(new Something_private) 
{

}

Something::~Something() 
{ 

}

int Something::work_a() 
{
      return something->work_a();
}
