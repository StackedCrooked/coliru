#include <vector>
#include <functional>
#include <string>
#include <utility>
#include <iostream>

class cButton
{
private:
    const std::function<void()> effect;

public:
    cButton(const std::function<void()>& effect);
    void onClick();
};

cButton::cButton(const std::function<void()>& effect)
    : effect(effect)
{
}

class cMessage
{
public:
    std::vector<cButton*> button;
    cMessage(const std::vector<std::function<void()> >& effect);
};

cMessage::cMessage(const std::vector<std::function<void()> >& effect)
{
    for(unsigned int i = 0; i < effect.size(); i++)
    {
       button.push_back(new cButton(effect[i]));
    }
}

void cButton::onClick()
{
    if (effect) effect();
}
    
int main()
{
    cMessage* message;
    {
        const std::pair<const std::string, const unsigned int> var("test", 1);
        std::function<void()> f = [var](){ std::cout << var.first << std::endl << var.second << std::endl; };
        message = new cMessage( {f} );
    };
    message->button[0]->onClick();
}
