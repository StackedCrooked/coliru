#include <iostream>
#include <atomic>
#include <mutex>

class Person
{
public:
    void set_age(int age)
    {
        this->age = age;
    }
    
    int get_age() const
    {
        return age;
    }
    
    void set_name(const std::string& name)
    {
        std::lock_guard<std::mutex> lock(mutex);
        this->name = name;
    }
    
    std::string get_name() const
    {
        std::lock_guard<std::mutex> lock(mutex);
        return name;
    }
    
private:
    mutable std::mutex mutex;
    std::atomic<int> age;
    std::string name;
};


int main()
{
}