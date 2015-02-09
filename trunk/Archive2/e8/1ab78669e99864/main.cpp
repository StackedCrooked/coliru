#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class make_vector {
public:
    typedef make_vector<T> my_type;
    my_type& operator<<(const T& val) &
    {
        data_.push_back(val);
        return *this;
    }
    my_type&& operator<<(const T& val) &&
    {
        data_.push_back(val);
        return std::move(*this);
    }
    
    operator std::vector<T>&() &
    {
        return  this->data_;
    }
    
    operator std::vector<T>() &&
    {
        return  std::move(this->data_);
    }

private:
    std::vector<T> data_;
};


int main() {
    std::vector<int>  A2 = make_vector<int>() << 1 << 2 << 3 << 4;

    for (std::vector<int>::iterator it = A2.begin(); it != A2.end(); ++it)        
    {
        cout << *it << " ";
    }
    cout << endl;
    return 0;
}