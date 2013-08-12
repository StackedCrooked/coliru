#include <typeinfo>

class base
{
    public:
        virtual ~base(){};
        virtual int type() = 0;
};
class derived1 : public base
{
    public:
        void derived1specific() const {}
        virtual int type(){return 1;}
};
class derived2 : public base
{
    public:
        void derived2specific() const {}
        virtual int type(){return 2;}
};
int main()
{
    // use pointers
    base* test = new derived1;
    derived2* d2 = dynamic_cast<derived2*>(test);
    if(d2)
        d2->derived2specific();
    derived1* d1 = dynamic_cast<derived1*>(test);
    if(d1)
        d1->derived1specific();
        
    // use references
    const base& testr = derived1();
    try{
        const derived1& d1 = dynamic_cast<const derived1&>(testr);
        d1.derived1specific();
    }
    catch(std::bad_cast&){}
    try{
        const derived2& d2 = dynamic_cast<const derived2&>(testr);
        d2.derived2specific();
    }
    catch(std::bad_cast&){}
    
    auto doNothing = [](){return;};
    (test->type()==1?(((derived1*)test)->derived1specific()):doNothing());
    (test->type()==2?(((derived2*)test)->derived2specific()):doNothing());
}
