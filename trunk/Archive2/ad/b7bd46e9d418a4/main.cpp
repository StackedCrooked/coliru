#include <array>
#include <vector>
#include <iostream>

template<typename Type>
class elements 
{
    public: 

        elements(const std::initializer_list<Type>& list)
            :
                data_(list)
        {}

        auto begin() const
        {
            return data_.begin(); 
        }

        auto end() const
        {
            return data_.end(); 
        }

    private:

        std::vector<Type> data_; 
}; 

template<typename Type>
class triElement 
{
    public: 

        triElement(const std::initializer_list<Type>& list)
            :
                data_(list)
        {}

        auto begin() const
        {
            return data_.begin(); 
        }

        auto end() const
        {
            return data_.end(); 
        }

    private:

        std::array<Type, 3> data_; 
}; 

template<typename C>
void print(C const & c)
{
    for (const auto& e : c)
    {
        std::cout << e  << " "; 
    }
    std::cout << "\n";
}

using namespace std;

int main(int argc, const char *argv[])
{
    // Works. 
    std::array<int, 3> a = {1,2,3}; 

    print(a);

    // Works. 
    elements<int>  e = {1,2,3,4,5,6,7}; 

    print(e);

    // Fails.
    triElement<int> t = {1,2,3};
    
    print(t);

    return 0;
}




