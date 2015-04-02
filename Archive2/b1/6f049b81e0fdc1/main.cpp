#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <queue>

static size_t mark() {
    static const auto t0 = boost::posix_time::microsec_clock::local_time();
    return (boost::posix_time::microsec_clock::local_time() - t0).total_milliseconds();
}

class Test : public std::enable_shared_from_this<Test> {
    using guard = boost::lock_guard<boost::mutex>;
  public:
    Test() : io_(), work_(boost::asio::io_service::work(io_)) {
        io_thread = boost::thread([this] { io_.run(); });
    }

    void TimedOpen(int num, int duration);

    void Stop() {
        {
            guard lk(mx_);
            if (work_) work_.reset();
        }
        io_thread.join();
    }

    ~Test() {
        Stop();

        guard lk(mx_);
        timers_ex_.clear();
    }

  private:
    struct Session : std::enable_shared_from_this<Session> {
        Session(boost::asio::io_service &io, int type) : strand_(io), timer_(io), type(type) {}

        void Enqueue(int duration) {
            auto This = shared_from_this();
            strand_.post([This,duration,this] { 
                    std::cout << "t0 + " << std::setw(4) << mark() << "ms Enqueue for Number: "  << type <<  " (dur:"  << duration       <<  ")\n";
                    This->queue_.push(duration);
                    if (This->queue_.size() == 1)
                        This->Wait();
                });
        }

      private:
        boost::asio::strand strand_;
        boost::asio::deadline_timer timer_;
        int type;
        std::queue<int> queue_;

        void Close() {
            assert(!queue_.empty());
            std::cout << "t0 + " << std::setw(4) << mark() << "ms Close for Number :  "  << type <<  " (dur:"  << queue_.front() <<  ") (depth " << queue_.size() << ")\n";

            queue_.pop();
            Wait();
        }
        void Wait() {
            if (!queue_.empty()) {
                std::cout << "t0 + " << std::setw(4) << mark() << "ms Open for Number :   "  << type <<  " (dur:"  << queue_.front() <<  ") (depth " << queue_.size() << ")\n";
                timer_.expires_from_now(boost::posix_time::milliseconds(queue_.front()));
                timer_.async_wait(strand_.wrap(std::bind(&Session::Close, shared_from_this())));
            }
        }
    };

    mutable boost::mutex mx_;
    boost::asio::io_service io_;
    boost::optional<boost::asio::io_service::work> work_;
    std::map<int, std::shared_ptr<Session> > timers_ex_;
    boost::thread io_thread;
};

void Test::TimedOpen(int type, int duration) {
    guard lk(mx_);

    auto &session = timers_ex_[type];
    if (!session) session = std::make_shared<Session>(io_, type);

    session->Enqueue(duration);
}

int main() {
    auto t = std::make_shared<Test>();
    t->TimedOpen(1, 300);
    t->TimedOpen(2, 150);
    t->TimedOpen(1,  50);
    t->TimedOpen(2,  20);

    boost::this_thread::sleep_for(boost::chrono::milliseconds(400));
    std::cout << "================\n";
    t->TimedOpen(1,  50);
    t->TimedOpen(2,  20);
    t->TimedOpen(1, 300);
    t->TimedOpen(2, 150);

    t->Stop();
}
