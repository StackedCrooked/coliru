class uncopyable {
    
   uncopyable(uncopyable const&) = delete;
   uncopyable & operator =(uncopyable const&) = delete;
};


struct type : uncopyable {

   void * ptr;
};


int main() {}
