#include <type_traits>
#include <utility>


template<typename T>
struct Timer {
    T start;
};


template<typename T>
Timer<typename std::remove_reference<T>::type> MakeTimer(T&& startVal) {   // Forwards the parameter
   return Timer<typename std::remove_reference<T>::type>{std::forward<T>(startVal)};
}

int main() {
    auto timer = MakeTimer(1234);
}