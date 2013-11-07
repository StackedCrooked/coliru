#include <iostream>
#include <string>
#include <sstream>


#define TRACE //std::cout << __PRETTY_FUNCTION__ << std::endl;


struct IsOwner
{
    IsOwner() : owns(true) {}
    
    IsOwner(const IsOwner& rhs)  = delete;
    IsOwner& operator=(const IsOwner& rhs) = delete;
    
    IsOwner(IsOwner&& rhs) : owns(true)
    {
        rhs.owns = false;
    }
    
    IsOwner& operator==(IsOwner&& rhs)
    {
        this->owns = rhs.owns;
        rhs.owns = false;
        return *this;
    }
    
    bool owns;
};

struct Log;

template<typename, typename>
struct LogItem;

void print(const Log&);

template<typename T, typename U>
void print(const LogItem<T, U>& item);

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
        TRACE
    }
    
    LogItem(LogItem<Head, Tail>&&) = default;
    
    ~LogItem()
    {
        if (owns.owns)
        {
            print(head);
            print(tail);
        }
    }
    
    
    template<int N>
    using Literal = const char[N];
    
    template<int N>
    auto operator<<(Literal<N>&& literal) -> LogItem<LogItem<Head, Tail>, Literal<N>>
    {
        TRACE
        return LogItem<LogItem<Head, Tail>, Literal<N>>(
            std::move(*this),
            std::forward<Literal<N>>(literal));
    }

    template<typename T>
    auto operator<<(T&& t) -> LogItem<LogItem<Head, Tail>, T>
    {
        TRACE
        return LogItem<LogItem<Head, Tail>, T>(
            std::move(*this),
            std::forward<T>(t)
        );
    }
    
    Head head;
    Tail tail;
    IsOwner owns;
};


template<typename T>
void print(const T& t)
{
    std::cout << t;
}

void print(const Log&)
{
}

template<typename T, typename U>
void print(const LogItem<T, U>& item)
{
    print(item.head);
    print(item.tail);        
}

struct Log
{
    Log() {}
    Log(Log&&) = default;
    template<typename T>
    auto operator<<(T&& t) -> LogItem<T, Log>
    {
        TRACE
        return LogItem<T, Log>(std::forward<T>(t), Log{});
    }
};



int main()
{
    Log() << 1;
    std::cout << std::endl;
    
    Log() << 1 << 2;
    std::cout << std::endl;
    
    Log() << 1 << 2 << 3;
}
