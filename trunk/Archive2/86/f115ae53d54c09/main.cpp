struct A{
    void function(){
        auto lambda = [this](){
            method();
            member = 5;
        };
        lambda();
    }
    void method(){}
    private:
    int member;
};

int main()
{
}
