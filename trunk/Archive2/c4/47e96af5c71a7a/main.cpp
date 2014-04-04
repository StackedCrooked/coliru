#include <cstddef>
#include <string>
#include <vector>

class Screen {
public:
    using pos = std::string::size_type;
    Screen() = default;
    Screen(pos ht, pos wd, char c) : height(ht), width(wd), contents(ht*wd, c) {}
    char get() const { return contents[cursor]; }
    char get(pos r, pos c) const;
    Screen &move(pos r, pos c);

private:
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;
};

inline char Screen::get(pos r, pos c) const {
    pos row = r*width;
    return contents[row + c];
}

inline Screen &Screen::move(pos r, pos c) {
    pos row = r*width;
    cursor = row + c;
    return *this;
}


class Window_mgr {
private:
public:
    std::vector<Screen> screens = { Screen(24, 80, ' ') };

};

int main() {
    Window_mgr w;
    w.screens.push_back(Screen(24, 80, ' '));

    std::vector<Screen> screens = { Screen(24, 80, ' ') };
}