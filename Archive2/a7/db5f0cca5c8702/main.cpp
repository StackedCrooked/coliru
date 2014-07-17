#include <iostream>
#include <vector>
#include <iterator>
#include <memory>
#include <algorithm>
#include <functional>

using namespace std;

class AbstractCallback{
    public:
		AbstractCallback() {};
		virtual ~AbstractCallback() {};
		virtual void operator()() {};
};
template<class R,typename... Args>
class ObjFunCallback:public AbstractCallback{
    public:
		ObjFunCallback(std::function<R(Args...)>fun,Args...args){
			_fun = std::bind(fun,args...);
		};
		virtual void operator()(){
			_fun();
		}
	private: 
		std::function<R()>  _fun;
};

class Test{
    public:
    void fun(){
        cout<<"fun"<<endl;
    }
    
    void fun1(int i){
        cout<<"fun "<<i<<endl;
    }
    
    void fun2(int i, int j){
        cout<<"fun "<<i<<","<<j<<endl;
    }
};

typedef std::shared_ptr<AbstractCallback> AbstractCallbackPtr;

template<class T_return, class T_obj, class arg1, class arg2>
static inline
ObjFunCallback<T_return,T_obj,arg1,arg2> make_callback(T_obj* pObj, T_return(T_obj::* func)(arg1, arg2), arg1 a_1, arg2 a_2) {
	return ObjFunCallback<T_return,T_obj*,arg1,arg2>(func,pObj,a_1,a_2);
}

template<class T_return, class T_obj>
static inline AbstractCallbackPtr make_callbackPtr(T_obj* pObj, T_return(T_obj::* func)()) {
	return AbstractCallbackPtr(new ObjFunCallback<T_return,T_obj*>(func,pObj));
}

template<class T_return, class T_obj, class arg1>
static inline AbstractCallbackPtr make_callbackPtr(T_obj* pObj, T_return(T_obj::* func)(arg1), arg1 a_1) {
	return AbstractCallbackPtr(new ObjFunCallback<T_return,T_obj*,arg1>(func,pObj,a_1));
}

template<class T_return, class T_obj, class arg1, class arg2>
static inline AbstractCallbackPtr make_callbackPtr(T_obj* pObj, T_return(T_obj::* func)(arg1, arg2), arg1 a_1, arg2 a_2) {
	return AbstractCallbackPtr(new ObjFunCallback<T_return,T_obj*,arg1,arg2>(func,pObj,a_1,a_2));
}

int main()
{
   cout << "start:" << endl; 
   Test t;
   ObjFunCallback<void,Test*> callback0(&Test::fun,&t);
   callback0();
   
   
   ObjFunCallback<void,Test*,int> callback1(&Test::fun1,&t,1);
   callback1();

   cout<<"use common interface"<<endl;
   std::vector<AbstractCallbackPtr> v;
   v.push_back(AbstractCallbackPtr(new ObjFunCallback<void,Test*>(&Test::fun,&t)));
   v.push_back(AbstractCallbackPtr(new ObjFunCallback<void,Test*,int>(&Test::fun1,&t,1)));
   v.push_back(AbstractCallbackPtr(new ObjFunCallback<void,Test*,int,int>(&Test::fun2,&t,10,11)));
   for_each(v.begin(),v.end(),[](AbstractCallbackPtr pCallback){
		   (*pCallback)();
		   });

   cout<<"use simple way"<<endl;
   Test t1;
   AbstractCallbackPtr ptr = make_callbackPtr(&t1,&Test::fun);
   (*ptr)();
   
   AbstractCallbackPtr ptr1 = make_callbackPtr(&t1,&Test::fun1,1);
   (*ptr1)();

   AbstractCallbackPtr ptr2 = make_callbackPtr(&t1,&Test::fun2,10,11);
   (*ptr2)();
   return 0;
}
