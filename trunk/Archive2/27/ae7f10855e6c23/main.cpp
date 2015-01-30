
#include <stdio.h>
#include <queue>

int main(int argc, char *argv[]) {
    std::queue<int> queue;
    const int limit = 10;
    for (int i = 0; i < limit; i++) {
        queue.push(i);
    }
    for (int i = 0; i < limit+1; i++) {
        //if (!queue.empty())
        queue.pop();
        printf("queue.size()=%zu\n", queue.size());
    }
    
    queue.push(7);
    printf("queue.size()=%zu\n", queue.size());
    return 0;
}
