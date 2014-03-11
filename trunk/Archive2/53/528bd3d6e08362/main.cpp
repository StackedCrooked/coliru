// -*- Restaurant Management System -*-
// Concept

// every restaurant has a food.
// an order is composed of food

#define MAX_CHAR 32 // max characters of a name

// food structure
struct Food {
    unsigned price;        // price of food
    char name[ MAX_CHAR ]; // name of food
};

// drinks structure
struct Drink {
    unsigned price;
    char name[ MAX_CHAR ];
};

#define MAX_FOOD_PER_ORDER  5 // max food per order (adjust if neccessary)
#define MAX_DRINK_PER_ORDER 5 // max drink per order

struct Order {
    unsigned price;
    Food  order[ MAX_FOOD_PER_ORDER ];
    Drink drink[ MAX_DRINK_PER_ORDER ];
};

// and some functions
Food* read_list_of_foods_from_file( /* */ );
void  update_list_of_foods( /* */ );
void  takeOrder( /* */ );

// etc ...

int main() { /* */ }