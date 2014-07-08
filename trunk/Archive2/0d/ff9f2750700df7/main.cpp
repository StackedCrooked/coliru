#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/weak_ptr.hpp>
struct object {
    object(int i) : i(i) {}
    int i;
};
boost::weak_ptr<object> make() {
    static boost::shared_ptr<object> o = boost::make_shared<object>(42);
    return boost::weak_ptr<object>(o);
}
int main() {
    boost::weak_ptr<object> o = make();
    if(boost::shared_ptr<object> sp = o.lock()) {
        std::cout << sp->i << std::endl;
        std::cout << sp.use_count() << std::endl;
    } else {
        std::cout << "nothing" << std::endl;
    }
    std::cout << o.use_count() << std::endl;
}
