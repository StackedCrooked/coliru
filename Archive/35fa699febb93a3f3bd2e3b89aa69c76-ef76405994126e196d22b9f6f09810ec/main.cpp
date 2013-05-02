#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

#include <iostream> 

const std::string buf ("hello world");

void
writeHandler(
        const boost::system::error_code& error,
        const size_t bytesTransferred
        )
{
    if ( error ) {
        std::cerr << "could not write: " << error.message() << std::endl;
        return;
    }

    std::cout << "wrote " << bytesTransferred << " bytes" << std::endl;
}


void
connectHandler(
        boost::asio::local::stream_protocol::socket* socket,
        const boost::system::error_code& error
        )
{
    if ( error ) {
        std::cerr << "could not connect: " << error.message() << std::endl;
        return;
    }

    boost::asio::async_write(
            *socket,
            boost::asio::buffer( buf ),
            boost::bind(
                &writeHandler,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred
                )
            );
}

int
main(int argc, char* argv[])
{
    if ( argc < 3 ) {
        std::cerr << argv[0] << "[af_unix socket name] [num connections]" << std::endl;
        exit(1);
    }

    const int count = boost::lexical_cast<int>( argv[2] );

    std::string path( 1, '\0' ); // first byte is NULL for anonymous namespace
    path.append( argv[1] );
    const boost::asio::local::stream_protocol::endpoint ep( path );

    boost::asio::io_service ios;

    for ( unsigned i = 0; i < count; ++i ) {
        boost::asio::local::stream_protocol::socket* socket(
                new boost::asio::local::stream_protocol::socket(ios)
                );
        socket->async_connect(
                ep,
                boost::bind(
                    &connectHandler,
                    socket,
                    boost::asio::placeholders::error
                    )
                );
    }

    const size_t result = ios.run();
    std::cout << "ran " << result << " handlers" << std::endl;
}
