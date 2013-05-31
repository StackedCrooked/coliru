#include <boost/thread.hpp>
#include <boost/asio.hpp>

#include <string>

class CConnection {
public:
    CConnection(void);
    boost::asio::io_service io_service;
    boost::shared_ptr<boost::asio::ip::tcp::socket> socket;
    boost::asio::ip::tcp::endpoint endpoint;
    boost::shared_ptr<boost::thread> thread;
    boost::asio::io_service *master_io_service;
    bool close;
};

void worker(boost::shared_ptr<CConnection> connection) 
{
    boost::asio::ip::tcp::socket &socket = *(connection->socket);
    boost::asio::socket_base::non_blocking_io make_non_blocking(true);
    socket.io_control(make_non_blocking);

    char acBuffer[1024];
    std::string line("");

    while ( connection->close == false ) {

    } // while connection not to be closed
}

int
main()
{
    boost::shared_ptr<CConnection> connection( new CConnection );
    new boost::thread(worker, connection);
}