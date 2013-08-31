void f(int const (&)[3]){}

int main(){
    f({1,2,3});
}