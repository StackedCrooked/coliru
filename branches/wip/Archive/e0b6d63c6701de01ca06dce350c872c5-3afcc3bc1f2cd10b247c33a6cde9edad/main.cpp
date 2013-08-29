#include <utility>


template<typename T>
struct Timer {
    T start;
};


template<typename T>
Timer<T> MakeTimer(T&& startVal) {   // Forwards the parameter
   return Timer<T>{std::forward<T>(startVal)};
}

int main() {
    auto timer = MakeTimer(1234);
}