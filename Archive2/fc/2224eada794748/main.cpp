#include <iostream>
#include <string>
#include <memory>
#include <boost/thread.hpp>

using namespace std;
class SafeThreadWorker 
{
public:
   virtual ~SafeThreadWorker() { }

   virtual void Detach() = 0;
   virtual void Interrupt() = 0;
};

template <typename T, typename Method>
class SafeThreadWorkerImpl : public SafeThreadWorker {
public:
   SafeThreadWorkerImpl(std::shared_ptr<T> object, Method method)
   {
      m_thread = boost::thread(&SafeThreadWorkerImpl::Dispatch, object, method);
   }

   virtual void Detach()
   {
      m_thread.detach();
   }

   virtual void Interrupt()
   {
      m_thread.interrupt();
   }

private:
   boost::thread m_thread;

   static void Dispatch(std::shared_ptr<T> object, Method method)
   {
      T* ptr = object.get();
      (ptr->*method)();
   }
};

template<typename T, typename Method>
std::shared_ptr<SafeThreadWorker> MakeSafeThreadWorker(std::shared_ptr<T> object, Method method)
{
   return std::make_shared<SafeThreadWorkerImpl<T, Method>>(object, method);
}

class Foo : public std::enable_shared_from_this<Foo> {
public:
   Foo(int value) : m_value(new int(value))
   {
       cout << "Foo" << endl;
   }

   ~Foo()
   {
      cout << "~Foo" << endl;
      delete m_value;
      m_value = 0;
   }

   void SafeWork()
   {
      cout << "  SafeWork" << endl;
      std::shared_ptr<SafeThreadWorker> safeWorkerThread = MakeSafeThreadWorker(shared_from_this(), &Foo::DoWork);
      safeWorkerThread->Detach();
   }

   void UnSafeWork()
   {
      cout << "  UnSafeWork" << endl;
      boost::thread workerThread(&Foo::DoWork, this);
      workerThread.detach();
   }

private:
   int *m_value;

   void DoWork() 
   {
      if (!m_value) {
        cout << "  DoWork: value=NULL!!" << endl;
        return;
      }
      
      cout << "  DoWork: value=" << *m_value << endl;
   }
};

int main()
{
    {
        std::shared_ptr<Foo> foo(new Foo(10));
        foo->SafeWork();
    }
    sleep(5);

    {
        std::shared_ptr<Foo> foo(new Foo(10));
        foo->UnSafeWork();
    }
    sleep(5);
    
    return 1;
}