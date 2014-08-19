template<class T, T value>
struct set_on_exit {
    set_on_exit(T& var) :var(&var) {}
    ~set_on_exit() {*var = value;}
    set_on_exit(const set_on_exit&rhs) = delete;
    set_on_exit& operator=(const set_on_exit&rhs) = delete;
private:
    T* var;
}

void call_really_just_once()
{
    static std::mutex mutex;
    std::unique_lock<std::mutex> lock(mutex, std::try_to_lock);
    
    //if can't grab the lock, must not be first.  return
    if (!lock)
        return
    
    static bool first = true;    
    //the first thread to get here will have first=true
    //it will set first==false, and no subsequent threads will enter the block
    if (first) {
        first = false;
        
        //only one thread will ever make it here.  
        may_throw();
    }
}