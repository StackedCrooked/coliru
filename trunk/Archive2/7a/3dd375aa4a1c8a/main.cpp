#include <boost/asio.hpp>
#include <boost/optional.hpp>
#include <boost/make_shared.hpp>
#include <boost/thread.hpp>
#include <fstream>
#include <queue>
#include <boost/bind.hpp>

using boost::asio::ip::tcp;

struct Noop {
    template <typename...T> void operator()(T...) const {}
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
    tcp::socket ss;
    boost::mutex mx;
    std::vector<tcp::socket> connections;

    Server(int serverPort = 6767) : 
        iosvc(),
        work(boost::asio::io_service::work(iosvc)),
        data_worker(&Server::generate_jobs, this),
        io_worker(boost::bind(&boost::asio::io_service::run, &iosvc)),
        acceptor(iosvc, tcp::endpoint(tcp::v4(), serverPort)),
        ss(iosvc)
    {
        acceptor.async_accept(ss, boost::bind(&Server::add_client, this, boost::asio::placeholders::error));
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
            connections.push_back(std::move(ss)); 
        }

        if (ec != boost::asio::error::operation_aborted) {
            acceptor.async_accept(ss, boost::bind(&Server::add_client, this, boost::asio::placeholders::error));
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
        auto data = boost::make_shared<std::string>(cmd.serialize());
        *data += '\n';

        boost::lock_guard<boost::mutex> lk(mx);
        for (auto sit = connections.begin(); sit != connections.end();)
        {
            if (sit->is_open())
            {
                boost::system::error_code ec;
                auto end_point =  sit->remote_endpoint(ec);
                if (ec) {
                    sit->close();
                } else
                {
                    //std::cout << "[Sending to " << end_point << "]\n";
                    sit->async_send(boost::asio::buffer(*data),
                            [data/*keep-alive*/](boost::system::error_code, size_t) { });
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
    boost::this_thread::sleep_for(boost::chrono::seconds(60));
}
