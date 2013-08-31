#include <iostream>

/*
// Usage Example

// TypeTraits policy class using boost::shared_ptr
template <typename T>
struct TypeTraitsShared{
    typedef const T type;
	typedef boost::shared_ptr<const T> factoryConstructedPtr;
};

// TypeTraits policy class using raw pointers
template <typename T>
struct TypeTraitsRaw{
	typedef const T type;
	typedef const T* factoryConstructedPtr;
};

class Prova1 : public FactoryConstructible<TypeTraitsRaw<Prova1> >{
public:
	Prova1(){}
};

class Prova2 : public FactoryConstructible<TypeTraitsShared<Prova2> >{
protected:
	friend FactoryConstructible<TypeTraitsShared<Prova2> >;
	Prova2(double& a){
		a += 1;
	}
};

class Prova3 : public FactoryConstructible<TypeTraitsShared<Prova3> >{
protected:
	friend FactoryConstructible<TypeTraitsShared<Prova3> >;
	Prova3(double* a){
		*a += 1;
	}
};

class Prova4 : public FactoryConstructible<TypeTraitsShared<Prova4> >{
protected:
	friend FactoryConstructible<TypeTraitsShared<Prova4> >;
	Prova4(const double& a){
	}
};

class Prova5 : public FactoryConstructible<TypeTraitsShared<Prova5> >{
protected:
	friend FactoryConstructible<TypeTraitsShared<Prova5> >;
	Prova5(const double& a){
	}
};

void f()
{
	Prova1::ptr p1 = Prova1::factory();
	delete p1;

	double a = 5;
	Prova2::ptr p2 = Prova2::factory(a);
	cout << a << endl;

	Prova3::ptr p3 = Prova3::factory(&a);
	cout << a << endl;

	Prova4::ptr p4 = Prova4::factory(a);
	cout << a << endl;
	
	Prova5::ptr p5 = Prova5::factory(5.);
	
	system("pause");
	return;
}

*/

template <typename TypeTraits>
class FactoryConstructible{
public:
	typedef typename TypeTraits::factoryConstructedPtr ptr;
	typedef typename TypeTraits::type type;

	//no arguments
	static ptr factory(){
		ptr ret(new type());
		return ret;
	}

	//one argument
	template <typename T1>
	static ptr factory(T1 & t1){
		ptr ret(new type(t1));
		return ret;
	}
	template <typename T1>
	static ptr factory(T1 const & t1){
		ptr ret(new type(t1));
		return ret;
	}

	//two arguments
	template <typename T1, typename T2>
	static ptr factory(T1 & t1, T2 & t2){
		ptr ret(new type(t1, t2));
		return ret;
	}
	template <typename T1, typename T2>
	static ptr factory(T1 const & t1, T2 const & t2){
		ptr ret(new type(t1, t2));
		return ret;
	}
	template <typename T1, typename T2>
	static ptr factory(T1 const & t1, T2 & t2){
		ptr ret(new type(t1, t2));
		return ret;
	}
	template <typename T1, typename T2>
	static ptr factory(T1 & t1, T2 const & t2){
		ptr ret(new type(t1, t2));
		return ret;
	}
	
	//three arguments
	template <typename T1, typename T2, typename T3>
	static ptr factory(T1 & t1, T2 & t2, T3 & t3){
		ptr ret(new type(t1, t2, t3));
		return ret;
	}
	template <typename T1, typename T2, typename T3>
	static ptr factory(T1 & t1, T2 & t2, T3 const & t3){
		ptr ret(new type(t1, t2, t3));
		return ret;
	}
	template <typename T1, typename T2, typename T3>
	static ptr factory(T1 & t1, T2 const & t2, T3 & t3){
		ptr ret(new type(t1, t2, t3));
		return ret;
	}
	template <typename T1, typename T2, typename T3>
	static ptr factory(T1 & t1, T2 const & t2, T3 const & t3){
		ptr ret(new type(t1, t2, t3));
		return ret;
	}
	template <typename T1, typename T2, typename T3>
	static ptr factory(T1 const & t1, T2 & t2, T3 & t3){
		ptr ret(new type(t1, t2, t3));
		return ret;
	}
	template <typename T1, typename T2, typename T3>
	static ptr factory(T1 const & t1, T2 & t2, T3 const & t3){
		ptr ret(new type(t1, t2, t3));
		return ret;
	}
	template <typename T1, typename T2, typename T3>
	static ptr factory(T1 const & t1, T2 const & t2, T3 & t3){
		ptr ret(new type(t1, t2, t3));
		return ret;
	}
	template <typename T1, typename T2, typename T3>
	static ptr factory(T1 const & t1, T2 const & t2, T3 const & t3){
		ptr ret(new type(t1, t2, t3));
		return ret;
	}

