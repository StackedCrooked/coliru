#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

class ExtraObj
{
public:
    ExtraObj(std::string name)
        : name_(name)
    {
        printf("%s ExtraObj()\n", name_.c_str());
        buf_test = new char[256];
    }
    ~ExtraObj()
    {
        printf("%s ~ExtraObj()\n", name_.c_str());
        delete[] buf_test;
    }
    
    char* buf_test;
    std::string name_;
};

class BaseObj
{
public:
    BaseObj(std::string name)
        : name_(name)
    {
        printf("%s BaseObj()\n", name_.c_str());
    }
    ~BaseObj()
    {
        printf("%s ~BaseObj()\n", name_.c_str());
    }
    
    std::string name_;
};

class DerivedObj1 : public BaseObj
{
public:
    DerivedObj1(std::string name)
        : BaseObj(name), obj(name)
    {
        printf("%s DerivedObj1()\n", name_.c_str());
    }
    ~DerivedObj1()
    {
        printf("%s ~DerivedObj1()\n", name_.c_str());
    }
    
    ExtraObj obj;
};

class DerivedObj2 : public BaseObj
{
public:
    DerivedObj2(std::string name)
        : BaseObj(name), obj(name)
    {
        printf("%s DerivedObj2()\n", name_.c_str());
    }
    ~DerivedObj2()
    {
        printf("%s ~DerivedObj2()\n", name_.c_str());
    }
    
    ExtraObj obj;
};

int main()
{
    /*
    BaseObj base_obj1;
    BaseObj base_obj2;
    DerivedObj1 derived_obj1;
    DerivedObj2 derived_obj2;
    */
    
    BaseObj* base_ptr = new BaseObj("base_ptr");
    BaseObj* base_ptr_derived1 = new DerivedObj1("base_ptr_derived1");
    BaseObj* base_ptr_derived2 = new DerivedObj2("base_ptr_derived2");
    DerivedObj1* derived_ptr_derived = new DerivedObj1("derived_ptr_derived");
    
    delete base_ptr;
    delete base_ptr_derived1;
    delete base_ptr_derived2;
    delete derived_ptr_derived;
    
    return 0;
}
