#include <iostream>
#include <vector>
#include "ScreenCls.h"

using namespace std;

class WindowManager {
    
public:
    // location ID for each screen on window
    using ScreenIndex = vector<ScreenCls>::size_type;
    // reset the Screen at the given position to all blanks
    void clear(ScreenIndex);
    
private:
    vector<ScreenCls> screens{ Screen(24, 80, ' ') };
};

void WindowManager::clear(ScreenIndex index) {
    ScreenCls &s = screens[i];
    s.contents = string(s.height * s.width, ' ');
}