    const int blah = 1 ;
    
    enum Flags { good=0, fail=blah, bad=2, eof=4 };

	constexpr 
    int operator|(Flags f1, Flags f2) { return Flags(static_cast<int>(f1) | static_cast<int>(f2)); }

	void f(Flags x)
	{
		switch (x) {
		case bad:         /* ... */ break;
		case eof:         /* ... */ break;
		case bad|eof:     /* ... */ break;
		default:          /* ... */ break;
		}
	}
    
    int main()
    {
        constexpr int size = 10 ;
        int arr[size] ;
    }