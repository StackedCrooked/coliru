#include <iostream>
#include <stdint.h>

class Base
{
    public:
        Base(int aLockValue)
        {
            mLock = aLockValue;
        }
    
    protected:
    
        int mLock;
};

class Derived: public Base
{
    protected:
    
        static int mLock;

    public: 
        Derived(int aLockValue):
        Base(aLockValue)
        {
        }

        void SetBaseLock(int aLockValue)
        {
            Base::mLock = aLockValue;
        }
        
        void SetLock(int aLockValue)
        {
            mLock = aLockValue;
        }
    
        int GetLock()
        {
            return mLock;
        }
        
        int GetNonStaticVersionOfLock()
        {
            return Base::mLock;
        }
        
        int GetStaticVersionOfLock()
        {
            return Derived::mLock;
        }
};

int Derived::mLock = 42;

int main()
{
    Derived d(123);
    
    std::cout << "d.mLock        = " << d.GetLock() << std::endl;
    std::cout << "Base::mLock    = " << d.GetNonStaticVersionOfLock() << std::endl;
    std::cout << "Derived::mLock = " << d.GetStaticVersionOfLock() << std::endl;    
    
    d.SetLock(456);
    d.SetBaseLock(321);
    
    std::cout << "d.mLock        = " << d.GetLock() << std::endl;
    std::cout << "Base::mLock    = " << d.GetNonStaticVersionOfLock() << std::endl;
    std::cout << "Derived::mLock = " << d.GetStaticVersionOfLock() << std::endl;    

return 0;
}