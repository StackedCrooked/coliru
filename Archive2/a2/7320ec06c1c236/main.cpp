#include <boost/thread/mutex.hpp>
#include <map>


class foo {
public:
    foo() {}
    foo(foo const& cp)
    : data_(cp.data_) {}
    
    foo& operator=(foo const& cp) {
        data_ = cp.data_;
        return *this;
    }
    
private:
    boost::mutex mtx_;
    
    bool data_;
};


int main(int argc, char* argv[]) {
    std::map<int, foo> bar;
    bar[1] = foo();
    return 0;
}