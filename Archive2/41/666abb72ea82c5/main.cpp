#include <iostream>
#include <functional>
#include <list>
#include <algorithm>

using namespace std;

class Event {
    function<double()> func;
public:
    template <typename H, typename... Args>
    Event(H &&f, Args&&... args) 
          : func(bind(std::forward<H>(f), std::forward<Args>(args)...)) {}

    void run()
    {
        double ret = func();
        std::cout << ret << "\n";
    }
};

double twoDoubleParam(double a, double b) {
    return a + b;
}

double threeIntParam(int a, int b, int c) {
    return (a + b) / c;
}

int main(int argc, char* argv[]) {
    std::list<Event> events;
    events.push_back(Event(twoDoubleParam, 1.0, 3.5));
    events.push_back(Event(threeIntParam, 2, 4, 2));
    std::for_each(events.begin(), events.end(), [&](Event &event)
    {
        event.run();
    });
}