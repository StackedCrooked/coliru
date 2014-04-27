#include <iostream>
#include <memory>
using namespace std;

// prints a message when members of parent are freed, except after being moved from
struct MoveTracer {
    string msg_;
    MoveTracer(const string& msg) : msg_{msg} {}
    MoveTracer(string&& msg) : msg_{move(msg)} {}
    
    MoveTracer(const MoveTracer&) = default;
    MoveTracer(MoveTracer&& other) : msg_{move(other.msg_)} { other.msg_.clear(); }
    MoveTracer& operator=(const MoveTracer&) = default;
    MoveTracer& operator=(MoveTracer&& other) { msg_ = move(other.msg_); other.msg_.clear(); return *this; }
    ~MoveTracer() { cout << msg_; }
};

struct MoveOnly { unique_ptr<int> ptr; MoveTracer t; };

template<typename MoveOnly>
class MoveWrapper {
public:
    MoveWrapper() = delete;
    MoveWrapper(MoveOnly&& m) : m_(move(m)) {}

    // hijack copies to be moves
    MoveWrapper(const MoveWrapper& other) : m_(move(other.m_)) {}
    MoveWrapper& operator=(const MoveWrapper& other) { m_ = move(other.m_); return *this; }

    MoveWrapper(MoveWrapper&&) = default;
    MoveWrapper& operator=(MoveWrapper&&) = default;
    ~MoveWrapper() = default;

    MoveOnly operator*() const { return move(m_); }

private:
    mutable MoveOnly m_;
};

template<typename MoveOnly>
MoveWrapper<MoveOnly> wrap(MoveOnly&& m) {
    return {forward<MoveOnly>(m)};
}

int main() {
    MoveOnly m{unique_ptr<int>(new int(0)), string{"no leaks! :)\n"}};
    
    //auto copy = m; // error: copy of move-only type
    auto moved = move(m);
    
    //auto f = [moved] { cout << ++*moved.ptr << '\n'; }; //error: copy of move-only type
    auto wrapper = wrap(move(moved));
    auto f = [wrapper] {
        static auto m = *wrapper;
        cout << ++*m.ptr << '\n';
    };
    
    f();
    f();
    f();
}
