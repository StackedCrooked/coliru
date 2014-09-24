#include <utility>
#include <boost/smart_ptr.hpp>

template<class T>
class SingletonObject {
private:
    static boost::shared_ptr<T> instance_ptr;

    SingletonObject() {}
    ~SingletonObject() {}
    SingletonObject(const SingletonObject&) {}
    void operator=(const SingletonObject&) {}

public:
    template <typename... Args>
    static boost::shared_ptr<T> getInstance_ptr(Args&&... args) {

        if (!instance_ptr) {
            instance_ptr.reset(new T(std::forward<Args>(args)...));
        }

        return instance_ptr;
    }
};

template<class T>
boost::shared_ptr<T> SingletonObject<T>::instance_ptr;

struct A
{
    A(int i, float f, char c) {}
};

int main()
{
    SingletonObject<A>::getInstance_ptr(1, 3.14f, 'a');
}
