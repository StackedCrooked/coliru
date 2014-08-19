#include <vector>
#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/variant.hpp>
#include <memory>
#include <type_traits>

namespace crtp
{

  // Definition of the interface (abstract class).
  template< typename C >
  struct CBase
  {
    void f() { static_cast<C&>(*this).f(); }
    int g(const double & x) { return static_cast<C&>(*this).g(x); }
  };

  // Definition of the first implementation.
  struct C1 : public CBase<C1>
  {
    void f();
    int g(const double & x);
  };
  void C1::f() { return ; }
  int C1::g(const double & x) { return sizeof(x); }

  // Definition of the second implementation.        
  struct C2 : public CBase<C2>
  {
    void f();
    int g(const double & x);
  };
  void C2::f() { return ; }
  int C2::g(const double & x) { return sizeof(x); }

  // Definition of the visitor for the first function of the interface.  
  class f_visitor : public boost::static_visitor<int>
  {
  public:
    template< typename C >
    int operator()(CBase<C> &c ) const { c.f(); return 0; }
  };

  // Definition of the visitor for the second function of the interface.  
  struct g_visitor : public boost::static_visitor<int>
  {
    const double & x;
    g_visitor( const double & x ) : x(x) {}
  public:
    template< typename C >
    int operator()(CBase<C> & c) const { return c.g(x);  }
  };

  // Example of use: construct a random collection and visit it.
  void test(int nbSample)
  {
    typedef boost::variant<C1,C2> CV;
    std::vector<CV> vec;

    for( int i=0;i<nbSample;++i ) 
      {
    switch( std::rand() % 2 )
      {
      case 1:       vec.push_back( C1() ); break;
      case 2:       vec.push_back( C2() ); break;
      }
      }

    double argdouble;
    BOOST_FOREACH(CV & c, vec)
      {
    boost::apply_visitor( f_visitor(), c );
    g_visitor g(argdouble);
    boost::apply_visitor( g, c );
      }
  }
}




namespace virt_fun
{
  struct CBase
  {
    virtual void f() = 0;
    virtual int g(const double & x) = 0;
  };

  struct C1 : public CBase  
  {
    void f() {}
    int g(const double & x) { return 1; }
  };
  struct C2 : public CBase
  {
    void f() {}
    int g(const double & x) { return 2; }
  };

  void test(int nbSample)
  {
    typedef boost::shared_ptr<CBase> CV;
    std::vector<CV> vec;
    for( int i=0;i<nbSample;++i ) 
      {
    switch( std::rand() % 2 )
      {
      case 1:       vec.push_back( CV(new C1()) ); break;
      case 2:       vec.push_back( CV(new C2()) ); break;
      }
      }

    double argdouble = 0.0;
    BOOST_FOREACH( CV & c, vec)
    {
      c->f();
      c->g(argdouble);
    }
  }
}


namespace virt_cont
{
  struct CBase
  {
    virtual void f() = 0;
    virtual int g(const double & x) = 0;
    virtual ~CBase() = default;
  };

  struct C1 : public CBase  
  {
    void f() {}
    int g(const double & x) { return 1; }
  };
  struct C2 : public CBase
  {
    void f() {}
    int g(const double & x) { return 2; }
  };
  
  struct foo
  {
    std::aligned_storage<sizeof(C2)>::type buf;
    CBase* ptr;
    
    foo(C1 c) { ptr = new ((void*)&buf) C1(c); }
    foo(C2 c) { ptr = new ((void*)&buf) C2(c); }
    
    foo(foo&& x) : buf(x.buf) { ptr = reinterpret_cast<CBase*>(&buf); } // UB :(
    foo& operator= (foo&& x) { buf = x.buf; return *this; } // maybe UB?
    
    ~foo() { ptr->~CBase(); }
  };
  void test(int nbSample)
  {
    std::vector<foo> vec;
    vec.reserve(nbSample);
    for( int i=0;i<nbSample;++i ) 
      {
    switch( std::rand() % 2 )
      {
      case 1:       vec.emplace_back( C1() ); break;
      case 2:       vec.emplace_back( C2() ); break;
      }
      }

    double argdouble = 0.0;
    BOOST_FOREACH( foo & c, vec)
    {
      c.ptr->f();
      c.ptr->g(argdouble);
    }
  }
}



#include <chrono>
#include <string>

// your code goes here, including header files

int main(int argc, char* argv[]) {

  auto const rounds = std::atoll(argv[1]) ;
  
  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();

  
#define VER 2
  
#if VER==0
  crtp::test(rounds);
#elif VER==1
  virt_fun::test(rounds);
#elif VER==2
  virt_cont::test(rounds);
#endif

  end = std::chrono::system_clock::now();

  std::chrono::duration<double> elapsed_seconds = end - start;
  std::time_t end_time = std::chrono::system_clock::to_time_t(end);

  std::cout << "finished computation at " << std::ctime(&end_time)
            << "elapsed time: " << elapsed_seconds.count() << "s\n";

  return 0;
}