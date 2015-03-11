#include <chrono>
#include <ctime>
#include <string>
#include <iostream>
#include <sstream>
#include <thread>
#include <list>
#include <unordered_map>
#include <type_traits>

class attribute
{
public:
    constexpr attribute() 
      : attribute("undefined")
    {}

    constexpr explicit attribute(const char* name) 
      : name_(name) 
    {}
    
    attribute(const attribute&) = default;
    attribute(attribute&&)      = default;
    
    attribute& operator=(const attribute&) = default;
    attribute& operator=(attribute&&)      = default;

    virtual ~attribute() 
    {}
    
    const char* name() const noexcept
    {
        return name_;        
    }

    virtual void value(std::ostream& sink, const std::stringstream& ctx) const noexcept
    {}
    
private:
    const char* name_;
};

class local_time_attr final : public attribute
{
public:
    explicit local_time_attr(const std::string& format) noexcept
      : attribute("local_time")
      , format_(format)
    {}

    void value(std::ostream& sink, const std::stringstream& ctx) const noexcept override
    {
        const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        const auto local = *std::localtime(&now);
        char buffer[128]{}; 
        std::strftime(buffer, std::extent<decltype(buffer)>::value, format_.c_str(), &local);
        sink << buffer;
    }
    
private:
    const std::string format_;
};

class current_thread_id_attr final : attribute
{
public:
    current_thread_id_attr() 
      : attribute("current_thread_id")
    {}

    void value(std::ostream& sink, const std::stringstream& ctx) const noexcept override
    {
        sink << std::hash<std::thread::id>()(std::this_thread::get_id());
    }    
};

class message_attr final : attribute
{
public:
    message_attr()
      : attribute("message")
    {}
    
    void value(std::ostream& sink, const std::stringstream& ctx) const noexcept override
    {
        sink << ctx;
    }
};

class synchronous_sink
{
public:
    synchronous_sink(std::ostream& sink, std::initializer_list<attribute> attrs) 
      : sink_(sink)
    {
        for (auto& attr : attrs)
        {
            attrs_[attr.name()] = std::move(attr);
        }
    }
    
    void write(const std::stringstream& message) const
    {

    }
    
private:
    std::ostream& sink_;
    std::unordered_map<const char*, attribute> attrs_;
};

int main(int argc, char* argv[])
{
    local_time_attr time("%Y.%m.%d %H:%M:%S");
    current_thread_id_attr th;
    
    return 0;   
}
