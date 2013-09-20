#include <iostream>
#include <vector>
#include <cmath>

#define DELTAX 0.00000001
#define ACCURACY 0.00000001

double f(double x)
{
    return sin(x);
}

double getDerivative(double (*f) (double), double x0)
{
    double dx = DELTAX;

    return (f(x0 + dx) - f(x0)) / dx;
}

double getRoot(double (*f) (double), double x0, bool& isRoot)
{
    double x = x0;

    double derivative;

    isRoot = true;

    for (int i = 0; i < 100; i++)
    {
        derivative = getDerivative(f, x);

        if (derivative == 0)
        {
            isRoot = false;
            return 0;
        }

        x = x - f(x) / derivative;
    }

    return x;
}

int main()
{
    double a = -10, b = 10, c = 1;

    double x;

    std::vector<double> roots;

    for (double x0 = a; x0 <= b; x0++)
    {
        bool isRoot;

        x = getRoot(f, x0, isRoot);

        if (!isRoot)
            continue;

        for (auto &root : roots)
        {
            if (fabs(root - x) < ACCURACY)
            {
                if (fabs(f(x)) < fabs(root))
                    root = x;

                isRoot = false;
                break;
            }
        }

        if (isRoot)
            roots.push_back(x);
    }

    for (auto &root : roots)
    {
        std::cout<<root<<std::endl;
    }

    return 0;
}
