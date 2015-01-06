

    // member function: Non-const version
    //template <typename R, typename... Args, R (T::* func)(Args...)>
    //int call (int arf) {
    //    return 1;
    //}
    // work... around?
    template <typename T, typename R, typename... Args>
    struct member {
        template <R (T::* func)(Args...)>
        static int call (int arf) {
            return 0;
        }
    };
    
    // free function version
    template <typename R, typename... Args, R (* func)(Args...)>
    int call (int arf) {
        return 1;
    }
    
    // member-variable pointer
    template <typename T, typename R, R T::* variable>
    int call (int arf) {
        return 2;
    }

    struct woof {
        int bark;
        
        void meow () {
        }
    };
    
    bool purr (bool) {
        return true;
    }

int main()
{
    typedef int(* fp)(int);
    fp a = call<woof, int, &woof::bark>;
    // tears begin here
    //fp b = call<bool, bool, &purr>;
    //fp c = call<woof, void, &woof::meow>;
}