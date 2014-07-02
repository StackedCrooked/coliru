class Handle;

class Base
{
protected:		
	 virtual void load(const Handle &handle, const char * data) = 0;
public:
	 virtual ~Base();
	 void operator()(const Handle &handle, const char * data)
	 {
		 load(handle, data);
	 }
};

template<class Func>
class Child : public Base
{
	Func loader;
protected:
	virtual void load(const Handle &handle, const char * data)
	{
		loader(handle, *reinterpret_cast<const /* type of Func's second argument */  *>(data));
	}
public:
	Child(Func f) : loader(f) {}
};