struct X{};
struct Y : X{};

struct interface
{
    virtual X* f(Y*) = 0;
};

struct impl : interface
{
    Y* f(X*) override { return nullptr; }
};

int main(){
}