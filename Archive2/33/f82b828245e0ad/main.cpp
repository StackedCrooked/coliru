struct X
{
};

struct Y
{
    X&& x; 
    Y(Y const&);
};

Y::Y(Y const&)= default;

int main() { }