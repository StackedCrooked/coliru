struct Foo { Foo() {} };

int main()
{  
    {
        a:
            goto e; // OK
        
        b:
            goto d; // ERROR
            
        c:
            Foo foo;
            
            
        d:
            ;
   }
   
   e:
    ;
    
   
}
