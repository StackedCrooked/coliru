#define CONCAT2(a,b) a##b
#define CONCAT(a,b) CONCAT2(a,b)

#define VERSION XY123
#define PRODUCT CONCAT(MyApplication_,VERSION)

PRODUCT a;