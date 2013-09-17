#include <functional>
#include <vector>
#include <iostream>

//-- Cons: 1. Precisa definir uma interface, mais codigo.
struct IListener
{
    virtual void OnEvent(const char *) {};
    virtual void OnEventFail(int) {};
};

struct Sender
{
    //-- Pro: 1. Implementacao mais simples do Sender.
    std::vector<IListener *> vListeners;

    void Add(IListener *l)
    {
        vListeners.push_back(l);
    }
    
    void SendEvent()
    {
        for (auto each: vListeners)
            each->OnEvent("an event");
    }
};

//-- Cons: 2. Heranca de virtual, vtable
struct Listener : public IListener
{
    //-- Cons: 3. Lembrar do virtual destructor, mais codigo.
    virtual ~Listener() {}
    
    virtual void OnEvent(const char *ev)
    {
        std::cout << "Listener::OnEvent() received event: " << ev << std::endl;
    }
    
    Listener()
    {
        // Pro: 2. Facil uso
        // Pro: 3. Multiplos handlers (OnEvent, OnEventFail) de uma vez
        s.Add(this);
        s.SendEvent();
    }
    
    Sender s;
};

int main(int, char **)
{
    Listener l;
    return 0;
}