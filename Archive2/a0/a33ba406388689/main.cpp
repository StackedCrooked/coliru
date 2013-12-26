struct Derived                                                                               
{                                                                                            
   virtual ~Derived(){}                                                                      
   static void operator delete(void*) = delete;                                                     
};                                                                                           
                                                                                             
                                                                                             
int main()                                                                                   
{                                                                                            
}  