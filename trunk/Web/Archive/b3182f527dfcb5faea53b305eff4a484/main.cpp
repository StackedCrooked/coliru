#include <utility>
#include <iostream>
#include <string>

using std::cout; using std::endl;

template <typename T>
class SuperClass
{
public:    

	SuperClass() : m_Str("'a string'"), m_Data(), m_Int(0), m_bValid(true)
	{
		cout << "SuperClass() empty constructor" << endl;
	}
	~SuperClass()
	{
		cout << "~SuperClass() destructor, string value at destruct: " << m_Str << endl;
	}

	SuperClass(const SuperClass<T>& copyFrom) : m_Str(copyFrom.m_Str), m_Data(copyFrom.m_Data)
	{
		cout << "SuperClass COPY-constructor" << endl;
		m_Int = copyFrom.m_Int; m_bValid = copyFrom.m_bValid;
	}
	SuperClass(SuperClass<T>&& moveFrom) throw()
	// All non-POD data must be std::move()'d
		: m_Str(std::move(moveFrom.m_Str)), m_Data(std::move(moveFrom.m_Data))
	{
		cout << "SuperClass MOVE-constructor" << endl;
		m_Int = std::move(moveFrom.m_Int);	
		m_bValid = std::move(moveFrom.m_bValid);
	}

	SuperClass<T>& operator=(const SuperClass<T>& copyFrom)
	{
		cout << "SuperClass COPY-Assignment" << endl;
		// Avoid copies to self
		if (this != &copyFrom)
		{
			assign(copyFrom);
		}
		return *this;
	}
	SuperClass<T>& operator=(SuperClass<T>&& moveFrom) throw()
	{
		cout << "SuperClass MOVE-Assignment" << endl;
		// Avoid moves to self
		if (this != &moveFrom)
		{
			// Move MUST be used, otherwise assign(Const LValue) version is invoked
			assign(std::move(moveFrom));
		}
		return *this;
	}

	void assign(const SuperClass<T>& copyFrom)
	{
		cout << "SuperClass.assign() - Const LValue version" << endl;
		// Our data will be overwritten, so its best to free the resources 1st
		destroy();
		// Now we can copy
		m_Str = copyFrom.m_Str;
		m_Data = copyFrom.m_Data;
		m_Int = copyFrom.m_Int;
		m_bValid = copyFrom.m_bValid;
	}

	void assign(SuperClass<T>&& moveFrom)
	{
		cout << "SuperClass.assign() - RValue version" << endl;
        // Our data will be overwritten, so its best to free the resources 1st
    	destroy();        
		// move for non-POD and unknown types:
		m_Str = std::move(moveFrom.m_Str);
		m_Data = std::move(moveFrom.m_Data);
		
		// for POD members we can simply copy-assign, then invalidate the temporary
		m_Int = moveFrom.m_Int;
		moveFrom.m_Int = 0;

		m_bValid = moveFrom.m_bValid;
		moveFrom.m_bValid = false;
	}

	void destroy()
	{
		m_Str.clear();
		m_bValid = false;		
		// Since T doesn't have a known 'destroy' method, we can't make assumptions here
		//m_Data.destroy();
	}

	void setInt(int nInt)
	{
		m_Int = nInt;
	}

protected:
	std::string m_Str;
	T m_Data;
	int m_Int;
	bool m_bValid;	
};


class SubClass : public SuperClass<unsigned>
{
public:

	typedef SuperClass<unsigned> Parent;

	SubClass() : Parent()
	{
		cout << "SubClass() empty constructor" << endl;
	}
	~SubClass()
	{
		cout << "~SubClass() destructor" << endl;
	}
	SubClass(const SubClass& copyFrom) : Parent(copyFrom)
	{
		cout << "SubClass COPY-constructor" << endl;
	}
	SubClass(SubClass&& moveFrom) throw()
		: Parent(std::move(moveFrom))
	{
		cout << "SubClass MOVE-constructor" << endl;
	}

