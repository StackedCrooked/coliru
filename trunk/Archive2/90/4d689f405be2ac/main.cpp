#include <iostream>
#include <string>
#include <vector>

//positionCallback(.......);

struct TimingPoint
{
    int sync;
    int offset;
    bool selected;
};

class Audio
{
    public:
    Audio()
    {
    }
    
    void register_event(TimingPoint &point)
    {
        point.sync = 4;
    }
};


class Session
{
    public:
    std::vector<TimingPoint> timing_points;
    Audio *audio;
    
    void register_tick(int time)
    {   audio = new Audio();
    
        TimingPoint tp;
        tp.offset = time;
        tp.selected = false;
        
        timing_points.push_back(tp);

        audio->register_event(timing_points.back());
        
        std::cout << timing_points.back().offset << " " << timing_points.back().sync ;
    }
};

int main()
{
    Session session;
    session.register_tick(500);
    return 0;
}
