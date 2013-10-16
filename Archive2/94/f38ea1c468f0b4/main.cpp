#include <list>
#include <algorithm>
#include <iostream>

using namespace std;

template <typename Policy>
struct Itp{
    Itp() : bi() {}
    double computeEndCircle(){
        return bi.val();
    }
    virtual double computeAccaso(){
        return Policy(bi).val();
    }
    typename Policy::hold_type bi;
};

template <typename Policy>
struct ImageDrower : public Itp<Policy>{
    ImageDrower(){}
    double computeStart(){
        return Policy(Itp<Policy>::bi).val();
    }
    double computeAccaso(){
        return Policy(Itp<Policy>::bi).val();
    }
};

struct Bi{
    double val;
};

struct PolicyOne{
    typedef Bi hold_type;
    PolicyOne(hold_type& bi_) : bi(bi_){}
    hold_type& bi;
    double val(){
        return bi.val;
    }
};

int main() {
    ImageDrower<PolicyOne> id;
}
