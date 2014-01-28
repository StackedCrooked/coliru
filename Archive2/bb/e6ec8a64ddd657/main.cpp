//#define LOGGER_UPDATE_DATA(bit,...) {  \
//  do { \
//    int i; \
//    int j = 0; \
//    int _args[] = {__VA_ARGS__};\
//    int *addr = (int *) LOGGER_ADDR ; \
//    for (i = 0; i < (sizeof(_args)/sizeof(_args[0])); i++) {\
//     *(int *) (LOGGER_DATA_ADDR - j) |= _args[i];\
//      j = j + 0x4; \
//    }\
//    *addr |= 1 << bit;\
//  }while (0); \
//}
