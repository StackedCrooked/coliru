#include <iostream>
#include <thread>
#include <vector>

using std::vector;

template <typename T>
void variadic_vector_emplace(vector<T>&) {}

template <typename T, typename First, typename... Args>
void variadic_vector_emplace(vector<T>& v, First&& first, Args&&... args)
{
    v.emplace_back(std::forward<First>(first));
    variadic_vector_emplace(v, std::forward<Args>(args)...);
}

struct my_struct
{
    template <typename... Args>
    my_struct(Args&&... args)
    {
        variadic_vector_emplace(_data, std::forward<Args>(args)...);
    }
    
    vector<int>& data() { return _data; }
    
private:
  vector<int> _data;
};


int main()
{
    my_struct my(5, 6, 7, 8);
    
    for(int i : my.data())
      std::cout << i << std::endl;
}