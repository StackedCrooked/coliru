#include <boost/asio.hpp>
#include <boost/bind.hpp>

class mag_serial
{
bool data_available;
boost::asio::serial_port& ser_port;
boost::asio::deadline_timer timeout;
char my_buffer[1];
std::string str;
std::string st;


void read_callback(
    bool& data_available, 
    boost::asio::deadline_timer& timeout, 
    const boost::system::error_code& error, 
    std::size_t bytes_transferred
    )
{
    ser_port.async_read_some(
        boost::asio::buffer(my_buffer),
        boost::bind(
            &mag_serial::read_callback,
            this,
            boost::ref(data_available),
            boost::ref(timeout),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred
            )
        );

        data_available = true;
}

public:
mag_serial(boost::asio::serial_port& ser_port, boost::asio::io_service& io_svc): ser_port(ser_port), timeout(ser_port.get_io_service()){}


};

int
main()
{
    
}