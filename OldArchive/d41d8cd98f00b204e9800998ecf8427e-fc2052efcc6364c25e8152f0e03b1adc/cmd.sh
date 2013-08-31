echo -e "#include <stdio.h>\nint main(){printf( \"hello world\\\n\" ) ; return 0 ;}"  | gcc -xc - && ./a.out
