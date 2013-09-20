int main() {
    int i;
    auto lambda = [i]{};
    
    bool b = lambda;
    
    if(lambda) {}
}