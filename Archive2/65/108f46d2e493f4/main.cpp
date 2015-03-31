#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define container_of(ptr, type, member) (type *)((char *)(ptr) - offsetof(type, member))

#define MAX_ID_LENGTH 255

struct object_id {
    const char *str;
    size_t length;
};

struct object_id_data {
    char id[MAX_ID_LENGTH];
    struct object_id user_data;
};

struct object_id *new_object_id(int id)
{
    struct object_id_data *pdata = (struct object_id_data *)
        malloc(sizeof(struct object_id_data));
    if (!pdata)
        return NULL;
    
    int length = snprintf(pdata->id, sizeof(pdata->id), "%08x", id);
    
    pdata->user_data.str = pdata->id;
    pdata->user_data.length = (size_t) length;
    
    return &pdata->user_data;
}

void free_object_id(struct object_id *id)
{
    struct object_id_data *pdata = container_of(id, struct object_id_data, user_data);
    free(pdata);
}

int main(int argc, char* argv[])
{
    struct object_id *id = new_object_id(1337);
    printf("Object ID: %s\n", id->str);
    free_object_id(id);

    return 0;
}
