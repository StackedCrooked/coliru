#include <iostream>
#include <map>
#include <string>
#include <vector>

template<typename T>
class EventDispatcher {
    public:
        typedef void (*EventHandler)(T event);

        EventDispatcher() { }
        ~EventDispatcher() { }

        void addListener(const std::string eventName, EventHandler handler) { }
        void fireEvent(T event) {}

    private:
        typedef std::vector<EventHandler> ListenersList;
        typedef std::map<std::string, ListenersList*> ListenersMap;

        ListenersMap listeners;
};

int main()
{
    EventDispatcher<int> e;
    std::cout << "All is well\n";
}