#ifndef NETWORKING_H
#define NETWORKING_H


#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <string>


class UDPServer : boost::noncopyable
{
public:
    typedef boost::function<std::string(const std::string &)> RequestHandler;

    UDPServer(unsigned port, const RequestHandler & requestHandler);

    ~UDPServer();

private:
    struct Impl;
    boost::scoped_ptr<Impl> mImpl;
};


class UDPClient : boost::noncopyable
{
public:
    UDPClient(const std::string & inHost, unsigned inPort);

    ~UDPClient();

    std::string send(const std::string & inMessage);

private:
    struct Impl;
    boost::scoped_ptr<Impl> mImpl;
};


class UDPReceiver : boost::noncopyable
{
public:
    typedef boost::function<bool(const std::string &)> RequestHandler;

    UDPReceiver(unsigned port, const RequestHandler & handler);

    ~UDPReceiver();

    void waitForAll();

private:
    struct Impl;
    boost::scoped_ptr<Impl> mImpl;
};


class UDPSender : boost::noncopyable
{
public:
    UDPSender(const std::string & inHost, unsigned inPort);

    ~UDPSender();

    void send(const std::string & inMessage);

private:
    struct Impl;
    boost::scoped_ptr<Impl> mImpl;
};


#endif // NETWORKING_H


#include "Networking.h"
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/replace.hpp>


using namespace boost::asio;
using boost::asio::ip::udp;


//
// Always returns the same io_service instance.
//
boost::asio::io_service & get_io_service()
{
    static boost::asio::io_service io;
    return io;
}


//
// UDPServer
//
struct UDPServer::Impl
{
    Impl(unsigned inPort, const RequestHandler & inRequestHandler) :
        mPort(inPort),
        mRequestHandler(inRequestHandler),
        mSocket(get_io_service(), boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), mPort))
    {
        while (true)
        {
            const unsigned int cMaxLength = 1024 * 1024;
            char data[cMaxLength];
            udp::endpoint sender_endpoint;
            size_t length = mSocket.receive_from(boost::asio::buffer(data, cMaxLength), sender_endpoint);
            std::string req(data, length);
            std::cout << "\nRequest size: " << req.size() << std::endl;
            std::cout << "Request data:\n" << req << std::endl;
            std::string response = inRequestHandler(req);
            std::cout << "\nResponse size: " << response.size() << std::endl;
            std::cout << "Response data:\n" << response << std::endl;
            mSocket.send_to(boost::asio::buffer(response.c_str(), response.size()), sender_endpoint);
        }
    }

    ~Impl()
    {
    }

    unsigned mPort;
    RequestHandler mRequestHandler;
    boost::asio::ip::udp::socket mSocket;
};


UDPServer::UDPServer(unsigned inPort, const RequestHandler & inRequestHandler) :
    mImpl(new Impl(inPort, inRequestHandler))
{
}


UDPServer::~UDPServer()
{
}


//
// UDPClient
//
struct UDPClient::Impl : boost::noncopyable
{
    Impl(const std::string & inURL, unsigned inPort) :
        socket(get_io_service(), udp::endpoint(udp::v4(), 0)),
        resolver(get_io_service()),
        query(udp::v4(), inURL.c_str(), boost::lexical_cast<std::string>(inPort).c_str()),
        iterator(resolver.resolve(query))
    {

    }

    ~Impl()
    {
    }

    udp::socket socket;
    udp::resolver resolver;
    udp::resolver::query query;
    udp::resolver::iterator iterator;
};


UDPClient::UDPClient(const std::string & inURL, unsigned inPort) :
    mImpl(new Impl(inURL, inPort))
{
}


UDPClient::~UDPClient()
{
}


std::string UDPClient::send(const std::string & inMessage)
{
    mImpl->socket.send_to(boost::asio::buffer(inMessage.c_str(), inMessage.size()), *mImpl->iterator);

    static const unsigned cMaxLength = 1024 * 1024;
    char reply[cMaxLength];
    udp::endpoint sender_endpoint;
    size_t reply_length = mImpl->socket.receive_from(boost::asio::buffer(reply, cMaxLength), sender_endpoint);
    return std::string(reply, reply_length);
}


//
// UDPReceiver
//
struct UDPReceiver::Impl
{
    typedef UDPReceiver::RequestHandler RequestHandler;

    Impl(UDPReceiver * inUDPReceiver,
         unsigned inPort,
         const RequestHandler & inRequestHandler) :
        mUDPReceiver(inUDPReceiver),
        mPort(inPort),
        mRequestHandler(inRequestHandler),
        mSocket(get_io_service(), boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), mPort))
    {
        prepareForReceiving();
    }


    ~Impl()
    {
    }



    void prepareForReceiving()
    {
        mSocket.async_receive_from(boost::asio::buffer(mData, cMaxLength), mSenderEndpoint,
                                   boost::bind(&Impl::handleReceivedData, this,
                                               boost::asio::placeholders::error,
                                               boost::asio::placeholders::bytes_transferred));
    }

    void handleReceivedData(const boost::system::error_code & inError, std::size_t inSize)
    {
        if (!inError && inSize > 0)
        {
            if (mRequestHandler(std::string(mData, inSize)))
            {
                prepareForReceiving();
                mUDPReceiver->waitForAll();
            }
            // else: stop listening
        }
        else
        {
            throw std::runtime_error(inError.message());
        }
    }

    UDPReceiver * mUDPReceiver;
    unsigned mPort;
    RequestHandler mRequestHandler;
    boost::asio::ip::udp::socket mSocket;
    udp::endpoint mSenderEndpoint;
    enum { cMaxLength = 1024 * 1024 };
    char mData[cMaxLength];
};


UDPReceiver::UDPReceiver(unsigned inPort, const RequestHandler & inRequestHandler) :
    mImpl(new Impl(this, inPort, inRequestHandler))
{
}


UDPReceiver::~UDPReceiver()
{
}


void UDPReceiver::waitForAll()
{
    get_io_service().run_one();
}


//
// UDPSender
//
struct UDPSender::Impl : boost::noncopyable
{
    Impl(const std::string & inURL, unsigned inPort) :
        socket(get_io_service(), udp::endpoint(udp::v4(), 0)),
        resolver(get_io_service()),
        query(udp::v4(), inURL.c_str(), boost::lexical_cast<std::string>(inPort).c_str()),
        iterator(resolver.resolve(query))
    {
    }

    ~Impl()
    {
    }

    udp::socket socket;
    udp::resolver resolver;
    udp::resolver::query query;
    udp::resolver::iterator iterator;
};


UDPSender::UDPSender(const std::string & inURL, unsigned inPort) :
    mImpl(new Impl(inURL, inPort))
{
}


UDPSender::~UDPSender()
{
}


void UDPSender::send(const std::string & inMessage)
{
    std::cout << "Sending: " << inMessage << std::endl;
    mImpl->socket.send_to(boost::asio::buffer(inMessage.c_str(), inMessage.size()), *mImpl->iterator);
}
