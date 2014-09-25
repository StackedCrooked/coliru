int main() {
    auto lambda1 = []() mutable { };
    auto lambda2 = lambda1;
}