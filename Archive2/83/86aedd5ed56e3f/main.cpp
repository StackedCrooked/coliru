#include <stdio.h>
#include <string.h>
#define NAME_LENGTH 20

struct human {
    int age;
    char name[NAME_LENGTH];
};

void print_human(struct human h){
    printf("age %d | name address %p | name: %s\n",h.age, h.name, h.name);
}

void change_human(struct human h){
    strcpy(h.name, "Alice");    
    printf("age %d | name address %p | name: %s\n",h.age, h.name, h.name);
    print_human(h);
}

int main(void){
    struct human me = {22, "Bob"}, other = {0};
    printf("age %d | name address %p | name: %s\n",other.age, other.name, other.name);
    printf("age %d | name address %p | name: %s\n",me.age, me.name, me.name);
    strcpy(other.name, "Alice");    
    printf("age %d | name address %p | name: %s\n",other.age, other.name, other.name);
    printf("age %d | name address %p | name: %s\n",me.age, me.name, me.name);
    return 0;
}
