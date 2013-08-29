template<typename Ret, typename... Args, typename... Rest>
void foo(Ret(*)(Args...), Rest...) {}

int main() {
    char(*bar)(int, double) = nullptr;
    foo(bar, true, "hi");
}