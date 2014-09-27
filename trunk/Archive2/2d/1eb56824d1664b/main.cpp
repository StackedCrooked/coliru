#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

bool isTwoDigit (int n)
{
    return (n > 9) || (n < -9);
}

template <typename T>
class make_vector {
public:
  typedef make_vector<T> my_type;
  my_type& operator<< (const T& val) {
    data_.push_back(val);
    return *this;
  }
  operator std::vector<T>() const {
    return data_;
  }
private:
  std::vector<T> data_;
};

int main()
{
    std::vector<int> vec = make_vector<int>() << 1 << 2 << 3 << 5 << 9;
    for (int i = 0; i < vec.size(); i++)
        cout << vec[i] << " ";
        
    if ( std::any_of(vec.begin(), vec.end(),[](int i){return i>9;} ) )
        cout << "There is two-digit number\n";
    else cout << "There isn't any two-digit number\n";
    
    
    vec.push_back(15);          
    for (int i = 0; i < vec.size(); i++)            //скопировал аки индус
        cout << vec[i] << " ";
        
    if ( std::any_of(vec.begin(), vec.end(),[](int i){return i>9;} ) )
        cout << "There is two-digit number\n";
    else cout << "There isn't any two-digit number\n";
    
    
   return 0;
}

//код проверялся единственным онлайн-компилятором, который это дело принял: http://coliru.stacked-crooked.com/
