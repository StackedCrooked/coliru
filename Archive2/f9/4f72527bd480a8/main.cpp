
// Old version that works, but does not take parameters in the Call function

class Callback{
private:
	std::function<bool()> func_;
private:
	Callback(std::function<bool()> func){
		func_ = func;
	}
public:
	template<class Func, class Type, class... Args>
	static Callback* Create(Func f, std::shared_ptr<Type> s_ptr, Args&&... args){
		std::weak_ptr<Type> w_ptr = s_ptr;
		auto bound = std::bind(f, s_ptr.get(), std::forward<Args>(args)...);
			[w_ptr, bound]() mutable {   // added mutable
			if (auto ptr = w_ptr.lock()){
				bound();
				return true;
			}
			else return false;
		};
		return new Callback{ func };
	}
	bool Call(){
		return func_();
	}
};
    
    
// New version that does not work, because it tries to accept parameters in the Call function
    
template <typename... Args>
class A{
private:
    std::function<bool(Args&&...)> func_;
private:
	A(std::function<bool(Args&&...)> func)
		: func_{ func }
	{

	}
public:
	
	template<class Func, class Type, class... FArgs>
	static A<FArgs...>* Create(Func f, std::shared_ptr<Type> s_ptr, FArgs&&... args){
		std::weak_ptr<Type> w_ptr = s_ptr;
		auto bound = std::bind(f, s_ptr.get(), std::forward<FArgs>(args)...);
		return new A{
			[w_ptr, bound](FArgs&&... as) mutable { // package
				if (auto ptr = w_ptr.lock()){
					bound(as...); // package
					return true;
				}
				else return false;
			}
		};
	}
	bool Call(Args&&... args){
		return func_(std::forward<Args>(args)...);
	}
};
    