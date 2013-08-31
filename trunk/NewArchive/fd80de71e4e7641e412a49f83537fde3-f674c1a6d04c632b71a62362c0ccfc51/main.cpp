#include <iostream>
#include <memory>
#include <functional>

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

class Test {
    public:
        std::string data;
};

typedef std::function<void()> handler_erased_t;
static handler_erased_t handler;

template<class HandlerF>
void begin(Test& input, HandlerF h) {
    handler = h;
}
void end() {
    handler();
}
//=======
void myhandler(Test&& t) {
    std::cout << "Handling " << t.data << "\n";
}
void myhandler2(std::shared_ptr<Test> t) {
    std::cout << "Handling " << t->data << "\n";
}

int main() {
    {
        auto myt = make_unique<Test>();
        myt->data = "test";
        
        begin(*myt,
            std::bind(&myhandler, std::bind(static_cast<Test&&(&)(Test&)>(std::move<Test&>), *myt))
        );
    }
    end();
    {
        auto myt = std::make_shared<Test>();
        myt->data = "test2";
        begin(*myt, std::bind(&myhandler2, myt));
    }
    end();
    
    return 0;
}