#include <mutex>

class Test{
public:
    std::mutex thread_mutex;

    static void functstatic(){
        std::unique_lock<std::mutex>(thread_mutex);
    }
    void functnorm(){
        std::unique_lock<std::mutex>(thread_mutex);
    }
};

int main(){
    Test::functstatic();

    Test ts;
    ts.functnorm();
}