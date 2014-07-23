#include <stdio.h>

#define STR_IMPL(X) #X
#define STR(X) STR_IMPL(X)

#define GLOBAL_INT (3)

// I AM TRYING TO SAVE THE TEXTUAL MACRO CONTENT "GLOBAL_INT" (WITHOUT THE QUOTES)
//  IN ANOTHER MACRO SO THAT I CAN UNDEFINE GIM AND STILL REFER TO GLOBAL_INT

#define GIM (GLOBAL_INT)

#define GIM_SAVE (GIM)
#define GIM_SAVE_STR (STR(GIM))
#define STR_GIM_SAVE (STR(GIM_SAVE))
const char *strGimSave = STR(GIM_SAVE);
const char *gimSaveStr = GIM_SAVE_STR;
const char *strGimSaveM = STR_GIM_SAVE;
const char *gimStr = STR(GIM);

#undef GIM

int main(int argc, char *argv[])
{
    printf("strGimSave=%s\n", strGimSave);
    printf("gimSaveStr=%s\n", gimSaveStr);
    printf("strGimSaveM=%s\n", strGimSaveM);
    printf("gimStr=%s\n", gimStr);

    const char *gim_save = STR(GIM_SAVE);
    const char *gim_save_str = GIM_SAVE_STR;
    const char *str_gim_save = STR_GIM_SAVE;
    printf("\ngim_save=%s\n", gim_save);
    printf("gim_save_str=%s\n", gim_save_str);
    printf("str_gim_save=%s\n", str_gim_save);

    return 0;
}