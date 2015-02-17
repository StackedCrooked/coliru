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
using sessionPtr = std::shared_ptr < CSerSession >;

class CSerSessionsManager{
private:

	std::set<sessionPtr> sessions_; //Active Sessions : Online Info

public:
	CSerSessionsManager();
	~CSerSessionsManager();

	void addSession(sessionPtr session);
	void dropSession(sessionPtr session);
};

class CBuffer
{

public:
	enum { buffsize = 32 };

private:

	char received_[buffsize];

public:

	CBuffer()
	{
		received_[0] = '\0';
	}

	CBuffer(const std::string str)
	{
		//Truncate if Overflow
		auto len = str.size();
		if (len >= buffsize)
		{
			len = buffsize - 1;
		}
		std::copy(str.begin(), str.begin() + len, received_);
		received_[str.size()] = '\0';
	}

	bool empty() const
	{
		auto i = 0;
		while (received_[i] != '\0')
			i++;
		if (i == 0)
			return true;
		else
			return false;
	}
	const std::string getString() const
	{
		return std::string(received_);
	}
	const char* getReceived() const
	{
		return received_;
	}


};


class CSerSession : public std::enable_shared_from_this < CSerSession > {
private:

	mutable tcp::socket socket_;   // client connection
	CSerSessionsManager& manager_;

	std::string ip_;
	std::string port_;

	CBuffer msg_;

public:
	CSerSession(asio::io_service& io_service, CSerSessionsManager& mng) :
		socket_(io_service), manager_(mng)
	{
		DEBUG_MSG("Server Session Created");
	}

	~CSerSession()
	{
		DEBUG_MSG("Server Session Destroyed");
	}

	void startSession()
	{
		DEBUG_MSG("Server Session Started");
		//Critical Section
		static std::mutex m;
		std::lock_guard<std::mutex> lock(m);
		manager_.addSession(shared_from_this());//Multiple threads should not try adding section
		read(msg_);
	}

	void handle_read(const boost::system::error_code& error /*error*/, size_t /*bytes_transferred*/)
	{
		if (!error)
		{
			DEBUG_MSG("Read");
			//Critical Section
			static std::mutex m;
			std::lock_guard<std::mutex> lock(m);

			read(msg_);
		}
		else
		{
			DEBUG_MSG("Read Error Detected : " << error.message());
			//Check If shared_from_this() is valid or not
			try
			{
				//Check if session was already dropped e.g. server object destroying
				//i.e. if session object exists
				DEBUG_MSG("Dropping Session");
				//if (error == boost::system::error::operation_aborted)
				manager_.dropSession(shared_from_this());
			}
			catch (const std::bad_weak_ptr& e)
			{
				DEBUG_MSG(e.what());
				throw e;
			}
			return;
		}
	}

	void read(CBuffer & buff)
	{
		DEBUG_MSG("Read");
		asio::async_read(socket_, asio::buffer(const_cast<char *> (buff.getReceived()), buff.buffsize),
			std::bind(&CSerSession::handle_read, shared_from_this(),
			std::placeholders::_1, std::placeholders::_2));
	}


	tcp::socket& socket()
	{
		//Critical Section
		static std::mutex m;
		std::lock_guard<std::mutex> lock(m);
		return socket_;
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
	DEBUG_MSG("Incoming Session Entry saved");
	//Critical Section
	static std::mutex m;
	std::lock_guard<std::mutex> lock(m);
	sessions_.insert(session);
}

void CSerSessionsManager::dropSession(sessionPtr session)
{
	//Properly handle Existing connections first shutdown sockets
	DEBUG_MSG("Session dropped");

	//Critical Section
	static std::mutex m;
	std::lock_guard<std::mutex> lock(m);

	std::set<sessionPtr>::iterator it;
	for (it = sessions_.begin(); it != sessions_.end(); ++it)
	{
		if ((*it) == session)
		{
			sessions_.erase(session);
			return;
		}
	}
	//throw ASIOError(Session_Not_Found);
}




class CServer {
private:

	asio::io_service& io_;
	mutable tcp::acceptor acceptor_; // only in the listener
	CSerSessionsManager mng_;

	std::string ip_;
	std::string port_;

public:

	CServer(asio::io_service& io_service, const std::string IP, const std::string port) : io_(io_service), acceptor_(io_service)
		, ip_(IP), port_(port)
	{
		DEBUG_MSG("Listener Created");
	}

	~CServer()
	{
		DEBUG_MSG("Listener Destroyed");
		acceptor_.close();
	}

	void initProtocol()
	{
		DEBUG_MSG(" Protocol Initiated");
		std::array<unsigned char, 4> ip;
		std::string delimiter = ".";

		//Parse the IP String
		size_t pos = 0;
		auto i = 0;
		std::string token;

		while ((pos = ip_.find(delimiter)) != std::string::npos) {
			token = ip_.substr(0, pos);
			ip[i] = std::stoi(token);//what if stoi fails
			i++;
			ip_.erase(0, pos + delimiter.length());
		}

		ip[i] = std::stoi(ip_);


		asio::ip::address_v4 address(ip);
		tcp::endpoint ep(address, std::stoi(port_));


		static std::mutex m;
		std::unique_lock<std::mutex> lck(m, std::defer_lock);

		//Critical Section start
		lck.lock();
		acceptor_ = tcp::acceptor(io_, ep);//Creating IOService
		lck.unlock();
		//Critical Section End

		listen();
	}


	void listen()
	{
		DEBUG_MSG("!==============================================================!");

		////Critical Section
		static std::mutex m;
		std::lock_guard<std::mutex> lock(m);

		sessionPtr newSession = std::make_shared<CSerSession>(io_, mng_);

		try
		{
			acceptor_.async_accept(newSession->socket(), std::bind(&CServer::handle_accept, /*shared_from_this()*/ this, newSession,
				std::placeholders::_1));
			///*boost::system::error_code ec;
			//pSocket_->shutdown(asio::ip::tcp::socket::shutdown_send, ec);*/
		}
		catch (const std::bad_weak_ptr& e)
		{
			DEBUG_MSG(e.what());
			throw e;
		}

		DEBUG_MSG("Listen Activated");
	}


	void handle_accept(sessionPtr newSession, const boost::system::error_code& error)
	{
		if (!acceptor_.is_open())
		{
			return;
		}

		if (!error)
		{
			DEBUG_MSG("Incoming Session accepted");
			//Do I need a Lock here?
			//Critical Section
			static std::mutex m;
			std::lock_guard<std::mutex> lock(m);
			newSession->startSession();
			listen();
		}
		else
		{
			DEBUG_MSG("Listen_Error");
			//	//throw ASIOError(Listen_Error);
			DEBUG_MSG(error.message());
			return;
		}
	}

};

int main()
{
	try
	{
		asio::io_service io_service;
		//CServer  server(io_service, "Default", "127.0.0.1", "8000");
		auto sPtr = std::make_shared<CServer>(io_service, "127.0.0.1", "8000");
		sPtr->initProtocol();
		//server.initProtocol();
        boost::thread t(boost::bind(&asio::io_service::run, &io_service));

	}
	catch (...)
	{
	}
}

