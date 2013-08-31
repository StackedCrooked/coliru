#include <mutex>
using namespace std;

class Test{
public:
    mutex thread_mutex;

    static void functstatic(){
        unique_lock<mutex>(thread_mutex);
    }
    void functnorm(){
        unique_lock<mutex>(thread_mutex);
    }
};

int main(){
    Test::functstatic();

    Test ts;
    ts.functnorm();
}