#include <thread>
#include <future>
#include <iostream>
#include <vector>
#include <functional>

bool odd(int i) { return (((i&1)==1)?true:false); }

template <typename _returnType>
void exec_and_collect(std::vector<_returnType>& results,
                      std::vector<std::function<_returnType()>> funcs
                    ) {
    std::size_t numTasks = std::min(funcs.size(), results.size());

    std::vector<std::packaged_task<_returnType()>> tasks(numTasks);
    std::vector<std::future<_returnType>> futures(numTasks);

    std::vector<std::thread> threads(numTasks);

    for (std::size_t h = 0; h < numTasks; h++) {
        tasks[h] = std::packaged_task<_returnType()>(funcs[h]);
        futures[h] = tasks[h].get_future();
        threads[h] = std::thread(std::move(tasks[h]));
    }

    // threads are now running, collect results
    for (std::size_t h = 0; h < numTasks; h++) {
        results[h] = futures[h].get();
        threads[h].join();
    }
}

int main() {
    std::size_t num = 8;
    std::vector<bool> results(num);
    std::vector<std::function<bool()>> funcs(num);

    for (std::size_t i = 0; i < num; i++) {
        funcs[i] = std::bind(odd, static_cast<int>(i));
    }
    exec_and_collect<bool>(results, funcs);
    for (std::size_t i = 0; i < num; i++) {
        printf("odd(%zu)=%s\n", i, (results[i]?"true":"false"));
    }
    return 0;
}
