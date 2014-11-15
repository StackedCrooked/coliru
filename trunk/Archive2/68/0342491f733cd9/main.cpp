#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <typeinfo>
#include <map>
 
class Event
{
public:
    enum Type {
        MODIFY = 0,
        ADD,
        DELETE
    };
};
 
class Validation
{
public:
    void add_error(std::string msg) {}
};
class Module;
class Subscriber
{
public:
    enum Type {
        Interface = 0,
        Route
    };
    typedef std::vector<std::pair<Module*, Type>> Subscribers;
    void notify(Module *module, Type sub_type, Event::Type event_type);
    void add(Module *module, Type sub_type);
private:
    Subscribers _subscribers;
};
 
class Module
{
public:
    Module(Subscriber &sub, Validation &val) : _sub(sub), _val(val), _enabled(false) {}
 
    virtual void disable() { _enabled = false; };
    virtual void enable() { _enabled = true; };
    virtual bool validate() = 0;
    virtual void modify(const Module &delta) {};
    virtual void on_notify(Module *module, Subscriber::Type sub_type, Event::Type event_type) {}
protected:
    Subscriber& _sub;
    Validation& _val;
    bool _enabled;
};
 
void Subscriber::notify(Module *module, Type sub_type, Event::Type event_type)
{
    for (Subscribers::const_iterator cit = _subscribers.begin();
         cit != _subscribers.end(); ++cit) {
        if (cit->second == sub_type)
            cit->first->on_notify(module, sub_type, event_type);
    }
}

void Subscriber::add(Module *module, Type sub_type)
{
    _subscribers.push_back(std::make_pair(module, sub_type));
}
 
 
class Interface : public Module
{
public:
    Interface(Subscriber &sub, Validation &val) : Module(sub, val) {}
    void modify(const Module &delta) { _sub.notify(this, Subscriber::Interface, Event::MODIFY); }
    virtual bool validate()
    {
        return true;
    }
    bool operator == (const Interface& d) const {
        return d.name() == _name;
    }
    std::string name() const { return _name; }
private:
    std::string _name;
};
 
class MyApp1 : public Module
{
public:
    MyApp1(Subscriber &sub, Validation &val) : Module(sub, val) { _sub.add(this, Subscriber::Interface); }
    virtual bool validate()
    {
        return _val1.size() > 0 && _val2.size() > 0;
    }
 
    void on_notify(Module *module, Subscriber::Type sub_type, Event::Type event_type)
    {
        if (sub_type == Subscriber::Interface) {
            Interface *changed = dynamic_cast<Interface*>(module);
            if (changed == interface && event_type == Event::DELETE) {
                std::cout << "Whoa, deleting interface MyApp1 is using. Disabling app." << std::endl;
                disable();
            }
        }
    }
private:
    Interface *interface;
    std::string _val1;
    std::string _val2;
};
 
class Configuration
{
    typedef std::vector<Interface> Interfaces;
public:
    Configuration(Validation &val, Subscriber &sub) : _val(val), _sub(sub) {}
 
    Validation &_val;
    Subscriber &_sub;
 
    Interfaces _interfaces;
 
    bool add_interface(Interface interface)
    {
        if (interface.validate()) {
            _interfaces.push_back(interface);
            _sub.notify(dynamic_cast<Module*>(&interface), Subscriber::Interface, Event::ADD);
            return true;
        }
        return false;
    }
 
    bool edit_interface(Interface &interface)
    {
        if (interface.validate()) {
            _sub.notify(dynamic_cast<Module*>(&interface), Subscriber::Interface, Event::MODIFY);
            return true;
        }
        return false;
    }
};
 
int main(int argc, char* argv[])
{
    Validation val;
    Subscriber sub;
    Configuration config(val, sub);
    MyApp1 myapp(sub, val);
    Interface interface(sub, val);
    config.add_interface(interface);
 
    return 0;
}