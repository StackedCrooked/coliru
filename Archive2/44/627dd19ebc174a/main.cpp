#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/make_shared.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <iostream>

using boost::asio::ip::tcp;

struct TCPNetworkSession;
typedef boost::shared_ptr<TCPNetworkSession> SharedPtr;

enum NetworkListener { NLState_Unspecified, NLState_Running };

struct TCPNetworkListener {

    TCPNetworkListener();
	boost::asio::io_service m_IOService;
	tcp::endpoint m_TCPEndpoint;
	tcp::acceptor m_SocketAcceptor; 
	long m_lastConnectedClientId;
	NetworkListener m_listenerState;

	bool StartListener();
	void HandleNewConnection( SharedPtr session, const boost::system::error_code& error );

	void ClientConnected(SharedPtr const& session) const;
	void ClientDisconnected(SharedPtr const& session) const;
	void ClientDataReceived(SharedPtr const& session, std::string data) const;
};

TCPNetworkListener::TCPNetworkListener() :
	m_SocketAcceptor(m_IOService)
{
	m_TCPEndpoint = tcp::endpoint(tcp::v4(), 12001);
	m_lastConnectedClientId = -1;
	m_listenerState = NLState_Unspecified;
}

#define SOCKETBUFFERLENGTH 32

struct TCPNetworkSession : boost::enable_shared_from_this<TCPNetworkSession> {

	tcp::socket m_socket;
	boost::asio::io_service& m_IOService;
	TCPNetworkListener* m_networkHandler;
	long m_clientId;
	bool m_sendingData;
	boost::array<char, SOCKETBUFFERLENGTH> m_readBuffer;

	TCPNetworkSession( boost::asio::io_service& io_service , TCPNetworkListener* handler, long clientId) :
	m_socket(io_service),
		m_IOService(io_service),
		m_networkHandler(handler),
		m_clientId(clientId),
		m_sendingData(false)
	{
	}

	tcp::socket& GetSocket()
	{
		return m_socket;
	}

	void StartNewSession()
	{
		//notify of new connection established
		if (m_networkHandler)
		{
			m_networkHandler->ClientConnected(shared_from_this());
		}

		m_socket.set_option(boost::asio::socket_base::keep_alive(true));

		//try to read the first message data
		m_socket.async_read_some(
			boost::asio::buffer(m_readBuffer, SOCKETBUFFERLENGTH),
			boost::bind(&TCPNetworkSession::HandleReadData, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	}

	void HandleReadData( const boost::system::error_code& error, std::size_t bytes_transferred )
	{
		if (error)
		{
			//we have got disconnected
			if (m_networkHandler)
			{
				m_networkHandler->ClientDisconnected(shared_from_this());
			}

			return;
		}

		//we received new data
		if (m_networkHandler)
		{
			m_readBuffer[bytes_transferred] = 0;
			std::string strData(reinterpret_cast<const char*>(m_readBuffer.begin()), bytes_transferred);
			m_networkHandler->ClientDataReceived(shared_from_this(), strData);
		}

		//try to read the next message data
		m_socket.async_read_some(
			boost::asio::buffer(m_readBuffer, SOCKETBUFFERLENGTH),
			boost::bind(&TCPNetworkSession::HandleReadData, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	}
};

bool TCPNetworkListener::StartListener()
{
	//check if already started
	if (m_SocketAcceptor.is_open())
	{
		return false;
	}

	//create the socket acceptor
	m_SocketAcceptor.open(m_TCPEndpoint.protocol());
	m_SocketAcceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	m_SocketAcceptor.bind(m_TCPEndpoint);
	m_SocketAcceptor.listen();

	//accept async connections
	m_lastConnectedClientId++;
	SharedPtr new_session(new TCPNetworkSession(m_IOService, this, m_lastConnectedClientId));
	m_SocketAcceptor.async_accept(new_session->GetSocket(),
		boost::bind(&TCPNetworkListener::HandleNewConnection, this, new_session,
		boost::asio::placeholders::error));

	//all fine
	m_listenerState = NLState_Running;
	return true;
}

void TCPNetworkListener::HandleNewConnection( SharedPtr session, const boost::system::error_code& error )
{
	if (error)
	{
		return;
	}

	session->StartNewSession();

	//accept new async connections
	m_lastConnectedClientId++;
	SharedPtr new_session(new TCPNetworkSession(m_IOService, this, m_lastConnectedClientId));
	m_SocketAcceptor.async_accept(new_session->GetSocket(),
		boost::bind(&TCPNetworkListener::HandleNewConnection, this, new_session,
		boost::asio::placeholders::error));
}

void TCPNetworkListener::ClientConnected(SharedPtr const& session) const {
	std::cout  << " id " << session->m_clientId << "\n";
}
void TCPNetworkListener::ClientDisconnected(SharedPtr const& session) const {
	std::cout << " id " << session->m_clientId << "\n";
}
void TCPNetworkListener::ClientDataReceived(SharedPtr const& session, std::string data) const {
	std::cout << " id " << session->m_clientId << ": '" << data << "'\n";
}

int main()
{
	TCPNetworkListener listener;
	listener.StartListener();
	listener.m_IOService.run();
}
