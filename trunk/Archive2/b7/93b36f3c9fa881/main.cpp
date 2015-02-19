#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/make_shared.hpp>
#include <boost/bind.hpp>
#include <thread>
#include <mutex>
#include <chrono>
#include <memory>
#include <iostream>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>

using boost::asio::ip::udp;
typedef std::chrono::high_resolution_clock Clock;

namespace demo_results {
    using namespace boost::accumulators;

    static std::mutex mx;
    accumulator_set<double, stats<tag::mean, tag::median, tag::variance> > bufsize, mbps, micros;
}

struct Run {
    std::vector<char> buffer;
    int buffersToSend;
    int transferredBuffers;
    Clock::time_point start;
    Clock::duration elapsed;

    Run() :
    //buffer(rand()%1200 + 200, '\0'),
    buffer(1178, '\0'),
        //buffersToSend(rand()%10 + 1),
        buffersToSend(1000),
        transferredBuffers(0),
        start(Clock::now())
    {

    }

        void stopTimerAndLog()
        {
            using namespace std::chrono;

            Clock::duration const elapsed = Clock::now() - start;
            int tmm = duration_cast<microseconds>(elapsed).count();

            double mBitPerSecond = tmm
                ? buffer.size() * transferredBuffers * 8.0 / 1024 / 1024 / (tmm / 1000000.0)
                : std::numeric_limits<double>::infinity();

            std::lock_guard<std::mutex> lk(demo_results::mx);

            demo_results::bufsize(buffer.size());
            demo_results::micros(tmm);
            if (tmm)
                demo_results::mbps(mBitPerSecond);

#if 0
            std::cout << __FUNCTION__ << "  -----------------------------------------------\n";
            std::cout << __FUNCTION__ << ": " << "Buffer size: " << buffer.size()      << "\n";
            std::cout << __FUNCTION__ << ": " << "Num Buffers: " << transferredBuffers << "\n";
            std::cout << __FUNCTION__ << ": " << "Time: "        << tmm                << " micro_sec\n";
            std::cout << __FUNCTION__ << ": " << mBitPerSecond   << " MBit/s\n";
#endif
        }

    typedef boost::shared_ptr<Run> Ptr;
};

struct Demo {
    boost::asio::io_service                        m_IOService;
    std::unique_ptr<boost::asio::io_service::work> m_work;
    std::unique_ptr<boost::asio::ip::udp::socket>  m_pSocket;
    boost::asio::ip::udp::endpoint                 m_ReceiverEndpoint;
    std::thread                                  m_io_thread;

    Demo() :
        m_IOService(),
        m_work(new boost::asio::io_service::work(m_IOService)),
        m_io_thread([this] { m_IOService.run(); })
    {
    }

    ~Demo() {
        m_work.reset();
        m_io_thread.join();
    }

    void on_connect(std::string const& host, std::string const& port)
    {
        try {
            udp::resolver resolver(m_IOService);
            m_ReceiverEndpoint = *resolver.resolve(udp::resolver::query(udp::v4(), host, port));
            m_pSocket = std::unique_ptr<boost::asio::ip::udp::socket>(new boost::asio::ip::udp::socket(m_IOService));
            m_pSocket->open(udp::v4());
        }
        catch (std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    void perform_run(Run::Ptr state) {
        
    	for(decltype(state->buffersToSend) i = 0; i < state->buffersToSend; i++ )
		{
			std::fill(state->buffer.begin(), state->buffer.end(), i);

            m_pSocket->async_send_to(boost::asio::buffer(state->buffer),
                    m_ReceiverEndpoint,
                    boost::bind(&Demo::handle_sent, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred,
                        state));
		}
    }

    void handle_sent(boost::system::error_code const&error, size_t actually_transferred, Run::Ptr state)
    {
        assert(actually_transferred == state->buffer.size());
        state->transferredBuffers += 1;

        if (error) {
            // missing error propagation to main thread
            std::cerr << __FUNCTION__ << ": ERROR: Client error while sending (error code = " << error.message() << "): ";
            std::cerr << __FUNCTION__ << ": ERROR: Recovering...";
        }

		if (state->transferredBuffers >= state->buffersToSend ) {
			            state->stopTimerAndLog();
		}
    }

    void on_async_testrun() {
        perform_run(boost::make_shared<Run>());
    }
};


int main(int argc, char const** argv)
{
    assert(argc==3);
    
    std::cout << "*** Welcome ***" << std::endl;

    {
        Demo demo;
        demo.on_connect(argv[1], argv[2]);

		int max = 10;
        for (int i = 1; i<=max; ++i) {
			//std::cout << "round " << i << " of " << max << std::endl;
            //boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
            demo.on_async_testrun();
			//if ( i < max )
				//std::cin.get();
        }
    } // Demo destructor joins IO thread, making sure all stats are final

    using namespace boost::accumulators;
    std::cout << "avg. Buffer size: " << mean(demo_results::bufsize) << ", std.dev. "      << sqrt(variance(demo_results::bufsize)) << "\n";
    std::cout << "avg. b/w:         " << mean(demo_results::mbps)    << " mbps, std.dev. " << sqrt(variance(demo_results::mbps))    << "\n";
    std::cout << "avg. time:        " << mean(demo_results::micros)  << " micro_sec, std.dev. "   << sqrt(variance(demo_results::micros))  << "\n";

    //std::cin.get();

    return 0;
}

