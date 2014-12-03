#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

class foo
{
    friend class bar;
private:
    foo()
    {}
};
    
class bar
{
public:
  bar()
  {
    foo* f = new foo();
//    auto sp1 = boost::make_shared<foo>();  // this doesn't compile
    auto sp2 = boost::shared_ptr<foo>(new foo);
  } 
};

int main()
{}
