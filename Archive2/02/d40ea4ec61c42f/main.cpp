#include <iostream>
#include <vector>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/utility/result_of.hpp>


class PublisherX
{
public:
    bool isSubscribed() const { return true; }
    void someMember( int a, int b ) { std::cout<< "PUBLISHER X : " << a << ", " << b << std::endl; }
};


class PublisherY
{
public:
    bool isSubscribed() const { return false; }
    void someMemberOther( int a, int b ) { std::cout<< "PUBLISHER Y : " << a << ", " << b << std::endl; }
};


class ConverterZ
{
public:    
    typedef boost::function<void(int,int)> Callback;
private:
    typedef std::vector<Callback> CallbackList;
    CallbackList _callbacks;
public:
  void registerCallback( Callback callback ){ _callbacks.push_back( callback ); }
  
  void callAll()
  {
      // DO A LOT OF WORK HERE.
      for(CallbackList::iterator it = _callbacks.begin(), end = _callbacks.end();
        it != end; ++it )
      {
          (*it)( 12, 34 );
      }
  }
  
};

template< class PublisherType, class MemberFunc >
struct TriggeredIfSubscribed
{
  MemberFunc _member_callback;
  PublisherType _publisher;
    
  TriggeredIfSubscribed( MemberFunc memberCallback, PublisherType publisher )
    : _member_callback( memberCallback )
    , _publisher(publisher)
  {
  }

  template< class ARG1, class ARG2 > // variadic...
  void operator()( ARG1 arg1, ARG2 arg2 ) 
  {
      if( _publisher->isSubscribed() )
      {
          (*_publisher.*_member_callback)( arg1, arg2 );
      }
  }
};

template< class PublisherType, class MemberFunc >
TriggeredIfSubscribed<PublisherType, MemberFunc> triggerIfSubscribed( MemberFunc memberCallback, PublisherType publisher )
{
    return TriggeredIfSubscribed<PublisherType, MemberFunc>( memberCallback, publisher );
}



int main()
{
    boost::shared_ptr<PublisherX> p1 = boost::make_shared<PublisherX>();
    boost::shared_ptr<PublisherY> p2 = boost::make_shared<PublisherY>(); 
    boost::shared_ptr<PublisherX> p3 = boost::make_shared<PublisherX>();
    
   ConverterZ converter;
   converter.registerCallback( triggerIfSubscribed( &PublisherX::someMember, p1 ) );
   converter.registerCallback( triggerIfSubscribed( &PublisherY::someMemberOther, p2 ) );
   converter.registerCallback( triggerIfSubscribed( &PublisherX::someMember, p3 ) );
   
   converter.callAll();
}
