#include <iostream>
#include <atomic>
#include <mutex>


#define TRACE std::cout << __FUNCTION__ << std::endl;


// print when locked and unlocked
struct DebugLock : std::lock_guard<std::mutex>
{
    DebugLock(std::mutex& m) : std::lock_guard<std::mutex>(m)
    {
        TRACE
    }
    
    ~DebugLock()
    {
        TRACE
    }
};

class Person
{
public:    
    void set_name(const std::string& name)
    {
        TRACE
        DebugLock lock(mutex);
        this->name = name;
    }
    
    std::string get_name() const
    {
        TRACE
        DebugLock lock(mutex);
        return name;
    }
    
private:
    mutable std::mutex mutex;
    std::string name;
};


int main()
{
    Person p;
    p.set_name(p.get_name());
}