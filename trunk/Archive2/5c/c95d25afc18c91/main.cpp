typedef struct STRLIST{
    unsigned int size;
    char** list;
} STRLIST;

static char* list[] = {
    "Book",
    "Map",
    "Booklet",
    "Pamphlet",
    "Magazine",
    "Report",
    "Journal"
};
static STRLIST listMediaType = {
    sizeof list / sizeof *list,
    list,
};

int main() {return 0;}
