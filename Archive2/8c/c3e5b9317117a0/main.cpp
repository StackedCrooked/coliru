#include <cstdint>
#include <cstring>

struct MAC { unsigned char data[6]; };

// compare a 6-byte array
bool operator<(MAC lhs, MAC rhs)
{
    uint64_t a = 0;
    uint64_t b = 0;
    memcpy(&a, &lhs, sizeof(lhs));
    memcpy(&b, &rhs, sizeof(rhs));
    return a < b;
}


#if 0

// CLANG:
    movabs	rax, 281474976710655 // rax = 0x0000'FFFF'FFFF'FFFF
	and	rsi, rax
	and	rdi, rax
	cmp	rdi, rsi
	setb	al
	ret


// GCC:
	mov	QWORD PTR [rsp-16], 0
	mov	QWORD PTR [rsp-8], 0
	mov	DWORD PTR [rsp-16], edi
	mov	DWORD PTR [rsp-8], esi
	shr	rdi, 32
	shr	rsi, 32
	mov	WORD PTR [rsp-12], di
	mov	WORD PTR [rsp-4], si
	mov	rax, QWORD PTR [rsp-8]
	cmp	QWORD PTR [rsp-16], rax
	setb	al
	ret
    
#endif

