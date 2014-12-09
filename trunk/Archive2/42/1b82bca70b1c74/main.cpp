#include <string>
#include <iostream>
#include <deque>
#include <chrono>
#include <thread>

#include <boost/scoped_ptr.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

static constexpr auto MIN_QUEUE_WORK = 10;
static constexpr auto MAX_QUEUE_WORK = 40; // 4000;

class A {
  private:
    boost::thread myProducerThread;
    boost::thread myConsumerThread;

    boost::mutex mutex_;
    boost::condition_variable pushed_, popped_;

    struct Record {
        char response[128];

        Record(const char *response) {
            memset(this->response, 0, sizeof(this->response));
            strcpy(this->response, response);
        }

        ~Record() {}

        Record &operator=(const Record &cmd) {
            if (this == &cmd) // Same object?
            {
                return *this;
            }

            memset(this->response, 0, sizeof(this->response));
            strcpy(this->response, cmd.response);
            return *this;
        }
    };

    typedef std::deque<Record> RecordsQueue;
    RecordsQueue queue_;

  public:
    void RunThreads();
    void RunProducer();
    void RunConsumer();

    void ProducerWait();
    void ConsumerWait();
};

void A::RunThreads() {
    myProducerThread = boost::thread(boost::bind(&A::RunProducer, this));
    myConsumerThread = boost::thread(boost::bind(&A::RunConsumer, this));

    myProducerThread.join();
    myConsumerThread.join();
}

void A::RunProducer() {
    int i = 0;

    while (i<1000) {
        boost::this_thread::yield();

        boost::mutex::scoped_lock lock(mutex_);
        popped_.wait(lock, [this] { return queue_.size()<MAX_QUEUE_WORK; });

        queue_.push_back(Record { std::to_string(i).c_str() });
        std::cout << "Added: " << std::to_string(i) << " size: " << queue_.size() << std::endl;
        i++;
        pushed_.notify_one();
    }
}

void A::RunConsumer() {
    while (true) {
        boost::this_thread::yield();

        boost::mutex::scoped_lock lock(mutex_);
        pushed_.wait(lock, [this]{return queue_.size()>MIN_QUEUE_WORK;});

        Record res = queue_.front();
        std::cout << "Processed: " << res.response << std::endl;
        queue_.pop_front();

        popped_.notify_one();
    }
}

int main() {
    A a;
    a.RunThreads();
}
