#define TOKENPASTE(x, y) x ## y
#define TOKENPASTE2(x, y) TOKENPASTE(x, y)      // concat
#define TOKENPASTE3(x, y) TOKENPASTE(x, y)    // concat-stringify (warnings)
const char* s = TOKENPASTE3(Hi, There);