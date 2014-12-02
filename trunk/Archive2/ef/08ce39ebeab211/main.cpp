#include <iostream>
#include <string>
#include <vector>

#include <boost/functional/factory.hpp>
#include <boost/function.hpp>
#include <boost/make_shared.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

//////////////////////////////////////////////////////////////////

template<typename AbstractClass, typename ConcreteClass, typename Loop>
struct Factory {
    Factory (Loop& loop) : loop(loop) {
    }

    template<typename EventHandler>
    boost::shared_ptr<AbstractClass> operator ()(EventHandler& handler) {
        return boost::make_shared<ConcreteClass>(boost::ref(loop), boost::ref(handler));
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
    AmfComponent(EventLoop&, IAvailabilityEventHandler& handler) : handler(handler) {}
    
    virtual void print() {
        std::cout << "I am AmfComponent!" << std::endl;
        handler.handle();
    }
    
    IAvailabilityEventHandler& handler;
};

typedef Factory<IComponent, AmfComponent, EventLoop> AmfComponentFactory;
typedef boost::function<boost::shared_ptr<IComponent>(IAvailabilityEventHandler&)> IComponentFactory;

struct Controller : public IAvailabilityEventHandler {
    Controller(const IComponentFactory& factory) {
        component = factory(*this);
    }
    
    virtual void handle() {
        std::cout << "I am Controller!" << std::endl;
    }
    
    boost::shared_ptr<IComponent> component;
};

int main() {
    
    boost::scoped_ptr<EventLoop> loop(new EventLoop());
    IComponentFactory factory = AmfComponentFactory(*loop);
    
    Controller controller(factory);
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
