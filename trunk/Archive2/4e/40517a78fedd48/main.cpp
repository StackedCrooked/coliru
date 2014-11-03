template <typename T>
struct binary_expr {
    auto operator()(int i){
        return 1;
    }
};

int main(){
    binary_expr<double> b;
}
