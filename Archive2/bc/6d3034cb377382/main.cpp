//Note that macros never expand recursively.
//If REPEAT is expanded and doing the outer loop, the outer loop calling
//REPEAT(i, MACRO) will not expand REPEAT since it's already been expanded for the outer loop
//and what is left is REPEAT(1, MACRO) REPEAT(2, MACRO) REPEAT(3, MACRO).
//Thus, we need to determine whether a nesting level is in use before using it.

//CAT returns two tokens pasted together
//CAT(ab, cd) = abcd
#define CAT(x,y) CAT_(x,y)
#define CAT_(x,y) x##y

//IF returns t if cond is 1, or f if cond is false
//IF(1, ab, cd) = ab
//IF(0, ab, cd) = cd
#define IF(cond, t, f) CAT(IF_, cond)(t, f)
#define IF_0(t, f) f
#define IF_1(t, f) t

//NOTHING ignores all arguments
//NOTHING(ab, cd) = 
#define NOTHING(...)

//Main macro REPEAT expands to REPEAT1 or REPEAT2, depending on whether the first dimension is available
#define REPEAT CAT(REPEAT, MIN_AVAIL_DIM)

//MIN_AVAIL_DIM returns 2 if dimension one is in use, else 1
#define MIN_AVAIL_DIM IF(DIM_IN_USE(1), 2, 1)

//DIM_IN_USE returns 1 if the dimension is being used
//If called with 1 and dimension 1 is in use, it expands to DIM_IN_USE_REPEAT1(1, NO NOTHING), which is 1 below
//If called with 1 and dimension 1 is not in use, it expands to DIM_IN_USE_ REPEAT1(1, NO NOTHING)
//This expands to DIM_IN_USE_ REPEAT1_1(NO NOTHING) => DIM_IN_USE_ NO NOTHING(1) => DIM_IN_USE_NO
#define DIM_IN_USE(dim) CAT(DIM_IN_USE_, REPEAT##dim(1, NO NOTHING))
#define DIM_IN_USE_NO 0
#define DIM_IN_USE_REPEAT1(x, m) 1

//REPEAT1 is the first dimension of REPEAT
#define REPEAT1(x, m) REPEAT1_##x(m)

#define REPEAT1_1(m) m(1)
#define REPEAT1_2(m) REPEAT1_1(m) m(2)
#define REPEAT1_3(m) REPEAT1_2(m) m(3)

//REPEAT2 is the second dimension of REPEAT
#define REPEAT2(x, m) REPEAT2_##x(m)

#define REPEAT2_1(m) m(1)
#define REPEAT2_2(m) REPEAT2_1(m) m(2)
#define REPEAT2_3(m) REPEAT2_2(m) m(3)

//inner loop
#define MACRO(i) int x##i;

//each loop has an inner loop
#define LOOP(i) REPEAT(i, MACRO)

int main() {
    REPEAT(3, LOOP)
}