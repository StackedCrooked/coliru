#include <iomanip>
#include <random>
#include <queue>
#include <iostream>

struct Event {
    double event_time;
    int type;
};

class EventCompare {
public:
    bool operator()(Event &a, Event &b) {
        return a.event_time > b.event_time;
    }
};


int main()
{
    std::priority_queue<Event, std::vector<Event>, EventCompare> queue;

    std::random_device rd;
    std::uniform_real_distribution<double> dist(0, 1000000);
    
    
    for (int i = 0; i < 100; ++i) {
        queue.push(Event{dist(rd), i});
    }
    
    
    while (!queue.empty()) {
        std::cout << std::fixed << queue.top().event_time << "\n";
        queue.pop();
    }
}

