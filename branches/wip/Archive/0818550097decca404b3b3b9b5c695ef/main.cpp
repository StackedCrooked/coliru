#include <string>

class screen; //FORWARD DECLARATION OF screen

class Window_Mgr
{
public:
Window_Mgr& relocate(int r, int c, screen& s);
private:
};

class screen
{
public:
typedef std::string::size_type index;
friend Window_Mgr& Window_Mgr::relocate(int, int, screen&);
private:
int width, height;
};

Window_Mgr& Window_Mgr::relocate(int r, int c, screen& s)
{
   s.height=10;
   s.width=10;
   return *this;
}

int main(int argc, char* argv[])
{
}