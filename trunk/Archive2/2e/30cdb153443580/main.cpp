#include <immintrin.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/time.h>
#include <sched.h>
#include <pthread.h>

#define VEC_LEN 256
#define VEC_NUM (1024 * 1024)

#define LOOP_TIME 1

typedef unsigned char BYTE;

static void thread_bind(int cpu)
{
    cpu_set_t cpu_set;
    CPU_ZERO(&cpu_set);
    CPU_SET(cpu, &cpu_set);
    if (pthread_setaffinity_np(pthread_self(),
            sizeof(cpu_set_t), &cpu_set) != 0)
    {
        fprintf(stderr, "Error: cpu[%d] bind failed.\n", cpu);
        exit(0);
    }
}

static inline double get_time(struct timeval *start, struct timeval *end)
{
    return end->tv_sec - start->tv_sec + (end->tv_usec - start->tv_usec) * 1e-6;
}

static unsigned char lt_128[16] __attribute__((aligned(16))) =
{
    0x0, 0x1, 0x1, 0x2, 0x1, 0x2, 0x2, 0x3, 0x1, 0x2, 0x2, 0x3, 0x2, 0x3, 0x3, 0x4
};

int hamming_dist_tune1(unsigned char *a, unsigned char *b, int len)
{
    int i;
    unsigned long *aa = (unsigned long *)a;
    unsigned long *bb = (unsigned long *)b;

    int u64len = len >> 3;
    int u64left = len & 0x7;

    long t1 = 0, t2 = 0, t3 = 0;
    for (i = 0; i <= u64len - 3; i += 3)
    {
        t1 += _mm_popcnt_u64(aa[0] ^ bb[0]);
        t2 += _mm_popcnt_u64(aa[1] ^ bb[1]);
        t3 += _mm_popcnt_u64(aa[2] ^ bb[2]);
        aa += 3;
        bb += 3;
    }
    if (i < u64len - 1)
    {
        t1 += _mm_popcnt_u64(aa[0] ^ bb[0]);
        t2 += _mm_popcnt_u64(aa[1] ^ bb[1]);
        aa += 2;
        bb += 2;
    }
    else if (i < u64len)
    {
        t1 += _mm_popcnt_u64(aa[0] ^ bb[0]);
        aa++;
        bb++;
    }
    a = (unsigned char*)aa;
    b = (unsigned char*)bb;
    for (i = 0; i < u64left; i++)
    {
        unsigned char tmp = a[i] ^ b[i];
        t1 += lt_128[tmp & 0xF];
        t2 += lt_128[tmp >> 4];
    }
    return (int)(t1 + t2 + t3);
}

int main()
{
    int j, k;
    struct timeval start, end;
    
    thread_bind(0);

    BYTE *a;
    BYTE *b;
    a = (BYTE*)malloc(VEC_NUM * VEC_LEN * sizeof(BYTE));
    for (j = 0; j < VEC_NUM; j++)
    {
        for (k = 0; k < VEC_LEN; k++)
        {
            a[j * VEC_LEN + k] = (BYTE)rand();
        }
    }
    b = (BYTE*)malloc(VEC_LEN * sizeof(BYTE));
    for (j = 0; j < VEC_LEN; j++)
    {
        b[j] = (BYTE)rand();
    }

    double time;
    int result;

    result = 0;
    gettimeofday(&start, NULL);
    for (k = 0; k < VEC_NUM; k++)
    {
        result += hamming_dist_tune1(a + k * VEC_LEN, b, VEC_LEN);
    }
    gettimeofday(&end, NULL);
    time = get_time(&start, &end);
    printf("Result = %d, time = %fs.\n", result, (float)time);

    return 0;
}
