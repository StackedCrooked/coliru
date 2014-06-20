#include <algorithm>
#include <vector>
struct dataunit
{
    double a, b, c;

    dataunit(void)
    {
        a = 0.0;
        b = 0.0;
        c = 0.0;
    }

    dataunit(double a, double b, double c)
    {
        this->a = a;
        this->b = b;
        this->c = c;
    }
};

bool pred(dataunit du1, dataunit du2)
{
    return (du1.b < du2.b); // I am interested in sorting by the member 'b' only
}

int main( )
{ 
    std::vector<dataunit> result;
    std::sort(result.begin(), result.end(), pred);
    return 0;
}