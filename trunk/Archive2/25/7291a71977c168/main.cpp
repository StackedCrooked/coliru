#include <type_traits>
#include <memory>
#include <iostream>

template <typename T, typename... Args>
  typename std::enable_if<std::extent<T>::value != 0, std::unique_ptr<T>>::type
    make_unique(Args&&... args) = delete;
  
template <typename T, typename... Args>
  typename std::enable_if<std::extent<T>::value == 0, std::unique_ptr<T>>::type
    make_unique(Args&& ...args)
    { return std::unique_ptr<T>(new T(std::forward<Args>(args)...)); }

template <typename T>
  std::unique_ptr<T[]>
    make_unique<T[]>(size_t n)
    { return std::unique_ptr<T[]>(new T[n]); }

using namespace std;

int main()
{
    cout << *make_unique<int>() << endl;
    cout << *make_unique<int>(1729) << endl;
    cout << "\"" << *make_unique<string>() << "\"" << endl;
    cout << "\"" << *make_unique<string>("meow") << "\"" << endl;
    cout << "\"" << *make_unique<string>(6, 'z') << "\"" << endl;

    auto up = make_unique<int[]>(5);

    for (int i = 0; i < 5; ++i) {
        cout << up[i] << " ";
    }

    cout << endl;
    
    // These should fail
    //auto up1 = make_unique<string[]>("error");
    //auto up2 = make_unique<int[]>(10, 20, 30, 40);
    //auto up3 = make_unique<int[5]>();
    //auto up4 = make_unique<int[5]>(11, 22, 33, 44, 55);
}
