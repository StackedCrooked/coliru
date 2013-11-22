#include <string>
#include <algorithm>

class Thing {
private:

    std::string mValue;

public:
    Thing() : mValue( "" ) {}

    void set(const std::string& s)
    {
        mValue = s;
        std::reverse( mValue.begin(), mValue.end() );
    }

    const std::string& getValue() const
    {
        return mValue;
    }
};

#include <memory>
#include <iostream>
#include <future>

int main(int argc, const char * argv[])
{
    using namespace std;
    
    unique_ptr<Thing> tA{ new Thing() };    // make_unique in C++1y
    unique_ptr<Thing> tB{ new Thing() };
    unique_ptr<Thing> tC{ new Thing() };

    auto tLambda = [](const string& iStr, unique_ptr<Thing> oThing) -> unique_ptr<Thing> {
        oThing->set( iStr );
        return oThing;
    };

    auto tA1 = async( launch::async, tLambda, "This is a test...A", move(tA) );
    auto tB1 = async( launch::async, tLambda, "This is a test...B", move(tB) );
    auto tC1 = async( launch::async, tLambda, "This is a test...C", move(tC) );

    cout << "tA is non-empty: "<< boolalpha << (bool)tA << '\n';

    tA = tA1.get();
    tB = tB1.get();
    tC = tC1.get();

    auto tA2 = async( launch::async, tLambda, tA->getValue(), move(tA) );
    auto tB2 = async( launch::async, tLambda, tB->getValue(), move(tB) );
    auto tC2 = async( launch::async, tLambda, tC->getValue(), move(tC) );

    cout << tA2.get()->getValue() << endl;
    cout << tB2.get()->getValue() << endl;
    cout << tC2.get()->getValue() << endl;

    return 0;
}