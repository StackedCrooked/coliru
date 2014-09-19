struct Message1 {
    int a;
    int b;
};
template<class MSG_T> void RegisterMessageType() {
    MSG_T t;
}

void foo() { int x; int y; x + y; }
foo();

int main()
{
    Message1 m;
    RegisterMessageType<Message1>();
    
    return 0;
}