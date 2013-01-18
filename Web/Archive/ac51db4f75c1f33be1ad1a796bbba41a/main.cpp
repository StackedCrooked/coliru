#include <string>

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
};

int main(int argc, char* argv[])
{
}