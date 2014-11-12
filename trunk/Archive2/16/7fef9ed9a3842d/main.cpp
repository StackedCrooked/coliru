#include <memory>
#include <chrono>
#include <iostream>

struct LargeObj {
    char data[4096];
};

template<typename F>
void timed(F &&f, std::string name) {
    auto start = std::chrono::high_resolution_clock::now();
    std::forward<F>(f)();
    std::cout << name << ": " << std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - start).count() << "\n";
}

int main (int argc, char *argv[])
{
    
    timed([]{
        for(int i = 0; i < (1<<24); ++i) {
            std::make_shared<LargeObj>();
        }
      },
      "make_shared");
    
        timed([]{
        for(int i = 0; i < (1<<24); ++i) {
            std::shared_ptr<LargeObj>(new LargeObj{});
        }
      },
      "new");
}
