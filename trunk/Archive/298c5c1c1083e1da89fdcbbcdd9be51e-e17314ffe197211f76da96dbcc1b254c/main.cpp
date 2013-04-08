#include "Message.h"
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <algorithm>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <set>


typedef std::deque<Message> RequestQueue;


class AbstractMessageSession
{
public:
    virtual ~AbstractMessageSession() {}
    virtual void deliver(const Message & msg) = 0;
};


typedef boost::shared_ptr<AbstractMessageSession> AbstractSessionPtr;


class MessageSessions
{
public:
    void join(AbstractSessionPtr session)
    {
        std::cout << "join" << std::endl;
        mSessions.insert(session);
    }

    void leave(AbstractSessionPtr participant)
    {
        std::cout << "leave" << std::endl;
        mSessions.erase(participant);
    }
    
private:
    std::set<AbstractSessionPtr> mSessions;
};


class MessageSession : public AbstractMessageSession,
                       public boost::enable_shared_from_this<MessageSession>
{
public:
    MessageSession(boost::asio::io_service & io_service, MessageSessions & room) :
        socket_(io_service),
        mSessions(room),
        mReadMessage()
    {
        std::cout << "MessageSession created." << std::endl;
    }
    
    ~MessageSession()
    {
        std::cout << "MessageSession destroyed." << std::endl;
    }

    boost::asio::ip::tcp::socket & socket()
    {
        return socket_;
    }

    void start()
    {
        mSessions.join(shared_from_this());
        boost::asio::async_read(socket_,
                                boost::asio::buffer(mReadMessage.data(), Message::header_length),
                                boost::bind(&MessageSession::handle_read_header, shared_from_this(),
                                            boost::asio::placeholders::error));
    }

    void deliver(const Message & msg)
    {
        bool write_in_progress = !write_msgs_.empty();
        write_msgs_.push_back(msg);
        if (!write_in_progress)
        {
            boost::asio::async_write(socket_,
                                     boost::asio::buffer(write_msgs_.front().data(),
                                                         write_msgs_.front().length()),
                                     boost::bind(&MessageSession::handle_write, shared_from_this(),
                                                 boost::asio::placeholders::error));
        }
    }

    void handle_read_header(const boost::system::error_code & error)
    {
        if (!error && mReadMessage.decode_header())
        {
            boost::asio::async_read(socket_,
                                    boost::asio::buffer(mReadMessage.body(), mReadMessage.body_length()),
                                    boost::bind(&MessageSession::handle_read_body, shared_from_this(),
                                                boost::asio::placeholders::error));
        }
        else
        {
            mSessions.leave(shared_from_this());
        }
    }

    void handle_read_body(const boost::system::error_code & error)
    {
        if (!error)
        {
            deliver(mReadMessage);
            boost::asio::async_read(socket_,
                                    boost::asio::buffer(mReadMessage.data(), Message::header_length),
                                    boost::bind(&MessageSession::handle_read_header, shared_from_this(),
                                                boost::asio::placeholders::error));
        }
        else
        {
            mSessions.leave(shared_from_this());
        }
    }

    void handle_write(const boost::system::error_code & error)
    {
        if (!error)
        {
            write_msgs_.pop_front();
            if (!write_msgs_.empty())
            {
                boost::asio::async_write(socket_,
                                         boost::asio::buffer(write_msgs_.front().data(),
                                                             write_msgs_.front().length()),
                                         boost::bind(&MessageSession::handle_write, shared_from_this(),
                                                     boost::asio::placeholders::error));
            }
        }
        else
        {
            mSessions.leave(shared_from_this());
        }
    }

private:
    boost::asio::ip::tcp::socket socket_;
    MessageSessions & mSessions;
    Message mReadMessage;
    RequestQueue write_msgs_;
};


typedef boost::shared_ptr<MessageSession> SessionPtr;


class MessageServer
{
public:
    MessageServer(uint16_t port) :
        mIOService(get_io_service()),
        mAcceptor(mIOService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
    {        
        start_accept();
        mIOService.run();
    }

    void start_accept()
    {
        SessionPtr new_session(new MessageSession(mIOService, room_));
        mAcceptor.async_accept(new_session->socket(),
                               boost::bind(&MessageServer::handle_accept, this, new_session,
                                           boost::asio::placeholders::error));
    }

    void handle_accept(SessionPtr session,
                       const boost::system::error_code & error)
    {
        if (!error)
        {
            session->start();
        }

        start_accept();
    }

private:
    boost::asio::io_service & mIOService;
    boost::asio::ip::tcp::acceptor mAcceptor;
    MessageSessions room_;
};


typedef boost::shared_ptr<MessageServer> ServerPtr;
typedef std::list<ServerPtr> Servers;