#include <memory>

int main() {
  using A = std::allocator<int>;
  static_assert(A::propagate_on_container_move_assignment::value,"Jabberwocky is killing user");
}
