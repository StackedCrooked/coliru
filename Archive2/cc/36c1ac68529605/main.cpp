#include<string>
int main(void) {
static_assert(std::is_nothrow_move_assignable<std::string>::value, "should not fail");
}