#include <functional>
#include <vector>
#include <iostream>

struct Sender
{
    typedef std::function<void(const char *)> Listener;
    std::vector<Listener> vListeners;
    
    //-- Cons: 1. Perde multiplos handlers (OnEvent, OnEventFail), precisa "setar" todos individualmente
    typedef std::function<void(int)> FailListener;
    std::vector<FailListener> vFailListeners;

    void Add(Listener l)
    {
        vListeners.push_back(l);
    }

    void AddFail(FailListener l)
    {
        vFailListeners.push_back(l);
    }
    
    void SendEvent()
    {
        for (auto each: vListeners)
            each("an event");
    }
};

void func_callback(const char *ev)
{
    std::cout << "func_callback() received event: " << ev << std::endl;
}

//-- Pro 1: Nao precisa herdar uma interfacem = menos codigo para digitar.
//-- Pro 2: Nao precisa de virtual = menor footprint, melhor performance.
struct Listener
{
    void OnEvent(const char *ev)
    {
        std::cout << "Listener::OnEvent() received event: " << ev << std::endl;
    }
    
    Listener()
    {
       //-- Pro: 3. Anonymoys functions - util para callbacks rapidos inplace
       s.Add([&](const char *ev) 
        {
            std::cout << "<anonymous> received event: " << ev << " Redirect -> ";
            this->OnEvent(ev);
        });
        
        //-- Pro: 4. funcoes basicas servem tambem!
        s.Add(func_callback);
        
        //-- Cons: 2. Passar um metodo da classe fica verbose e contra intuitivo (para olhos desacostumados)
        s.Add(std::bind(&Listener::OnEvent, this, std::placeholders::_1));       
        s.SendEvent();
    }
    
    Sender s;
};

int main(int, char **)
{
    Listener l;
    return 0;
}