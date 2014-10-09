#define BOOST_MULTI_INDEX_ENABLE_INVARIANT_CHECKING
#include <boost/flyweight.hpp>

template<typename Base>
class poly_holder
{
public:
  poly_holder(const Base& x):p(&x),dlt(false){}
  poly_holder(const poly_holder& x):p(x.p->clone()),dlt(true){}
  poly_holder(poly_holder&& x):p(x.dlt?x.p:x.p->clone()),dlt(true){x.dlt=false;}
  poly_holder& operator=(const poly_holder& x)
  {
    Base* q=x.p->clone();
    if(dlt)delete p;
    p=q;
    dlt=true;
    return *this;
  }
  poly_holder& operator=(poly_holder&& x)
  {
    Base* q=x.dlt?x.p:x.p->clone();
    if(dlt)delete p;
    p=q;
    dlt=true;
    x.dlt=false;
    return *this; 
  }
  ~poly_holder(){if(dlt)delete p;}
  
  operator const Base&()const {return *p;}

private:
  const Base* p;
  bool        dlt;
};

template<typename Base>
class poly_flyweight:public boost::flyweight<poly_holder<Base>>
{
public:
  using super=boost::flyweight<poly_holder<Base>>;
  using super::super;
  
  template<typename U>
  operator const poly_flyweight<U>&() const
  {
    const void* me = this;
    return *static_cast<const poly_flyweight<U>*>(me);
  }  
  
  const Base& operator*() const{return base();}
  const Base* operator->()const{return &base();}
  
private:
 const Base& base()const{return this->get();}
};

struct Base
{
  virtual ~Base(){}
  virtual Base* clone()const{return new Base(*this);}
};

std::size_t hash_value(const Base&){return 0;}
bool operator==(const Base&,const Base&){return true;}

struct Derived:Base
{
  virtual Derived* clone()const{return new Derived(*this);}
};

#include <iostream>

int main()
{
  {
    poly_flyweight<Base> fb(Base{});
    {
      poly_flyweight<Derived> fd(Derived{});
      poly_flyweight<Base> fb2(static_cast<const poly_flyweight<Base>&>(fd));
      fb=fb2;
    }
    std::cout<<"Now I'll crash:\n";
  }
  std::cout<<"I'll never make it here\n";
}