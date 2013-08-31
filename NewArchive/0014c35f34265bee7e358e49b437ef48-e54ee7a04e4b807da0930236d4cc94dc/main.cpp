#include <future>
#include <memory>
#include <stdexcept>
#include <vector>


// wraps a weak_ptr and prevents the user from
// getting a shared_ptr (and extend the lifetime)
template<typename T>
struct Expirable
{
    explicit Expirable(const std::shared_ptr<T> & p) : wp(p)
    {
    }
    
    template<typename F>
    auto execute(const F& f) -> typename std::result_of<F(T&)>::type
    {
        auto shared = wp.lock();
        if (!shared) throw std::runtime_error("expired");
        return f(*shared);
    }
    
private:    
    std::weak_ptr<T> wp;
};



// Protocol owns Session objects.
// Session must not outlive Protocol    
struct Session
{
};

struct Protocol
{    
    Expirable<Session> open_Session()
    {
        Sessions.emplace_back(new Session);
        return Expirable<Session>(Sessions.back());
    }
    
private:
    std::vector<std::shared_ptr<Session>> Sessions;
};


int main()
{
    Protocol p;
    Expirable<Session> s = p.open_Session();
        
    s.execute([](Session&) {
        // ...
    });    
}