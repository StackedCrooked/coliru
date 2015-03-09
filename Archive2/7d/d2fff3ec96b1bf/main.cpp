#include <iostream>
#include <unordered_map>
#include <thread>

using namespace std;

void thread_add(unordered_map<int, int>& ht, int from, int to)
{
    for(int i = from; i <= to; ++i)
        ht.insert(unordered_map<int, int>::value_type(i, 0));
}

void test()
{
    unordered_map<int, int> ht;
    thread t[2];

    t[0] = thread(thread_add, std::ref(ht), 0, 9);

    t[0].join();

    std::cout << "size: " << ht.size() << std::endl;
}

int main()
{
    test();
    return 0;
}