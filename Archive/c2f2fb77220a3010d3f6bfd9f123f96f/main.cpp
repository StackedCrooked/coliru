#include <utility>

struct NetworkId { };

template< class MessageType >
class FromNetwork
{
public:
    FromNetwork( const MessageType& message, NetworkId source ) 
        : m_message( message )
        , m_source( std::move( source ) )
    {}

    const MessageType& message() const { return m_message; }
    const NetworkId& source() const { return m_source; }

    const MessageType& operator*() const { return m_message; }
    const MessageType* operator->() const { return &m_message; } // ERROR

private:
    const MessageType& m_message;
    NetworkId m_source;
};

struct SlaveRequest {
    int slave_id() const { return 0; }
};

struct Master {
    void on_slave_request(int, NetworkId) { }
} m_master;

void handle_message( const FromNetwork<SlaveRequest>& message )
    {
        m_master.on_slave_request( message->slave_id(), message.source() );
    }

int main() {
    SlaveRequest slave;
    FromNetwork<SlaveRequest> msg(slave, NetworkId());
    handle_message(msg);
}