    template<class T>
	void foo(T a)
	{
		std::cout << a;
	}

	template<class T>
	using signal_t = signal<void(int)>;
	
	signal_t<int> sig;
	sig.connect(foo);
	sig(23123);