	//four arguments
	template <typename T1, typename T2, typename T3, typename T4>
	static ptr factory(T1 & t1, T2 & t2, T3 & t3, T4 & t4){
		ptr ret(new type(t1, t2, t3, t4));
		return ret;
	}
	template <typename T1, typename T2, typename T3, typename T4>
	static ptr factory(T1 & t1, T2 & t2, T3 & t3, T4 const & t4){
		ptr ret(new type(t1, t2, t3, t4));
		return ret;
	}
	template <typename T1, typename T2, typename T3, typename T4>
	static ptr factory(T1 & t1, T2 & t2, T3 const & t3, T4 & t4){
		ptr ret(new type(t1, t2, t3, t4));
		return ret;
	}
	template <typename T1, typename T2, typename T3, typename T4>
	static ptr factory(T1 & t1, T2 & t2, T3 const & t3, T4 const & t4){
		ptr ret(new type(t1, t2, t3, t4));
		return ret;
	}
	template <typename T1, typename T2, typename T3, typename T4>
	static ptr factory(T1 & t1, T2 const & t2, T3 & t3, T4 & t4){
		ptr ret(new type(t1, t2, t3, t4));
		return ret;
	}
	template <typename T1, typename T2, typename T3, typename T4>
	static ptr factory(T1 & t1, T2 const & t2, T3 & t3, T4 const & t4){
		ptr ret(new type(t1, t2, t3, t4));
		return ret;
	}
	template <typename T1, typename T2, typename T3, typename T4>
	static ptr factory(T1 & t1, T2 const & t2, T3 const & t3, T4 & t4){
		ptr ret(new type(t1, t2, t3, t4));
		return ret;
	}
	template <typename T1, typename T2, typename T3, typename T4>
	static ptr factory(T1 & t1, T2 const & t2, T3 const & t3, T4 const & t4){
		ptr ret(new type(t1, t2, t3, t4));
		return ret;
	}
	template <typename T1, typename T2, typename T3, typename T4>
	static ptr factory(T1 const & t1, T2 & t2, T3 & t3, T4 & t4){
		ptr ret(new type(t1, t2, t3, t4));
		return ret;
	}
	template <typename T1, typename T2, typename T3, typename T4>
	static ptr factory(T1 const & t1, T2 & t2, T3 & t3, T4 const & t4){
		ptr ret(new type(t1, t2, t3, t4));
		return ret;
	}
	template <typename T1, typename T2, typename T3, typename T4>
	static ptr factory(T1 const & t1, T2 & t2, T3 const & t3, T4 & t4){
		ptr ret(new type(t1, t2, t3, t4));
		return ret;
	}
	template <typename T1, typename T2, typename T3, typename T4>
	static ptr factory(T1 const & t1, T2 & t2, T3 const & t3, T4 const & t4){
		ptr ret(new type(t1, t2, t3, t4));
		return ret;
	}
	template <typename T1, typename T2, typename T3, typename T4>
	static ptr factory(T1 const & t1, T2 const & t2, T3 & t3, T4 & t4){
		ptr ret(new type(t1, t2, t3, t4));
		return ret;
	}
	template <typename T1,typename T2, typename T3, typename T4>
	static ptr factory(T1 const & t1, T2 const & t2, T3 & t3, T4 const & t4){
		ptr ret(new type(t1, t2, t3, t4));
		return ret;
	}
	template <typename T1, typename T2, typename T3, typename T4>
	static ptr factory(T1 const & t1, T2 const & t2, T3 const & t3, T4 & t4){
		ptr ret(new type(t1, t2, t3, t4));
		return ret;
	}
	template <typename T1, typename T2, typename T3, typename T4>
	static ptr factory(T1 const & t1, T2 const & t2, T3 const & t3, T4 const & t4){
		ptr ret(new type(t1, t2, t3, t4));
		return ret;
	}

protected:
	FactoryConstructible(){}
	~FactoryConstructible(){}
};

int main(){
  
}
