#include <vector>

struct ObjectEvent;
struct GameObject {
    std::vector<ObjectEvent*> events;
    void process_events();
};

Class ObjectEvent
{
private:
    bool* trigger;
    void (*response)(GameObject*);
public:
    process(GameObject* obj)
    {
        if (*trigger)
            response(obj);
    }
};

void GameObject::process_events()
{
    std::vector<ObjectEvent*>::iterator it;
    for (it = events.begin(); it != events.end(); it++)
        (*it)->process(this);
}



int main() {}