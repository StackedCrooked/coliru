int main(int argc, char** argv) {
    auto x = [](auto f) { return f(f); };
    x(x);
    
    return 0;
}
