#include <type_traits>
#include <utility>


template<typename T>
struct Timer {
    T start;
};


template<typename T>
Timer<typename std::decay<T>::type> MakeTimer(T&& startVal) {   // Forwards the parameter
   return Timer<typename std::decay<T>::type>{std::forward<T>(startVal)};
}

int main() {
    auto timer = MakeTimer(1234);
}