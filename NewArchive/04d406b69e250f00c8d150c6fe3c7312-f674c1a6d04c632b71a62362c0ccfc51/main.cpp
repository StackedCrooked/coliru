#include <memory>
#include <utility>

struct addrinfo { };

void freeaddrinfo(addrinfo* ) { }

auto deleter = [](struct addrinfo* ptr) {
  if (ptr != nullptr)
    freeaddrinfo(ptr);
};

std::unique_ptr<struct addrinfo, decltype(deleter)>
resources_keeper(nullptr, deleter);

int main() {

    decltype(resources_keeper) plouf1(nullptr, deleter);
    decltype(resources_keeper) plouf2(nullptr, deleter);

    std::swap(plouf1, plouf2);
    return 0;
}
