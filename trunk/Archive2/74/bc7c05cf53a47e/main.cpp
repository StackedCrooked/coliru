#include <thread>
#include <mutex>

int main(){
    int i;
    std::mutex cPlusPlusMutex;
    cPlusPlusMutex.lock();
    cPlusPlusMutex.lock();
    i++;
     cPlusPlusMutex.unlock();
}