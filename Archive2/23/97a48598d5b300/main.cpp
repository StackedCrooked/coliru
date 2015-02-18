#include <iostream>
#include <tuple>

template<typename ... Args>
class Container
{
   public:

    template<class T> void Set(const T& value)
    {
        std::get<T>(data) = value;
    }

    template<class T> T Get() const
    {
       return std::get<T>(data);
    }

   private:
    std::tuple<Args...> data;
};

int main()
{
   Container<int, float, double> c;
   c.Set(10);
   c.Set(20.125f);
   c.Set(30.7890);

   std::cout << c.Get<int>() << std::endl;
   std::cout << c.Get<float>() << std::endl;
   std::cout << c.Get<double>() << std::endl;

   return 0;
}
