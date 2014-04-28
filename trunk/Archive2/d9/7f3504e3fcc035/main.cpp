char name1[] = "Mary"; char name2[] = "Gordon";

char temp = name1[0];

name1[0] = name2[0];

name2[0] = temp;

printf("name1 = %s\n", name1);

printf("name2 = %s\n", name2);