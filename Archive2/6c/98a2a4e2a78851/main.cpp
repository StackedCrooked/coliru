//#include <iostream>

//#include "monster.h"
namespace monster {struct app {};}

#define DECLARE_MAIN(a)

class game : public monster::app {
  void init()
  {
  }
  void startup()
  {
  }
  void render(double currentTime)
  {
  }
};

DECLARE_MAIN(game)

int main(int argc, const char ** argv)
{
  a *app = new a;
  app->run(app);
  delete app;
  return 0;
}