#include <iostream>
#include <string>
#include <vector>
#include <functional>

struct layered_exception {
    std::vector<std::string> messages;
};
struct T {
    std::string s;
    ~T() {
        if (std::uncaught_exception()) {
            try {
                throw;
            } catch(layered_exception& e) {
                e.messages.push_back(std::move(s));
                throw;
            } catch(...) {
                throw;
            }
        }
    }
};