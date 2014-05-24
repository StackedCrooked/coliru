#include <utility>

template<typename T>
class Task
{
public:
  template<typename... Args>
  static T* make(Args&&... args) {
    return new T(std::forward<Args>(args)...);
  }
};

template<typename A, typename B, typename C>
class MyTask : public Task<MyTask<A, B, C>>
{
    public: MyTask(A, B, C) {}
};

template<typename A, typename B, typename C>
MyTask<A, B, C> *make_MyTask(A&& a, B&& b, C&& c)
{
    return Task<MyTask<A, B, C>>::make(std::forward<A>(a), std::forward<B>(b), std::forward<C>(c));
}

int main()
{
    auto my_task = MyTask<int, long, double>::make(10, 20L, 30.);
    auto my_task1 = make_MyTask(10, 20L, 30.);
}
