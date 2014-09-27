#include <random>
#include <algorithm>
#include <functional>
#include <string>
#include <array>
#include <iostream>
#include <utility>

using namespace std;

const constexpr auto numEntries = 1U << 16U;

array<pair<int, string>, numEntries> horrible;
pair<function<const char*(int)>, array<int, numEntries>> lessHorrible;

namespace network {
    
    auto simpleMap(int someId) {
        switch (someId) {
            case 1:
                return "Hurr.";
            case 2:
                return "Durr.";
            case 3:
                return "Yeah.";
        }
        return "Fuck.";
    }
    
    void initData() {
        auto fromOneToThree = [] { return 1 + rand() % 3; };
        
        generate(begin(horrible), end(horrible), [=] {
            unsigned r = fromOneToThree();
            return make_pair(r, simpleMap(r));
        });
        
        lessHorrible.first = simpleMap;
        generate(begin(lessHorrible.second), end(lessHorrible.second), [=] {
            return  fromOneToThree();
        });
    }
    
    void fakeSend() {
        auto bytesToMega = [](unsigned bytes) { return (bytes / 1024.) / 1024.; };
        
        cout << "Sending horrible. Size: " <<
            bytesToMega(
                horrible.size() * (sizeof(int) + 5 * sizeof(char))
            )
             << "MB\n";
             
        cout << "Sending lessHorrible. Size: " <<
            bytesToMega(
                (lessHorrible.second.size() * sizeof(int)) + sizeof(function<const char*(int)>)
            )
             << "MB" << endl;
    }
    
} // ::network

int main() {
    network::initData();
    network::fakeSend();
}