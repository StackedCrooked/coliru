#include <stdint.h>
typedef int8_t    i8;
typedef int16_t   i16;
typedef int32_t   i32;
typedef int64_t   i64;

typedef uint8_t   u8;
typedef uint16_t  u16;
typedef uint32_t  u32;
typedef uint64_t  u64;
typedef float  f32;
typedef double f64;

typedef struct {u32 s1, s2, s3;} taus88_t;

taus88_t make_taus88(u32 seed);
u32 taus88u32(taus88_t *t);
f32 taus88f32(taus88_t *t);

taus88_t make_taus88(u32 seed)
{
  taus88_t t;
  t.s1 = 1243598713U ^ seed; if (t.s1 <  2) t.s1 = 1243598713U;
  t.s2 = 3093459404U ^ seed; if (t.s2 <  8) t.s2 = 3093459404U;
  t.s3 = 1821928721U ^ seed; if (t.s3 < 16) t.s3 = 1821928721U;
  return t;
}

u32 taus88u32(taus88_t *t)
{
  t->s1 = ((t->s1 &  -2) << 12) ^ (((t->s1 << 13) ^  t->s1) >> 19);
  t->s2 = ((t->s2 &  -8) <<  4) ^ (((t->s2 <<  2) ^  t->s2) >> 25);
  t->s3 = ((t->s3 & -16) << 17) ^ (((t->s3 <<  3) ^  t->s3) >> 11);
  return t->s1 ^ t->s2 ^ t->s3;
}

f32 taus88f32(taus88_t *t)
{
  union {u32 i ; f32 f ;} u;
  u.i = 0x3F800000 | (taus88u32(t) >> 9);
  return u.f - 1.0;
}

int main()
{

    taus88_t* TAUS88 ;
    
    *TAUS88 = make_taus88(6346456);
    u32 numberu32 = taus88u32(TAUS88);
    f32 numberf32 = taus88f32(TAUS88);

    return 0;
}