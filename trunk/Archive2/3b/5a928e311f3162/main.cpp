#ifndef CEPH_KVSMONITOR_H
#define CEPH_KVSMONITOR_H

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

#include <map>
#include <string>
#include <stdlib.h>

/*
 * number of threads involved in
 * *all* I/O operations of io_service (also w/ clients)
 */
#define KV_IOTHREADS_NUM 1
#define KV_SERVER_PORT   5002
#define KV_BUFMAXLEN     1024

using boost::asio::ip::tcp;

class KVSMonitor;
class ClientSession;

enum KVCommand {
    SET  = 'S',
    GET  = 'G',
    LIST = 'L',
    DEL  = 'D'
};

class KVSMonitor {
public:
    KVSMonitor() :
		serving(false) {	}

	void init();
	void serve();
	void handle_client(ClientSession* new_connection, const boost::system::error_code& error);
	void stop_server();

	std::map <std::string, int> db;
private:
	bool serving;
	tcp::acceptor* acceptor_;
	boost::asio::io_service io_service;
	boost::thread_group tg;

};

class ClientSession {
public:
	ClientSession(boost::asio::io_service& io_service, KVSMonitor* kvs) : socket_(io_service), kvs(kvs) { }
	tcp::socket& socket();
	void start();

private:
	void handle_read(const boost::system::error_code& error, size_t bytes_transferred);
	void handle_write(const boost::system::error_code& error);

	std::string trim_str(std::string str);
	tcp::socket socket_;
	char data_[KV_BUFMAXLEN];
	KVSMonitor* kvs;
};

#endif

#include <sstream>
#include <cstring>

#include <boost/thread/thread.hpp>

using boost::asio::ip::tcp;
using namespace std;

void KVSMonitor::init() {
    cout	<< "KVSMonitor::init... " << boost::this_thread::get_id() << endl;

	if (serving) return;

	acceptor_ = new tcp::acceptor(io_service, tcp::endpoint(tcp::v4(), KV_SERVER_PORT));
	acceptor_->set_option(tcp::acceptor::reuse_address(true));
	serve();

	for (int i = 0; i < KV_IOTHREADS_NUM; ++i)
		tg.create_thread(boost::bind(&boost::asio::io_service::run, &io_service));
}

void KVSMonitor::serve() {
	serving = true;
	ClientSession* new_connection = new ClientSession(acceptor_->get_io_service(), this);

	acceptor_->async_accept(new_connection->socket(),
			boost::bind(&KVSMonitor::handle_client, this, new_connection,
					boost::asio::placeholders::error));
}

void KVSMonitor::handle_client(ClientSession* new_connection,
		const boost::system::error_code& error) {

	if (!error)
		boost::thread workerThread(&ClientSession::start, new_connection);
	else
		delete new_connection;

	if (serving)
		serve();
}

void KVSMonitor::stop_server() {
	try {
		cout	<< "Shutdown server" << endl;
		serving = false;
		io_service.stop();
		tg.join_all();
		delete acceptor_;
	} catch (std::exception& e) {
		cout << "Exception in stop_server" << e.what() << endl;
	}
}


/********** ClientSession **********/

tcp::socket& ClientSession::socket() {
	return socket_;
}

void ClientSession::start() {
	socket_.async_read_some(boost::asio::buffer(data_, KV_BUFMAXLEN),
			boost::bind(&ClientSession::handle_read, this,
			  boost::asio::placeholders::error,
			  boost::asio::placeholders::bytes_transferred));
}

std::string ClientSession::trim_str(std::string str){
	size_t first = str.find_first_not_of(" \n\r\t");
	size_t last = str.find_last_not_of(" \n\r\t");
	str = str.substr(first, (last-first+1));
	str.resize(last+1);
	return str;
}

void ClientSession::handle_read(const boost::system::error_code& error, size_t bytes_transferred) {
	if (!error) {
        std::istringstream request(std::string(data_, bytes_transferred));
        boost::asio::streambuf resp;
        std::ostream os(&resp);

        char cmd_char = 0;
        std::string key;
        int value;
        if (request >> cmd_char) switch(cmd_char) {
            case SET:                          
                if (request >> key >> value)
                    kvs->db[key] = value;

                os << "A";
                break;
            case GET:
                if (request >> key)
                    os << kvs->db[key];
                break;

            case LIST:
                for (auto const& e : kvs->db)
                    os << e.first << ": " << e.second << "; ";
                break;

            case DEL: 
                if (request >> key)
                    kvs->db.erase(key);

                os << "A";
                break;
            default: 
                os << "NACK.";
        }

		cout << "resp: " << &resp << "*" << endl;
		cout << "len: " << resp.size() << "*" << endl;
		std::size_t written = boost::asio::write(socket_, resp);
		cout << "written: " << written << endl;

		boost::system::error_code ignored_ec;
		socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
		socket_.close();
	} else
		delete this;
}

int main() {
	KVSMonitor kvs;
	kvs.init();

	while (true)
		boost::this_thread::sleep( boost::posix_time::seconds(5) );
}
