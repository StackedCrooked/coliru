extern "C"
{
#include <sys/file.h> /* flock */
}

#include <iostream>
#include <system_error>
#include <atomic>
#include <thread>
#include <chrono>
#include <string>
#include <cstdio>
#include <cstddef>

inline std::system_error make_syserr(int e, const char * msg="")
{
    return std::system_error(std::error_code(e, std::system_category()), msg);
}

inline std::system_error make_syserr(std::errc e, const char * msg="")
{
    return std::system_error(static_cast<int>(e), std::system_category(), msg);
}

inline std::system_error make_syserr(int e, int line)
{
    // probably a dangling ref
    return make_syserr(e, std::to_string(line).c_str());
}

///////////////////////////////////////////////
///////////////////// FILE ////////////////////
///////////////////////////////////////////////
class File final
{
public:
    File(File const &) = delete;
    File & operator=(File const &) = delete;
 
    ///// Default
    File() : 
        m_locked(false),
        m_fileno(-1),
        m_handle(nullptr)
    { 
        std::cout << "DEFAULT CTOR\n";
    }

    ///// fopen
    explicit File(std::string const & path,
                  std::string const & mode) :
        File()
    {
        std::cout << "ARG CTOR\n";
        
        m_path = path;

        if ((m_handle = std::fopen(m_path.c_str(), mode.c_str())) == nullptr)
            throw make_syserr(errno, __LINE__);

        m_fileno = ::fileno(m_handle);
    }

    ////// move
    File(File && other) :
        m_locked(other.m_locked.load()),
        m_fileno(other.m_fileno),
        m_handle(other.m_handle), 
        m_path(std::move(other.m_path))
    { 
        std::cout << "MOVE CTOR\n";
    }

    File& operator=(File && other)
    {
        std::cout << "MOVE ASSIGN\n";

        this->m_locked = other.m_locked.load();
        this->m_fileno = other.m_fileno;
        this->m_locked = other.m_handle;
        this->m_path = std::move(other.m_path);
        return *this;
    }

    void lock()
    {
        if (m_locked.load())
            throw make_syserr(std::errc::resource_deadlock_would_occur);

        if (::flock(m_fileno, LOCK_EX | LOCK_NB) == -1)
            throw make_syserr(errno, __LINE__);

        m_locked.store(true);
    }

    void unlock()
    {
        if (!m_locked.load())
            throw make_syserr(std::errc::resource_deadlock_would_occur);
            
        if (::flock(m_fileno, LOCK_UN | LOCK_NB) == -1)
            throw make_syserr(errno, __LINE__);
    
        m_locked.store(false);
    }

    ~File() 
    { 
        if (m_locked.load())
            unlock();
    }

    operator std::FILE * () noexcept { return m_handle; }
    operator std::FILE & () noexcept { return *m_handle; } // unsafe

private:
    std::atomic<bool> m_locked;
    int m_fileno;
    std::FILE * m_handle;
    std::string m_path;
};


int main(void)
{
    File f;
    f = std::move(File{"test", "w"});
    f.lock();

    // while sleeping run same binary as another process
    std::this_thread::sleep_for(std::chrono::seconds(5));
}

