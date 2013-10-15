template <typename T>
struct X {
    
    T pop()
	{
		T tmp{ std::move(/*back()*/) }; // move/copy might throw, we're fine
		// destroy back()               // noexcept
		return tmp;                     // ??
	}
    
};
