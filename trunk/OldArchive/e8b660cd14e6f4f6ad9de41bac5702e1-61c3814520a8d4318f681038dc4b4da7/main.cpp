class MyClass {
    MyClass();                       // Default ctor
	MyClass(int a_param);            // Ctor
	MyClass(MyClass& other);         // Copy ctor
	MyClass(const MyClass& other);   // Copy ctor
	operator=(MyClass& other);       // Assignment
	operator=(const MyClass& other); // Assignment
	MyClass(MyClass&& other);        // Move ctor	
	~MyClass();                      // Dtor
}