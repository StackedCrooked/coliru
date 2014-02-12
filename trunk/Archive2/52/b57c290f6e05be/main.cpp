

struct Internal {};

enum EventId
{
    stop,
    start,
    restart
};

template<EventId>
struct event
{
    Internal in;
};

template<typename T>
void process_event(T)
{
}


int main()
{
    Internal in;
    process_event(event<start>{in});
    process_event(event<stop>{in});
    process_event(event<restart>{in});
}
