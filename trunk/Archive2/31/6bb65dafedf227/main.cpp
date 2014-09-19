struct Message1 {
    int a;
    int b;
};
template<class MSG_T> void RegisterMessageType() {
    MSG_T t;
}

int main()
{
    Message1 m;
    RegisterMessageType<Message1>();
    
    return 0;
}