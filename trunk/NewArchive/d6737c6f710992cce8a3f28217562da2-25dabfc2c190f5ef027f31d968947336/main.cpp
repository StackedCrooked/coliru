// Component.h
struct Entity; // forward-declaration
class Component 
{        
    Entity& entity;
    template<class T = Entity> void doAImpl() { static_cast<T&>(entity).a(); } 

    public:
        // void notWorking() { entity.a(); } <- this does not compile
        void doA() { doAImpl(); }
};

int main()
{
}