#include <iostream>
#include <string>
#include <cmath>
#include <chrono>
#include <vector>

using namespace std;

class Fraction1
{
    public:
    Fraction1(double x)
    {
        auto pui = ceil(log10(x));
        num = x*pow(10, pui);
        denum = pow(10, pui);
        simplifie();
    }
    void simplifie(){}
    private:
    int num;
    int denum;
};
class Fraction2
{
    public:
    Fraction2(double x)
    {
        std::string temp = std::to_string(x);
        auto pos = temp.find(".");
        num = x*pow(10, temp.size()-pos);
        denum = pow(10, temp.size()-pos);
        simplifie();
    }
    void simplifie(){}
    private:
    int num;
    int denum;
};

int main()
{
    //init des variables pour ne pas fausser le bench
    size_t const iter = 10000;
    vector<Fraction1> vect1;
    vector<Fraction2> vect2;
    vect1.reserve(iter);
    vect2.reserve(iter);
    
    //Bench
    auto start = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iter; ++i)
        vect1.push_back(Fraction1{i*i/static_cast<double>(i)});
    auto end = chrono::high_resolution_clock::now();
    auto time1 = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    
    start = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iter; ++i)
        vect2.push_back(Fraction2{i*i/static_cast<double>(i)});
    end = chrono::high_resolution_clock::now();
    auto time2 = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    
    //Affichage
    cout << time1 << " ms to make " << iter << " Fraction with log10-algo." << endl;
    cout << time2 << " ms to make " << iter << " Fraction with string::find-algo." << endl;
    cout << "log10-algo was " << time2/time1 << "x faster than string::find-algo." << endl;
}
