#include <iostream>

template <typename type, unsigned int size>
class vector
{
};

template <unsigned int size>
class vector<void, size>
{
    public:
    
        void stuff();   
};

template <unsigned int size>
class vector<float, size> : public vector<void, size>
{
    public:
    
        void bar();
};

// -------

template <unsigned int size>
void vector<void, size>::stuff()
{
	std::cout << "stuff" << std::endl;
}

template <unsigned int size>
void vector<float, size>::bar()
{
	std::cout << "bar" << std::endl;
}

template class vector<int, 2>;
template class vector<int, 3>;
template class vector<unsigned int, 2>;
template class vector<unsigned int, 3>;
template class vector<float, 2>;
template class vector<float, 3>;
template class vector<float, 4>;

int main()
{
    vector<float, 3> lol;
    
    lol.stuff();
    lol.bar();
}