#include <functional>
#include <iostream>
namespace{
    using std::function;
    class base {
    protected:
        using signiture =void(void);
        using func_t = function<signiture>;
        ~base(){}
    public:
        func_t bar;
    };
}
template <typename implementation>
class foo:public base {
public:
    foo(implementation* instance){
        bar = func_t(std::bind(&implementation::bar_implementation,instance));
    }
};
typedef base foo_base;

class testcase:public foo<testcase> {
public:
    friend class foo;//allows implementations to be protected or private
    testcase():foo(this){}
protected:
    void bar_implementation(void){
        std::cout<<"Hello"<<std::endl;
    }
};
class testcase2:public foo<testcase2> {
public:
    friend class foo;//allows implementations to be protected or private
    testcase2():foo(this){}
protected:
    void bar_implementation(void){
        std::cout<<"World!"<<std::endl;
    }
};


int main(int argc, const char * argv[]) {
    testcase t;
    testcase2 t2;
    
    foo_base* b = &t;
    foo_base* b2 = &t2;
    b->bar();
    b2->bar();
    return 0;
}

