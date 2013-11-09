#include <map>
#include <functional>

namespace sf {
  struct Keyboard {
    enum Key {
      Left, Right
    };
  };

  struct Vector2f {
    float x,y;

    Vector2f(float x,float y) : x(x), y(y) { }
  };
}

class InputMap
{
    public:
        template<typename Function>
        void setHotkey(sf::Keyboard::Key hotkey, Function onClick)
        {
            map[hotkey] = onClick;
        }

        void triggerHotkey(sf::Keyboard::Key hotkey)
        {
            if(map.find(hotkey) != map.end())
                map[hotkey]();
        }

    protected:
        std::map <sf::Keyboard::Key, std::function<void()>> map;
};


struct Actor {
  void move(sf::Vector2f) { }
};

static void setHotkey(sf::Keyboard::Key,std::function<void()>)
{
}

int main(int,char**)
{
  Actor TestActorObject;
  Actor *TestActor = &TestActorObject;

  setHotkey(sf::Keyboard::Left, [=](){TestActor->move(sf::Vector2f(-20, 0));});
  setHotkey(sf::Keyboard::Right, [=](){TestActor->move(sf::Vector2f(20, 0));});
}
