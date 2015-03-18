
#include <functional>
#include <memory>

template <typename... Args>
class A{
private:
    std::function<bool(Args&&...)> func_;
public:
	A(std::function<bool(Args&&...)> func)
		: func_{ func }
	{

	}

	bool Call(Args&&... args){
		return func_(std::forward<Args>(args)...);
	}
};

template<class Func, class Type, class... FArgs>
static A<FArgs...>* Create(Func f, std::shared_ptr<Type> s_ptr, FArgs&&... args){
	std::weak_ptr<Type> w_ptr = s_ptr;
	auto bound = std::bind(f, s_ptr.get(), std::forward<FArgs>(args)...);
	return new A<FArgs...>{
		[w_ptr, bound](FArgs&&... as) mutable { // package
			if (auto ptr = w_ptr.lock()){
				bound(as...); // package
				return true;
			}
			else return false;
		}
	};
}

class B{
private:
    int taco_ = 0;
public:
	int Increment(int i){
		return taco_ += i;
	}
};
 
int main(){
    
    auto a = Create(&B::Increment, std::make_shared<B>(), std::placeholders::_1);
    
    return 0;
}
 