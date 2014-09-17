#include <string>
#include <vector>
#include <iostream>

class Screen;

class Window_mgr {
public:
    using ScreenIndex = std::vector<Screen>::size_type;
    Window_mgr();
    void clear(ScreenIndex);
    ScreenIndex addScreen(const Screen&);
private:
    std::vector<Screen> screens;
};


class Screen {
friend void Window_mgr::clear(ScreenIndex);
public:
    using pos = std::string::size_type;
    Screen();
    Screen(pos, pos);
    Screen(pos, pos, char);
    char get() const;
    char get(pos ht, pos wd) const;
    Screen &set(char);
    Screen &set(pos, pos, char);
    Screen &display(std::ostream&);
    const Screen &display(std::ostream&) const;
    Screen &move(pos r, pos c);
private:
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;
    void do_display(std::ostream&) const;
};


Window_mgr::Window_mgr(): screens{Screen(24, 80, ' ')} { }

void Window_mgr::clear(ScreenIndex i)
{
    std::cout << "success!" << std::endl;
    Screen &s = screens[i];
    s.contents = std::string(s.height * s.width, ' ');
}

Window_mgr::ScreenIndex Window_mgr::addScreen(const Screen &s)
{
    screens.push_back(s);
    return screens.size() - 1;
}

Screen::Screen() = default;

Screen::Screen(pos ht, pos wd): height(ht), width(wd), contents(ht * wd, ' ') { }

Screen::Screen(pos ht, pos wd, char c): height(ht), width(wd), contents(ht * wd, c) { }

inline char Screen::get() const
{
    return contents[cursor];
}

inline char Screen::get(pos r, pos c) const
{
    return contents[r * width + c];
}

inline Screen &Screen::move(pos r, pos c)
{
    cursor = r * width + c;
    return *this;
}

inline Screen &Screen::set(char c)
{
    contents[cursor] = c;
    return *this;
}

inline Screen &Screen::set(pos r, pos col, char ch)
{
    contents[r * width + col] = ch;
    return *this;
}

inline Screen &Screen::display(std::ostream &os)
{
    do_display(os);
    return *this;
}

inline const Screen &Screen::display(std::ostream &os) const
{
    do_display(os);
    return *this;
}

inline void Screen::do_display(std::ostream &os) const
{
    os << contents;
}

int main()
{
    Window_mgr m;
    m.clear(0);
}