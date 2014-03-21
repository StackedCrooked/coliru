#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <thread>
#include <future>
#include <cstdint>
#include <memory>
#include <string>
#include <chrono>
#include <stdexcept>

using namespace std;

struct image {
    image(char c) : str(20, c) {}
    void render() const {
        cout << '+' << string(20, '-') << '+' << endl;
        for (int n = 5; n; --n) cout << '|' << str << '|' << endl;
        cout << '+' << string(20, '-') << '+' << endl;
    }
    char value() const { return str[0];}
    
    string str;
};

auto call_filter(shared_ptr<image const>& img) {
    // invoke worker thread
    return std::async(std::launch::async, [&img, in = img](){
        shared_ptr<image const> out = make_shared<image>(in->value() + 1);
        img = out;
    });
}

int main() {
    try {
        shared_ptr<image const> img = make_shared<image>('0');
        vector<future<void>> f;

        for (int num = 5; num; --num) {
            // GUI thread render & initiate filter call
            f.emplace_back(call_filter(img));
            for (int n = 5; n; --n) {
                // render image
                auto local = img;
                local->render();
            }
        }
    } catch(std::exception const& e) {
        cout << e.what() << endl;
    }
}