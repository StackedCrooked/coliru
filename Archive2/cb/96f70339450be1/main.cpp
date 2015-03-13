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
			auto func =
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