#include <iostream>
#include <string>
#include <sstream>

struct Log;

template<typename, typename>
struct LogItem;

void print(const Log&);

template<typename T, typename U>
void print(const LogItem<T, U>& item, char endl = 0);

template<typename T>
void print(const T& t);


template<typename Head, typename Tail>
struct LogItem
{   
    template<typename T, typename U>
    LogItem(T&& t, U&& u) :
        head(std::forward<T>(t)),
        tail(std::forward<U>(u))
    {
        // std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    
    LogItem(LogItem<Head, Tail>&&) = default;
    
    ~LogItem()
    {
        if (owns())
        {
            print(*this, '\n');
        }
    }

    template<typename T>
    auto operator<<(T&& t) -> LogItem<LogItem<Head, Tail>, T>
    {
        // std::cout << __PRETTY_FUNCTION__ << std::endl;
        return LogItem<LogItem<Head, Tail>, T>(
            std::move(*this),
            std::forward<T>(t)
        );
    }
    
    bool owns() const
    {
        return owns_.owns;
    }
    
    void disown() const
    {
        owns_.disown();
    }
    
    Head head;
    Tail tail;
    
    // Helper which prevents me from having to implement move constructor.
    struct IsOwner
    {
        IsOwner() : owns(true) {}    
        IsOwner(const IsOwner& rhs)  = delete;
        IsOwner& operator=(const IsOwner& rhs) = delete;    
        IsOwner(IsOwner&& rhs) : owns(true) { rhs.owns = false; }
        IsOwner& operator==(IsOwner&& rhs) { this->owns = rhs.owns; rhs.owns = false; return *this; }    
        void disown() const { owns = false; }    
        mutable bool owns;
    };

    IsOwner owns_;
};


template<typename T>
void print(const T& t)
{
    std::cout << t;
}

void print(const Log&)
{
    // dummy
}

template<typename T, typename U>
void print(const LogItem<T, U>& item, char endl)
{
    if (item.owns())
    {
        print(item.head);
        print(item.tail);
        if (endl)
        {
            print(endl);
        }
        item.disown();
    }
}

struct Log
{
    Log() {}
    
    Log(Log&&) = default;
    
    template<typename T>
    auto operator<<(T&& t) -> LogItem<T, Log>
    {
        return LogItem<T, Log>(std::forward<T>(t), Log{});
    }
};


int main()
{
    Log() << 1;    
    Log() << 1 << 2;
    Log() << 1 << 2 << 3;
    Log() << "char array";
    
    std::string name = "John";
    Log() << "Name: " << name << ". Size: " << name.size();
}
