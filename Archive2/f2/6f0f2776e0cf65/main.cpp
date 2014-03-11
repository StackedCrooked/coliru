#include <stdio.h>

struct student{
    char name[50];
    int roll;
    float marks;
};

int main() {
    struct student s[10];
    int i;
    FILE *fp;
    fp = fopen("file.txt","w");

    //
    // Fill the array of students w/ data first
    //

    //fprintf(fp, "Enter information of students:\n");
    puts( "Enter information of students : " );
    for(i=0;i<10;++i)
    {
        s[i].roll=i+1;
        //fprintf(fp, "\nFor roll number %d\n",s[i].roll);
        printf( "\nFor roll number %d\n", s[ i ].roll );
        //fprintf(fp, "Enter name: ");
        printf("Enter name: " );
        //fscanf(fp, "%s",s[i].name);
        scanf( "%s", s[ i ].name );
        //fprintf(fp, "Enter marks: ");
        printf( "Enter marks : " );
        //fscanf(fp, "%f",&s[i].marks);
        scanf( "%f", &s[ i ].marks );
        //fprintf(fp, "\n");
        puts( "" );
    }
    
    //
    // Now write the array of students to file
    //

    //fprintf(fp, "Displaying information of students:\n\n");
    puts( "Displaying information of students:\n" );
    for(i=0;i<10;++i)
    {
        fprintf(fp, "\nInformation for roll number %d:\n",i+1);
        fprintf(fp, "Name: ");
        fputs(s[i].name, fp);
        fprintf(fp, " Marks: %.1f",s[i].marks);
    }
    
    fclose(fp);
    return 0;
}