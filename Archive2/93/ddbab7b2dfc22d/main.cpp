#include <tuple>

//----------------------------------------------------------------------
//
class MessageBase
{
  public:
    MessageBase( const int _id ) : m_id( _id ) {}
    virtual int getMessageID() const { return( m_id ); }

  private:
    const int m_id;
};

#define MESSAGE( NAME, VAL ) \
  class Message##NAME : public MessageBase { \
    public: \
      Message##NAME() : MessageBase( VAL ) { } \
  };

  MESSAGE( One, 1 )
  MESSAGE( Two, 2 )
  MESSAGE( Ten, 10 )

//----------------------------------------------------------------------
//

template< typename T > 
struct MyMessageInterface {
    virtual void processMsg( const T& t ) { } 
};

template< typename... T > 
struct MyMessageHandler : public MyMessageInterface< T >...
{};

template< typename... T > 
struct MyMessageHandler< std::tuple< T... > > 
  : public MyMessageInterface< T >...
{
    template< typename U >
    void processMsg( const U& u )
    {
        MyMessageInterface< U >::processMsg( u );
    }
};


//----------------------------------------------------------------------
//
typedef std::tuple< MessageOne, MessageTwo, MessageTen > Foople;

int main()
{
  MyMessageHandler< Foople > mmh;
  mmh.processMsg( MessageOne() );
}
