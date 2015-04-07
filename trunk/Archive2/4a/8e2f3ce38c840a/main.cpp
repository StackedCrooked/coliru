#include <iostream>
#include <memory>
#include <boost/signals2.hpp>
using namespace std;

boost::signals2::signal<void (int, int)> mouseOver;

struct mean {
    int count =0;
    float value =0;
    void add(float x) {
        value = (value * count + x) / (++count);
    }
};



void subscribe() {
    auto m = make_shared<mean>();
    mouseOver.connect([=](int x, int y){
        m->add(x+y);
        cout << m->value << endl;
    });
}

void invoke() {
    for (int i = 0; i < 10000; ++i) {
        mouseOver(12, i);
    }
}

int main() {
    subscribe();
    invoke();
}
