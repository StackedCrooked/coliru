#include <vector>
#include <boost/function.hpp>

std::vector<boost::function<void (bool)>> callbacks;

void funcA(const boost::function<void (bool)>& callback) {
    callbacks.push_back(callback);
}

void funcB() {
    for (int i = 0; i < callbacks.size(); i++) {
        callbacks[i](true);
    }
}

int main() {
    funcA ([](bool success) {
        printf("function works properly\n");
    });
    funcB();
}
