#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/thread/thread.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <thread>
//#include "test.pb.cc" - this was the problem (you should only include *.h files)
//#include "test.pb.h"

using boost::asio::ip::tcp;

struct Person {
    int id() {return 42;}
    const char* name() {return "name";}
    void set_id(int) {}
    void set_name(const char*) {}

    bool SerializeToString(std::string* data) const { if (data) *data += "someserializedform"; return data; }
};

int main()
{
    try
    {
        // connect to the server:
        boost::asio::io_service io_service;
        tcp::resolver resolver(io_service);
        std::string const server_address = "localhost";
        std::string const server_port    = "55555";

        tcp::resolver::query query(server_address, server_port);
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        tcp::socket socket(io_service);
        boost::asio::connect(socket, endpoint_iterator);
        while ( true)
        {
            Person p = Person();
            p.set_id(22);
            p.set_name("some name");

            std::cout << p.id();
            std::cout << p.name();

            std::string data; // this will hold serialized data
            bool ok = p.SerializeToString(&data);
            assert(ok);

            std::cout << data.size() << std::endl;
            boost::asio::write(socket, boost::asio::buffer(data), boost::asio::transfer_exactly(65536));
            std::cout << data.size() << std::endl;  // shows a reduction in amount of remaining data
        }

    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    std::cout << "\nClosing";
    std::string dummy;
    std::cin >> dummy;
}
