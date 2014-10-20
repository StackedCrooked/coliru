typedef struct STRLIST{
    unsigned int size;
    char** list;
} STRLIST;

static STRLIST listMediaType = {
    .size = 7,
    .list = (char*[]){
        "Book",
        "Map",
        "Booklet",
        "Pamphlet",
        "Magazine",
        "Report",
        "Journal"
    },
};

int main() {}
