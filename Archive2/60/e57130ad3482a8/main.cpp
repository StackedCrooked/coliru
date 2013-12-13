#include <iostream>
#include <string>
#include <locale>
 
#include <boost/shared_ptr.hpp> 

class Counter;
typedef boost::shared_ptr<Counter> CounterPtr_t;

class Counter {
protected:
    int value_;
    
public:
    Counter() : value_(0) {
    }

    Counter(const int &argValue) : value_(argValue) {
    }
    
    Counter(const Counter &argCounter) {
        value_ = argCounter.value_;
    }
    
    const int &getValue() const {
        return value_;
    }
    
    void inc() {
        value_++;
    }
    
    void reset() {
        value_ = 0;
    }
};

int main()
{
    CounterPtr_t cnt_ptr_1 = CounterPtr_t(new Counter());
    CounterPtr_t cnt_ptr_2;
    
    cnt_ptr_1->inc();

    cnt_ptr_2 = CounterPtr_t(new Counter(*cnt_ptr_1.get()));    
    
    cnt_ptr_2->inc();
    
    std::cout << "CNT 1= " << cnt_ptr_1->getValue() << std::endl;
    std::cout << "CNT 2= " << cnt_ptr_2->getValue() << std::endl;
}