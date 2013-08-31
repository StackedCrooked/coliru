struct foo{
    int a, b, c;
};

void f(foo){}

int main(){
    f(foo{1,2,3});
}