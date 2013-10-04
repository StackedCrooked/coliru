#include <iomanip>
#include <random>
#include <queue>
#include <iostream>
#include <cstdlib>

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

#if 0
    std::random_device rd;
    std::uniform_real_distribution<double> dist(0, 1000000);
    
    
    for (int i = 0; i < 100; ++i) {
        queue.push(Event{dist(rd), i});
    }
#else

    double action_time = 0;
    srand((unsigned int)time(NULL));
    while(action_time < 100) {
        auto u = (double)rand()/(double)RAND_MAX;
        action_time += -log(u)/25;
        Event e = {action_time, 0};
        queue.push(e);
    }
#endif
    
    
    while (!queue.empty()) {
        std::cout << std::fixed << queue.top().event_time << "\n";
        queue.pop();
    }
}

