#include <stdio.h>
#include <string.h>

char *reverse(char *x) {
     int len = strlen(x);
     char ans[len+1];
     int i;
     for (i = 0; i < len; i++) {
          ans[i] = x[len-i-1];
     }
     ans[i] = '\0';
     return ans;
}

int main() {
     char *a = reverse("hello");
     printf("%s\n", a);
}
