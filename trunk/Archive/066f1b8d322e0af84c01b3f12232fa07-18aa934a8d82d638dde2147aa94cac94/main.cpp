template<class T>
void f(T&&);

void f(char const*){}

int main(){
    char buffer[] = "hi";
    f(buffer);
}