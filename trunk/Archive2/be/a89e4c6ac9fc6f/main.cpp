#include <boost/ptr_container/ptr_vector.hpp>

class A
{
protected:
    virtual int getNumber() {return 1;};

public:

    static int getSum( boost::ptr_vector<A> &pv){
        int sum = 0;
        for(std::vector<int>::size_type i = 0; i != pv.size(); i++) {
            sum += pv[i].getNumber();
        }
        return sum;
    }

    virtual ~A(void)=0;
};

int main()
{
    boost::ptr_vector<A> pv;
}