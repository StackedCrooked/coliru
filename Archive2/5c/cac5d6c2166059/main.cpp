extern int printf(char*,...),getchar(); int main() { printf("Enter a letter between A and Z :");
int i,j,letter=getchar(); for( i='A'; i<=letter; ++i ) { printf("\n"); for( j=0; j<(letter-i); ++j )
printf(" "); for( j='A'; j<i; ++j ) printf("%c",j); while( j>='A' ) printf("%c",j--); } }
