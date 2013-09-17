
struct Y {

        explicit Y(int) {}
    };
    
struct X 
    {
    template <typename T> 
    operator T() { return T(); }
    };

int main()
{
X x;
Y y(x); 
}
