#include <iostream>
#include <string>
#include <vector>

#include <boost/functional/factory.hpp>
#include <boost/function.hpp>


//////////////////////////////////////////////////////////////////

template<typename AbstractClass, typename ConcreteClass, typename Loop, typename EventHandler>
struct Factory {
    Factory (Loop& loop) : loop(loop) {
    }
    
    AbstractClass* operator ()(EventHandler& handler) {
        return new ConcreteClass(loop, handler);   
    }
private:
    Loop& loop;
};

struct EventLoop {};

struct IAvailabilityEventHandler {
    virtual void handle() = 0;
};

struct IComponent {
    virtual void print() = 0;
};

struct AmfComponent : public IComponent {
    AmfComponent(EventLoop*, IAvailabilityEventHandler& handler) : handler(handler) {}
    
    virtual void print() {
        std::cout << "I am AmfComponent!" << std::endl;
        handler.handle();
    }
    
    IAvailabilityEventHandler& handler;
};

typedef Factory<IComponent, AmfComponent, EventLoop, IAvailabilityEventHandler> AmfComponentFactory;
typedef boost::function<IComponent*(EventLoop&)> IComponentFactory;

struct Controller : public IAvailabilityEventHandler {
    Controller(EventLoop* loop, const IComponentFactory& factory) {
        controller = factory(*(IAvailabilityEventHandler*)this);
    }
    
    virtual void handle() {
        std::cout << "I am Controller!" << std::endl;
    }
    
    IComponent* component;
};

int main() {
    
    EventLoop* loop = new EventLoop();
    IComponentFactory factory = AmfComponentFactory(*loop);
    
    Controller controller(loop, factory);
    controller.component->print();
}

//////////////////////////////////////////////////////////////////

#if 0

struct Loop {};

struct EventHandler {};

struct Abstract {
    virtual void print() = 0;
};

struct Concrete : public Abstract {
    Concrete(Loop*, EventHandler&) {}
    
    virtual void print() {
        std::cout << "I am Concrete!" << std::endl;
    }
};

typedef boost::function<Abstract*(Loop*, EventHandler&)> AbstractFactory;

struct Controller : public EventHandler {
    Controller(Loop* loop, const AbstractFactory& factory) {
        data = factory(loop, *this);
    }
    
    Abstract* data;
};

int main()
{
    Loop* loop = new Loop();
    AbstractFactory factory = boost::factory<Concrete*>();
    Controller controller(loop, factory);
    
    controller.data->print();
}

#endif
