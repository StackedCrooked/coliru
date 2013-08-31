struct Entity; // forward-declaration
class Component 
{        
    Entity& entity;
    template<class T = Entity> void doAImpl() { static_cast<T&>(entity).a(); }

    public:
        Component(Entity& e) : entity(e){}
        // void notWorking() { entity.a(); } <- this does not compile
        void doA() { doAImpl(); }
};

struct Entity { void a() {} };

int main()
{
    Entity e;
    Component c(e);
    c.doA();
}