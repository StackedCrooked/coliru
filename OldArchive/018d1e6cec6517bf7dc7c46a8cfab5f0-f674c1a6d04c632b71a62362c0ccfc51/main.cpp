#include <iostream>
#include <memory>
#include <set>


struct Test
{    
    struct Listener;    
    
    struct Event
    {   
        void add_listener(Listener* listener)
        {
            listeners.insert(listener);
        }
        
        void remove_listener(Listener* listener)
        {
            listeners.erase(listener);
        }
        
        std::set<Listener*> listeners;
    };
    
    struct Listener
    {        
        Listener(const std::string& name, Event& evt) :
            name(name),
            event(&evt, [=](Event* e) { e->remove_listener(this); })
        {
            event->add_listener(this);
            std::cout << "Create Listener " << name << std::endl;
        }
        
        ~Listener()
        {
            std::cout << "Destroy Listener " << name << std::endl;
        }
        
        std::string name;
        std::shared_ptr<Event> event;
    };
    
    void run()
    {
        Event event;
        Listener a("a", event);
        Listener b("b", event);
        b = a;
    }
};
    

int main()
{
    Test().run();
}