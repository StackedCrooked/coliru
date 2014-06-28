Seems pretty straightforwared.  With the macro variant, there's two structures. if the first template parameter is `true`, then that code gets instantiated, otherwise the other gets instantiated.  The other branch of code is never instantiated, so the problems don't occur.

With the lambda-based solution, you have a similar thing, except for the lambdas.  Lambdas are like real functionoids, so your second code is vaguely like this:

    
    template<bool do_it>
    struct lambda1{
         typedef decltype(if_else<do_it>([]{ return B(); },[]{ return A(); }));
    
         lambda1(Test*& self, datatype& data) 
             :self(&self), data(&data)
         {}
         auto operator()() {return (*self)->fn1(*data);}
     
         Test** self;
         datatype* self;
    };
    //similar for lambda2
    
    template<bool do_it>
    void go(){        
        auto data = if_else<do_it>(
                    []{ return B(); },
                    []{ return A(); }
                );
        std::cout << std::is_same<decltype(data), A>::value;
        lambda1 lam1(this,data);
        lambda2 lam2(this,data);

        std::cout << if_else<do_it>(lam1, lam2);
    }

So this means when `go<false>` is instantiated, `data` is of type `B`, and when it generates the code for the `lam1` and `lam2` lambdas, it fails to create the `lambda1::operator()` because it can't pass a `B` to a function expecting an `A`.  It can't pass these objects to the `if_else` functions, because they can't be instantiated!

Basically, what it comes down to is that C++11 lambdas aren't going to cut it here, and you'll need to put the two forks into different functions manually or with macros.  The normal way is simply use dispatching functions:

    struct A{
        int id= 4;
    };
    struct B : A{
        int h = 900;
    };


    class Test{
        int fn1(B &a) {std::cout << "fn1 " << a.h; return a.h;}
        int fn2(A &a) {std::cout << "fn1 " << a.id; a.id = 9; return a.id;}

        int dispatch_fn(B& b) {return fn1(b);}
        int dispatch_fn(A& a) {return fn2(a);}        
    public:
        template<bool do_it>
        void go(){
            using datatype = typename std::conditional<do_it,B,A>::type;
            datatype data;
            std::cout << std::is_same<decltype(data), A>::value;
            std::cout << dispatch_fn(data); //easy
        }
    };

    int main(){
        Test().template go<false>();
        return 0;
    }

You'll find patterns like this all over the standard template library.