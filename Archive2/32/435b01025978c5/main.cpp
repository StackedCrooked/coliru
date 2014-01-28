#include <cstdlib>
#include <cstdio>
#include <cstring>

int main(){
char api_id[] = "df499685-sdfsdf7-sdfsdf4-09sdf-89cd0f6dc81b";
char pwd[] ="ssdfsdfsdrt";
char login[]="34345334";

char str[]="";
strcpy (str,api_id);
strcat (str,pwd);
strcat (str,login);

printf ("str = %s\n",str);

char command[]="echo -e ";
 printf ("command = %s\n", command);
 strcat (command, str);
 printf ("command = %s\n", command);
 strcat (command, "|sha512sum|sed 's/-//'");
 printf ("command = %s\n", command);
}
