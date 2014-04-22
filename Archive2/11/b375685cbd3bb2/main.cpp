class A { 
public:   
    class state {
        friend A;
        void* intermediate_buffer_;
    };
    
   //uses intermediate buffer but doesn't change outward behavior
   //intermediate buffer is expensive to fill
   state foo(void* input_data);

   //uses intermediate buffer and DOES explicitly change something internally
   //intermediate buffer is expensive to fill
   state bar(void* input_data);

   //if input_data hasn't changed since foo, we can totally reuse what happened in foo
   //I cannot check if the data is equal quickly, so I allow the user to pass in the
   //assertion (put the honerous on them, explicitly tell them in the comments
   //that this is dangerous to do, ect)
   void bar(void* input_data);
   void bar(state input_data);
private:
   void* something_;
};

int main() {
    A a;
    a.bar({...};
    
    A::state state = a.foo({...}};
    a.bar(state);
}