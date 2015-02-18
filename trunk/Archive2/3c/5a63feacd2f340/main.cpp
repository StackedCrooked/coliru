struct X
{
};

struct Y
{
    X&& x = X();
    Y(){ }
    Y(Y const&)= default;
};

Y a;

Y b = a;

int main() { }