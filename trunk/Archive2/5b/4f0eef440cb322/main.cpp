#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>


using query_map_t = std::unordered_map<std::string, std::string>;


query_map_t parse_query(const std::string& query) {
    query_map_t get_data;
    
    auto iter = query.begin();

    while(true) {
        if(iter == query.end()) break;

        // Find '=' symbol
        auto key_begin = iter;
        iter = std::find(iter, query.end(), '=');
        if(iter == query.end()) break;          // '=' not found
        if(iter == query.end() - 1) break;      // '=' is the last character

        std::string key(key_begin, iter);

        // Find '&' symbol
        auto val_begin = iter + 1;
        iter = std::find(iter + 1, query.end(), '&');

        std::string val(val_begin, iter);       // Note: if val_begin == iter then string is empty,
                                                //      which may not be the desired behavior.
                                                //      TODO: research more into this
                                                // Also, this would still be valid if iter == end

        get_data.emplace(std::move(key), std::move(val));

        ++iter;
    }

    return get_data;
}


template<typename T>
void print(const T& c) {
    for(const auto& e : c) {
        std::cout << e.first << ": " << e.second << std::endl;
    }
    std::cout << std::endl;
}


int main() {
    auto q1 = parse_query("p1=6&p2=7&p3=8");
    print(q1);
    
    auto q2 = parse_query("p1=&p2=7&p3=8");
    print(q2);
    
    auto q3 = parse_query("p1=&p2=7&p3=8");
    print(q3);
    
    auto q4 = parse_query("first=this+is+a+field&second=was+it+clear+%28already%29%3F");
    print(q4);
}
