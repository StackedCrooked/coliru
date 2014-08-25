#include <functional>
#include <string>

class Actor
{
public:
        //void setPosition(const int& x, const int& y, const int& z) {};
        void setPosition(const int& position) {};
};

int main()
{
   typedef void (*set_type)(Actor&, const int&);
   std::function<void(Actor&, const int&)> setPos = (&Actor::setPosition);

   return 0;
}