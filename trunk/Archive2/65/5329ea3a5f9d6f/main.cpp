#include <iostream>
#include <string>
#include <sstream>

// no windows.h here :(
typedef unsigned UINT;
#define WM_CREATE 1
#define WM_DESTROY 2
// no windows.h here :(


std::string TranslateWMessage(UINT message)
{
    switch (message) {
#define MESSAGE_CASE(msg) case msg: return #msg;
//#include "wmmessages.h"
// wmmessages.h would have 1 line per message
// MESSAGE_CASE(WM_CREATE)
// MESSAGE_CASE(etc...)
// I'll say them here...

    MESSAGE_CASE(WM_CREATE)
    MESSAGE_CASE(WM_DESTROY)
    
    default: {
        std::stringstream ss;
        ss << "Unrecognized message " << message;
        return ss.str();
    }
}

}


int main()
{
    std::cout << TranslateWMessage(WM_CREATE) << std::endl;
    std::cout << TranslateWMessage(WM_DESTROY) << std::endl;
    std::cout << TranslateWMessage(1234) << std::endl;
}
