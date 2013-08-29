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
            std::cout << "add_listener: " << listener << std::endl;
            listeners.insert(listener);
        }
        
        void remove_listener(Listener* listener)
        {
            std::cout << "remove_listener: " << listener << std::endl;
            listeners.erase(listener);
        }
        
        std::set<Listener*> listeners;
    };
    
    struct Listener
    {        
        Listener(const std::string& name, Event& evt) :
            name(name),
            event(&evt)
        {
            event->add_listener(this);
        }
        
        ~Listener()
        {
            event->remove_listener(this);
        }
        
        Listener(const Listener& rhs) : 
            name(rhs.name),
            event(rhs.event)
        {
            event->add_listener(this);
        }
        
        Listener& operator=(Listener rhs) // copy swap
        {
            this->swap(rhs);
            return *this;
        }
        
        void swap(Listener& rhs)
        {
            using std::swap;
            swap(name, rhs.name);
            swap(event, rhs.event);
        }
        
        std::string name;
        Event* event;
    };
    
    void run()
    {
        Event event;
        Listener a("a", event);
        Listener b("b", event);
        
        std::cout << "1" << std::endl;
        a = b;
        b = a;
        std::cout << "2" << std::endl;
    }
};
    

int main()
{
    Test().run();
}