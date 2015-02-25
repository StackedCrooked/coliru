#include <iostream>
#include <string>
#include <memory>

class Object : public std::enable_shared_from_this<Object>
{
protected:
    struct CreateObject {};
    
    static void Init(std::shared_ptr<Object> const &ob)
    {
        std::cout << "Object Initd" << std::endl;
    }
    
public:
    Object(Object const &) = delete;
    Object(Object &&) = delete;
    Object & operator = (Object const &) = delete;
    Object & operator = (Object &&) = delete;
    
    Object(CreateObject)
    {
        std::cout << "Object Created" << std::endl;
    }
    
    virtual ~Object()
    {
        // empty
    }
    
    static std::shared_ptr<Object> Create()
    {
        auto ob =  std::make_shared<Object>(CreateObject());
        Object::Init(ob);
        return ob;
    }
};

//

class Thing final: public Object
{
    struct CreateThing {};
    
    static void Init(std::shared_ptr<Thing> const &thing)
    {
        Object::Init(thing);
        std::cout << "Thing Initd" << std::endl;
    }
    
public:
    Thing(CreateThing) :
        Object(CreateObject())
    {
        std::cout << "Thing Created" << std::endl;
    }
    
    ~Thing()
    {
        // empty
    }
    
    static std::shared_ptr<Thing> Create()
    {
        auto thing = std::make_shared<Thing>(CreateThing());    
        Thing::Init(thing);
        return thing;
    }
};


int main()
{
    std::shared_ptr<Thing> ob = Thing::Create();
    
    return 0;
}
