struct Message1 {
    int a;
    int b;
};
template<class MSG_T> void RegisterMessageType() {
    MSG_T t;
}

Message1 m;
RegisterMessageType<Message1>();

int main()
{    
    return 0;
}