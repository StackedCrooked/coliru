#include <chrono>
#include <cstring>
#include <iosfwd>
#include <system_error>
#include <semaphore.h>


struct Semaphore
{
    Semaphore()
    {
        if (-1 == sem_init(&mSem, 0, 0))
        {
            throw std::system_error(std::error_code(errno, std::system_category()), strerror(errno));
        }
    }

    ~Semaphore()
    {
        if (-1 == sem_destroy(&mSem))
        {
            // silently discard error
        }
    }

    Semaphore(const Semaphore&) = delete;
    Semaphore& operator=(const Semaphore&) = delete;

    void post()
    {
        if (-1 == sem_post(&mSem))
        {
            throw std::system_error(std::error_code(errno, std::system_category()), strerror(errno));
        }
    }

    void wait()
    {
        if (-1 == sem_wait(&mSem))
        {
            throw std::system_error(std::error_code(errno, std::system_category()), strerror(errno));
        }
    }

    enum class Status
    {
        Timeout,
        NoTimeout
    };
    
    friend std::ostream& operator<<(std::ostream& os, Status status);

    template<typename Rep, typename Period>
    Status wait_for(std::chrono::duration<Rep, Period> requested_duration)
    {
        using namespace std::chrono;

        auto duration_s = duration_cast<seconds>(requested_duration);
        auto duration_ns = duration_cast<nanoseconds>(requested_duration) - duration_s;

        timespec ts;
        ts.tv_nsec = duration_ns.count();
        ts.tv_sec = duration_s.count();

        if (-1 == sem_timedwait(&mSem, &ts))
        {
            switch (errno)
            {
                case EINVAL:
                case EINTR: // TODO: figure out how interrupts should be handled
                {
                    throw std::system_error(std::error_code(errno, std::system_category()), strerror(errno));
                }
                case ETIMEDOUT:
                {
                    return Status::Timeout;
                }
                default:
                {
                    throw std::system_error(std::error_code(errno, std::system_category()), strerror(errno));
                }
            }
        }

        return Status::NoTimeout;
    }

    bool try_wait()
    {
        if (-1 == sem_trywait(&mSem))
        {
            auto e = errno;
            switch (e)
            {
                case EAGAIN:
                case EINTR: // treat interrupt as a failed try
                {
                     return false;
                }
                case EDEADLK: // "Deadlock was detected" (TODO: find out how this should be handled)
                case EINVAL:
                {
                    throw std::system_error(std::error_code(errno, std::system_category()), strerror(errno));
                }
            }
        }
    }

    int get() const
    {
        int result = 0;
        if (-1 == sem_getvalue(&mSem, &result))
        {
            throw std::system_error(std::error_code(errno, std::system_category()), strerror(errno));
        }
        return result;
    }

private:
    mutable sem_t mSem;
};


#include <iostream>


std::ostream& operator<<(std::ostream& os, Semaphore::Status status)
{
    return os << "Semaphore::Status(" << (status == Semaphore::Status::Timeout ? "Timeout" : "NoTimeout") << ")";
}
    
    
int main()
{
    Semaphore sem;
    std::cout << "sem=" << sem.get() << std::endl;
    sem.post();
    std::cout << "sem=" << sem.get() << std::endl;
    std::cout << sem.wait_for(std::chrono::seconds(1)) << std::endl;
    std::cout << sem.wait_for(std::chrono::seconds(1)) << std::endl;
    sem.post();
    sem.post();
    std::cout << "sem=" << sem.get() << std::endl;
    std::cout << sem.wait_for(std::chrono::seconds(1)) << std::endl;
    std::cout << sem.wait_for(std::chrono::seconds(1)) << std::endl;
}

