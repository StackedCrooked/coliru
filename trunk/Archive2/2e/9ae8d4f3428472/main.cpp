#include <iostream>
#include <boost/asio.hpp>
#include <memory>
#include <deque>
#include <set>
#include <iomanip>
#include <mutex>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

#define DEBUG ON

#ifdef DEBUG
#define DEBUG_MSG(str) do {std::cout << std::setw(75) << std::left  << __FUNCTION__ \
    << std::setw(3) << std::left << ":" << std::setw(5) << std::left << __LINE__ \
    << std::setw(5) << std::left << ":"\
    << std::left  << str \
    << std::endl;} while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif

namespace asio = boost::asio;
using asio::ip::tcp;

class CSerSession;
using sessionPtr = std::shared_ptr<CSerSession>;

class CSerSessionsManager {
  private:
    mutable std::mutex mutex_;
    std::set<sessionPtr> sessions_; // Active Sessions : Online Info

  public:
    CSerSessionsManager();
    ~CSerSessionsManager();

    void addSession(sessionPtr session);
    void dropSession(sessionPtr session);
};

class CBuffer {

  public:
    enum { buffsize = 32 };

  private:
    char received_[buffsize];

  public:
    CBuffer() : received_{} {}

    CBuffer(const std::string str)
    {
        // Truncate if Overflow
        auto len = str.size();
        if (len >= buffsize) {
            len = buffsize - 1;
        }
        std::copy(str.begin(), str.begin() + len, received_);
        received_[len] = '\0';
    }

    bool empty() const
    {
        return !received_[0];
    }
    const std::string getString() const { return std::string(received_); }
    const char* getReceived() const { return received_; }
};

class CSerSession : public std::enable_shared_from_this<CSerSession> {
  private:
    mutable std::mutex mutex_;
    mutable tcp::socket socket_; // client connection
    CSerSessionsManager& manager_;

    std::string ip_;
    std::string port_;

    CBuffer msg_;

  public:
    CSerSession(asio::io_service& io_service, CSerSessionsManager& mng) : socket_(io_service), manager_(mng)
    {
        DEBUG_MSG("Server Session Created");
    }

    ~CSerSession() { DEBUG_MSG("Server Session Destroyed"); }

    void startSession()
    {
        DEBUG_MSG("Server Session Started");
        manager_.addSession(shared_from_this()); // Multiple threads should not try adding section

        read();
    }

    tcp::socket& socket() { return socket_; }
  private:
    void handle_read(const boost::system::error_code& error /*error*/, size_t /*bytes_transferred*/)
    {
        if (!error) {
            read();
        } else {
            DEBUG_MSG("Read Error Detected : " << error.message());
            manager_.dropSession(shared_from_this()); // might throw
        }
    }

    void read()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        DEBUG_MSG("Read");
        asio::async_read(socket_, asio::buffer(const_cast<char*>(msg_.getReceived()), msg_.buffsize),
                         std::bind(&CSerSession::handle_read, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
    }
};


CSerSessionsManager::CSerSessionsManager()
{
    DEBUG_MSG("Construction");
}

CSerSessionsManager::~CSerSessionsManager()
{
    DEBUG_MSG("Destruction");
}

void CSerSessionsManager::addSession(sessionPtr session)
{
    std::lock_guard<std::mutex> lock(mutex_);
    DEBUG_MSG("Incoming Session Entry saved");
    sessions_.insert(session);
}

void CSerSessionsManager::dropSession(sessionPtr session)
{
    std::lock_guard<std::mutex> lock(mutex_);
    DEBUG_MSG("Session dropped");
    sessions_.erase(session);
}

class CServer {
private:
    mutable std::mutex mutex_;
    asio::io_service& io_;
    mutable tcp::acceptor acceptor_; // only in the listener
    CSerSessionsManager mng_;
public:

    CServer(asio::io_service& io_service, const std::string& IP, int port)
        : io_(io_service), acceptor_(io_, tcp::endpoint(asio::ip::address::from_string(IP), port))
    {
        DEBUG_MSG("Listener Created");
    }

    ~CServer()
    {
        DEBUG_MSG("Listener Destroyed");
        acceptor_.close(); // likely to be redundant
    }

    void initProtocol()
    {
        listen();
    }

  private:
    void listen()
    {
        DEBUG_MSG("!==============================================================!");

        sessionPtr newSession = std::make_shared<CSerSession>(io_, mng_);

        std::lock_guard<std::mutex> lock(mutex_);
        acceptor_.async_accept(newSession->socket(), std::bind(&CServer::handle_accept, this, newSession,
                    std::placeholders::_1));
    }

    void handle_accept(sessionPtr newSession, const boost::system::error_code& error)
    {
        if (error || !acceptor_.is_open()) {
            DEBUG_MSG("Listen_Error");
            DEBUG_MSG(error.message());
            return;
        }

        DEBUG_MSG("Incoming Session accepted");
        newSession->startSession();
        listen();
    }
};

int main()
{
    try
    {
        asio::io_service io_service;
        auto server = std::make_shared<CServer>(io_service, "127.0.0.1", 8973);
        server->initProtocol();
        boost::thread t(boost::bind(&asio::io_service::run, &io_service));

        boost::this_thread::sleep_for(boost::chrono::seconds(3));

        t.join();
    }
    catch (...)
    {
    }
}

