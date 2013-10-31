#include <iostream>
#include <string>
#include <vector>


using Words = std::vector<std::string>;

class MyClass
{
    void start()
    {
        if (inst)
            throw std::logic_error;
            
        inst.reset(new OtherClass);
    }
    
    void stop()
    {
        if (!inst)
            throw std::logic_error;
            
        inst.reset();  // this throw an exception
    }
    
    private:
    boost::shared_ptr<OtherClass> inst;
}


int main()
{
    MyClass a;
    a.start();
    a.stop();
}
