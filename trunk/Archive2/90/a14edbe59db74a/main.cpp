#include <stdio.h>
#include <string.h>

#define BUF_SIZE 512

typedef struct {
    const char* username;
	const char* password;
	const char* version;
} LoginData;

char stringified[BUF_SIZE];

void stringify(LoginData* data)
{
    memset(stringified, 0x00, BUF_SIZE);
    snprintf(stringified, BUF_SIZE, "['%s', '%s', '%s']", 
        data->username, data->password, data->version);
}

int main()
{
    LoginData d = {"Mark", "secret", "2.4.0"};
    stringify(&d);
    
    printf("%s\n", stringified);
}