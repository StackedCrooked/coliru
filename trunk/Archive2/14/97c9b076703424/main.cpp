#include <fstream>
#include <stdlib.h>     /* atof */
#include <iostream>
#include <string.h>
#include <math.h>
#include <iomanip>
#include <cstring>

/* Definitions */
#define MAX_KO  5000
#define MAX_GN    2000

using namespace std;


int main()
{
    double m_ko_genome[MAX_KO][MAX_GN];
    

    ifstream f_in_genome_matrix;
    f_in_genome_matrix.open("input.txt");
    string f_line;
    
    int x=0; // The row of the matrix we are currently on
    int y=0; // The column.
    while(getline(f_in_genome_matrix, f_line))
    {
        y = 0;
        
        char *cstr = new char[f_line.length() + 1];
        strcpy(cstr, f_line.c_str()); // Aparrantly fixes the const char* problem.
        
        char *str_tok;
        str_tok = strtok(cstr, "\t");
        m_ko_genome[x][y] = atof(str_tok);
        while(str_tok != NULL)
        {
            y++;
            m_ko_genome[x][y] = atof(str_tok);
        }
        x++;
    }
    int i,j;
    
    for(i=0;i<=x;i++)
    {
        for(j=0;j<=y;j++)
        {
            cout << "a" << "\t";
        }
        cout << endl;
    }
    
    
    // READ
    
    f_in_genome_matrix.close();
    
    
    
    printf("Heyo!\n");
    
    return 0;
}
