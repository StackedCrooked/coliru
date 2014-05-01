#include <iostream>
#include <memory>
#include <type_traits>


// Inheritance has one nice advantage: deleting the derived object ensures deletion of the base class.
// However, the drawback is that it creates a strong coupling.
// Here I try to get the best of both worlds.



namespace PacketBlasting
{
    // no dependency to RPC
    
    struct Flow
    {
        Flow() { std::cout << "Create Flow\n"; }
        virtual ~Flow() { std::cout << "Destroy Flow\n"; }
    };
}



namespace RPC
{
    // no dependency to PacketBlasting or Communication
    
    
    template<typename T>    
    struct ServerObject
    {
        ServerObject() { std::cout << "Create ServerObject<T>\n"; }
        ~ServerObject() { std::cout << "Destroy ServerObject<T>\n"; }
    };
        
        
    
    /**
     * Helper function that generates a Helper class that inherits both T and ServerObject<T>
     * It returns the new instance as std::unique_ptr<T> (the "Helper" is hidden for the user)
     * Deleting this object will result in deletion of both T and ServerObject<T>.
     * Requires T to have a virtual destructor
     */
    template<typename T, typename ...Args>
    std::unique_ptr<T> Create(Args&& ...args)
    {
        // T must have virtual destructor
        static_assert(std::is_polymorphic<T>::value, "");
    
        // Helper class inherits both T and RPC::ServerObject<T>
        struct Helper : ServerObject<T>, T
        {
            Helper(Args&& ...args) : T(std::forward<Args>(args)...)
            {
            }
            
            virtual ~Helper() {}
        };
        
        
        // deleting the T will also result in delete the RPC object.
        return std::unique_ptr<T>(new Helper);
    }
}



int main()
{
    // here we depend both on RPC and PacketBlasting
    
    using namespace PacketBlasting;
    using namespace RPC;
    
    std::unique_ptr<Flow> flow = Create<Flow>();
    
    std::cout << "\n";
    
    
    
    flow.reset(); // also deletes the RPC object. So no lifetime syncing required. 
}
