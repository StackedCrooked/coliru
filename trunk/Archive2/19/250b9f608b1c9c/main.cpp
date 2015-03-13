    template<class Implementation>
	class ICallback{
	private:
		std::unique_ptr<Implementation> u_impl_;
	public:
		ICallback()
			: u_impl_(static_cast<Implementation*>(this))
		{
			
		}
		bool Call(){
			return u_impl_->Call();
		}
	};
    
    template<class Type>
	class Callback : ICallback<Callback<Type>>{
	private:
		std::weak_ptr<Type> w_ptr_;
		std::function<void()> func_;
	public:
		Callback(std::weak_ptr<Type> w_ptr, std::function<void()> func){
			w_ptr_ = w_ptr;
			func_ = func;
		}
		bool Call(){
			if (w_ptr_.expired()) return false;
			else func_();
			return true;
		}
		
	};