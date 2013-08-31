//C++ CODE:
int func(int i) {
  const char* pos = "HI";
  while ((pos[i] & 0x80) == 0) 
    ++i;
  return 1;
}

//ASSEMBLY PRODUCED BY G++ 4.6.4 -O3 -march=native

.LC0:
    .string	"HI"
func(int):
	movslq	%edi, %rdi
	cmpb	$0, .LC0(%rdi)
	js	.L2
	addq	$.LC0+1, %rdi
.L3:
	addq	$1, %rdi
	cmpb	$0, -1(%rdi)      //one opcode is probably 
	jns	.L3
.L2:
	movl	$1, %eax
	ret
