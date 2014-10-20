%:include <stdlib.h>
%:include <stdio.h>
%:include <iso646.h>
 
int main(int argc, char** argv)
??<
    if (argc > 1 and argv<:1:> not_eq NULL)
    <%
       printf("Hello%s\n", argv<:1:>);
    %>
 
    return EXIT_SUCCESS;
??>