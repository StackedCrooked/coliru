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
    
    auto initData() {
        generate(begin(horrible), end(horrible), [=] {
            return make_pair(2, simpleMap(2));
        });
        
        lessHorrible.first = simpleMap;
        generate(begin(lessHorrible.second), end(lessHorrible.second), [=] {
            return 2;
        });
    }
    
    auto fakeSend() {
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

namespace client {
    template <typename Infer, typename Original>
    auto recoverInformation(Infer info, Original redundant) {
        auto map = info.first;
        auto data = info.second;
        
        array<pair<int, string>, numEntries> unpacked;
        transform(begin(data), end(data), begin(unpacked), [=](int elem) {
            return make_pair(elem, map(elem));
        });
        
        if (unpacked == redundant) {
            cout << "Information recovered.";   
        } else {
            cout << "Derp.";   
        }
        cout << endl;
    }
}

int main() {
    network::initData();
    network::fakeSend();
    client::recoverInformation(lessHorrible, horrible);
}