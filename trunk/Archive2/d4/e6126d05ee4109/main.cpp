#include <functional>
#include <utility>

template<typename F>
class Timer {
public:
    explicit Timer(F callback) : onTimeout(std::move(callback)) {
        // create POSIX stuff; call onTimeout(…) when timer fires
    }

private:
    F onTimeout;
};

template<typename F>
Timer<F> makeTimer(F callback) {
    return Timer<F>(callback);
}
