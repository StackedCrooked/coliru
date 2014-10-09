#include <iostream>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/construct.hpp>
#include <boost/lambda/bind.hpp>
#include <algorithm>
#include <boost/iterator/counting_iterator.hpp>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>

class Base
{
public:
    Base (int i) : i_(i) { std::cout << "Creating: " << i << std::endl; }
    ~Base(){ std::cout << "Deleting: " << i_ << std::endl; }
private:
    int i_;
};

int main()
{
    using namespace boost;

    std::vector< boost::shared_ptr<Base> > bsp;
    bsp.reserve(10);

    std::transform(boost::counting_iterator<int>(0), boost::counting_iterator<int>(10), std::back_inserter(bsp),
            lambda::bind< boost::shared_ptr<Base> >(lambda::constructor< boost::shared_ptr<Base> >(), lambda::bind<Base*>(lambda::new_ptr<Base>(), lambda::_1)));
}
