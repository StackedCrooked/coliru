int foo(void* a,int b ,char** c ,char** d )
{
 
 return 1; 
}

int main( )
{
     typedef int (*SQLQueryCallback)(void*,int,char**,char**); 
     
     SQLQueryCallback = &foo ; // error: expected unqualified-id before '=' token. Works only when SQLQueryCallback is function pointer.
     
     SQLQueryCallback sqlCb = &foo ; // This is correct since SQLQueryCallback is a type
}