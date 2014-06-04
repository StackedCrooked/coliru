#include <boost/asio.hpp>
#include <boost/optional.hpp>
#include <boost/make_shared.hpp>
#include <boost/thread.hpp>
#include <fstream>
#include <queue>
#include <boost/bind.hpp>

using boost::asio::ip::tcp;

struct Noop {
    typedef void result_type;
    void operator()(boost::shared_ptr<std::string>, boost::system::error_code, size_t) const {}
};

struct Command { 
    int value;

    Command(int i = -1) : value(i) {}

    friend std::ostream& operator<<(std::ostream& os, Command const& cmd) { 
        return os << "Command(" << cmd.value << ")";
    }

    std::string serialize() const { 
        std::ostringstream oss;
        oss << (*this);
        return oss.str();
    }
};

struct Server { 
    boost::asio::io_service iosvc;
    boost::optional<boost::asio::io_service::work> work;
    boost::thread data_worker, io_worker;

    tcp::acceptor acceptor;
    boost::shared_ptr<tcp::socket> newaccept;
    boost::mutex mx;
    typedef std::vector<boost::shared_ptr<tcp::socket> > conntable;
    conntable connections;

    Server(int serverPort = 6767) : 
        iosvc(),
        work(boost::asio::io_service::work(iosvc)),
        data_worker(&Server::generate_jobs, this),
        io_worker(boost::bind(&boost::asio::io_service::run, &iosvc)),
        acceptor(iosvc, tcp::endpoint(tcp::v4(), serverPort))
    {
        newaccept.reset(new tcp::socket(iosvc));
        acceptor.async_accept(*newaccept, boost::bind(&Server::add_client, this, boost::asio::placeholders::error));
    }

    ~Server()
    {
        acceptor.cancel();
        data_worker.interrupt();
        data_worker.join();

        work = boost::none;
        io_worker.join();
    }

    void add_client(boost::system::error_code ec) {
        if (!ec) {
            boost::lock_guard<boost::mutex> lk(mx);
            connections.push_back(newaccept);
        }

        if (ec != boost::asio::error::operation_aborted) {
            newaccept.reset(new tcp::socket(iosvc));
            acceptor.async_accept(*newaccept, boost::bind(&Server::add_client, this, boost::asio::placeholders::error));
        }
    }

  private:
    void generate_jobs() // we're on the data thread
    {
        try { 
            for(;;) {
                boost::this_thread::sleep_for(boost::chrono::milliseconds(200));
                boost::this_thread::interruption_point();

                std::cout << '.' << std::flush;

                static uint64_t id = 0;
                Command cmd(++id);
                iosvc.post(boost::bind(&Server::dispatch, this, cmd)); // to the IO thread!
            }
        }
        catch(boost::thread_interrupted const&) {
            std::cout << "generate_jobs is stopped" << std::endl;
        }
    }

    void dispatch(Command cmd) { // we're on the io service thread
        boost::shared_ptr<std::string> data = boost::make_shared<std::string>(cmd.serialize());
        *data += '\n';

        boost::lock_guard<boost::mutex> lk(mx);
        for (conntable::iterator sit = connections.begin(); sit != connections.end();)
        {
            if ((*sit)->is_open())
            {
                boost::system::error_code ec;
                tcp::endpoint end_point =  (*sit)->remote_endpoint(ec);
                if (ec) {
                    (*sit)->close();
                } else
                {
                    //std::cout << "[Sending to " << end_point << "]\n";
                    (*sit)->async_send(boost::asio::buffer(*data), 
                            boost::bind(Noop(), data /*keep-alive*/, _1, _2));
                }
                ++sit;
            } else
            {
                //std::cout << "\nRemoving closed connection\n";
                sit = connections.erase(sit);
            }
        }
    }

};

int main()
{
    Server r(6767);
    // run the server for 1 minute
    boost::this_thread::sleep_for(boost::chrono::seconds(10));
}
