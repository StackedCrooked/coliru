template<class T>
void f(T&&);

void f(char const*){}

int main(){
    f("hi");
}