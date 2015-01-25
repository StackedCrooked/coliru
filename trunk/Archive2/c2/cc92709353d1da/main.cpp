#include <amp.h>

#include <iostream>

int main(int argc, char **argv) {
    std::vector<int> nums = { 0, 1, 2, 3, 4 };
    concurrency::array_view<int, 1> view(nums.size(), nums);
    concurrency::parallel_for_each(view.extent,
        [=](concurrency::index<1> idx) restrict(amp) {
            view[idx] = view[idx] + 42; }
    );
    view.synchronize();

    for (auto n : nums)
        std::cout << n << "\n";

    std::cin.get();
}