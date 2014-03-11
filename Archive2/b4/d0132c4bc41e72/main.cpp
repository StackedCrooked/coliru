#include <boost/optional.hpp>
#include <functional>


struct Value
{
    Value(const int* value):
    mValue(0)
    {
        if(!value)
        {
            throw std::runtime_error("Invalid pointer");    
        }
        mValue = *value;
    }

    Value():
    mValue(0)
    {}

    int get() const { return mValue;}

    int mValue;
};

struct Sum
{
    
    Sum(const int* first, const int* second) try :
    mFirst(Value(first)),
    mSecond(Value(second))
    {
    }
    catch(const std::exception& e)
    {
        // Exception is always rethrown in the function try blocks
        std::cout << "Invalid input: (" << e.what() << ") when constructing element of type Sum" << std::endl;   
    }

    int get() const { return mFirst.get() + mSecond.get(); }

    const Value mFirst;
    const Value mSecond;
};

int main() { 

    int number = 5;
    (void)number;
    
    int* ptr(nullptr);
    
    Sum val(ptr, ptr);
    
    std::cout << val.get();
    


}