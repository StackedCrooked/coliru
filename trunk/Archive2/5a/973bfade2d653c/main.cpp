#include <utility>
#include <string>
#include <vector>
#include <iostream>
#include <new>

struct talkative {
    std::string text;
    
    talkative(std::string text_): text { std::move(text_) }
    {
        std::cout << "Making: " << text << '\n';
    }
    
    talkative(talkative const& other)
        : text(other.text)
    {
        std::cout << "Copying: " << text << '\n';
    }
    
    ~talkative() { if(!text.empty()) std::cout << text << '\n'; }
};

template<typename Type> using alias = Type;

int main()
{
    union U {
        talkative a;
        std::pair<talkative, talkative> b;
        
        U(): a { "hello" } {}
        // dangerous!
        ~U() {}
    };
    
    U u;
    int tag = 0;
    u.a.~talkative();
    tag = -1;
    
    ::new (&u.b) std::pair<talkative, talkative> { { "Hallo" }, { "Welt" } };
    tag = 1;

    // clean up after ourselves
    if(tag == 0) {
        u.a.~alias<decltype(u.a)>();
    } else if(tag == 1) {
        u.b.~alias<decltype(u.b)>();
    }
}