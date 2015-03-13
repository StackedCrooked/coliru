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
			// I get a C3848 in VS2013 due to the 'bound' being used in the lambda bellow
			return new Callback{
				[w_ptr, bound]{
					if (auto ptr = w_ptr.lock()){
						bound();
						return true;
					}
					else return false;
				}
			};
		}
		bool Call(){
			return func_();
		}
		
	};