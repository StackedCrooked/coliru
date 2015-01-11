#include <iostream>
#include <vector>
using namespace std;

template<class T>
class SomeClass;
/* {
 *     vector<float> (const &?) getAverages() const;
 * }; */

template<>
class SomeClass<int>
{
    vector<vector<int>> data {};
    /* compute the averages as data is added and removed: */
    vector<float> averages   {};

    public:

        /* return precomputed averages; we don't want to copy: */
        vector<float> const & getAverages() const { return averages; }
};

template<>
class SomeClass<double>
{
    vector<vector<double>> data {};

    public:

        /* we don't want to compute averages on the fly to avoid loss of
         * precision or whatever and we don't want to memoise the generated
         * vector to save on memory... or whatever (this is perhaps a stupid
         * reason here but this is just an example and I'm sure there are
         * plenty of more pertinent examples): */
        vector<float> getAverages()
        {
            auto averages = vector<float>{};
            //for (...) compute averages
            return averages;
        }
};

template<class SomeClass>
void doSomething(SomeClass&& x)
{
    const auto& averages = x.getAverages();
    //...
}

int main()
{
    doSomething(SomeClass<int>{});
    doSomething(SomeClass<double>{});
    return 0;
}
