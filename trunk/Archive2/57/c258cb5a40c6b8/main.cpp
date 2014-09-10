int main() {
    auto lambda = [] (auto x) { return x; };
    lambda(lambda);
    return 0;
}
