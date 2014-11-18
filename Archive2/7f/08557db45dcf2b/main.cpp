#include <iostream>
#include <string>
#include <vector>
#include <map>

namespace client {
    struct key {
        std::string ip;
        std::string id;
    };
    
    bool operator < (const key& l, const key& r) {
        return l.ip < r.ip && l.id < r.id;
    }
    
    struct comp {
        bool operator()(const key& l, const key& r) {
            return l < r;
        }
    };
    
    typedef int pointer_to_entry;
    
    typedef std::map<key, pointer_to_entry, comp> map_type;
}

int main() {
    client::map_type m(client::comp());
}
