// -> http://stackoverflow.com/questions/18196412/generate-a-unique-type-or-id-for-each-template-instantiation-example-observer

#include <vector>
#include <iostream>
#include <functional>

template <typename T>
struct type2type {};

template<class T>    // the UNIQUE_T is no more need
class SUBJECT_BASE
{
  std::vector<std::function<void ( T ) >> observers;

public:
  void do_notify ()
  {
    for ( auto& obs : observers )
      obs ( T {} );
  }

  void add_listener ( std::function<void ( T ) > l )
  {
    observers.emplace_back ( std::move ( l ) );
  }
};

class X {};
class Y {};

class UNIQUE_A {};
class UNIQUE_B {};
class UNIQUE_C {};

struct Observer
{
  void notify ( X, type2type< UNIQUE_A > )
  {
    std::cout << "x from Subject_A" << std::endl;
  }

  void notify ( X, type2type< UNIQUE_B > )
  {
    std::cout << "x from Subject_B" << std::endl;
  }

  void notify ( Y, type2type< UNIQUE_C > )
  {
    std::cout << "y from Subject_C" << std::endl;
  }
};

int main ()
{
  SUBJECT_BASE<X> sub_a {};
  SUBJECT_BASE<X> sub_b {};
  SUBJECT_BASE<Y> sub_c {};

  Observer obs{};

  sub_a.add_listener ( [&obs]( X x ){ obs.notify( x, type2type< UNIQUE_A >{} ); } );
  sub_b.add_listener ( [&obs]( X x ){ obs.notify( x, type2type< UNIQUE_B >{} ); } );
  sub_c.add_listener ( [&obs]( Y y ){ obs.notify( y, type2type< UNIQUE_C >{} ); } );

  sub_a.do_notify();
  sub_b.do_notify();
  sub_c.do_notify();
}