	SubClass& operator=(const SubClass& copyFrom)
	{
		cout << "SubClass COPY-Assignment" << endl;
		if (this != &copyFrom)
		{
			Parent::assign(copyFrom);
		}
		return *this;
	}
	SubClass& operator=(SubClass&& moveFrom) throw()
	{
		cout << "SubClass MOVE-Assignment" << endl;
		if (this != &moveFrom)
		{
			// Move MUST be used, otherwise assign(Const LValue) version is invoked
			Parent::assign(std::move(moveFrom));
		}
		return *this;
	}
};

class SubFailClass : public SuperClass<char>
{
public:
	typedef SuperClass<char> Parent;

	SubFailClass() : Parent()
	{
		cout << "SubFailClass() empty constructor" << endl;
	}
	~SubFailClass()
	{
		cout << "~SubFailClass() destructor" << endl;
	}
	SubFailClass(const SubFailClass& copyFrom) : Parent(copyFrom)
	{
		cout << "SubFailClass COPY-constructor" << endl;
	}

// Failure to pass moveFrom to parent correctly
	SubFailClass(SubFailClass&& moveFrom) throw()
	// Correct version = ": Parent(std::move(moveFrom))"
		: Parent(moveFrom)	
	{
		cout << "SubFailClass MOVE-constructor" << endl;
	}

	SubFailClass& operator=(const SubFailClass& copyFrom)
	{
		cout << "SubFailClass COPY-Assignment" << endl;
		if (this != &copyFrom)
		{
			Parent::assign(copyFrom);
		}
		return *this;
	}
// Failure to pass to correct assign()
	SubFailClass& operator=(SubFailClass&& moveFrom) throw()
	{
		cout << "SubFailClass MOVE-Assignment" << endl;
		if (this != &moveFrom)
		{
			// Move MUST be used, otherwise assign(Const LValue) version is invoked
			Parent::assign(moveFrom);
		}
		return *this;
	}
};


SubClass retSub()
{
	cout << "\n- retSub(): returning temporary --\n" << endl;
	auto Obj = SubClass();
	// Perform some operation(s) so that the compiler is less likely to elide the temporary
	Obj.setInt(5);
	return Obj;
}

void TestSub()
{
	cout << "\n[[TestSub(): Initializing child object via temp (via retSub())]]" << endl;
	//Move construction: implicit, explicit:
	//auto myObj = retSub();
	auto myObj(retSub());

	cout << "\n[[TestSub(): Empty constructor]]\n" << endl;
	SubClass dupObj;

	cout << "\n[[TestSub(): Copy-assignment]]\n" << endl;
	dupObj = myObj;
	cout << "\n[[TestSub() exiting, Destructors follow]]\n" << endl;
}


SuperClass<short> retSuper()
{
	cout << "\n-- retSuper(): returning temporary [copy elision form] --\n" << endl;
	// This line is typically constructed at the return location, rather than creating a temporary
	return SuperClass<short>();
}

void TestSuper()
{
	cout << "\n[[TestSuper(): Initializing parent object via temp (via retSuper())]]" << endl;
	auto mySuper = retSuper();

	cout << "\n[[TestSuper(): Empty construction]]\n" << endl;
	decltype(retSuper()) dupSuper;

	cout << "\n[[TestSuper(): MOVE-assignment]]\n" << endl;
	dupSuper = std::move(mySuper);

	cout << "\n[[TestSuper() exiting, Destructors follow]]\n" << endl;
}

SubFailClass retSubFail()
{
	cout << "\n-- retSubFail(): returning temporary --\n" << endl;
	auto Obj = SubFailClass();
	// Perform some operation(s) so that the compiler is less likely to elide the temporary
	Obj.setInt(8);
	return Obj;
}

void TestSubFail()
{
	cout << "\n[[TestSubFail(): Initializing child object via temp (via retSubFail()) -\n\tNotice Parent COPY-construct error!]]" << endl;
	auto myFail = retSubFail();

	cout << "\n[[TestSubFail(): Empty constructor]]\n" << endl;
	SubFailClass dupFail;

	cout << "\n[[TestSubFail(): MOVE-assignment - Notice incorrect LValue assign!]]\n" << endl;
	dupFail = std::move(myFail);

	cout << "\n[[TestSubFail() exiting, Destructors follow]]\n" << endl;
}

int main()
{
	TestSuper();
	TestSub();
	TestSubFail();
	return 0;
}