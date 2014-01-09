#include <stddef.h>
    
    struct s {
            int i;
            char c;
            double d;
            char a[];
        };
    
    int main()
    {
        int offsetArray[4] = { offsetof(struct s, i ), offsetof( struct s, c ), offsetof(struct s, d ), offsetof(struct s, a )  } ;
        
        return 0 ;
    }