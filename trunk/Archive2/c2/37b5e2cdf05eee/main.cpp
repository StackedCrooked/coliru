#include <deque>
 
int main() {
    std::deque<int> nums(1000, 42);
    nums.push_front(1);
    nums.pop_front();
 
    nums.clear();
 
    // nums now contains no items, but it may still be holding allocated memory. 
    // Calling shrink_to_fit will free any unused memory.
    nums.shrink_to_fit();
}