#include <iostream>
#include <memory>
#include <boost/signals2.hpp>
using namespace std;

struct mean {
    int count =0;
    float value =0;
    void add(float x) {
        value = (value * count + x) / (++count);
    }
    
    ~mean() {
        cout << "s u!" << endl;
    }
};

void subscribe( boost::signals2::signal<void (int, int)> & mouseOver ) {
    auto m = make_shared<mean>();
    mouseOver.connect([=](int x, int y){
        m->add(x+y);
        cout << m->value << endl;
    });
}

void invoke( boost::signals2::signal<void (int, int)> & mouseOver ) {
    for (int i = 0; i < 10; ++i) {
        mouseOver(12, i);
    }
}

int main() {
    {
        boost::signals2::signal<void (int, int)> mouseOver;
        subscribe(mouseOver);
        invoke(mouseOver);
        cout << "pre clean" << endl;
    }
    cout << "all clean" << endl;
}
