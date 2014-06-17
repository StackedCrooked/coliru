// Type your code here, or load an example.
#include <vector>
#include <list>

#include <utility>
#include <iostream>

template <typename T>
class sequence
{
    std::vector<T> internals_;
public:

	typedef typename std::vector<T>::const_iterator iterator;
	
	template <typename TContainer>
	sequence(TContainer container) {
        internals_.resize(container.size());
		std::move(container.begin(), container.end(), internals_.begin());
	}
    
    sequence(std::vector<T>&& vec){
        internals_ = std::move(vec); 
    }
    
    // TODO: add here iterator based shit
	
	iterator begin () {
		return internals_.begin();
	}
	
	iterator end() {
		return internals_.end();
	}
};

sequence<int> return_from_list()
{
    std::list<int> x = {1, 2, 3};
    return std::move(x);
}

sequence<int> return_from_vector()
{
    std::vector<int> x = {1, 2, 3};
    return std::move(x);
}


int main() 
{
    // Check for constexpressiveness
    std::list<int> x = {1, 2, 3, 4};
    sequence<int> y = std::move(x);
    for (auto val : y) {
        std::cout << val << std::endl;
    }
    
    for (auto val : return_from_list()) {
        std::cout << val << std::endl;
    }

    for (auto val : return_from_vector()) {
        std::cout << val << std::endl;
    }

    std::cout << "Hello world" << std::endl;
}