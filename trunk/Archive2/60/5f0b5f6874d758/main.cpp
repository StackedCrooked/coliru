
#include <functional>
#include <memory>

// new Create function called FCreate
template<typename Func, typename Type, typename... FArgs>
static auto FCreate(Func f, std::shared_ptr<Type> s_ptr, FArgs&&... args){
    std::weak_ptr<Type> w_ptr = s_ptr;
	auto func = 
		[w_ptr](FArgs&&... f_args){
		if (auto ptr = w_ptr.lock()){
			ptr->f(f_args...);
			return true;
		}
		else return false;
	};
	return func; // expects trailing return type, only in msvc though?
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
    
    //auto a = Create(&B::Increment, std::make_shared<B>(), std::placeholders::_1);
    
    return 0;
}
 