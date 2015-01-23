#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

class A
{
public:

    A() 
    { 
        m_SomePtr = std::make_shared<bool>( false );
    }

    virtual ~A()
    {
        std::weak_ptr<bool> Ref = m_SomePtr;
        m_SomePtr.reset();

        // Spin (will be optimised into an infinite loop in release builds)
        while ( !Ref.expired() );
    }

    std::shared_ptr<bool> GetPtr() const { return m_SomePtr; }

private:
    std::shared_ptr<bool> m_SomePtr;
};

class B
{
public:
    B( std::shared_ptr<bool> SomePtr ) : m_Ref( SomePtr ) {}

    void LockPtr() { m_SomePtr = m_Ref.lock(); }
    void UnLockPtr() { m_SomePtr.reset(); }

private:
    std::shared_ptr<bool> m_SomePtr;
    std::weak_ptr<bool> m_Ref;
};

int main()
{
    std::unique_ptr<A> a( new A() );
    std::unique_ptr<B> b( new B( a->GetPtr() ) );

    b->LockPtr();

    std::cout << "Starting " << std::endl;

    std::thread first( [&]()
    {
        std::this_thread::sleep_for( std::chrono::seconds( 5 ) );
        b->UnLockPtr();
    } );

    std::thread second( [&]()
    {
        a.reset( nullptr );
    } );

    first.join();
    second.join();

    std::cout << "Complete" << std::endl;
    return 0;
}