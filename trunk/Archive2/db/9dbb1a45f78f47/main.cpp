#include <iostream>
#include <memory>
#include <functional>
using namespace std;

class Thing
{
public:
    Thing() : x(0)
    {

    }

    Thing(Thing const &other)
    {
        this->x = other.x;
        std::cout << "Copy constructed Thing!\n";
    }

    Thing(Thing &&other)
    {
        this->x = other.x;
        std::cout << "Move constructed Thing!\n";
    }

    Thing & operator = (Thing const &other)
    {
        this->x = other.x;
        std::cout << "Copied Thing!\n";
        return (*this);
    }

    Thing & operator = (Thing && other)
    {
        this->x = other.x;
        std::cout << "Moved Thing!\n";
        return (*this);
    }

    int x;
};

class Event
{
public:
    Event() { }
    Event(function<void()> && f) : m_f() { }
    void SetF(function<void()> && f) { m_f = std::move(f); }

private:
    function<void()> m_f;
};

int main() {

    auto lambda = [](Thing &thing) { std::cout << thing.x << "\n"; };

    Thing thing;
    std::cout << "without unique_ptr: \n";
    Event ev(std::bind(lambda,thing));
    std::cout << "\n";

    std::cout << "with unique_ptr, no make_unique\n";
    unique_ptr<Event> ev_p(new Event(move(std::bind(lambda,thing))));
    std::cout << "\n";

    std::cout << "with make_unique: \n";
    auto ev_ptr = make_unique<Event>(move(std::bind(lambda,thing)));
    std::cout << "\n";

    std::cout << "with SetF: \n";
    ev_ptr.reset(nullptr);
    ev_ptr = make_unique<Event>();
    ev_ptr->SetF(std::bind(lambda,thing));
    std::cout << "\n";

    return 0;
}