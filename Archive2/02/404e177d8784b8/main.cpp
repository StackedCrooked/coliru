#include <iostream>
#include <stdexcept>

class Something
{
    class Something_private;
    Something_private* something;
public:
    Something();
    ~Something();
    int work_a();
    int work_b(const char *str);
};

void run()
{
    Something something;
        
    int x= something.work_a();
        
    x=something.work_b("die!");
    
    std::cout << "X:" << x << std::endl;
    
}

int main()
{
    try{
        run();
    } catch(...) {}
    
    return 0;
}

// In another compilation unit: 

class Something::Something_private
{
    int x;
    public:
    Something_private():x(0){}
    ~Something_private(){std::cout << "Dont forget that. " << x << std::endl;}
    inline int work_a() { return ++x; }
};

Something::Something():
    something(new Something_private) 
{

}

Something::~Something() 
{ 
  delete something;
}

int Something::work_a() 
{
      return something->work_a();
}

int Something::work_b(const char *str) 
{
      throw std::runtime_error(str);
}

