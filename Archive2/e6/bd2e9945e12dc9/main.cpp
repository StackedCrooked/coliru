struct Derived                                                                               
{                                                                                            
   virtual ~Derived(){}                                                                      
   void operator delete(void*) = delete;                                                     
};                                                                                           
                                                                                             
                                                                                             
int main()                                                                                   
{                                                                                            
}  