#include <iostream>
#include <mutex>
#include <thread>

 

// Wrapper class for resources X and Y that only allows access to the object if a corresponding lock object is passed.

struct XY
{    
    XY() : x_(), y_() {}
    
    // Define a unique lock types.
    struct X_Locker : private std::lock_guard<std::mutex>
    {
         X_Locker(XY& xy) : std::lock_guard<std::mutex>(xy.x_mutex_) {}
    };
    
    struct Y_Locker : private std::lock_guard<std::mutex>
    {
        // constructor takes the XY object and locks the mutex
         Y_Locker(XY& xy) : std::lock_guard<std::mutex>(xy.y_mutex_) {}
    };
    
    
    // Accessor methods take a Locker object as argument. This makes it impossible for the user to "forget" the lock.
    // Because the lock types are unique the compiler will generate an error if we pass a lock object of the wrong type.
    
    void set_x(X_Locker&, int x) { x_ = x; }
    void set_y(Y_Locker&, int y) { y_ = y; }
    
    int get_x(X_Locker&) const { return x_; }
    int get_y(Y_Locker&) const { return y_; }
    
        
    int sum(X_Locker& xlocker, Y_Locker& ylocker) const
    {
        return get_x(xlocker) + get_y(ylocker);
    }
    
private:    
    friend struct X_Locker;
    friend struct Y_Locker;
    int x_, y_;
    std::mutex x_mutex_, y_mutex_;
};



// This prevents:
// - data race caused by forgetting a lock.
// - dead-lock caused by methods that lock internally and then call other methods which also lock internally.


int main()
{
    // The XY object.
    XY xy;
    
    
    // set x to 3 in first thread
    std::thread t1([&xy]{
        XY::X_Locker xlock(xy); 
        xy.set_x(xlock, 3);
    });
    
    
    // set y to 4 in second thread
    std::thread t2([&xy]{
        XY::Y_Locker ylock(xy); 
        xy.set_y(ylock, 4);
    });
    
    
    // wait for both threads to complete
    t1.join();
    t2.join();
    
    
    // get the sum
    // lambda conveniently provides a scope (to minimize the lifetime of the locks)
    // and it also allows us to return the result and store that outside
    auto sum = [&xy]{
        XY::X_Locker xl(xy); // lock x
        XY::Y_Locker yl(xy); // lock y
        return xy.sum(xl, yl); // pass both locks to the sum method and return the result
    }();
    
    std::cout << sum << std::endl;
}


