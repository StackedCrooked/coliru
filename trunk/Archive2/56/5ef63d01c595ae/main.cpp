#include <iostream>    

using namespace std;    

struct Secret{
    int value;
    Secret(int value):value(value){}
    ~Secret(){
        cout<<"destructor:"<<(void*)this<<endl;
        value=0;
    }
};    

template<class Func>
class Copier{
public:
    Func func;
    Copier(Func func):func(func){}
    void run(){
        func();
    }
    auto copy(){
        auto output = [me = *this](){
            me.func();
        };
        Copier<decltype(output)> out(output);
        return out;
    }    

};
auto makeSecretPrinter(){
    Secret secret(42);
    auto secretPrinter = [secret](){
        cout<<"reading object at address:"<<(void*)&secret<<endl;
        cout<<"the secret is:"<<secret.value<<endl;
    };
    return Copier<decltype(secretPrinter)>(secretPrinter).copy();
}    

int main(){
    makeSecretPrinter().run();
    return 0;
}