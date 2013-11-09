#include <string>
#include <exception>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

using namespace std;

class semaphore
{
public:
    semaphore(int value = 0): value(value) {};

private:
    int value;
    semaphore(const semaphore& orig) = delete;

};

struct workerT
{
    workerT() : status(true), threadSem(0) {}
    bool status;
    std::function<void(void)> func;
    semaphore threadSem;
};

std::vector<workerT> workers;

int main()
{
    fill(workers.begin(), workers.end(), workerT());
}