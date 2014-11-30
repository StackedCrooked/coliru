#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/scoped_ptr.hpp>
#include <iostream>

static boost::mutex mutexCOM;

struct Navigation {
    void begin() {
        size_t count = 0;
        while(++count< 10) {
            {
                boost::mutex::scoped_lock lock(mutexCOM);
                std::cout << "-----shared function-----" << std::endl;
                boost::this_thread::sleep_for(boost::chrono::milliseconds(200));
                std::cout << "----Shared function will now end...-----" << std::endl;
            }
            boost::this_thread::sleep_for(boost::chrono::milliseconds(100)); // or boost::this_thread::yield e.g.
        }
        std::cout << "Navigation::begin() completed\n";
    }
};

struct mainclass {
    void run() {
        size_t count = 0;
        this->runNav();
        while (++count < (1ull<<20))
        {
            {
                boost::mutex::scoped_lock lock(mutexCOM);
                std::cout << "testing!" << std::endl;
            }

            boost::this_thread::yield();
        }
        std::cout << "mainclass::run() completed\n";
    }

    ~mainclass() {
        if (navThread.joinable())
        {
            std::cout << "Waiting for Navigation to end...\n";
            navThread.join();
        }
    }
  private:
    void runNav() {
        navThread = boost::thread(boost::bind(&Navigation::begin, *(this->nav)));
    }

    boost::scoped_ptr<Navigation> nav { new Navigation };
    boost::thread navThread;
};

int main() {
    mainclass instance;
    instance.run();
}
