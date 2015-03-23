    #include <stdlib.h>
    #include <stdio.h>

    typedef struct s_Dog {
        struct s_Dog *bob;
        struct s_Dog *jack;
        int x;
    } Dog;

    void die( const char * error ) {
        fprintf(stderr, error);
        exit(99);
    }
    
    Dog *newDog(int x) {
        Dog *dog = (Dog*) malloc(sizeof(Dog));
        if (dog == NULL) die("no memory for Dog");
        dog->bob  = NULL;
        dog->jack = NULL;
        dog->x = x;
        return dog;
    }
    
    Dog *copyConstructDog(Dog *other) {
        Dog *dog = newDog(0);
        *dog = *other;
        return dog;
    }
    
    int main()
    {
        Dog *dave = newDog(21);
        dave->bob = copyConstructDog(dave);

        printf("dave->x is %d, and dave->bob->x is %d", dave->x, dave->bob->x);

        return 0;
    }
