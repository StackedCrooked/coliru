       
namespace std
{
  typedef long unsigned int size_t;
  typedef long int ptrdiff_t;
  typedef decltype(nullptr) nullptr_t;
}
typedef long unsigned int size_t;
extern "C" {
typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;
typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;
typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;
typedef long int __quad_t;
typedef unsigned long int __u_quad_t;
typedef unsigned long int __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long int __ino_t;
typedef unsigned long int __ino64_t;
typedef unsigned int __mode_t;
typedef unsigned long int __nlink_t;
typedef long int __off_t;
typedef long int __off64_t;
typedef int __pid_t;
typedef struct { int __val[2]; } __fsid_t;
typedef long int __clock_t;
typedef unsigned long int __rlim_t;
typedef unsigned long int __rlim64_t;
typedef unsigned int __id_t;
typedef long int __time_t;
typedef unsigned int __useconds_t;
typedef long int __suseconds_t;
typedef int __daddr_t;
typedef int __key_t;
typedef int __clockid_t;
typedef void * __timer_t;
typedef long int __blksize_t;
typedef long int __blkcnt_t;
typedef long int __blkcnt64_t;
typedef unsigned long int __fsblkcnt_t;
typedef unsigned long int __fsblkcnt64_t;
typedef unsigned long int __fsfilcnt_t;
typedef unsigned long int __fsfilcnt64_t;
typedef long int __fsword_t;
typedef long int __ssize_t;
typedef long int __syscall_slong_t;
typedef unsigned long int __syscall_ulong_t;
typedef __off64_t __loff_t;
typedef __quad_t *__qaddr_t;
typedef char *__caddr_t;
typedef long int __intptr_t;
typedef unsigned int __socklen_t;
static __inline unsigned int
__bswap_32 (unsigned int __bsx)
{
  return __builtin_bswap32 (__bsx);
}
static __inline __uint64_t
__bswap_64 (__uint64_t __bsx)
{
  return __builtin_bswap64 (__bsx);
}
union wait
  {
    int w_status;
    struct
      {
 unsigned int __w_termsig:7;
 unsigned int __w_coredump:1;
 unsigned int __w_retcode:8;
 unsigned int:16;
      } __wait_terminated;
    struct
      {
 unsigned int __w_stopval:8;
 unsigned int __w_stopsig:8;
 unsigned int:16;
      } __wait_stopped;
  };

typedef struct
  {
    int quot;
    int rem;
  } div_t;
typedef struct
  {
    long int quot;
    long int rem;
  } ldiv_t;


__extension__ typedef struct
  {
    long long int quot;
    long long int rem;
  } lldiv_t;

extern size_t __ctype_get_mb_cur_max (void) throw () ;

extern double atof (const char *__nptr)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;
extern int atoi (const char *__nptr)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;
extern long int atol (const char *__nptr)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;


__extension__ extern long long int atoll (const char *__nptr)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;


extern double strtod (const char *__restrict __nptr,
        char **__restrict __endptr)
     throw () __attribute__ ((__nonnull__ (1)));


extern float strtof (const char *__restrict __nptr,
       char **__restrict __endptr) throw () __attribute__ ((__nonnull__ (1)));
extern long double strtold (const char *__restrict __nptr,
       char **__restrict __endptr)
     throw () __attribute__ ((__nonnull__ (1)));


extern long int strtol (const char *__restrict __nptr,
   char **__restrict __endptr, int __base)
     throw () __attribute__ ((__nonnull__ (1)));
extern unsigned long int strtoul (const char *__restrict __nptr,
      char **__restrict __endptr, int __base)
     throw () __attribute__ ((__nonnull__ (1)));

__extension__
extern long long int strtoq (const char *__restrict __nptr,
        char **__restrict __endptr, int __base)
     throw () __attribute__ ((__nonnull__ (1)));
__extension__
extern unsigned long long int strtouq (const char *__restrict __nptr,
           char **__restrict __endptr, int __base)
     throw () __attribute__ ((__nonnull__ (1)));

__extension__
extern long long int strtoll (const char *__restrict __nptr,
         char **__restrict __endptr, int __base)
     throw () __attribute__ ((__nonnull__ (1)));
__extension__
extern unsigned long long int strtoull (const char *__restrict __nptr,
     char **__restrict __endptr, int __base)
     throw () __attribute__ ((__nonnull__ (1)));

typedef struct __locale_struct
{
  struct __locale_data *__locales[13];
  const unsigned short int *__ctype_b;
  const int *__ctype_tolower;
  const int *__ctype_toupper;
  const char *__names[13];
} *__locale_t;
typedef __locale_t locale_t;
extern long int strtol_l (const char *__restrict __nptr,
     char **__restrict __endptr, int __base,
     __locale_t __loc) throw () __attribute__ ((__nonnull__ (1, 4)));
extern unsigned long int strtoul_l (const char *__restrict __nptr,
        char **__restrict __endptr,
        int __base, __locale_t __loc)
     throw () __attribute__ ((__nonnull__ (1, 4)));
__extension__
extern long long int strtoll_l (const char *__restrict __nptr,
    char **__restrict __endptr, int __base,
    __locale_t __loc)
     throw () __attribute__ ((__nonnull__ (1, 4)));
__extension__
extern unsigned long long int strtoull_l (const char *__restrict __nptr,
       char **__restrict __endptr,
       int __base, __locale_t __loc)
     throw () __attribute__ ((__nonnull__ (1, 4)));
extern double strtod_l (const char *__restrict __nptr,
   char **__restrict __endptr, __locale_t __loc)
     throw () __attribute__ ((__nonnull__ (1, 3)));
extern float strtof_l (const char *__restrict __nptr,
         char **__restrict __endptr, __locale_t __loc)
     throw () __attribute__ ((__nonnull__ (1, 3)));
extern long double strtold_l (const char *__restrict __nptr,
         char **__restrict __endptr,
         __locale_t __loc)
     throw () __attribute__ ((__nonnull__ (1, 3)));
extern char *l64a (long int __n) throw () ;
extern long int a64l (const char *__s)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;
extern "C" {
typedef __u_char u_char;
typedef __u_short u_short;
typedef __u_int u_int;
typedef __u_long u_long;
typedef __quad_t quad_t;
typedef __u_quad_t u_quad_t;
typedef __fsid_t fsid_t;
typedef __loff_t loff_t;
typedef __ino_t ino_t;
typedef __ino64_t ino64_t;
typedef __dev_t dev_t;
typedef __gid_t gid_t;
typedef __mode_t mode_t;
typedef __nlink_t nlink_t;
typedef __uid_t uid_t;
typedef __off_t off_t;
typedef __off64_t off64_t;
typedef __pid_t pid_t;
typedef __id_t id_t;
typedef __ssize_t ssize_t;
typedef __daddr_t daddr_t;
typedef __caddr_t caddr_t;
typedef __key_t key_t;

typedef __clock_t clock_t;



typedef __time_t time_t;


typedef __clockid_t clockid_t;
typedef __timer_t timer_t;
typedef __useconds_t useconds_t;
typedef __suseconds_t suseconds_t;
typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;
typedef int int8_t __attribute__ ((__mode__ (__QI__)));
typedef int int16_t __attribute__ ((__mode__ (__HI__)));
typedef int int32_t __attribute__ ((__mode__ (__SI__)));
typedef int int64_t __attribute__ ((__mode__ (__DI__)));
typedef unsigned int u_int8_t __attribute__ ((__mode__ (__QI__)));
typedef unsigned int u_int16_t __attribute__ ((__mode__ (__HI__)));
typedef unsigned int u_int32_t __attribute__ ((__mode__ (__SI__)));
typedef unsigned int u_int64_t __attribute__ ((__mode__ (__DI__)));
typedef int register_t __attribute__ ((__mode__ (__word__)));
typedef int __sig_atomic_t;
typedef struct
  {
    unsigned long int __val[(1024 / (8 * sizeof (unsigned long int)))];
  } __sigset_t;
typedef __sigset_t sigset_t;
struct timespec
  {
    __time_t tv_sec;
    __syscall_slong_t tv_nsec;
  };
struct timeval
  {
    __time_t tv_sec;
    __suseconds_t tv_usec;
  };
typedef long int __fd_mask;
typedef struct
  {
    __fd_mask fds_bits[1024 / (8 * (int) sizeof (__fd_mask))];
  } fd_set;
typedef __fd_mask fd_mask;
extern "C" {
extern int select (int __nfds, fd_set *__restrict __readfds,
     fd_set *__restrict __writefds,
     fd_set *__restrict __exceptfds,
     struct timeval *__restrict __timeout);
extern int pselect (int __nfds, fd_set *__restrict __readfds,
      fd_set *__restrict __writefds,
      fd_set *__restrict __exceptfds,
      const struct timespec *__restrict __timeout,
      const __sigset_t *__restrict __sigmask);
}
extern "C" {
__extension__
extern unsigned int gnu_dev_major (unsigned long long int __dev)
     throw () __attribute__ ((__const__));
__extension__
extern unsigned int gnu_dev_minor (unsigned long long int __dev)
     throw () __attribute__ ((__const__));
__extension__
extern unsigned long long int gnu_dev_makedev (unsigned int __major,
            unsigned int __minor)
     throw () __attribute__ ((__const__));
}
typedef __blksize_t blksize_t;
typedef __blkcnt_t blkcnt_t;
typedef __fsblkcnt_t fsblkcnt_t;
typedef __fsfilcnt_t fsfilcnt_t;
typedef __blkcnt64_t blkcnt64_t;
typedef __fsblkcnt64_t fsblkcnt64_t;
typedef __fsfilcnt64_t fsfilcnt64_t;
typedef unsigned long int pthread_t;
union pthread_attr_t
{
  char __size[56];
  long int __align;
};
typedef union pthread_attr_t pthread_attr_t;
typedef struct __pthread_internal_list
{
  struct __pthread_internal_list *__prev;
  struct __pthread_internal_list *__next;
} __pthread_list_t;
typedef union
{
  struct __pthread_mutex_s
  {
    int __lock;
    unsigned int __count;
    int __owner;
    unsigned int __nusers;
    int __kind;
    short __spins;
    short __elision;
    __pthread_list_t __list;
  } __data;
  char __size[40];
  long int __align;
} pthread_mutex_t;
typedef union
{
  char __size[4];
  int __align;
} pthread_mutexattr_t;
typedef union
{
  struct
  {
    int __lock;
    unsigned int __futex;
    __extension__ unsigned long long int __total_seq;
    __extension__ unsigned long long int __wakeup_seq;
    __extension__ unsigned long long int __woken_seq;
    void *__mutex;
    unsigned int __nwaiters;
    unsigned int __broadcast_seq;
  } __data;
  char __size[48];
  __extension__ long long int __align;
} pthread_cond_t;
typedef union
{
  char __size[4];
  int __align;
} pthread_condattr_t;
typedef unsigned int pthread_key_t;
typedef int pthread_once_t;
typedef union
{
  struct
  {
    int __lock;
    unsigned int __nr_readers;
    unsigned int __readers_wakeup;
    unsigned int __writer_wakeup;
    unsigned int __nr_readers_queued;
    unsigned int __nr_writers_queued;
    int __writer;
    int __shared;
    signed char __rwelision;
    unsigned char __pad1[7];
    unsigned long int __pad2;
    unsigned int __flags;
  } __data;
  char __size[56];
  long int __align;
} pthread_rwlock_t;
typedef union
{
  char __size[8];
  long int __align;
} pthread_rwlockattr_t;
typedef volatile int pthread_spinlock_t;
typedef union
{
  char __size[32];
  long int __align;
} pthread_barrier_t;
typedef union
{
  char __size[4];
  int __align;
} pthread_barrierattr_t;
}
extern long int random (void) throw ();
extern void srandom (unsigned int __seed) throw ();
extern char *initstate (unsigned int __seed, char *__statebuf,
   size_t __statelen) throw () __attribute__ ((__nonnull__ (2)));
extern char *setstate (char *__statebuf) throw () __attribute__ ((__nonnull__ (1)));
struct random_data
  {
    int32_t *fptr;
    int32_t *rptr;
    int32_t *state;
    int rand_type;
    int rand_deg;
    int rand_sep;
    int32_t *end_ptr;
  };
extern int random_r (struct random_data *__restrict __buf,
       int32_t *__restrict __result) throw () __attribute__ ((__nonnull__ (1, 2)));
extern int srandom_r (unsigned int __seed, struct random_data *__buf)
     throw () __attribute__ ((__nonnull__ (2)));
extern int initstate_r (unsigned int __seed, char *__restrict __statebuf,
   size_t __statelen,
   struct random_data *__restrict __buf)
     throw () __attribute__ ((__nonnull__ (2, 4)));
extern int setstate_r (char *__restrict __statebuf,
         struct random_data *__restrict __buf)
     throw () __attribute__ ((__nonnull__ (1, 2)));

extern int rand (void) throw ();
extern void srand (unsigned int __seed) throw ();

extern int rand_r (unsigned int *__seed) throw ();
extern double drand48 (void) throw ();
extern double erand48 (unsigned short int __xsubi[3]) throw () __attribute__ ((__nonnull__ (1)));
extern long int lrand48 (void) throw ();
extern long int nrand48 (unsigned short int __xsubi[3])
     throw () __attribute__ ((__nonnull__ (1)));
extern long int mrand48 (void) throw ();
extern long int jrand48 (unsigned short int __xsubi[3])
     throw () __attribute__ ((__nonnull__ (1)));
extern void srand48 (long int __seedval) throw ();
extern unsigned short int *seed48 (unsigned short int __seed16v[3])
     throw () __attribute__ ((__nonnull__ (1)));
extern void lcong48 (unsigned short int __param[7]) throw () __attribute__ ((__nonnull__ (1)));
struct drand48_data
  {
    unsigned short int __x[3];
    unsigned short int __old_x[3];
    unsigned short int __c;
    unsigned short int __init;
    __extension__ unsigned long long int __a;
  };
extern int drand48_r (struct drand48_data *__restrict __buffer,
        double *__restrict __result) throw () __attribute__ ((__nonnull__ (1, 2)));
extern int erand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        double *__restrict __result) throw () __attribute__ ((__nonnull__ (1, 2)));
extern int lrand48_r (struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern int nrand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern int mrand48_r (struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern int jrand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern int srand48_r (long int __seedval, struct drand48_data *__buffer)
     throw () __attribute__ ((__nonnull__ (2)));
extern int seed48_r (unsigned short int __seed16v[3],
       struct drand48_data *__buffer) throw () __attribute__ ((__nonnull__ (1, 2)));
extern int lcong48_r (unsigned short int __param[7],
        struct drand48_data *__buffer)
     throw () __attribute__ ((__nonnull__ (1, 2)));

extern void *malloc (size_t __size) throw () __attribute__ ((__malloc__)) ;
extern void *calloc (size_t __nmemb, size_t __size)
     throw () __attribute__ ((__malloc__)) ;


extern void *realloc (void *__ptr, size_t __size)
     throw () __attribute__ ((__warn_unused_result__));
extern void free (void *__ptr) throw ();

extern void cfree (void *__ptr) throw ();
extern "C" {
extern void *alloca (size_t __size) throw ();
}
extern void *valloc (size_t __size) throw () __attribute__ ((__malloc__)) ;
extern int posix_memalign (void **__memptr, size_t __alignment, size_t __size)
     throw () __attribute__ ((__nonnull__ (1))) ;
extern void *aligned_alloc (size_t __alignment, size_t __size)
     throw () __attribute__ ((__malloc__)) __attribute__ ((__alloc_size__ (2))) ;

extern void abort (void) throw () __attribute__ ((__noreturn__));
extern int atexit (void (*__func) (void)) throw () __attribute__ ((__nonnull__ (1)));
extern "C++" int at_quick_exit (void (*__func) (void))
     throw () __asm ("at_quick_exit") __attribute__ ((__nonnull__ (1)));

extern int on_exit (void (*__func) (int __status, void *__arg), void *__arg)
     throw () __attribute__ ((__nonnull__ (1)));

extern void exit (int __status) throw () __attribute__ ((__noreturn__));
extern void quick_exit (int __status) throw () __attribute__ ((__noreturn__));


extern void _Exit (int __status) throw () __attribute__ ((__noreturn__));


extern char *getenv (const char *__name) throw () __attribute__ ((__nonnull__ (1))) ;

extern char *secure_getenv (const char *__name)
     throw () __attribute__ ((__nonnull__ (1))) ;
extern int putenv (char *__string) throw () __attribute__ ((__nonnull__ (1)));
extern int setenv (const char *__name, const char *__value, int __replace)
     throw () __attribute__ ((__nonnull__ (2)));
extern int unsetenv (const char *__name) throw () __attribute__ ((__nonnull__ (1)));
extern int clearenv (void) throw ();
extern char *mktemp (char *__template) throw () __attribute__ ((__nonnull__ (1)));
extern int mkstemp (char *__template) __attribute__ ((__nonnull__ (1))) ;
extern int mkstemp64 (char *__template) __attribute__ ((__nonnull__ (1))) ;
extern int mkstemps (char *__template, int __suffixlen) __attribute__ ((__nonnull__ (1))) ;
extern int mkstemps64 (char *__template, int __suffixlen)
     __attribute__ ((__nonnull__ (1))) ;
extern char *mkdtemp (char *__template) throw () __attribute__ ((__nonnull__ (1))) ;
extern int mkostemp (char *__template, int __flags) __attribute__ ((__nonnull__ (1))) ;
extern int mkostemp64 (char *__template, int __flags) __attribute__ ((__nonnull__ (1))) ;
extern int mkostemps (char *__template, int __suffixlen, int __flags)
     __attribute__ ((__nonnull__ (1))) ;
extern int mkostemps64 (char *__template, int __suffixlen, int __flags)
     __attribute__ ((__nonnull__ (1))) ;

extern int system (const char *__command) ;

extern char *canonicalize_file_name (const char *__name)
     throw () __attribute__ ((__nonnull__ (1))) ;
extern char *realpath (const char *__restrict __name,
         char *__restrict __resolved) throw () ;
typedef int (*__compar_fn_t) (const void *, const void *);
typedef __compar_fn_t comparison_fn_t;
typedef int (*__compar_d_fn_t) (const void *, const void *, void *);

extern void *bsearch (const void *__key, const void *__base,
        size_t __nmemb, size_t __size, __compar_fn_t __compar)
     __attribute__ ((__nonnull__ (1, 2, 5))) ;
extern void qsort (void *__base, size_t __nmemb, size_t __size,
     __compar_fn_t __compar) __attribute__ ((__nonnull__ (1, 4)));
extern void qsort_r (void *__base, size_t __nmemb, size_t __size,
       __compar_d_fn_t __compar, void *__arg)
  __attribute__ ((__nonnull__ (1, 4)));
extern int abs (int __x) throw () __attribute__ ((__const__)) ;
extern long int labs (long int __x) throw () __attribute__ ((__const__)) ;

__extension__ extern long long int llabs (long long int __x)
     throw () __attribute__ ((__const__)) ;

extern div_t div (int __numer, int __denom)
     throw () __attribute__ ((__const__)) ;
extern ldiv_t ldiv (long int __numer, long int __denom)
     throw () __attribute__ ((__const__)) ;


__extension__ extern lldiv_t lldiv (long long int __numer,
        long long int __denom)
     throw () __attribute__ ((__const__)) ;

extern char *ecvt (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign) throw () __attribute__ ((__nonnull__ (3, 4))) ;
extern char *fcvt (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign) throw () __attribute__ ((__nonnull__ (3, 4))) ;
extern char *gcvt (double __value, int __ndigit, char *__buf)
     throw () __attribute__ ((__nonnull__ (3))) ;
extern char *qecvt (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign)
     throw () __attribute__ ((__nonnull__ (3, 4))) ;
extern char *qfcvt (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign)
     throw () __attribute__ ((__nonnull__ (3, 4))) ;
extern char *qgcvt (long double __value, int __ndigit, char *__buf)
     throw () __attribute__ ((__nonnull__ (3))) ;
extern int ecvt_r (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign, char *__restrict __buf,
     size_t __len) throw () __attribute__ ((__nonnull__ (3, 4, 5)));
extern int fcvt_r (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign, char *__restrict __buf,
     size_t __len) throw () __attribute__ ((__nonnull__ (3, 4, 5)));
extern int qecvt_r (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign,
      char *__restrict __buf, size_t __len)
     throw () __attribute__ ((__nonnull__ (3, 4, 5)));
extern int qfcvt_r (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign,
      char *__restrict __buf, size_t __len)
     throw () __attribute__ ((__nonnull__ (3, 4, 5)));

extern int mblen (const char *__s, size_t __n) throw ();
extern int mbtowc (wchar_t *__restrict __pwc,
     const char *__restrict __s, size_t __n) throw ();
extern int wctomb (char *__s, wchar_t __wchar) throw ();
extern size_t mbstowcs (wchar_t *__restrict __pwcs,
   const char *__restrict __s, size_t __n) throw ();
extern size_t wcstombs (char *__restrict __s,
   const wchar_t *__restrict __pwcs, size_t __n)
     throw ();

extern int rpmatch (const char *__response) throw () __attribute__ ((__nonnull__ (1))) ;
extern int getsubopt (char **__restrict __optionp,
        char *const *__restrict __tokens,
        char **__restrict __valuep)
     throw () __attribute__ ((__nonnull__ (1, 2, 3))) ;
extern void setkey (const char *__key) throw () __attribute__ ((__nonnull__ (1)));
extern int posix_openpt (int __oflag) ;
extern int grantpt (int __fd) throw ();
extern int unlockpt (int __fd) throw ();
extern char *ptsname (int __fd) throw () ;
extern int ptsname_r (int __fd, char *__buf, size_t __buflen)
     throw () __attribute__ ((__nonnull__ (2)));
extern int getpt (void);
extern int getloadavg (double __loadavg[], int __nelem)
     throw () __attribute__ ((__nonnull__ (1)));
}
namespace std __attribute__ ((__visibility__ ("default")))
{

  using ::div_t;
  using ::ldiv_t;
  using ::abort;
  using ::abs;
  using ::atexit;
  using ::at_quick_exit;
  using ::atof;
  using ::atoi;
  using ::atol;
  using ::bsearch;
  using ::calloc;
  using ::div;
  using ::exit;
  using ::free;
  using ::getenv;
  using ::labs;
  using ::ldiv;
  using ::malloc;
  using ::mblen;
  using ::mbstowcs;
  using ::mbtowc;
  using ::qsort;
  using ::quick_exit;
  using ::rand;
  using ::realloc;
  using ::srand;
  using ::strtod;
  using ::strtol;
  using ::strtoul;
  using ::system;
  using ::wcstombs;
  using ::wctomb;
  inline long
  abs(long __i) { return __builtin_labs(__i); }
  inline ldiv_t
  div(long __i, long __j) { return ldiv(__i, __j); }
  inline long long
  abs(long long __x) { return __builtin_llabs (__x); }

}
namespace __gnu_cxx __attribute__ ((__visibility__ ("default")))
{

  using ::lldiv_t;
  using ::_Exit;
  using ::llabs;
  inline lldiv_t
  div(long long __n, long long __d)
  { lldiv_t __q; __q.quot = __n / __d; __q.rem = __n % __d; return __q; }
  using ::lldiv;
  using ::atoll;
  using ::strtoll;
  using ::strtoull;
  using ::strtof;
  using ::strtold;

}
namespace std
{
  using ::__gnu_cxx::lldiv_t;
  using ::__gnu_cxx::_Exit;
  using ::__gnu_cxx::llabs;
  using ::__gnu_cxx::div;
  using ::__gnu_cxx::lldiv;
  using ::__gnu_cxx::atoll;
  using ::__gnu_cxx::strtof;
  using ::__gnu_cxx::strtoll;
  using ::__gnu_cxx::strtoull;
  using ::__gnu_cxx::strtold;
}
       
extern "C" {

extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
       size_t __n) throw () __attribute__ ((__nonnull__ (1, 2)));
extern void *memmove (void *__dest, const void *__src, size_t __n)
     throw () __attribute__ ((__nonnull__ (1, 2)));

extern void *memccpy (void *__restrict __dest, const void *__restrict __src,
        int __c, size_t __n)
     throw () __attribute__ ((__nonnull__ (1, 2)));

extern void *memset (void *__s, int __c, size_t __n) throw () __attribute__ ((__nonnull__ (1)));
extern int memcmp (const void *__s1, const void *__s2, size_t __n)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern "C++"
{
extern void *memchr (void *__s, int __c, size_t __n)
      throw () __asm ("memchr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern const void *memchr (const void *__s, int __c, size_t __n)
      throw () __asm ("memchr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
}

extern "C++" void *rawmemchr (void *__s, int __c)
     throw () __asm ("rawmemchr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern "C++" const void *rawmemchr (const void *__s, int __c)
     throw () __asm ("rawmemchr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern "C++" void *memrchr (void *__s, int __c, size_t __n)
      throw () __asm ("memrchr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern "C++" const void *memrchr (const void *__s, int __c, size_t __n)
      throw () __asm ("memrchr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));

extern char *strcpy (char *__restrict __dest, const char *__restrict __src)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern char *strncpy (char *__restrict __dest,
        const char *__restrict __src, size_t __n)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern char *strcat (char *__restrict __dest, const char *__restrict __src)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern char *strncat (char *__restrict __dest, const char *__restrict __src,
        size_t __n) throw () __attribute__ ((__nonnull__ (1, 2)));
extern int strcmp (const char *__s1, const char *__s2)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern int strncmp (const char *__s1, const char *__s2, size_t __n)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern int strcoll (const char *__s1, const char *__s2)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern size_t strxfrm (char *__restrict __dest,
         const char *__restrict __src, size_t __n)
     throw () __attribute__ ((__nonnull__ (2)));

extern int strcoll_l (const char *__s1, const char *__s2, __locale_t __l)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 3)));
extern size_t strxfrm_l (char *__dest, const char *__src, size_t __n,
    __locale_t __l) throw () __attribute__ ((__nonnull__ (2, 4)));
extern char *strdup (const char *__s)
     throw () __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));
extern char *strndup (const char *__string, size_t __n)
     throw () __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));

extern "C++"
{
extern char *strchr (char *__s, int __c)
     throw () __asm ("strchr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern const char *strchr (const char *__s, int __c)
     throw () __asm ("strchr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
}
extern "C++"
{
extern char *strrchr (char *__s, int __c)
     throw () __asm ("strrchr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern const char *strrchr (const char *__s, int __c)
     throw () __asm ("strrchr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
}

extern "C++" char *strchrnul (char *__s, int __c)
     throw () __asm ("strchrnul") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern "C++" const char *strchrnul (const char *__s, int __c)
     throw () __asm ("strchrnul") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));

extern size_t strcspn (const char *__s, const char *__reject)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern size_t strspn (const char *__s, const char *__accept)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern "C++"
{
extern char *strpbrk (char *__s, const char *__accept)
     throw () __asm ("strpbrk") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern const char *strpbrk (const char *__s, const char *__accept)
     throw () __asm ("strpbrk") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
}
extern "C++"
{
extern char *strstr (char *__haystack, const char *__needle)
     throw () __asm ("strstr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern const char *strstr (const char *__haystack, const char *__needle)
     throw () __asm ("strstr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
}
extern char *strtok (char *__restrict __s, const char *__restrict __delim)
     throw () __attribute__ ((__nonnull__ (2)));

extern char *__strtok_r (char *__restrict __s,
    const char *__restrict __delim,
    char **__restrict __save_ptr)
     throw () __attribute__ ((__nonnull__ (2, 3)));
extern char *strtok_r (char *__restrict __s, const char *__restrict __delim,
         char **__restrict __save_ptr)
     throw () __attribute__ ((__nonnull__ (2, 3)));
extern "C++" char *strcasestr (char *__haystack, const char *__needle)
     throw () __asm ("strcasestr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern "C++" const char *strcasestr (const char *__haystack,
         const char *__needle)
     throw () __asm ("strcasestr") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern void *memmem (const void *__haystack, size_t __haystacklen,
       const void *__needle, size_t __needlelen)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 3)));
extern void *__mempcpy (void *__restrict __dest,
   const void *__restrict __src, size_t __n)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern void *mempcpy (void *__restrict __dest,
        const void *__restrict __src, size_t __n)
     throw () __attribute__ ((__nonnull__ (1, 2)));

extern size_t strlen (const char *__s)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));

extern size_t strnlen (const char *__string, size_t __maxlen)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));

extern char *strerror (int __errnum) throw ();

extern char *strerror_r (int __errnum, char *__buf, size_t __buflen)
     throw () __attribute__ ((__nonnull__ (2))) ;
extern char *strerror_l (int __errnum, __locale_t __l) throw ();
extern void __bzero (void *__s, size_t __n) throw () __attribute__ ((__nonnull__ (1)));
extern void bcopy (const void *__src, void *__dest, size_t __n)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern void bzero (void *__s, size_t __n) throw () __attribute__ ((__nonnull__ (1)));
extern int bcmp (const void *__s1, const void *__s2, size_t __n)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern "C++"
{
extern char *index (char *__s, int __c)
     throw () __asm ("index") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern const char *index (const char *__s, int __c)
     throw () __asm ("index") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
}
extern "C++"
{
extern char *rindex (char *__s, int __c)
     throw () __asm ("rindex") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern const char *rindex (const char *__s, int __c)
     throw () __asm ("rindex") __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
}
extern int ffs (int __i) throw () __attribute__ ((__const__));
extern int ffsl (long int __l) throw () __attribute__ ((__const__));
__extension__ extern int ffsll (long long int __ll)
     throw () __attribute__ ((__const__));
extern int strcasecmp (const char *__s1, const char *__s2)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern int strncasecmp (const char *__s1, const char *__s2, size_t __n)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern int strcasecmp_l (const char *__s1, const char *__s2,
    __locale_t __loc)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 3)));
extern int strncasecmp_l (const char *__s1, const char *__s2,
     size_t __n, __locale_t __loc)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 4)));
extern char *strsep (char **__restrict __stringp,
       const char *__restrict __delim)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern char *strsignal (int __sig) throw ();
extern char *__stpcpy (char *__restrict __dest, const char *__restrict __src)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern char *stpcpy (char *__restrict __dest, const char *__restrict __src)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern char *__stpncpy (char *__restrict __dest,
   const char *__restrict __src, size_t __n)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern char *stpncpy (char *__restrict __dest,
        const char *__restrict __src, size_t __n)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern int strverscmp (const char *__s1, const char *__s2)
     throw () __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strfry (char *__string) throw () __attribute__ ((__nonnull__ (1)));
extern void *memfrob (void *__s, size_t __n) throw () __attribute__ ((__nonnull__ (1)));
extern "C++" char *basename (char *__filename)
     throw () __asm ("basename") __attribute__ ((__nonnull__ (1)));
extern "C++" const char *basename (const char *__filename)
     throw () __asm ("basename") __attribute__ ((__nonnull__ (1)));
}
namespace std __attribute__ ((__visibility__ ("default")))
{

  using ::memchr;
  using ::memcmp;
  using ::memcpy;
  using ::memmove;
  using ::memset;
  using ::strcat;
  using ::strcmp;
  using ::strcoll;
  using ::strcpy;
  using ::strcspn;
  using ::strerror;
  using ::strlen;
  using ::strncat;
  using ::strncmp;
  using ::strncpy;
  using ::strspn;
  using ::strtok;
  using ::strxfrm;
  using ::strchr;
  using ::strpbrk;
  using ::strrchr;
  using ::strstr;

}
typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long int uint64_t;
typedef signed char int_least8_t;
typedef short int int_least16_t;
typedef int int_least32_t;
typedef long int int_least64_t;
typedef unsigned char uint_least8_t;
typedef unsigned short int uint_least16_t;
typedef unsigned int uint_least32_t;
typedef unsigned long int uint_least64_t;
typedef signed char int_fast8_t;
typedef long int int_fast16_t;
typedef long int int_fast32_t;
typedef long int int_fast64_t;
typedef unsigned char uint_fast8_t;
typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long int uint_fast64_t;
typedef long int intptr_t;
typedef unsigned long int uintptr_t;
typedef long int intmax_t;
typedef unsigned long int uintmax_t;
extern "C" {
typedef struct
  {
    long int quot;
    long int rem;
  } imaxdiv_t;
extern intmax_t imaxabs (intmax_t __n) throw () __attribute__ ((__const__));
extern imaxdiv_t imaxdiv (intmax_t __numer, intmax_t __denom)
      throw () __attribute__ ((__const__));
extern intmax_t strtoimax (const char *__restrict __nptr,
      char **__restrict __endptr, int __base) throw ();
extern uintmax_t strtoumax (const char *__restrict __nptr,
       char ** __restrict __endptr, int __base) throw ();
extern intmax_t wcstoimax (const wchar_t *__restrict __nptr,
      wchar_t **__restrict __endptr, int __base)
     throw ();
extern uintmax_t wcstoumax (const wchar_t *__restrict __nptr,
       wchar_t ** __restrict __endptr, int __base)
     throw ();
}
namespace rapidjson {
typedef unsigned SizeType;
}
namespace rapidjson {
using std::size_t;
}
       
extern "C" {
extern void __assert_fail (const char *__assertion, const char *__file,
      unsigned int __line, const char *__function)
     throw () __attribute__ ((__noreturn__));
extern void __assert_perror_fail (int __errnum, const char *__file,
      unsigned int __line, const char *__function)
     throw () __attribute__ ((__noreturn__));
extern void __assert (const char *__assertion, const char *__file, int __line)
     throw () __attribute__ ((__noreturn__));
}
namespace rapidjson {
template <bool x> struct STATIC_ASSERTION_FAILURE;
template <> struct STATIC_ASSERTION_FAILURE<true> { enum { value = 1 }; };
template<int x> struct StaticAssertTest {};
}
namespace rapidjson {
class CrtAllocator {
public:
    static const bool kNeedFree = true;
    void* Malloc(size_t size) { return std::malloc(size); }
    void* Realloc(void* originalPtr, size_t originalSize, size_t newSize) { (void)originalSize; return std::realloc(originalPtr, newSize); }
    static void Free(void *ptr) { std::free(ptr); }
};
template <typename BaseAllocator = CrtAllocator>
class MemoryPoolAllocator {
public:
    static const bool kNeedFree = false;
    MemoryPoolAllocator(size_t chunkSize = kDefaultChunkCapacity, BaseAllocator* baseAllocator = 0) :
        chunkHead_(0), chunk_capacity_(chunkSize), userBuffer_(0), baseAllocator_(baseAllocator), ownBaseAllocator_(0)
    {
    }
    MemoryPoolAllocator(void *buffer, size_t size, size_t chunkSize = kDefaultChunkCapacity, BaseAllocator* baseAllocator = 0) :
        chunkHead_(0), chunk_capacity_(chunkSize), userBuffer_(buffer), baseAllocator_(baseAllocator), ownBaseAllocator_(0)
    {
        ((buffer != 0) ? static_cast<void> (0) : __assert_fail ("buffer != 0", "aapt/rapidjson/allocators.h", 122, __PRETTY_FUNCTION__));
        ((size > sizeof(ChunkHeader)) ? static_cast<void> (0) : __assert_fail ("size > sizeof(ChunkHeader)", "aapt/rapidjson/allocators.h", 123, __PRETTY_FUNCTION__));
        chunkHead_ = reinterpret_cast<ChunkHeader*>(buffer);
        chunkHead_->capacity = size - sizeof(ChunkHeader);
        chunkHead_->size = 0;
        chunkHead_->next = 0;
    }
    ~MemoryPoolAllocator() {
        Clear();
        delete ownBaseAllocator_;
    }
    void Clear() {
        while(chunkHead_ != 0 && chunkHead_ != userBuffer_) {
            ChunkHeader* next = chunkHead_->next;
            baseAllocator_->Free(chunkHead_);
            chunkHead_ = next;
        }
    }
    size_t Capacity() const {
        size_t capacity = 0;
        for (ChunkHeader* c = chunkHead_; c != 0; c = c->next)
            capacity += c->capacity;
        return capacity;
    }
    size_t Size() const {
        size_t size = 0;
        for (ChunkHeader* c = chunkHead_; c != 0; c = c->next)
            size += c->size;
        return size;
    }
    void* Malloc(size_t size) {
        size = ((size + 3u) & ~3u);
        if (chunkHead_ == 0 || chunkHead_->size + size > chunkHead_->capacity)
            AddChunk(chunk_capacity_ > size ? chunk_capacity_ : size);
        void *buffer = reinterpret_cast<char *>(chunkHead_ + 1) + chunkHead_->size;
        chunkHead_->size += size;
        return buffer;
    }
    void* Realloc(void* originalPtr, size_t originalSize, size_t newSize) {
        if (originalPtr == 0)
            return Malloc(newSize);
        if (originalSize >= newSize)
            return originalPtr;
        if (originalPtr == (char *)(chunkHead_ + 1) + chunkHead_->size - originalSize) {
            size_t increment = static_cast<size_t>(newSize - originalSize);
            increment = ((increment + 3u) & ~3u);
            if (chunkHead_->size + increment <= chunkHead_->capacity) {
                chunkHead_->size += increment;
                return originalPtr;
            }
        }
        void* newBuffer = Malloc(newSize);
        ((newBuffer != 0) ? static_cast<void> (0) : __assert_fail ("newBuffer != 0", "aapt/rapidjson/allocators.h", 199, __PRETTY_FUNCTION__));
        return std::memcpy(newBuffer, originalPtr, originalSize);
    }
    static void Free(void *ptr) { (void)ptr; }
private:
    MemoryPoolAllocator(const MemoryPoolAllocator& rhs) ;
    MemoryPoolAllocator& operator=(const MemoryPoolAllocator& rhs) ;
    void AddChunk(size_t capacity) {
        if (!baseAllocator_)
            ownBaseAllocator_ = baseAllocator_ = new BaseAllocator();
        ChunkHeader* chunk = reinterpret_cast<ChunkHeader*>(baseAllocator_->Malloc(sizeof(ChunkHeader) + capacity));
        chunk->capacity = capacity;
        chunk->size = 0;
        chunk->next = chunkHead_;
        chunkHead_ = chunk;
    }
    static const int kDefaultChunkCapacity = 64 * 1024;
    struct ChunkHeader {
        size_t capacity;
        size_t size;
        ChunkHeader *next;
    };
    ChunkHeader *chunkHead_;
    size_t chunk_capacity_;
    void *userBuffer_;
    BaseAllocator* baseAllocator_;
    BaseAllocator* ownBaseAllocator_;
};
}

#pragma GCC diagnostic push


#pragma GCC diagnostic ignored "-Weffc++"

namespace rapidjson {
template<typename CharType = char>
struct UTF8 {
    typedef CharType Ch;
    enum { supportUnicode = 1 };
    template<typename OutputStream>
    static void Encode(OutputStream& os, unsigned codepoint) {
        if (codepoint <= 0x7F)
            os.Put(static_cast<Ch>(codepoint & 0xFF));
        else if (codepoint <= 0x7FF) {
            os.Put(static_cast<Ch>(0xC0 | ((codepoint >> 6) & 0xFF)));
            os.Put(static_cast<Ch>(0x80 | ((codepoint & 0x3F))));
        }
        else if (codepoint <= 0xFFFF) {
            os.Put(static_cast<Ch>(0xE0 | ((codepoint >> 12) & 0xFF)));
            os.Put(static_cast<Ch>(0x80 | ((codepoint >> 6) & 0x3F)));
            os.Put(static_cast<Ch>(0x80 | (codepoint & 0x3F)));
        }
        else {
            ((codepoint <= 0x10FFFF) ? static_cast<void> (0) : __assert_fail ("codepoint <= 0x10FFFF", "aapt/rapidjson/encodings.h", 120, __PRETTY_FUNCTION__));
            os.Put(static_cast<Ch>(0xF0 | ((codepoint >> 18) & 0xFF)));
            os.Put(static_cast<Ch>(0x80 | ((codepoint >> 12) & 0x3F)));
            os.Put(static_cast<Ch>(0x80 | ((codepoint >> 6) & 0x3F)));
            os.Put(static_cast<Ch>(0x80 | (codepoint & 0x3F)));
        }
    }
    template <typename InputStream>
    static bool Decode(InputStream& is, unsigned* codepoint) {
        Ch c = is.Take();
        if (!(c & 0x80)) {
            *codepoint = (unsigned char)c;
            return true;
        }
        unsigned char type = GetRange((unsigned char)c);
        *codepoint = (0xFF >> type) & (unsigned char)c;
        bool result = true;
        switch (type) {
        case 2: c = is.Take(); *codepoint = (*codepoint << 6) | ((unsigned char)c & 0x3Fu); result &= ((GetRange((unsigned char)c) & 0x70) != 0); return result;
        case 3: c = is.Take(); *codepoint = (*codepoint << 6) | ((unsigned char)c & 0x3Fu); result &= ((GetRange((unsigned char)c) & 0x70) != 0); c = is.Take(); *codepoint = (*codepoint << 6) | ((unsigned char)c & 0x3Fu); result &= ((GetRange((unsigned char)c) & 0x70) != 0); return result;
        case 4: c = is.Take(); *codepoint = (*codepoint << 6) | ((unsigned char)c & 0x3Fu); result &= ((GetRange((unsigned char)c) & 0x50) != 0); c = is.Take(); *codepoint = (*codepoint << 6) | ((unsigned char)c & 0x3Fu); result &= ((GetRange((unsigned char)c) & 0x70) != 0); return result;
        case 5: c = is.Take(); *codepoint = (*codepoint << 6) | ((unsigned char)c & 0x3Fu); result &= ((GetRange((unsigned char)c) & 0x10) != 0); c = is.Take(); *codepoint = (*codepoint << 6) | ((unsigned char)c & 0x3Fu); result &= ((GetRange((unsigned char)c) & 0x70) != 0); c = is.Take(); *codepoint = (*codepoint << 6) | ((unsigned char)c & 0x3Fu); result &= ((GetRange((unsigned char)c) & 0x70) != 0); return result;
        case 6: c = is.Take(); *codepoint = (*codepoint << 6) | ((unsigned char)c & 0x3Fu); result &= ((GetRange((unsigned char)c) & 0x70) != 0); c = is.Take(); *codepoint = (*codepoint << 6) | ((unsigned char)c & 0x3Fu); result &= ((GetRange((unsigned char)c) & 0x70) != 0); c = is.Take(); *codepoint = (*codepoint << 6) | ((unsigned char)c & 0x3Fu); result &= ((GetRange((unsigned char)c) & 0x70) != 0); return result;
        case 10: c = is.Take(); *codepoint = (*codepoint << 6) | ((unsigned char)c & 0x3Fu); result &= ((GetRange((unsigned char)c) & 0x20) != 0); c = is.Take(); *codepoint = (*codepoint << 6) | ((unsigned char)c & 0x3Fu); result &= ((GetRange((unsigned char)c) & 0x70) != 0); return result;
        case 11: c = is.Take(); *codepoint = (*codepoint << 6) | ((unsigned char)c & 0x3Fu); result &= ((GetRange((unsigned char)c) & 0x60) != 0); c = is.Take(); *codepoint = (*codepoint << 6) | ((unsigned char)c & 0x3Fu); result &= ((GetRange((unsigned char)c) & 0x70) != 0); c = is.Take(); *codepoint = (*codepoint << 6) | ((unsigned char)c & 0x3Fu); result &= ((GetRange((unsigned char)c) & 0x70) != 0); return result;
        default: return false;
        }
    }
    template <typename InputStream, typename OutputStream>
    static bool Validate(InputStream& is, OutputStream& os) {
        Ch c;
        os.Put(c = is.Take());
        if (!(c & 0x80))
            return true;
        bool result = true;
        switch (GetRange((unsigned char)c)) {
        case 2: os.Put(c = is.Take()); result &= ((GetRange((unsigned char)c) & 0x70) != 0); return result;
        case 3: os.Put(c = is.Take()); result &= ((GetRange((unsigned char)c) & 0x70) != 0); os.Put(c = is.Take()); result &= ((GetRange((unsigned char)c) & 0x70) != 0); return result;
        case 4: os.Put(c = is.Take()); result &= ((GetRange((unsigned char)c) & 0x50) != 0); os.Put(c = is.Take()); result &= ((GetRange((unsigned char)c) & 0x70) != 0); return result;
        case 5: os.Put(c = is.Take()); result &= ((GetRange((unsigned char)c) & 0x10) != 0); os.Put(c = is.Take()); result &= ((GetRange((unsigned char)c) & 0x70) != 0); os.Put(c = is.Take()); result &= ((GetRange((unsigned char)c) & 0x70) != 0); return result;
        case 6: os.Put(c = is.Take()); result &= ((GetRange((unsigned char)c) & 0x70) != 0); os.Put(c = is.Take()); result &= ((GetRange((unsigned char)c) & 0x70) != 0); os.Put(c = is.Take()); result &= ((GetRange((unsigned char)c) & 0x70) != 0); return result;
        case 10: os.Put(c = is.Take()); result &= ((GetRange((unsigned char)c) & 0x20) != 0); os.Put(c = is.Take()); result &= ((GetRange((unsigned char)c) & 0x70) != 0); return result;
        case 11: os.Put(c = is.Take()); result &= ((GetRange((unsigned char)c) & 0x60) != 0); os.Put(c = is.Take()); result &= ((GetRange((unsigned char)c) & 0x70) != 0); os.Put(c = is.Take()); result &= ((GetRange((unsigned char)c) & 0x70) != 0); return result;
        default: return false;
        }
    }
    static unsigned char GetRange(unsigned char c) {
        static const unsigned char type[] = {
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
            0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,
            0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
            0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
            8,8,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
            10,3,3,3,3,3,3,3,3,3,3,3,3,4,3,3, 11,6,6,6,5,8,8,8,8,8,8,8,8,8,8,8,
        };
        return type[c];
    }
    template <typename InputByteStream>
    static CharType TakeBOM(InputByteStream& is) {
        typedef ::rapidjson::StaticAssertTest< sizeof(::rapidjson::STATIC_ASSERTION_FAILURE<bool(sizeof(typename InputByteStream::Ch) == 1) >)> StaticAssertTypedef203 __attribute__((unused));
        Ch c = Take(is);
        if ((unsigned char)c != 0xEFu) return c;
        c = is.Take();
        if ((unsigned char)c != 0xBBu) return c;
        c = is.Take();
        if ((unsigned char)c != 0xBFu) return c;
        c = is.Take();
        return c;
    }
    template <typename InputByteStream>
    static Ch Take(InputByteStream& is) {
        typedef ::rapidjson::StaticAssertTest< sizeof(::rapidjson::STATIC_ASSERTION_FAILURE<bool(sizeof(typename InputByteStream::Ch) == 1) >)> StaticAssertTypedef216 __attribute__((unused));
        return is.Take();
    }
    template <typename OutputByteStream>
    static void PutBOM(OutputByteStream& os) {
        typedef ::rapidjson::StaticAssertTest< sizeof(::rapidjson::STATIC_ASSERTION_FAILURE<bool(sizeof(typename OutputByteStream::Ch) == 1) >)> StaticAssertTypedef222 __attribute__((unused));
        os.Put(0xEFu); os.Put(0xBBu); os.Put(0xBFu);
    }
    template <typename OutputByteStream>
    static void Put(OutputByteStream& os, Ch c) {
        typedef ::rapidjson::StaticAssertTest< sizeof(::rapidjson::STATIC_ASSERTION_FAILURE<bool(sizeof(typename OutputByteStream::Ch) == 1) >)> StaticAssertTypedef228 __attribute__((unused));
        os.Put(static_cast<typename OutputByteStream::Ch>(c));
    }
};
template<typename CharType = wchar_t>
struct UTF16 {
    typedef CharType Ch;
    typedef ::rapidjson::StaticAssertTest< sizeof(::rapidjson::STATIC_ASSERTION_FAILURE<bool(sizeof(Ch) >= 2) >)> StaticAssertTypedef248 __attribute__((unused));
    enum { supportUnicode = 1 };
    template<typename OutputStream>
    static void Encode(OutputStream& os, unsigned codepoint) {
        typedef ::rapidjson::StaticAssertTest< sizeof(::rapidjson::STATIC_ASSERTION_FAILURE<bool(sizeof(typename OutputStream::Ch) >= 2) >)> StaticAssertTypedef254 __attribute__((unused));
        if (codepoint <= 0xFFFF) {
            ((codepoint < 0xD800 || codepoint > 0xDFFF) ? static_cast<void> (0) : __assert_fail ("codepoint < 0xD800 || codepoint > 0xDFFF", "aapt/rapidjson/encodings.h", 256, __PRETTY_FUNCTION__));
            os.Put(static_cast<typename OutputStream::Ch>(codepoint));
        }
        else {
            ((codepoint <= 0x10FFFF) ? static_cast<void> (0) : __assert_fail ("codepoint <= 0x10FFFF", "aapt/rapidjson/encodings.h", 260, __PRETTY_FUNCTION__));
            unsigned v = codepoint - 0x10000;
            os.Put(static_cast<typename OutputStream::Ch>((v >> 10) | 0xD800));
            os.Put((v & 0x3FF) | 0xDC00);
        }
    }
    template <typename InputStream>
    static bool Decode(InputStream& is, unsigned* codepoint) {
        typedef ::rapidjson::StaticAssertTest< sizeof(::rapidjson::STATIC_ASSERTION_FAILURE<bool(sizeof(typename InputStream::Ch) >= 2) >)> StaticAssertTypedef269 __attribute__((unused));
        Ch c = is.Take();
        if (c < 0xD800 || c > 0xDFFF) {
            *codepoint = c;
            return true;
        }
        else if (c <= 0xDBFF) {
            *codepoint = (c & 0x3FF) << 10;
            c = is.Take();
            *codepoint |= (c & 0x3FF);
            *codepoint += 0x10000;
            return c >= 0xDC00 && c <= 0xDFFF;
        }
        return false;
    }
    template <typename InputStream, typename OutputStream>
    static bool Validate(InputStream& is, OutputStream& os) {
        typedef ::rapidjson::StaticAssertTest< sizeof(::rapidjson::STATIC_ASSERTION_FAILURE<bool(sizeof(typename InputStream::Ch) >= 2) >)> StaticAssertTypedef287 __attribute__((unused));
        typedef ::rapidjson::StaticAssertTest< sizeof(::rapidjson::STATIC_ASSERTION_FAILURE<bool(sizeof(typename OutputStream::Ch) >= 2) >)> StaticAssertTypedef288 __attribute__((unused));
        Ch c;
        os.Put(c = is.Take());
        if (c < 0xD800 || c > 0xDFFF)
            return true;
        else if (c <= 0xDBFF) {
            os.Put(c = is.Take());
            return c >= 0xDC00 && c <= 0xDFFF;
        }
        return false;
    }
};
template<typename CharType = wchar_t>
struct UTF16LE : UTF16<CharType> {
    template <typename InputByteStream>
    static CharType TakeBOM(InputByteStream& is) {
        typedef ::rapidjson::StaticAssertTest< sizeof(::rapidjson::STATIC_ASSERTION_FAILURE<bool(sizeof(typename InputByteStream::Ch) == 1) >)> StaticAssertTypedef306 __attribute__((unused));
        CharType c = Take(is);
        return (unsigned short)c == 0xFEFFu ? Take(is) : c;
    }
    template <typename InputByteStream>
    static CharType Take(InputByteStream& is) {
        typedef ::rapidjson::StaticAssertTest< sizeof(::rapidjson::STATIC_ASSERTION_FAILURE<bool(sizeof(typename InputByteStream::Ch) == 1) >)> StaticAssertTypedef313 __attribute__((unused));
        CharType c = (unsigned char)is.Take();
        c |= (unsigned char)is.Take() << 8;
        return c;
    }
    template <typename OutputByteStream>
    static void PutBOM(OutputByteStream& os) {
        typedef ::rapidjson::StaticAssertTest< sizeof(::rapidjson::STATIC_ASSERTION_FAILURE<bool(sizeof(typename OutputByteStream::Ch) == 1) >)> StaticAssertTypedef321 __attribute__((unused));
        os.Put(0xFFu); os.Put(0xFEu);
    }
    template <typename OutputByteStream>
    static void Put(OutputByteStream& os, CharType c) {
        typedef ::rapidjson::StaticAssertTest< sizeof(::rapidjson::STATIC_ASSERTION_FAILURE<bool(sizeof(typename OutputByteStream::Ch) == 1) >)> StaticAssertTypedef327 __attribute__((unused));
        os.Put(c & 0xFFu);
        os.Put((c >> 8) & 0xFFu);
    }
};
template<typename CharType = wchar_t>
struct UTF16BE : UTF16<CharType> {
    template <typename InputByteStream>
    static CharType TakeBOM(InputByteStream& is) {
        typedef ::rapidjson::StaticAssertTest< sizeof(::rapidjson::STATIC_ASSERTION_FAILURE<bool(sizeof(typename InputByteStream::Ch) == 1) >)> StaticAssertTypedef338 __attribute__((unused));
        CharType c = Take(is);
        return (unsigned short)c == 0xFEFFu ? Take(is) : c;
    }
    template <typename InputByteStream>
    static CharType Take(InputByteStream& is) {
        typedef ::rapidjson::StaticAssertTest< sizeof(::rapidjson::STATIC_ASSERTION_FAILURE<bool(sizeof(typename InputByteStream::Ch) == 1) >)> StaticAssertTypedef345 __attribute__((unused));
        CharType c = (unsigned char)is.Take() << 8;
        c |= (unsigned char)is.Take();
        return c;
    }
    template <typename OutputByteStream>
    static void PutBOM(OutputByteStream& os) {
        typedef ::rapidjson::StaticAssertTest< sizeof(::rapidjson::STATIC_ASSERTION_FAILURE<bool(sizeof(typename OutputByteStream::Ch) == 1) >)> StaticAssertTypedef353 __attribute__((unused));
        os.Put(0xFEu); os.Put(0xFFu);
    }
    template <typename OutputByteStream>
    static void Put(OutputByteStream& os, CharType c) {
        typedef ::rapidjson::StaticAssertTest< sizeof(::rapidjson::STATIC_ASSERTION_FAILURE<bool(sizeof(typename OutputByteStream::Ch) == 1) >)> StaticAssertTypedef359 __attribute__((unused));
        os.Put((c >> 8) & 0xFFu);
        os.Put(c & 0xFFu);
    }
};
template<typename CharType = unsigned>
struct UTF32 {
    typedef CharType Ch;
    typedef ::rapidjson::StaticAssertTest< sizeof(::rapidjson::STATIC_ASSERTION_FAILURE<bool(sizeof(Ch) >= 4) >)> StaticAssertTypedef379 __attribute__((unused));
    enum { supportUnicode = 1 };
    template<typename OutputStream>
    static void Encode(OutputStream& os, unsigned codepoint) {
        typedef ::rapidjson::StaticAssertTest< sizeof(::rapidjson::STATIC_ASSERTION_FAILURE<bool(sizeof(typename OutputStream::Ch) >= 4) >)> StaticAssertTypedef385 __attribute__((unused));
        ((codepoint <= 0x10FFFF) ? static_cast<void> (0) : __assert_fail ("codepoint <= 0x10FFFF", "aapt/rapidjson/encodings.h", 386, __PRETTY_FUNCTION__));
        os.Put(codepoint);
    }
    template <typename InputStream>
    static bool Decode(InputStream& is, unsigned* codepoint) {
        typedef ::rapidjson::StaticAssertTest< sizeof(::rapidjson::STATIC_ASSERTION_FAILURE<bool(sizeof(typename InputStream::Ch) >= 4) >)> StaticAssertTypedef392 __attribute__((unused));
        Ch c = is.Take();
        *codepoint = c;
        return c <= 0x10FFFF;
    }
    template <typename InputStream, typename OutputStream>
    static bool Validate(InputStream& is, OutputStream& os) {
        typedef ::rapidjson::StaticAssertTest< sizeof(::rapidjson::STATIC_ASSERTION_FAILURE<bool(sizeof(typename InputStream::Ch) >= 4) >)> StaticAssertTypedef400 __attribute__((unused));
        Ch c;
        os.Put(c = is.Take());
        return c <= 0x10FFFF;
    }
};
template<typename CharType = unsigned>
struct UTF32LE : UTF32<CharType> {
    template <typename InputByteStream>
    static CharType TakeBOM(InputByteStream& is) {
        typedef ::rapidjson::StaticAssertTest< sizeof(::rapidjson::STATIC_ASSERTION_FAILURE<bool(sizeof(typename InputByteStream::Ch) == 1) >)> StaticAssertTypedef412 __attribute__((unused));
        CharType c = Take(is);
        return (unsigned)c == 0x0000FEFFu ? Take(is) : c;
    }
    template <typename InputByteStream>
    static CharType Take(InputByteStream& is) {
        typedef ::rapidjson::StaticAssertTest< sizeof(::rapidjson::STATIC_ASSERTION_FAILURE<bool(sizeof(typename InputByteStream::Ch) == 1) >)> StaticAssertTypedef419 __attribute__((unused));
        CharType c = (unsigned char)is.Take();
        c |= (unsigned char)is.Take() << 8;
        c |= (unsigned char)is.Take() << 16;
        c |= (unsigned char)is.Take() << 24;
        return c;
    }
    template <typename OutputByteStream>
    static void PutBOM(OutputByteStream& os) {
        typedef ::rapidjson::StaticAssertTest< sizeof(::rapidjson::STATIC_ASSERTION_FAILURE<bool(sizeof(typename OutputByteStream::Ch) == 1) >)> StaticAssertTypedef429 __attribute__((unused));
        os.Put(0xFFu); os.Put(0xFEu); os.Put(0x00u); os.Put(0x00u);
    }
    template <typename OutputByteStream>
    static void Put(OutputByteStream& os, CharType c) {
        typedef ::rapidjson::StaticAssertTest< sizeof(::rapidjson::STATIC_ASSERTION_FAILURE<bool(sizeof(typename OutputByteStream::Ch) == 1) >)> StaticAssertTypedef435 __attribute__((unused));
        os.Put(c & 0xFFu);
        os.Put((c >> 8) & 0xFFu);
        os.Put((c >> 16) & 0xFFu);
        os.Put((c >> 24) & 0xFFu);
    }
};
template<typename CharType = unsigned>
struct UTF32BE : UTF32<CharType> {
    template <typename InputByteStream>
    static CharType TakeBOM(InputByteStream& is) {
        typedef ::rapidjson::StaticAssertTest< sizeof(::rapidjson::STATIC_ASSERTION_FAILURE<bool(sizeof(typename InputByteStream::Ch) == 1) >)> StaticAssertTypedef448 __attribute__((unused));
        CharType c = Take(is);
        return (unsigned)c == 0x0000FEFFu ? Take(is) : c;
    }
    template <typename InputByteStream>
    static CharType Take(InputByteStream& is) {
        typedef ::rapidjson::StaticAssertTest< sizeof(::rapidjson::STATIC_ASSERTION_FAILURE<bool(sizeof(typename InputByteStream::Ch) == 1) >)> StaticAssertTypedef455 __attribute__((unused));
        CharType c = (unsigned char)is.Take() << 24;
        c |= (unsigned char)is.Take() << 16;
        c |= (unsigned char)is.Take() << 8;
        c |= (unsigned char)is.Take();
        return c;
    }
    template <typename OutputByteStream>
    static void PutBOM(OutputByteStream& os) {
        typedef ::rapidjson::StaticAssertTest< sizeof(::rapidjson::STATIC_ASSERTION_FAILURE<bool(sizeof(typename OutputByteStream::Ch) == 1) >)> StaticAssertTypedef465 __attribute__((unused));
        os.Put(0x00u); os.Put(0x00u); os.Put(0xFEu); os.Put(0xFFu);
    }
    template <typename OutputByteStream>
    static void Put(OutputByteStream& os, CharType c) {
        typedef ::rapidjson::StaticAssertTest< sizeof(::rapidjson::STATIC_ASSERTION_FAILURE<bool(sizeof(typename OutputByteStream::Ch) == 1) >)> StaticAssertTypedef471 __attribute__((unused));
        os.Put((c >> 24) & 0xFFu);
        os.Put((c >> 16) & 0xFFu);
        os.Put((c >> 8) & 0xFFu);
        os.Put(c & 0xFFu);
    }
};
template<typename CharType = char>
struct ASCII {
    typedef CharType Ch;
    enum { supportUnicode = 0 };
    template<typename OutputStream>
    static void Encode(OutputStream& os, unsigned codepoint) {
        ((codepoint <= 0x7F) ? static_cast<void> (0) : __assert_fail ("codepoint <= 0x7F", "aapt/rapidjson/encodings.h", 495, __PRETTY_FUNCTION__));
        os.Put(static_cast<Ch>(codepoint & 0xFF));
    }
    template <typename InputStream>
    static bool Decode(InputStream& is, unsigned* codepoint) {
        unsigned char c = static_cast<unsigned char>(is.Take());
        *codepoint = c;
        return c <= 0X7F;
    }
    template <typename InputStream, typename OutputStream>
    static bool Validate(InputStream& is, OutputStream& os) {
        unsigned char c = is.Take();
        os.Put(c);
        return c <= 0x7F;
    }
    template <typename InputByteStream>
    static CharType TakeBOM(InputByteStream& is) {
        typedef ::rapidjson::StaticAssertTest< sizeof(::rapidjson::STATIC_ASSERTION_FAILURE<bool(sizeof(typename InputByteStream::Ch) == 1) >)> StaticAssertTypedef515 __attribute__((unused));
        Ch c = Take(is);
        return c;
    }
    template <typename InputByteStream>
    static Ch Take(InputByteStream& is) {
        typedef ::rapidjson::StaticAssertTest< sizeof(::rapidjson::STATIC_ASSERTION_FAILURE<bool(sizeof(typename InputByteStream::Ch) == 1) >)> StaticAssertTypedef522 __attribute__((unused));
        return is.Take();
    }
    template <typename OutputByteStream>
    static void PutBOM(OutputByteStream& os) {
        typedef ::rapidjson::StaticAssertTest< sizeof(::rapidjson::STATIC_ASSERTION_FAILURE<bool(sizeof(typename OutputByteStream::Ch) == 1) >)> StaticAssertTypedef528 __attribute__((unused));
        (void)os;
    }
    template <typename OutputByteStream>
    static void Put(OutputByteStream& os, Ch c) {
        typedef ::rapidjson::StaticAssertTest< sizeof(::rapidjson::STATIC_ASSERTION_FAILURE<bool(sizeof(typename OutputByteStream::Ch) == 1) >)> StaticAssertTypedef534 __attribute__((unused));
        os.Put(static_cast<typename OutputByteStream::Ch>(c));
    }
};
enum UTFType {
    kUTF8 = 0,
    kUTF16LE = 1,
    kUTF16BE = 2,
    kUTF32LE = 3,
    kUTF32BE = 4
};
template<typename CharType>
struct AutoUTF {
    typedef CharType Ch;
    enum { supportUnicode = 1 };
    template<typename OutputStream>
    __attribute__((always_inline)) static void Encode(OutputStream& os, unsigned codepoint) {
        typedef void (*EncodeFunc)(OutputStream&, unsigned);
        static const EncodeFunc f[] = { UTF8<Ch>::Encode, UTF16LE<Ch>::Encode, UTF16BE<Ch>::Encode, UTF32LE<Ch>::Encode, UTF32BE<Ch>::Encode };
        (*f[os.GetType()])(os, codepoint);
    }
    template <typename InputStream>
    __attribute__((always_inline)) static bool Decode(InputStream& is, unsigned* codepoint) {
        typedef bool (*DecodeFunc)(InputStream&, unsigned*);
        static const DecodeFunc f[] = { UTF8<Ch>::Decode, UTF16LE<Ch>::Decode, UTF16BE<Ch>::Decode, UTF32LE<Ch>::Decode, UTF32BE<Ch>::Decode };
        return (*f[is.GetType()])(is, codepoint);
    }
    template <typename InputStream, typename OutputStream>
    __attribute__((always_inline)) static bool Validate(InputStream& is, OutputStream& os) {
        typedef bool (*ValidateFunc)(InputStream&, OutputStream&);
        static const ValidateFunc f[] = { UTF8<Ch>::Validate, UTF16LE<Ch>::Validate, UTF16BE<Ch>::Validate, UTF32LE<Ch>::Validate, UTF32BE<Ch>::Validate };
        return (*f[is.GetType()])(is, os);
    }
};
template<typename SourceEncoding, typename TargetEncoding>
struct Transcoder {
    template<typename InputStream, typename OutputStream>
    __attribute__((always_inline)) static bool Transcode(InputStream& is, OutputStream& os) {
        unsigned codepoint;
        if (!SourceEncoding::Decode(is, &codepoint))
            return false;
        TargetEncoding::Encode(os, codepoint);
        return true;
    }
    template<typename InputStream, typename OutputStream>
    __attribute__((always_inline)) static bool Validate(InputStream& is, OutputStream& os) {
        return Transcode(is, os);
    }
};
template<typename Encoding>
struct Transcoder<Encoding, Encoding> {
    template<typename InputStream, typename OutputStream>
    __attribute__((always_inline)) static bool Transcode(InputStream& is, OutputStream& os) {
        os.Put(is.Take());
        return true;
    }
    template<typename InputStream, typename OutputStream>
    __attribute__((always_inline)) static bool Validate(InputStream& is, OutputStream& os) {
        return Encoding::Validate(is, os);
    }
};
}

#pragma GCC diagnostic pop

namespace rapidjson {
template<typename Stream>
struct StreamTraits {
    enum { copyOptimization = 0 };
};
template<typename Stream, typename Ch>
inline void PutN(Stream& stream, Ch c, size_t n) {
    for (size_t i = 0; i < n; i++)
        stream.Put(c);
}
template <typename Encoding>
struct GenericStringStream {
    typedef typename Encoding::Ch Ch;
    GenericStringStream(const Ch *src) : src_(src), head_(src) {}
    Ch Peek() const { return *src_; }
    Ch Take() { return *src_++; }
    size_t Tell() const { return static_cast<size_t>(src_ - head_); }
    Ch* PutBegin() { ((false) ? static_cast<void> (0) : __assert_fail ("false", "aapt/rapidjson/rapidjson.h", 554, __PRETTY_FUNCTION__)); return 0; }
    void Put(Ch) { ((false) ? static_cast<void> (0) : __assert_fail ("false", "aapt/rapidjson/rapidjson.h", 555, __PRETTY_FUNCTION__)); }
    void Flush() { ((false) ? static_cast<void> (0) : __assert_fail ("false", "aapt/rapidjson/rapidjson.h", 556, __PRETTY_FUNCTION__)); }
    size_t PutEnd(Ch*) { ((false) ? static_cast<void> (0) : __assert_fail ("false", "aapt/rapidjson/rapidjson.h", 557, __PRETTY_FUNCTION__)); return 0; }
    const Ch* src_;
    const Ch* head_;
};
template <typename Encoding>
struct StreamTraits<GenericStringStream<Encoding> > {
    enum { copyOptimization = 1 };
};
typedef GenericStringStream<UTF8<> > StringStream;
template <typename Encoding>
struct GenericInsituStringStream {
    typedef typename Encoding::Ch Ch;
    GenericInsituStringStream(Ch *src) : src_(src), dst_(0), head_(src) {}
    Ch Peek() { return *src_; }
    Ch Take() { return *src_++; }
    size_t Tell() { return static_cast<size_t>(src_ - head_); }
    void Put(Ch c) { ((dst_ != 0) ? static_cast<void> (0) : __assert_fail ("dst_ != 0", "aapt/rapidjson/rapidjson.h", 590, __PRETTY_FUNCTION__)); *dst_++ = c; }
    Ch* PutBegin() { return dst_ = src_; }
    size_t PutEnd(Ch* begin) { return static_cast<size_t>(dst_ - begin); }
    void Flush() {}
    Ch* Push(size_t count) { Ch* begin = dst_; dst_ += count; return begin; }
    void Pop(size_t count) { dst_ -= count; }
    Ch* src_;
    Ch* dst_;
    Ch* head_;
};
template <typename Encoding>
struct StreamTraits<GenericInsituStringStream<Encoding> > {
    enum { copyOptimization = 1 };
};
typedef GenericInsituStringStream<UTF8<> > InsituStringStream;
enum Type {
    kNullType = 0,
    kFalseType = 1,
    kTrueType = 2,
    kObjectType = 3,
    kArrayType = 4,
    kStringType = 5,
    kNumberType = 6
};
}

#pragma GCC diagnostic push


#pragma GCC diagnostic ignored "-Weffc++"

namespace rapidjson {
namespace internal {
template <typename T> struct Void { typedef void Type; };
template <bool Cond> struct BoolType {
    static const bool Value = Cond;
    typedef BoolType Type;
};
typedef BoolType<true> TrueType;
typedef BoolType<false> FalseType;
template <bool C> struct SelectIfImpl { template <typename T1, typename T2> struct Apply { typedef T1 Type; }; };
template <> struct SelectIfImpl<false> { template <typename T1, typename T2> struct Apply { typedef T2 Type; }; };
template <bool C, typename T1, typename T2> struct SelectIfCond : SelectIfImpl<C>::template Apply<T1,T2> {};
template <typename C, typename T1, typename T2> struct SelectIf : SelectIfCond<C::Value, T1, T2> {};
template <bool Cond1, bool Cond2> struct AndExprCond : FalseType {};
template <> struct AndExprCond<true, true> : TrueType {};
template <bool Cond1, bool Cond2> struct OrExprCond : TrueType {};
template <> struct OrExprCond<false, false> : FalseType {};
template <typename C> struct BoolExpr : SelectIf<C,TrueType,FalseType>::Type {};
template <typename C> struct NotExpr : SelectIf<C,FalseType,TrueType>::Type {};
template <typename C1, typename C2> struct AndExpr : AndExprCond<C1::Value, C2::Value>::Type {};
template <typename C1, typename C2> struct OrExpr : OrExprCond<C1::Value, C2::Value>::Type {};
template <typename T> struct AddConst { typedef const T Type; };
template <bool Constify, typename T> struct MaybeAddConst : SelectIfCond<Constify, const T, T> {};
template <typename T> struct RemoveConst { typedef T Type; };
template <typename T> struct RemoveConst<const T> { typedef T Type; };
template <typename T, typename U> struct IsSame : FalseType {};
template <typename T> struct IsSame<T, T> : TrueType {};
template <typename T> struct IsConst : FalseType {};
template <typename T> struct IsConst<const T> : TrueType {};
template <typename CT, typename T>
struct IsMoreConst
    : AndExpr<IsSame<typename RemoveConst<CT>::Type, typename RemoveConst<T>::Type>,
              BoolType<IsConst<CT>::Value >= IsConst<T>::Value> >::Type {};
template <typename T> struct IsPointer : FalseType {};
template <typename T> struct IsPointer<T*> : TrueType {};
template<typename B, typename D> struct IsBaseOfImpl {
    typedef ::rapidjson::StaticAssertTest< sizeof(::rapidjson::STATIC_ASSERTION_FAILURE<bool(sizeof(B) != 0) >)> StaticAssertTypedef115 __attribute__((unused));
    typedef ::rapidjson::StaticAssertTest< sizeof(::rapidjson::STATIC_ASSERTION_FAILURE<bool(sizeof(D) != 0) >)> StaticAssertTypedef116 __attribute__((unused));
    typedef char (&Yes)[1];
    typedef char (&No) [2];
    template <typename T>
    static Yes Check(const D*, T);
    static No Check(const B*, int);
    struct Host {
        operator const B*() const;
        operator const D*();
    };
    enum { Value = (sizeof(Check(Host(), 0)) == sizeof(Yes)) };
};
template <typename B, typename D> struct IsBaseOf
    : OrExpr<IsSame<B, D>, BoolExpr<IsBaseOfImpl<B, D> > >::Type {};
template <bool Condition, typename T = void> struct EnableIfCond { typedef T Type; };
template <typename T> struct EnableIfCond<false, T> { };
template <bool Condition, typename T = void> struct DisableIfCond { typedef T Type; };
template <typename T> struct DisableIfCond<true, T> { };
template <typename Condition, typename T = void>
struct EnableIf : EnableIfCond<Condition::Value, T> {};
template <typename Condition, typename T = void>
struct DisableIf : DisableIfCond<Condition::Value, T> {};
struct SfinaeTag {};
template <typename T> struct RemoveSfinaeTag;
template <typename T> struct RemoveSfinaeTag<SfinaeTag&(*)(T)> { typedef T Type; };
}
}

#pragma GCC diagnostic pop

namespace rapidjson {
namespace internal {
template <typename Allocator>
class Stack {
public:
    Stack(Allocator* allocator, size_t stackCapacity) : allocator_(allocator), ownAllocator_(0), stack_(0), stackTop_(0), stackEnd_(0), initialCapacity_(stackCapacity) {
        ((stackCapacity > 0) ? static_cast<void> (0) : __assert_fail ("stackCapacity > 0", "aapt/rapidjson/internal/stack.h", 39, __PRETTY_FUNCTION__));
    }
    Stack(Stack&& rhs)
        : allocator_(rhs.allocator_),
          ownAllocator_(rhs.ownAllocator_),
          stack_(rhs.stack_),
          stackTop_(rhs.stackTop_),
          stackEnd_(rhs.stackEnd_),
          initialCapacity_(rhs.initialCapacity_)
    {
        rhs.allocator_ = 0;
        rhs.ownAllocator_ = 0;
        rhs.stack_ = 0;
        rhs.stackTop_ = 0;
        rhs.stackEnd_ = 0;
        rhs.initialCapacity_ = 0;
    }
    ~Stack() {
        Destroy();
    }
    Stack& operator=(Stack&& rhs) {
        if (&rhs != this)
        {
            Destroy();
            allocator_ = rhs.allocator_;
            ownAllocator_ = rhs.ownAllocator_;
            stack_ = rhs.stack_;
            stackTop_ = rhs.stackTop_;
            stackEnd_ = rhs.stackEnd_;
            initialCapacity_ = rhs.initialCapacity_;
            rhs.allocator_ = 0;
            rhs.ownAllocator_ = 0;
            rhs.stack_ = 0;
            rhs.stackTop_ = 0;
            rhs.stackEnd_ = 0;
            rhs.initialCapacity_ = 0;
        }
        return *this;
    }
    void Clear() { stackTop_ = stack_; }
    void ShrinkToFit() {
        if (Empty()) {
            Allocator::Free(stack_);
            stack_ = 0;
            stackTop_ = 0;
            stackEnd_ = 0;
        }
        else
            Resize(GetSize());
    }
    template<typename T>
    __attribute__((always_inline)) T* Push(size_t count = 1) {
        if (stackTop_ + sizeof(T) * count >= stackEnd_)
            Expand<T>(count);
        T* ret = reinterpret_cast<T*>(stackTop_);
        stackTop_ += sizeof(T) * count;
        return ret;
    }
    template<typename T>
    T* Pop(size_t count) {
        ((GetSize() >= count * sizeof(T)) ? static_cast<void> (0) : __assert_fail ("GetSize() >= count * sizeof(T)", "aapt/rapidjson/internal/stack.h", 117, __PRETTY_FUNCTION__));
        stackTop_ -= count * sizeof(T);
        return reinterpret_cast<T*>(stackTop_);
    }
    template<typename T>
    T* Top() {
        ((GetSize() >= sizeof(T)) ? static_cast<void> (0) : __assert_fail ("GetSize() >= sizeof(T)", "aapt/rapidjson/internal/stack.h", 124, __PRETTY_FUNCTION__));
        return reinterpret_cast<T*>(stackTop_ - sizeof(T));
    }
    template<typename T>
    T* Bottom() { return (T*)stack_; }
    Allocator& GetAllocator() { return *allocator_; }
    bool Empty() const { return stackTop_ == stack_; }
    size_t GetSize() const { return static_cast<size_t>(stackTop_ - stack_); }
    size_t GetCapacity() const { return static_cast<size_t>(stackEnd_ - stack_); }
private:
    template<typename T>
    void Expand(size_t count) {
        size_t newCapacity;
        if (stack_ == 0) {
            if (!allocator_)
                ownAllocator_ = allocator_ = new Allocator();
            newCapacity = initialCapacity_;
        } else {
            newCapacity = GetCapacity();
            newCapacity += (newCapacity + 1) / 2;
        }
        size_t newSize = GetSize() + sizeof(T) * count;
        if (newCapacity < newSize)
            newCapacity = newSize;
        Resize(newCapacity);
    }
    void Resize(size_t newCapacity) {
        const size_t size = GetSize();
        stack_ = (char*)allocator_->Realloc(stack_, GetCapacity(), newCapacity);
        stackTop_ = stack_ + size;
        stackEnd_ = stack_ + newCapacity;
    }
    void Destroy() {
        Allocator::Free(stack_);
        delete ownAllocator_;
    }
    Stack(const Stack&);
    Stack& operator=(const Stack&);
    Allocator* allocator_;
    Allocator* ownAllocator_;
    char *stack_;
    char *stackTop_;
    char *stackEnd_;
    size_t initialCapacity_;
};
}
}
namespace rapidjson {
namespace internal {
class Double {
public:
    Double() {}
    Double(double d) : d(d) {}
    Double(uint64_t u) : u(u) {}
    double Value() const { return d; }
    uint64_t Uint64Value() const { return u; }
    double NextPositiveDouble() const {
        ((!Sign()) ? static_cast<void> (0) : __assert_fail ("!Sign()", "aapt/rapidjson/internal/ieee754.h", 39, __PRETTY_FUNCTION__));
        return Double(u + 1).Value();
    }
    double PreviousPositiveDouble() const {
        ((!Sign()) ? static_cast<void> (0) : __assert_fail ("!Sign()", "aapt/rapidjson/internal/ieee754.h", 44, __PRETTY_FUNCTION__));
        if (d == 0.0)
            return 0.0;
        else
            return Double(u - 1).Value();
    }
    bool Sign() const { return (u & kSignMask) != 0; }
    uint64_t Significand() const { return u & kSignificandMask; }
    int Exponent() const { return ((u & kExponentMask) >> kSignificandSize) - kExponentBias; }
    bool IsNan() const { return (u & kExponentMask) == kExponentMask && Significand() != 0; }
    bool IsInf() const { return (u & kExponentMask) == kExponentMask && Significand() == 0; }
    bool IsNormal() const { return (u & kExponentMask) != 0 || Significand() == 0; }
    uint64_t IntegerSignificand() const { return IsNormal() ? Significand() | kHiddenBit : Significand(); }
    int IntegerExponent() const { return (IsNormal() ? Exponent() : kDenormalExponent) - kSignificandSize; }
    uint64_t ToBias() const { return (u & kSignMask) ? ~u + 1 : u | kSignMask; }
    static unsigned EffectiveSignificandSize(int order) {
        if (order >= -1021)
            return 53;
        else if (order <= -1074)
            return 0;
        else
            return order + 1074;
    }
private:
    static const int kSignificandSize = 52;
    static const int kExponentBias = 0x3FF;
    static const int kDenormalExponent = 1 - kExponentBias;
    static const uint64_t kSignMask = ((static_cast<uint64_t>(0x80000000) << 32) | static_cast<uint64_t>(0x00000000));
    static const uint64_t kExponentMask = ((static_cast<uint64_t>(0x7FF00000) << 32) | static_cast<uint64_t>(0x00000000));
    static const uint64_t kSignificandMask = ((static_cast<uint64_t>(0x000FFFFF) << 32) | static_cast<uint64_t>(0xFFFFFFFF));
    static const uint64_t kHiddenBit = ((static_cast<uint64_t>(0x00100000) << 32) | static_cast<uint64_t>(0x00000000));
    union {
        double d;
        uint64_t u;
    };
};
}
}
namespace rapidjson {
namespace internal {
class BigInteger {
public:
    typedef uint64_t Type;
    BigInteger(const BigInteger& rhs) : count_(rhs.count_) {
        std::memcpy(digits_, rhs.digits_, count_ * sizeof(Type));
    }
    explicit BigInteger(uint64_t u) : count_(1) {
        digits_[0] = u;
    }
    BigInteger(const char* decimals, size_t length) : count_(1) {
        ((length > 0) ? static_cast<void> (0) : __assert_fail ("length > 0", "aapt/rapidjson/internal/biginteger.h", 42, __PRETTY_FUNCTION__));
        digits_[0] = 0;
        size_t i = 0;
        const size_t kMaxDigitPerIteration = 19;
        while (length >= kMaxDigitPerIteration) {
            AppendDecimal64(decimals + i, decimals + i + kMaxDigitPerIteration);
            length -= kMaxDigitPerIteration;
            i += kMaxDigitPerIteration;
        }
        if (length > 0)
            AppendDecimal64(decimals + i, decimals + i + length);
    }
    BigInteger& operator=(uint64_t u) {
        digits_[0] = u;
        count_ = 1;
        return *this;
    }
    BigInteger& operator+=(uint64_t u) {
        Type backup = digits_[0];
        digits_[0] += u;
        for (size_t i = 0; i < count_ - 1; i++) {
            if (digits_[i] >= backup)
                return *this;
            backup = digits_[i + 1];
            digits_[i + 1] += 1;
        }
        if (digits_[count_ - 1] < backup)
            PushBack(1);
        return *this;
    }
    BigInteger& operator*=(uint64_t u) {
        if (u == 0) return *this = 0;
        if (u == 1) return *this;
        if (*this == 1) return *this = u;
        uint64_t k = 0;
        for (size_t i = 0; i < count_; i++) {
            uint64_t hi;
            digits_[i] = MulAdd64(digits_[i], u, k, &hi);
            k = hi;
        }
        if (k > 0)
            PushBack(k);
        return *this;
    }
    BigInteger& operator*=(uint32_t u) {
        if (u == 0) return *this = 0;
        if (u == 1) return *this;
        if (*this == 1) return *this = u;
        uint32_t k = 0;
        for (size_t i = 0; i < count_; i++) {
            const uint64_t c = digits_[i] >> 32;
            const uint64_t d = digits_[i] & 0xFFFFFFFF;
            const uint64_t uc = u * c;
            const uint64_t ud = u * d;
            const uint64_t p0 = ud + k;
            const uint64_t p1 = uc + (p0 >> 32);
            digits_[i] = (p0 & 0xFFFFFFFF) | (p1 << 32);
            k = p1 >> 32;
        }
        if (k > 0)
            PushBack(k);
        return *this;
    }
    BigInteger& operator<<=(size_t shift) {
        if (IsZero() || shift == 0) return *this;
        size_t offset = shift / kTypeBit;
        size_t interShift = shift % kTypeBit;
        ((count_ + offset <= kCapacity) ? static_cast<void> (0) : __assert_fail ("count_ + offset <= kCapacity", "aapt/rapidjson/internal/biginteger.h", 125, __PRETTY_FUNCTION__));
        if (interShift == 0) {
            std::memmove(&digits_[count_ - 1 + offset], &digits_[count_ - 1], count_ * sizeof(Type));
            count_ += offset;
        }
        else {
            digits_[count_] = 0;
            for (size_t i = count_; i > 0; i--)
                digits_[i + offset] = (digits_[i] << interShift) | (digits_[i - 1] >> (kTypeBit - interShift));
            digits_[offset] = digits_[0] << interShift;
            count_ += offset;
            if (digits_[count_])
                count_++;
        }
        std::memset(digits_, 0, offset * sizeof(Type));
        return *this;
    }
    bool operator==(const BigInteger& rhs) const {
        return count_ == rhs.count_ && memcmp(digits_, rhs.digits_, count_ * sizeof(Type)) == 0;
    }
    bool operator==(const Type rhs) const {
        return count_ == 1 && digits_[0] == rhs;
    }
    BigInteger& MultiplyPow5(unsigned exp) {
        static const uint32_t kPow5[12] = {
            5,
            5 * 5,
            5 * 5 * 5,
            5 * 5 * 5 * 5,
            5 * 5 * 5 * 5 * 5,
            5 * 5 * 5 * 5 * 5 * 5,
            5 * 5 * 5 * 5 * 5 * 5 * 5,
            5 * 5 * 5 * 5 * 5 * 5 * 5 * 5,
            5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5,
            5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5,
            5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5,
            5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5
        };
        if (exp == 0) return *this;
        for (; exp >= 27; exp -= 27) *this *= ((static_cast<uint64_t>(0X6765C793) << 32) | static_cast<uint64_t>(0XFA10079D));
        for (; exp >= 13; exp -= 13) *this *= 1220703125u;
        if (exp > 0) *this *= kPow5[exp - 1];
        return *this;
    }
    bool Difference(const BigInteger& rhs, BigInteger* out) const {
        int cmp = Compare(rhs);
        if (cmp == 0) {
            *out = BigInteger(0);
            return false;
        }
        const BigInteger *a, *b;
        bool ret;
        if (cmp < 0) { a = &rhs; b = this; ret = true; }
        else { a = this; b = &rhs; ret = false; }
        Type borrow = 0;
        for (size_t i = 0; i < a->count_; i++) {
            Type d = a->digits_[i] - borrow;
            if (i < b->count_)
                d -= b->digits_[i];
            borrow = (d > a->digits_[i]) ? 1 : 0;
            out->digits_[i] = d;
            if (d != 0)
                out->count_ = i + 1;
        }
        return ret;
    }
    int Compare(const BigInteger& rhs) const {
        if (count_ != rhs.count_)
            return count_ < rhs.count_ ? -1 : 1;
        for (size_t i = count_; i-- > 0;)
            if (digits_[i] != rhs.digits_[i])
                return digits_[i] < rhs.digits_[i] ? -1 : 1;
        return 0;
    }
    size_t GetCount() const { return count_; }
    Type GetDigit(size_t index) const { ((index < count_) ? static_cast<void> (0) : __assert_fail ("index < count_", "aapt/rapidjson/internal/biginteger.h", 215, __PRETTY_FUNCTION__)); return digits_[index]; }
    bool IsZero() const { return count_ == 1 && digits_[0] == 0; }
private:
    void AppendDecimal64(const char* begin, const char* end) {
        uint64_t u = ParseUint64(begin, end);
        if (IsZero())
            *this = u;
        else {
            unsigned exp = static_cast<unsigned>(end - begin);
            (MultiplyPow5(exp) <<= exp) += u;
        }
    }
    void PushBack(Type digit) {
        ((count_ < kCapacity) ? static_cast<void> (0) : __assert_fail ("count_ < kCapacity", "aapt/rapidjson/internal/biginteger.h", 230, __PRETTY_FUNCTION__));
        digits_[count_++] = digit;
    }
    static uint64_t ParseUint64(const char* begin, const char* end) {
        uint64_t r = 0;
        for (const char* p = begin; p != end; ++p) {
            ((*p >= '0' && *p <= '9') ? static_cast<void> (0) : __assert_fail ("*p >= '0' && *p <= '9'", "aapt/rapidjson/internal/biginteger.h", 237, __PRETTY_FUNCTION__));
            r = r * 10 + (*p - '0');
        }
        return r;
    }
    static uint64_t MulAdd64(uint64_t a, uint64_t b, uint64_t k, uint64_t* outHigh) {
        unsigned __int128 p = static_cast<unsigned __int128>(a) * static_cast<unsigned __int128>(b);
        p += k;
        *outHigh = p >> 64;
        return static_cast<uint64_t>(p);
    }
    static Type FullAdd(Type a, Type b, bool inCarry, bool* outCarry) {
        Type c = a + b + (inCarry ? 1 : 0);
        *outCarry = c < a;
        return c;
    }
    static const size_t kBitCount = 3328;
    static const size_t kCapacity = kBitCount / sizeof(Type);
    static const size_t kTypeBit = sizeof(Type) * 8;
    Type digits_[kCapacity];
    size_t count_;
};
}
}
namespace rapidjson {
namespace internal {

#pragma GCC diagnostic push


#pragma GCC diagnostic ignored "-Weffc++"

struct DiyFp {
    DiyFp() {}
    DiyFp(uint64_t fp, int exp) : f(fp), e(exp) {}
    explicit DiyFp(double d) {
        union {
            double d;
            uint64_t u64;
        } u = { d };
        int biased_e = (u.u64 & kDpExponentMask) >> kDpSignificandSize;
        uint64_t significand = (u.u64 & kDpSignificandMask);
        if (biased_e != 0) {
            f = significand + kDpHiddenBit;
            e = biased_e - kDpExponentBias;
        }
        else {
            f = significand;
            e = kDpMinExponent + 1;
        }
    }
    DiyFp operator-(const DiyFp& rhs) const {
        return DiyFp(f - rhs.f, e);
    }
    DiyFp operator*(const DiyFp& rhs) const {
        unsigned __int128 p = static_cast<unsigned __int128>(f) * static_cast<unsigned __int128>(rhs.f);
        uint64_t h = p >> 64;
        uint64_t l = static_cast<uint64_t>(p);
        if (l & (uint64_t(1) << 63))
            h++;
        return DiyFp(h, e + rhs.e + 64);
    }
    DiyFp Normalize() const {
        int s = __builtin_clzll(f);
        return DiyFp(f << s, e - s);
    }
    DiyFp NormalizeBoundary() const {
        DiyFp res = *this;
        while (!(res.f & (kDpHiddenBit << 1))) {
            res.f <<= 1;
            res.e--;
        }
        res.f <<= (kDiySignificandSize - kDpSignificandSize - 2);
        res.e = res.e - (kDiySignificandSize - kDpSignificandSize - 2);
        return res;
    }
    void NormalizedBoundaries(DiyFp* minus, DiyFp* plus) const {
        DiyFp pl = DiyFp((f << 1) + 1, e - 1).NormalizeBoundary();
        DiyFp mi = (f == kDpHiddenBit) ? DiyFp((f << 2) - 1, e - 2) : DiyFp((f << 1) - 1, e - 1);
        mi.f <<= mi.e - pl.e;
        mi.e = pl.e;
        *plus = pl;
        *minus = mi;
    }
    double ToDouble() const {
        union {
            double d;
            uint64_t u64;
        }u;
        uint64_t significand = f;
        int exponent = e;
        while (significand > kDpHiddenBit + kDpSignificandMask) {
            significand >>= 1;
            exponent++;
        }
        while (exponent > kDpDenormalExponent && (significand & kDpHiddenBit) == 0) {
            significand <<= 1;
            exponent--;
        }
        if (exponent >= kDpMaxExponent) {
            u.u64 = kDpExponentMask;
            return u.d;
        }
        else if (exponent < kDpDenormalExponent)
            return 0.0;
        const uint64_t be = (exponent == kDpDenormalExponent && (significand & kDpHiddenBit) == 0) ? 0 :
            static_cast<uint64_t>(exponent + kDpExponentBias);
        u.u64 = (significand & kDpSignificandMask) | (be << kDpSignificandSize);
        return u.d;
    }
    static const int kDiySignificandSize = 64;
    static const int kDpSignificandSize = 52;
    static const int kDpExponentBias = 0x3FF + kDpSignificandSize;
    static const int kDpMaxExponent = 0x7FF - kDpExponentBias;
    static const int kDpMinExponent = -kDpExponentBias;
    static const int kDpDenormalExponent = -kDpExponentBias + 1;
    static const uint64_t kDpExponentMask = ((static_cast<uint64_t>(0x7FF00000) << 32) | static_cast<uint64_t>(0x00000000));
    static const uint64_t kDpSignificandMask = ((static_cast<uint64_t>(0x000FFFFF) << 32) | static_cast<uint64_t>(0xFFFFFFFF));
    static const uint64_t kDpHiddenBit = ((static_cast<uint64_t>(0x00100000) << 32) | static_cast<uint64_t>(0x00000000));
    uint64_t f;
    int e;
};
inline DiyFp GetCachedPowerByIndex(size_t index) {
    static const uint64_t kCachedPowers_F[] = {
        ((static_cast<uint64_t>(0xfa8fd5a0) << 32) | static_cast<uint64_t>(0x081c0288)), ((static_cast<uint64_t>(0xbaaee17f) << 32) | static_cast<uint64_t>(0xa23ebf76)),
        ((static_cast<uint64_t>(0x8b16fb20) << 32) | static_cast<uint64_t>(0x3055ac76)), ((static_cast<uint64_t>(0xcf42894a) << 32) | static_cast<uint64_t>(0x5dce35ea)),
        ((static_cast<uint64_t>(0x9a6bb0aa) << 32) | static_cast<uint64_t>(0x55653b2d)), ((static_cast<uint64_t>(0xe61acf03) << 32) | static_cast<uint64_t>(0x3d1a45df)),
        ((static_cast<uint64_t>(0xab70fe17) << 32) | static_cast<uint64_t>(0xc79ac6ca)), ((static_cast<uint64_t>(0xff77b1fc) << 32) | static_cast<uint64_t>(0xbebcdc4f)),
        ((static_cast<uint64_t>(0xbe5691ef) << 32) | static_cast<uint64_t>(0x416bd60c)), ((static_cast<uint64_t>(0x8dd01fad) << 32) | static_cast<uint64_t>(0x907ffc3c)),
        ((static_cast<uint64_t>(0xd3515c28) << 32) | static_cast<uint64_t>(0x31559a83)), ((static_cast<uint64_t>(0x9d71ac8f) << 32) | static_cast<uint64_t>(0xada6c9b5)),
        ((static_cast<uint64_t>(0xea9c2277) << 32) | static_cast<uint64_t>(0x23ee8bcb)), ((static_cast<uint64_t>(0xaecc4991) << 32) | static_cast<uint64_t>(0x4078536d)),
        ((static_cast<uint64_t>(0x823c1279) << 32) | static_cast<uint64_t>(0x5db6ce57)), ((static_cast<uint64_t>(0xc2109436) << 32) | static_cast<uint64_t>(0x4dfb5637)),
        ((static_cast<uint64_t>(0x9096ea6f) << 32) | static_cast<uint64_t>(0x3848984f)), ((static_cast<uint64_t>(0xd77485cb) << 32) | static_cast<uint64_t>(0x25823ac7)),
        ((static_cast<uint64_t>(0xa086cfcd) << 32) | static_cast<uint64_t>(0x97bf97f4)), ((static_cast<uint64_t>(0xef340a98) << 32) | static_cast<uint64_t>(0x172aace5)),
        ((static_cast<uint64_t>(0xb23867fb) << 32) | static_cast<uint64_t>(0x2a35b28e)), ((static_cast<uint64_t>(0x84c8d4df) << 32) | static_cast<uint64_t>(0xd2c63f3b)),
        ((static_cast<uint64_t>(0xc5dd4427) << 32) | static_cast<uint64_t>(0x1ad3cdba)), ((static_cast<uint64_t>(0x936b9fce) << 32) | static_cast<uint64_t>(0xbb25c996)),
        ((static_cast<uint64_t>(0xdbac6c24) << 32) | static_cast<uint64_t>(0x7d62a584)), ((static_cast<uint64_t>(0xa3ab6658) << 32) | static_cast<uint64_t>(0x0d5fdaf6)),
        ((static_cast<uint64_t>(0xf3e2f893) << 32) | static_cast<uint64_t>(0xdec3f126)), ((static_cast<uint64_t>(0xb5b5ada8) << 32) | static_cast<uint64_t>(0xaaff80b8)),
        ((static_cast<uint64_t>(0x87625f05) << 32) | static_cast<uint64_t>(0x6c7c4a8b)), ((static_cast<uint64_t>(0xc9bcff60) << 32) | static_cast<uint64_t>(0x34c13053)),
        ((static_cast<uint64_t>(0x964e858c) << 32) | static_cast<uint64_t>(0x91ba2655)), ((static_cast<uint64_t>(0xdff97724) << 32) | static_cast<uint64_t>(0x70297ebd)),
        ((static_cast<uint64_t>(0xa6dfbd9f) << 32) | static_cast<uint64_t>(0xb8e5b88f)), ((static_cast<uint64_t>(0xf8a95fcf) << 32) | static_cast<uint64_t>(0x88747d94)),
        ((static_cast<uint64_t>(0xb9447093) << 32) | static_cast<uint64_t>(0x8fa89bcf)), ((static_cast<uint64_t>(0x8a08f0f8) << 32) | static_cast<uint64_t>(0xbf0f156b)),
        ((static_cast<uint64_t>(0xcdb02555) << 32) | static_cast<uint64_t>(0x653131b6)), ((static_cast<uint64_t>(0x993fe2c6) << 32) | static_cast<uint64_t>(0xd07b7fac)),
        ((static_cast<uint64_t>(0xe45c10c4) << 32) | static_cast<uint64_t>(0x2a2b3b06)), ((static_cast<uint64_t>(0xaa242499) << 32) | static_cast<uint64_t>(0x697392d3)),
        ((static_cast<uint64_t>(0xfd87b5f2) << 32) | static_cast<uint64_t>(0x8300ca0e)), ((static_cast<uint64_t>(0xbce50864) << 32) | static_cast<uint64_t>(0x92111aeb)),
        ((static_cast<uint64_t>(0x8cbccc09) << 32) | static_cast<uint64_t>(0x6f5088cc)), ((static_cast<uint64_t>(0xd1b71758) << 32) | static_cast<uint64_t>(0xe219652c)),
        ((static_cast<uint64_t>(0x9c400000) << 32) | static_cast<uint64_t>(0x00000000)), ((static_cast<uint64_t>(0xe8d4a510) << 32) | static_cast<uint64_t>(0x00000000)),
        ((static_cast<uint64_t>(0xad78ebc5) << 32) | static_cast<uint64_t>(0xac620000)), ((static_cast<uint64_t>(0x813f3978) << 32) | static_cast<uint64_t>(0xf8940984)),
        ((static_cast<uint64_t>(0xc097ce7b) << 32) | static_cast<uint64_t>(0xc90715b3)), ((static_cast<uint64_t>(0x8f7e32ce) << 32) | static_cast<uint64_t>(0x7bea5c70)),
        ((static_cast<uint64_t>(0xd5d238a4) << 32) | static_cast<uint64_t>(0xabe98068)), ((static_cast<uint64_t>(0x9f4f2726) << 32) | static_cast<uint64_t>(0x179a2245)),
        ((static_cast<uint64_t>(0xed63a231) << 32) | static_cast<uint64_t>(0xd4c4fb27)), ((static_cast<uint64_t>(0xb0de6538) << 32) | static_cast<uint64_t>(0x8cc8ada8)),
        ((static_cast<uint64_t>(0x83c7088e) << 32) | static_cast<uint64_t>(0x1aab65db)), ((static_cast<uint64_t>(0xc45d1df9) << 32) | static_cast<uint64_t>(0x42711d9a)),
        ((static_cast<uint64_t>(0x924d692c) << 32) | static_cast<uint64_t>(0xa61be758)), ((static_cast<uint64_t>(0xda01ee64) << 32) | static_cast<uint64_t>(0x1a708dea)),
        ((static_cast<uint64_t>(0xa26da399) << 32) | static_cast<uint64_t>(0x9aef774a)), ((static_cast<uint64_t>(0xf209787b) << 32) | static_cast<uint64_t>(0xb47d6b85)),
        ((static_cast<uint64_t>(0xb454e4a1) << 32) | static_cast<uint64_t>(0x79dd1877)), ((static_cast<uint64_t>(0x865b8692) << 32) | static_cast<uint64_t>(0x5b9bc5c2)),
        ((static_cast<uint64_t>(0xc83553c5) << 32) | static_cast<uint64_t>(0xc8965d3d)), ((static_cast<uint64_t>(0x952ab45c) << 32) | static_cast<uint64_t>(0xfa97a0b3)),
        ((static_cast<uint64_t>(0xde469fbd) << 32) | static_cast<uint64_t>(0x99a05fe3)), ((static_cast<uint64_t>(0xa59bc234) << 32) | static_cast<uint64_t>(0xdb398c25)),
        ((static_cast<uint64_t>(0xf6c69a72) << 32) | static_cast<uint64_t>(0xa3989f5c)), ((static_cast<uint64_t>(0xb7dcbf53) << 32) | static_cast<uint64_t>(0x54e9bece)),
        ((static_cast<uint64_t>(0x88fcf317) << 32) | static_cast<uint64_t>(0xf22241e2)), ((static_cast<uint64_t>(0xcc20ce9b) << 32) | static_cast<uint64_t>(0xd35c78a5)),
        ((static_cast<uint64_t>(0x98165af3) << 32) | static_cast<uint64_t>(0x7b2153df)), ((static_cast<uint64_t>(0xe2a0b5dc) << 32) | static_cast<uint64_t>(0x971f303a)),
        ((static_cast<uint64_t>(0xa8d9d153) << 32) | static_cast<uint64_t>(0x5ce3b396)), ((static_cast<uint64_t>(0xfb9b7cd9) << 32) | static_cast<uint64_t>(0xa4a7443c)),
        ((static_cast<uint64_t>(0xbb764c4c) << 32) | static_cast<uint64_t>(0xa7a44410)), ((static_cast<uint64_t>(0x8bab8eef) << 32) | static_cast<uint64_t>(0xb6409c1a)),
        ((static_cast<uint64_t>(0xd01fef10) << 32) | static_cast<uint64_t>(0xa657842c)), ((static_cast<uint64_t>(0x9b10a4e5) << 32) | static_cast<uint64_t>(0xe9913129)),
        ((static_cast<uint64_t>(0xe7109bfb) << 32) | static_cast<uint64_t>(0xa19c0c9d)), ((static_cast<uint64_t>(0xac2820d9) << 32) | static_cast<uint64_t>(0x623bf429)),
        ((static_cast<uint64_t>(0x80444b5e) << 32) | static_cast<uint64_t>(0x7aa7cf85)), ((static_cast<uint64_t>(0xbf21e440) << 32) | static_cast<uint64_t>(0x03acdd2d)),
        ((static_cast<uint64_t>(0x8e679c2f) << 32) | static_cast<uint64_t>(0x5e44ff8f)), ((static_cast<uint64_t>(0xd433179d) << 32) | static_cast<uint64_t>(0x9c8cb841)),
        ((static_cast<uint64_t>(0x9e19db92) << 32) | static_cast<uint64_t>(0xb4e31ba9)), ((static_cast<uint64_t>(0xeb96bf6e) << 32) | static_cast<uint64_t>(0xbadf77d9)),
        ((static_cast<uint64_t>(0xaf87023b) << 32) | static_cast<uint64_t>(0x9bf0ee6b))
    };
    static const int16_t kCachedPowers_E[] = {
        -1220, -1193, -1166, -1140, -1113, -1087, -1060, -1034, -1007, -980,
        -954, -927, -901, -874, -847, -821, -794, -768, -741, -715,
        -688, -661, -635, -608, -582, -555, -529, -502, -475, -449,
        -422, -396, -369, -343, -316, -289, -263, -236, -210, -183,
        -157, -130, -103, -77, -50, -24, 3, 30, 56, 83,
        109, 136, 162, 189, 216, 242, 269, 295, 322, 348,
        375, 402, 428, 455, 481, 508, 534, 561, 588, 614,
        641, 667, 694, 720, 747, 774, 800, 827, 853, 880,
        907, 933, 960, 986, 1013, 1039, 1066
    };
    return DiyFp(kCachedPowers_F[index], kCachedPowers_E[index]);
}
inline DiyFp GetCachedPower(int e, int* K) {
    double dk = (-61 - e) * 0.30102999566398114 + 347;
    int k = static_cast<int>(dk);
    if (k != dk)
        k++;
    unsigned index = static_cast<unsigned>((k >> 3) + 1);
    *K = -(-348 + static_cast<int>(index << 3));
    return GetCachedPowerByIndex(index);
}
inline DiyFp GetCachedPower10(int exp, int *outExp) {
     unsigned index = (exp + 348) / 8;
     *outExp = -348 + index * 8;
     return GetCachedPowerByIndex(index);
 }

#pragma GCC diagnostic pop

}
}
namespace rapidjson {
namespace internal {
inline double Pow10(int n) {
    static const double e[] = {
        1e+0,
        1e+1, 1e+2, 1e+3, 1e+4, 1e+5, 1e+6, 1e+7, 1e+8, 1e+9, 1e+10, 1e+11, 1e+12, 1e+13, 1e+14, 1e+15, 1e+16, 1e+17, 1e+18, 1e+19, 1e+20,
        1e+21, 1e+22, 1e+23, 1e+24, 1e+25, 1e+26, 1e+27, 1e+28, 1e+29, 1e+30, 1e+31, 1e+32, 1e+33, 1e+34, 1e+35, 1e+36, 1e+37, 1e+38, 1e+39, 1e+40,
        1e+41, 1e+42, 1e+43, 1e+44, 1e+45, 1e+46, 1e+47, 1e+48, 1e+49, 1e+50, 1e+51, 1e+52, 1e+53, 1e+54, 1e+55, 1e+56, 1e+57, 1e+58, 1e+59, 1e+60,
        1e+61, 1e+62, 1e+63, 1e+64, 1e+65, 1e+66, 1e+67, 1e+68, 1e+69, 1e+70, 1e+71, 1e+72, 1e+73, 1e+74, 1e+75, 1e+76, 1e+77, 1e+78, 1e+79, 1e+80,
        1e+81, 1e+82, 1e+83, 1e+84, 1e+85, 1e+86, 1e+87, 1e+88, 1e+89, 1e+90, 1e+91, 1e+92, 1e+93, 1e+94, 1e+95, 1e+96, 1e+97, 1e+98, 1e+99, 1e+100,
        1e+101,1e+102,1e+103,1e+104,1e+105,1e+106,1e+107,1e+108,1e+109,1e+110,1e+111,1e+112,1e+113,1e+114,1e+115,1e+116,1e+117,1e+118,1e+119,1e+120,
        1e+121,1e+122,1e+123,1e+124,1e+125,1e+126,1e+127,1e+128,1e+129,1e+130,1e+131,1e+132,1e+133,1e+134,1e+135,1e+136,1e+137,1e+138,1e+139,1e+140,
        1e+141,1e+142,1e+143,1e+144,1e+145,1e+146,1e+147,1e+148,1e+149,1e+150,1e+151,1e+152,1e+153,1e+154,1e+155,1e+156,1e+157,1e+158,1e+159,1e+160,
        1e+161,1e+162,1e+163,1e+164,1e+165,1e+166,1e+167,1e+168,1e+169,1e+170,1e+171,1e+172,1e+173,1e+174,1e+175,1e+176,1e+177,1e+178,1e+179,1e+180,
        1e+181,1e+182,1e+183,1e+184,1e+185,1e+186,1e+187,1e+188,1e+189,1e+190,1e+191,1e+192,1e+193,1e+194,1e+195,1e+196,1e+197,1e+198,1e+199,1e+200,
        1e+201,1e+202,1e+203,1e+204,1e+205,1e+206,1e+207,1e+208,1e+209,1e+210,1e+211,1e+212,1e+213,1e+214,1e+215,1e+216,1e+217,1e+218,1e+219,1e+220,
        1e+221,1e+222,1e+223,1e+224,1e+225,1e+226,1e+227,1e+228,1e+229,1e+230,1e+231,1e+232,1e+233,1e+234,1e+235,1e+236,1e+237,1e+238,1e+239,1e+240,
        1e+241,1e+242,1e+243,1e+244,1e+245,1e+246,1e+247,1e+248,1e+249,1e+250,1e+251,1e+252,1e+253,1e+254,1e+255,1e+256,1e+257,1e+258,1e+259,1e+260,
        1e+261,1e+262,1e+263,1e+264,1e+265,1e+266,1e+267,1e+268,1e+269,1e+270,1e+271,1e+272,1e+273,1e+274,1e+275,1e+276,1e+277,1e+278,1e+279,1e+280,
        1e+281,1e+282,1e+283,1e+284,1e+285,1e+286,1e+287,1e+288,1e+289,1e+290,1e+291,1e+292,1e+293,1e+294,1e+295,1e+296,1e+297,1e+298,1e+299,1e+300,
        1e+301,1e+302,1e+303,1e+304,1e+305,1e+306,1e+307,1e+308
    };
    ((n >= 0 && n <= 308) ? static_cast<void> (0) : __assert_fail ("n >= 0 && n <= 308", "aapt/rapidjson/internal/pow10.h", 52, __PRETTY_FUNCTION__));
    return e[n];
}
}
}
namespace rapidjson {
namespace internal {
inline double FastPath(double significand, int exp) {
    if (exp < -308)
        return 0.0;
    else if (exp >= 0)
        return significand * internal::Pow10(exp);
    else
        return significand / internal::Pow10(-exp);
}
inline double StrtodNormalPrecision(double d, int p) {
    if (p < -308) {
        d = FastPath(d, -308);
        d = FastPath(d, p + 308);
    }
    else
        d = FastPath(d, p);
    return d;
}
template <typename T>
inline T Min3(T a, T b, T c) {
    T m = a;
    if (m > b) m = b;
    if (m > c) m = c;
    return m;
}
inline int CheckWithinHalfULP(double b, const BigInteger& d, int dExp, bool* adjustToNegative) {
    const Double db(b);
    const uint64_t bInt = db.IntegerSignificand();
    const int bExp = db.IntegerExponent();
    const int hExp = bExp - 1;
    int dS_Exp2 = 0, dS_Exp5 = 0, bS_Exp2 = 0, bS_Exp5 = 0, hS_Exp2 = 0, hS_Exp5 = 0;
    if (dExp >= 0) {
        dS_Exp2 += dExp;
        dS_Exp5 += dExp;
    }
    else {
        bS_Exp2 -= dExp;
        bS_Exp5 -= dExp;
        hS_Exp2 -= dExp;
        hS_Exp5 -= dExp;
    }
    if (bExp >= 0)
        bS_Exp2 += bExp;
    else {
        dS_Exp2 -= bExp;
        hS_Exp2 -= bExp;
    }
    if (hExp >= 0)
        hS_Exp2 += hExp;
    else {
        dS_Exp2 -= hExp;
        bS_Exp2 -= hExp;
    }
    int common_Exp2 = Min3(dS_Exp2, bS_Exp2, hS_Exp2);
    dS_Exp2 -= common_Exp2;
    bS_Exp2 -= common_Exp2;
    hS_Exp2 -= common_Exp2;
    BigInteger dS = d;
    dS.MultiplyPow5(dS_Exp5) <<= dS_Exp2;
    BigInteger bS(bInt);
    bS.MultiplyPow5(bS_Exp5) <<= bS_Exp2;
    BigInteger hS(1);
    hS.MultiplyPow5(hS_Exp5) <<= hS_Exp2;
    BigInteger delta(0);
    *adjustToNegative = dS.Difference(bS, &delta);
    int cmp = delta.Compare(hS);
    if (cmp < 0 && *adjustToNegative &&
        db.IsNormal() && (bInt & (bInt - 1)) == 0 &&
        db.Uint64Value() != ((static_cast<uint64_t>(0x00100000) << 32) | static_cast<uint64_t>(0x00000000)))
    {
        delta <<= 1;
        return delta.Compare(hS);
    }
    return cmp;
}
inline bool StrtodFast(double d, int p, double* result) {
    if (p > 22 && p < 22 + 16) {
        d *= internal::Pow10(p - 22);
        p = 22;
    }
    if (p >= -22 && p <= 22 && d <= 9007199254740991.0) {
        *result = FastPath(d, p);
        return true;
    }
    else
        return false;
}
inline bool StrtodDiyFp(const char* decimals, size_t length, size_t decimalPosition, int exp, double* result) {
    uint64_t significand = 0;
    size_t i = 0;
    for (; i < length; i++) {
        if (significand > ((static_cast<uint64_t>(0x19999999) << 32) | static_cast<uint64_t>(0x99999999)) ||
            (significand == ((static_cast<uint64_t>(0x19999999) << 32) | static_cast<uint64_t>(0x99999999)) && decimals[i] > '5'))
            break;
        significand = significand * 10 + (decimals[i] - '0');
    }
    if (i < length && decimals[i] >= '5')
        significand++;
    size_t remaining = length - i;
    const unsigned kUlpShift = 3;
    const unsigned kUlp = 1 << kUlpShift;
    int error = (remaining == 0) ? 0 : kUlp / 2;
    DiyFp v(significand, 0);
    v = v.Normalize();
    error <<= -v.e;
    const int dExp = (int)decimalPosition - (int)i + exp;
    int actualExp;
    DiyFp cachedPower = GetCachedPower10(dExp, &actualExp);
    if (actualExp != dExp) {
        static const DiyFp kPow10[] = {
            DiyFp(((static_cast<uint64_t>(0xa0000000) << 32) | static_cast<uint64_t>(00000000)), -60),
            DiyFp(((static_cast<uint64_t>(0xc8000000) << 32) | static_cast<uint64_t>(00000000)), -57),
            DiyFp(((static_cast<uint64_t>(0xfa000000) << 32) | static_cast<uint64_t>(00000000)), -54),
            DiyFp(((static_cast<uint64_t>(0x9c400000) << 32) | static_cast<uint64_t>(00000000)), -50),
            DiyFp(((static_cast<uint64_t>(0xc3500000) << 32) | static_cast<uint64_t>(00000000)), -47),
            DiyFp(((static_cast<uint64_t>(0xf4240000) << 32) | static_cast<uint64_t>(00000000)), -44),
            DiyFp(((static_cast<uint64_t>(0x98968000) << 32) | static_cast<uint64_t>(00000000)), -40)
        };
        int adjustment = dExp - actualExp - 1;
        ((adjustment >= 0 && adjustment < 7) ? static_cast<void> (0) : __assert_fail ("adjustment >= 0 && adjustment < 7", "aapt/rapidjson/internal/strtod.h", 183, __PRETTY_FUNCTION__));
        v = v * kPow10[adjustment];
        if (length + adjustment > 19)
            error += kUlp / 2;
    }
    v = v * cachedPower;
    error += kUlp + (error == 0 ? 0 : 1);
    const int oldExp = v.e;
    v = v.Normalize();
    error <<= oldExp - v.e;
    const unsigned effectiveSignificandSize = Double::EffectiveSignificandSize(64 + v.e);
    unsigned precisionSize = 64 - effectiveSignificandSize;
    if (precisionSize + kUlpShift >= 64) {
        unsigned scaleExp = (precisionSize + kUlpShift) - 63;
        v.f >>= scaleExp;
        v.e += scaleExp;
        error = (error >> scaleExp) + 1 + kUlp;
        precisionSize -= scaleExp;
    }
    DiyFp rounded(v.f >> precisionSize, v.e + precisionSize);
    const uint64_t precisionBits = (v.f & ((uint64_t(1) << precisionSize) - 1)) * kUlp;
    const uint64_t halfWay = (uint64_t(1) << (precisionSize - 1)) * kUlp;
    if (precisionBits >= halfWay + error)
        rounded.f++;
    *result = rounded.ToDouble();
    return halfWay - error >= precisionBits || precisionBits >= halfWay + error;
}
inline double StrtodBigInteger(double approx, const char* decimals, size_t length, size_t decimalPosition, int exp) {
    const BigInteger dInt(decimals, length);
    const int dExp = (int)decimalPosition - (int)length + exp;
    Double a(approx);
    for (int i = 0; i < 10; i++) {
        bool adjustToNegative;
        int cmp = CheckWithinHalfULP(a.Value(), dInt, dExp, &adjustToNegative);
        if (cmp < 0)
            return a.Value();
        else if (cmp == 0) {
            if (a.Significand() & 1)
                return adjustToNegative ? a.PreviousPositiveDouble() : a.NextPositiveDouble();
            else
                return a.Value();
        }
        else
            a = adjustToNegative ? a.PreviousPositiveDouble() : a.NextPositiveDouble();
    }
    return a.Value();
}
inline double StrtodFullPrecision(double d, int p, const char* decimals, size_t length, size_t decimalPosition, int exp) {
    ((d >= 0.0) ? static_cast<void> (0) : __assert_fail ("d >= 0.0", "aapt/rapidjson/internal/strtod.h", 243, __PRETTY_FUNCTION__));
    ((length >= 1) ? static_cast<void> (0) : __assert_fail ("length >= 1", "aapt/rapidjson/internal/strtod.h", 244, __PRETTY_FUNCTION__));
    double result;
    if (StrtodFast(d, p, &result))
        return result;
    while (*decimals == '0' && length > 1) {
        length--;
        decimals++;
        decimalPosition--;
    }
    while (decimals[length - 1] == '0' && length > 1) {
        length--;
        decimalPosition--;
        exp++;
    }
    const int kMaxDecimalDigit = 780;
    if ((int)length > kMaxDecimalDigit) {
        exp += (int(length) - kMaxDecimalDigit);
        length = kMaxDecimalDigit;
    }
    if (int(length) + exp < -324)
        return 0.0;
    if (StrtodDiyFp(decimals, length, decimalPosition, exp, &result))
        return result;
    return StrtodBigInteger(result, decimals, length, decimalPosition, exp);
}
}
}

#pragma GCC diagnostic push


#pragma GCC diagnostic ignored "-Weffc++"

namespace rapidjson {
enum ParseErrorCode {
    kParseErrorNone = 0,
    kParseErrorDocumentEmpty,
    kParseErrorDocumentRootNotSingular,
    kParseErrorValueInvalid,
    kParseErrorObjectMissName,
    kParseErrorObjectMissColon,
    kParseErrorObjectMissCommaOrCurlyBracket,
    kParseErrorArrayMissCommaOrSquareBracket,
    kParseErrorStringUnicodeEscapeInvalidHex,
    kParseErrorStringUnicodeSurrogateInvalid,
    kParseErrorStringEscapeInvalid,
    kParseErrorStringMissQuotationMark,
    kParseErrorStringInvalidEncoding,
    kParseErrorNumberTooBig,
    kParseErrorNumberMissFraction,
    kParseErrorNumberMissExponent,
    kParseErrorTermination,
    kParseErrorUnspecificSyntaxError,
};
struct ParseResult {
    ParseResult() : code_(kParseErrorNone), offset_(0) {}
    ParseResult(ParseErrorCode code, size_t offset) : code_(code), offset_(offset) {}
    ParseErrorCode Code() const { return code_; }
    size_t Offset() const { return offset_; }
    operator bool() const { return !IsError(); }
    bool IsError() const { return code_ != kParseErrorNone; }
    bool operator==(const ParseResult& that) const { return code_ == that.code_; }
    bool operator==(ParseErrorCode code) const { return code_ == code; }
    friend bool operator==(ParseErrorCode code, const ParseResult & err) { return code == err.code_; }
    void Clear() { Set(kParseErrorNone); }
    void Set(ParseErrorCode code, size_t offset = 0) { code_ = code; offset_ = offset; }
private:
    ParseErrorCode code_;
    size_t offset_;
};
typedef const char* (*GetParseErrorFunc)(ParseErrorCode);
}
namespace rapidjson {
enum ParseFlag {
    kParseNoFlags = 0,
    kParseInsituFlag = 1,
    kParseValidateEncodingFlag = 2,
    kParseIterativeFlag = 4,
    kParseStopWhenDoneFlag = 8,
    kParseFullPrecisionFlag = 16,
    kParseDefaultFlags = kParseNoFlags
};
template<typename Encoding = UTF8<>, typename Derived = void>
struct BaseReaderHandler {
    typedef typename Encoding::Ch Ch;
    typedef typename internal::SelectIf<internal::IsSame<Derived, void>, BaseReaderHandler, Derived>::Type Override;
    bool Default() { return true; }
    bool Null() { return static_cast<Override&>(*this).Default(); }
    bool Bool(bool) { return static_cast<Override&>(*this).Default(); }
    bool Int(int) { return static_cast<Override&>(*this).Default(); }
    bool Uint(unsigned) { return static_cast<Override&>(*this).Default(); }
    bool Int64(int64_t) { return static_cast<Override&>(*this).Default(); }
    bool Uint64(uint64_t) { return static_cast<Override&>(*this).Default(); }
    bool Double(double) { return static_cast<Override&>(*this).Default(); }
    bool String(const Ch*, SizeType, bool) { return static_cast<Override&>(*this).Default(); }
    bool StartObject() { return static_cast<Override&>(*this).Default(); }
    bool Key(const Ch* str, SizeType len, bool copy) { return static_cast<Override&>(*this).String(str, len, copy); }
    bool EndObject(SizeType) { return static_cast<Override&>(*this).Default(); }
    bool StartArray() { return static_cast<Override&>(*this).Default(); }
    bool EndArray(SizeType) { return static_cast<Override&>(*this).Default(); }
};
namespace internal {
template<typename Stream, int = StreamTraits<Stream>::copyOptimization>
class StreamLocalCopy;
template<typename Stream>
class StreamLocalCopy<Stream, 1> {
public:
    StreamLocalCopy(Stream& original) : s(original), original_(original) {}
    ~StreamLocalCopy() { original_ = s; }
    Stream s;
private:
    StreamLocalCopy& operator=(const StreamLocalCopy&) ;
    Stream& original_;
};
template<typename Stream>
class StreamLocalCopy<Stream, 0> {
public:
    StreamLocalCopy(Stream& original) : s(original) {}
    Stream& s;
private:
    StreamLocalCopy& operator=(const StreamLocalCopy&) ;
};
}
template<typename InputStream>
void SkipWhitespace(InputStream& is) {
    internal::StreamLocalCopy<InputStream> copy(is);
    InputStream& s(copy.s);
    while (s.Peek() == ' ' || s.Peek() == '\n' || s.Peek() == '\r' || s.Peek() == '\t')
        s.Take();
}
template <typename SourceEncoding, typename TargetEncoding, typename StackAllocator = CrtAllocator>
class GenericReader {
public:
    typedef typename SourceEncoding::Ch Ch;
    GenericReader(StackAllocator* stackAllocator = 0, size_t stackCapacity = kDefaultStackCapacity) : stack_(stackAllocator, stackCapacity), parseResult_() {}
    template <unsigned parseFlags, typename InputStream, typename Handler>
    ParseResult Parse(InputStream& is, Handler& handler) {
        if (parseFlags & kParseIterativeFlag)
            return IterativeParse<parseFlags>(is, handler);
        parseResult_.Clear();
        ClearStackOnExit scope(*this);
        SkipWhitespace(is);
        if (is.Peek() == '\0') {
            do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 410, __PRETTY_FUNCTION__)); SetParseError(kParseErrorDocumentEmpty, is.Tell()); } while((void)0, 0);
            do { if (HasParseError()) { return parseResult_; } } while((void)0, 0);
        }
        else {
            ParseValue<parseFlags>(is, handler);
            do { if (HasParseError()) { return parseResult_; } } while((void)0, 0);
            if (!(parseFlags & kParseStopWhenDoneFlag)) {
                SkipWhitespace(is);
                if (is.Peek() != '\0') {
                    do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 421, __PRETTY_FUNCTION__)); SetParseError(kParseErrorDocumentRootNotSingular, is.Tell()); } while((void)0, 0);
                    do { if (HasParseError()) { return parseResult_; } } while((void)0, 0);
                }
            }
        }
        return parseResult_;
    }
    template <typename InputStream, typename Handler>
    ParseResult Parse(InputStream& is, Handler& handler) {
        return Parse<kParseDefaultFlags>(is, handler);
    }
    bool HasParseError() const { return parseResult_.IsError(); }
    ParseErrorCode GetParseErrorCode() const { return parseResult_.Code(); }
    size_t GetErrorOffset() const { return parseResult_.Offset(); }
protected:
    void SetParseError(ParseErrorCode code, size_t offset) { parseResult_.Set(code, offset); }
private:
    GenericReader(const GenericReader&);
    GenericReader& operator=(const GenericReader&);
    void ClearStack() { stack_.Clear(); }
    struct ClearStackOnExit {
        explicit ClearStackOnExit(GenericReader& r) : r_(r) {}
        ~ClearStackOnExit() { r_.ClearStack(); }
    private:
        GenericReader& r_;
        ClearStackOnExit(const ClearStackOnExit&);
        ClearStackOnExit& operator=(const ClearStackOnExit&);
    };
    template<unsigned parseFlags, typename InputStream, typename Handler>
    void ParseObject(InputStream& is, Handler& handler) {
        ((is.Peek() == '{') ? static_cast<void> (0) : __assert_fail ("is.Peek() == '{'", "aapt/rapidjson/reader.h", 474, __PRETTY_FUNCTION__));
        is.Take();
        if (!handler.StartObject())
            do { do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 478, __PRETTY_FUNCTION__)); SetParseError(kParseErrorTermination, is.Tell()); } while((void)0, 0); do { if (HasParseError()) { return ; } } while((void)0, 0); } while((void)0, 0);
        SkipWhitespace(is);
        if (is.Peek() == '}') {
            is.Take();
            if (!handler.EndObject(0))
                do { do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 485, __PRETTY_FUNCTION__)); SetParseError(kParseErrorTermination, is.Tell()); } while((void)0, 0); do { if (HasParseError()) { return ; } } while((void)0, 0); } while((void)0, 0);
            return;
        }
        for (SizeType memberCount = 0;;) {
            if (is.Peek() != '"')
                do { do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 491, __PRETTY_FUNCTION__)); SetParseError(kParseErrorObjectMissName, is.Tell()); } while((void)0, 0); do { if (HasParseError()) { return ; } } while((void)0, 0); } while((void)0, 0);
            ParseString<parseFlags>(is, handler, true);
            do { if (HasParseError()) { return ; } } while((void)0, 0);
            SkipWhitespace(is);
            if (is.Take() != ':')
                do { do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 499, __PRETTY_FUNCTION__)); SetParseError(kParseErrorObjectMissColon, is.Tell()); } while((void)0, 0); do { if (HasParseError()) { return ; } } while((void)0, 0); } while((void)0, 0);
            SkipWhitespace(is);
            ParseValue<parseFlags>(is, handler);
            do { if (HasParseError()) { return ; } } while((void)0, 0);
            SkipWhitespace(is);
            ++memberCount;
            switch (is.Take()) {
                case ',': SkipWhitespace(is); break;
                case '}':
                    if (!handler.EndObject(memberCount))
                        do { do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 514, __PRETTY_FUNCTION__)); SetParseError(kParseErrorTermination, is.Tell()); } while((void)0, 0); do { if (HasParseError()) { return ; } } while((void)0, 0); } while((void)0, 0);
                    else
                        return;
                default: do { do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 517, __PRETTY_FUNCTION__)); SetParseError(kParseErrorObjectMissCommaOrCurlyBracket, is.Tell()); } while((void)0, 0); do { if (HasParseError()) { return ; } } while((void)0, 0); } while((void)0, 0);
            }
        }
    }
    template<unsigned parseFlags, typename InputStream, typename Handler>
    void ParseArray(InputStream& is, Handler& handler) {
        ((is.Peek() == '[') ? static_cast<void> (0) : __assert_fail ("is.Peek() == '['", "aapt/rapidjson/reader.h", 525, __PRETTY_FUNCTION__));
        is.Take();
        if (!handler.StartArray())
            do { do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 529, __PRETTY_FUNCTION__)); SetParseError(kParseErrorTermination, is.Tell()); } while((void)0, 0); do { if (HasParseError()) { return ; } } while((void)0, 0); } while((void)0, 0);
        SkipWhitespace(is);
        if (is.Peek() == ']') {
            is.Take();
            if (!handler.EndArray(0))
                do { do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 536, __PRETTY_FUNCTION__)); SetParseError(kParseErrorTermination, is.Tell()); } while((void)0, 0); do { if (HasParseError()) { return ; } } while((void)0, 0); } while((void)0, 0);
            return;
        }
        for (SizeType elementCount = 0;;) {
            ParseValue<parseFlags>(is, handler);
            do { if (HasParseError()) { return ; } } while((void)0, 0);
            ++elementCount;
            SkipWhitespace(is);
            switch (is.Take()) {
                case ',': SkipWhitespace(is); break;
                case ']':
                    if (!handler.EndArray(elementCount))
                        do { do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 551, __PRETTY_FUNCTION__)); SetParseError(kParseErrorTermination, is.Tell()); } while((void)0, 0); do { if (HasParseError()) { return ; } } while((void)0, 0); } while((void)0, 0);
                    else
                        return;
                default: do { do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 554, __PRETTY_FUNCTION__)); SetParseError(kParseErrorArrayMissCommaOrSquareBracket, is.Tell()); } while((void)0, 0); do { if (HasParseError()) { return ; } } while((void)0, 0); } while((void)0, 0);
            }
        }
    }
    template<unsigned parseFlags, typename InputStream, typename Handler>
    void ParseNull(InputStream& is, Handler& handler) {
        ((is.Peek() == 'n') ? static_cast<void> (0) : __assert_fail ("is.Peek() == 'n'", "aapt/rapidjson/reader.h", 561, __PRETTY_FUNCTION__));
        is.Take();
        if (is.Take() == 'u' && is.Take() == 'l' && is.Take() == 'l') {
            if (!handler.Null())
                do { do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 566, __PRETTY_FUNCTION__)); SetParseError(kParseErrorTermination, is.Tell()); } while((void)0, 0); do { if (HasParseError()) { return ; } } while((void)0, 0); } while((void)0, 0);
        }
        else
            do { do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 569, __PRETTY_FUNCTION__)); SetParseError(kParseErrorValueInvalid, is.Tell() - 1); } while((void)0, 0); do { if (HasParseError()) { return ; } } while((void)0, 0); } while((void)0, 0);
    }
    template<unsigned parseFlags, typename InputStream, typename Handler>
    void ParseTrue(InputStream& is, Handler& handler) {
        ((is.Peek() == 't') ? static_cast<void> (0) : __assert_fail ("is.Peek() == 't'", "aapt/rapidjson/reader.h", 574, __PRETTY_FUNCTION__));
        is.Take();
        if (is.Take() == 'r' && is.Take() == 'u' && is.Take() == 'e') {
            if (!handler.Bool(true))
                do { do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 579, __PRETTY_FUNCTION__)); SetParseError(kParseErrorTermination, is.Tell()); } while((void)0, 0); do { if (HasParseError()) { return ; } } while((void)0, 0); } while((void)0, 0);
        }
        else
            do { do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 582, __PRETTY_FUNCTION__)); SetParseError(kParseErrorValueInvalid, is.Tell() - 1); } while((void)0, 0); do { if (HasParseError()) { return ; } } while((void)0, 0); } while((void)0, 0);
    }
    template<unsigned parseFlags, typename InputStream, typename Handler>
    void ParseFalse(InputStream& is, Handler& handler) {
        ((is.Peek() == 'f') ? static_cast<void> (0) : __assert_fail ("is.Peek() == 'f'", "aapt/rapidjson/reader.h", 587, __PRETTY_FUNCTION__));
        is.Take();
        if (is.Take() == 'a' && is.Take() == 'l' && is.Take() == 's' && is.Take() == 'e') {
            if (!handler.Bool(false))
                do { do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 592, __PRETTY_FUNCTION__)); SetParseError(kParseErrorTermination, is.Tell()); } while((void)0, 0); do { if (HasParseError()) { return ; } } while((void)0, 0); } while((void)0, 0);
        }
        else
            do { do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 595, __PRETTY_FUNCTION__)); SetParseError(kParseErrorValueInvalid, is.Tell() - 1); } while((void)0, 0); do { if (HasParseError()) { return ; } } while((void)0, 0); } while((void)0, 0);
    }
    template<typename InputStream>
    unsigned ParseHex4(InputStream& is) {
        unsigned codepoint = 0;
        for (int i = 0; i < 4; i++) {
            Ch c = is.Take();
            codepoint <<= 4;
            codepoint += static_cast<unsigned>(c);
            if (c >= '0' && c <= '9')
                codepoint -= '0';
            else if (c >= 'A' && c <= 'F')
                codepoint -= 'A' - 10;
            else if (c >= 'a' && c <= 'f')
                codepoint -= 'a' - 10;
            else {
                do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 613, __PRETTY_FUNCTION__)); SetParseError(kParseErrorStringUnicodeEscapeInvalidHex, is.Tell() - 1); } while((void)0, 0);
                do { if (HasParseError()) { return 0; } } while((void)0, 0);
            }
        }
        return codepoint;
    }
    template <typename CharType>
    class StackStream {
    public:
        typedef CharType Ch;
        StackStream(internal::Stack<StackAllocator>& stack) : stack_(stack), length_(0) {}
        __attribute__((always_inline)) void Put(Ch c) {
            *stack_.template Push<Ch>() = c;
            ++length_;
        }
        size_t Length() const { return length_; }
        Ch* Pop() {
            return stack_.template Pop<Ch>(length_);
        }
    private:
        StackStream(const StackStream&);
        StackStream& operator=(const StackStream&);
        internal::Stack<StackAllocator>& stack_;
        SizeType length_;
    };
    template<unsigned parseFlags, typename InputStream, typename Handler>
    void ParseString(InputStream& is, Handler& handler, bool isKey = false) {
        internal::StreamLocalCopy<InputStream> copy(is);
        InputStream& s(copy.s);
        bool success = false;
        if (parseFlags & kParseInsituFlag) {
            typename InputStream::Ch *head = s.PutBegin();
            ParseStringToStream<parseFlags, SourceEncoding, SourceEncoding>(s, s);
            do { if (HasParseError()) { return ; } } while((void)0, 0);
            size_t length = s.PutEnd(head) - 1;
            ((length <= 0xFFFFFFFF) ? static_cast<void> (0) : __assert_fail ("length <= 0xFFFFFFFF", "aapt/rapidjson/reader.h", 655, __PRETTY_FUNCTION__));
            const typename TargetEncoding::Ch* const str = (typename TargetEncoding::Ch*)head;
            success = (isKey ? handler.Key(str, SizeType(length), false) : handler.String(str, SizeType(length), false));
        }
        else {
            StackStream<typename TargetEncoding::Ch> stackStream(stack_);
            ParseStringToStream<parseFlags, SourceEncoding, TargetEncoding>(s, stackStream);
            do { if (HasParseError()) { return ; } } while((void)0, 0);
            SizeType length = static_cast<SizeType>(stackStream.Length()) - 1;
            const typename TargetEncoding::Ch* const str = stackStream.Pop();
            success = (isKey ? handler.Key(str, length, true) : handler.String(str, length, true));
        }
        if (!success)
            do { do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 668, __PRETTY_FUNCTION__)); SetParseError(kParseErrorTermination, s.Tell()); } while((void)0, 0); do { if (HasParseError()) { return ; } } while((void)0, 0); } while((void)0, 0);
    }
    template<unsigned parseFlags, typename SEncoding, typename TEncoding, typename InputStream, typename OutputStream>
    __attribute__((always_inline)) void ParseStringToStream(InputStream& is, OutputStream& os) {
        static const char escape[256] = {
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0,'\"', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'/',
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'\\', 0, 0, 0,
            0, 0,'\b', 0, 0, 0,'\f', 0, 0, 0, 0, 0, 0, 0,'\n', 0,
            0, 0,'\r', 0,'\t', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
        };
        ((is.Peek() == '\"') ? static_cast<void> (0) : __assert_fail ("is.Peek() == '\\\"'", "aapt/rapidjson/reader.h", 687, __PRETTY_FUNCTION__));
        is.Take();
        for (;;) {
            Ch c = is.Peek();
            if (c == '\\') {
                is.Take();
                Ch e = is.Take();
                if ((sizeof(Ch) == 1 || unsigned(e) < 256) && escape[(unsigned char)e]) {
                    os.Put(escape[(unsigned char)e]);
                }
                else if (e == 'u') {
                    unsigned codepoint = ParseHex4(is);
                    if (codepoint >= 0xD800 && codepoint <= 0xDBFF) {
                        if (is.Take() != '\\' || is.Take() != 'u')
                            do { do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 703, __PRETTY_FUNCTION__)); SetParseError(kParseErrorStringUnicodeSurrogateInvalid, is.Tell() - 2); } while((void)0, 0); do { if (HasParseError()) { return ; } } while((void)0, 0); } while((void)0, 0);
                        unsigned codepoint2 = ParseHex4(is);
                        if (codepoint2 < 0xDC00 || codepoint2 > 0xDFFF)
                            do { do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 706, __PRETTY_FUNCTION__)); SetParseError(kParseErrorStringUnicodeSurrogateInvalid, is.Tell() - 2); } while((void)0, 0); do { if (HasParseError()) { return ; } } while((void)0, 0); } while((void)0, 0);
                        codepoint = (((codepoint - 0xD800) << 10) | (codepoint2 - 0xDC00)) + 0x10000;
                    }
                    TEncoding::Encode(os, codepoint);
                }
                else
                    do { do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 712, __PRETTY_FUNCTION__)); SetParseError(kParseErrorStringEscapeInvalid, is.Tell() - 1); } while((void)0, 0); do { if (HasParseError()) { return ; } } while((void)0, 0); } while((void)0, 0);
            }
            else if (c == '"') {
                is.Take();
                os.Put('\0');
                return;
            }
            else if (c == '\0')
                do { do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 720, __PRETTY_FUNCTION__)); SetParseError(kParseErrorStringMissQuotationMark, is.Tell() - 1); } while((void)0, 0); do { if (HasParseError()) { return ; } } while((void)0, 0); } while((void)0, 0);
            else if ((unsigned)c < 0x20)
                do { do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 722, __PRETTY_FUNCTION__)); SetParseError(kParseErrorStringEscapeInvalid, is.Tell() - 1); } while((void)0, 0); do { if (HasParseError()) { return ; } } while((void)0, 0); } while((void)0, 0);
            else {
                if (parseFlags & kParseValidateEncodingFlag ?
                    !Transcoder<SEncoding, TEncoding>::Validate(is, os) :
                    !Transcoder<SEncoding, TEncoding>::Transcode(is, os))
                    do { do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 727, __PRETTY_FUNCTION__)); SetParseError(kParseErrorStringInvalidEncoding, is.Tell()); } while((void)0, 0); do { if (HasParseError()) { return ; } } while((void)0, 0); } while((void)0, 0);
            }
        }
    }
    template<typename InputStream, bool backup>
    class NumberStream {};
    template<typename InputStream>
    class NumberStream<InputStream, false> {
    public:
        NumberStream(GenericReader& reader, InputStream& is) : is(is) { (void)reader; }
        ~NumberStream() {}
        __attribute__((always_inline)) Ch Peek() const { return is.Peek(); }
        __attribute__((always_inline)) Ch TakePush() { return is.Take(); }
        __attribute__((always_inline)) Ch Take() { return is.Take(); }
        size_t Tell() { return is.Tell(); }
        size_t Length() { return 0; }
        const char* Pop() { return 0; }
    protected:
        NumberStream& operator=(const NumberStream&);
        InputStream& is;
    };
    template<typename InputStream>
    class NumberStream<InputStream, true> : public NumberStream<InputStream, false> {
        typedef NumberStream<InputStream, false> Base;
    public:
        NumberStream(GenericReader& reader, InputStream& is) : NumberStream<InputStream, false>(reader, is), stackStream(reader.stack_) {}
        ~NumberStream() {}
        __attribute__((always_inline)) Ch TakePush() {
            stackStream.Put((char)Base::is.Peek());
            return Base::is.Take();
        }
        size_t Length() { return stackStream.Length(); }
        const char* Pop() {
            stackStream.Put('\0');
            return stackStream.Pop();
        }
    private:
        StackStream<char> stackStream;
    };
    template<unsigned parseFlags, typename InputStream, typename Handler>
    void ParseNumber(InputStream& is, Handler& handler) {
        internal::StreamLocalCopy<InputStream> copy(is);
        NumberStream<InputStream, (parseFlags & kParseFullPrecisionFlag) != 0> s(*this, copy.s);
        bool minus = false;
        if (s.Peek() == '-') {
            minus = true;
            s.Take();
        }
        unsigned i = 0;
        uint64_t i64 = 0;
        bool use64bit = false;
        int significandDigit = 0;
        if (s.Peek() == '0') {
            i = 0;
            s.TakePush();
        }
        else if (s.Peek() >= '1' && s.Peek() <= '9') {
            i = static_cast<unsigned>(s.TakePush() - '0');
            if (minus)
                while (s.Peek() >= '0' && s.Peek() <= '9') {
                    if (i >= 214748364) {
                        if (i != 214748364 || s.Peek() > '8') {
                            i64 = i;
                            use64bit = true;
                            break;
                        }
                    }
                    i = i * 10 + static_cast<unsigned>(s.TakePush() - '0');
                    significandDigit++;
                }
            else
                while (s.Peek() >= '0' && s.Peek() <= '9') {
                    if (i >= 429496729) {
                        if (i != 429496729 || s.Peek() > '5') {
                            i64 = i;
                            use64bit = true;
                            break;
                        }
                    }
                    i = i * 10 + static_cast<unsigned>(s.TakePush() - '0');
                    significandDigit++;
                }
        }
        else
            do { do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 827, __PRETTY_FUNCTION__)); SetParseError(kParseErrorValueInvalid, s.Tell()); } while((void)0, 0); do { if (HasParseError()) { return ; } } while((void)0, 0); } while((void)0, 0);
        bool useDouble = false;
        double d = 0.0;
        if (use64bit) {
            if (minus)
                while (s.Peek() >= '0' && s.Peek() <= '9') {
                     if (i64 >= ((static_cast<uint64_t>(0x0CCCCCCC) << 32) | static_cast<uint64_t>(0xCCCCCCCC)))
                        if (i64 != ((static_cast<uint64_t>(0x0CCCCCCC) << 32) | static_cast<uint64_t>(0xCCCCCCCC)) || s.Peek() > '8') {
                            d = i64;
                            useDouble = true;
                            break;
                        }
                    i64 = i64 * 10 + static_cast<unsigned>(s.TakePush() - '0');
                    significandDigit++;
                }
            else
                while (s.Peek() >= '0' && s.Peek() <= '9') {
                    if (i64 >= ((static_cast<uint64_t>(0x19999999) << 32) | static_cast<uint64_t>(0x99999999)))
                        if (i64 != ((static_cast<uint64_t>(0x19999999) << 32) | static_cast<uint64_t>(0x99999999)) || s.Peek() > '5') {
                            d = i64;
                            useDouble = true;
                            break;
                        }
                    i64 = i64 * 10 + static_cast<unsigned>(s.TakePush() - '0');
                    significandDigit++;
                }
        }
        if (useDouble) {
            while (s.Peek() >= '0' && s.Peek() <= '9') {
                if (d >= 1.7976931348623157e307)
                    do { do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 861, __PRETTY_FUNCTION__)); SetParseError(kParseErrorNumberTooBig, s.Tell()); } while((void)0, 0); do { if (HasParseError()) { return ; } } while((void)0, 0); } while((void)0, 0);
                d = d * 10 + (s.TakePush() - '0');
            }
        }
        int expFrac = 0;
        size_t decimalPosition;
        if (s.Peek() == '.') {
            s.Take();
            decimalPosition = s.Length();
            if (!(s.Peek() >= '0' && s.Peek() <= '9'))
                do { do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 874, __PRETTY_FUNCTION__)); SetParseError(kParseErrorNumberMissFraction, s.Tell()); } while((void)0, 0); do { if (HasParseError()) { return ; } } while((void)0, 0); } while((void)0, 0);
            if (!useDouble) {
                if (!use64bit)
                    i64 = i;
                while (s.Peek() >= '0' && s.Peek() <= '9') {
                    if (i64 > ((static_cast<uint64_t>(0x1FFFFF) << 32) | static_cast<uint64_t>(0xFFFFFFFF)))
                        break;
                    else {
                        i64 = i64 * 10 + static_cast<unsigned>(s.TakePush() - '0');
                        --expFrac;
                        if (i64 != 0)
                            significandDigit++;
                    }
                }
                d = (double)i64;
                useDouble = true;
            }
            while (s.Peek() >= '0' && s.Peek() <= '9') {
                if (significandDigit < 17) {
                    d = d * 10.0 + (s.TakePush() - '0');
                    --expFrac;
                    if (d != 0.0)
                        significandDigit++;
                }
                else
                    s.TakePush();
            }
        }
        else
            decimalPosition = s.Length();
        int exp = 0;
        if (s.Peek() == 'e' || s.Peek() == 'E') {
            if (!useDouble) {
                d = use64bit ? i64 : i;
                useDouble = true;
            }
            s.Take();
            bool expMinus = false;
            if (s.Peek() == '+')
                s.Take();
            else if (s.Peek() == '-') {
                s.Take();
                expMinus = true;
            }
            if (s.Peek() >= '0' && s.Peek() <= '9') {
                exp = s.Take() - '0';
                while (s.Peek() >= '0' && s.Peek() <= '9') {
                    exp = exp * 10 + (s.Take() - '0');
                    if (exp > 308 && !expMinus)
                        do { do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 937, __PRETTY_FUNCTION__)); SetParseError(kParseErrorNumberTooBig, s.Tell()); } while((void)0, 0); do { if (HasParseError()) { return ; } } while((void)0, 0); } while((void)0, 0);
                }
            }
            else
                do { do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 941, __PRETTY_FUNCTION__)); SetParseError(kParseErrorNumberMissExponent, s.Tell()); } while((void)0, 0); do { if (HasParseError()) { return ; } } while((void)0, 0); } while((void)0, 0);
            if (expMinus)
                exp = -exp;
        }
        bool cont = true;
        size_t length = s.Length();
        const char* decimal = s.Pop();
        if (useDouble) {
            int p = exp + expFrac;
            if (parseFlags & kParseFullPrecisionFlag)
                d = internal::StrtodFullPrecision(d, p, decimal, length, decimalPosition, exp);
            else
                d = internal::StrtodNormalPrecision(d, p);
            cont = handler.Double(minus ? -d : d);
        }
        else {
            if (use64bit) {
                if (minus)
                    cont = handler.Int64(-(int64_t)i64);
                else
                    cont = handler.Uint64(i64);
            }
            else {
                if (minus)
                    cont = handler.Int(-(int)i);
                else
                    cont = handler.Uint(i);
            }
        }
        if (!cont)
            do { do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 976, __PRETTY_FUNCTION__)); SetParseError(kParseErrorTermination, s.Tell()); } while((void)0, 0); do { if (HasParseError()) { return ; } } while((void)0, 0); } while((void)0, 0);
    }
    template<unsigned parseFlags, typename InputStream, typename Handler>
    void ParseValue(InputStream& is, Handler& handler) {
        switch (is.Peek()) {
            case 'n': ParseNull <parseFlags>(is, handler); break;
            case 't': ParseTrue <parseFlags>(is, handler); break;
            case 'f': ParseFalse <parseFlags>(is, handler); break;
            case '"': ParseString<parseFlags>(is, handler); break;
            case '{': ParseObject<parseFlags>(is, handler); break;
            case '[': ParseArray <parseFlags>(is, handler); break;
            default : ParseNumber<parseFlags>(is, handler);
        }
    }
    enum IterativeParsingState {
        IterativeParsingStartState = 0,
        IterativeParsingFinishState,
        IterativeParsingErrorState,
        IterativeParsingObjectInitialState,
        IterativeParsingMemberKeyState,
        IterativeParsingKeyValueDelimiterState,
        IterativeParsingMemberValueState,
        IterativeParsingMemberDelimiterState,
        IterativeParsingObjectFinishState,
        IterativeParsingArrayInitialState,
        IterativeParsingElementState,
        IterativeParsingElementDelimiterState,
        IterativeParsingArrayFinishState,
        IterativeParsingValueState,
        cIterativeParsingStateCount
    };
    enum Token {
        LeftBracketToken = 0,
        RightBracketToken,
        LeftCurlyBracketToken,
        RightCurlyBracketToken,
        CommaToken,
        ColonToken,
        StringToken,
        FalseToken,
        TrueToken,
        NullToken,
        NumberToken,
        kTokenCount
    };
    __attribute__((always_inline)) Token Tokenize(Ch c) {
        static const unsigned char tokenMap[256] = {
            NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,
            NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,
            NumberToken, NumberToken, StringToken, NumberToken, NumberToken, NumberToken, NumberToken, NumberToken, NumberToken, NumberToken, NumberToken, NumberToken, CommaToken, NumberToken, NumberToken, NumberToken,
            NumberToken, NumberToken, NumberToken, NumberToken, NumberToken, NumberToken, NumberToken, NumberToken, NumberToken, NumberToken, ColonToken, NumberToken, NumberToken, NumberToken, NumberToken, NumberToken,
            NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,
            NumberToken, NumberToken, NumberToken, NumberToken, NumberToken, NumberToken, NumberToken, NumberToken, NumberToken, NumberToken, NumberToken, LeftBracketToken, NumberToken, RightBracketToken, NumberToken, NumberToken,
            NumberToken, NumberToken, NumberToken, NumberToken, NumberToken, NumberToken, FalseToken, NumberToken, NumberToken, NumberToken, NumberToken, NumberToken, NumberToken, NumberToken, NullToken, NumberToken,
            NumberToken, NumberToken, NumberToken, NumberToken, TrueToken, NumberToken, NumberToken, NumberToken, NumberToken, NumberToken, NumberToken, LeftCurlyBracketToken, NumberToken, RightCurlyBracketToken, NumberToken, NumberToken,
            NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken, NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken, NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken, NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken, NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken, NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken, NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken, NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken,NumberToken
        };
        if (sizeof(Ch) == 1 || unsigned(c) < 256)
            return (Token)tokenMap[(unsigned char)c];
        else
            return NumberToken;
    }
    __attribute__((always_inline)) IterativeParsingState Predict(IterativeParsingState state, Token token) {
        static const char G[cIterativeParsingStateCount][kTokenCount] = {
            {
                IterativeParsingArrayInitialState,
                IterativeParsingErrorState,
                IterativeParsingObjectInitialState,
                IterativeParsingErrorState,
                IterativeParsingErrorState,
                IterativeParsingErrorState,
                IterativeParsingValueState,
                IterativeParsingValueState,
                IterativeParsingValueState,
                IterativeParsingValueState,
                IterativeParsingValueState
            },
            {
                IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState,
                IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState,
                IterativeParsingErrorState
            },
            {
                IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState,
                IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState,
                IterativeParsingErrorState
            },
            {
                IterativeParsingErrorState,
                IterativeParsingErrorState,
                IterativeParsingErrorState,
                IterativeParsingObjectFinishState,
                IterativeParsingErrorState,
                IterativeParsingErrorState,
                IterativeParsingMemberKeyState,
                IterativeParsingErrorState,
                IterativeParsingErrorState,
                IterativeParsingErrorState,
                IterativeParsingErrorState
            },
            {
                IterativeParsingErrorState,
                IterativeParsingErrorState,
                IterativeParsingErrorState,
                IterativeParsingErrorState,
                IterativeParsingErrorState,
                IterativeParsingKeyValueDelimiterState,
                IterativeParsingErrorState,
                IterativeParsingErrorState,
                IterativeParsingErrorState,
                IterativeParsingErrorState,
                IterativeParsingErrorState
            },
            {
                IterativeParsingArrayInitialState,
                IterativeParsingErrorState,
                IterativeParsingObjectInitialState,
                IterativeParsingErrorState,
                IterativeParsingErrorState,
                IterativeParsingErrorState,
                IterativeParsingMemberValueState,
                IterativeParsingMemberValueState,
                IterativeParsingMemberValueState,
                IterativeParsingMemberValueState,
                IterativeParsingMemberValueState
            },
            {
                IterativeParsingErrorState,
                IterativeParsingErrorState,
                IterativeParsingErrorState,
                IterativeParsingObjectFinishState,
                IterativeParsingMemberDelimiterState,
                IterativeParsingErrorState,
                IterativeParsingErrorState,
                IterativeParsingErrorState,
                IterativeParsingErrorState,
                IterativeParsingErrorState,
                IterativeParsingErrorState
            },
            {
                IterativeParsingErrorState,
                IterativeParsingErrorState,
                IterativeParsingErrorState,
                IterativeParsingErrorState,
                IterativeParsingErrorState,
                IterativeParsingErrorState,
                IterativeParsingMemberKeyState,
                IterativeParsingErrorState,
                IterativeParsingErrorState,
                IterativeParsingErrorState,
                IterativeParsingErrorState
            },
            {
                IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState,
                IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState,
                IterativeParsingErrorState
            },
            {
                IterativeParsingArrayInitialState,
                IterativeParsingArrayFinishState,
                IterativeParsingObjectInitialState,
                IterativeParsingErrorState,
                IterativeParsingErrorState,
                IterativeParsingErrorState,
                IterativeParsingElementState,
                IterativeParsingElementState,
                IterativeParsingElementState,
                IterativeParsingElementState,
                IterativeParsingElementState
            },
            {
                IterativeParsingErrorState,
                IterativeParsingArrayFinishState,
                IterativeParsingErrorState,
                IterativeParsingErrorState,
                IterativeParsingElementDelimiterState,
                IterativeParsingErrorState,
                IterativeParsingErrorState,
                IterativeParsingErrorState,
                IterativeParsingErrorState,
                IterativeParsingErrorState,
                IterativeParsingErrorState
            },
            {
                IterativeParsingArrayInitialState,
                IterativeParsingErrorState,
                IterativeParsingObjectInitialState,
                IterativeParsingErrorState,
                IterativeParsingErrorState,
                IterativeParsingErrorState,
                IterativeParsingElementState,
                IterativeParsingElementState,
                IterativeParsingElementState,
                IterativeParsingElementState,
                IterativeParsingElementState
            },
            {
                IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState,
                IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState,
                IterativeParsingErrorState
            },
            {
                IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState,
                IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState, IterativeParsingErrorState,
                IterativeParsingErrorState
            }
        };
        return (IterativeParsingState)G[state][token];
    }
    template <unsigned parseFlags, typename InputStream, typename Handler>
    __attribute__((always_inline)) IterativeParsingState Transit(IterativeParsingState src, Token token, IterativeParsingState dst, InputStream& is, Handler& handler) {
        switch (dst) {
        case IterativeParsingStartState:
            ((false) ? static_cast<void> (0) : __assert_fail ("false", "aapt/rapidjson/reader.h", 1238, __PRETTY_FUNCTION__));
            return IterativeParsingErrorState;
        case IterativeParsingFinishState:
            return dst;
        case IterativeParsingErrorState:
            return dst;
        case IterativeParsingObjectInitialState:
        case IterativeParsingArrayInitialState:
        {
            IterativeParsingState n = src;
            if (src == IterativeParsingArrayInitialState || src == IterativeParsingElementDelimiterState)
                n = IterativeParsingElementState;
            else if (src == IterativeParsingKeyValueDelimiterState)
                n = IterativeParsingMemberValueState;
            *stack_.template Push<SizeType>(1) = n;
            *stack_.template Push<SizeType>(1) = 0;
            bool hr = (dst == IterativeParsingObjectInitialState) ? handler.StartObject() : handler.StartArray();
            if (!hr) {
                do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 1265, __PRETTY_FUNCTION__)); SetParseError(kParseErrorTermination, is.Tell()); } while((void)0, 0);
                return IterativeParsingErrorState;
            }
            else {
                is.Take();
                return dst;
            }
        }
        case IterativeParsingMemberKeyState:
            ParseString<parseFlags>(is, handler, true);
            if (HasParseError())
                return IterativeParsingErrorState;
            else
                return dst;
        case IterativeParsingKeyValueDelimiterState:
            if (token == ColonToken) {
                is.Take();
                return dst;
            }
            else
                return IterativeParsingErrorState;
        case IterativeParsingMemberValueState:
            ParseValue<parseFlags>(is, handler);
            if (HasParseError()) {
                return IterativeParsingErrorState;
            }
            return dst;
        case IterativeParsingElementState:
            ParseValue<parseFlags>(is, handler);
            if (HasParseError()) {
                return IterativeParsingErrorState;
            }
            return dst;
        case IterativeParsingMemberDelimiterState:
        case IterativeParsingElementDelimiterState:
            is.Take();
            *stack_.template Top<SizeType>() = *stack_.template Top<SizeType>() + 1;
            return dst;
        case IterativeParsingObjectFinishState:
        {
            SizeType c = *stack_.template Pop<SizeType>(1);
            if (src == IterativeParsingMemberValueState)
                ++c;
            IterativeParsingState n = static_cast<IterativeParsingState>(*stack_.template Pop<SizeType>(1));
            if (n == IterativeParsingStartState)
                n = IterativeParsingFinishState;
            bool hr = handler.EndObject(c);
            if (!hr) {
                do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 1328, __PRETTY_FUNCTION__)); SetParseError(kParseErrorTermination, is.Tell()); } while((void)0, 0);
                return IterativeParsingErrorState;
            }
            else {
                is.Take();
                return n;
            }
        }
        case IterativeParsingArrayFinishState:
        {
            SizeType c = *stack_.template Pop<SizeType>(1);
            if (src == IterativeParsingElementState)
                ++c;
            IterativeParsingState n = static_cast<IterativeParsingState>(*stack_.template Pop<SizeType>(1));
            if (n == IterativeParsingStartState)
                n = IterativeParsingFinishState;
            bool hr = handler.EndArray(c);
            if (!hr) {
                do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 1353, __PRETTY_FUNCTION__)); SetParseError(kParseErrorTermination, is.Tell()); } while((void)0, 0);
                return IterativeParsingErrorState;
            }
            else {
                is.Take();
                return n;
            }
        }
        case IterativeParsingValueState:
            ParseValue<parseFlags>(is, handler);
            if (HasParseError()) {
                return IterativeParsingErrorState;
            }
            return IterativeParsingFinishState;
        default:
            ((false) ? static_cast<void> (0) : __assert_fail ("false", "aapt/rapidjson/reader.h", 1371, __PRETTY_FUNCTION__));
            return IterativeParsingErrorState;
        }
    }
    template <typename InputStream>
    void HandleError(IterativeParsingState src, InputStream& is) {
        if (HasParseError()) {
            return;
        }
        switch (src) {
        case IterativeParsingStartState: do { do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 1384, __PRETTY_FUNCTION__)); SetParseError(kParseErrorDocumentEmpty, is.Tell()); } while((void)0, 0); do { if (HasParseError()) { return ; } } while((void)0, 0); } while((void)0, 0);
        case IterativeParsingFinishState: do { do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 1385, __PRETTY_FUNCTION__)); SetParseError(kParseErrorDocumentRootNotSingular, is.Tell()); } while((void)0, 0); do { if (HasParseError()) { return ; } } while((void)0, 0); } while((void)0, 0);
        case IterativeParsingObjectInitialState:
        case IterativeParsingMemberDelimiterState: do { do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 1387, __PRETTY_FUNCTION__)); SetParseError(kParseErrorObjectMissName, is.Tell()); } while((void)0, 0); do { if (HasParseError()) { return ; } } while((void)0, 0); } while((void)0, 0);
        case IterativeParsingMemberKeyState: do { do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 1388, __PRETTY_FUNCTION__)); SetParseError(kParseErrorObjectMissColon, is.Tell()); } while((void)0, 0); do { if (HasParseError()) { return ; } } while((void)0, 0); } while((void)0, 0);
        case IterativeParsingMemberValueState: do { do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 1389, __PRETTY_FUNCTION__)); SetParseError(kParseErrorObjectMissCommaOrCurlyBracket, is.Tell()); } while((void)0, 0); do { if (HasParseError()) { return ; } } while((void)0, 0); } while((void)0, 0);
        case IterativeParsingElementState: do { do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 1390, __PRETTY_FUNCTION__)); SetParseError(kParseErrorArrayMissCommaOrSquareBracket, is.Tell()); } while((void)0, 0); do { if (HasParseError()) { return ; } } while((void)0, 0); } while((void)0, 0);
        default: do { do { ((!HasParseError()) ? static_cast<void> (0) : __assert_fail ("!HasParseError()", "aapt/rapidjson/reader.h", 1391, __PRETTY_FUNCTION__)); SetParseError(kParseErrorUnspecificSyntaxError, is.Tell()); } while((void)0, 0); do { if (HasParseError()) { return ; } } while((void)0, 0); } while((void)0, 0);
        }
    }
    template <unsigned parseFlags, typename InputStream, typename Handler>
    ParseResult IterativeParse(InputStream& is, Handler& handler) {
        parseResult_.Clear();
        ClearStackOnExit scope(*this);
        IterativeParsingState state = IterativeParsingStartState;
        SkipWhitespace(is);
        while (is.Peek() != '\0') {
            Token t = Tokenize(is.Peek());
            IterativeParsingState n = Predict(state, t);
            IterativeParsingState d = Transit<parseFlags>(state, t, n, is, handler);
            if (d == IterativeParsingErrorState) {
                HandleError(state, is);
                break;
            }
            state = d;
            if ((parseFlags & kParseStopWhenDoneFlag) && state == IterativeParsingFinishState)
                break;
            SkipWhitespace(is);
        }
        if (state != IterativeParsingFinishState)
            HandleError(state, is);
        return parseResult_;
    }
    static const size_t kDefaultStackCapacity = 256;
    internal::Stack<StackAllocator> stack_;
    ParseResult parseResult_;
};
typedef GenericReader<UTF8<>, UTF8<> > Reader;
}

#pragma GCC diagnostic pop

namespace rapidjson {
namespace internal {
template <typename Ch>
inline SizeType StrLen(const Ch* s) {
    const Ch* p = s;
    while (*p) ++p;
    return SizeType(p - s);
}
}
}
       
       
#pragma GCC visibility push(default)
       
extern "C++" {
namespace std
{
  class exception
  {
  public:
    exception() noexcept { }
    virtual ~exception() noexcept;
    virtual const char* what() const noexcept;
  };
  class bad_exception : public exception
  {
  public:
    bad_exception() noexcept { }
    virtual ~bad_exception() noexcept;
    virtual const char* what() const noexcept;
  };
  typedef void (*terminate_handler) ();
  typedef void (*unexpected_handler) ();
  terminate_handler set_terminate(terminate_handler) noexcept;
  terminate_handler get_terminate() noexcept;
  void terminate() noexcept __attribute__ ((__noreturn__));
  unexpected_handler set_unexpected(unexpected_handler) noexcept;
  unexpected_handler get_unexpected() noexcept;
  void unexpected() __attribute__ ((__noreturn__));
  bool uncaught_exception() noexcept __attribute__ ((__pure__));
}
namespace __gnu_cxx
{

  void __verbose_terminate_handler();

}
}
#pragma GCC visibility pop
#pragma GCC visibility push(default)
extern "C++" {
namespace std
{
  class type_info;
  namespace __exception_ptr
  {
    class exception_ptr;
  }
  using __exception_ptr::exception_ptr;
  exception_ptr current_exception() noexcept;
  void rethrow_exception(exception_ptr) __attribute__ ((__noreturn__));
  namespace __exception_ptr
  {
    class exception_ptr
    {
      void* _M_exception_object;
      explicit exception_ptr(void* __e) noexcept;
      void _M_addref() noexcept;
      void _M_release() noexcept;
      void *_M_get() const noexcept __attribute__ ((__pure__));
      friend exception_ptr std::current_exception() noexcept;
      friend void std::rethrow_exception(exception_ptr);
    public:
      exception_ptr() noexcept;
      exception_ptr(const exception_ptr&) noexcept;
      exception_ptr(nullptr_t) noexcept
      : _M_exception_object(0)
      { }
      exception_ptr(exception_ptr&& __o) noexcept
      : _M_exception_object(__o._M_exception_object)
      { __o._M_exception_object = 0; }
      exception_ptr&
      operator=(const exception_ptr&) noexcept;
      exception_ptr&
      operator=(exception_ptr&& __o) noexcept
      {
        exception_ptr(static_cast<exception_ptr&&>(__o)).swap(*this);
        return *this;
      }
      ~exception_ptr() noexcept;
      void
      swap(exception_ptr&) noexcept;
      explicit operator bool() const
      { return _M_exception_object; }
      friend bool
      operator==(const exception_ptr&, const exception_ptr&)
 noexcept __attribute__ ((__pure__));
      const class std::type_info*
      __cxa_exception_type() const noexcept
 __attribute__ ((__pure__));
    };
    bool
    operator==(const exception_ptr&, const exception_ptr&)
      noexcept __attribute__ ((__pure__));
    bool
    operator!=(const exception_ptr&, const exception_ptr&)
      noexcept __attribute__ ((__pure__));
    inline void
    swap(exception_ptr& __lhs, exception_ptr& __rhs)
    { __lhs.swap(__rhs); }
  }
  template<typename _Ex>
    exception_ptr
    make_exception_ptr(_Ex __ex) noexcept
    {
      try
 {
   throw __ex;
 }
      catch(...)
 {
   return current_exception();
 }
    }
  template<typename _Ex>
    exception_ptr
    copy_exception(_Ex __ex) noexcept __attribute__ ((__deprecated__));
  template<typename _Ex>
    exception_ptr
    copy_exception(_Ex __ex) noexcept
    { return std::make_exception_ptr<_Ex>(__ex); }
}
}
#pragma GCC visibility pop
#pragma GCC visibility push(default)
extern "C++" {
namespace std
{
  class nested_exception
  {
    exception_ptr _M_ptr;
  public:
    nested_exception() noexcept : _M_ptr(current_exception()) { }
    nested_exception(const nested_exception&) = default;
    nested_exception& operator=(const nested_exception&) = default;
    virtual ~nested_exception() noexcept;
    void
    rethrow_nested() const __attribute__ ((__noreturn__))
    { rethrow_exception(_M_ptr); }
    exception_ptr
    nested_ptr() const
    { return _M_ptr; }
  };
  template<typename _Except>
    struct _Nested_exception : public _Except, public nested_exception
    {
      explicit _Nested_exception(_Except&& __ex)
      : _Except(static_cast<_Except&&>(__ex))
      { }
    };
  template<typename _Ex>
    struct __get_nested_helper
    {
      static const nested_exception*
      _S_get(const _Ex& __ex)
      { return dynamic_cast<const nested_exception*>(&__ex); }
    };
  template<typename _Ex>
    struct __get_nested_helper<_Ex*>
    {
      static const nested_exception*
      _S_get(const _Ex* __ex)
      { return dynamic_cast<const nested_exception*>(__ex); }
    };
  template<typename _Ex>
    inline const nested_exception*
    __get_nested_exception(const _Ex& __ex)
    { return __get_nested_helper<_Ex>::_S_get(__ex); }
  template<typename _Ex>
    void
    __throw_with_nested(_Ex&&, const nested_exception* = 0)
    __attribute__ ((__noreturn__));
  template<typename _Ex>
    void
    __throw_with_nested(_Ex&&, ...) __attribute__ ((__noreturn__));
  template<typename _Ex>
    inline void
    __throw_with_nested(_Ex&& __ex, const nested_exception*)
    { throw __ex; }
  template<typename _Ex>
    inline void
    __throw_with_nested(_Ex&& __ex, ...)
    { throw _Nested_exception<_Ex>(static_cast<_Ex&&>(__ex)); }
  template<typename _Ex>
    void
    throw_with_nested(_Ex __ex) __attribute__ ((__noreturn__));
  template<typename _Ex>
    inline void
    throw_with_nested(_Ex __ex)
    {
      if (__get_nested_exception(__ex))
        throw __ex;
      __throw_with_nested(static_cast<_Ex&&>(__ex), &__ex);
    }
  template<typename _Ex>
    inline void
    rethrow_if_nested(const _Ex& __ex)
    {
      if (const nested_exception* __nested = __get_nested_exception(__ex))
        __nested->rethrow_nested();
    }
  inline void
  rethrow_if_nested(const nested_exception& __ex)
  { __ex.rethrow_nested(); }
}
}
#pragma GCC visibility pop
#pragma GCC visibility push(default)
extern "C++" {
namespace std
{
  class bad_alloc : public exception
  {
  public:
    bad_alloc() throw() { }
    virtual ~bad_alloc() throw();
    virtual const char* what() const throw();
  };
  class bad_array_new_length : public bad_alloc
  {
  public:
    bad_array_new_length() throw() { };
    virtual ~bad_array_new_length() throw();
    virtual const char* what() const throw();
  };
  struct nothrow_t { };
  extern const nothrow_t nothrow;
  typedef void (*new_handler)();
  new_handler set_new_handler(new_handler) throw();
  new_handler get_new_handler() noexcept;
}
void* operator new(std::size_t)
  __attribute__((__externally_visible__));
void* operator new[](std::size_t)
  __attribute__((__externally_visible__));
void operator delete(void*) noexcept
  __attribute__((__externally_visible__));
void operator delete[](void*) noexcept
  __attribute__((__externally_visible__));
void* operator new(std::size_t, const std::nothrow_t&) noexcept
  __attribute__((__externally_visible__));
void* operator new[](std::size_t, const std::nothrow_t&) noexcept
  __attribute__((__externally_visible__));
void operator delete(void*, const std::nothrow_t&) noexcept
  __attribute__((__externally_visible__));
void operator delete[](void*, const std::nothrow_t&) noexcept
  __attribute__((__externally_visible__));
inline void* operator new(std::size_t, void* __p) noexcept
{ return __p; }
inline void* operator new[](std::size_t, void* __p) noexcept
{ return __p; }
inline void operator delete (void*, void*) noexcept { }
inline void operator delete[](void*, void*) noexcept { }
}
#pragma GCC visibility pop

#pragma GCC diagnostic push


#pragma GCC diagnostic ignored "-Weffc++"

       
       
       
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename>
    class allocator;
  template<>
    class allocator<void>;
  template<typename, typename>
    struct uses_allocator;

}
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<class _CharT>
    struct char_traits;
  template<typename _CharT, typename _Traits = char_traits<_CharT>,
           typename _Alloc = allocator<_CharT> >
    class basic_string;
  template<> struct char_traits<char>;
  typedef basic_string<char> string;
  template<> struct char_traits<wchar_t>;
  typedef basic_string<wchar_t> wstring;
  template<> struct char_traits<char16_t>;
  template<> struct char_traits<char32_t>;
  typedef basic_string<char16_t> u16string;
  typedef basic_string<char32_t> u32string;

}
       
namespace std __attribute__ ((__visibility__ ("default")))
{

  void
  __throw_bad_exception(void) __attribute__((__noreturn__));
  void
  __throw_bad_alloc(void) __attribute__((__noreturn__));
  void
  __throw_bad_cast(void) __attribute__((__noreturn__));
  void
  __throw_bad_typeid(void) __attribute__((__noreturn__));
  void
  __throw_logic_error(const char*) __attribute__((__noreturn__));
  void
  __throw_domain_error(const char*) __attribute__((__noreturn__));
  void
  __throw_invalid_argument(const char*) __attribute__((__noreturn__));
  void
  __throw_length_error(const char*) __attribute__((__noreturn__));
  void
  __throw_out_of_range(const char*) __attribute__((__noreturn__));
  void
  __throw_out_of_range_fmt(const char*, ...) __attribute__((__noreturn__))
    __attribute__((__format__(__printf__, 1, 2)));
  void
  __throw_runtime_error(const char*) __attribute__((__noreturn__));
  void
  __throw_range_error(const char*) __attribute__((__noreturn__));
  void
  __throw_overflow_error(const char*) __attribute__((__noreturn__));
  void
  __throw_underflow_error(const char*) __attribute__((__noreturn__));
  void
  __throw_ios_failure(const char*) __attribute__((__noreturn__));
  void
  __throw_system_error(int) __attribute__((__noreturn__));
  void
  __throw_future_error(int) __attribute__((__noreturn__));
  void
  __throw_bad_function_call() __attribute__((__noreturn__));

}
       
namespace __gnu_cxx __attribute__ ((__visibility__ ("default")))
{

  template<typename _Iterator, typename _Container>
    class __normal_iterator;

}
namespace std __attribute__ ((__visibility__ ("default")))
{

  struct __true_type { };
  struct __false_type { };
  template<bool>
    struct __truth_type
    { typedef __false_type __type; };
  template<>
    struct __truth_type<true>
    { typedef __true_type __type; };
  template<class _Sp, class _Tp>
    struct __traitor
    {
      enum { __value = bool(_Sp::__value) || bool(_Tp::__value) };
      typedef typename __truth_type<__value>::__type __type;
    };
  template<typename, typename>
    struct __are_same
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };
  template<typename _Tp>
    struct __are_same<_Tp, _Tp>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<typename _Tp>
    struct __is_void
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };
  template<>
    struct __is_void<void>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<typename _Tp>
    struct __is_integer
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };
  template<>
    struct __is_integer<bool>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<>
    struct __is_integer<char>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<>
    struct __is_integer<signed char>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<>
    struct __is_integer<unsigned char>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<>
    struct __is_integer<wchar_t>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<>
    struct __is_integer<char16_t>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<>
    struct __is_integer<char32_t>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<>
    struct __is_integer<short>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<>
    struct __is_integer<unsigned short>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<>
    struct __is_integer<int>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<>
    struct __is_integer<unsigned int>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<>
    struct __is_integer<long>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<>
    struct __is_integer<unsigned long>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<>
    struct __is_integer<long long>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<>
    struct __is_integer<unsigned long long>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<typename _Tp>
    struct __is_floating
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };
  template<>
    struct __is_floating<float>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<>
    struct __is_floating<double>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<>
    struct __is_floating<long double>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<typename _Tp>
    struct __is_pointer
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };
  template<typename _Tp>
    struct __is_pointer<_Tp*>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<typename _Tp>
    struct __is_normal_iterator
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };
  template<typename _Iterator, typename _Container>
    struct __is_normal_iterator< __gnu_cxx::__normal_iterator<_Iterator,
             _Container> >
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<typename _Tp>
    struct __is_arithmetic
    : public __traitor<__is_integer<_Tp>, __is_floating<_Tp> >
    { };
  template<typename _Tp>
    struct __is_scalar
    : public __traitor<__is_arithmetic<_Tp>, __is_pointer<_Tp> >
    { };
  template<typename _Tp>
    struct __is_char
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };
  template<>
    struct __is_char<char>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<>
    struct __is_char<wchar_t>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<typename _Tp>
    struct __is_byte
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };
  template<>
    struct __is_byte<char>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<>
    struct __is_byte<signed char>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<>
    struct __is_byte<unsigned char>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };
  template<typename _Tp>
    struct __is_move_iterator
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };
  template<typename _Iterator>
    class move_iterator;
  template<typename _Iterator>
    struct __is_move_iterator< move_iterator<_Iterator> >
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };

}
       
namespace __gnu_cxx __attribute__ ((__visibility__ ("default")))
{

  template<bool, typename>
    struct __enable_if
    { };
  template<typename _Tp>
    struct __enable_if<true, _Tp>
    { typedef _Tp __type; };
  template<bool _Cond, typename _Iftrue, typename _Iffalse>
    struct __conditional_type
    { typedef _Iftrue __type; };
  template<typename _Iftrue, typename _Iffalse>
    struct __conditional_type<false, _Iftrue, _Iffalse>
    { typedef _Iffalse __type; };
  template<typename _Tp>
    struct __add_unsigned
    {
    private:
      typedef __enable_if<std::__is_integer<_Tp>::__value, _Tp> __if_type;
    public:
      typedef typename __if_type::__type __type;
    };
  template<>
    struct __add_unsigned<char>
    { typedef unsigned char __type; };
  template<>
    struct __add_unsigned<signed char>
    { typedef unsigned char __type; };
  template<>
    struct __add_unsigned<short>
    { typedef unsigned short __type; };
  template<>
    struct __add_unsigned<int>
    { typedef unsigned int __type; };
  template<>
    struct __add_unsigned<long>
    { typedef unsigned long __type; };
  template<>
    struct __add_unsigned<long long>
    { typedef unsigned long long __type; };
  template<>
    struct __add_unsigned<bool>;
  template<>
    struct __add_unsigned<wchar_t>;
  template<typename _Tp>
    struct __remove_unsigned
    {
    private:
      typedef __enable_if<std::__is_integer<_Tp>::__value, _Tp> __if_type;
    public:
      typedef typename __if_type::__type __type;
    };
  template<>
    struct __remove_unsigned<char>
    { typedef signed char __type; };
  template<>
    struct __remove_unsigned<unsigned char>
    { typedef signed char __type; };
  template<>
    struct __remove_unsigned<unsigned short>
    { typedef short __type; };
  template<>
    struct __remove_unsigned<unsigned int>
    { typedef int __type; };
  template<>
    struct __remove_unsigned<unsigned long>
    { typedef long __type; };
  template<>
    struct __remove_unsigned<unsigned long long>
    { typedef long long __type; };
  template<>
    struct __remove_unsigned<bool>;
  template<>
    struct __remove_unsigned<wchar_t>;
  template<typename _Type>
    inline bool
    __is_null_pointer(_Type* __ptr)
    { return __ptr == 0; }
  template<typename _Type>
    inline bool
    __is_null_pointer(_Type)
    { return false; }
  inline bool
  __is_null_pointer(std::nullptr_t)
  { return true; }
  template<typename _Tp, bool = std::__is_integer<_Tp>::__value>
    struct __promote
    { typedef double __type; };
  template<typename _Tp>
    struct __promote<_Tp, false>
    { };
  template<>
    struct __promote<long double>
    { typedef long double __type; };
  template<>
    struct __promote<double>
    { typedef double __type; };
  template<>
    struct __promote<float>
    { typedef float __type; };
  template<typename _Tp, typename _Up,
           typename _Tp2 = typename __promote<_Tp>::__type,
           typename _Up2 = typename __promote<_Up>::__type>
    struct __promote_2
    {
      typedef __typeof__(_Tp2() + _Up2()) __type;
    };
  template<typename _Tp, typename _Up, typename _Vp,
           typename _Tp2 = typename __promote<_Tp>::__type,
           typename _Up2 = typename __promote<_Up>::__type,
           typename _Vp2 = typename __promote<_Vp>::__type>
    struct __promote_3
    {
      typedef __typeof__(_Tp2() + _Up2() + _Vp2()) __type;
    };
  template<typename _Tp, typename _Up, typename _Vp, typename _Wp,
           typename _Tp2 = typename __promote<_Tp>::__type,
           typename _Up2 = typename __promote<_Up>::__type,
           typename _Vp2 = typename __promote<_Vp>::__type,
           typename _Wp2 = typename __promote<_Wp>::__type>
    struct __promote_4
    {
      typedef __typeof__(_Tp2() + _Up2() + _Vp2() + _Wp2()) __type;
    };

}
       
namespace __gnu_cxx __attribute__ ((__visibility__ ("default")))
{

  template<typename _Value>
    struct __numeric_traits_integer
    {
      static const _Value __min = (((_Value)(-1) < 0) ? (_Value)1 << (sizeof(_Value) * 8 - ((_Value)(-1) < 0)) : (_Value)0);
      static const _Value __max = (((_Value)(-1) < 0) ? (((((_Value)1 << ((sizeof(_Value) * 8 - ((_Value)(-1) < 0)) - 1)) - 1) << 1) + 1) : ~(_Value)0);
      static const bool __is_signed = ((_Value)(-1) < 0);
      static const int __digits = (sizeof(_Value) * 8 - ((_Value)(-1) < 0));
    };
  template<typename _Value>
    const _Value __numeric_traits_integer<_Value>::__min;
  template<typename _Value>
    const _Value __numeric_traits_integer<_Value>::__max;
  template<typename _Value>
    const bool __numeric_traits_integer<_Value>::__is_signed;
  template<typename _Value>
    const int __numeric_traits_integer<_Value>::__digits;
  template<typename _Value>
    struct __numeric_traits_floating
    {
      static const int __max_digits10 = (2 + (std::__are_same<_Value, float>::__value ? 24 : std::__are_same<_Value, double>::__value ? 53 : 64) * 643L / 2136);
      static const bool __is_signed = true;
      static const int __digits10 = (std::__are_same<_Value, float>::__value ? 6 : std::__are_same<_Value, double>::__value ? 15 : 18);
      static const int __max_exponent10 = (std::__are_same<_Value, float>::__value ? 38 : std::__are_same<_Value, double>::__value ? 308 : 4932);
    };
  template<typename _Value>
    const int __numeric_traits_floating<_Value>::__max_digits10;
  template<typename _Value>
    const bool __numeric_traits_floating<_Value>::__is_signed;
  template<typename _Value>
    const int __numeric_traits_floating<_Value>::__digits10;
  template<typename _Value>
    const int __numeric_traits_floating<_Value>::__max_exponent10;
  template<typename _Value>
    struct __numeric_traits
    : public __conditional_type<std::__is_integer<_Value>::__value,
    __numeric_traits_integer<_Value>,
    __numeric_traits_floating<_Value> >::__type
    { };

}
       
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename _Tp>
    inline _Tp*
    __addressof(_Tp& __r) noexcept
    {
      return reinterpret_cast<_Tp*>
 (&const_cast<char&>(reinterpret_cast<const volatile char&>(__r)));
    }

}
       
namespace std
{
  typedef short unsigned int uint_least16_t;
  typedef unsigned int uint_least32_t;
}
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename _Tp, _Tp __v>
    struct integral_constant
    {
      static constexpr _Tp value = __v;
      typedef _Tp value_type;
      typedef integral_constant<_Tp, __v> type;
      constexpr operator value_type() const { return value; }
    };
  template<typename _Tp, _Tp __v>
    constexpr _Tp integral_constant<_Tp, __v>::value;
  typedef integral_constant<bool, true> true_type;
  typedef integral_constant<bool, false> false_type;
  template<bool, typename, typename>
    struct conditional;
  template<typename...>
    struct __or_;
  template<>
    struct __or_<>
    : public false_type
    { };
  template<typename _B1>
    struct __or_<_B1>
    : public _B1
    { };
  template<typename _B1, typename _B2>
    struct __or_<_B1, _B2>
    : public conditional<_B1::value, _B1, _B2>::type
    { };
  template<typename _B1, typename _B2, typename _B3, typename... _Bn>
    struct __or_<_B1, _B2, _B3, _Bn...>
    : public conditional<_B1::value, _B1, __or_<_B2, _B3, _Bn...>>::type
    { };
  template<typename...>
    struct __and_;
  template<>
    struct __and_<>
    : public true_type
    { };
  template<typename _B1>
    struct __and_<_B1>
    : public _B1
    { };
  template<typename _B1, typename _B2>
    struct __and_<_B1, _B2>
    : public conditional<_B1::value, _B2, _B1>::type
    { };
  template<typename _B1, typename _B2, typename _B3, typename... _Bn>
    struct __and_<_B1, _B2, _B3, _Bn...>
    : public conditional<_B1::value, __and_<_B2, _B3, _Bn...>, _B1>::type
    { };
  template<typename _Pp>
    struct __not_
    : public integral_constant<bool, !_Pp::value>
    { };
  template<typename _Tp>
    struct __success_type
    { typedef _Tp type; };
  struct __failure_type
  { };
  template<typename>
    struct remove_cv;
  template<typename>
    struct __is_void_helper
    : public false_type { };
  template<>
    struct __is_void_helper<void>
    : public true_type { };
  template<typename _Tp>
    struct is_void
    : public __is_void_helper<typename remove_cv<_Tp>::type>::type
    { };
  template<typename>
    struct __is_integral_helper
    : public false_type { };
  template<>
    struct __is_integral_helper<bool>
    : public true_type { };
  template<>
    struct __is_integral_helper<char>
    : public true_type { };
  template<>
    struct __is_integral_helper<signed char>
    : public true_type { };
  template<>
    struct __is_integral_helper<unsigned char>
    : public true_type { };
  template<>
    struct __is_integral_helper<wchar_t>
    : public true_type { };
  template<>
    struct __is_integral_helper<char16_t>
    : public true_type { };
  template<>
    struct __is_integral_helper<char32_t>
    : public true_type { };
  template<>
    struct __is_integral_helper<short>
    : public true_type { };
  template<>
    struct __is_integral_helper<unsigned short>
    : public true_type { };
  template<>
    struct __is_integral_helper<int>
    : public true_type { };
  template<>
    struct __is_integral_helper<unsigned int>
    : public true_type { };
  template<>
    struct __is_integral_helper<long>
    : public true_type { };
  template<>
    struct __is_integral_helper<unsigned long>
    : public true_type { };
  template<>
    struct __is_integral_helper<long long>
    : public true_type { };
  template<>
    struct __is_integral_helper<unsigned long long>
    : public true_type { };
  template<typename _Tp>
    struct is_integral
    : public __is_integral_helper<typename remove_cv<_Tp>::type>::type
    { };
  template<typename>
    struct __is_floating_point_helper
    : public false_type { };
  template<>
    struct __is_floating_point_helper<float>
    : public true_type { };
  template<>
    struct __is_floating_point_helper<double>
    : public true_type { };
  template<>
    struct __is_floating_point_helper<long double>
    : public true_type { };
  template<typename _Tp>
    struct is_floating_point
    : public __is_floating_point_helper<typename remove_cv<_Tp>::type>::type
    { };
  template<typename>
    struct is_array
    : public false_type { };
  template<typename _Tp, std::size_t _Size>
    struct is_array<_Tp[_Size]>
    : public true_type { };
  template<typename _Tp>
    struct is_array<_Tp[]>
    : public true_type { };
  template<typename>
    struct __is_pointer_helper
    : public false_type { };
  template<typename _Tp>
    struct __is_pointer_helper<_Tp*>
    : public true_type { };
  template<typename _Tp>
    struct is_pointer
    : public __is_pointer_helper<typename remove_cv<_Tp>::type>::type
    { };
  template<typename>
    struct is_lvalue_reference
    : public false_type { };
  template<typename _Tp>
    struct is_lvalue_reference<_Tp&>
    : public true_type { };
  template<typename>
    struct is_rvalue_reference
    : public false_type { };
  template<typename _Tp>
    struct is_rvalue_reference<_Tp&&>
    : public true_type { };
  template<typename>
    struct is_function;
  template<typename>
    struct __is_member_object_pointer_helper
    : public false_type { };
  template<typename _Tp, typename _Cp>
    struct __is_member_object_pointer_helper<_Tp _Cp::*>
    : public integral_constant<bool, !is_function<_Tp>::value> { };
  template<typename _Tp>
    struct is_member_object_pointer
    : public __is_member_object_pointer_helper<
    typename remove_cv<_Tp>::type>::type
    { };
  template<typename>
    struct __is_member_function_pointer_helper
    : public false_type { };
  template<typename _Tp, typename _Cp>
    struct __is_member_function_pointer_helper<_Tp _Cp::*>
    : public integral_constant<bool, is_function<_Tp>::value> { };
  template<typename _Tp>
    struct is_member_function_pointer
    : public __is_member_function_pointer_helper<
    typename remove_cv<_Tp>::type>::type
    { };
  template<typename _Tp>
    struct is_enum
    : public integral_constant<bool, __is_enum(_Tp)>
    { };
  template<typename _Tp>
    struct is_union
    : public integral_constant<bool, __is_union(_Tp)>
    { };
  template<typename _Tp>
    struct is_class
    : public integral_constant<bool, __is_class(_Tp)>
    { };
  template<typename>
    struct is_function
    : public false_type { };
  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes...)>
    : public true_type { };
  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes...) &>
    : public true_type { };
  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes...) &&>
    : public true_type { };
  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes......)>
    : public true_type { };
  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes......) &>
    : public true_type { };
  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes......) &&>
    : public true_type { };
  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes...) const>
    : public true_type { };
  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes...) const &>
    : public true_type { };
  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes...) const &&>
    : public true_type { };
  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes......) const>
    : public true_type { };
  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes......) const &>
    : public true_type { };
  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes......) const &&>
    : public true_type { };
  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes...) volatile>
    : public true_type { };
  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes...) volatile &>
    : public true_type { };
  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes...) volatile &&>
    : public true_type { };
  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes......) volatile>
    : public true_type { };
  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes......) volatile &>
    : public true_type { };
  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes......) volatile &&>
    : public true_type { };
  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes...) const volatile>
    : public true_type { };
  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes...) const volatile &>
    : public true_type { };
  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes...) const volatile &&>
    : public true_type { };
  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes......) const volatile>
    : public true_type { };
  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes......) const volatile &>
    : public true_type { };
  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes......) const volatile &&>
    : public true_type { };
  template<typename>
    struct __is_null_pointer_helper
    : public false_type { };
  template<>
    struct __is_null_pointer_helper<std::nullptr_t>
    : public true_type { };
  template<typename _Tp>
    struct is_null_pointer
    : public __is_null_pointer_helper<typename remove_cv<_Tp>::type>::type
    { };
  template<typename _Tp>
    struct __is_nullptr_t
    : public is_null_pointer<_Tp>
    { };
  template<typename _Tp>
    struct is_reference
    : public __or_<is_lvalue_reference<_Tp>,
                   is_rvalue_reference<_Tp>>::type
    { };
  template<typename _Tp>
    struct is_arithmetic
    : public __or_<is_integral<_Tp>, is_floating_point<_Tp>>::type
    { };
  template<typename _Tp>
    struct is_fundamental
    : public __or_<is_arithmetic<_Tp>, is_void<_Tp>,
     is_null_pointer<_Tp>>::type
    { };
  template<typename _Tp>
    struct is_object
    : public __not_<__or_<is_function<_Tp>, is_reference<_Tp>,
                          is_void<_Tp>>>::type
    { };
  template<typename>
    struct is_member_pointer;
  template<typename _Tp>
    struct is_scalar
    : public __or_<is_arithmetic<_Tp>, is_enum<_Tp>, is_pointer<_Tp>,
                   is_member_pointer<_Tp>, is_null_pointer<_Tp>>::type
    { };
  template<typename _Tp>
    struct is_compound
    : public integral_constant<bool, !is_fundamental<_Tp>::value> { };
  template<typename _Tp>
    struct __is_member_pointer_helper
    : public false_type { };
  template<typename _Tp, typename _Cp>
    struct __is_member_pointer_helper<_Tp _Cp::*>
    : public true_type { };
  template<typename _Tp>
    struct is_member_pointer
    : public __is_member_pointer_helper<typename remove_cv<_Tp>::type>::type
    { };
  template<typename _Tp>
    struct __is_referenceable
    : public __or_<is_object<_Tp>, is_reference<_Tp>>::type
    { };
  template<typename _Res, typename... _Args>
    struct __is_referenceable<_Res(_Args...)>
    : public true_type
    { };
  template<typename _Res, typename... _Args>
    struct __is_referenceable<_Res(_Args......)>
    : public true_type
    { };
  template<typename>
    struct is_const
    : public false_type { };
  template<typename _Tp>
    struct is_const<_Tp const>
    : public true_type { };
  template<typename>
    struct is_volatile
    : public false_type { };
  template<typename _Tp>
    struct is_volatile<_Tp volatile>
    : public true_type { };
  template<typename _Tp>
    struct is_trivial
    : public integral_constant<bool, __is_trivial(_Tp)>
    { };
  template<typename _Tp>
    struct is_standard_layout
    : public integral_constant<bool, __is_standard_layout(_Tp)>
    { };
  template<typename _Tp>
    struct is_pod
    : public integral_constant<bool, __is_pod(_Tp)>
    { };
  template<typename _Tp>
    struct is_literal_type
    : public integral_constant<bool, __is_literal_type(_Tp)>
    { };
  template<typename _Tp>
    struct is_empty
    : public integral_constant<bool, __is_empty(_Tp)>
    { };
  template<typename _Tp>
    struct is_polymorphic
    : public integral_constant<bool, __is_polymorphic(_Tp)>
    { };
  template<typename _Tp>
    struct is_abstract
    : public integral_constant<bool, __is_abstract(_Tp)>
    { };
  template<typename _Tp,
    bool = is_arithmetic<_Tp>::value>
    struct __is_signed_helper
    : public false_type { };
  template<typename _Tp>
    struct __is_signed_helper<_Tp, true>
    : public integral_constant<bool, _Tp(-1) < _Tp(0)>
    { };
  template<typename _Tp>
    struct is_signed
    : public __is_signed_helper<_Tp>::type
    { };
  template<typename _Tp>
    struct is_unsigned
    : public __and_<is_arithmetic<_Tp>, __not_<is_signed<_Tp>>>::type
    { };
  template<typename>
    struct add_rvalue_reference;
  template<typename _Tp>
    typename add_rvalue_reference<_Tp>::type declval() noexcept;
  template<typename, unsigned = 0>
    struct extent;
  template<typename>
    struct remove_all_extents;
  template<typename _Tp>
    struct __is_array_known_bounds
    : public integral_constant<bool, (extent<_Tp>::value > 0)>
    { };
  template<typename _Tp>
    struct __is_array_unknown_bounds
    : public __and_<is_array<_Tp>, __not_<extent<_Tp>>>::type
    { };
  struct __do_is_destructible_impl
  {
    template<typename _Tp, typename = decltype(declval<_Tp&>().~_Tp())>
      static true_type __test(int);
    template<typename>
      static false_type __test(...);
  };
  template<typename _Tp>
    struct __is_destructible_impl
    : public __do_is_destructible_impl
    {
      typedef decltype(__test<_Tp>(0)) type;
    };
  template<typename _Tp,
           bool = __or_<is_void<_Tp>,
                        __is_array_unknown_bounds<_Tp>,
                        is_function<_Tp>>::value,
           bool = __or_<is_reference<_Tp>, is_scalar<_Tp>>::value>
    struct __is_destructible_safe;
  template<typename _Tp>
    struct __is_destructible_safe<_Tp, false, false>
    : public __is_destructible_impl<typename
               remove_all_extents<_Tp>::type>::type
    { };
  template<typename _Tp>
    struct __is_destructible_safe<_Tp, true, false>
    : public false_type { };
  template<typename _Tp>
    struct __is_destructible_safe<_Tp, false, true>
    : public true_type { };
  template<typename _Tp>
    struct is_destructible
    : public __is_destructible_safe<_Tp>::type
    { };
  struct __do_is_nt_destructible_impl
  {
    template<typename _Tp>
      static integral_constant<bool, noexcept(declval<_Tp&>().~_Tp())>
        __test(int);
    template<typename>
      static false_type __test(...);
  };
  template<typename _Tp>
    struct __is_nt_destructible_impl
    : public __do_is_nt_destructible_impl
    {
      typedef decltype(__test<_Tp>(0)) type;
    };
  template<typename _Tp,
           bool = __or_<is_void<_Tp>,
                        __is_array_unknown_bounds<_Tp>,
                        is_function<_Tp>>::value,
           bool = __or_<is_reference<_Tp>, is_scalar<_Tp>>::value>
    struct __is_nt_destructible_safe;
  template<typename _Tp>
    struct __is_nt_destructible_safe<_Tp, false, false>
    : public __is_nt_destructible_impl<typename
               remove_all_extents<_Tp>::type>::type
    { };
  template<typename _Tp>
    struct __is_nt_destructible_safe<_Tp, true, false>
    : public false_type { };
  template<typename _Tp>
    struct __is_nt_destructible_safe<_Tp, false, true>
    : public true_type { };
  template<typename _Tp>
    struct is_nothrow_destructible
    : public __is_nt_destructible_safe<_Tp>::type
    { };
  struct __do_is_default_constructible_impl
  {
    template<typename _Tp, typename = decltype(_Tp())>
      static true_type __test(int);
    template<typename>
      static false_type __test(...);
  };
  template<typename _Tp>
    struct __is_default_constructible_impl
    : public __do_is_default_constructible_impl
    {
      typedef decltype(__test<_Tp>(0)) type;
    };
  template<typename _Tp>
    struct __is_default_constructible_atom
    : public __and_<__not_<is_void<_Tp>>,
                    __is_default_constructible_impl<_Tp>>::type
    { };
  template<typename _Tp, bool = is_array<_Tp>::value>
    struct __is_default_constructible_safe;
  template<typename _Tp>
    struct __is_default_constructible_safe<_Tp, true>
    : public __and_<__is_array_known_bounds<_Tp>,
      __is_default_constructible_atom<typename
                      remove_all_extents<_Tp>::type>>::type
    { };
  template<typename _Tp>
    struct __is_default_constructible_safe<_Tp, false>
    : public __is_default_constructible_atom<_Tp>::type
    { };
  template<typename _Tp>
    struct is_default_constructible
    : public __is_default_constructible_safe<_Tp>::type
    { };
  struct __do_is_static_castable_impl
  {
    template<typename _From, typename _To, typename
             = decltype(static_cast<_To>(declval<_From>()))>
      static true_type __test(int);
    template<typename, typename>
      static false_type __test(...);
  };
  template<typename _From, typename _To>
    struct __is_static_castable_impl
    : public __do_is_static_castable_impl
    {
      typedef decltype(__test<_From, _To>(0)) type;
    };
  template<typename _From, typename _To>
    struct __is_static_castable_safe
    : public __is_static_castable_impl<_From, _To>::type
    { };
  template<typename _From, typename _To>
    struct __is_static_castable
    : public integral_constant<bool, (__is_static_castable_safe<
          _From, _To>::value)>
    { };
  struct __do_is_direct_constructible_impl
  {
    template<typename _Tp, typename _Arg, typename
      = decltype(::new _Tp(declval<_Arg>()))>
      static true_type __test(int);
    template<typename, typename>
      static false_type __test(...);
  };
  template<typename _Tp, typename _Arg>
    struct __is_direct_constructible_impl
    : public __do_is_direct_constructible_impl
    {
      typedef decltype(__test<_Tp, _Arg>(0)) type;
    };
  template<typename _Tp, typename _Arg>
    struct __is_direct_constructible_new_safe
    : public __and_<is_destructible<_Tp>,
                    __is_direct_constructible_impl<_Tp, _Arg>>::type
    { };
  template<typename, typename>
    struct is_same;
  template<typename, typename>
    struct is_base_of;
  template<typename>
    struct remove_reference;
  template<typename _From, typename _To, bool
           = __not_<__or_<is_void<_From>,
                          is_function<_From>>>::value>
    struct __is_base_to_derived_ref;
  template<typename _From, typename _To>
    struct __is_base_to_derived_ref<_From, _To, true>
    {
      typedef typename remove_cv<typename remove_reference<_From
        >::type>::type __src_t;
      typedef typename remove_cv<typename remove_reference<_To
        >::type>::type __dst_t;
      typedef __and_<__not_<is_same<__src_t, __dst_t>>,
       is_base_of<__src_t, __dst_t>> type;
      static constexpr bool value = type::value;
    };
  template<typename _From, typename _To>
    struct __is_base_to_derived_ref<_From, _To, false>
    : public false_type
    { };
  template<typename _From, typename _To, bool
           = __and_<is_lvalue_reference<_From>,
                    is_rvalue_reference<_To>>::value>
    struct __is_lvalue_to_rvalue_ref;
  template<typename _From, typename _To>
    struct __is_lvalue_to_rvalue_ref<_From, _To, true>
    {
      typedef typename remove_cv<typename remove_reference<
        _From>::type>::type __src_t;
      typedef typename remove_cv<typename remove_reference<
        _To>::type>::type __dst_t;
      typedef __and_<__not_<is_function<__src_t>>,
        __or_<is_same<__src_t, __dst_t>,
      is_base_of<__dst_t, __src_t>>> type;
      static constexpr bool value = type::value;
    };
  template<typename _From, typename _To>
    struct __is_lvalue_to_rvalue_ref<_From, _To, false>
    : public false_type
    { };
  template<typename _Tp, typename _Arg>
    struct __is_direct_constructible_ref_cast
    : public __and_<__is_static_castable<_Arg, _Tp>,
                    __not_<__or_<__is_base_to_derived_ref<_Arg, _Tp>,
                                 __is_lvalue_to_rvalue_ref<_Arg, _Tp>
                   >>>::type
    { };
  template<typename _Tp, typename _Arg>
    struct __is_direct_constructible_new
    : public conditional<is_reference<_Tp>::value,
    __is_direct_constructible_ref_cast<_Tp, _Arg>,
    __is_direct_constructible_new_safe<_Tp, _Arg>
    >::type
    { };
  template<typename _Tp, typename _Arg>
    struct __is_direct_constructible
    : public __is_direct_constructible_new<_Tp, _Arg>::type
    { };
  struct __do_is_nary_constructible_impl
  {
    template<typename _Tp, typename... _Args, typename
             = decltype(_Tp(declval<_Args>()...))>
      static true_type __test(int);
    template<typename, typename...>
      static false_type __test(...);
  };
  template<typename _Tp, typename... _Args>
    struct __is_nary_constructible_impl
    : public __do_is_nary_constructible_impl
    {
      typedef decltype(__test<_Tp, _Args...>(0)) type;
    };
  template<typename _Tp, typename... _Args>
    struct __is_nary_constructible
    : public __is_nary_constructible_impl<_Tp, _Args...>::type
    {
      static_assert(sizeof...(_Args) > 1,
                    "Only useful for > 1 arguments");
    };
  template<typename _Tp, typename... _Args>
    struct __is_constructible_impl
    : public __is_nary_constructible<_Tp, _Args...>
    { };
  template<typename _Tp, typename _Arg>
    struct __is_constructible_impl<_Tp, _Arg>
    : public __is_direct_constructible<_Tp, _Arg>
    { };
  template<typename _Tp>
    struct __is_constructible_impl<_Tp>
    : public is_default_constructible<_Tp>
    { };
  template<typename _Tp, typename... _Args>
    struct is_constructible
    : public __is_constructible_impl<_Tp, _Args...>::type
    { };
  template<typename _Tp, bool = __is_referenceable<_Tp>::value>
    struct __is_copy_constructible_impl;
  template<typename _Tp>
    struct __is_copy_constructible_impl<_Tp, false>
    : public false_type { };
  template<typename _Tp>
    struct __is_copy_constructible_impl<_Tp, true>
    : public is_constructible<_Tp, const _Tp&>
    { };
  template<typename _Tp>
    struct is_copy_constructible
    : public __is_copy_constructible_impl<_Tp>
    { };
  template<typename _Tp, bool = __is_referenceable<_Tp>::value>
    struct __is_move_constructible_impl;
  template<typename _Tp>
    struct __is_move_constructible_impl<_Tp, false>
    : public false_type { };
  template<typename _Tp>
    struct __is_move_constructible_impl<_Tp, true>
    : public is_constructible<_Tp, _Tp&&>
    { };
  template<typename _Tp>
    struct is_move_constructible
    : public __is_move_constructible_impl<_Tp>
    { };
  template<typename _Tp>
    struct __is_nt_default_constructible_atom
    : public integral_constant<bool, noexcept(_Tp())>
    { };
  template<typename _Tp, bool = is_array<_Tp>::value>
    struct __is_nt_default_constructible_impl;
  template<typename _Tp>
    struct __is_nt_default_constructible_impl<_Tp, true>
    : public __and_<__is_array_known_bounds<_Tp>,
      __is_nt_default_constructible_atom<typename
                      remove_all_extents<_Tp>::type>>::type
    { };
  template<typename _Tp>
    struct __is_nt_default_constructible_impl<_Tp, false>
    : public __is_nt_default_constructible_atom<_Tp>
    { };
  template<typename _Tp>
    struct is_nothrow_default_constructible
    : public __and_<is_default_constructible<_Tp>,
                    __is_nt_default_constructible_impl<_Tp>>::type
    { };
  template<typename _Tp, typename... _Args>
    struct __is_nt_constructible_impl
    : public integral_constant<bool, noexcept(_Tp(declval<_Args>()...))>
    { };
  template<typename _Tp, typename _Arg>
    struct __is_nt_constructible_impl<_Tp, _Arg>
    : public integral_constant<bool,
                               noexcept(static_cast<_Tp>(declval<_Arg>()))>
    { };
  template<typename _Tp>
    struct __is_nt_constructible_impl<_Tp>
    : public is_nothrow_default_constructible<_Tp>
    { };
  template<typename _Tp, typename... _Args>
    struct is_nothrow_constructible
    : public __and_<is_constructible<_Tp, _Args...>,
      __is_nt_constructible_impl<_Tp, _Args...>>::type
    { };
  template<typename _Tp, bool = __is_referenceable<_Tp>::value>
    struct __is_nothrow_copy_constructible_impl;
  template<typename _Tp>
    struct __is_nothrow_copy_constructible_impl<_Tp, false>
    : public false_type { };
  template<typename _Tp>
    struct __is_nothrow_copy_constructible_impl<_Tp, true>
    : public is_nothrow_constructible<_Tp, const _Tp&>
    { };
  template<typename _Tp>
    struct is_nothrow_copy_constructible
    : public __is_nothrow_copy_constructible_impl<_Tp>
    { };
  template<typename _Tp, bool = __is_referenceable<_Tp>::value>
    struct __is_nothrow_move_constructible_impl;
  template<typename _Tp>
    struct __is_nothrow_move_constructible_impl<_Tp, false>
    : public false_type { };
  template<typename _Tp>
    struct __is_nothrow_move_constructible_impl<_Tp, true>
    : public is_nothrow_constructible<_Tp, _Tp&&>
    { };
  template<typename _Tp>
    struct is_nothrow_move_constructible
    : public __is_nothrow_move_constructible_impl<_Tp>
    { };
  template<typename _Tp, typename _Up>
    class __is_assignable_helper
    {
      template<typename _Tp1, typename _Up1,
        typename = decltype(declval<_Tp1>() = declval<_Up1>())>
 static true_type
 __test(int);
      template<typename, typename>
 static false_type
 __test(...);
    public:
      typedef decltype(__test<_Tp, _Up>(0)) type;
    };
  template<typename _Tp, typename _Up>
    struct is_assignable
      : public __is_assignable_helper<_Tp, _Up>::type
    { };
  template<typename _Tp, bool = __is_referenceable<_Tp>::value>
    struct __is_copy_assignable_impl;
  template<typename _Tp>
    struct __is_copy_assignable_impl<_Tp, false>
    : public false_type { };
  template<typename _Tp>
    struct __is_copy_assignable_impl<_Tp, true>
    : public is_assignable<_Tp&, const _Tp&>
    { };
  template<typename _Tp>
    struct is_copy_assignable
    : public __is_copy_assignable_impl<_Tp>
    { };
  template<typename _Tp, bool = __is_referenceable<_Tp>::value>
    struct __is_move_assignable_impl;
  template<typename _Tp>
    struct __is_move_assignable_impl<_Tp, false>
    : public false_type { };
  template<typename _Tp>
    struct __is_move_assignable_impl<_Tp, true>
    : public is_assignable<_Tp&, _Tp&&>
    { };
  template<typename _Tp>
    struct is_move_assignable
    : public __is_move_assignable_impl<_Tp>
    { };
  template<typename _Tp, typename _Up>
    struct __is_nt_assignable_impl
    : public integral_constant<bool, noexcept(declval<_Tp>() = declval<_Up>())>
    { };
  template<typename _Tp, typename _Up>
    struct is_nothrow_assignable
    : public __and_<is_assignable<_Tp, _Up>,
      __is_nt_assignable_impl<_Tp, _Up>>::type
    { };
  template<typename _Tp, bool = __is_referenceable<_Tp>::value>
    struct __is_nt_copy_assignable_impl;
  template<typename _Tp>
    struct __is_nt_copy_assignable_impl<_Tp, false>
    : public false_type { };
  template<typename _Tp>
    struct __is_nt_copy_assignable_impl<_Tp, true>
    : public is_nothrow_assignable<_Tp&, const _Tp&>
    { };
  template<typename _Tp>
    struct is_nothrow_copy_assignable
    : public __is_nt_copy_assignable_impl<_Tp>
    { };
  template<typename _Tp, bool = __is_referenceable<_Tp>::value>
    struct __is_nt_move_assignable_impl;
  template<typename _Tp>
    struct __is_nt_move_assignable_impl<_Tp, false>
    : public false_type { };
  template<typename _Tp>
    struct __is_nt_move_assignable_impl<_Tp, true>
    : public is_nothrow_assignable<_Tp&, _Tp&&>
    { };
  template<typename _Tp>
    struct is_nothrow_move_assignable
    : public __is_nt_move_assignable_impl<_Tp>
    { };
  template<typename _Tp>
    struct is_trivially_destructible
    : public __and_<is_destructible<_Tp>, integral_constant<bool,
         __has_trivial_destructor(_Tp)>>::type
    { };
  template<typename _Tp>
    struct has_trivial_default_constructor
    : public integral_constant<bool, __has_trivial_constructor(_Tp)>
    { };
  template<typename _Tp>
    struct has_trivial_copy_constructor
    : public integral_constant<bool, __has_trivial_copy(_Tp)>
    { };
  template<typename _Tp>
    struct has_trivial_copy_assign
    : public integral_constant<bool, __has_trivial_assign(_Tp)>
    { };
  template<typename _Tp>
    struct has_virtual_destructor
    : public integral_constant<bool, __has_virtual_destructor(_Tp)>
    { };
  template<typename _Tp>
    struct alignment_of
    : public integral_constant<std::size_t, __alignof__(_Tp)> { };
  template<typename>
    struct rank
    : public integral_constant<std::size_t, 0> { };
  template<typename _Tp, std::size_t _Size>
    struct rank<_Tp[_Size]>
    : public integral_constant<std::size_t, 1 + rank<_Tp>::value> { };
  template<typename _Tp>
    struct rank<_Tp[]>
    : public integral_constant<std::size_t, 1 + rank<_Tp>::value> { };
  template<typename, unsigned _Uint>
    struct extent
    : public integral_constant<std::size_t, 0> { };
  template<typename _Tp, unsigned _Uint, std::size_t _Size>
    struct extent<_Tp[_Size], _Uint>
    : public integral_constant<std::size_t,
          _Uint == 0 ? _Size : extent<_Tp,
          _Uint - 1>::value>
    { };
  template<typename _Tp, unsigned _Uint>
    struct extent<_Tp[], _Uint>
    : public integral_constant<std::size_t,
          _Uint == 0 ? 0 : extent<_Tp,
             _Uint - 1>::value>
    { };
  template<typename, typename>
    struct is_same
    : public false_type { };
  template<typename _Tp>
    struct is_same<_Tp, _Tp>
    : public true_type { };
  template<typename _Base, typename _Derived>
    struct is_base_of
    : public integral_constant<bool, __is_base_of(_Base, _Derived)>
    { };
  template<typename _From, typename _To,
           bool = __or_<is_void<_From>, is_function<_To>,
                        is_array<_To>>::value>
    struct __is_convertible_helper
    { typedef typename is_void<_To>::type type; };
  template<typename _From, typename _To>
    class __is_convertible_helper<_From, _To, false>
    {
       template<typename _To1>
 static void __test_aux(_To1);
      template<typename _From1, typename _To1,
        typename = decltype(__test_aux<_To1>(std::declval<_From1>()))>
 static true_type
 __test(int);
      template<typename, typename>
 static false_type
 __test(...);
    public:
      typedef decltype(__test<_From, _To>(0)) type;
    };
  template<typename _From, typename _To>
    struct is_convertible
    : public __is_convertible_helper<_From, _To>::type
    { };
  template<typename _Tp>
    struct remove_const
    { typedef _Tp type; };
  template<typename _Tp>
    struct remove_const<_Tp const>
    { typedef _Tp type; };
  template<typename _Tp>
    struct remove_volatile
    { typedef _Tp type; };
  template<typename _Tp>
    struct remove_volatile<_Tp volatile>
    { typedef _Tp type; };
  template<typename _Tp>
    struct remove_cv
    {
      typedef typename
      remove_const<typename remove_volatile<_Tp>::type>::type type;
    };
  template<typename _Tp>
    struct add_const
    { typedef _Tp const type; };
  template<typename _Tp>
    struct add_volatile
    { typedef _Tp volatile type; };
  template<typename _Tp>
    struct add_cv
    {
      typedef typename
      add_const<typename add_volatile<_Tp>::type>::type type;
    };
  template<typename _Tp>
    struct remove_reference
    { typedef _Tp type; };
  template<typename _Tp>
    struct remove_reference<_Tp&>
    { typedef _Tp type; };
  template<typename _Tp>
    struct remove_reference<_Tp&&>
    { typedef _Tp type; };
  template<typename _Tp, bool = __is_referenceable<_Tp>::value>
    struct __add_lvalue_reference_helper
    { typedef _Tp type; };
  template<typename _Tp>
    struct __add_lvalue_reference_helper<_Tp, true>
    { typedef _Tp& type; };
  template<typename _Tp>
    struct add_lvalue_reference
    : public __add_lvalue_reference_helper<_Tp>
    { };
  template<typename _Tp, bool = __is_referenceable<_Tp>::value>
    struct __add_rvalue_reference_helper
    { typedef _Tp type; };
  template<typename _Tp>
    struct __add_rvalue_reference_helper<_Tp, true>
    { typedef _Tp&& type; };
  template<typename _Tp>
    struct add_rvalue_reference
    : public __add_rvalue_reference_helper<_Tp>
    { };
  template<typename _Unqualified, bool _IsConst, bool _IsVol>
    struct __cv_selector;
  template<typename _Unqualified>
    struct __cv_selector<_Unqualified, false, false>
    { typedef _Unqualified __type; };
  template<typename _Unqualified>
    struct __cv_selector<_Unqualified, false, true>
    { typedef volatile _Unqualified __type; };
  template<typename _Unqualified>
    struct __cv_selector<_Unqualified, true, false>
    { typedef const _Unqualified __type; };
  template<typename _Unqualified>
    struct __cv_selector<_Unqualified, true, true>
    { typedef const volatile _Unqualified __type; };
  template<typename _Qualified, typename _Unqualified,
    bool _IsConst = is_const<_Qualified>::value,
    bool _IsVol = is_volatile<_Qualified>::value>
    class __match_cv_qualifiers
    {
      typedef __cv_selector<_Unqualified, _IsConst, _IsVol> __match;
    public:
      typedef typename __match::__type __type;
    };
  template<typename _Tp>
    struct __make_unsigned
    { typedef _Tp __type; };
  template<>
    struct __make_unsigned<char>
    { typedef unsigned char __type; };
  template<>
    struct __make_unsigned<signed char>
    { typedef unsigned char __type; };
  template<>
    struct __make_unsigned<short>
    { typedef unsigned short __type; };
  template<>
    struct __make_unsigned<int>
    { typedef unsigned int __type; };
  template<>
    struct __make_unsigned<long>
    { typedef unsigned long __type; };
  template<>
    struct __make_unsigned<long long>
    { typedef unsigned long long __type; };
  template<>
    struct __make_unsigned<wchar_t> : __make_unsigned<int>
    { };
  template<typename _Tp,
    bool _IsInt = is_integral<_Tp>::value,
    bool _IsEnum = is_enum<_Tp>::value>
    class __make_unsigned_selector;
  template<typename _Tp>
    class __make_unsigned_selector<_Tp, true, false>
    {
      typedef __make_unsigned<typename remove_cv<_Tp>::type> __unsignedt;
      typedef typename __unsignedt::__type __unsigned_type;
      typedef __match_cv_qualifiers<_Tp, __unsigned_type> __cv_unsigned;
    public:
      typedef typename __cv_unsigned::__type __type;
    };
  template<typename _Tp>
    class __make_unsigned_selector<_Tp, false, true>
    {
      typedef unsigned char __smallest;
      static const bool __b0 = sizeof(_Tp) <= sizeof(__smallest);
      static const bool __b1 = sizeof(_Tp) <= sizeof(unsigned short);
      static const bool __b2 = sizeof(_Tp) <= sizeof(unsigned int);
      typedef conditional<__b2, unsigned int, unsigned long> __cond2;
      typedef typename __cond2::type __cond2_type;
      typedef conditional<__b1, unsigned short, __cond2_type> __cond1;
      typedef typename __cond1::type __cond1_type;
    public:
      typedef typename conditional<__b0, __smallest, __cond1_type>::type __type;
    };
  template<typename _Tp>
    struct make_unsigned
    { typedef typename __make_unsigned_selector<_Tp>::__type type; };
  template<>
    struct make_unsigned<bool>;
  template<typename _Tp>
    struct __make_signed
    { typedef _Tp __type; };
  template<>
    struct __make_signed<char>
    { typedef signed char __type; };
  template<>
    struct __make_signed<unsigned char>
    { typedef signed char __type; };
  template<>
    struct __make_signed<unsigned short>
    { typedef signed short __type; };
  template<>
    struct __make_signed<unsigned int>
    { typedef signed int __type; };
  template<>
    struct __make_signed<unsigned long>
    { typedef signed long __type; };
  template<>
    struct __make_signed<unsigned long long>
    { typedef signed long long __type; };
  template<>
    struct __make_signed<char16_t> : __make_signed<uint_least16_t>
    { };
  template<>
    struct __make_signed<char32_t> : __make_signed<uint_least32_t>
    { };
  template<typename _Tp,
    bool _IsInt = is_integral<_Tp>::value,
    bool _IsEnum = is_enum<_Tp>::value>
    class __make_signed_selector;
  template<typename _Tp>
    class __make_signed_selector<_Tp, true, false>
    {
      typedef __make_signed<typename remove_cv<_Tp>::type> __signedt;
      typedef typename __signedt::__type __signed_type;
      typedef __match_cv_qualifiers<_Tp, __signed_type> __cv_signed;
    public:
      typedef typename __cv_signed::__type __type;
    };
  template<typename _Tp>
    class __make_signed_selector<_Tp, false, true>
    {
      typedef signed char __smallest;
      static const bool __b0 = sizeof(_Tp) <= sizeof(__smallest);
      static const bool __b1 = sizeof(_Tp) <= sizeof(signed short);
      static const bool __b2 = sizeof(_Tp) <= sizeof(signed int);
      typedef conditional<__b2, signed int, signed long> __cond2;
      typedef typename __cond2::type __cond2_type;
      typedef conditional<__b1, signed short, __cond2_type> __cond1;
      typedef typename __cond1::type __cond1_type;
    public:
      typedef typename conditional<__b0, __smallest, __cond1_type>::type __type;
    };
  template<typename _Tp>
    struct make_signed
    { typedef typename __make_signed_selector<_Tp>::__type type; };
  template<>
    struct make_signed<bool>;
  template<typename _Tp>
    struct remove_extent
    { typedef _Tp type; };
  template<typename _Tp, std::size_t _Size>
    struct remove_extent<_Tp[_Size]>
    { typedef _Tp type; };
  template<typename _Tp>
    struct remove_extent<_Tp[]>
    { typedef _Tp type; };
  template<typename _Tp>
    struct remove_all_extents
    { typedef _Tp type; };
  template<typename _Tp, std::size_t _Size>
    struct remove_all_extents<_Tp[_Size]>
    { typedef typename remove_all_extents<_Tp>::type type; };
  template<typename _Tp>
    struct remove_all_extents<_Tp[]>
    { typedef typename remove_all_extents<_Tp>::type type; };
  template<typename _Tp, typename>
    struct __remove_pointer_helper
    { typedef _Tp type; };
  template<typename _Tp, typename _Up>
    struct __remove_pointer_helper<_Tp, _Up*>
    { typedef _Up type; };
  template<typename _Tp>
    struct remove_pointer
    : public __remove_pointer_helper<_Tp, typename remove_cv<_Tp>::type>
    { };
  template<typename _Tp, bool = __or_<__is_referenceable<_Tp>,
          is_void<_Tp>>::value>
    struct __add_pointer_helper
    { typedef _Tp type; };
  template<typename _Tp>
    struct __add_pointer_helper<_Tp, true>
    { typedef typename remove_reference<_Tp>::type* type; };
  template<typename _Tp>
    struct add_pointer
    : public __add_pointer_helper<_Tp>
    { };
  template<std::size_t _Len>
    struct __aligned_storage_msa
    {
      union __type
      {
 unsigned char __data[_Len];
 struct __attribute__((__aligned__)) { } __align;
      };
    };
  template<std::size_t _Len, std::size_t _Align =
    __alignof__(typename __aligned_storage_msa<_Len>::__type)>
    struct aligned_storage
    {
      union type
      {
 unsigned char __data[_Len];
 struct __attribute__((__aligned__((_Align)))) { } __align;
      };
    };
  template<typename _Up,
    bool _IsArray = is_array<_Up>::value,
    bool _IsFunction = is_function<_Up>::value>
    struct __decay_selector;
  template<typename _Up>
    struct __decay_selector<_Up, false, false>
    { typedef typename remove_cv<_Up>::type __type; };
  template<typename _Up>
    struct __decay_selector<_Up, true, false>
    { typedef typename remove_extent<_Up>::type* __type; };
  template<typename _Up>
    struct __decay_selector<_Up, false, true>
    { typedef typename add_pointer<_Up>::type __type; };
  template<typename _Tp>
    class decay
    {
      typedef typename remove_reference<_Tp>::type __remove_type;
    public:
      typedef typename __decay_selector<__remove_type>::__type type;
    };
  template<typename _Tp>
    class reference_wrapper;
  template<typename _Tp>
    struct __strip_reference_wrapper
    {
      typedef _Tp __type;
    };
  template<typename _Tp>
    struct __strip_reference_wrapper<reference_wrapper<_Tp> >
    {
      typedef _Tp& __type;
    };
  template<typename _Tp>
    struct __decay_and_strip
    {
      typedef typename __strip_reference_wrapper<
 typename decay<_Tp>::type>::__type __type;
    };
  template<bool, typename _Tp = void>
    struct enable_if
    { };
  template<typename _Tp>
    struct enable_if<true, _Tp>
    { typedef _Tp type; };
  template<typename... _Cond>
    using _Require = typename enable_if<__and_<_Cond...>::value>::type;
  template<bool _Cond, typename _Iftrue, typename _Iffalse>
    struct conditional
    { typedef _Iftrue type; };
  template<typename _Iftrue, typename _Iffalse>
    struct conditional<false, _Iftrue, _Iffalse>
    { typedef _Iffalse type; };
  template<typename... _Tp>
    struct common_type;
  struct __do_common_type_impl
  {
    template<typename _Tp, typename _Up>
      static __success_type<typename decay<decltype
       (true ? std::declval<_Tp>()
        : std::declval<_Up>())>::type> _S_test(int);
    template<typename, typename>
      static __failure_type _S_test(...);
  };
  template<typename _Tp, typename _Up>
    struct __common_type_impl
    : private __do_common_type_impl
    {
      typedef decltype(_S_test<_Tp, _Up>(0)) type;
    };
  struct __do_member_type_wrapper
  {
    template<typename _Tp>
      static __success_type<typename _Tp::type> _S_test(int);
    template<typename>
      static __failure_type _S_test(...);
  };
  template<typename _Tp>
    struct __member_type_wrapper
    : private __do_member_type_wrapper
    {
      typedef decltype(_S_test<_Tp>(0)) type;
    };
  template<typename _CTp, typename... _Args>
    struct __expanded_common_type_wrapper
    {
      typedef common_type<typename _CTp::type, _Args...> type;
    };
  template<typename... _Args>
    struct __expanded_common_type_wrapper<__failure_type, _Args...>
    { typedef __failure_type type; };
  template<typename _Tp>
    struct common_type<_Tp>
    { typedef typename decay<_Tp>::type type; };
  template<typename _Tp, typename _Up>
    struct common_type<_Tp, _Up>
    : public __common_type_impl<_Tp, _Up>::type
    { };
  template<typename _Tp, typename _Up, typename... _Vp>
    struct common_type<_Tp, _Up, _Vp...>
    : public __expanded_common_type_wrapper<typename __member_type_wrapper<
               common_type<_Tp, _Up>>::type, _Vp...>::type
    { };
  template<typename _Tp>
    struct underlying_type
    {
      typedef __underlying_type(_Tp) type;
    };
  template<typename _Tp>
    struct __declval_protector
    {
      static const bool __stop = false;
      static typename add_rvalue_reference<_Tp>::type __delegate();
    };
  template<typename _Tp>
    inline typename add_rvalue_reference<_Tp>::type
    declval() noexcept
    {
      static_assert(__declval_protector<_Tp>::__stop,
      "declval() must not be used!");
      return __declval_protector<_Tp>::__delegate();
    }
  template<typename _Signature>
    class result_of;
  struct __result_of_memfun_ref_impl
  {
    template<typename _Fp, typename _Tp1, typename... _Args>
      static __success_type<decltype(
      (std::declval<_Tp1>().*std::declval<_Fp>())(std::declval<_Args>()...)
      )> _S_test(int);
    template<typename...>
      static __failure_type _S_test(...);
  };
  template<typename _MemPtr, typename _Arg, typename... _Args>
    struct __result_of_memfun_ref
    : private __result_of_memfun_ref_impl
    {
      typedef decltype(_S_test<_MemPtr, _Arg, _Args...>(0)) type;
    };
  struct __result_of_memfun_deref_impl
  {
    template<typename _Fp, typename _Tp1, typename... _Args>
      static __success_type<decltype(
      ((*std::declval<_Tp1>()).*std::declval<_Fp>())(std::declval<_Args>()...)
      )> _S_test(int);
    template<typename...>
      static __failure_type _S_test(...);
  };
  template<typename _MemPtr, typename _Arg, typename... _Args>
    struct __result_of_memfun_deref
    : private __result_of_memfun_deref_impl
    {
      typedef decltype(_S_test<_MemPtr, _Arg, _Args...>(0)) type;
    };
  struct __result_of_memobj_ref_impl
  {
    template<typename _Fp, typename _Tp1>
      static __success_type<decltype(
      std::declval<_Tp1>().*std::declval<_Fp>()
      )> _S_test(int);
    template<typename, typename>
      static __failure_type _S_test(...);
  };
  template<typename _MemPtr, typename _Arg>
    struct __result_of_memobj_ref
    : private __result_of_memobj_ref_impl
    {
      typedef decltype(_S_test<_MemPtr, _Arg>(0)) type;
    };
  struct __result_of_memobj_deref_impl
  {
    template<typename _Fp, typename _Tp1>
      static __success_type<decltype(
      (*std::declval<_Tp1>()).*std::declval<_Fp>()
      )> _S_test(int);
    template<typename, typename>
      static __failure_type _S_test(...);
  };
  template<typename _MemPtr, typename _Arg>
    struct __result_of_memobj_deref
    : private __result_of_memobj_deref_impl
    {
      typedef decltype(_S_test<_MemPtr, _Arg>(0)) type;
    };
  template<typename _MemPtr, typename _Arg>
    struct __result_of_memobj;
  template<typename _Res, typename _Class, typename _Arg>
    struct __result_of_memobj<_Res _Class::*, _Arg>
    {
      typedef typename remove_cv<typename remove_reference<
        _Arg>::type>::type _Argval;
      typedef _Res _Class::* _MemPtr;
      typedef typename conditional<__or_<is_same<_Argval, _Class>,
        is_base_of<_Class, _Argval>>::value,
        __result_of_memobj_ref<_MemPtr, _Arg>,
        __result_of_memobj_deref<_MemPtr, _Arg>
      >::type::type type;
    };
  template<typename _MemPtr, typename _Arg, typename... _Args>
    struct __result_of_memfun;
  template<typename _Res, typename _Class, typename _Arg, typename... _Args>
    struct __result_of_memfun<_Res _Class::*, _Arg, _Args...>
    {
      typedef typename remove_cv<typename remove_reference<
        _Arg>::type>::type _Argval;
      typedef _Res _Class::* _MemPtr;
      typedef typename conditional<__or_<is_same<_Argval, _Class>,
        is_base_of<_Class, _Argval>>::value,
        __result_of_memfun_ref<_MemPtr, _Arg, _Args...>,
        __result_of_memfun_deref<_MemPtr, _Arg, _Args...>
      >::type::type type;
    };
  template<bool, bool, typename _Functor, typename... _ArgTypes>
    struct __result_of_impl
    {
      typedef __failure_type type;
    };
  template<typename _MemPtr, typename _Arg>
    struct __result_of_impl<true, false, _MemPtr, _Arg>
    : public __result_of_memobj<typename decay<_MemPtr>::type, _Arg>
    { };
  template<typename _MemPtr, typename _Arg, typename... _Args>
    struct __result_of_impl<false, true, _MemPtr, _Arg, _Args...>
    : public __result_of_memfun<typename decay<_MemPtr>::type, _Arg, _Args...>
    { };
  struct __result_of_other_impl
  {
    template<typename _Fn, typename... _Args>
      static __success_type<decltype(
      std::declval<_Fn>()(std::declval<_Args>()...)
      )> _S_test(int);
    template<typename...>
      static __failure_type _S_test(...);
  };
  template<typename _Functor, typename... _ArgTypes>
    struct __result_of_impl<false, false, _Functor, _ArgTypes...>
    : private __result_of_other_impl
    {
      typedef decltype(_S_test<_Functor, _ArgTypes...>(0)) type;
    };
  template<typename _Functor, typename... _ArgTypes>
    struct result_of<_Functor(_ArgTypes...)>
    : public __result_of_impl<
        is_member_object_pointer<
          typename remove_reference<_Functor>::type
        >::value,
        is_member_function_pointer<
          typename remove_reference<_Functor>::type
        >::value,
     _Functor, _ArgTypes...
      >::type
    { };

}
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename _Tp>
    constexpr _Tp&&
    forward(typename std::remove_reference<_Tp>::type& __t) noexcept
    { return static_cast<_Tp&&>(__t); }
  template<typename _Tp>
    constexpr _Tp&&
    forward(typename std::remove_reference<_Tp>::type&& __t) noexcept
    {
      static_assert(!std::is_lvalue_reference<_Tp>::value, "template argument"
      " substituting _Tp is an lvalue reference type");
      return static_cast<_Tp&&>(__t);
    }
  template<typename _Tp>
    constexpr typename std::remove_reference<_Tp>::type&&
    move(_Tp&& __t) noexcept
    { return static_cast<typename std::remove_reference<_Tp>::type&&>(__t); }
  template<typename _Tp>
    struct __move_if_noexcept_cond
    : public __and_<__not_<is_nothrow_move_constructible<_Tp>>,
                    is_copy_constructible<_Tp>>::type { };
  template<typename _Tp>
    constexpr typename
    conditional<__move_if_noexcept_cond<_Tp>::value, const _Tp&, _Tp&&>::type
    move_if_noexcept(_Tp& __x) noexcept
    { return std::move(__x); }
  template<typename _Tp>
    inline _Tp*
    addressof(_Tp& __r) noexcept
    { return std::__addressof(__r); }

}
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename _Tp>
    inline void
    swap(_Tp& __a, _Tp& __b)
    noexcept(__and_<is_nothrow_move_constructible<_Tp>,
             is_nothrow_move_assignable<_Tp>>::value)
    {
     
      _Tp __tmp = std::move(__a);
      __a = std::move(__b);
      __b = std::move(__tmp);
    }
  template<typename _Tp, size_t _Nm>
    inline void
    swap(_Tp (&__a)[_Nm], _Tp (&__b)[_Nm])
    noexcept(noexcept(swap(*__a, *__b)))
    {
      for (size_t __n = 0; __n < _Nm; ++__n)
 swap(__a[__n], __b[__n]);
    }

}
namespace std __attribute__ ((__visibility__ ("default")))
{

  struct piecewise_construct_t { };
  constexpr piecewise_construct_t piecewise_construct = piecewise_construct_t();
  template<typename...>
    class tuple;
  template<std::size_t...>
    struct _Index_tuple;
  template<class _T1, class _T2>
    struct pair
    {
      typedef _T1 first_type;
      typedef _T2 second_type;
      _T1 first;
      _T2 second;
      constexpr pair()
      : first(), second() { }
      constexpr pair(const _T1& __a, const _T2& __b)
      : first(__a), second(__b) { }
      template<class _U1, class _U2, class = typename
        enable_if<__and_<is_convertible<const _U1&, _T1>,
    is_convertible<const _U2&, _T2>>::value>::type>
 constexpr pair(const pair<_U1, _U2>& __p)
 : first(__p.first), second(__p.second) { }
      constexpr pair(const pair&) = default;
      constexpr pair(pair&&) = default;
      template<class _U1, class = typename
        enable_if<is_convertible<_U1, _T1>::value>::type>
 constexpr pair(_U1&& __x, const _T2& __y)
 : first(std::forward<_U1>(__x)), second(__y) { }
      template<class _U2, class = typename
        enable_if<is_convertible<_U2, _T2>::value>::type>
 constexpr pair(const _T1& __x, _U2&& __y)
 : first(__x), second(std::forward<_U2>(__y)) { }
      template<class _U1, class _U2, class = typename
        enable_if<__and_<is_convertible<_U1, _T1>,
    is_convertible<_U2, _T2>>::value>::type>
 constexpr pair(_U1&& __x, _U2&& __y)
 : first(std::forward<_U1>(__x)), second(std::forward<_U2>(__y)) { }
      template<class _U1, class _U2, class = typename
        enable_if<__and_<is_convertible<_U1, _T1>,
    is_convertible<_U2, _T2>>::value>::type>
 constexpr pair(pair<_U1, _U2>&& __p)
 : first(std::forward<_U1>(__p.first)),
   second(std::forward<_U2>(__p.second)) { }
      template<typename... _Args1, typename... _Args2>
        pair(piecewise_construct_t, tuple<_Args1...>, tuple<_Args2...>);
      pair&
      operator=(const pair& __p)
      {
 first = __p.first;
 second = __p.second;
 return *this;
      }
      pair&
      operator=(pair&& __p)
      noexcept(__and_<is_nothrow_move_assignable<_T1>,
               is_nothrow_move_assignable<_T2>>::value)
      {
 first = std::forward<first_type>(__p.first);
 second = std::forward<second_type>(__p.second);
 return *this;
      }
      template<class _U1, class _U2>
 pair&
 operator=(const pair<_U1, _U2>& __p)
 {
   first = __p.first;
   second = __p.second;
   return *this;
 }
      template<class _U1, class _U2>
 pair&
 operator=(pair<_U1, _U2>&& __p)
 {
   first = std::forward<_U1>(__p.first);
   second = std::forward<_U2>(__p.second);
   return *this;
 }
      void
      swap(pair& __p)
      noexcept(noexcept(swap(first, __p.first))
        && noexcept(swap(second, __p.second)))
      {
 using std::swap;
 swap(first, __p.first);
 swap(second, __p.second);
      }
    private:
      template<typename... _Args1, std::size_t... _Indexes1,
               typename... _Args2, std::size_t... _Indexes2>
        pair(tuple<_Args1...>&, tuple<_Args2...>&,
             _Index_tuple<_Indexes1...>, _Index_tuple<_Indexes2...>);
    };
  template<class _T1, class _T2>
    inline constexpr bool
    operator==(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    { return __x.first == __y.first && __x.second == __y.second; }
  template<class _T1, class _T2>
    inline constexpr bool
    operator<(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    { return __x.first < __y.first
      || (!(__y.first < __x.first) && __x.second < __y.second); }
  template<class _T1, class _T2>
    inline constexpr bool
    operator!=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    { return !(__x == __y); }
  template<class _T1, class _T2>
    inline constexpr bool
    operator>(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    { return __y < __x; }
  template<class _T1, class _T2>
    inline constexpr bool
    operator<=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    { return !(__y < __x); }
  template<class _T1, class _T2>
    inline constexpr bool
    operator>=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
    { return !(__x < __y); }
  template<class _T1, class _T2>
    inline void
    swap(pair<_T1, _T2>& __x, pair<_T1, _T2>& __y)
    noexcept(noexcept(__x.swap(__y)))
    { __x.swap(__y); }
  template<class _T1, class _T2>
    constexpr pair<typename __decay_and_strip<_T1>::__type,
                   typename __decay_and_strip<_T2>::__type>
    make_pair(_T1&& __x, _T2&& __y)
    {
      typedef typename __decay_and_strip<_T1>::__type __ds_type1;
      typedef typename __decay_and_strip<_T2>::__type __ds_type2;
      typedef pair<__ds_type1, __ds_type2> __pair_type;
      return __pair_type(std::forward<_T1>(__x), std::forward<_T2>(__y));
    }

}
       
namespace std __attribute__ ((__visibility__ ("default")))
{

  struct input_iterator_tag { };
  struct output_iterator_tag { };
  struct forward_iterator_tag : public input_iterator_tag { };
  struct bidirectional_iterator_tag : public forward_iterator_tag { };
  struct random_access_iterator_tag : public bidirectional_iterator_tag { };
  template<typename _Category, typename _Tp, typename _Distance = ptrdiff_t,
           typename _Pointer = _Tp*, typename _Reference = _Tp&>
    struct iterator
    {
      typedef _Category iterator_category;
      typedef _Tp value_type;
      typedef _Distance difference_type;
      typedef _Pointer pointer;
      typedef _Reference reference;
    };
template<typename _Tp> class __has_iterator_category_helper { template<typename _Up> struct _Wrap_type { }; template<typename _Up> static true_type __test(_Wrap_type<typename _Up::iterator_category>*); template<typename _Up> static false_type __test(...); public: typedef decltype(__test<_Tp>(0)) type; }; template<typename _Tp> struct __has_iterator_category : public __has_iterator_category_helper <typename remove_cv<_Tp>::type>::type { };
  template<typename _Iterator,
    bool = __has_iterator_category<_Iterator>::value>
    struct __iterator_traits { };
  template<typename _Iterator>
    struct __iterator_traits<_Iterator, true>
    {
      typedef typename _Iterator::iterator_category iterator_category;
      typedef typename _Iterator::value_type value_type;
      typedef typename _Iterator::difference_type difference_type;
      typedef typename _Iterator::pointer pointer;
      typedef typename _Iterator::reference reference;
    };
  template<typename _Iterator>
    struct iterator_traits
    : public __iterator_traits<_Iterator> { };
  template<typename _Tp>
    struct iterator_traits<_Tp*>
    {
      typedef random_access_iterator_tag iterator_category;
      typedef _Tp value_type;
      typedef ptrdiff_t difference_type;
      typedef _Tp* pointer;
      typedef _Tp& reference;
    };
  template<typename _Tp>
    struct iterator_traits<const _Tp*>
    {
      typedef random_access_iterator_tag iterator_category;
      typedef _Tp value_type;
      typedef ptrdiff_t difference_type;
      typedef const _Tp* pointer;
      typedef const _Tp& reference;
    };
  template<typename _Iter>
    inline typename iterator_traits<_Iter>::iterator_category
    __iterator_category(const _Iter&)
    { return typename iterator_traits<_Iter>::iterator_category(); }
  template<typename _Iterator, bool _HasBase>
    struct _Iter_base
    {
      typedef _Iterator iterator_type;
      static iterator_type _S_base(_Iterator __it)
      { return __it; }
    };
  template<typename _Iterator>
    struct _Iter_base<_Iterator, true>
    {
      typedef typename _Iterator::iterator_type iterator_type;
      static iterator_type _S_base(_Iterator __it)
      { return __it.base(); }
    };
  template<typename _InIter>
    using _RequireInputIter = typename
      enable_if<is_convertible<typename
  iterator_traits<_InIter>::iterator_category,
          input_iterator_tag>::value>::type;

}
       
namespace std
{
  namespace __debug { }
}
namespace __gnu_debug
{
  using namespace std::__debug;
}
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename _InputIterator>
    inline typename iterator_traits<_InputIterator>::difference_type
    __distance(_InputIterator __first, _InputIterator __last,
               input_iterator_tag)
    {
     
      typename iterator_traits<_InputIterator>::difference_type __n = 0;
      while (__first != __last)
 {
   ++__first;
   ++__n;
 }
      return __n;
    }
  template<typename _RandomAccessIterator>
    inline typename iterator_traits<_RandomAccessIterator>::difference_type
    __distance(_RandomAccessIterator __first, _RandomAccessIterator __last,
               random_access_iterator_tag)
    {
     
      return __last - __first;
    }
  template<typename _InputIterator>
    inline typename iterator_traits<_InputIterator>::difference_type
    distance(_InputIterator __first, _InputIterator __last)
    {
      return std::__distance(__first, __last,
        std::__iterator_category(__first));
    }
  template<typename _InputIterator, typename _Distance>
    inline void
    __advance(_InputIterator& __i, _Distance __n, input_iterator_tag)
    {
     
      ;
      while (__n--)
 ++__i;
    }
  template<typename _BidirectionalIterator, typename _Distance>
    inline void
    __advance(_BidirectionalIterator& __i, _Distance __n,
       bidirectional_iterator_tag)
    {
     
      if (__n > 0)
        while (__n--)
   ++__i;
      else
        while (__n++)
   --__i;
    }
  template<typename _RandomAccessIterator, typename _Distance>
    inline void
    __advance(_RandomAccessIterator& __i, _Distance __n,
              random_access_iterator_tag)
    {
     
      __i += __n;
    }
  template<typename _InputIterator, typename _Distance>
    inline void
    advance(_InputIterator& __i, _Distance __n)
    {
      typename iterator_traits<_InputIterator>::difference_type __d = __n;
      std::__advance(__i, __d, std::__iterator_category(__i));
    }
  template<typename _ForwardIterator>
    inline _ForwardIterator
    next(_ForwardIterator __x, typename
  iterator_traits<_ForwardIterator>::difference_type __n = 1)
    {
      std::advance(__x, __n);
      return __x;
    }
  template<typename _BidirectionalIterator>
    inline _BidirectionalIterator
    prev(_BidirectionalIterator __x, typename
  iterator_traits<_BidirectionalIterator>::difference_type __n = 1)
    {
      std::advance(__x, -__n);
      return __x;
    }

}
namespace std __attribute__ ((__visibility__ ("default")))
{

template<typename _Tp> class __has_element_type_helper { template<typename _Up> struct _Wrap_type { }; template<typename _Up> static true_type __test(_Wrap_type<typename _Up::element_type>*); template<typename _Up> static false_type __test(...); public: typedef decltype(__test<_Tp>(0)) type; }; template<typename _Tp> struct __has_element_type : public __has_element_type_helper <typename remove_cv<_Tp>::type>::type { };
template<typename _Tp> class __has_difference_type_helper { template<typename _Up> struct _Wrap_type { }; template<typename _Up> static true_type __test(_Wrap_type<typename _Up::difference_type>*); template<typename _Up> static false_type __test(...); public: typedef decltype(__test<_Tp>(0)) type; }; template<typename _Tp> struct __has_difference_type : public __has_difference_type_helper <typename remove_cv<_Tp>::type>::type { };
  template<typename _Tp, bool = __has_element_type<_Tp>::value>
    struct __ptrtr_elt_type;
  template<typename _Tp>
    struct __ptrtr_elt_type<_Tp, true>
    {
      typedef typename _Tp::element_type __type;
    };
  template<template<typename, typename...> class _SomePtr, typename _Tp,
            typename... _Args>
    struct __ptrtr_elt_type<_SomePtr<_Tp, _Args...>, false>
    {
      typedef _Tp __type;
    };
  template<typename _Tp, bool = __has_difference_type<_Tp>::value>
    struct __ptrtr_diff_type
    {
      typedef typename _Tp::difference_type __type;
    };
  template<typename _Tp>
    struct __ptrtr_diff_type<_Tp, false>
    {
      typedef ptrdiff_t __type;
    };
  template<typename _Ptr, typename _Up>
    class __ptrtr_rebind_helper
    {
      template<typename _Ptr2, typename _Up2>
 static constexpr true_type
 _S_chk(typename _Ptr2::template rebind<_Up2>*);
      template<typename, typename>
 static constexpr false_type
 _S_chk(...);
    public:
      using __type = decltype(_S_chk<_Ptr, _Up>(nullptr));
    };
  template<typename _Tp, typename _Up,
           bool = __ptrtr_rebind_helper<_Tp, _Up>::__type::value>
    struct __ptrtr_rebind;
  template<typename _Tp, typename _Up>
    struct __ptrtr_rebind<_Tp, _Up, true>
    {
      typedef typename _Tp::template rebind<_Up> __type;
    };
  template<template<typename, typename...> class _SomePtr, typename _Up,
            typename _Tp, typename... _Args>
    struct __ptrtr_rebind<_SomePtr<_Tp, _Args...>, _Up, false>
    {
      typedef _SomePtr<_Up, _Args...> __type;
    };
  template<typename _Tp, typename = typename remove_cv<_Tp>::type>
    struct __ptrtr_not_void
    {
      typedef _Tp __type;
    };
  template<typename _Tp>
    struct __ptrtr_not_void<_Tp, void>
    {
      struct __type { };
    };
  template<typename _Ptr>
    class __ptrtr_pointer_to
    {
      typedef typename __ptrtr_elt_type<_Ptr>::__type __orig_type;
      typedef typename __ptrtr_not_void<__orig_type>::__type __element_type;
    public:
      static _Ptr pointer_to(__element_type& __e)
      { return _Ptr::pointer_to(__e); }
    };
  template<typename _Ptr>
    struct pointer_traits : __ptrtr_pointer_to<_Ptr>
    {
      typedef _Ptr pointer;
      typedef typename __ptrtr_elt_type<_Ptr>::__type element_type;
      typedef typename __ptrtr_diff_type<_Ptr>::__type difference_type;
      template<typename _Up>
        using rebind = typename __ptrtr_rebind<_Ptr, _Up>::__type;
    };
  template<typename _Tp>
    struct pointer_traits<_Tp*>
    {
      typedef _Tp* pointer;
      typedef _Tp element_type;
      typedef ptrdiff_t difference_type;
      template<typename _Up>
        using rebind = _Up*;
      static pointer
      pointer_to(typename __ptrtr_not_void<element_type>::__type& __r) noexcept
      { return std::addressof(__r); }
    };

}
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename _Iterator>
    class reverse_iterator
    : public iterator<typename iterator_traits<_Iterator>::iterator_category,
        typename iterator_traits<_Iterator>::value_type,
        typename iterator_traits<_Iterator>::difference_type,
        typename iterator_traits<_Iterator>::pointer,
                      typename iterator_traits<_Iterator>::reference>
    {
    protected:
      _Iterator current;
      typedef iterator_traits<_Iterator> __traits_type;
    public:
      typedef _Iterator iterator_type;
      typedef typename __traits_type::difference_type difference_type;
      typedef typename __traits_type::pointer pointer;
      typedef typename __traits_type::reference reference;
      reverse_iterator() : current() { }
      explicit
      reverse_iterator(iterator_type __x) : current(__x) { }
      reverse_iterator(const reverse_iterator& __x)
      : current(__x.current) { }
      template<typename _Iter>
        reverse_iterator(const reverse_iterator<_Iter>& __x)
 : current(__x.base()) { }
      iterator_type
      base() const
      { return current; }
      reference
      operator*() const
      {
 _Iterator __tmp = current;
 return *--__tmp;
      }
      pointer
      operator->() const
      { return &(operator*()); }
      reverse_iterator&
      operator++()
      {
 --current;
 return *this;
      }
      reverse_iterator
      operator++(int)
      {
 reverse_iterator __tmp = *this;
 --current;
 return __tmp;
      }
      reverse_iterator&
      operator--()
      {
 ++current;
 return *this;
      }
      reverse_iterator
      operator--(int)
      {
 reverse_iterator __tmp = *this;
 ++current;
 return __tmp;
      }
      reverse_iterator
      operator+(difference_type __n) const
      { return reverse_iterator(current - __n); }
      reverse_iterator&
      operator+=(difference_type __n)
      {
 current -= __n;
 return *this;
      }
      reverse_iterator
      operator-(difference_type __n) const
      { return reverse_iterator(current + __n); }
      reverse_iterator&
      operator-=(difference_type __n)
      {
 current += __n;
 return *this;
      }
      reference
      operator[](difference_type __n) const
      { return *(*this + __n); }
    };
  template<typename _Iterator>
    inline bool
    operator==(const reverse_iterator<_Iterator>& __x,
        const reverse_iterator<_Iterator>& __y)
    { return __x.base() == __y.base(); }
  template<typename _Iterator>
    inline bool
    operator<(const reverse_iterator<_Iterator>& __x,
       const reverse_iterator<_Iterator>& __y)
    { return __y.base() < __x.base(); }
  template<typename _Iterator>
    inline bool
    operator!=(const reverse_iterator<_Iterator>& __x,
        const reverse_iterator<_Iterator>& __y)
    { return !(__x == __y); }
  template<typename _Iterator>
    inline bool
    operator>(const reverse_iterator<_Iterator>& __x,
       const reverse_iterator<_Iterator>& __y)
    { return __y < __x; }
  template<typename _Iterator>
    inline bool
    operator<=(const reverse_iterator<_Iterator>& __x,
        const reverse_iterator<_Iterator>& __y)
    { return !(__y < __x); }
  template<typename _Iterator>
    inline bool
    operator>=(const reverse_iterator<_Iterator>& __x,
        const reverse_iterator<_Iterator>& __y)
    { return !(__x < __y); }
  template<typename _Iterator>
    inline typename reverse_iterator<_Iterator>::difference_type
    operator-(const reverse_iterator<_Iterator>& __x,
       const reverse_iterator<_Iterator>& __y)
    { return __y.base() - __x.base(); }
  template<typename _Iterator>
    inline reverse_iterator<_Iterator>
    operator+(typename reverse_iterator<_Iterator>::difference_type __n,
       const reverse_iterator<_Iterator>& __x)
    { return reverse_iterator<_Iterator>(__x.base() - __n); }
  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator==(const reverse_iterator<_IteratorL>& __x,
        const reverse_iterator<_IteratorR>& __y)
    { return __x.base() == __y.base(); }
  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator<(const reverse_iterator<_IteratorL>& __x,
       const reverse_iterator<_IteratorR>& __y)
    { return __y.base() < __x.base(); }
  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator!=(const reverse_iterator<_IteratorL>& __x,
        const reverse_iterator<_IteratorR>& __y)
    { return !(__x == __y); }
  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator>(const reverse_iterator<_IteratorL>& __x,
       const reverse_iterator<_IteratorR>& __y)
    { return __y < __x; }
  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator<=(const reverse_iterator<_IteratorL>& __x,
        const reverse_iterator<_IteratorR>& __y)
    { return !(__y < __x); }
  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator>=(const reverse_iterator<_IteratorL>& __x,
        const reverse_iterator<_IteratorR>& __y)
    { return !(__x < __y); }
  template<typename _IteratorL, typename _IteratorR>
    inline auto
    operator-(const reverse_iterator<_IteratorL>& __x,
       const reverse_iterator<_IteratorR>& __y)
    -> decltype(__y.base() - __x.base())
    { return __y.base() - __x.base(); }
  template<typename _Container>
    class back_insert_iterator
    : public iterator<output_iterator_tag, void, void, void, void>
    {
    protected:
      _Container* container;
    public:
      typedef _Container container_type;
      explicit
      back_insert_iterator(_Container& __x) : container(&__x) { }
      back_insert_iterator&
      operator=(const typename _Container::value_type& __value)
      {
 container->push_back(__value);
 return *this;
      }
      back_insert_iterator&
      operator=(typename _Container::value_type&& __value)
      {
 container->push_back(std::move(__value));
 return *this;
      }
      back_insert_iterator&
      operator*()
      { return *this; }
      back_insert_iterator&
      operator++()
      { return *this; }
      back_insert_iterator
      operator++(int)
      { return *this; }
    };
  template<typename _Container>
    inline back_insert_iterator<_Container>
    back_inserter(_Container& __x)
    { return back_insert_iterator<_Container>(__x); }
  template<typename _Container>
    class front_insert_iterator
    : public iterator<output_iterator_tag, void, void, void, void>
    {
    protected:
      _Container* container;
    public:
      typedef _Container container_type;
      explicit front_insert_iterator(_Container& __x) : container(&__x) { }
      front_insert_iterator&
      operator=(const typename _Container::value_type& __value)
      {
 container->push_front(__value);
 return *this;
      }
      front_insert_iterator&
      operator=(typename _Container::value_type&& __value)
      {
 container->push_front(std::move(__value));
 return *this;
      }
      front_insert_iterator&
      operator*()
      { return *this; }
      front_insert_iterator&
      operator++()
      { return *this; }
      front_insert_iterator
      operator++(int)
      { return *this; }
    };
  template<typename _Container>
    inline front_insert_iterator<_Container>
    front_inserter(_Container& __x)
    { return front_insert_iterator<_Container>(__x); }
  template<typename _Container>
    class insert_iterator
    : public iterator<output_iterator_tag, void, void, void, void>
    {
    protected:
      _Container* container;
      typename _Container::iterator iter;
    public:
      typedef _Container container_type;
      insert_iterator(_Container& __x, typename _Container::iterator __i)
      : container(&__x), iter(__i) {}
      insert_iterator&
      operator=(const typename _Container::value_type& __value)
      {
 iter = container->insert(iter, __value);
 ++iter;
 return *this;
      }
      insert_iterator&
      operator=(typename _Container::value_type&& __value)
      {
 iter = container->insert(iter, std::move(__value));
 ++iter;
 return *this;
      }
      insert_iterator&
      operator*()
      { return *this; }
      insert_iterator&
      operator++()
      { return *this; }
      insert_iterator&
      operator++(int)
      { return *this; }
    };
  template<typename _Container, typename _Iterator>
    inline insert_iterator<_Container>
    inserter(_Container& __x, _Iterator __i)
    {
      return insert_iterator<_Container>(__x,
      typename _Container::iterator(__i));
    }

}
namespace __gnu_cxx __attribute__ ((__visibility__ ("default")))
{

  using std::iterator_traits;
  using std::iterator;
  template<typename _Iterator, typename _Container>
    class __normal_iterator
    {
    protected:
      _Iterator _M_current;
      typedef iterator_traits<_Iterator> __traits_type;
    public:
      typedef _Iterator iterator_type;
      typedef typename __traits_type::iterator_category iterator_category;
      typedef typename __traits_type::value_type value_type;
      typedef typename __traits_type::difference_type difference_type;
      typedef typename __traits_type::reference reference;
      typedef typename __traits_type::pointer pointer;
      constexpr __normal_iterator() noexcept
      : _M_current(_Iterator()) { }
      explicit
      __normal_iterator(const _Iterator& __i) noexcept
      : _M_current(__i) { }
      template<typename _Iter>
        __normal_iterator(const __normal_iterator<_Iter,
     typename __enable_if<
              (std::__are_same<_Iter, typename _Container::pointer>::__value),
        _Container>::__type>& __i) noexcept
        : _M_current(__i.base()) { }
      reference
      operator*() const noexcept
      { return *_M_current; }
      pointer
      operator->() const noexcept
      { return _M_current; }
      __normal_iterator&
      operator++() noexcept
      {
 ++_M_current;
 return *this;
      }
      __normal_iterator
      operator++(int) noexcept
      { return __normal_iterator(_M_current++); }
      __normal_iterator&
      operator--() noexcept
      {
 --_M_current;
 return *this;
      }
      __normal_iterator
      operator--(int) noexcept
      { return __normal_iterator(_M_current--); }
      reference
      operator[](difference_type __n) const noexcept
      { return _M_current[__n]; }
      __normal_iterator&
      operator+=(difference_type __n) noexcept
      { _M_current += __n; return *this; }
      __normal_iterator
      operator+(difference_type __n) const noexcept
      { return __normal_iterator(_M_current + __n); }
      __normal_iterator&
      operator-=(difference_type __n) noexcept
      { _M_current -= __n; return *this; }
      __normal_iterator
      operator-(difference_type __n) const noexcept
      { return __normal_iterator(_M_current - __n); }
      const _Iterator&
      base() const noexcept
      { return _M_current; }
    };
  template<typename _IteratorL, typename _IteratorR, typename _Container>
    inline bool
    operator==(const __normal_iterator<_IteratorL, _Container>& __lhs,
        const __normal_iterator<_IteratorR, _Container>& __rhs)
    noexcept
    { return __lhs.base() == __rhs.base(); }
  template<typename _Iterator, typename _Container>
    inline bool
    operator==(const __normal_iterator<_Iterator, _Container>& __lhs,
        const __normal_iterator<_Iterator, _Container>& __rhs)
    noexcept
    { return __lhs.base() == __rhs.base(); }
  template<typename _IteratorL, typename _IteratorR, typename _Container>
    inline bool
    operator!=(const __normal_iterator<_IteratorL, _Container>& __lhs,
        const __normal_iterator<_IteratorR, _Container>& __rhs)
    noexcept
    { return __lhs.base() != __rhs.base(); }
  template<typename _Iterator, typename _Container>
    inline bool
    operator!=(const __normal_iterator<_Iterator, _Container>& __lhs,
        const __normal_iterator<_Iterator, _Container>& __rhs)
    noexcept
    { return __lhs.base() != __rhs.base(); }
  template<typename _IteratorL, typename _IteratorR, typename _Container>
    inline bool
    operator<(const __normal_iterator<_IteratorL, _Container>& __lhs,
       const __normal_iterator<_IteratorR, _Container>& __rhs)
    noexcept
    { return __lhs.base() < __rhs.base(); }
  template<typename _Iterator, typename _Container>
    inline bool
    operator<(const __normal_iterator<_Iterator, _Container>& __lhs,
       const __normal_iterator<_Iterator, _Container>& __rhs)
    noexcept
    { return __lhs.base() < __rhs.base(); }
  template<typename _IteratorL, typename _IteratorR, typename _Container>
    inline bool
    operator>(const __normal_iterator<_IteratorL, _Container>& __lhs,
       const __normal_iterator<_IteratorR, _Container>& __rhs)
    noexcept
    { return __lhs.base() > __rhs.base(); }
  template<typename _Iterator, typename _Container>
    inline bool
    operator>(const __normal_iterator<_Iterator, _Container>& __lhs,
       const __normal_iterator<_Iterator, _Container>& __rhs)
    noexcept
    { return __lhs.base() > __rhs.base(); }
  template<typename _IteratorL, typename _IteratorR, typename _Container>
    inline bool
    operator<=(const __normal_iterator<_IteratorL, _Container>& __lhs,
        const __normal_iterator<_IteratorR, _Container>& __rhs)
    noexcept
    { return __lhs.base() <= __rhs.base(); }
  template<typename _Iterator, typename _Container>
    inline bool
    operator<=(const __normal_iterator<_Iterator, _Container>& __lhs,
        const __normal_iterator<_Iterator, _Container>& __rhs)
    noexcept
    { return __lhs.base() <= __rhs.base(); }
  template<typename _IteratorL, typename _IteratorR, typename _Container>
    inline bool
    operator>=(const __normal_iterator<_IteratorL, _Container>& __lhs,
        const __normal_iterator<_IteratorR, _Container>& __rhs)
    noexcept
    { return __lhs.base() >= __rhs.base(); }
  template<typename _Iterator, typename _Container>
    inline bool
    operator>=(const __normal_iterator<_Iterator, _Container>& __lhs,
        const __normal_iterator<_Iterator, _Container>& __rhs)
    noexcept
    { return __lhs.base() >= __rhs.base(); }
  template<typename _IteratorL, typename _IteratorR, typename _Container>
    inline auto
    operator-(const __normal_iterator<_IteratorL, _Container>& __lhs,
       const __normal_iterator<_IteratorR, _Container>& __rhs) noexcept
    -> decltype(__lhs.base() - __rhs.base())
    { return __lhs.base() - __rhs.base(); }
  template<typename _Iterator, typename _Container>
    inline typename __normal_iterator<_Iterator, _Container>::difference_type
    operator-(const __normal_iterator<_Iterator, _Container>& __lhs,
       const __normal_iterator<_Iterator, _Container>& __rhs)
    noexcept
    { return __lhs.base() - __rhs.base(); }
  template<typename _Iterator, typename _Container>
    inline __normal_iterator<_Iterator, _Container>
    operator+(typename __normal_iterator<_Iterator, _Container>::difference_type
       __n, const __normal_iterator<_Iterator, _Container>& __i)
    noexcept
    { return __normal_iterator<_Iterator, _Container>(__i.base() + __n); }

}
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename _Iterator>
    class move_iterator
    {
    protected:
      _Iterator _M_current;
      typedef iterator_traits<_Iterator> __traits_type;
    public:
      typedef _Iterator iterator_type;
      typedef typename __traits_type::iterator_category iterator_category;
      typedef typename __traits_type::value_type value_type;
      typedef typename __traits_type::difference_type difference_type;
      typedef _Iterator pointer;
      typedef value_type&& reference;
      move_iterator()
      : _M_current() { }
      explicit
      move_iterator(iterator_type __i)
      : _M_current(__i) { }
      template<typename _Iter>
 move_iterator(const move_iterator<_Iter>& __i)
 : _M_current(__i.base()) { }
      iterator_type
      base() const
      { return _M_current; }
      reference
      operator*() const
      { return std::move(*_M_current); }
      pointer
      operator->() const
      { return _M_current; }
      move_iterator&
      operator++()
      {
 ++_M_current;
 return *this;
      }
      move_iterator
      operator++(int)
      {
 move_iterator __tmp = *this;
 ++_M_current;
 return __tmp;
      }
      move_iterator&
      operator--()
      {
 --_M_current;
 return *this;
      }
      move_iterator
      operator--(int)
      {
 move_iterator __tmp = *this;
 --_M_current;
 return __tmp;
      }
      move_iterator
      operator+(difference_type __n) const
      { return move_iterator(_M_current + __n); }
      move_iterator&
      operator+=(difference_type __n)
      {
 _M_current += __n;
 return *this;
      }
      move_iterator
      operator-(difference_type __n) const
      { return move_iterator(_M_current - __n); }
      move_iterator&
      operator-=(difference_type __n)
      {
 _M_current -= __n;
 return *this;
      }
      reference
      operator[](difference_type __n) const
      { return std::move(_M_current[__n]); }
    };
  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator==(const move_iterator<_IteratorL>& __x,
        const move_iterator<_IteratorR>& __y)
    { return __x.base() == __y.base(); }
  template<typename _Iterator>
    inline bool
    operator==(const move_iterator<_Iterator>& __x,
        const move_iterator<_Iterator>& __y)
    { return __x.base() == __y.base(); }
  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator!=(const move_iterator<_IteratorL>& __x,
        const move_iterator<_IteratorR>& __y)
    { return !(__x == __y); }
  template<typename _Iterator>
    inline bool
    operator!=(const move_iterator<_Iterator>& __x,
        const move_iterator<_Iterator>& __y)
    { return !(__x == __y); }
  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator<(const move_iterator<_IteratorL>& __x,
       const move_iterator<_IteratorR>& __y)
    { return __x.base() < __y.base(); }
  template<typename _Iterator>
    inline bool
    operator<(const move_iterator<_Iterator>& __x,
       const move_iterator<_Iterator>& __y)
    { return __x.base() < __y.base(); }
  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator<=(const move_iterator<_IteratorL>& __x,
        const move_iterator<_IteratorR>& __y)
    { return !(__y < __x); }
  template<typename _Iterator>
    inline bool
    operator<=(const move_iterator<_Iterator>& __x,
        const move_iterator<_Iterator>& __y)
    { return !(__y < __x); }
  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator>(const move_iterator<_IteratorL>& __x,
       const move_iterator<_IteratorR>& __y)
    { return __y < __x; }
  template<typename _Iterator>
    inline bool
    operator>(const move_iterator<_Iterator>& __x,
       const move_iterator<_Iterator>& __y)
    { return __y < __x; }
  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator>=(const move_iterator<_IteratorL>& __x,
        const move_iterator<_IteratorR>& __y)
    { return !(__x < __y); }
  template<typename _Iterator>
    inline bool
    operator>=(const move_iterator<_Iterator>& __x,
        const move_iterator<_Iterator>& __y)
    { return !(__x < __y); }
  template<typename _IteratorL, typename _IteratorR>
    inline auto
    operator-(const move_iterator<_IteratorL>& __x,
       const move_iterator<_IteratorR>& __y)
    -> decltype(__x.base() - __y.base())
    { return __x.base() - __y.base(); }
  template<typename _Iterator>
    inline auto
    operator-(const move_iterator<_Iterator>& __x,
       const move_iterator<_Iterator>& __y)
    -> decltype(__x.base() - __y.base())
    { return __x.base() - __y.base(); }
  template<typename _Iterator>
    inline move_iterator<_Iterator>
    operator+(typename move_iterator<_Iterator>::difference_type __n,
       const move_iterator<_Iterator>& __x)
    { return __x + __n; }
  template<typename _Iterator>
    inline move_iterator<_Iterator>
    make_move_iterator(_Iterator __i)
    { return move_iterator<_Iterator>(__i); }
  template<typename _Iterator, typename _ReturnType
    = typename conditional<__move_if_noexcept_cond
      <typename iterator_traits<_Iterator>::value_type>::value,
                _Iterator, move_iterator<_Iterator>>::type>
    inline _ReturnType
    __make_move_if_noexcept_iterator(_Iterator __i)
    { return _ReturnType(__i); }

}
namespace __gnu_cxx
{
namespace __ops
{
  struct _Iter_less_iter
  {
    template<typename _Iterator1, typename _Iterator2>
      bool
      operator()(_Iterator1 __it1, _Iterator2 __it2) const
      { return *__it1 < *__it2; }
  };
  inline _Iter_less_iter
  __iter_less_iter()
  { return _Iter_less_iter(); }
  struct _Iter_less_val
  {
    template<typename _Iterator, typename _Value>
      bool
      operator()(_Iterator __it, _Value& __val) const
      { return *__it < __val; }
    };
  inline _Iter_less_val
  __iter_less_val()
  { return _Iter_less_val(); }
  inline _Iter_less_val
  __iter_comp_val(_Iter_less_iter)
  { return _Iter_less_val(); }
  struct _Val_less_iter
  {
    template<typename _Value, typename _Iterator>
      bool
      operator()(_Value& __val, _Iterator __it) const
      { return __val < *__it; }
    };
  inline _Val_less_iter
  __val_less_iter()
  { return _Val_less_iter(); }
  inline _Val_less_iter
  __val_comp_iter(_Iter_less_iter)
  { return _Val_less_iter(); }
  struct _Iter_equal_to_iter
  {
    template<typename _Iterator1, typename _Iterator2>
      bool
      operator()(_Iterator1 __it1, _Iterator2 __it2) const
      { return *__it1 == *__it2; }
    };
  inline _Iter_equal_to_iter
  __iter_equal_to_iter()
  { return _Iter_equal_to_iter(); }
  struct _Iter_equal_to_val
  {
    template<typename _Iterator, typename _Value>
      bool
      operator()(_Iterator __it, _Value& __val) const
      { return *__it == __val; }
    };
  inline _Iter_equal_to_val
  __iter_equal_to_val()
  { return _Iter_equal_to_val(); }
  inline _Iter_equal_to_val
  __iter_comp_val(_Iter_equal_to_iter)
  { return _Iter_equal_to_val(); }
  template<typename _Compare>
    struct _Iter_comp_iter
    {
      _Compare _M_comp;
      _Iter_comp_iter(_Compare __comp)
 : _M_comp(__comp)
      { }
      template<typename _Iterator1, typename _Iterator2>
        bool
        operator()(_Iterator1 __it1, _Iterator2 __it2)
        { return bool(_M_comp(*__it1, *__it2)); }
    };
  template<typename _Compare>
    inline _Iter_comp_iter<_Compare>
    __iter_comp_iter(_Compare __comp)
    { return _Iter_comp_iter<_Compare>(__comp); }
  template<typename _Compare>
    struct _Iter_comp_val
    {
      _Compare _M_comp;
      _Iter_comp_val(_Compare __comp)
 : _M_comp(__comp)
      { }
      template<typename _Iterator, typename _Value>
 bool
 operator()(_Iterator __it, _Value& __val)
 { return bool(_M_comp(*__it, __val)); }
    };
  template<typename _Compare>
   inline _Iter_comp_val<_Compare>
    __iter_comp_val(_Compare __comp)
    { return _Iter_comp_val<_Compare>(__comp); }
  template<typename _Compare>
    inline _Iter_comp_val<_Compare>
    __iter_comp_val(_Iter_comp_iter<_Compare> __comp)
    { return _Iter_comp_val<_Compare>(__comp._M_comp); }
  template<typename _Compare>
    struct _Val_comp_iter
    {
      _Compare _M_comp;
      _Val_comp_iter(_Compare __comp)
 : _M_comp(__comp)
      { }
      template<typename _Value, typename _Iterator>
 bool
 operator()(_Value& __val, _Iterator __it)
 { return bool(_M_comp(__val, *__it)); }
    };
  template<typename _Compare>
    inline _Val_comp_iter<_Compare>
    __val_comp_iter(_Compare __comp)
    { return _Val_comp_iter<_Compare>(__comp); }
  template<typename _Compare>
    inline _Val_comp_iter<_Compare>
    __val_comp_iter(_Iter_comp_iter<_Compare> __comp)
    { return _Val_comp_iter<_Compare>(__comp._M_comp); }
  template<typename _Value>
    struct _Iter_equals_val
    {
      _Value& _M_value;
      _Iter_equals_val(_Value& __value)
 : _M_value(__value)
      { }
      template<typename _Iterator>
 bool
 operator()(_Iterator __it)
 { return *__it == _M_value; }
    };
  template<typename _Value>
    inline _Iter_equals_val<_Value>
    __iter_equals_val(_Value& __val)
    { return _Iter_equals_val<_Value>(__val); }
  template<typename _Iterator1>
    struct _Iter_equals_iter
    {
      typename std::iterator_traits<_Iterator1>::reference _M_ref;
      _Iter_equals_iter(_Iterator1 __it1)
 : _M_ref(*__it1)
      { }
      template<typename _Iterator2>
 bool
 operator()(_Iterator2 __it2)
 { return *__it2 == _M_ref; }
    };
  template<typename _Iterator>
    inline _Iter_equals_iter<_Iterator>
    __iter_comp_iter(_Iter_equal_to_iter, _Iterator __it)
    { return _Iter_equals_iter<_Iterator>(__it); }
  template<typename _Predicate>
    struct _Iter_pred
    {
      _Predicate _M_pred;
      _Iter_pred(_Predicate __pred)
 : _M_pred(__pred)
      { }
      template<typename _Iterator>
 bool
 operator()(_Iterator __it)
 { return bool(_M_pred(*__it)); }
    };
  template<typename _Predicate>
    inline _Iter_pred<_Predicate>
    __pred_iter(_Predicate __pred)
    { return _Iter_pred<_Predicate>(__pred); }
  template<typename _Compare, typename _Value>
    struct _Iter_comp_to_val
    {
      _Compare _M_comp;
      _Value& _M_value;
      _Iter_comp_to_val(_Compare __comp, _Value& __value)
 : _M_comp(__comp), _M_value(__value)
      { }
      template<typename _Iterator>
 bool
 operator()(_Iterator __it)
 { return bool(_M_comp(*__it, _M_value)); }
    };
  template<typename _Compare, typename _Value>
    _Iter_comp_to_val<_Compare, _Value>
    __iter_comp_val(_Compare __comp, _Value &__val)
    { return _Iter_comp_to_val<_Compare, _Value>(__comp, __val); }
  template<typename _Compare, typename _Iterator1>
    struct _Iter_comp_to_iter
    {
      _Compare _M_comp;
      typename std::iterator_traits<_Iterator1>::reference _M_ref;
      _Iter_comp_to_iter(_Compare __comp, _Iterator1 __it1)
 : _M_comp(__comp), _M_ref(*__it1)
      { }
      template<typename _Iterator2>
 bool
 operator()(_Iterator2 __it2)
 { return bool(_M_comp(*__it2, _M_ref)); }
    };
  template<typename _Compare, typename _Iterator>
    inline _Iter_comp_to_iter<_Compare, _Iterator>
    __iter_comp_iter(_Iter_comp_iter<_Compare> __comp, _Iterator __it)
    { return _Iter_comp_to_iter<_Compare, _Iterator>(__comp._M_comp, __it); }
  template<typename _Predicate>
    struct _Iter_negate
    {
      _Predicate _M_pred;
      _Iter_negate(_Predicate __pred)
 : _M_pred(__pred)
      { }
      template<typename _Iterator>
 bool
 operator()(_Iterator __it)
 { return !bool(_M_pred(*__it)); }
    };
  template<typename _Predicate>
    inline _Iter_negate<_Predicate>
    __negate(_Iter_pred<_Predicate> __pred)
    { return _Iter_negate<_Predicate>(__pred._M_pred); }
}
}
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename _ForwardIterator1, typename _ForwardIterator2>
    inline void
    iter_swap(_ForwardIterator1 __a, _ForwardIterator2 __b)
    {
     
     
      swap(*__a, *__b);
    }
  template<typename _ForwardIterator1, typename _ForwardIterator2>
    _ForwardIterator2
    swap_ranges(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
  _ForwardIterator2 __first2)
    {
     
     
      ;
      for (; __first1 != __last1; ++__first1, ++__first2)
 std::iter_swap(__first1, __first2);
      return __first2;
    }
  template<typename _Tp>
    inline const _Tp&
    min(const _Tp& __a, const _Tp& __b)
    {
     
      if (__b < __a)
 return __b;
      return __a;
    }
  template<typename _Tp>
    inline const _Tp&
    max(const _Tp& __a, const _Tp& __b)
    {
     
      if (__a < __b)
 return __b;
      return __a;
    }
  template<typename _Tp, typename _Compare>
    inline const _Tp&
    min(const _Tp& __a, const _Tp& __b, _Compare __comp)
    {
      if (__comp(__b, __a))
 return __b;
      return __a;
    }
  template<typename _Tp, typename _Compare>
    inline const _Tp&
    max(const _Tp& __a, const _Tp& __b, _Compare __comp)
    {
      if (__comp(__a, __b))
 return __b;
      return __a;
    }
  template<typename _Iterator>
    struct _Niter_base
    : _Iter_base<_Iterator, __is_normal_iterator<_Iterator>::__value>
    { };
  template<typename _Iterator>
    inline typename _Niter_base<_Iterator>::iterator_type
    __niter_base(_Iterator __it)
    { return std::_Niter_base<_Iterator>::_S_base(__it); }
  template<typename _Iterator>
    struct _Miter_base
    : _Iter_base<_Iterator, __is_move_iterator<_Iterator>::__value>
    { };
  template<typename _Iterator>
    inline typename _Miter_base<_Iterator>::iterator_type
    __miter_base(_Iterator __it)
    { return std::_Miter_base<_Iterator>::_S_base(__it); }
  template<bool, bool, typename>
    struct __copy_move
    {
      template<typename _II, typename _OI>
        static _OI
        __copy_m(_II __first, _II __last, _OI __result)
        {
   for (; __first != __last; ++__result, ++__first)
     *__result = *__first;
   return __result;
 }
    };
  template<typename _Category>
    struct __copy_move<true, false, _Category>
    {
      template<typename _II, typename _OI>
        static _OI
        __copy_m(_II __first, _II __last, _OI __result)
        {
   for (; __first != __last; ++__result, ++__first)
     *__result = std::move(*__first);
   return __result;
 }
    };
  template<>
    struct __copy_move<false, false, random_access_iterator_tag>
    {
      template<typename _II, typename _OI>
        static _OI
        __copy_m(_II __first, _II __last, _OI __result)
        {
   typedef typename iterator_traits<_II>::difference_type _Distance;
   for(_Distance __n = __last - __first; __n > 0; --__n)
     {
       *__result = *__first;
       ++__first;
       ++__result;
     }
   return __result;
 }
    };
  template<>
    struct __copy_move<true, false, random_access_iterator_tag>
    {
      template<typename _II, typename _OI>
        static _OI
        __copy_m(_II __first, _II __last, _OI __result)
        {
   typedef typename iterator_traits<_II>::difference_type _Distance;
   for(_Distance __n = __last - __first; __n > 0; --__n)
     {
       *__result = std::move(*__first);
       ++__first;
       ++__result;
     }
   return __result;
 }
    };
  template<bool _IsMove>
    struct __copy_move<_IsMove, true, random_access_iterator_tag>
    {
      template<typename _Tp>
        static _Tp*
        __copy_m(const _Tp* __first, const _Tp* __last, _Tp* __result)
        {
   static_assert( is_copy_assignable<_Tp>::value,
                  "type is not assignable" );
   const ptrdiff_t _Num = __last - __first;
   if (_Num)
     __builtin_memmove(__result, __first, sizeof(_Tp) * _Num);
   return __result + _Num;
 }
    };
  template<bool _IsMove, typename _II, typename _OI>
    inline _OI
    __copy_move_a(_II __first, _II __last, _OI __result)
    {
      typedef typename iterator_traits<_II>::value_type _ValueTypeI;
      typedef typename iterator_traits<_OI>::value_type _ValueTypeO;
      typedef typename iterator_traits<_II>::iterator_category _Category;
      const bool __simple = (__is_trivial(_ValueTypeI)
                      && __is_pointer<_II>::__value
                      && __is_pointer<_OI>::__value
        && __are_same<_ValueTypeI, _ValueTypeO>::__value);
      return std::__copy_move<_IsMove, __simple,
                       _Category>::__copy_m(__first, __last, __result);
    }
  template<typename _CharT>
    struct char_traits;
  template<typename _CharT, typename _Traits>
    class istreambuf_iterator;
  template<typename _CharT, typename _Traits>
    class ostreambuf_iterator;
  template<bool _IsMove, typename _CharT>
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value,
      ostreambuf_iterator<_CharT, char_traits<_CharT> > >::__type
    __copy_move_a2(_CharT*, _CharT*,
     ostreambuf_iterator<_CharT, char_traits<_CharT> >);
  template<bool _IsMove, typename _CharT>
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value,
      ostreambuf_iterator<_CharT, char_traits<_CharT> > >::__type
    __copy_move_a2(const _CharT*, const _CharT*,
     ostreambuf_iterator<_CharT, char_traits<_CharT> >);
  template<bool _IsMove, typename _CharT>
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value,
        _CharT*>::__type
    __copy_move_a2(istreambuf_iterator<_CharT, char_traits<_CharT> >,
     istreambuf_iterator<_CharT, char_traits<_CharT> >, _CharT*);
  template<bool _IsMove, typename _II, typename _OI>
    inline _OI
    __copy_move_a2(_II __first, _II __last, _OI __result)
    {
      return _OI(std::__copy_move_a<_IsMove>(std::__niter_base(__first),
          std::__niter_base(__last),
          std::__niter_base(__result)));
    }
  template<typename _II, typename _OI>
    inline _OI
    copy(_II __first, _II __last, _OI __result)
    {
     
     
      ;
      return (std::__copy_move_a2<__is_move_iterator<_II>::__value>
       (std::__miter_base(__first), std::__miter_base(__last),
        __result));
    }
  template<typename _II, typename _OI>
    inline _OI
    move(_II __first, _II __last, _OI __result)
    {
     
     
      ;
      return std::__copy_move_a2<true>(std::__miter_base(__first),
           std::__miter_base(__last), __result);
    }
  template<bool, bool, typename>
    struct __copy_move_backward
    {
      template<typename _BI1, typename _BI2>
        static _BI2
        __copy_move_b(_BI1 __first, _BI1 __last, _BI2 __result)
        {
   while (__first != __last)
     *--__result = *--__last;
   return __result;
 }
    };
  template<typename _Category>
    struct __copy_move_backward<true, false, _Category>
    {
      template<typename _BI1, typename _BI2>
        static _BI2
        __copy_move_b(_BI1 __first, _BI1 __last, _BI2 __result)
        {
   while (__first != __last)
     *--__result = std::move(*--__last);
   return __result;
 }
    };
  template<>
    struct __copy_move_backward<false, false, random_access_iterator_tag>
    {
      template<typename _BI1, typename _BI2>
        static _BI2
        __copy_move_b(_BI1 __first, _BI1 __last, _BI2 __result)
        {
   typename iterator_traits<_BI1>::difference_type __n;
   for (__n = __last - __first; __n > 0; --__n)
     *--__result = *--__last;
   return __result;
 }
    };
  template<>
    struct __copy_move_backward<true, false, random_access_iterator_tag>
    {
      template<typename _BI1, typename _BI2>
        static _BI2
        __copy_move_b(_BI1 __first, _BI1 __last, _BI2 __result)
        {
   typename iterator_traits<_BI1>::difference_type __n;
   for (__n = __last - __first; __n > 0; --__n)
     *--__result = std::move(*--__last);
   return __result;
 }
    };
  template<bool _IsMove>
    struct __copy_move_backward<_IsMove, true, random_access_iterator_tag>
    {
      template<typename _Tp>
        static _Tp*
        __copy_move_b(const _Tp* __first, const _Tp* __last, _Tp* __result)
        {
   static_assert( is_copy_assignable<_Tp>::value,
                  "type is not assignable" );
   const ptrdiff_t _Num = __last - __first;
   if (_Num)
     __builtin_memmove(__result - _Num, __first, sizeof(_Tp) * _Num);
   return __result - _Num;
 }
    };
  template<bool _IsMove, typename _BI1, typename _BI2>
    inline _BI2
    __copy_move_backward_a(_BI1 __first, _BI1 __last, _BI2 __result)
    {
      typedef typename iterator_traits<_BI1>::value_type _ValueType1;
      typedef typename iterator_traits<_BI2>::value_type _ValueType2;
      typedef typename iterator_traits<_BI1>::iterator_category _Category;
      const bool __simple = (__is_trivial(_ValueType1)
                      && __is_pointer<_BI1>::__value
                      && __is_pointer<_BI2>::__value
        && __are_same<_ValueType1, _ValueType2>::__value);
      return std::__copy_move_backward<_IsMove, __simple,
                                _Category>::__copy_move_b(__first,
         __last,
         __result);
    }
  template<bool _IsMove, typename _BI1, typename _BI2>
    inline _BI2
    __copy_move_backward_a2(_BI1 __first, _BI1 __last, _BI2 __result)
    {
      return _BI2(std::__copy_move_backward_a<_IsMove>
    (std::__niter_base(__first), std::__niter_base(__last),
     std::__niter_base(__result)));
    }
  template<typename _BI1, typename _BI2>
    inline _BI2
    copy_backward(_BI1 __first, _BI1 __last, _BI2 __result)
    {
     
     
     
      ;
      return (std::__copy_move_backward_a2<__is_move_iterator<_BI1>::__value>
       (std::__miter_base(__first), std::__miter_base(__last),
        __result));
    }
  template<typename _BI1, typename _BI2>
    inline _BI2
    move_backward(_BI1 __first, _BI1 __last, _BI2 __result)
    {
     
     
     
      ;
      return std::__copy_move_backward_a2<true>(std::__miter_base(__first),
      std::__miter_base(__last),
      __result);
    }
  template<typename _ForwardIterator, typename _Tp>
    inline typename
    __gnu_cxx::__enable_if<!__is_scalar<_Tp>::__value, void>::__type
    __fill_a(_ForwardIterator __first, _ForwardIterator __last,
       const _Tp& __value)
    {
      for (; __first != __last; ++__first)
 *__first = __value;
    }
  template<typename _ForwardIterator, typename _Tp>
    inline typename
    __gnu_cxx::__enable_if<__is_scalar<_Tp>::__value, void>::__type
    __fill_a(_ForwardIterator __first, _ForwardIterator __last,
      const _Tp& __value)
    {
      const _Tp __tmp = __value;
      for (; __first != __last; ++__first)
 *__first = __tmp;
    }
  template<typename _Tp>
    inline typename
    __gnu_cxx::__enable_if<__is_byte<_Tp>::__value, void>::__type
    __fill_a(_Tp* __first, _Tp* __last, const _Tp& __c)
    {
      const _Tp __tmp = __c;
      __builtin_memset(__first, static_cast<unsigned char>(__tmp),
         __last - __first);
    }
  template<typename _ForwardIterator, typename _Tp>
    inline void
    fill(_ForwardIterator __first, _ForwardIterator __last, const _Tp& __value)
    {
     
      ;
      std::__fill_a(std::__niter_base(__first), std::__niter_base(__last),
      __value);
    }
  template<typename _OutputIterator, typename _Size, typename _Tp>
    inline typename
    __gnu_cxx::__enable_if<!__is_scalar<_Tp>::__value, _OutputIterator>::__type
    __fill_n_a(_OutputIterator __first, _Size __n, const _Tp& __value)
    {
      for (__decltype(__n + 0) __niter = __n;
    __niter > 0; --__niter, ++__first)
 *__first = __value;
      return __first;
    }
  template<typename _OutputIterator, typename _Size, typename _Tp>
    inline typename
    __gnu_cxx::__enable_if<__is_scalar<_Tp>::__value, _OutputIterator>::__type
    __fill_n_a(_OutputIterator __first, _Size __n, const _Tp& __value)
    {
      const _Tp __tmp = __value;
      for (__decltype(__n + 0) __niter = __n;
    __niter > 0; --__niter, ++__first)
 *__first = __tmp;
      return __first;
    }
  template<typename _Size, typename _Tp>
    inline typename
    __gnu_cxx::__enable_if<__is_byte<_Tp>::__value, _Tp*>::__type
    __fill_n_a(_Tp* __first, _Size __n, const _Tp& __c)
    {
      std::__fill_a(__first, __first + __n, __c);
      return __first + __n;
    }
  template<typename _OI, typename _Size, typename _Tp>
    inline _OI
    fill_n(_OI __first, _Size __n, const _Tp& __value)
    {
     
      return _OI(std::__fill_n_a(std::__niter_base(__first), __n, __value));
    }
  template<bool _BoolType>
    struct __equal
    {
      template<typename _II1, typename _II2>
        static bool
        equal(_II1 __first1, _II1 __last1, _II2 __first2)
        {
   for (; __first1 != __last1; ++__first1, ++__first2)
     if (!(*__first1 == *__first2))
       return false;
   return true;
 }
    };
  template<>
    struct __equal<true>
    {
      template<typename _Tp>
        static bool
        equal(const _Tp* __first1, const _Tp* __last1, const _Tp* __first2)
        {
   return !__builtin_memcmp(__first1, __first2, sizeof(_Tp)
       * (__last1 - __first1));
 }
    };
  template<typename _II1, typename _II2>
    inline bool
    __equal_aux(_II1 __first1, _II1 __last1, _II2 __first2)
    {
      typedef typename iterator_traits<_II1>::value_type _ValueType1;
      typedef typename iterator_traits<_II2>::value_type _ValueType2;
      const bool __simple = ((__is_integer<_ValueType1>::__value
         || __is_pointer<_ValueType1>::__value)
                      && __is_pointer<_II1>::__value
                      && __is_pointer<_II2>::__value
        && __are_same<_ValueType1, _ValueType2>::__value);
      return std::__equal<__simple>::equal(__first1, __last1, __first2);
    }
  template<typename, typename>
    struct __lc_rai
    {
      template<typename _II1, typename _II2>
        static _II1
        __newlast1(_II1, _II1 __last1, _II2, _II2)
        { return __last1; }
      template<typename _II>
        static bool
        __cnd2(_II __first, _II __last)
        { return __first != __last; }
    };
  template<>
    struct __lc_rai<random_access_iterator_tag, random_access_iterator_tag>
    {
      template<typename _RAI1, typename _RAI2>
        static _RAI1
        __newlast1(_RAI1 __first1, _RAI1 __last1,
     _RAI2 __first2, _RAI2 __last2)
        {
   const typename iterator_traits<_RAI1>::difference_type
     __diff1 = __last1 - __first1;
   const typename iterator_traits<_RAI2>::difference_type
     __diff2 = __last2 - __first2;
   return __diff2 < __diff1 ? __first1 + __diff2 : __last1;
 }
      template<typename _RAI>
        static bool
        __cnd2(_RAI, _RAI)
        { return true; }
    };
  template<typename _II1, typename _II2, typename _Compare>
    bool
    __lexicographical_compare_impl(_II1 __first1, _II1 __last1,
       _II2 __first2, _II2 __last2,
       _Compare __comp)
    {
      typedef typename iterator_traits<_II1>::iterator_category _Category1;
      typedef typename iterator_traits<_II2>::iterator_category _Category2;
      typedef std::__lc_rai<_Category1, _Category2> __rai_type;
      __last1 = __rai_type::__newlast1(__first1, __last1, __first2, __last2);
      for (; __first1 != __last1 && __rai_type::__cnd2(__first2, __last2);
    ++__first1, ++__first2)
 {
   if (__comp(__first1, __first2))
     return true;
   if (__comp(__first2, __first1))
     return false;
 }
      return __first1 == __last1 && __first2 != __last2;
    }
  template<bool _BoolType>
    struct __lexicographical_compare
    {
      template<typename _II1, typename _II2>
        static bool __lc(_II1, _II1, _II2, _II2);
    };
  template<bool _BoolType>
    template<typename _II1, typename _II2>
      bool
      __lexicographical_compare<_BoolType>::
      __lc(_II1 __first1, _II1 __last1, _II2 __first2, _II2 __last2)
      {
 return std::__lexicographical_compare_impl(__first1, __last1,
         __first2, __last2,
     __gnu_cxx::__ops::__iter_less_iter());
      }
  template<>
    struct __lexicographical_compare<true>
    {
      template<typename _Tp, typename _Up>
        static bool
        __lc(const _Tp* __first1, const _Tp* __last1,
      const _Up* __first2, const _Up* __last2)
 {
   const size_t __len1 = __last1 - __first1;
   const size_t __len2 = __last2 - __first2;
   const int __result = __builtin_memcmp(__first1, __first2,
      std::min(__len1, __len2));
   return __result != 0 ? __result < 0 : __len1 < __len2;
 }
    };
  template<typename _II1, typename _II2>
    inline bool
    __lexicographical_compare_aux(_II1 __first1, _II1 __last1,
      _II2 __first2, _II2 __last2)
    {
      typedef typename iterator_traits<_II1>::value_type _ValueType1;
      typedef typename iterator_traits<_II2>::value_type _ValueType2;
      const bool __simple =
 (__is_byte<_ValueType1>::__value && __is_byte<_ValueType2>::__value
  && !__gnu_cxx::__numeric_traits<_ValueType1>::__is_signed
  && !__gnu_cxx::__numeric_traits<_ValueType2>::__is_signed
  && __is_pointer<_II1>::__value
  && __is_pointer<_II2>::__value);
      return std::__lexicographical_compare<__simple>::__lc(__first1, __last1,
           __first2, __last2);
    }
  template<typename _ForwardIterator, typename _Tp, typename _Compare>
    _ForwardIterator
    __lower_bound(_ForwardIterator __first, _ForwardIterator __last,
    const _Tp& __val, _Compare __comp)
    {
      typedef typename iterator_traits<_ForwardIterator>::difference_type
 _DistanceType;
      _DistanceType __len = std::distance(__first, __last);
      while (__len > 0)
 {
   _DistanceType __half = __len >> 1;
   _ForwardIterator __middle = __first;
   std::advance(__middle, __half);
   if (__comp(__middle, __val))
     {
       __first = __middle;
       ++__first;
       __len = __len - __half - 1;
     }
   else
     __len = __half;
 }
      return __first;
    }
  template<typename _ForwardIterator, typename _Tp>
    inline _ForwardIterator
    lower_bound(_ForwardIterator __first, _ForwardIterator __last,
  const _Tp& __val)
    {
     
     
      ;
      return std::__lower_bound(__first, __last, __val,
    __gnu_cxx::__ops::__iter_less_val());
    }
  inline constexpr int
  __lg(int __n)
  { return sizeof(int) * 8 - 1 - __builtin_clz(__n); }
  inline constexpr unsigned
  __lg(unsigned __n)
  { return sizeof(int) * 8 - 1 - __builtin_clz(__n); }
  inline constexpr long
  __lg(long __n)
  { return sizeof(long) * 8 - 1 - __builtin_clzl(__n); }
  inline constexpr unsigned long
  __lg(unsigned long __n)
  { return sizeof(long) * 8 - 1 - __builtin_clzl(__n); }
  inline constexpr long long
  __lg(long long __n)
  { return sizeof(long long) * 8 - 1 - __builtin_clzll(__n); }
  inline constexpr unsigned long long
  __lg(unsigned long long __n)
  { return sizeof(long long) * 8 - 1 - __builtin_clzll(__n); }


  template<typename _II1, typename _II2>
    inline bool
    equal(_II1 __first1, _II1 __last1, _II2 __first2)
    {
     
     
     
      ;
      return std::__equal_aux(std::__niter_base(__first1),
         std::__niter_base(__last1),
         std::__niter_base(__first2));
    }
  template<typename _IIter1, typename _IIter2, typename _BinaryPredicate>
    inline bool
    equal(_IIter1 __first1, _IIter1 __last1,
   _IIter2 __first2, _BinaryPredicate __binary_pred)
    {
     
     
      ;
      for (; __first1 != __last1; ++__first1, ++__first2)
 if (!bool(__binary_pred(*__first1, *__first2)))
   return false;
      return true;
    }
  template<typename _II1, typename _II2>
    inline bool
    lexicographical_compare(_II1 __first1, _II1 __last1,
       _II2 __first2, _II2 __last2)
    {
     
     
     
     
      ;
      ;
      return std::__lexicographical_compare_aux(std::__niter_base(__first1),
      std::__niter_base(__last1),
      std::__niter_base(__first2),
      std::__niter_base(__last2));
    }
  template<typename _II1, typename _II2, typename _Compare>
    inline bool
    lexicographical_compare(_II1 __first1, _II1 __last1,
       _II2 __first2, _II2 __last2, _Compare __comp)
    {
     
     
      ;
      ;
      return std::__lexicographical_compare_impl
 (__first1, __last1, __first2, __last2,
  __gnu_cxx::__ops::__iter_comp_iter(__comp));
    }
  template<typename _InputIterator1, typename _InputIterator2,
    typename _BinaryPredicate>
    pair<_InputIterator1, _InputIterator2>
    __mismatch(_InputIterator1 __first1, _InputIterator1 __last1,
        _InputIterator2 __first2, _BinaryPredicate __binary_pred)
    {
      while (__first1 != __last1 && __binary_pred(__first1, __first2))
        {
   ++__first1;
   ++__first2;
        }
      return pair<_InputIterator1, _InputIterator2>(__first1, __first2);
    }
  template<typename _InputIterator1, typename _InputIterator2>
    inline pair<_InputIterator1, _InputIterator2>
    mismatch(_InputIterator1 __first1, _InputIterator1 __last1,
      _InputIterator2 __first2)
    {
     
     
     
      ;
      return std::__mismatch(__first1, __last1, __first2,
        __gnu_cxx::__ops::__iter_equal_to_iter());
    }
  template<typename _InputIterator1, typename _InputIterator2,
    typename _BinaryPredicate>
    inline pair<_InputIterator1, _InputIterator2>
    mismatch(_InputIterator1 __first1, _InputIterator1 __last1,
      _InputIterator2 __first2, _BinaryPredicate __binary_pred)
    {
     
     
      ;
      return std::__mismatch(__first1, __last1, __first2,
 __gnu_cxx::__ops::__iter_comp_iter(__binary_pred));
    }

}
       
       
struct _IO_FILE;

typedef struct _IO_FILE FILE;


typedef struct _IO_FILE __FILE;
typedef __builtin_va_list __gnuc_va_list;
typedef unsigned int wint_t;
typedef struct
{
  int __count;
  union
  {
    unsigned int __wch;
    char __wchb[4];
  } __value;
} __mbstate_t;

typedef __mbstate_t mbstate_t;


extern "C" {

struct tm;



extern wchar_t *wcscpy (wchar_t *__restrict __dest,
   const wchar_t *__restrict __src) throw ();
extern wchar_t *wcsncpy (wchar_t *__restrict __dest,
    const wchar_t *__restrict __src, size_t __n)
     throw ();
extern wchar_t *wcscat (wchar_t *__restrict __dest,
   const wchar_t *__restrict __src) throw ();
extern wchar_t *wcsncat (wchar_t *__restrict __dest,
    const wchar_t *__restrict __src, size_t __n)
     throw ();
extern int wcscmp (const wchar_t *__s1, const wchar_t *__s2)
     throw () __attribute__ ((__pure__));
extern int wcsncmp (const wchar_t *__s1, const wchar_t *__s2, size_t __n)
     throw () __attribute__ ((__pure__));

extern int wcscasecmp (const wchar_t *__s1, const wchar_t *__s2) throw ();
extern int wcsncasecmp (const wchar_t *__s1, const wchar_t *__s2,
   size_t __n) throw ();
extern int wcscasecmp_l (const wchar_t *__s1, const wchar_t *__s2,
    __locale_t __loc) throw ();
extern int wcsncasecmp_l (const wchar_t *__s1, const wchar_t *__s2,
     size_t __n, __locale_t __loc) throw ();

extern int wcscoll (const wchar_t *__s1, const wchar_t *__s2) throw ();
extern size_t wcsxfrm (wchar_t *__restrict __s1,
         const wchar_t *__restrict __s2, size_t __n) throw ();

extern int wcscoll_l (const wchar_t *__s1, const wchar_t *__s2,
        __locale_t __loc) throw ();
extern size_t wcsxfrm_l (wchar_t *__s1, const wchar_t *__s2,
    size_t __n, __locale_t __loc) throw ();
extern wchar_t *wcsdup (const wchar_t *__s) throw () __attribute__ ((__malloc__));

extern "C++" wchar_t *wcschr (wchar_t *__wcs, wchar_t __wc)
     throw () __asm ("wcschr") __attribute__ ((__pure__));
extern "C++" const wchar_t *wcschr (const wchar_t *__wcs, wchar_t __wc)
     throw () __asm ("wcschr") __attribute__ ((__pure__));
extern "C++" wchar_t *wcsrchr (wchar_t *__wcs, wchar_t __wc)
     throw () __asm ("wcsrchr") __attribute__ ((__pure__));
extern "C++" const wchar_t *wcsrchr (const wchar_t *__wcs, wchar_t __wc)
     throw () __asm ("wcsrchr") __attribute__ ((__pure__));

extern wchar_t *wcschrnul (const wchar_t *__s, wchar_t __wc)
     throw () __attribute__ ((__pure__));

extern size_t wcscspn (const wchar_t *__wcs, const wchar_t *__reject)
     throw () __attribute__ ((__pure__));
extern size_t wcsspn (const wchar_t *__wcs, const wchar_t *__accept)
     throw () __attribute__ ((__pure__));
extern "C++" wchar_t *wcspbrk (wchar_t *__wcs, const wchar_t *__accept)
     throw () __asm ("wcspbrk") __attribute__ ((__pure__));
extern "C++" const wchar_t *wcspbrk (const wchar_t *__wcs,
         const wchar_t *__accept)
     throw () __asm ("wcspbrk") __attribute__ ((__pure__));
extern "C++" wchar_t *wcsstr (wchar_t *__haystack, const wchar_t *__needle)
     throw () __asm ("wcsstr") __attribute__ ((__pure__));
extern "C++" const wchar_t *wcsstr (const wchar_t *__haystack,
        const wchar_t *__needle)
     throw () __asm ("wcsstr") __attribute__ ((__pure__));
extern wchar_t *wcstok (wchar_t *__restrict __s,
   const wchar_t *__restrict __delim,
   wchar_t **__restrict __ptr) throw ();
extern size_t wcslen (const wchar_t *__s) throw () __attribute__ ((__pure__));

extern "C++" wchar_t *wcswcs (wchar_t *__haystack, const wchar_t *__needle)
     throw () __asm ("wcswcs") __attribute__ ((__pure__));
extern "C++" const wchar_t *wcswcs (const wchar_t *__haystack,
        const wchar_t *__needle)
     throw () __asm ("wcswcs") __attribute__ ((__pure__));
extern size_t wcsnlen (const wchar_t *__s, size_t __maxlen)
     throw () __attribute__ ((__pure__));

extern "C++" wchar_t *wmemchr (wchar_t *__s, wchar_t __c, size_t __n)
     throw () __asm ("wmemchr") __attribute__ ((__pure__));
extern "C++" const wchar_t *wmemchr (const wchar_t *__s, wchar_t __c,
         size_t __n)
     throw () __asm ("wmemchr") __attribute__ ((__pure__));
extern int wmemcmp (const wchar_t *__s1, const wchar_t *__s2, size_t __n)
     throw () __attribute__ ((__pure__));
extern wchar_t *wmemcpy (wchar_t *__restrict __s1,
    const wchar_t *__restrict __s2, size_t __n) throw ();
extern wchar_t *wmemmove (wchar_t *__s1, const wchar_t *__s2, size_t __n)
     throw ();
extern wchar_t *wmemset (wchar_t *__s, wchar_t __c, size_t __n) throw ();

extern wchar_t *wmempcpy (wchar_t *__restrict __s1,
     const wchar_t *__restrict __s2, size_t __n)
     throw ();

extern wint_t btowc (int __c) throw ();
extern int wctob (wint_t __c) throw ();
extern int mbsinit (const mbstate_t *__ps) throw () __attribute__ ((__pure__));
extern size_t mbrtowc (wchar_t *__restrict __pwc,
         const char *__restrict __s, size_t __n,
         mbstate_t *__restrict __p) throw ();
extern size_t wcrtomb (char *__restrict __s, wchar_t __wc,
         mbstate_t *__restrict __ps) throw ();
extern size_t __mbrlen (const char *__restrict __s, size_t __n,
   mbstate_t *__restrict __ps) throw ();
extern size_t mbrlen (const char *__restrict __s, size_t __n,
        mbstate_t *__restrict __ps) throw ();


extern size_t mbsrtowcs (wchar_t *__restrict __dst,
    const char **__restrict __src, size_t __len,
    mbstate_t *__restrict __ps) throw ();
extern size_t wcsrtombs (char *__restrict __dst,
    const wchar_t **__restrict __src, size_t __len,
    mbstate_t *__restrict __ps) throw ();

extern size_t mbsnrtowcs (wchar_t *__restrict __dst,
     const char **__restrict __src, size_t __nmc,
     size_t __len, mbstate_t *__restrict __ps) throw ();
extern size_t wcsnrtombs (char *__restrict __dst,
     const wchar_t **__restrict __src,
     size_t __nwc, size_t __len,
     mbstate_t *__restrict __ps) throw ();
extern int wcwidth (wchar_t __c) throw ();
extern int wcswidth (const wchar_t *__s, size_t __n) throw ();

extern double wcstod (const wchar_t *__restrict __nptr,
        wchar_t **__restrict __endptr) throw ();


extern float wcstof (const wchar_t *__restrict __nptr,
       wchar_t **__restrict __endptr) throw ();
extern long double wcstold (const wchar_t *__restrict __nptr,
       wchar_t **__restrict __endptr) throw ();


extern long int wcstol (const wchar_t *__restrict __nptr,
   wchar_t **__restrict __endptr, int __base) throw ();
extern unsigned long int wcstoul (const wchar_t *__restrict __nptr,
      wchar_t **__restrict __endptr, int __base)
     throw ();


__extension__
extern long long int wcstoll (const wchar_t *__restrict __nptr,
         wchar_t **__restrict __endptr, int __base)
     throw ();
__extension__
extern unsigned long long int wcstoull (const wchar_t *__restrict __nptr,
     wchar_t **__restrict __endptr,
     int __base) throw ();

__extension__
extern long long int wcstoq (const wchar_t *__restrict __nptr,
        wchar_t **__restrict __endptr, int __base)
     throw ();
__extension__
extern unsigned long long int wcstouq (const wchar_t *__restrict __nptr,
           wchar_t **__restrict __endptr,
           int __base) throw ();
extern long int wcstol_l (const wchar_t *__restrict __nptr,
     wchar_t **__restrict __endptr, int __base,
     __locale_t __loc) throw ();
extern unsigned long int wcstoul_l (const wchar_t *__restrict __nptr,
        wchar_t **__restrict __endptr,
        int __base, __locale_t __loc) throw ();
__extension__
extern long long int wcstoll_l (const wchar_t *__restrict __nptr,
    wchar_t **__restrict __endptr,
    int __base, __locale_t __loc) throw ();
__extension__
extern unsigned long long int wcstoull_l (const wchar_t *__restrict __nptr,
       wchar_t **__restrict __endptr,
       int __base, __locale_t __loc)
     throw ();
extern double wcstod_l (const wchar_t *__restrict __nptr,
   wchar_t **__restrict __endptr, __locale_t __loc)
     throw ();
extern float wcstof_l (const wchar_t *__restrict __nptr,
         wchar_t **__restrict __endptr, __locale_t __loc)
     throw ();
extern long double wcstold_l (const wchar_t *__restrict __nptr,
         wchar_t **__restrict __endptr,
         __locale_t __loc) throw ();
extern wchar_t *wcpcpy (wchar_t *__restrict __dest,
   const wchar_t *__restrict __src) throw ();
extern wchar_t *wcpncpy (wchar_t *__restrict __dest,
    const wchar_t *__restrict __src, size_t __n)
     throw ();
extern __FILE *open_wmemstream (wchar_t **__bufloc, size_t *__sizeloc) throw ();

extern int fwide (__FILE *__fp, int __mode) throw ();
extern int fwprintf (__FILE *__restrict __stream,
       const wchar_t *__restrict __format, ...)
                                                           ;
extern int wprintf (const wchar_t *__restrict __format, ...)
                                                           ;
extern int swprintf (wchar_t *__restrict __s, size_t __n,
       const wchar_t *__restrict __format, ...)
     throw () ;
extern int vfwprintf (__FILE *__restrict __s,
        const wchar_t *__restrict __format,
        __gnuc_va_list __arg)
                                                           ;
extern int vwprintf (const wchar_t *__restrict __format,
       __gnuc_va_list __arg)
                                                           ;
extern int vswprintf (wchar_t *__restrict __s, size_t __n,
        const wchar_t *__restrict __format,
        __gnuc_va_list __arg)
     throw () ;
extern int fwscanf (__FILE *__restrict __stream,
      const wchar_t *__restrict __format, ...)
                                                          ;
extern int wscanf (const wchar_t *__restrict __format, ...)
                                                          ;
extern int swscanf (const wchar_t *__restrict __s,
      const wchar_t *__restrict __format, ...)
     throw () ;


extern int vfwscanf (__FILE *__restrict __s,
       const wchar_t *__restrict __format,
       __gnuc_va_list __arg)
                                                          ;
extern int vwscanf (const wchar_t *__restrict __format,
      __gnuc_va_list __arg)
                                                          ;
extern int vswscanf (const wchar_t *__restrict __s,
       const wchar_t *__restrict __format,
       __gnuc_va_list __arg)
     throw () ;


extern wint_t fgetwc (__FILE *__stream);
extern wint_t getwc (__FILE *__stream);
extern wint_t getwchar (void);
extern wint_t fputwc (wchar_t __wc, __FILE *__stream);
extern wint_t putwc (wchar_t __wc, __FILE *__stream);
extern wint_t putwchar (wchar_t __wc);
extern wchar_t *fgetws (wchar_t *__restrict __ws, int __n,
   __FILE *__restrict __stream);
extern int fputws (const wchar_t *__restrict __ws,
     __FILE *__restrict __stream);
extern wint_t ungetwc (wint_t __wc, __FILE *__stream);

extern wint_t getwc_unlocked (__FILE *__stream);
extern wint_t getwchar_unlocked (void);
extern wint_t fgetwc_unlocked (__FILE *__stream);
extern wint_t fputwc_unlocked (wchar_t __wc, __FILE *__stream);
extern wint_t putwc_unlocked (wchar_t __wc, __FILE *__stream);
extern wint_t putwchar_unlocked (wchar_t __wc);
extern wchar_t *fgetws_unlocked (wchar_t *__restrict __ws, int __n,
     __FILE *__restrict __stream);
extern int fputws_unlocked (const wchar_t *__restrict __ws,
       __FILE *__restrict __stream);

extern size_t wcsftime (wchar_t *__restrict __s, size_t __maxsize,
   const wchar_t *__restrict __format,
   const struct tm *__restrict __tp) throw ();

extern size_t wcsftime_l (wchar_t *__restrict __s, size_t __maxsize,
     const wchar_t *__restrict __format,
     const struct tm *__restrict __tp,
     __locale_t __loc) throw ();
}
namespace std
{
  using ::mbstate_t;
}
namespace std __attribute__ ((__visibility__ ("default")))
{

  using ::wint_t;
  using ::btowc;
  using ::fgetwc;
  using ::fgetws;
  using ::fputwc;
  using ::fputws;
  using ::fwide;
  using ::fwprintf;
  using ::fwscanf;
  using ::getwc;
  using ::getwchar;
  using ::mbrlen;
  using ::mbrtowc;
  using ::mbsinit;
  using ::mbsrtowcs;
  using ::putwc;
  using ::putwchar;
  using ::swprintf;
  using ::swscanf;
  using ::ungetwc;
  using ::vfwprintf;
  using ::vfwscanf;
  using ::vswprintf;
  using ::vswscanf;
  using ::vwprintf;
  using ::vwscanf;
  using ::wcrtomb;
  using ::wcscat;
  using ::wcscmp;
  using ::wcscoll;
  using ::wcscpy;
  using ::wcscspn;
  using ::wcsftime;
  using ::wcslen;
  using ::wcsncat;
  using ::wcsncmp;
  using ::wcsncpy;
  using ::wcsrtombs;
  using ::wcsspn;
  using ::wcstod;
  using ::wcstof;
  using ::wcstok;
  using ::wcstol;
  using ::wcstoul;
  using ::wcsxfrm;
  using ::wctob;
  using ::wmemcmp;
  using ::wmemcpy;
  using ::wmemmove;
  using ::wmemset;
  using ::wprintf;
  using ::wscanf;
  using ::wcschr;
  using ::wcspbrk;
  using ::wcsrchr;
  using ::wcsstr;
  using ::wmemchr;

}
namespace __gnu_cxx
{
  using ::wcstold;
  using ::wcstoll;
  using ::wcstoull;
}
namespace std
{
  using ::__gnu_cxx::wcstold;
  using ::__gnu_cxx::wcstoll;
  using ::__gnu_cxx::wcstoull;
}
namespace std
{
  using std::wcstof;
  using std::vfwscanf;
  using std::vswscanf;
  using std::vwscanf;
  using std::wcstold;
  using std::wcstoll;
  using std::wcstoull;
}
namespace std __attribute__ ((__visibility__ ("default")))
{

  typedef long streamoff;
  typedef ptrdiff_t streamsize;
  template<typename _StateT>
    class fpos
    {
    private:
      streamoff _M_off;
      _StateT _M_state;
    public:
      fpos()
      : _M_off(0), _M_state() { }
      fpos(streamoff __off)
      : _M_off(__off), _M_state() { }
      operator streamoff() const { return _M_off; }
      void
      state(_StateT __st)
      { _M_state = __st; }
      _StateT
      state() const
      { return _M_state; }
      fpos&
      operator+=(streamoff __off)
      {
 _M_off += __off;
 return *this;
      }
      fpos&
      operator-=(streamoff __off)
      {
 _M_off -= __off;
 return *this;
      }
      fpos
      operator+(streamoff __off) const
      {
 fpos __pos(*this);
 __pos += __off;
 return __pos;
      }
      fpos
      operator-(streamoff __off) const
      {
 fpos __pos(*this);
 __pos -= __off;
 return __pos;
      }
      streamoff
      operator-(const fpos& __other) const
      { return _M_off - __other._M_off; }
    };
  template<typename _StateT>
    inline bool
    operator==(const fpos<_StateT>& __lhs, const fpos<_StateT>& __rhs)
    { return streamoff(__lhs) == streamoff(__rhs); }
  template<typename _StateT>
    inline bool
    operator!=(const fpos<_StateT>& __lhs, const fpos<_StateT>& __rhs)
    { return streamoff(__lhs) != streamoff(__rhs); }
  typedef fpos<mbstate_t> streampos;
  typedef fpos<mbstate_t> wstreampos;
  typedef fpos<mbstate_t> u16streampos;
  typedef fpos<mbstate_t> u32streampos;

}
       
namespace __gnu_cxx __attribute__ ((__visibility__ ("default")))
{

  template<typename _CharT>
    struct _Char_types
    {
      typedef unsigned long int_type;
      typedef std::streampos pos_type;
      typedef std::streamoff off_type;
      typedef std::mbstate_t state_type;
    };
  template<typename _CharT>
    struct char_traits
    {
      typedef _CharT char_type;
      typedef typename _Char_types<_CharT>::int_type int_type;
      typedef typename _Char_types<_CharT>::pos_type pos_type;
      typedef typename _Char_types<_CharT>::off_type off_type;
      typedef typename _Char_types<_CharT>::state_type state_type;
      static void
      assign(char_type& __c1, const char_type& __c2)
      { __c1 = __c2; }
      static constexpr bool
      eq(const char_type& __c1, const char_type& __c2)
      { return __c1 == __c2; }
      static constexpr bool
      lt(const char_type& __c1, const char_type& __c2)
      { return __c1 < __c2; }
      static int
      compare(const char_type* __s1, const char_type* __s2, std::size_t __n);
      static std::size_t
      length(const char_type* __s);
      static const char_type*
      find(const char_type* __s, std::size_t __n, const char_type& __a);
      static char_type*
      move(char_type* __s1, const char_type* __s2, std::size_t __n);
      static char_type*
      copy(char_type* __s1, const char_type* __s2, std::size_t __n);
      static char_type*
      assign(char_type* __s, std::size_t __n, char_type __a);
      static constexpr char_type
      to_char_type(const int_type& __c)
      { return static_cast<char_type>(__c); }
      static constexpr int_type
      to_int_type(const char_type& __c)
      { return static_cast<int_type>(__c); }
      static constexpr bool
      eq_int_type(const int_type& __c1, const int_type& __c2)
      { return __c1 == __c2; }
      static constexpr int_type
      eof()
      { return static_cast<int_type>(-1); }
      static constexpr int_type
      not_eof(const int_type& __c)
      { return !eq_int_type(__c, eof()) ? __c : to_int_type(char_type()); }
    };
  template<typename _CharT>
    int
    char_traits<_CharT>::
    compare(const char_type* __s1, const char_type* __s2, std::size_t __n)
    {
      for (std::size_t __i = 0; __i < __n; ++__i)
 if (lt(__s1[__i], __s2[__i]))
   return -1;
 else if (lt(__s2[__i], __s1[__i]))
   return 1;
      return 0;
    }
  template<typename _CharT>
    std::size_t
    char_traits<_CharT>::
    length(const char_type* __p)
    {
      std::size_t __i = 0;
      while (!eq(__p[__i], char_type()))
        ++__i;
      return __i;
    }
  template<typename _CharT>
    const typename char_traits<_CharT>::char_type*
    char_traits<_CharT>::
    find(const char_type* __s, std::size_t __n, const char_type& __a)
    {
      for (std::size_t __i = 0; __i < __n; ++__i)
        if (eq(__s[__i], __a))
          return __s + __i;
      return 0;
    }
  template<typename _CharT>
    typename char_traits<_CharT>::char_type*
    char_traits<_CharT>::
    move(char_type* __s1, const char_type* __s2, std::size_t __n)
    {
      return static_cast<_CharT*>(__builtin_memmove(__s1, __s2,
          __n * sizeof(char_type)));
    }
  template<typename _CharT>
    typename char_traits<_CharT>::char_type*
    char_traits<_CharT>::
    copy(char_type* __s1, const char_type* __s2, std::size_t __n)
    {
      std::copy(__s2, __s2 + __n, __s1);
      return __s1;
    }
  template<typename _CharT>
    typename char_traits<_CharT>::char_type*
    char_traits<_CharT>::
    assign(char_type* __s, std::size_t __n, char_type __a)
    {
      std::fill_n(__s, __n, __a);
      return __s;
    }

}
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<class _CharT>
    struct char_traits : public __gnu_cxx::char_traits<_CharT>
    { };
  template<>
    struct char_traits<char>
    {
      typedef char char_type;
      typedef int int_type;
      typedef streampos pos_type;
      typedef streamoff off_type;
      typedef mbstate_t state_type;
      static void
      assign(char_type& __c1, const char_type& __c2) noexcept
      { __c1 = __c2; }
      static constexpr bool
      eq(const char_type& __c1, const char_type& __c2) noexcept
      { return __c1 == __c2; }
      static constexpr bool
      lt(const char_type& __c1, const char_type& __c2) noexcept
      {
 return (static_cast<unsigned char>(__c1)
  < static_cast<unsigned char>(__c2));
      }
      static int
      compare(const char_type* __s1, const char_type* __s2, size_t __n)
      { return __builtin_memcmp(__s1, __s2, __n); }
      static size_t
      length(const char_type* __s)
      { return __builtin_strlen(__s); }
      static const char_type*
      find(const char_type* __s, size_t __n, const char_type& __a)
      { return static_cast<const char_type*>(__builtin_memchr(__s, __a, __n)); }
      static char_type*
      move(char_type* __s1, const char_type* __s2, size_t __n)
      { return static_cast<char_type*>(__builtin_memmove(__s1, __s2, __n)); }
      static char_type*
      copy(char_type* __s1, const char_type* __s2, size_t __n)
      { return static_cast<char_type*>(__builtin_memcpy(__s1, __s2, __n)); }
      static char_type*
      assign(char_type* __s, size_t __n, char_type __a)
      { return static_cast<char_type*>(__builtin_memset(__s, __a, __n)); }
      static constexpr char_type
      to_char_type(const int_type& __c) noexcept
      { return static_cast<char_type>(__c); }
      static constexpr int_type
      to_int_type(const char_type& __c) noexcept
      { return static_cast<int_type>(static_cast<unsigned char>(__c)); }
      static constexpr bool
      eq_int_type(const int_type& __c1, const int_type& __c2) noexcept
      { return __c1 == __c2; }
      static constexpr int_type
      eof() noexcept
      { return static_cast<int_type>(-1); }
      static constexpr int_type
      not_eof(const int_type& __c) noexcept
      { return (__c == eof()) ? 0 : __c; }
  };
  template<>
    struct char_traits<wchar_t>
    {
      typedef wchar_t char_type;
      typedef wint_t int_type;
      typedef streamoff off_type;
      typedef wstreampos pos_type;
      typedef mbstate_t state_type;
      static void
      assign(char_type& __c1, const char_type& __c2) noexcept
      { __c1 = __c2; }
      static constexpr bool
      eq(const char_type& __c1, const char_type& __c2) noexcept
      { return __c1 == __c2; }
      static constexpr bool
      lt(const char_type& __c1, const char_type& __c2) noexcept
      { return __c1 < __c2; }
      static int
      compare(const char_type* __s1, const char_type* __s2, size_t __n)
      { return wmemcmp(__s1, __s2, __n); }
      static size_t
      length(const char_type* __s)
      { return wcslen(__s); }
      static const char_type*
      find(const char_type* __s, size_t __n, const char_type& __a)
      { return wmemchr(__s, __a, __n); }
      static char_type*
      move(char_type* __s1, const char_type* __s2, size_t __n)
      { return wmemmove(__s1, __s2, __n); }
      static char_type*
      copy(char_type* __s1, const char_type* __s2, size_t __n)
      { return wmemcpy(__s1, __s2, __n); }
      static char_type*
      assign(char_type* __s, size_t __n, char_type __a)
      { return wmemset(__s, __a, __n); }
      static constexpr char_type
      to_char_type(const int_type& __c) noexcept
      { return char_type(__c); }
      static constexpr int_type
      to_int_type(const char_type& __c) noexcept
      { return int_type(__c); }
      static constexpr bool
      eq_int_type(const int_type& __c1, const int_type& __c2) noexcept
      { return __c1 == __c2; }
      static constexpr int_type
      eof() noexcept
      { return static_cast<int_type>((0xffffffffu)); }
      static constexpr int_type
      not_eof(const int_type& __c) noexcept
      { return eq_int_type(__c, eof()) ? 0 : __c; }
  };

}
       
namespace std
{
  using ::int8_t;
  using ::int16_t;
  using ::int32_t;
  using ::int64_t;
  using ::int_fast8_t;
  using ::int_fast16_t;
  using ::int_fast32_t;
  using ::int_fast64_t;
  using ::int_least8_t;
  using ::int_least16_t;
  using ::int_least32_t;
  using ::int_least64_t;
  using ::intmax_t;
  using ::intptr_t;
  using ::uint8_t;
  using ::uint16_t;
  using ::uint32_t;
  using ::uint64_t;
  using ::uint_fast8_t;
  using ::uint_fast16_t;
  using ::uint_fast32_t;
  using ::uint_fast64_t;
  using ::uint_least8_t;
  using ::uint_least16_t;
  using ::uint_least32_t;
  using ::uint_least64_t;
  using ::uintmax_t;
  using ::uintptr_t;
}
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<>
    struct char_traits<char16_t>
    {
      typedef char16_t char_type;
      typedef uint_least16_t int_type;
      typedef streamoff off_type;
      typedef u16streampos pos_type;
      typedef mbstate_t state_type;
      static void
      assign(char_type& __c1, const char_type& __c2) noexcept
      { __c1 = __c2; }
      static constexpr bool
      eq(const char_type& __c1, const char_type& __c2) noexcept
      { return __c1 == __c2; }
      static constexpr bool
      lt(const char_type& __c1, const char_type& __c2) noexcept
      { return __c1 < __c2; }
      static int
      compare(const char_type* __s1, const char_type* __s2, size_t __n)
      {
 for (size_t __i = 0; __i < __n; ++__i)
   if (lt(__s1[__i], __s2[__i]))
     return -1;
   else if (lt(__s2[__i], __s1[__i]))
     return 1;
 return 0;
      }
      static size_t
      length(const char_type* __s)
      {
 size_t __i = 0;
 while (!eq(__s[__i], char_type()))
   ++__i;
 return __i;
      }
      static const char_type*
      find(const char_type* __s, size_t __n, const char_type& __a)
      {
 for (size_t __i = 0; __i < __n; ++__i)
   if (eq(__s[__i], __a))
     return __s + __i;
 return 0;
      }
      static char_type*
      move(char_type* __s1, const char_type* __s2, size_t __n)
      {
 return (static_cast<char_type*>
  (__builtin_memmove(__s1, __s2, __n * sizeof(char_type))));
      }
      static char_type*
      copy(char_type* __s1, const char_type* __s2, size_t __n)
      {
 return (static_cast<char_type*>
  (__builtin_memcpy(__s1, __s2, __n * sizeof(char_type))));
      }
      static char_type*
      assign(char_type* __s, size_t __n, char_type __a)
      {
 for (size_t __i = 0; __i < __n; ++__i)
   assign(__s[__i], __a);
 return __s;
      }
      static constexpr char_type
      to_char_type(const int_type& __c) noexcept
      { return char_type(__c); }
      static constexpr int_type
      to_int_type(const char_type& __c) noexcept
      { return int_type(__c); }
      static constexpr bool
      eq_int_type(const int_type& __c1, const int_type& __c2) noexcept
      { return __c1 == __c2; }
      static constexpr int_type
      eof() noexcept
      { return static_cast<int_type>(-1); }
      static constexpr int_type
      not_eof(const int_type& __c) noexcept
      { return eq_int_type(__c, eof()) ? 0 : __c; }
    };
  template<>
    struct char_traits<char32_t>
    {
      typedef char32_t char_type;
      typedef uint_least32_t int_type;
      typedef streamoff off_type;
      typedef u32streampos pos_type;
      typedef mbstate_t state_type;
      static void
      assign(char_type& __c1, const char_type& __c2) noexcept
      { __c1 = __c2; }
      static constexpr bool
      eq(const char_type& __c1, const char_type& __c2) noexcept
      { return __c1 == __c2; }
      static constexpr bool
      lt(const char_type& __c1, const char_type& __c2) noexcept
      { return __c1 < __c2; }
      static int
      compare(const char_type* __s1, const char_type* __s2, size_t __n)
      {
 for (size_t __i = 0; __i < __n; ++__i)
   if (lt(__s1[__i], __s2[__i]))
     return -1;
   else if (lt(__s2[__i], __s1[__i]))
     return 1;
 return 0;
      }
      static size_t
      length(const char_type* __s)
      {
 size_t __i = 0;
 while (!eq(__s[__i], char_type()))
   ++__i;
 return __i;
      }
      static const char_type*
      find(const char_type* __s, size_t __n, const char_type& __a)
      {
 for (size_t __i = 0; __i < __n; ++__i)
   if (eq(__s[__i], __a))
     return __s + __i;
 return 0;
      }
      static char_type*
      move(char_type* __s1, const char_type* __s2, size_t __n)
      {
 return (static_cast<char_type*>
  (__builtin_memmove(__s1, __s2, __n * sizeof(char_type))));
      }
      static char_type*
      copy(char_type* __s1, const char_type* __s2, size_t __n)
      {
 return (static_cast<char_type*>
  (__builtin_memcpy(__s1, __s2, __n * sizeof(char_type))));
      }
      static char_type*
      assign(char_type* __s, size_t __n, char_type __a)
      {
 for (size_t __i = 0; __i < __n; ++__i)
   assign(__s[__i], __a);
 return __s;
      }
      static constexpr char_type
      to_char_type(const int_type& __c) noexcept
      { return char_type(__c); }
      static constexpr int_type
      to_int_type(const char_type& __c) noexcept
      { return int_type(__c); }
      static constexpr bool
      eq_int_type(const int_type& __c1, const int_type& __c2) noexcept
      { return __c1 == __c2; }
      static constexpr int_type
      eof() noexcept
      { return static_cast<int_type>(-1); }
      static constexpr int_type
      not_eof(const int_type& __c) noexcept
      { return eq_int_type(__c, eof()) ? 0 : __c; }
    };

}
namespace __gnu_cxx __attribute__ ((__visibility__ ("default")))
{

  using std::size_t;
  using std::ptrdiff_t;
  template<typename _Tp>
    class new_allocator
    {
    public:
      typedef size_t size_type;
      typedef ptrdiff_t difference_type;
      typedef _Tp* pointer;
      typedef const _Tp* const_pointer;
      typedef _Tp& reference;
      typedef const _Tp& const_reference;
      typedef _Tp value_type;
      template<typename _Tp1>
        struct rebind
        { typedef new_allocator<_Tp1> other; };
      typedef std::true_type propagate_on_container_move_assignment;
      new_allocator() noexcept { }
      new_allocator(const new_allocator&) noexcept { }
      template<typename _Tp1>
        new_allocator(const new_allocator<_Tp1>&) noexcept { }
      ~new_allocator() noexcept { }
      pointer
      address(reference __x) const noexcept
      { return std::__addressof(__x); }
      const_pointer
      address(const_reference __x) const noexcept
      { return std::__addressof(__x); }
      pointer
      allocate(size_type __n, const void* = 0)
      {
 if (__n > this->max_size())
   std::__throw_bad_alloc();
 return static_cast<_Tp*>(::operator new(__n * sizeof(_Tp)));
      }
      void
      deallocate(pointer __p, size_type)
      { ::operator delete(__p); }
      size_type
      max_size() const noexcept
      { return size_t(-1) / sizeof(_Tp); }
      template<typename _Up, typename... _Args>
        void
        construct(_Up* __p, _Args&&... __args)
 { ::new((void *)__p) _Up(std::forward<_Args>(__args)...); }
      template<typename _Up>
        void
        destroy(_Up* __p) { __p->~_Up(); }
    };
  template<typename _Tp>
    inline bool
    operator==(const new_allocator<_Tp>&, const new_allocator<_Tp>&)
    { return true; }
  template<typename _Tp>
    inline bool
    operator!=(const new_allocator<_Tp>&, const new_allocator<_Tp>&)
    { return false; }

}
namespace std
{
  template<typename _Tp>
    using __allocator_base = __gnu_cxx::new_allocator<_Tp>;
}
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<>
    class allocator<void>
    {
    public:
      typedef size_t size_type;
      typedef ptrdiff_t difference_type;
      typedef void* pointer;
      typedef const void* const_pointer;
      typedef void value_type;
      template<typename _Tp1>
        struct rebind
        { typedef allocator<_Tp1> other; };
      typedef true_type propagate_on_container_move_assignment;
    };
  template<typename _Tp>
    class allocator: public __allocator_base<_Tp>
    {
   public:
      typedef size_t size_type;
      typedef ptrdiff_t difference_type;
      typedef _Tp* pointer;
      typedef const _Tp* const_pointer;
      typedef _Tp& reference;
      typedef const _Tp& const_reference;
      typedef _Tp value_type;
      template<typename _Tp1>
        struct rebind
        { typedef allocator<_Tp1> other; };
      typedef true_type propagate_on_container_move_assignment;
      allocator() throw() { }
      allocator(const allocator& __a) throw()
      : __allocator_base<_Tp>(__a) { }
      template<typename _Tp1>
        allocator(const allocator<_Tp1>&) throw() { }
      ~allocator() throw() { }
    };
  template<typename _T1, typename _T2>
    inline bool
    operator==(const allocator<_T1>&, const allocator<_T2>&)
    { return true; }
  template<typename _Tp>
    inline bool
    operator==(const allocator<_Tp>&, const allocator<_Tp>&)
    { return true; }
  template<typename _T1, typename _T2>
    inline bool
    operator!=(const allocator<_T1>&, const allocator<_T2>&)
    { return false; }
  template<typename _Tp>
    inline bool
    operator!=(const allocator<_Tp>&, const allocator<_Tp>&)
    { return false; }
  extern template class allocator<char>;
  extern template class allocator<wchar_t>;
  template<typename _Alloc, bool = __is_empty(_Alloc)>
    struct __alloc_swap
    { static void _S_do_it(_Alloc&, _Alloc&) noexcept { } };
  template<typename _Alloc>
    struct __alloc_swap<_Alloc, false>
    {
      static void
      _S_do_it(_Alloc& __one, _Alloc& __two) noexcept
      {
 if (__one != __two)
   swap(__one, __two);
      }
    };
  template<typename _Alloc, bool = __is_empty(_Alloc)>
    struct __alloc_neq
    {
      static bool
      _S_do_it(const _Alloc&, const _Alloc&)
      { return false; }
    };
  template<typename _Alloc>
    struct __alloc_neq<_Alloc, false>
    {
      static bool
      _S_do_it(const _Alloc& __one, const _Alloc& __two)
      { return __one != __two; }
    };
  template<typename _Tp, bool
    = __or_<is_copy_constructible<typename _Tp::value_type>,
            is_nothrow_move_constructible<typename _Tp::value_type>>::value>
    struct __shrink_to_fit_aux
    { static bool _S_do_it(_Tp&) noexcept { return false; } };
  template<typename _Tp>
    struct __shrink_to_fit_aux<_Tp, true>
    {
      static bool
      _S_do_it(_Tp& __c) noexcept
      {
 try
   {
     _Tp(__make_move_if_noexcept_iterator(__c.begin()),
  __make_move_if_noexcept_iterator(__c.end()),
  __c.get_allocator()).swap(__c);
     return true;
   }
 catch(...)
   { return false; }
      }
    };

}
       
       
       
extern "C" {

struct lconv
{
  char *decimal_point;
  char *thousands_sep;
  char *grouping;
  char *int_curr_symbol;
  char *currency_symbol;
  char *mon_decimal_point;
  char *mon_thousands_sep;
  char *mon_grouping;
  char *positive_sign;
  char *negative_sign;
  char int_frac_digits;
  char frac_digits;
  char p_cs_precedes;
  char p_sep_by_space;
  char n_cs_precedes;
  char n_sep_by_space;
  char p_sign_posn;
  char n_sign_posn;
  char int_p_cs_precedes;
  char int_p_sep_by_space;
  char int_n_cs_precedes;
  char int_n_sep_by_space;
  char int_p_sign_posn;
  char int_n_sign_posn;
};
extern char *setlocale (int __category, const char *__locale) throw ();
extern struct lconv *localeconv (void) throw ();

extern __locale_t newlocale (int __category_mask, const char *__locale,
        __locale_t __base) throw ();
extern __locale_t duplocale (__locale_t __dataset) throw ();
extern void freelocale (__locale_t __dataset) throw ();
extern __locale_t uselocale (__locale_t __dataset) throw ();
}
namespace std
{
  using ::lconv;
  using ::setlocale;
  using ::localeconv;
}
namespace __gnu_cxx __attribute__ ((__visibility__ ("default")))
{

  extern "C" __typeof(uselocale) __uselocale;

}
namespace std __attribute__ ((__visibility__ ("default")))
{

  typedef __locale_t __c_locale;
  inline int
  __convert_from_v(const __c_locale& __cloc __attribute__ ((__unused__)),
     char* __out,
     const int __size __attribute__ ((__unused__)),
     const char* __fmt, ...)
  {
    __c_locale __old = __gnu_cxx::__uselocale(__cloc);
    __builtin_va_list __args;
    __builtin_va_start(__args, __fmt);
    const int __ret = __builtin_vsnprintf(__out, __size, __fmt, __args);
    __builtin_va_end(__args);
    __gnu_cxx::__uselocale(__old);
    return __ret;
  }

}
       
namespace std __attribute__ ((__visibility__ ("default")))
{

  class ios_base;
  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_ios;
  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_streambuf;
  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_istream;
  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_ostream;
  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_iostream;
  template<typename _CharT, typename _Traits = char_traits<_CharT>,
     typename _Alloc = allocator<_CharT> >
    class basic_stringbuf;
  template<typename _CharT, typename _Traits = char_traits<_CharT>,
    typename _Alloc = allocator<_CharT> >
    class basic_istringstream;
  template<typename _CharT, typename _Traits = char_traits<_CharT>,
    typename _Alloc = allocator<_CharT> >
    class basic_ostringstream;
  template<typename _CharT, typename _Traits = char_traits<_CharT>,
    typename _Alloc = allocator<_CharT> >
    class basic_stringstream;
  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_filebuf;
  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_ifstream;
  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_ofstream;
  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class basic_fstream;
  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class istreambuf_iterator;
  template<typename _CharT, typename _Traits = char_traits<_CharT> >
    class ostreambuf_iterator;
  typedef basic_ios<char> ios;
  typedef basic_streambuf<char> streambuf;
  typedef basic_istream<char> istream;
  typedef basic_ostream<char> ostream;
  typedef basic_iostream<char> iostream;
  typedef basic_stringbuf<char> stringbuf;
  typedef basic_istringstream<char> istringstream;
  typedef basic_ostringstream<char> ostringstream;
  typedef basic_stringstream<char> stringstream;
  typedef basic_filebuf<char> filebuf;
  typedef basic_ifstream<char> ifstream;
  typedef basic_ofstream<char> ofstream;
  typedef basic_fstream<char> fstream;
  typedef basic_ios<wchar_t> wios;
  typedef basic_streambuf<wchar_t> wstreambuf;
  typedef basic_istream<wchar_t> wistream;
  typedef basic_ostream<wchar_t> wostream;
  typedef basic_iostream<wchar_t> wiostream;
  typedef basic_stringbuf<wchar_t> wstringbuf;
  typedef basic_istringstream<wchar_t> wistringstream;
  typedef basic_ostringstream<wchar_t> wostringstream;
  typedef basic_stringstream<wchar_t> wstringstream;
  typedef basic_filebuf<wchar_t> wfilebuf;
  typedef basic_ifstream<wchar_t> wifstream;
  typedef basic_ofstream<wchar_t> wofstream;
  typedef basic_fstream<wchar_t> wfstream;

}
       
extern "C" {
enum
{
  _ISupper = ((0) < 8 ? ((1 << (0)) << 8) : ((1 << (0)) >> 8)),
  _ISlower = ((1) < 8 ? ((1 << (1)) << 8) : ((1 << (1)) >> 8)),
  _ISalpha = ((2) < 8 ? ((1 << (2)) << 8) : ((1 << (2)) >> 8)),
  _ISdigit = ((3) < 8 ? ((1 << (3)) << 8) : ((1 << (3)) >> 8)),
  _ISxdigit = ((4) < 8 ? ((1 << (4)) << 8) : ((1 << (4)) >> 8)),
  _ISspace = ((5) < 8 ? ((1 << (5)) << 8) : ((1 << (5)) >> 8)),
  _ISprint = ((6) < 8 ? ((1 << (6)) << 8) : ((1 << (6)) >> 8)),
  _ISgraph = ((7) < 8 ? ((1 << (7)) << 8) : ((1 << (7)) >> 8)),
  _ISblank = ((8) < 8 ? ((1 << (8)) << 8) : ((1 << (8)) >> 8)),
  _IScntrl = ((9) < 8 ? ((1 << (9)) << 8) : ((1 << (9)) >> 8)),
  _ISpunct = ((10) < 8 ? ((1 << (10)) << 8) : ((1 << (10)) >> 8)),
  _ISalnum = ((11) < 8 ? ((1 << (11)) << 8) : ((1 << (11)) >> 8))
};
extern const unsigned short int **__ctype_b_loc (void)
     throw () __attribute__ ((__const__));
extern const __int32_t **__ctype_tolower_loc (void)
     throw () __attribute__ ((__const__));
extern const __int32_t **__ctype_toupper_loc (void)
     throw () __attribute__ ((__const__));

extern int isalnum (int) throw ();
extern int isalpha (int) throw ();
extern int iscntrl (int) throw ();
extern int isdigit (int) throw ();
extern int islower (int) throw ();
extern int isgraph (int) throw ();
extern int isprint (int) throw ();
extern int ispunct (int) throw ();
extern int isspace (int) throw ();
extern int isupper (int) throw ();
extern int isxdigit (int) throw ();
extern int tolower (int __c) throw ();
extern int toupper (int __c) throw ();


extern int isblank (int) throw ();

extern int isctype (int __c, int __mask) throw ();
extern int isascii (int __c) throw ();
extern int toascii (int __c) throw ();
extern int _toupper (int) throw ();
extern int _tolower (int) throw ();
extern int isalnum_l (int, __locale_t) throw ();
extern int isalpha_l (int, __locale_t) throw ();
extern int iscntrl_l (int, __locale_t) throw ();
extern int isdigit_l (int, __locale_t) throw ();
extern int islower_l (int, __locale_t) throw ();
extern int isgraph_l (int, __locale_t) throw ();
extern int isprint_l (int, __locale_t) throw ();
extern int ispunct_l (int, __locale_t) throw ();
extern int isspace_l (int, __locale_t) throw ();
extern int isupper_l (int, __locale_t) throw ();
extern int isxdigit_l (int, __locale_t) throw ();
extern int isblank_l (int, __locale_t) throw ();
extern int __tolower_l (int __c, __locale_t __l) throw ();
extern int tolower_l (int __c, __locale_t __l) throw ();
extern int __toupper_l (int __c, __locale_t __l) throw ();
extern int toupper_l (int __c, __locale_t __l) throw ();
}
namespace std
{
  using ::isalnum;
  using ::isalpha;
  using ::iscntrl;
  using ::isdigit;
  using ::isgraph;
  using ::islower;
  using ::isprint;
  using ::ispunct;
  using ::isspace;
  using ::isupper;
  using ::isxdigit;
  using ::tolower;
  using ::toupper;
}
namespace std
{
  using ::isblank;
}
namespace std __attribute__ ((__visibility__ ("default")))
{

  class locale;
  template<typename _Facet>
    bool
    has_facet(const locale&) throw();
  template<typename _Facet>
    const _Facet&
    use_facet(const locale&);
  template<typename _CharT>
    bool
    isspace(_CharT, const locale&);
  template<typename _CharT>
    bool
    isprint(_CharT, const locale&);
  template<typename _CharT>
    bool
    iscntrl(_CharT, const locale&);
  template<typename _CharT>
    bool
    isupper(_CharT, const locale&);
  template<typename _CharT>
    bool
    islower(_CharT, const locale&);
  template<typename _CharT>
    bool
    isalpha(_CharT, const locale&);
  template<typename _CharT>
    bool
    isdigit(_CharT, const locale&);
  template<typename _CharT>
    bool
    ispunct(_CharT, const locale&);
  template<typename _CharT>
    bool
    isxdigit(_CharT, const locale&);
  template<typename _CharT>
    bool
    isalnum(_CharT, const locale&);
  template<typename _CharT>
    bool
    isgraph(_CharT, const locale&);
  template<typename _CharT>
    _CharT
    toupper(_CharT, const locale&);
  template<typename _CharT>
    _CharT
    tolower(_CharT, const locale&);
  class ctype_base;
  template<typename _CharT>
    class ctype;
  template<> class ctype<char>;
  template<> class ctype<wchar_t>;
  template<typename _CharT>
    class ctype_byname;
  class codecvt_base;
  template<typename _InternT, typename _ExternT, typename _StateT>
    class codecvt;
  template<> class codecvt<char, char, mbstate_t>;
  template<> class codecvt<wchar_t, char, mbstate_t>;
  template<typename _InternT, typename _ExternT, typename _StateT>
    class codecvt_byname;

  template<typename _CharT, typename _InIter = istreambuf_iterator<_CharT> >
    class num_get;
  template<typename _CharT, typename _OutIter = ostreambuf_iterator<_CharT> >
    class num_put;

  template<typename _CharT> class numpunct;
  template<typename _CharT> class numpunct_byname;
  template<typename _CharT>
    class collate;
  template<typename _CharT> class
    collate_byname;
  class time_base;
  template<typename _CharT, typename _InIter = istreambuf_iterator<_CharT> >
    class time_get;
  template<typename _CharT, typename _InIter = istreambuf_iterator<_CharT> >
    class time_get_byname;
  template<typename _CharT, typename _OutIter = ostreambuf_iterator<_CharT> >
    class time_put;
  template<typename _CharT, typename _OutIter = ostreambuf_iterator<_CharT> >
    class time_put_byname;
  class money_base;

  template<typename _CharT, typename _InIter = istreambuf_iterator<_CharT> >
    class money_get;
  template<typename _CharT, typename _OutIter = ostreambuf_iterator<_CharT> >
    class money_put;

  template<typename _CharT, bool _Intl = false>
    class moneypunct;
  template<typename _CharT, bool _Intl = false>
    class moneypunct_byname;
  class messages_base;
  template<typename _CharT>
    class messages;
  template<typename _CharT>
    class messages_byname;

}
       
       
#pragma GCC visibility push(default)
namespace __cxxabiv1
{
  class __forced_unwind
  {
    virtual ~__forced_unwind() throw();
    virtual void __pure_dummy() = 0;
  };
}
#pragma GCC visibility pop
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename _CharT, typename _Traits>
    inline void
    __ostream_write(basic_ostream<_CharT, _Traits>& __out,
      const _CharT* __s, streamsize __n)
    {
      typedef basic_ostream<_CharT, _Traits> __ostream_type;
      typedef typename __ostream_type::ios_base __ios_base;
      const streamsize __put = __out.rdbuf()->sputn(__s, __n);
      if (__put != __n)
 __out.setstate(__ios_base::badbit);
    }
  template<typename _CharT, typename _Traits>
    inline void
    __ostream_fill(basic_ostream<_CharT, _Traits>& __out, streamsize __n)
    {
      typedef basic_ostream<_CharT, _Traits> __ostream_type;
      typedef typename __ostream_type::ios_base __ios_base;
      const _CharT __c = __out.fill();
      for (; __n > 0; --__n)
 {
   const typename _Traits::int_type __put = __out.rdbuf()->sputc(__c);
   if (_Traits::eq_int_type(__put, _Traits::eof()))
     {
       __out.setstate(__ios_base::badbit);
       break;
     }
 }
    }
  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    __ostream_insert(basic_ostream<_CharT, _Traits>& __out,
       const _CharT* __s, streamsize __n)
    {
      typedef basic_ostream<_CharT, _Traits> __ostream_type;
      typedef typename __ostream_type::ios_base __ios_base;
      typename __ostream_type::sentry __cerb(__out);
      if (__cerb)
 {
   try
     {
       const streamsize __w = __out.width();
       if (__w > __n)
  {
    const bool __left = ((__out.flags()
     & __ios_base::adjustfield)
           == __ios_base::left);
    if (!__left)
      __ostream_fill(__out, __w - __n);
    if (__out.good())
      __ostream_write(__out, __s, __n);
    if (__left && __out.good())
      __ostream_fill(__out, __w - __n);
  }
       else
  __ostream_write(__out, __s, __n);
       __out.width(0);
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       __out._M_setstate(__ios_base::badbit);
       throw;
     }
   catch(...)
     { __out._M_setstate(__ios_base::badbit); }
 }
      return __out;
    }
  extern template ostream& __ostream_insert(ostream&, const char*, streamsize);
  extern template wostream& __ostream_insert(wostream&, const wchar_t*,
          streamsize);

}
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename _Arg, typename _Result>
    struct unary_function
    {
      typedef _Arg argument_type;
      typedef _Result result_type;
    };
  template<typename _Arg1, typename _Arg2, typename _Result>
    struct binary_function
    {
      typedef _Arg1 first_argument_type;
      typedef _Arg2 second_argument_type;
      typedef _Result result_type;
    };
  template<typename _Tp>
    struct plus : public binary_function<_Tp, _Tp, _Tp>
    {
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x + __y; }
    };
  template<typename _Tp>
    struct minus : public binary_function<_Tp, _Tp, _Tp>
    {
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x - __y; }
    };
  template<typename _Tp>
    struct multiplies : public binary_function<_Tp, _Tp, _Tp>
    {
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x * __y; }
    };
  template<typename _Tp>
    struct divides : public binary_function<_Tp, _Tp, _Tp>
    {
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x / __y; }
    };
  template<typename _Tp>
    struct modulus : public binary_function<_Tp, _Tp, _Tp>
    {
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x % __y; }
    };
  template<typename _Tp>
    struct negate : public unary_function<_Tp, _Tp>
    {
      _Tp
      operator()(const _Tp& __x) const
      { return -__x; }
    };
  template<typename _Tp>
    struct equal_to : public binary_function<_Tp, _Tp, bool>
    {
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x == __y; }
    };
  template<typename _Tp>
    struct not_equal_to : public binary_function<_Tp, _Tp, bool>
    {
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x != __y; }
    };
  template<typename _Tp>
    struct greater : public binary_function<_Tp, _Tp, bool>
    {
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x > __y; }
    };
  template<typename _Tp>
    struct less : public binary_function<_Tp, _Tp, bool>
    {
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x < __y; }
    };
  template<typename _Tp>
    struct greater_equal : public binary_function<_Tp, _Tp, bool>
    {
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x >= __y; }
    };
  template<typename _Tp>
    struct less_equal : public binary_function<_Tp, _Tp, bool>
    {
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x <= __y; }
    };
  template<typename _Tp>
    struct logical_and : public binary_function<_Tp, _Tp, bool>
    {
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x && __y; }
    };
  template<typename _Tp>
    struct logical_or : public binary_function<_Tp, _Tp, bool>
    {
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x || __y; }
    };
  template<typename _Tp>
    struct logical_not : public unary_function<_Tp, bool>
    {
      bool
      operator()(const _Tp& __x) const
      { return !__x; }
    };
  template<typename _Tp>
    struct bit_and : public binary_function<_Tp, _Tp, _Tp>
    {
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x & __y; }
    };
  template<typename _Tp>
    struct bit_or : public binary_function<_Tp, _Tp, _Tp>
    {
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x | __y; }
    };
  template<typename _Tp>
    struct bit_xor : public binary_function<_Tp, _Tp, _Tp>
    {
      _Tp
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x ^ __y; }
    };
  template<typename _Tp>
    struct bit_not : public unary_function<_Tp, _Tp>
    {
      _Tp
      operator()(const _Tp& __x) const
      { return ~__x; }
    };
  template<typename _Predicate>
    class unary_negate
    : public unary_function<typename _Predicate::argument_type, bool>
    {
    protected:
      _Predicate _M_pred;
    public:
      explicit
      unary_negate(const _Predicate& __x) : _M_pred(__x) { }
      bool
      operator()(const typename _Predicate::argument_type& __x) const
      { return !_M_pred(__x); }
    };
  template<typename _Predicate>
    inline unary_negate<_Predicate>
    not1(const _Predicate& __pred)
    { return unary_negate<_Predicate>(__pred); }
  template<typename _Predicate>
    class binary_negate
    : public binary_function<typename _Predicate::first_argument_type,
        typename _Predicate::second_argument_type, bool>
    {
    protected:
      _Predicate _M_pred;
    public:
      explicit
      binary_negate(const _Predicate& __x) : _M_pred(__x) { }
      bool
      operator()(const typename _Predicate::first_argument_type& __x,
   const typename _Predicate::second_argument_type& __y) const
      { return !_M_pred(__x, __y); }
    };
  template<typename _Predicate>
    inline binary_negate<_Predicate>
    not2(const _Predicate& __pred)
    { return binary_negate<_Predicate>(__pred); }
  template<typename _Arg, typename _Result>
    class pointer_to_unary_function : public unary_function<_Arg, _Result>
    {
    protected:
      _Result (*_M_ptr)(_Arg);
    public:
      pointer_to_unary_function() { }
      explicit
      pointer_to_unary_function(_Result (*__x)(_Arg))
      : _M_ptr(__x) { }
      _Result
      operator()(_Arg __x) const
      { return _M_ptr(__x); }
    };
  template<typename _Arg, typename _Result>
    inline pointer_to_unary_function<_Arg, _Result>
    ptr_fun(_Result (*__x)(_Arg))
    { return pointer_to_unary_function<_Arg, _Result>(__x); }
  template<typename _Arg1, typename _Arg2, typename _Result>
    class pointer_to_binary_function
    : public binary_function<_Arg1, _Arg2, _Result>
    {
    protected:
      _Result (*_M_ptr)(_Arg1, _Arg2);
    public:
      pointer_to_binary_function() { }
      explicit
      pointer_to_binary_function(_Result (*__x)(_Arg1, _Arg2))
      : _M_ptr(__x) { }
      _Result
      operator()(_Arg1 __x, _Arg2 __y) const
      { return _M_ptr(__x, __y); }
    };
  template<typename _Arg1, typename _Arg2, typename _Result>
    inline pointer_to_binary_function<_Arg1, _Arg2, _Result>
    ptr_fun(_Result (*__x)(_Arg1, _Arg2))
    { return pointer_to_binary_function<_Arg1, _Arg2, _Result>(__x); }
  template<typename _Tp>
    struct _Identity
    : public unary_function<_Tp,_Tp>
    {
      _Tp&
      operator()(_Tp& __x) const
      { return __x; }
      const _Tp&
      operator()(const _Tp& __x) const
      { return __x; }
    };
  template<typename _Pair>
    struct _Select1st
    : public unary_function<_Pair, typename _Pair::first_type>
    {
      typename _Pair::first_type&
      operator()(_Pair& __x) const
      { return __x.first; }
      const typename _Pair::first_type&
      operator()(const _Pair& __x) const
      { return __x.first; }
      template<typename _Pair2>
        typename _Pair2::first_type&
        operator()(_Pair2& __x) const
        { return __x.first; }
      template<typename _Pair2>
        const typename _Pair2::first_type&
        operator()(const _Pair2& __x) const
        { return __x.first; }
    };
  template<typename _Pair>
    struct _Select2nd
    : public unary_function<_Pair, typename _Pair::second_type>
    {
      typename _Pair::second_type&
      operator()(_Pair& __x) const
      { return __x.second; }
      const typename _Pair::second_type&
      operator()(const _Pair& __x) const
      { return __x.second; }
    };
  template<typename _Ret, typename _Tp>
    class mem_fun_t : public unary_function<_Tp*, _Ret>
    {
    public:
      explicit
      mem_fun_t(_Ret (_Tp::*__pf)())
      : _M_f(__pf) { }
      _Ret
      operator()(_Tp* __p) const
      { return (__p->*_M_f)(); }
    private:
      _Ret (_Tp::*_M_f)();
    };
  template<typename _Ret, typename _Tp>
    class const_mem_fun_t : public unary_function<const _Tp*, _Ret>
    {
    public:
      explicit
      const_mem_fun_t(_Ret (_Tp::*__pf)() const)
      : _M_f(__pf) { }
      _Ret
      operator()(const _Tp* __p) const
      { return (__p->*_M_f)(); }
    private:
      _Ret (_Tp::*_M_f)() const;
    };
  template<typename _Ret, typename _Tp>
    class mem_fun_ref_t : public unary_function<_Tp, _Ret>
    {
    public:
      explicit
      mem_fun_ref_t(_Ret (_Tp::*__pf)())
      : _M_f(__pf) { }
      _Ret
      operator()(_Tp& __r) const
      { return (__r.*_M_f)(); }
    private:
      _Ret (_Tp::*_M_f)();
  };
  template<typename _Ret, typename _Tp>
    class const_mem_fun_ref_t : public unary_function<_Tp, _Ret>
    {
    public:
      explicit
      const_mem_fun_ref_t(_Ret (_Tp::*__pf)() const)
      : _M_f(__pf) { }
      _Ret
      operator()(const _Tp& __r) const
      { return (__r.*_M_f)(); }
    private:
      _Ret (_Tp::*_M_f)() const;
    };
  template<typename _Ret, typename _Tp, typename _Arg>
    class mem_fun1_t : public binary_function<_Tp*, _Arg, _Ret>
    {
    public:
      explicit
      mem_fun1_t(_Ret (_Tp::*__pf)(_Arg))
      : _M_f(__pf) { }
      _Ret
      operator()(_Tp* __p, _Arg __x) const
      { return (__p->*_M_f)(__x); }
    private:
      _Ret (_Tp::*_M_f)(_Arg);
    };
  template<typename _Ret, typename _Tp, typename _Arg>
    class const_mem_fun1_t : public binary_function<const _Tp*, _Arg, _Ret>
    {
    public:
      explicit
      const_mem_fun1_t(_Ret (_Tp::*__pf)(_Arg) const)
      : _M_f(__pf) { }
      _Ret
      operator()(const _Tp* __p, _Arg __x) const
      { return (__p->*_M_f)(__x); }
    private:
      _Ret (_Tp::*_M_f)(_Arg) const;
    };
  template<typename _Ret, typename _Tp, typename _Arg>
    class mem_fun1_ref_t : public binary_function<_Tp, _Arg, _Ret>
    {
    public:
      explicit
      mem_fun1_ref_t(_Ret (_Tp::*__pf)(_Arg))
      : _M_f(__pf) { }
      _Ret
      operator()(_Tp& __r, _Arg __x) const
      { return (__r.*_M_f)(__x); }
    private:
      _Ret (_Tp::*_M_f)(_Arg);
    };
  template<typename _Ret, typename _Tp, typename _Arg>
    class const_mem_fun1_ref_t : public binary_function<_Tp, _Arg, _Ret>
    {
    public:
      explicit
      const_mem_fun1_ref_t(_Ret (_Tp::*__pf)(_Arg) const)
      : _M_f(__pf) { }
      _Ret
      operator()(const _Tp& __r, _Arg __x) const
      { return (__r.*_M_f)(__x); }
    private:
      _Ret (_Tp::*_M_f)(_Arg) const;
    };
  template<typename _Ret, typename _Tp>
    inline mem_fun_t<_Ret, _Tp>
    mem_fun(_Ret (_Tp::*__f)())
    { return mem_fun_t<_Ret, _Tp>(__f); }
  template<typename _Ret, typename _Tp>
    inline const_mem_fun_t<_Ret, _Tp>
    mem_fun(_Ret (_Tp::*__f)() const)
    { return const_mem_fun_t<_Ret, _Tp>(__f); }
  template<typename _Ret, typename _Tp>
    inline mem_fun_ref_t<_Ret, _Tp>
    mem_fun_ref(_Ret (_Tp::*__f)())
    { return mem_fun_ref_t<_Ret, _Tp>(__f); }
  template<typename _Ret, typename _Tp>
    inline const_mem_fun_ref_t<_Ret, _Tp>
    mem_fun_ref(_Ret (_Tp::*__f)() const)
    { return const_mem_fun_ref_t<_Ret, _Tp>(__f); }
  template<typename _Ret, typename _Tp, typename _Arg>
    inline mem_fun1_t<_Ret, _Tp, _Arg>
    mem_fun(_Ret (_Tp::*__f)(_Arg))
    { return mem_fun1_t<_Ret, _Tp, _Arg>(__f); }
  template<typename _Ret, typename _Tp, typename _Arg>
    inline const_mem_fun1_t<_Ret, _Tp, _Arg>
    mem_fun(_Ret (_Tp::*__f)(_Arg) const)
    { return const_mem_fun1_t<_Ret, _Tp, _Arg>(__f); }
  template<typename _Ret, typename _Tp, typename _Arg>
    inline mem_fun1_ref_t<_Ret, _Tp, _Arg>
    mem_fun_ref(_Ret (_Tp::*__f)(_Arg))
    { return mem_fun1_ref_t<_Ret, _Tp, _Arg>(__f); }
  template<typename _Ret, typename _Tp, typename _Arg>
    inline const_mem_fun1_ref_t<_Ret, _Tp, _Arg>
    mem_fun_ref(_Ret (_Tp::*__f)(_Arg) const)
    { return const_mem_fun1_ref_t<_Ret, _Tp, _Arg>(__f); }

}
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename _Operation>
    class binder1st
    : public unary_function<typename _Operation::second_argument_type,
       typename _Operation::result_type>
    {
    protected:
      _Operation op;
      typename _Operation::first_argument_type value;
    public:
      binder1st(const _Operation& __x,
  const typename _Operation::first_argument_type& __y)
      : op(__x), value(__y) { }
      typename _Operation::result_type
      operator()(const typename _Operation::second_argument_type& __x) const
      { return op(value, __x); }
      typename _Operation::result_type
      operator()(typename _Operation::second_argument_type& __x) const
      { return op(value, __x); }
    } __attribute__ ((__deprecated__));
  template<typename _Operation, typename _Tp>
    inline binder1st<_Operation>
    bind1st(const _Operation& __fn, const _Tp& __x)
    {
      typedef typename _Operation::first_argument_type _Arg1_type;
      return binder1st<_Operation>(__fn, _Arg1_type(__x));
    }
  template<typename _Operation>
    class binder2nd
    : public unary_function<typename _Operation::first_argument_type,
       typename _Operation::result_type>
    {
    protected:
      _Operation op;
      typename _Operation::second_argument_type value;
    public:
      binder2nd(const _Operation& __x,
  const typename _Operation::second_argument_type& __y)
      : op(__x), value(__y) { }
      typename _Operation::result_type
      operator()(const typename _Operation::first_argument_type& __x) const
      { return op(__x, value); }
      typename _Operation::result_type
      operator()(typename _Operation::first_argument_type& __x) const
      { return op(__x, value); }
    } __attribute__ ((__deprecated__));
  template<typename _Operation, typename _Tp>
    inline binder2nd<_Operation>
    bind2nd(const _Operation& __fn, const _Tp& __x)
    {
      typedef typename _Operation::second_argument_type _Arg2_type;
      return binder2nd<_Operation>(__fn, _Arg2_type(__x));
    }

}
       
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<class _Container>
    inline auto
    begin(_Container& __cont) -> decltype(__cont.begin())
    { return __cont.begin(); }
  template<class _Container>
    inline auto
    begin(const _Container& __cont) -> decltype(__cont.begin())
    { return __cont.begin(); }
  template<class _Container>
    inline auto
    end(_Container& __cont) -> decltype(__cont.end())
    { return __cont.end(); }
  template<class _Container>
    inline auto
    end(const _Container& __cont) -> decltype(__cont.end())
    { return __cont.end(); }
  template<class _Tp, size_t _Nm>
    inline _Tp*
    begin(_Tp (&__arr)[_Nm])
    { return __arr; }
  template<class _Tp, size_t _Nm>
    inline _Tp*
    end(_Tp (&__arr)[_Nm])
    { return __arr + _Nm; }

}
       
       
#pragma GCC visibility push(default)
struct sched_param
  {
    int __sched_priority;
  };
extern "C" {
extern int clone (int (*__fn) (void *__arg), void *__child_stack,
    int __flags, void *__arg, ...) throw ();
extern int unshare (int __flags) throw ();
extern int sched_getcpu (void) throw ();
extern int setns (int __fd, int __nstype) throw ();
}
struct __sched_param
  {
    int __sched_priority;
  };
typedef unsigned long int __cpu_mask;
typedef struct
{
  __cpu_mask __bits[1024 / (8 * sizeof (__cpu_mask))];
} cpu_set_t;
extern "C" {
extern int __sched_cpucount (size_t __setsize, const cpu_set_t *__setp)
  throw ();
extern cpu_set_t *__sched_cpualloc (size_t __count) throw () ;
extern void __sched_cpufree (cpu_set_t *__set) throw ();
}
extern "C" {
extern int sched_setparam (__pid_t __pid, const struct sched_param *__param)
     throw ();
extern int sched_getparam (__pid_t __pid, struct sched_param *__param) throw ();
extern int sched_setscheduler (__pid_t __pid, int __policy,
          const struct sched_param *__param) throw ();
extern int sched_getscheduler (__pid_t __pid) throw ();
extern int sched_yield (void) throw ();
extern int sched_get_priority_max (int __algorithm) throw ();
extern int sched_get_priority_min (int __algorithm) throw ();
extern int sched_rr_get_interval (__pid_t __pid, struct timespec *__t) throw ();
extern int sched_setaffinity (__pid_t __pid, size_t __cpusetsize,
         const cpu_set_t *__cpuset) throw ();
extern int sched_getaffinity (__pid_t __pid, size_t __cpusetsize,
         cpu_set_t *__cpuset) throw ();
}
extern "C" {
struct timex
{
  unsigned int modes;
  __syscall_slong_t offset;
  __syscall_slong_t freq;
  __syscall_slong_t maxerror;
  __syscall_slong_t esterror;
  int status;
  __syscall_slong_t constant;
  __syscall_slong_t precision;
  __syscall_slong_t tolerance;
  struct timeval time;
  __syscall_slong_t tick;
  __syscall_slong_t ppsfreq;
  __syscall_slong_t jitter;
  int shift;
  __syscall_slong_t stabil;
  __syscall_slong_t jitcnt;
  __syscall_slong_t calcnt;
  __syscall_slong_t errcnt;
  __syscall_slong_t stbcnt;
  int tai;
  int :32; int :32; int :32; int :32;
  int :32; int :32; int :32; int :32;
  int :32; int :32; int :32;
};
extern "C" {
extern int clock_adjtime (__clockid_t __clock_id, struct timex *__utx) throw ();
}

struct tm
{
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;
  long int tm_gmtoff;
  const char *tm_zone;
};


struct itimerspec
  {
    struct timespec it_interval;
    struct timespec it_value;
  };
struct sigevent;

extern clock_t clock (void) throw ();
extern time_t time (time_t *__timer) throw ();
extern double difftime (time_t __time1, time_t __time0)
     throw () __attribute__ ((__const__));
extern time_t mktime (struct tm *__tp) throw ();
extern size_t strftime (char *__restrict __s, size_t __maxsize,
   const char *__restrict __format,
   const struct tm *__restrict __tp) throw ();

extern char *strptime (const char *__restrict __s,
         const char *__restrict __fmt, struct tm *__tp)
     throw ();
extern size_t strftime_l (char *__restrict __s, size_t __maxsize,
     const char *__restrict __format,
     const struct tm *__restrict __tp,
     __locale_t __loc) throw ();
extern char *strptime_l (const char *__restrict __s,
    const char *__restrict __fmt, struct tm *__tp,
    __locale_t __loc) throw ();

extern struct tm *gmtime (const time_t *__timer) throw ();
extern struct tm *localtime (const time_t *__timer) throw ();

extern struct tm *gmtime_r (const time_t *__restrict __timer,
       struct tm *__restrict __tp) throw ();
extern struct tm *localtime_r (const time_t *__restrict __timer,
          struct tm *__restrict __tp) throw ();

extern char *asctime (const struct tm *__tp) throw ();
extern char *ctime (const time_t *__timer) throw ();

extern char *asctime_r (const struct tm *__restrict __tp,
   char *__restrict __buf) throw ();
extern char *ctime_r (const time_t *__restrict __timer,
        char *__restrict __buf) throw ();
extern char *__tzname[2];
extern int __daylight;
extern long int __timezone;
extern char *tzname[2];
extern void tzset (void) throw ();
extern int daylight;
extern long int timezone;
extern int stime (const time_t *__when) throw ();
extern time_t timegm (struct tm *__tp) throw ();
extern time_t timelocal (struct tm *__tp) throw ();
extern int dysize (int __year) throw () __attribute__ ((__const__));
extern int nanosleep (const struct timespec *__requested_time,
        struct timespec *__remaining);
extern int clock_getres (clockid_t __clock_id, struct timespec *__res) throw ();
extern int clock_gettime (clockid_t __clock_id, struct timespec *__tp) throw ();
extern int clock_settime (clockid_t __clock_id, const struct timespec *__tp)
     throw ();
extern int clock_nanosleep (clockid_t __clock_id, int __flags,
       const struct timespec *__req,
       struct timespec *__rem);
extern int clock_getcpuclockid (pid_t __pid, clockid_t *__clock_id) throw ();
extern int timer_create (clockid_t __clock_id,
    struct sigevent *__restrict __evp,
    timer_t *__restrict __timerid) throw ();
extern int timer_delete (timer_t __timerid) throw ();
extern int timer_settime (timer_t __timerid, int __flags,
     const struct itimerspec *__restrict __value,
     struct itimerspec *__restrict __ovalue) throw ();
extern int timer_gettime (timer_t __timerid, struct itimerspec *__value)
     throw ();
extern int timer_getoverrun (timer_t __timerid) throw ();
extern int timespec_get (struct timespec *__ts, int __base)
     throw () __attribute__ ((__nonnull__ (1)));
extern int getdate_err;
extern struct tm *getdate (const char *__string);
extern int getdate_r (const char *__restrict __string,
        struct tm *__restrict __resbufp);
}
typedef long int __jmp_buf[8];
enum
{
  PTHREAD_CREATE_JOINABLE,
  PTHREAD_CREATE_DETACHED
};
enum
{
  PTHREAD_MUTEX_TIMED_NP,
  PTHREAD_MUTEX_RECURSIVE_NP,
  PTHREAD_MUTEX_ERRORCHECK_NP,
  PTHREAD_MUTEX_ADAPTIVE_NP
  ,
  PTHREAD_MUTEX_NORMAL = PTHREAD_MUTEX_TIMED_NP,
  PTHREAD_MUTEX_RECURSIVE = PTHREAD_MUTEX_RECURSIVE_NP,
  PTHREAD_MUTEX_ERRORCHECK = PTHREAD_MUTEX_ERRORCHECK_NP,
  PTHREAD_MUTEX_DEFAULT = PTHREAD_MUTEX_NORMAL
  , PTHREAD_MUTEX_FAST_NP = PTHREAD_MUTEX_TIMED_NP
};
enum
{
  PTHREAD_MUTEX_STALLED,
  PTHREAD_MUTEX_STALLED_NP = PTHREAD_MUTEX_STALLED,
  PTHREAD_MUTEX_ROBUST,
  PTHREAD_MUTEX_ROBUST_NP = PTHREAD_MUTEX_ROBUST
};
enum
{
  PTHREAD_PRIO_NONE,
  PTHREAD_PRIO_INHERIT,
  PTHREAD_PRIO_PROTECT
};
enum
{
  PTHREAD_RWLOCK_PREFER_READER_NP,
  PTHREAD_RWLOCK_PREFER_WRITER_NP,
  PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP,
  PTHREAD_RWLOCK_DEFAULT_NP = PTHREAD_RWLOCK_PREFER_READER_NP
};
enum
{
  PTHREAD_INHERIT_SCHED,
  PTHREAD_EXPLICIT_SCHED
};
enum
{
  PTHREAD_SCOPE_SYSTEM,
  PTHREAD_SCOPE_PROCESS
};
enum
{
  PTHREAD_PROCESS_PRIVATE,
  PTHREAD_PROCESS_SHARED
};
struct _pthread_cleanup_buffer
{
  void (*__routine) (void *);
  void *__arg;
  int __canceltype;
  struct _pthread_cleanup_buffer *__prev;
};
enum
{
  PTHREAD_CANCEL_ENABLE,
  PTHREAD_CANCEL_DISABLE
};
enum
{
  PTHREAD_CANCEL_DEFERRED,
  PTHREAD_CANCEL_ASYNCHRONOUS
};
extern "C" {
extern int pthread_create (pthread_t *__restrict __newthread,
      const pthread_attr_t *__restrict __attr,
      void *(*__start_routine) (void *),
      void *__restrict __arg) throw () __attribute__ ((__nonnull__ (1, 3)));
extern void pthread_exit (void *__retval) __attribute__ ((__noreturn__));
extern int pthread_join (pthread_t __th, void **__thread_return);
extern int pthread_tryjoin_np (pthread_t __th, void **__thread_return) throw ();
extern int pthread_timedjoin_np (pthread_t __th, void **__thread_return,
     const struct timespec *__abstime);
extern int pthread_detach (pthread_t __th) throw ();
extern pthread_t pthread_self (void) throw () __attribute__ ((__const__));
extern int pthread_equal (pthread_t __thread1, pthread_t __thread2)
  throw () __attribute__ ((__const__));
extern int pthread_attr_init (pthread_attr_t *__attr) throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_attr_destroy (pthread_attr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_attr_getdetachstate (const pthread_attr_t *__attr,
     int *__detachstate)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern int pthread_attr_setdetachstate (pthread_attr_t *__attr,
     int __detachstate)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_attr_getguardsize (const pthread_attr_t *__attr,
          size_t *__guardsize)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern int pthread_attr_setguardsize (pthread_attr_t *__attr,
          size_t __guardsize)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_attr_getschedparam (const pthread_attr_t *__restrict __attr,
           struct sched_param *__restrict __param)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern int pthread_attr_setschedparam (pthread_attr_t *__restrict __attr,
           const struct sched_param *__restrict
           __param) throw () __attribute__ ((__nonnull__ (1, 2)));
extern int pthread_attr_getschedpolicy (const pthread_attr_t *__restrict
     __attr, int *__restrict __policy)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern int pthread_attr_setschedpolicy (pthread_attr_t *__attr, int __policy)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_attr_getinheritsched (const pthread_attr_t *__restrict
      __attr, int *__restrict __inherit)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern int pthread_attr_setinheritsched (pthread_attr_t *__attr,
      int __inherit)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_attr_getscope (const pthread_attr_t *__restrict __attr,
      int *__restrict __scope)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern int pthread_attr_setscope (pthread_attr_t *__attr, int __scope)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_attr_getstackaddr (const pthread_attr_t *__restrict
          __attr, void **__restrict __stackaddr)
     throw () __attribute__ ((__nonnull__ (1, 2))) __attribute__ ((__deprecated__));
extern int pthread_attr_setstackaddr (pthread_attr_t *__attr,
          void *__stackaddr)
     throw () __attribute__ ((__nonnull__ (1))) __attribute__ ((__deprecated__));
extern int pthread_attr_getstacksize (const pthread_attr_t *__restrict
          __attr, size_t *__restrict __stacksize)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern int pthread_attr_setstacksize (pthread_attr_t *__attr,
          size_t __stacksize)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_attr_getstack (const pthread_attr_t *__restrict __attr,
      void **__restrict __stackaddr,
      size_t *__restrict __stacksize)
     throw () __attribute__ ((__nonnull__ (1, 2, 3)));
extern int pthread_attr_setstack (pthread_attr_t *__attr, void *__stackaddr,
      size_t __stacksize) throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_attr_setaffinity_np (pthread_attr_t *__attr,
     size_t __cpusetsize,
     const cpu_set_t *__cpuset)
     throw () __attribute__ ((__nonnull__ (1, 3)));
extern int pthread_attr_getaffinity_np (const pthread_attr_t *__attr,
     size_t __cpusetsize,
     cpu_set_t *__cpuset)
     throw () __attribute__ ((__nonnull__ (1, 3)));
extern int pthread_getattr_default_np (pthread_attr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_setattr_default_np (const pthread_attr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_getattr_np (pthread_t __th, pthread_attr_t *__attr)
     throw () __attribute__ ((__nonnull__ (2)));
extern int pthread_setschedparam (pthread_t __target_thread, int __policy,
      const struct sched_param *__param)
     throw () __attribute__ ((__nonnull__ (3)));
extern int pthread_getschedparam (pthread_t __target_thread,
      int *__restrict __policy,
      struct sched_param *__restrict __param)
     throw () __attribute__ ((__nonnull__ (2, 3)));
extern int pthread_setschedprio (pthread_t __target_thread, int __prio)
     throw ();
extern int pthread_getname_np (pthread_t __target_thread, char *__buf,
          size_t __buflen)
     throw () __attribute__ ((__nonnull__ (2)));
extern int pthread_setname_np (pthread_t __target_thread, const char *__name)
     throw () __attribute__ ((__nonnull__ (2)));
extern int pthread_getconcurrency (void) throw ();
extern int pthread_setconcurrency (int __level) throw ();
extern int pthread_yield (void) throw ();
extern int pthread_setaffinity_np (pthread_t __th, size_t __cpusetsize,
       const cpu_set_t *__cpuset)
     throw () __attribute__ ((__nonnull__ (3)));
extern int pthread_getaffinity_np (pthread_t __th, size_t __cpusetsize,
       cpu_set_t *__cpuset)
     throw () __attribute__ ((__nonnull__ (3)));
extern int pthread_once (pthread_once_t *__once_control,
    void (*__init_routine) (void)) __attribute__ ((__nonnull__ (1, 2)));
extern int pthread_setcancelstate (int __state, int *__oldstate);
extern int pthread_setcanceltype (int __type, int *__oldtype);
extern int pthread_cancel (pthread_t __th);
extern void pthread_testcancel (void);
typedef struct
{
  struct
  {
    __jmp_buf __cancel_jmp_buf;
    int __mask_was_saved;
  } __cancel_jmp_buf[1];
  void *__pad[4];
} __pthread_unwind_buf_t __attribute__ ((__aligned__));
struct __pthread_cleanup_frame
{
  void (*__cancel_routine) (void *);
  void *__cancel_arg;
  int __do_it;
  int __cancel_type;
};
class __pthread_cleanup_class
{
  void (*__cancel_routine) (void *);
  void *__cancel_arg;
  int __do_it;
  int __cancel_type;
 public:
  __pthread_cleanup_class (void (*__fct) (void *), void *__arg)
    : __cancel_routine (__fct), __cancel_arg (__arg), __do_it (1) { }
  ~__pthread_cleanup_class () { if (__do_it) __cancel_routine (__cancel_arg); }
  void __setdoit (int __newval) { __do_it = __newval; }
  void __defer () { pthread_setcanceltype (PTHREAD_CANCEL_DEFERRED,
        &__cancel_type); }
  void __restore () const { pthread_setcanceltype (__cancel_type, 0); }
};
struct __jmp_buf_tag;
extern int __sigsetjmp (struct __jmp_buf_tag *__env, int __savemask) throw ();
extern int pthread_mutex_init (pthread_mutex_t *__mutex,
          const pthread_mutexattr_t *__mutexattr)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_mutex_destroy (pthread_mutex_t *__mutex)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_mutex_trylock (pthread_mutex_t *__mutex)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_mutex_lock (pthread_mutex_t *__mutex)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_mutex_timedlock (pthread_mutex_t *__restrict __mutex,
        const struct timespec *__restrict
        __abstime) throw () __attribute__ ((__nonnull__ (1, 2)));
extern int pthread_mutex_unlock (pthread_mutex_t *__mutex)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_mutex_getprioceiling (const pthread_mutex_t *
      __restrict __mutex,
      int *__restrict __prioceiling)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern int pthread_mutex_setprioceiling (pthread_mutex_t *__restrict __mutex,
      int __prioceiling,
      int *__restrict __old_ceiling)
     throw () __attribute__ ((__nonnull__ (1, 3)));
extern int pthread_mutex_consistent (pthread_mutex_t *__mutex)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_mutex_consistent_np (pthread_mutex_t *__mutex)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_mutexattr_init (pthread_mutexattr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_mutexattr_destroy (pthread_mutexattr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_mutexattr_getpshared (const pthread_mutexattr_t *
      __restrict __attr,
      int *__restrict __pshared)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern int pthread_mutexattr_setpshared (pthread_mutexattr_t *__attr,
      int __pshared)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_mutexattr_gettype (const pthread_mutexattr_t *__restrict
          __attr, int *__restrict __kind)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern int pthread_mutexattr_settype (pthread_mutexattr_t *__attr, int __kind)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_mutexattr_getprotocol (const pthread_mutexattr_t *
       __restrict __attr,
       int *__restrict __protocol)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern int pthread_mutexattr_setprotocol (pthread_mutexattr_t *__attr,
       int __protocol)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_mutexattr_getprioceiling (const pthread_mutexattr_t *
          __restrict __attr,
          int *__restrict __prioceiling)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern int pthread_mutexattr_setprioceiling (pthread_mutexattr_t *__attr,
          int __prioceiling)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_mutexattr_getrobust (const pthread_mutexattr_t *__attr,
     int *__robustness)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern int pthread_mutexattr_getrobust_np (const pthread_mutexattr_t *__attr,
        int *__robustness)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern int pthread_mutexattr_setrobust (pthread_mutexattr_t *__attr,
     int __robustness)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_mutexattr_setrobust_np (pthread_mutexattr_t *__attr,
        int __robustness)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_rwlock_init (pthread_rwlock_t *__restrict __rwlock,
    const pthread_rwlockattr_t *__restrict
    __attr) throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_rwlock_destroy (pthread_rwlock_t *__rwlock)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_rwlock_rdlock (pthread_rwlock_t *__rwlock)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_rwlock_tryrdlock (pthread_rwlock_t *__rwlock)
  throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_rwlock_timedrdlock (pthread_rwlock_t *__restrict __rwlock,
           const struct timespec *__restrict
           __abstime) throw () __attribute__ ((__nonnull__ (1, 2)));
extern int pthread_rwlock_wrlock (pthread_rwlock_t *__rwlock)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_rwlock_trywrlock (pthread_rwlock_t *__rwlock)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_rwlock_timedwrlock (pthread_rwlock_t *__restrict __rwlock,
           const struct timespec *__restrict
           __abstime) throw () __attribute__ ((__nonnull__ (1, 2)));
extern int pthread_rwlock_unlock (pthread_rwlock_t *__rwlock)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_rwlockattr_init (pthread_rwlockattr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_rwlockattr_destroy (pthread_rwlockattr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_rwlockattr_getpshared (const pthread_rwlockattr_t *
       __restrict __attr,
       int *__restrict __pshared)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern int pthread_rwlockattr_setpshared (pthread_rwlockattr_t *__attr,
       int __pshared)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_rwlockattr_getkind_np (const pthread_rwlockattr_t *
       __restrict __attr,
       int *__restrict __pref)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern int pthread_rwlockattr_setkind_np (pthread_rwlockattr_t *__attr,
       int __pref) throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_cond_init (pthread_cond_t *__restrict __cond,
         const pthread_condattr_t *__restrict __cond_attr)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_cond_destroy (pthread_cond_t *__cond)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_cond_signal (pthread_cond_t *__cond)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_cond_broadcast (pthread_cond_t *__cond)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_cond_wait (pthread_cond_t *__restrict __cond,
         pthread_mutex_t *__restrict __mutex)
     __attribute__ ((__nonnull__ (1, 2)));
extern int pthread_cond_timedwait (pthread_cond_t *__restrict __cond,
       pthread_mutex_t *__restrict __mutex,
       const struct timespec *__restrict __abstime)
     __attribute__ ((__nonnull__ (1, 2, 3)));
extern int pthread_condattr_init (pthread_condattr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_condattr_destroy (pthread_condattr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_condattr_getpshared (const pthread_condattr_t *
     __restrict __attr,
     int *__restrict __pshared)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern int pthread_condattr_setpshared (pthread_condattr_t *__attr,
     int __pshared) throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_condattr_getclock (const pthread_condattr_t *
          __restrict __attr,
          __clockid_t *__restrict __clock_id)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern int pthread_condattr_setclock (pthread_condattr_t *__attr,
          __clockid_t __clock_id)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_spin_init (pthread_spinlock_t *__lock, int __pshared)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_spin_destroy (pthread_spinlock_t *__lock)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_spin_lock (pthread_spinlock_t *__lock)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_spin_trylock (pthread_spinlock_t *__lock)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_spin_unlock (pthread_spinlock_t *__lock)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_barrier_init (pthread_barrier_t *__restrict __barrier,
     const pthread_barrierattr_t *__restrict
     __attr, unsigned int __count)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_barrier_destroy (pthread_barrier_t *__barrier)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_barrier_wait (pthread_barrier_t *__barrier)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_barrierattr_init (pthread_barrierattr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_barrierattr_destroy (pthread_barrierattr_t *__attr)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_barrierattr_getpshared (const pthread_barrierattr_t *
        __restrict __attr,
        int *__restrict __pshared)
     throw () __attribute__ ((__nonnull__ (1, 2)));
extern int pthread_barrierattr_setpshared (pthread_barrierattr_t *__attr,
        int __pshared)
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_key_create (pthread_key_t *__key,
          void (*__destr_function) (void *))
     throw () __attribute__ ((__nonnull__ (1)));
extern int pthread_key_delete (pthread_key_t __key) throw ();
extern void *pthread_getspecific (pthread_key_t __key) throw ();
extern int pthread_setspecific (pthread_key_t __key,
    const void *__pointer) throw () ;
extern int pthread_getcpuclockid (pthread_t __thread_id,
      __clockid_t *__clock_id)
     throw () __attribute__ ((__nonnull__ (2)));
extern int pthread_atfork (void (*__prepare) (void),
      void (*__parent) (void),
      void (*__child) (void)) throw ();
}
typedef pthread_t __gthread_t;
typedef pthread_key_t __gthread_key_t;
typedef pthread_once_t __gthread_once_t;
typedef pthread_mutex_t __gthread_mutex_t;
typedef pthread_mutex_t __gthread_recursive_mutex_t;
typedef pthread_cond_t __gthread_cond_t;
typedef struct timespec __gthread_time_t;
static __typeof(pthread_once) __gthrw_pthread_once __attribute__ ((__weakref__("pthread_once")));
static __typeof(pthread_getspecific) __gthrw_pthread_getspecific __attribute__ ((__weakref__("pthread_getspecific")));
static __typeof(pthread_setspecific) __gthrw_pthread_setspecific __attribute__ ((__weakref__("pthread_setspecific")));
static __typeof(pthread_create) __gthrw_pthread_create __attribute__ ((__weakref__("pthread_create")));
static __typeof(pthread_join) __gthrw_pthread_join __attribute__ ((__weakref__("pthread_join")));
static __typeof(pthread_equal) __gthrw_pthread_equal __attribute__ ((__weakref__("pthread_equal")));
static __typeof(pthread_self) __gthrw_pthread_self __attribute__ ((__weakref__("pthread_self")));
static __typeof(pthread_detach) __gthrw_pthread_detach __attribute__ ((__weakref__("pthread_detach")));
static __typeof(pthread_cancel) __gthrw_pthread_cancel __attribute__ ((__weakref__("pthread_cancel")));
static __typeof(sched_yield) __gthrw_sched_yield __attribute__ ((__weakref__("sched_yield")));
static __typeof(pthread_mutex_lock) __gthrw_pthread_mutex_lock __attribute__ ((__weakref__("pthread_mutex_lock")));
static __typeof(pthread_mutex_trylock) __gthrw_pthread_mutex_trylock __attribute__ ((__weakref__("pthread_mutex_trylock")));
static __typeof(pthread_mutex_timedlock) __gthrw_pthread_mutex_timedlock __attribute__ ((__weakref__("pthread_mutex_timedlock")));
static __typeof(pthread_mutex_unlock) __gthrw_pthread_mutex_unlock __attribute__ ((__weakref__("pthread_mutex_unlock")));
static __typeof(pthread_mutex_init) __gthrw_pthread_mutex_init __attribute__ ((__weakref__("pthread_mutex_init")));
static __typeof(pthread_mutex_destroy) __gthrw_pthread_mutex_destroy __attribute__ ((__weakref__("pthread_mutex_destroy")));
static __typeof(pthread_cond_init) __gthrw_pthread_cond_init __attribute__ ((__weakref__("pthread_cond_init")));
static __typeof(pthread_cond_broadcast) __gthrw_pthread_cond_broadcast __attribute__ ((__weakref__("pthread_cond_broadcast")));
static __typeof(pthread_cond_signal) __gthrw_pthread_cond_signal __attribute__ ((__weakref__("pthread_cond_signal")));
static __typeof(pthread_cond_wait) __gthrw_pthread_cond_wait __attribute__ ((__weakref__("pthread_cond_wait")));
static __typeof(pthread_cond_timedwait) __gthrw_pthread_cond_timedwait __attribute__ ((__weakref__("pthread_cond_timedwait")));
static __typeof(pthread_cond_destroy) __gthrw_pthread_cond_destroy __attribute__ ((__weakref__("pthread_cond_destroy")));
static __typeof(pthread_key_create) __gthrw_pthread_key_create __attribute__ ((__weakref__("pthread_key_create")));
static __typeof(pthread_key_delete) __gthrw_pthread_key_delete __attribute__ ((__weakref__("pthread_key_delete")));
static __typeof(pthread_mutexattr_init) __gthrw_pthread_mutexattr_init __attribute__ ((__weakref__("pthread_mutexattr_init")));
static __typeof(pthread_mutexattr_settype) __gthrw_pthread_mutexattr_settype __attribute__ ((__weakref__("pthread_mutexattr_settype")));
static __typeof(pthread_mutexattr_destroy) __gthrw_pthread_mutexattr_destroy __attribute__ ((__weakref__("pthread_mutexattr_destroy")));
static __typeof(pthread_key_create) __gthrw___pthread_key_create __attribute__ ((__weakref__("__pthread_key_create")));
static inline int
__gthread_active_p (void)
{
  static void *const __gthread_active_ptr
    = __extension__ (void *) &__gthrw___pthread_key_create;
  return __gthread_active_ptr != 0;
}
static inline int
__gthread_create (__gthread_t *__threadid, void *(*__func) (void*),
    void *__args)
{
  return __gthrw_pthread_create (__threadid, __null, __func, __args);
}
static inline int
__gthread_join (__gthread_t __threadid, void **__value_ptr)
{
  return __gthrw_pthread_join (__threadid, __value_ptr);
}
static inline int
__gthread_detach (__gthread_t __threadid)
{
  return __gthrw_pthread_detach (__threadid);
}
static inline int
__gthread_equal (__gthread_t __t1, __gthread_t __t2)
{
  return __gthrw_pthread_equal (__t1, __t2);
}
static inline __gthread_t
__gthread_self (void)
{
  return __gthrw_pthread_self ();
}
static inline int
__gthread_yield (void)
{
  return __gthrw_sched_yield ();
}
static inline int
__gthread_once (__gthread_once_t *__once, void (*__func) (void))
{
  if (__gthread_active_p ())
    return __gthrw_pthread_once (__once, __func);
  else
    return -1;
}
static inline int
__gthread_key_create (__gthread_key_t *__key, void (*__dtor) (void *))
{
  return __gthrw_pthread_key_create (__key, __dtor);
}
static inline int
__gthread_key_delete (__gthread_key_t __key)
{
  return __gthrw_pthread_key_delete (__key);
}
static inline void *
__gthread_getspecific (__gthread_key_t __key)
{
  return __gthrw_pthread_getspecific (__key);
}
static inline int
__gthread_setspecific (__gthread_key_t __key, const void *__ptr)
{
  return __gthrw_pthread_setspecific (__key, __ptr);
}
static inline void
__gthread_mutex_init_function (__gthread_mutex_t *__mutex)
{
  if (__gthread_active_p ())
    __gthrw_pthread_mutex_init (__mutex, __null);
}
static inline int
__gthread_mutex_destroy (__gthread_mutex_t *__mutex)
{
  if (__gthread_active_p ())
    return __gthrw_pthread_mutex_destroy (__mutex);
  else
    return 0;
}
static inline int
__gthread_mutex_lock (__gthread_mutex_t *__mutex)
{
  if (__gthread_active_p ())
    return __gthrw_pthread_mutex_lock (__mutex);
  else
    return 0;
}
static inline int
__gthread_mutex_trylock (__gthread_mutex_t *__mutex)
{
  if (__gthread_active_p ())
    return __gthrw_pthread_mutex_trylock (__mutex);
  else
    return 0;
}
static inline int
__gthread_mutex_timedlock (__gthread_mutex_t *__mutex,
      const __gthread_time_t *__abs_timeout)
{
  if (__gthread_active_p ())
    return __gthrw_pthread_mutex_timedlock (__mutex, __abs_timeout);
  else
    return 0;
}
static inline int
__gthread_mutex_unlock (__gthread_mutex_t *__mutex)
{
  if (__gthread_active_p ())
    return __gthrw_pthread_mutex_unlock (__mutex);
  else
    return 0;
}
static inline int
__gthread_recursive_mutex_lock (__gthread_recursive_mutex_t *__mutex)
{
  return __gthread_mutex_lock (__mutex);
}
static inline int
__gthread_recursive_mutex_trylock (__gthread_recursive_mutex_t *__mutex)
{
  return __gthread_mutex_trylock (__mutex);
}
static inline int
__gthread_recursive_mutex_timedlock (__gthread_recursive_mutex_t *__mutex,
         const __gthread_time_t *__abs_timeout)
{
  return __gthread_mutex_timedlock (__mutex, __abs_timeout);
}
static inline int
__gthread_recursive_mutex_unlock (__gthread_recursive_mutex_t *__mutex)
{
  return __gthread_mutex_unlock (__mutex);
}
static inline int
__gthread_recursive_mutex_destroy (__gthread_recursive_mutex_t *__mutex)
{
  return __gthread_mutex_destroy (__mutex);
}
static inline int
__gthread_cond_broadcast (__gthread_cond_t *__cond)
{
  return __gthrw_pthread_cond_broadcast (__cond);
}
static inline int
__gthread_cond_signal (__gthread_cond_t *__cond)
{
  return __gthrw_pthread_cond_signal (__cond);
}
static inline int
__gthread_cond_wait (__gthread_cond_t *__cond, __gthread_mutex_t *__mutex)
{
  return __gthrw_pthread_cond_wait (__cond, __mutex);
}
static inline int
__gthread_cond_timedwait (__gthread_cond_t *__cond, __gthread_mutex_t *__mutex,
     const __gthread_time_t *__abs_timeout)
{
  return __gthrw_pthread_cond_timedwait (__cond, __mutex, __abs_timeout);
}
static inline int
__gthread_cond_wait_recursive (__gthread_cond_t *__cond,
          __gthread_recursive_mutex_t *__mutex)
{
  return __gthread_cond_wait (__cond, __mutex);
}
static inline int
__gthread_cond_destroy (__gthread_cond_t* __cond)
{
  return __gthrw_pthread_cond_destroy (__cond);
}
#pragma GCC visibility pop
typedef int _Atomic_word;
namespace __gnu_cxx __attribute__ ((__visibility__ ("default")))
{

  static inline _Atomic_word
  __exchange_and_add(volatile _Atomic_word* __mem, int __val)
  { return __atomic_fetch_add(__mem, __val, 4); }
  static inline void
  __atomic_add(volatile _Atomic_word* __mem, int __val)
  { __atomic_fetch_add(__mem, __val, 4); }
  static inline _Atomic_word
  __exchange_and_add_single(_Atomic_word* __mem, int __val)
  {
    _Atomic_word __result = *__mem;
    *__mem += __val;
    return __result;
  }
  static inline void
  __atomic_add_single(_Atomic_word* __mem, int __val)
  { *__mem += __val; }
  static inline _Atomic_word
  __attribute__ ((__unused__))
  __exchange_and_add_dispatch(_Atomic_word* __mem, int __val)
  {
    if (__gthread_active_p())
      return __exchange_and_add(__mem, __val);
    else
      return __exchange_and_add_single(__mem, __val);
  }
  static inline void
  __attribute__ ((__unused__))
  __atomic_add_dispatch(_Atomic_word* __mem, int __val)
  {
    if (__gthread_active_p())
      __atomic_add(__mem, __val);
    else
      __atomic_add_single(__mem, __val);
  }

}
       
#pragma GCC visibility push(default)
namespace std
{
  template<class _E>
    class initializer_list
    {
    public:
      typedef _E value_type;
      typedef const _E& reference;
      typedef const _E& const_reference;
      typedef size_t size_type;
      typedef const _E* iterator;
      typedef const _E* const_iterator;
    private:
      iterator _M_array;
      size_type _M_len;
      constexpr initializer_list(const_iterator __a, size_type __l)
      : _M_array(__a), _M_len(__l) { }
    public:
      constexpr initializer_list() noexcept
      : _M_array(0), _M_len(0) { }
      constexpr size_type
      size() const noexcept { return _M_len; }
      constexpr const_iterator
      begin() const noexcept { return _M_array; }
      constexpr const_iterator
      end() const noexcept { return begin() + size(); }
    };
  template<class _Tp>
    constexpr const _Tp*
    begin(initializer_list<_Tp> __ils) noexcept
    { return __ils.begin(); }
  template<class _Tp>
    constexpr const _Tp*
    end(initializer_list<_Tp> __ils) noexcept
    { return __ils.end(); }
}
#pragma GCC visibility pop
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename _CharT, typename _Traits, typename _Alloc>
    class basic_string
    {
      typedef typename _Alloc::template rebind<_CharT>::other _CharT_alloc_type;
    public:
      typedef _Traits traits_type;
      typedef typename _Traits::char_type value_type;
      typedef _Alloc allocator_type;
      typedef typename _CharT_alloc_type::size_type size_type;
      typedef typename _CharT_alloc_type::difference_type difference_type;
      typedef typename _CharT_alloc_type::reference reference;
      typedef typename _CharT_alloc_type::const_reference const_reference;
      typedef typename _CharT_alloc_type::pointer pointer;
      typedef typename _CharT_alloc_type::const_pointer const_pointer;
      typedef __gnu_cxx::__normal_iterator<pointer, basic_string> iterator;
      typedef __gnu_cxx::__normal_iterator<const_pointer, basic_string>
                                                            const_iterator;
      typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
      typedef std::reverse_iterator<iterator> reverse_iterator;
    private:
      struct _Rep_base
      {
 size_type _M_length;
 size_type _M_capacity;
 _Atomic_word _M_refcount;
      };
      struct _Rep : _Rep_base
      {
 typedef typename _Alloc::template rebind<char>::other _Raw_bytes_alloc;
 static const size_type _S_max_size;
 static const _CharT _S_terminal;
        static size_type _S_empty_rep_storage[];
        static _Rep&
        _S_empty_rep() noexcept
        {
   void* __p = reinterpret_cast<void*>(&_S_empty_rep_storage);
   return *reinterpret_cast<_Rep*>(__p);
 }
        bool
 _M_is_leaked() const noexcept
        { return this->_M_refcount < 0; }
        bool
 _M_is_shared() const noexcept
        { return this->_M_refcount > 0; }
        void
 _M_set_leaked() noexcept
        { this->_M_refcount = -1; }
        void
 _M_set_sharable() noexcept
        { this->_M_refcount = 0; }
 void
 _M_set_length_and_sharable(size_type __n) noexcept
 {
   if (__builtin_expect(this != &_S_empty_rep(), false))
     {
       this->_M_set_sharable();
       this->_M_length = __n;
       traits_type::assign(this->_M_refdata()[__n], _S_terminal);
     }
 }
 _CharT*
 _M_refdata() throw()
 { return reinterpret_cast<_CharT*>(this + 1); }
 _CharT*
 _M_grab(const _Alloc& __alloc1, const _Alloc& __alloc2)
 {
   return (!_M_is_leaked() && __alloc1 == __alloc2)
           ? _M_refcopy() : _M_clone(__alloc1);
 }
 static _Rep*
 _S_create(size_type, size_type, const _Alloc&);
 void
 _M_dispose(const _Alloc& __a) noexcept
 {
   if (__builtin_expect(this != &_S_empty_rep(), false))
     {
       ;
       if (__gnu_cxx::__exchange_and_add_dispatch(&this->_M_refcount,
        -1) <= 0)
  {
    ;
    _M_destroy(__a);
  }
     }
 }
 void
 _M_destroy(const _Alloc&) throw();
 _CharT*
 _M_refcopy() throw()
 {
   if (__builtin_expect(this != &_S_empty_rep(), false))
            __gnu_cxx::__atomic_add_dispatch(&this->_M_refcount, 1);
   return _M_refdata();
 }
 _CharT*
 _M_clone(const _Alloc&, size_type __res = 0);
      };
      struct _Alloc_hider : _Alloc
      {
 _Alloc_hider(_CharT* __dat, const _Alloc& __a) noexcept
 : _Alloc(__a), _M_p(__dat) { }
 _CharT* _M_p;
      };
    public:
      static const size_type npos = static_cast<size_type>(-1);
    private:
      mutable _Alloc_hider _M_dataplus;
      _CharT*
      _M_data() const noexcept
      { return _M_dataplus._M_p; }
      _CharT*
      _M_data(_CharT* __p) noexcept
      { return (_M_dataplus._M_p = __p); }
      _Rep*
      _M_rep() const noexcept
      { return &((reinterpret_cast<_Rep*> (_M_data()))[-1]); }
      iterator
      _M_ibegin() const noexcept
      { return iterator(_M_data()); }
      iterator
      _M_iend() const noexcept
      { return iterator(_M_data() + this->size()); }
      void
      _M_leak()
      {
 if (!_M_rep()->_M_is_leaked())
   _M_leak_hard();
      }
      size_type
      _M_check(size_type __pos, const char* __s) const
      {
 if (__pos > this->size())
   __throw_out_of_range_fmt(("%s: __pos (which is %zu) > " "this->size() (which is %zu)"),
       __s, __pos, this->size());
 return __pos;
      }
      void
      _M_check_length(size_type __n1, size_type __n2, const char* __s) const
      {
 if (this->max_size() - (this->size() - __n1) < __n2)
   __throw_length_error((__s));
      }
      size_type
      _M_limit(size_type __pos, size_type __off) const noexcept
      {
 const bool __testoff = __off < this->size() - __pos;
 return __testoff ? __off : this->size() - __pos;
      }
      bool
      _M_disjunct(const _CharT* __s) const noexcept
      {
 return (less<const _CharT*>()(__s, _M_data())
  || less<const _CharT*>()(_M_data() + this->size(), __s));
      }
      static void
      _M_copy(_CharT* __d, const _CharT* __s, size_type __n) noexcept
      {
 if (__n == 1)
   traits_type::assign(*__d, *__s);
 else
   traits_type::copy(__d, __s, __n);
      }
      static void
      _M_move(_CharT* __d, const _CharT* __s, size_type __n) noexcept
      {
 if (__n == 1)
   traits_type::assign(*__d, *__s);
 else
   traits_type::move(__d, __s, __n);
      }
      static void
      _M_assign(_CharT* __d, size_type __n, _CharT __c) noexcept
      {
 if (__n == 1)
   traits_type::assign(*__d, __c);
 else
   traits_type::assign(__d, __n, __c);
      }
      template<class _Iterator>
        static void
        _S_copy_chars(_CharT* __p, _Iterator __k1, _Iterator __k2)
 noexcept
        {
   for (; __k1 != __k2; ++__k1, ++__p)
     traits_type::assign(*__p, *__k1);
 }
      static void
      _S_copy_chars(_CharT* __p, iterator __k1, iterator __k2) noexcept
      { _S_copy_chars(__p, __k1.base(), __k2.base()); }
      static void
      _S_copy_chars(_CharT* __p, const_iterator __k1, const_iterator __k2)
      noexcept
      { _S_copy_chars(__p, __k1.base(), __k2.base()); }
      static void
      _S_copy_chars(_CharT* __p, _CharT* __k1, _CharT* __k2) noexcept
      { _M_copy(__p, __k1, __k2 - __k1); }
      static void
      _S_copy_chars(_CharT* __p, const _CharT* __k1, const _CharT* __k2)
      noexcept
      { _M_copy(__p, __k1, __k2 - __k1); }
      static int
      _S_compare(size_type __n1, size_type __n2) noexcept
      {
 const difference_type __d = difference_type(__n1 - __n2);
 if (__d > __gnu_cxx::__numeric_traits<int>::__max)
   return __gnu_cxx::__numeric_traits<int>::__max;
 else if (__d < __gnu_cxx::__numeric_traits<int>::__min)
   return __gnu_cxx::__numeric_traits<int>::__min;
 else
   return int(__d);
      }
      void
      _M_mutate(size_type __pos, size_type __len1, size_type __len2);
      void
      _M_leak_hard();
      static _Rep&
      _S_empty_rep() noexcept
      { return _Rep::_S_empty_rep(); }
    public:
      basic_string()
      : _M_dataplus(_S_empty_rep()._M_refdata(), _Alloc()) { }
      explicit
      basic_string(const _Alloc& __a);
      basic_string(const basic_string& __str);
      basic_string(const basic_string& __str, size_type __pos,
     size_type __n = npos);
      basic_string(const basic_string& __str, size_type __pos,
     size_type __n, const _Alloc& __a);
      basic_string(const _CharT* __s, size_type __n,
     const _Alloc& __a = _Alloc());
      basic_string(const _CharT* __s, const _Alloc& __a = _Alloc());
      basic_string(size_type __n, _CharT __c, const _Alloc& __a = _Alloc());
      basic_string(basic_string&& __str)
      noexcept
      : _M_dataplus(__str._M_dataplus)
      {
 __str._M_data(_S_empty_rep()._M_refdata());
      }
      basic_string(initializer_list<_CharT> __l, const _Alloc& __a = _Alloc());
      template<class _InputIterator>
        basic_string(_InputIterator __beg, _InputIterator __end,
       const _Alloc& __a = _Alloc());
      ~basic_string() noexcept
      { _M_rep()->_M_dispose(this->get_allocator()); }
      basic_string&
      operator=(const basic_string& __str)
      { return this->assign(__str); }
      basic_string&
      operator=(const _CharT* __s)
      { return this->assign(__s); }
      basic_string&
      operator=(_CharT __c)
      {
 this->assign(1, __c);
 return *this;
      }
      basic_string&
      operator=(basic_string&& __str)
      {
 this->swap(__str);
 return *this;
      }
      basic_string&
      operator=(initializer_list<_CharT> __l)
      {
 this->assign(__l.begin(), __l.size());
 return *this;
      }
      iterator
      begin()
      {
 _M_leak();
 return iterator(_M_data());
      }
      const_iterator
      begin() const noexcept
      { return const_iterator(_M_data()); }
      iterator
      end()
      {
 _M_leak();
 return iterator(_M_data() + this->size());
      }
      const_iterator
      end() const noexcept
      { return const_iterator(_M_data() + this->size()); }
      reverse_iterator
      rbegin()
      { return reverse_iterator(this->end()); }
      const_reverse_iterator
      rbegin() const noexcept
      { return const_reverse_iterator(this->end()); }
      reverse_iterator
      rend()
      { return reverse_iterator(this->begin()); }
      const_reverse_iterator
      rend() const noexcept
      { return const_reverse_iterator(this->begin()); }
      const_iterator
      cbegin() const noexcept
      { return const_iterator(this->_M_data()); }
      const_iterator
      cend() const noexcept
      { return const_iterator(this->_M_data() + this->size()); }
      const_reverse_iterator
      crbegin() const noexcept
      { return const_reverse_iterator(this->end()); }
      const_reverse_iterator
      crend() const noexcept
      { return const_reverse_iterator(this->begin()); }
    public:
      size_type
      size() const noexcept
      { return _M_rep()->_M_length; }
      size_type
      length() const noexcept
      { return _M_rep()->_M_length; }
      size_type
      max_size() const noexcept
      { return _Rep::_S_max_size; }
      void
      resize(size_type __n, _CharT __c);
      void
      resize(size_type __n)
      { this->resize(__n, _CharT()); }
      void
      shrink_to_fit() noexcept
      {
 if (capacity() > size())
   {
     try
       { reserve(0); }
     catch(...)
       { }
   }
      }
      size_type
      capacity() const noexcept
      { return _M_rep()->_M_capacity; }
      void
      reserve(size_type __res_arg = 0);
      void
      clear()
      { _M_mutate(0, this->size(), 0); }
      bool
      empty() const noexcept
      { return this->size() == 0; }
      const_reference
      operator[] (size_type __pos) const noexcept
      {
 ;
 return _M_data()[__pos];
      }
      reference
      operator[](size_type __pos)
      {
 ;
 ;
 _M_leak();
 return _M_data()[__pos];
      }
      const_reference
      at(size_type __n) const
      {
 if (__n >= this->size())
   __throw_out_of_range_fmt(("basic_string::at: __n " "(which is %zu) >= this->size() " "(which is %zu)"),
       __n, this->size());
 return _M_data()[__n];
      }
      reference
      at(size_type __n)
      {
 if (__n >= size())
   __throw_out_of_range_fmt(("basic_string::at: __n " "(which is %zu) >= this->size() " "(which is %zu)"),
       __n, this->size());
 _M_leak();
 return _M_data()[__n];
      }
      reference
      front()
      { return operator[](0); }
      const_reference
      front() const noexcept
      { return operator[](0); }
      reference
      back()
      { return operator[](this->size() - 1); }
      const_reference
      back() const noexcept
      { return operator[](this->size() - 1); }
      basic_string&
      operator+=(const basic_string& __str)
      { return this->append(__str); }
      basic_string&
      operator+=(const _CharT* __s)
      { return this->append(__s); }
      basic_string&
      operator+=(_CharT __c)
      {
 this->push_back(__c);
 return *this;
      }
      basic_string&
      operator+=(initializer_list<_CharT> __l)
      { return this->append(__l.begin(), __l.size()); }
      basic_string&
      append(const basic_string& __str);
      basic_string&
      append(const basic_string& __str, size_type __pos, size_type __n);
      basic_string&
      append(const _CharT* __s, size_type __n);
      basic_string&
      append(const _CharT* __s)
      {
 ;
 return this->append(__s, traits_type::length(__s));
      }
      basic_string&
      append(size_type __n, _CharT __c);
      basic_string&
      append(initializer_list<_CharT> __l)
      { return this->append(__l.begin(), __l.size()); }
      template<class _InputIterator>
        basic_string&
        append(_InputIterator __first, _InputIterator __last)
        { return this->replace(_M_iend(), _M_iend(), __first, __last); }
      void
      push_back(_CharT __c)
      {
 const size_type __len = 1 + this->size();
 if (__len > this->capacity() || _M_rep()->_M_is_shared())
   this->reserve(__len);
 traits_type::assign(_M_data()[this->size()], __c);
 _M_rep()->_M_set_length_and_sharable(__len);
      }
      basic_string&
      assign(const basic_string& __str);
      basic_string&
      assign(basic_string&& __str)
      {
 this->swap(__str);
 return *this;
      }
      basic_string&
      assign(const basic_string& __str, size_type __pos, size_type __n)
      { return this->assign(__str._M_data()
       + __str._M_check(__pos, "basic_string::assign"),
       __str._M_limit(__pos, __n)); }
      basic_string&
      assign(const _CharT* __s, size_type __n);
      basic_string&
      assign(const _CharT* __s)
      {
 ;
 return this->assign(__s, traits_type::length(__s));
      }
      basic_string&
      assign(size_type __n, _CharT __c)
      { return _M_replace_aux(size_type(0), this->size(), __n, __c); }
      template<class _InputIterator>
        basic_string&
        assign(_InputIterator __first, _InputIterator __last)
        { return this->replace(_M_ibegin(), _M_iend(), __first, __last); }
      basic_string&
      assign(initializer_list<_CharT> __l)
      { return this->assign(__l.begin(), __l.size()); }
      void
      insert(iterator __p, size_type __n, _CharT __c)
      { this->replace(__p, __p, __n, __c); }
      template<class _InputIterator>
        void
        insert(iterator __p, _InputIterator __beg, _InputIterator __end)
        { this->replace(__p, __p, __beg, __end); }
      void
      insert(iterator __p, initializer_list<_CharT> __l)
      {
 ;
 this->insert(__p - _M_ibegin(), __l.begin(), __l.size());
      }
      basic_string&
      insert(size_type __pos1, const basic_string& __str)
      { return this->insert(__pos1, __str, size_type(0), __str.size()); }
      basic_string&
      insert(size_type __pos1, const basic_string& __str,
      size_type __pos2, size_type __n)
      { return this->insert(__pos1, __str._M_data()
       + __str._M_check(__pos2, "basic_string::insert"),
       __str._M_limit(__pos2, __n)); }
      basic_string&
      insert(size_type __pos, const _CharT* __s, size_type __n);
      basic_string&
      insert(size_type __pos, const _CharT* __s)
      {
 ;
 return this->insert(__pos, __s, traits_type::length(__s));
      }
      basic_string&
      insert(size_type __pos, size_type __n, _CharT __c)
      { return _M_replace_aux(_M_check(__pos, "basic_string::insert"),
         size_type(0), __n, __c); }
      iterator
      insert(iterator __p, _CharT __c)
      {
 ;
 const size_type __pos = __p - _M_ibegin();
 _M_replace_aux(__pos, size_type(0), size_type(1), __c);
 _M_rep()->_M_set_leaked();
 return iterator(_M_data() + __pos);
      }
      basic_string&
      erase(size_type __pos = 0, size_type __n = npos)
      {
 _M_mutate(_M_check(__pos, "basic_string::erase"),
    _M_limit(__pos, __n), size_type(0));
 return *this;
      }
      iterator
      erase(iterator __position)
      {
 ;
 const size_type __pos = __position - _M_ibegin();
 _M_mutate(__pos, size_type(1), size_type(0));
 _M_rep()->_M_set_leaked();
 return iterator(_M_data() + __pos);
      }
      iterator
      erase(iterator __first, iterator __last);
      void
      pop_back()
      { erase(size()-1, 1); }
      basic_string&
      replace(size_type __pos, size_type __n, const basic_string& __str)
      { return this->replace(__pos, __n, __str._M_data(), __str.size()); }
      basic_string&
      replace(size_type __pos1, size_type __n1, const basic_string& __str,
       size_type __pos2, size_type __n2)
      { return this->replace(__pos1, __n1, __str._M_data()
        + __str._M_check(__pos2, "basic_string::replace"),
        __str._M_limit(__pos2, __n2)); }
      basic_string&
      replace(size_type __pos, size_type __n1, const _CharT* __s,
       size_type __n2);
      basic_string&
      replace(size_type __pos, size_type __n1, const _CharT* __s)
      {
 ;
 return this->replace(__pos, __n1, __s, traits_type::length(__s));
      }
      basic_string&
      replace(size_type __pos, size_type __n1, size_type __n2, _CharT __c)
      { return _M_replace_aux(_M_check(__pos, "basic_string::replace"),
         _M_limit(__pos, __n1), __n2, __c); }
      basic_string&
      replace(iterator __i1, iterator __i2, const basic_string& __str)
      { return this->replace(__i1, __i2, __str._M_data(), __str.size()); }
      basic_string&
      replace(iterator __i1, iterator __i2, const _CharT* __s, size_type __n)
      {
 ;
 return this->replace(__i1 - _M_ibegin(), __i2 - __i1, __s, __n);
      }
      basic_string&
      replace(iterator __i1, iterator __i2, const _CharT* __s)
      {
 ;
 return this->replace(__i1, __i2, __s, traits_type::length(__s));
      }
      basic_string&
      replace(iterator __i1, iterator __i2, size_type __n, _CharT __c)
      {
 ;
 return _M_replace_aux(__i1 - _M_ibegin(), __i2 - __i1, __n, __c);
      }
      template<class _InputIterator>
        basic_string&
        replace(iterator __i1, iterator __i2,
  _InputIterator __k1, _InputIterator __k2)
        {
   ;
   ;
   typedef typename std::__is_integer<_InputIterator>::__type _Integral;
   return _M_replace_dispatch(__i1, __i2, __k1, __k2, _Integral());
 }
      basic_string&
      replace(iterator __i1, iterator __i2, _CharT* __k1, _CharT* __k2)
      {
 ;
 ;
 return this->replace(__i1 - _M_ibegin(), __i2 - __i1,
        __k1, __k2 - __k1);
      }
      basic_string&
      replace(iterator __i1, iterator __i2,
       const _CharT* __k1, const _CharT* __k2)
      {
 ;
 ;
 return this->replace(__i1 - _M_ibegin(), __i2 - __i1,
        __k1, __k2 - __k1);
      }
      basic_string&
      replace(iterator __i1, iterator __i2, iterator __k1, iterator __k2)
      {
 ;
 ;
 return this->replace(__i1 - _M_ibegin(), __i2 - __i1,
        __k1.base(), __k2 - __k1);
      }
      basic_string&
      replace(iterator __i1, iterator __i2,
       const_iterator __k1, const_iterator __k2)
      {
 ;
 ;
 return this->replace(__i1 - _M_ibegin(), __i2 - __i1,
        __k1.base(), __k2 - __k1);
      }
      basic_string& replace(iterator __i1, iterator __i2,
       initializer_list<_CharT> __l)
      { return this->replace(__i1, __i2, __l.begin(), __l.end()); }
    private:
      template<class _Integer>
 basic_string&
 _M_replace_dispatch(iterator __i1, iterator __i2, _Integer __n,
       _Integer __val, __true_type)
        { return _M_replace_aux(__i1 - _M_ibegin(), __i2 - __i1, __n, __val); }
      template<class _InputIterator>
 basic_string&
 _M_replace_dispatch(iterator __i1, iterator __i2, _InputIterator __k1,
       _InputIterator __k2, __false_type);
      basic_string&
      _M_replace_aux(size_type __pos1, size_type __n1, size_type __n2,
       _CharT __c);
      basic_string&
      _M_replace_safe(size_type __pos1, size_type __n1, const _CharT* __s,
        size_type __n2);
      template<class _InIterator>
        static _CharT*
        _S_construct_aux(_InIterator __beg, _InIterator __end,
    const _Alloc& __a, __false_type)
 {
          typedef typename iterator_traits<_InIterator>::iterator_category _Tag;
          return _S_construct(__beg, __end, __a, _Tag());
 }
      template<class _Integer>
        static _CharT*
        _S_construct_aux(_Integer __beg, _Integer __end,
    const _Alloc& __a, __true_type)
        { return _S_construct_aux_2(static_cast<size_type>(__beg),
        __end, __a); }
      static _CharT*
      _S_construct_aux_2(size_type __req, _CharT __c, const _Alloc& __a)
      { return _S_construct(__req, __c, __a); }
      template<class _InIterator>
        static _CharT*
        _S_construct(_InIterator __beg, _InIterator __end, const _Alloc& __a)
 {
   typedef typename std::__is_integer<_InIterator>::__type _Integral;
   return _S_construct_aux(__beg, __end, __a, _Integral());
        }
      template<class _InIterator>
        static _CharT*
         _S_construct(_InIterator __beg, _InIterator __end, const _Alloc& __a,
        input_iterator_tag);
      template<class _FwdIterator>
        static _CharT*
        _S_construct(_FwdIterator __beg, _FwdIterator __end, const _Alloc& __a,
       forward_iterator_tag);
      static _CharT*
      _S_construct(size_type __req, _CharT __c, const _Alloc& __a);
    public:
      size_type
      copy(_CharT* __s, size_type __n, size_type __pos = 0) const;
      void
      swap(basic_string& __s);
      const _CharT*
      c_str() const noexcept
      { return _M_data(); }
      const _CharT*
      data() const noexcept
      { return _M_data(); }
      allocator_type
      get_allocator() const noexcept
      { return _M_dataplus; }
      size_type
      find(const _CharT* __s, size_type __pos, size_type __n) const;
      size_type
      find(const basic_string& __str, size_type __pos = 0) const
 noexcept
      { return this->find(__str.data(), __pos, __str.size()); }
      size_type
      find(const _CharT* __s, size_type __pos = 0) const
      {
 ;
 return this->find(__s, __pos, traits_type::length(__s));
      }
      size_type
      find(_CharT __c, size_type __pos = 0) const noexcept;
      size_type
      rfind(const basic_string& __str, size_type __pos = npos) const
 noexcept
      { return this->rfind(__str.data(), __pos, __str.size()); }
      size_type
      rfind(const _CharT* __s, size_type __pos, size_type __n) const;
      size_type
      rfind(const _CharT* __s, size_type __pos = npos) const
      {
 ;
 return this->rfind(__s, __pos, traits_type::length(__s));
      }
      size_type
      rfind(_CharT __c, size_type __pos = npos) const noexcept;
      size_type
      find_first_of(const basic_string& __str, size_type __pos = 0) const
 noexcept
      { return this->find_first_of(__str.data(), __pos, __str.size()); }
      size_type
      find_first_of(const _CharT* __s, size_type __pos, size_type __n) const;
      size_type
      find_first_of(const _CharT* __s, size_type __pos = 0) const
      {
 ;
 return this->find_first_of(__s, __pos, traits_type::length(__s));
      }
      size_type
      find_first_of(_CharT __c, size_type __pos = 0) const noexcept
      { return this->find(__c, __pos); }
      size_type
      find_last_of(const basic_string& __str, size_type __pos = npos) const
 noexcept
      { return this->find_last_of(__str.data(), __pos, __str.size()); }
      size_type
      find_last_of(const _CharT* __s, size_type __pos, size_type __n) const;
      size_type
      find_last_of(const _CharT* __s, size_type __pos = npos) const
      {
 ;
 return this->find_last_of(__s, __pos, traits_type::length(__s));
      }
      size_type
      find_last_of(_CharT __c, size_type __pos = npos) const noexcept
      { return this->rfind(__c, __pos); }
      size_type
      find_first_not_of(const basic_string& __str, size_type __pos = 0) const
 noexcept
      { return this->find_first_not_of(__str.data(), __pos, __str.size()); }
      size_type
      find_first_not_of(const _CharT* __s, size_type __pos,
   size_type __n) const;
      size_type
      find_first_not_of(const _CharT* __s, size_type __pos = 0) const
      {
 ;
 return this->find_first_not_of(__s, __pos, traits_type::length(__s));
      }
      size_type
      find_first_not_of(_CharT __c, size_type __pos = 0) const
 noexcept;
      size_type
      find_last_not_of(const basic_string& __str, size_type __pos = npos) const
 noexcept
      { return this->find_last_not_of(__str.data(), __pos, __str.size()); }
      size_type
      find_last_not_of(const _CharT* __s, size_type __pos,
         size_type __n) const;
      size_type
      find_last_not_of(const _CharT* __s, size_type __pos = npos) const
      {
 ;
 return this->find_last_not_of(__s, __pos, traits_type::length(__s));
      }
      size_type
      find_last_not_of(_CharT __c, size_type __pos = npos) const
 noexcept;
      basic_string
      substr(size_type __pos = 0, size_type __n = npos) const
      { return basic_string(*this,
       _M_check(__pos, "basic_string::substr"), __n); }
      int
      compare(const basic_string& __str) const
      {
 const size_type __size = this->size();
 const size_type __osize = __str.size();
 const size_type __len = std::min(__size, __osize);
 int __r = traits_type::compare(_M_data(), __str.data(), __len);
 if (!__r)
   __r = _S_compare(__size, __osize);
 return __r;
      }
      int
      compare(size_type __pos, size_type __n, const basic_string& __str) const;
      int
      compare(size_type __pos1, size_type __n1, const basic_string& __str,
       size_type __pos2, size_type __n2) const;
      int
      compare(const _CharT* __s) const;
      int
      compare(size_type __pos, size_type __n1, const _CharT* __s) const;
      int
      compare(size_type __pos, size_type __n1, const _CharT* __s,
       size_type __n2) const;
  };
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>
    operator+(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
       const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    {
      basic_string<_CharT, _Traits, _Alloc> __str(__lhs);
      __str.append(__rhs);
      return __str;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT,_Traits,_Alloc>
    operator+(const _CharT* __lhs,
       const basic_string<_CharT,_Traits,_Alloc>& __rhs);
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT,_Traits,_Alloc>
    operator+(_CharT __lhs, const basic_string<_CharT,_Traits,_Alloc>& __rhs);
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline basic_string<_CharT, _Traits, _Alloc>
    operator+(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
      const _CharT* __rhs)
    {
      basic_string<_CharT, _Traits, _Alloc> __str(__lhs);
      __str.append(__rhs);
      return __str;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline basic_string<_CharT, _Traits, _Alloc>
    operator+(const basic_string<_CharT, _Traits, _Alloc>& __lhs, _CharT __rhs)
    {
      typedef basic_string<_CharT, _Traits, _Alloc> __string_type;
      typedef typename __string_type::size_type __size_type;
      __string_type __str(__lhs);
      __str.append(__size_type(1), __rhs);
      return __str;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline basic_string<_CharT, _Traits, _Alloc>
    operator+(basic_string<_CharT, _Traits, _Alloc>&& __lhs,
       const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return std::move(__lhs.append(__rhs)); }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline basic_string<_CharT, _Traits, _Alloc>
    operator+(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
       basic_string<_CharT, _Traits, _Alloc>&& __rhs)
    { return std::move(__rhs.insert(0, __lhs)); }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline basic_string<_CharT, _Traits, _Alloc>
    operator+(basic_string<_CharT, _Traits, _Alloc>&& __lhs,
       basic_string<_CharT, _Traits, _Alloc>&& __rhs)
    {
      const auto __size = __lhs.size() + __rhs.size();
      const bool __cond = (__size > __lhs.capacity()
      && __size <= __rhs.capacity());
      return __cond ? std::move(__rhs.insert(0, __lhs))
             : std::move(__lhs.append(__rhs));
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline basic_string<_CharT, _Traits, _Alloc>
    operator+(const _CharT* __lhs,
       basic_string<_CharT, _Traits, _Alloc>&& __rhs)
    { return std::move(__rhs.insert(0, __lhs)); }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline basic_string<_CharT, _Traits, _Alloc>
    operator+(_CharT __lhs,
       basic_string<_CharT, _Traits, _Alloc>&& __rhs)
    { return std::move(__rhs.insert(0, 1, __lhs)); }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline basic_string<_CharT, _Traits, _Alloc>
    operator+(basic_string<_CharT, _Traits, _Alloc>&& __lhs,
       const _CharT* __rhs)
    { return std::move(__lhs.append(__rhs)); }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline basic_string<_CharT, _Traits, _Alloc>
    operator+(basic_string<_CharT, _Traits, _Alloc>&& __lhs,
       _CharT __rhs)
    { return std::move(__lhs.append(1, __rhs)); }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator==(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
        const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __lhs.compare(__rhs) == 0; }
  template<typename _CharT>
    inline
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value, bool>::__type
    operator==(const basic_string<_CharT>& __lhs,
        const basic_string<_CharT>& __rhs)
    { return (__lhs.size() == __rhs.size()
       && !std::char_traits<_CharT>::compare(__lhs.data(), __rhs.data(),
          __lhs.size())); }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator==(const _CharT* __lhs,
        const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __rhs.compare(__lhs) == 0; }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator==(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
        const _CharT* __rhs)
    { return __lhs.compare(__rhs) == 0; }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator!=(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
        const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return !(__lhs == __rhs); }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator!=(const _CharT* __lhs,
        const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return !(__lhs == __rhs); }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator!=(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
        const _CharT* __rhs)
    { return !(__lhs == __rhs); }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator<(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
       const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __lhs.compare(__rhs) < 0; }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator<(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
       const _CharT* __rhs)
    { return __lhs.compare(__rhs) < 0; }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator<(const _CharT* __lhs,
       const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __rhs.compare(__lhs) > 0; }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator>(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
       const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __lhs.compare(__rhs) > 0; }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator>(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
       const _CharT* __rhs)
    { return __lhs.compare(__rhs) > 0; }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator>(const _CharT* __lhs,
       const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __rhs.compare(__lhs) < 0; }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator<=(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
        const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __lhs.compare(__rhs) <= 0; }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator<=(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
        const _CharT* __rhs)
    { return __lhs.compare(__rhs) <= 0; }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator<=(const _CharT* __lhs,
        const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __rhs.compare(__lhs) >= 0; }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator>=(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
        const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __lhs.compare(__rhs) >= 0; }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator>=(const basic_string<_CharT, _Traits, _Alloc>& __lhs,
        const _CharT* __rhs)
    { return __lhs.compare(__rhs) >= 0; }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline bool
    operator>=(const _CharT* __lhs,
      const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { return __rhs.compare(__lhs) <= 0; }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline void
    swap(basic_string<_CharT, _Traits, _Alloc>& __lhs,
  basic_string<_CharT, _Traits, _Alloc>& __rhs)
    { __lhs.swap(__rhs); }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>& __is,
        basic_string<_CharT, _Traits, _Alloc>& __str);
  template<>
    basic_istream<char>&
    operator>>(basic_istream<char>& __is, basic_string<char>& __str);
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& __os,
        const basic_string<_CharT, _Traits, _Alloc>& __str)
    {
      return __ostream_insert(__os, __str.data(), __str.size());
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_istream<_CharT, _Traits>&
    getline(basic_istream<_CharT, _Traits>& __is,
     basic_string<_CharT, _Traits, _Alloc>& __str, _CharT __delim);
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline basic_istream<_CharT, _Traits>&
    getline(basic_istream<_CharT, _Traits>& __is,
     basic_string<_CharT, _Traits, _Alloc>& __str)
    { return std::getline(__is, __str, __is.widen('\n')); }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline basic_istream<_CharT, _Traits>&
    getline(basic_istream<_CharT, _Traits>&& __is,
     basic_string<_CharT, _Traits, _Alloc>& __str, _CharT __delim)
    { return std::getline(__is, __str, __delim); }
  template<typename _CharT, typename _Traits, typename _Alloc>
    inline basic_istream<_CharT, _Traits>&
    getline(basic_istream<_CharT, _Traits>&& __is,
     basic_string<_CharT, _Traits, _Alloc>& __str)
    { return std::getline(__is, __str); }
  template<>
    basic_istream<char>&
    getline(basic_istream<char>& __in, basic_string<char>& __str,
     char __delim);
  template<>
    basic_istream<wchar_t>&
    getline(basic_istream<wchar_t>& __in, basic_string<wchar_t>& __str,
     wchar_t __delim);

}
       
       
       
       
extern "C" {
typedef struct
{
  __off_t __pos;
  __mbstate_t __state;
} _G_fpos_t;
typedef struct
{
  __off64_t __pos;
  __mbstate_t __state;
} _G_fpos64_t;
struct _IO_jump_t; struct _IO_FILE;
typedef void _IO_lock_t;
struct _IO_marker {
  struct _IO_marker *_next;
  struct _IO_FILE *_sbuf;
  int _pos;
};
enum __codecvt_result
{
  __codecvt_ok,
  __codecvt_partial,
  __codecvt_error,
  __codecvt_noconv
};
struct _IO_FILE {
  int _flags;
  char* _IO_read_ptr;
  char* _IO_read_end;
  char* _IO_read_base;
  char* _IO_write_base;
  char* _IO_write_ptr;
  char* _IO_write_end;
  char* _IO_buf_base;
  char* _IO_buf_end;
  char *_IO_save_base;
  char *_IO_backup_base;
  char *_IO_save_end;
  struct _IO_marker *_markers;
  struct _IO_FILE *_chain;
  int _fileno;
  int _flags2;
  __off_t _old_offset;
  unsigned short _cur_column;
  signed char _vtable_offset;
  char _shortbuf[1];
  _IO_lock_t *_lock;
  __off64_t _offset;
  void *__pad1;
  void *__pad2;
  void *__pad3;
  void *__pad4;
  size_t __pad5;
  int _mode;
  char _unused2[15 * sizeof (int) - 4 * sizeof (void *) - sizeof (size_t)];
};
struct _IO_FILE_plus;
extern struct _IO_FILE_plus _IO_2_1_stdin_;
extern struct _IO_FILE_plus _IO_2_1_stdout_;
extern struct _IO_FILE_plus _IO_2_1_stderr_;
typedef __ssize_t __io_read_fn (void *__cookie, char *__buf, size_t __nbytes);
typedef __ssize_t __io_write_fn (void *__cookie, const char *__buf,
     size_t __n);
typedef int __io_seek_fn (void *__cookie, __off64_t *__pos, int __w);
typedef int __io_close_fn (void *__cookie);
typedef __io_read_fn cookie_read_function_t;
typedef __io_write_fn cookie_write_function_t;
typedef __io_seek_fn cookie_seek_function_t;
typedef __io_close_fn cookie_close_function_t;
typedef struct
{
  __io_read_fn *read;
  __io_write_fn *write;
  __io_seek_fn *seek;
  __io_close_fn *close;
} _IO_cookie_io_functions_t;
typedef _IO_cookie_io_functions_t cookie_io_functions_t;
struct _IO_cookie_file;
extern void _IO_cookie_init (struct _IO_cookie_file *__cfile, int __read_write,
        void *__cookie, _IO_cookie_io_functions_t __fns);
extern "C" {
extern int __underflow (_IO_FILE *);
extern int __uflow (_IO_FILE *);
extern int __overflow (_IO_FILE *, int);
extern int _IO_getc (_IO_FILE *__fp);
extern int _IO_putc (int __c, _IO_FILE *__fp);
extern int _IO_feof (_IO_FILE *__fp) throw ();
extern int _IO_ferror (_IO_FILE *__fp) throw ();
extern int _IO_peekc_locked (_IO_FILE *__fp);
extern void _IO_flockfile (_IO_FILE *) throw ();
extern void _IO_funlockfile (_IO_FILE *) throw ();
extern int _IO_ftrylockfile (_IO_FILE *) throw ();
extern int _IO_vfscanf (_IO_FILE * __restrict, const char * __restrict,
   __gnuc_va_list, int *__restrict);
extern int _IO_vfprintf (_IO_FILE *__restrict, const char *__restrict,
    __gnuc_va_list);
extern __ssize_t _IO_padn (_IO_FILE *, int, __ssize_t);
extern size_t _IO_sgetn (_IO_FILE *, void *, size_t);
extern __off64_t _IO_seekoff (_IO_FILE *, __off64_t, int, int);
extern __off64_t _IO_seekpos (_IO_FILE *, __off64_t, int);
extern void _IO_free_backup_area (_IO_FILE *) throw ();
}
typedef __gnuc_va_list va_list;

typedef _G_fpos_t fpos_t;

typedef _G_fpos64_t fpos64_t;
extern struct _IO_FILE *stdin;
extern struct _IO_FILE *stdout;
extern struct _IO_FILE *stderr;

extern int remove (const char *__filename) throw ();
extern int rename (const char *__old, const char *__new) throw ();

extern int renameat (int __oldfd, const char *__old, int __newfd,
       const char *__new) throw ();

extern FILE *tmpfile (void) ;
extern FILE *tmpfile64 (void) ;
extern char *tmpnam (char *__s) throw () ;

extern char *tmpnam_r (char *__s) throw () ;
extern char *tempnam (const char *__dir, const char *__pfx)
     throw () __attribute__ ((__malloc__)) ;

extern int fclose (FILE *__stream);
extern int fflush (FILE *__stream);

extern int fflush_unlocked (FILE *__stream);
extern int fcloseall (void);

extern FILE *fopen (const char *__restrict __filename,
      const char *__restrict __modes) ;
extern FILE *freopen (const char *__restrict __filename,
        const char *__restrict __modes,
        FILE *__restrict __stream) ;

extern FILE *fopen64 (const char *__restrict __filename,
        const char *__restrict __modes) ;
extern FILE *freopen64 (const char *__restrict __filename,
   const char *__restrict __modes,
   FILE *__restrict __stream) ;
extern FILE *fdopen (int __fd, const char *__modes) throw () ;
extern FILE *fopencookie (void *__restrict __magic_cookie,
     const char *__restrict __modes,
     _IO_cookie_io_functions_t __io_funcs) throw () ;
extern FILE *fmemopen (void *__s, size_t __len, const char *__modes)
  throw () ;
extern FILE *open_memstream (char **__bufloc, size_t *__sizeloc) throw () ;

extern void setbuf (FILE *__restrict __stream, char *__restrict __buf) throw ();
extern int setvbuf (FILE *__restrict __stream, char *__restrict __buf,
      int __modes, size_t __n) throw ();

extern void setbuffer (FILE *__restrict __stream, char *__restrict __buf,
         size_t __size) throw ();
extern void setlinebuf (FILE *__stream) throw ();

extern int fprintf (FILE *__restrict __stream,
      const char *__restrict __format, ...);
extern int printf (const char *__restrict __format, ...);
extern int sprintf (char *__restrict __s,
      const char *__restrict __format, ...) throw ();
extern int vfprintf (FILE *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg);
extern int vprintf (const char *__restrict __format, __gnuc_va_list __arg);
extern int vsprintf (char *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg) throw ();


extern int snprintf (char *__restrict __s, size_t __maxlen,
       const char *__restrict __format, ...)
     throw () __attribute__ ((__format__ (__printf__, 3, 4)));
extern int vsnprintf (char *__restrict __s, size_t __maxlen,
        const char *__restrict __format, __gnuc_va_list __arg)
     throw () __attribute__ ((__format__ (__printf__, 3, 0)));

extern int vasprintf (char **__restrict __ptr, const char *__restrict __f,
        __gnuc_va_list __arg)
     throw () __attribute__ ((__format__ (__printf__, 2, 0))) ;
extern int __asprintf (char **__restrict __ptr,
         const char *__restrict __fmt, ...)
     throw () __attribute__ ((__format__ (__printf__, 2, 3))) ;
extern int asprintf (char **__restrict __ptr,
       const char *__restrict __fmt, ...)
     throw () __attribute__ ((__format__ (__printf__, 2, 3))) ;
extern int vdprintf (int __fd, const char *__restrict __fmt,
       __gnuc_va_list __arg)
     __attribute__ ((__format__ (__printf__, 2, 0)));
extern int dprintf (int __fd, const char *__restrict __fmt, ...)
     __attribute__ ((__format__ (__printf__, 2, 3)));

extern int fscanf (FILE *__restrict __stream,
     const char *__restrict __format, ...) ;
extern int scanf (const char *__restrict __format, ...) ;
extern int sscanf (const char *__restrict __s,
     const char *__restrict __format, ...) throw ();


extern int vfscanf (FILE *__restrict __s, const char *__restrict __format,
      __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 2, 0))) ;
extern int vscanf (const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 1, 0))) ;
extern int vsscanf (const char *__restrict __s,
      const char *__restrict __format, __gnuc_va_list __arg)
     throw () __attribute__ ((__format__ (__scanf__, 2, 0)));


extern int fgetc (FILE *__stream);
extern int getc (FILE *__stream);
extern int getchar (void);

extern int getc_unlocked (FILE *__stream);
extern int getchar_unlocked (void);
extern int fgetc_unlocked (FILE *__stream);

extern int fputc (int __c, FILE *__stream);
extern int putc (int __c, FILE *__stream);
extern int putchar (int __c);

extern int fputc_unlocked (int __c, FILE *__stream);
extern int putc_unlocked (int __c, FILE *__stream);
extern int putchar_unlocked (int __c);
extern int getw (FILE *__stream);
extern int putw (int __w, FILE *__stream);

extern char *fgets (char *__restrict __s, int __n, FILE *__restrict __stream)
     ;
extern char *gets (char *__s) __attribute__ ((__deprecated__));

extern char *fgets_unlocked (char *__restrict __s, int __n,
        FILE *__restrict __stream) ;
extern __ssize_t __getdelim (char **__restrict __lineptr,
          size_t *__restrict __n, int __delimiter,
          FILE *__restrict __stream) ;
extern __ssize_t getdelim (char **__restrict __lineptr,
        size_t *__restrict __n, int __delimiter,
        FILE *__restrict __stream) ;
extern __ssize_t getline (char **__restrict __lineptr,
       size_t *__restrict __n,
       FILE *__restrict __stream) ;

extern int fputs (const char *__restrict __s, FILE *__restrict __stream);
extern int puts (const char *__s);
extern int ungetc (int __c, FILE *__stream);
extern size_t fread (void *__restrict __ptr, size_t __size,
       size_t __n, FILE *__restrict __stream) ;
extern size_t fwrite (const void *__restrict __ptr, size_t __size,
        size_t __n, FILE *__restrict __s);

extern int fputs_unlocked (const char *__restrict __s,
      FILE *__restrict __stream);
extern size_t fread_unlocked (void *__restrict __ptr, size_t __size,
         size_t __n, FILE *__restrict __stream) ;
extern size_t fwrite_unlocked (const void *__restrict __ptr, size_t __size,
          size_t __n, FILE *__restrict __stream);

extern int fseek (FILE *__stream, long int __off, int __whence);
extern long int ftell (FILE *__stream) ;
extern void rewind (FILE *__stream);

extern int fseeko (FILE *__stream, __off_t __off, int __whence);
extern __off_t ftello (FILE *__stream) ;

extern int fgetpos (FILE *__restrict __stream, fpos_t *__restrict __pos);
extern int fsetpos (FILE *__stream, const fpos_t *__pos);

extern int fseeko64 (FILE *__stream, __off64_t __off, int __whence);
extern __off64_t ftello64 (FILE *__stream) ;
extern int fgetpos64 (FILE *__restrict __stream, fpos64_t *__restrict __pos);
extern int fsetpos64 (FILE *__stream, const fpos64_t *__pos);

extern void clearerr (FILE *__stream) throw ();
extern int feof (FILE *__stream) throw () ;
extern int ferror (FILE *__stream) throw () ;

extern void clearerr_unlocked (FILE *__stream) throw ();
extern int feof_unlocked (FILE *__stream) throw () ;
extern int ferror_unlocked (FILE *__stream) throw () ;

extern void perror (const char *__s);

extern int sys_nerr;
extern const char *const sys_errlist[];
extern int _sys_nerr;
extern const char *const _sys_errlist[];
extern int fileno (FILE *__stream) throw () ;
extern int fileno_unlocked (FILE *__stream) throw () ;
extern FILE *popen (const char *__command, const char *__modes) ;
extern int pclose (FILE *__stream);
extern char *ctermid (char *__s) throw ();
extern char *cuserid (char *__s);
struct obstack;
extern int obstack_printf (struct obstack *__restrict __obstack,
      const char *__restrict __format, ...)
     throw () __attribute__ ((__format__ (__printf__, 2, 3)));
extern int obstack_vprintf (struct obstack *__restrict __obstack,
       const char *__restrict __format,
       __gnuc_va_list __args)
     throw () __attribute__ ((__format__ (__printf__, 2, 0)));
extern void flockfile (FILE *__stream) throw ();
extern int ftrylockfile (FILE *__stream) throw () ;
extern void funlockfile (FILE *__stream) throw ();
}
namespace std
{
  using ::FILE;
  using ::fpos_t;
  using ::clearerr;
  using ::fclose;
  using ::feof;
  using ::ferror;
  using ::fflush;
  using ::fgetc;
  using ::fgetpos;
  using ::fgets;
  using ::fopen;
  using ::fprintf;
  using ::fputc;
  using ::fputs;
  using ::fread;
  using ::freopen;
  using ::fscanf;
  using ::fseek;
  using ::fsetpos;
  using ::ftell;
  using ::fwrite;
  using ::getc;
  using ::getchar;
  using ::gets;
  using ::perror;
  using ::printf;
  using ::putc;
  using ::putchar;
  using ::puts;
  using ::remove;
  using ::rename;
  using ::rewind;
  using ::scanf;
  using ::setbuf;
  using ::setvbuf;
  using ::sprintf;
  using ::sscanf;
  using ::tmpfile;
  using ::tmpnam;
  using ::ungetc;
  using ::vfprintf;
  using ::vprintf;
  using ::vsprintf;
}
namespace __gnu_cxx
{
  using ::snprintf;
  using ::vfscanf;
  using ::vscanf;
  using ::vsnprintf;
  using ::vsscanf;
}
namespace std
{
  using ::__gnu_cxx::snprintf;
  using ::__gnu_cxx::vfscanf;
  using ::__gnu_cxx::vscanf;
  using ::__gnu_cxx::vsnprintf;
  using ::__gnu_cxx::vsscanf;
}
       
extern "C" {
extern int *__errno_location (void) throw () __attribute__ ((__const__));
extern char *program_invocation_name, *program_invocation_short_name;
}
typedef int error_t;
namespace __gnu_cxx __attribute__ ((__visibility__ ("default")))
{

  template<typename _TRet, typename _Ret = _TRet, typename _CharT,
    typename... _Base>
    _Ret
    __stoa(_TRet (*__convf) (const _CharT*, _CharT**, _Base...),
    const char* __name, const _CharT* __str, std::size_t* __idx,
    _Base... __base)
    {
      _Ret __ret;
      _CharT* __endptr;
      (*__errno_location ()) = 0;
      const _TRet __tmp = __convf(__str, &__endptr, __base...);
      if (__endptr == __str)
 std::__throw_invalid_argument(__name);
      else if ((*__errno_location ()) == 34
        || (std::__are_same<_Ret, int>::__value
     && (__tmp < __numeric_traits<int>::__min
         || __tmp > __numeric_traits<int>::__max)))
 std::__throw_out_of_range(__name);
      else
 __ret = __tmp;
      if (__idx)
 *__idx = __endptr - __str;
      return __ret;
    }
  template<typename _String, typename _CharT = typename _String::value_type>
    _String
    __to_xstring(int (*__convf) (_CharT*, std::size_t, const _CharT*,
     __builtin_va_list), std::size_t __n,
   const _CharT* __fmt, ...)
    {
      _CharT* __s = static_cast<_CharT*>(__builtin_alloca(sizeof(_CharT)
         * __n));
      __builtin_va_list __args;
      __builtin_va_start(__args, __fmt);
      const int __len = __convf(__s, __n, __fmt, __args);
      __builtin_va_end(__args);
      return _String(__s, __s + __len);
    }

}
namespace std __attribute__ ((__visibility__ ("default")))
{

  inline int
  stoi(const string& __str, size_t* __idx = 0, int __base = 10)
  { return __gnu_cxx::__stoa<long, int>(&std::strtol, "stoi", __str.c_str(),
     __idx, __base); }
  inline long
  stol(const string& __str, size_t* __idx = 0, int __base = 10)
  { return __gnu_cxx::__stoa(&std::strtol, "stol", __str.c_str(),
        __idx, __base); }
  inline unsigned long
  stoul(const string& __str, size_t* __idx = 0, int __base = 10)
  { return __gnu_cxx::__stoa(&std::strtoul, "stoul", __str.c_str(),
        __idx, __base); }
  inline long long
  stoll(const string& __str, size_t* __idx = 0, int __base = 10)
  { return __gnu_cxx::__stoa(&std::strtoll, "stoll", __str.c_str(),
        __idx, __base); }
  inline unsigned long long
  stoull(const string& __str, size_t* __idx = 0, int __base = 10)
  { return __gnu_cxx::__stoa(&std::strtoull, "stoull", __str.c_str(),
        __idx, __base); }
  inline float
  stof(const string& __str, size_t* __idx = 0)
  { return __gnu_cxx::__stoa(&std::strtof, "stof", __str.c_str(), __idx); }
  inline double
  stod(const string& __str, size_t* __idx = 0)
  { return __gnu_cxx::__stoa(&std::strtod, "stod", __str.c_str(), __idx); }
  inline long double
  stold(const string& __str, size_t* __idx = 0)
  { return __gnu_cxx::__stoa(&std::strtold, "stold", __str.c_str(), __idx); }
  inline string
  to_string(int __val)
  { return __gnu_cxx::__to_xstring<string>(&std::vsnprintf, 4 * sizeof(int),
        "%d", __val); }
  inline string
  to_string(unsigned __val)
  { return __gnu_cxx::__to_xstring<string>(&std::vsnprintf,
        4 * sizeof(unsigned),
        "%u", __val); }
  inline string
  to_string(long __val)
  { return __gnu_cxx::__to_xstring<string>(&std::vsnprintf, 4 * sizeof(long),
        "%ld", __val); }
  inline string
  to_string(unsigned long __val)
  { return __gnu_cxx::__to_xstring<string>(&std::vsnprintf,
        4 * sizeof(unsigned long),
        "%lu", __val); }
  inline string
  to_string(long long __val)
  { return __gnu_cxx::__to_xstring<string>(&std::vsnprintf,
        4 * sizeof(long long),
        "%lld", __val); }
  inline string
  to_string(unsigned long long __val)
  { return __gnu_cxx::__to_xstring<string>(&std::vsnprintf,
        4 * sizeof(unsigned long long),
        "%llu", __val); }
  inline string
  to_string(float __val)
  {
    const int __n =
      __gnu_cxx::__numeric_traits<float>::__max_exponent10 + 20;
    return __gnu_cxx::__to_xstring<string>(&std::vsnprintf, __n,
        "%f", __val);
  }
  inline string
  to_string(double __val)
  {
    const int __n =
      __gnu_cxx::__numeric_traits<double>::__max_exponent10 + 20;
    return __gnu_cxx::__to_xstring<string>(&std::vsnprintf, __n,
        "%f", __val);
  }
  inline string
  to_string(long double __val)
  {
    const int __n =
      __gnu_cxx::__numeric_traits<long double>::__max_exponent10 + 20;
    return __gnu_cxx::__to_xstring<string>(&std::vsnprintf, __n,
        "%Lf", __val);
  }
  inline int
  stoi(const wstring& __str, size_t* __idx = 0, int __base = 10)
  { return __gnu_cxx::__stoa<long, int>(&std::wcstol, "stoi", __str.c_str(),
     __idx, __base); }
  inline long
  stol(const wstring& __str, size_t* __idx = 0, int __base = 10)
  { return __gnu_cxx::__stoa(&std::wcstol, "stol", __str.c_str(),
        __idx, __base); }
  inline unsigned long
  stoul(const wstring& __str, size_t* __idx = 0, int __base = 10)
  { return __gnu_cxx::__stoa(&std::wcstoul, "stoul", __str.c_str(),
        __idx, __base); }
  inline long long
  stoll(const wstring& __str, size_t* __idx = 0, int __base = 10)
  { return __gnu_cxx::__stoa(&std::wcstoll, "stoll", __str.c_str(),
        __idx, __base); }
  inline unsigned long long
  stoull(const wstring& __str, size_t* __idx = 0, int __base = 10)
  { return __gnu_cxx::__stoa(&std::wcstoull, "stoull", __str.c_str(),
        __idx, __base); }
  inline float
  stof(const wstring& __str, size_t* __idx = 0)
  { return __gnu_cxx::__stoa(&std::wcstof, "stof", __str.c_str(), __idx); }
  inline double
  stod(const wstring& __str, size_t* __idx = 0)
  { return __gnu_cxx::__stoa(&std::wcstod, "stod", __str.c_str(), __idx); }
  inline long double
  stold(const wstring& __str, size_t* __idx = 0)
  { return __gnu_cxx::__stoa(&std::wcstold, "stold", __str.c_str(), __idx); }
  inline wstring
  to_wstring(int __val)
  { return __gnu_cxx::__to_xstring<wstring>(&std::vswprintf, 4 * sizeof(int),
         L"%d", __val); }
  inline wstring
  to_wstring(unsigned __val)
  { return __gnu_cxx::__to_xstring<wstring>(&std::vswprintf,
         4 * sizeof(unsigned),
         L"%u", __val); }
  inline wstring
  to_wstring(long __val)
  { return __gnu_cxx::__to_xstring<wstring>(&std::vswprintf, 4 * sizeof(long),
         L"%ld", __val); }
  inline wstring
  to_wstring(unsigned long __val)
  { return __gnu_cxx::__to_xstring<wstring>(&std::vswprintf,
         4 * sizeof(unsigned long),
         L"%lu", __val); }
  inline wstring
  to_wstring(long long __val)
  { return __gnu_cxx::__to_xstring<wstring>(&std::vswprintf,
         4 * sizeof(long long),
         L"%lld", __val); }
  inline wstring
  to_wstring(unsigned long long __val)
  { return __gnu_cxx::__to_xstring<wstring>(&std::vswprintf,
         4 * sizeof(unsigned long long),
         L"%llu", __val); }
  inline wstring
  to_wstring(float __val)
  {
    const int __n =
      __gnu_cxx::__numeric_traits<float>::__max_exponent10 + 20;
    return __gnu_cxx::__to_xstring<wstring>(&std::vswprintf, __n,
         L"%f", __val);
  }
  inline wstring
  to_wstring(double __val)
  {
    const int __n =
      __gnu_cxx::__numeric_traits<double>::__max_exponent10 + 20;
    return __gnu_cxx::__to_xstring<wstring>(&std::vswprintf, __n,
         L"%f", __val);
  }
  inline wstring
  to_wstring(long double __val)
  {
    const int __n =
      __gnu_cxx::__numeric_traits<long double>::__max_exponent10 + 20;
    return __gnu_cxx::__to_xstring<wstring>(&std::vswprintf, __n,
         L"%Lf", __val);
  }

}
       
       
namespace std
{

  size_t
  _Hash_bytes(const void* __ptr, size_t __len, size_t __seed);
  size_t
  _Fnv_hash_bytes(const void* __ptr, size_t __len, size_t __seed);

}
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename _Result, typename _Arg>
    struct __hash_base
    {
      typedef _Result result_type;
      typedef _Arg argument_type;
    };
  template<typename _Tp>
    struct hash;
  template<typename _Tp>
    struct hash<_Tp*> : public __hash_base<size_t, _Tp*>
    {
      size_t
      operator()(_Tp* __p) const noexcept
      { return reinterpret_cast<size_t>(__p); }
    };
  template<> struct hash<bool> : public __hash_base<size_t, bool> { size_t operator()(bool __val) const noexcept { return static_cast<size_t>(__val); } };
  template<> struct hash<char> : public __hash_base<size_t, char> { size_t operator()(char __val) const noexcept { return static_cast<size_t>(__val); } };
  template<> struct hash<signed char> : public __hash_base<size_t, signed char> { size_t operator()(signed char __val) const noexcept { return static_cast<size_t>(__val); } };
  template<> struct hash<unsigned char> : public __hash_base<size_t, unsigned char> { size_t operator()(unsigned char __val) const noexcept { return static_cast<size_t>(__val); } };
  template<> struct hash<wchar_t> : public __hash_base<size_t, wchar_t> { size_t operator()(wchar_t __val) const noexcept { return static_cast<size_t>(__val); } };
  template<> struct hash<char16_t> : public __hash_base<size_t, char16_t> { size_t operator()(char16_t __val) const noexcept { return static_cast<size_t>(__val); } };
  template<> struct hash<char32_t> : public __hash_base<size_t, char32_t> { size_t operator()(char32_t __val) const noexcept { return static_cast<size_t>(__val); } };
  template<> struct hash<short> : public __hash_base<size_t, short> { size_t operator()(short __val) const noexcept { return static_cast<size_t>(__val); } };
  template<> struct hash<int> : public __hash_base<size_t, int> { size_t operator()(int __val) const noexcept { return static_cast<size_t>(__val); } };
  template<> struct hash<long> : public __hash_base<size_t, long> { size_t operator()(long __val) const noexcept { return static_cast<size_t>(__val); } };
  template<> struct hash<long long> : public __hash_base<size_t, long long> { size_t operator()(long long __val) const noexcept { return static_cast<size_t>(__val); } };
  template<> struct hash<unsigned short> : public __hash_base<size_t, unsigned short> { size_t operator()(unsigned short __val) const noexcept { return static_cast<size_t>(__val); } };
  template<> struct hash<unsigned int> : public __hash_base<size_t, unsigned int> { size_t operator()(unsigned int __val) const noexcept { return static_cast<size_t>(__val); } };
  template<> struct hash<unsigned long> : public __hash_base<size_t, unsigned long> { size_t operator()(unsigned long __val) const noexcept { return static_cast<size_t>(__val); } };
  template<> struct hash<unsigned long long> : public __hash_base<size_t, unsigned long long> { size_t operator()(unsigned long long __val) const noexcept { return static_cast<size_t>(__val); } };
  struct _Hash_impl
  {
    static size_t
    hash(const void* __ptr, size_t __clength,
  size_t __seed = static_cast<size_t>(0xc70f6907UL))
    { return _Hash_bytes(__ptr, __clength, __seed); }
    template<typename _Tp>
      static size_t
      hash(const _Tp& __val)
      { return hash(&__val, sizeof(__val)); }
    template<typename _Tp>
      static size_t
      __hash_combine(const _Tp& __val, size_t __hash)
      { return hash(&__val, sizeof(__val), __hash); }
  };
  struct _Fnv_hash_impl
  {
    static size_t
    hash(const void* __ptr, size_t __clength,
  size_t __seed = static_cast<size_t>(2166136261UL))
    { return _Fnv_hash_bytes(__ptr, __clength, __seed); }
    template<typename _Tp>
      static size_t
      hash(const _Tp& __val)
      { return hash(&__val, sizeof(__val)); }
    template<typename _Tp>
      static size_t
      __hash_combine(const _Tp& __val, size_t __hash)
      { return hash(&__val, sizeof(__val), __hash); }
  };
  template<>
    struct hash<float> : public __hash_base<size_t, float>
    {
      size_t
      operator()(float __val) const noexcept
      {
 return __val != 0.0f ? std::_Hash_impl::hash(__val) : 0;
      }
    };
  template<>
    struct hash<double> : public __hash_base<size_t, double>
    {
      size_t
      operator()(double __val) const noexcept
      {
 return __val != 0.0 ? std::_Hash_impl::hash(__val) : 0;
      }
    };
  template<>
    struct hash<long double>
    : public __hash_base<size_t, long double>
    {
      __attribute__ ((__pure__)) size_t
      operator()(long double __val) const noexcept;
    };
  template<typename _Hash>
    struct __is_fast_hash : public std::true_type
    { };
  template<>
    struct __is_fast_hash<hash<long double>> : public std::false_type
    { };

}
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<>
    struct hash<string>
    : public __hash_base<size_t, string>
    {
      size_t
      operator()(const string& __s) const noexcept
      { return std::_Hash_impl::hash(__s.data(), __s.length()); }
    };
  template<>
    struct __is_fast_hash<hash<string>> : std::false_type
    { };
  template<>
    struct hash<wstring>
    : public __hash_base<size_t, wstring>
    {
      size_t
      operator()(const wstring& __s) const noexcept
      { return std::_Hash_impl::hash(__s.data(),
                                     __s.length() * sizeof(wchar_t)); }
    };
  template<>
    struct __is_fast_hash<hash<wstring>> : std::false_type
    { };
  template<>
    struct hash<u16string>
    : public __hash_base<size_t, u16string>
    {
      size_t
      operator()(const u16string& __s) const noexcept
      { return std::_Hash_impl::hash(__s.data(),
                                     __s.length() * sizeof(char16_t)); }
    };
  template<>
    struct __is_fast_hash<hash<u16string>> : std::false_type
    { };
  template<>
    struct hash<u32string>
    : public __hash_base<size_t, u32string>
    {
      size_t
      operator()(const u32string& __s) const noexcept
      { return std::_Hash_impl::hash(__s.data(),
                                     __s.length() * sizeof(char32_t)); }
    };
  template<>
    struct __is_fast_hash<hash<u32string>> : std::false_type
    { };

}
       
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename _CharT, typename _Traits, typename _Alloc>
    const typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    _Rep::_S_max_size = (((npos - sizeof(_Rep_base))/sizeof(_CharT)) - 1) / 4;
  template<typename _CharT, typename _Traits, typename _Alloc>
    const _CharT
    basic_string<_CharT, _Traits, _Alloc>::
    _Rep::_S_terminal = _CharT();
  template<typename _CharT, typename _Traits, typename _Alloc>
    const typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::npos;
  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::_Rep::_S_empty_rep_storage[
    (sizeof(_Rep_base) + sizeof(_CharT) + sizeof(size_type) - 1) /
      sizeof(size_type)];
  template<typename _CharT, typename _Traits, typename _Alloc>
    template<typename _InIterator>
      _CharT*
      basic_string<_CharT, _Traits, _Alloc>::
      _S_construct(_InIterator __beg, _InIterator __end, const _Alloc& __a,
     input_iterator_tag)
      {
 if (__beg == __end && __a == _Alloc())
   return _S_empty_rep()._M_refdata();
 _CharT __buf[128];
 size_type __len = 0;
 while (__beg != __end && __len < sizeof(__buf) / sizeof(_CharT))
   {
     __buf[__len++] = *__beg;
     ++__beg;
   }
 _Rep* __r = _Rep::_S_create(__len, size_type(0), __a);
 _M_copy(__r->_M_refdata(), __buf, __len);
 try
   {
     while (__beg != __end)
       {
  if (__len == __r->_M_capacity)
    {
      _Rep* __another = _Rep::_S_create(__len + 1, __len, __a);
      _M_copy(__another->_M_refdata(), __r->_M_refdata(), __len);
      __r->_M_destroy(__a);
      __r = __another;
    }
  __r->_M_refdata()[__len++] = *__beg;
  ++__beg;
       }
   }
 catch(...)
   {
     __r->_M_destroy(__a);
     throw;
   }
 __r->_M_set_length_and_sharable(__len);
 return __r->_M_refdata();
      }
  template<typename _CharT, typename _Traits, typename _Alloc>
    template <typename _InIterator>
      _CharT*
      basic_string<_CharT, _Traits, _Alloc>::
      _S_construct(_InIterator __beg, _InIterator __end, const _Alloc& __a,
     forward_iterator_tag)
      {
 if (__beg == __end && __a == _Alloc())
   return _S_empty_rep()._M_refdata();
 if (__gnu_cxx::__is_null_pointer(__beg) && __beg != __end)
   __throw_logic_error(("basic_string::_S_construct null not valid"));
 const size_type __dnew = static_cast<size_type>(std::distance(__beg,
              __end));
 _Rep* __r = _Rep::_S_create(__dnew, size_type(0), __a);
 try
   { _S_copy_chars(__r->_M_refdata(), __beg, __end); }
 catch(...)
   {
     __r->_M_destroy(__a);
     throw;
   }
 __r->_M_set_length_and_sharable(__dnew);
 return __r->_M_refdata();
      }
  template<typename _CharT, typename _Traits, typename _Alloc>
    _CharT*
    basic_string<_CharT, _Traits, _Alloc>::
    _S_construct(size_type __n, _CharT __c, const _Alloc& __a)
    {
      if (__n == 0 && __a == _Alloc())
 return _S_empty_rep()._M_refdata();
      _Rep* __r = _Rep::_S_create(__n, size_type(0), __a);
      if (__n)
 _M_assign(__r->_M_refdata(), __n, __c);
      __r->_M_set_length_and_sharable(__n);
      return __r->_M_refdata();
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(const basic_string& __str)
    : _M_dataplus(__str._M_rep()->_M_grab(_Alloc(__str.get_allocator()),
       __str.get_allocator()),
    __str.get_allocator())
    { }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(const _Alloc& __a)
    : _M_dataplus(_S_construct(size_type(), _CharT(), __a), __a)
    { }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(const basic_string& __str, size_type __pos, size_type __n)
    : _M_dataplus(_S_construct(__str._M_data()
          + __str._M_check(__pos,
      "basic_string::basic_string"),
          __str._M_data() + __str._M_limit(__pos, __n)
          + __pos, _Alloc()), _Alloc())
    { }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(const basic_string& __str, size_type __pos,
   size_type __n, const _Alloc& __a)
    : _M_dataplus(_S_construct(__str._M_data()
          + __str._M_check(__pos,
      "basic_string::basic_string"),
          __str._M_data() + __str._M_limit(__pos, __n)
          + __pos, __a), __a)
    { }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(const _CharT* __s, size_type __n, const _Alloc& __a)
    : _M_dataplus(_S_construct(__s, __s + __n, __a), __a)
    { }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(const _CharT* __s, const _Alloc& __a)
    : _M_dataplus(_S_construct(__s, __s ? __s + traits_type::length(__s) :
          __s + npos, __a), __a)
    { }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(size_type __n, _CharT __c, const _Alloc& __a)
    : _M_dataplus(_S_construct(__n, __c, __a), __a)
    { }
  template<typename _CharT, typename _Traits, typename _Alloc>
    template<typename _InputIterator>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(_InputIterator __beg, _InputIterator __end, const _Alloc& __a)
    : _M_dataplus(_S_construct(__beg, __end, __a), __a)
    { }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>::
    basic_string(initializer_list<_CharT> __l, const _Alloc& __a)
    : _M_dataplus(_S_construct(__l.begin(), __l.end(), __a), __a)
    { }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    assign(const basic_string& __str)
    {
      if (_M_rep() != __str._M_rep())
 {
   const allocator_type __a = this->get_allocator();
   _CharT* __tmp = __str._M_rep()->_M_grab(__a, __str.get_allocator());
   _M_rep()->_M_dispose(__a);
   _M_data(__tmp);
 }
      return *this;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    assign(const _CharT* __s, size_type __n)
    {
      ;
      _M_check_length(this->size(), __n, "basic_string::assign");
      if (_M_disjunct(__s) || _M_rep()->_M_is_shared())
 return _M_replace_safe(size_type(0), this->size(), __s, __n);
      else
 {
   const size_type __pos = __s - _M_data();
   if (__pos >= __n)
     _M_copy(_M_data(), __s, __n);
   else if (__pos)
     _M_move(_M_data(), __s, __n);
   _M_rep()->_M_set_length_and_sharable(__n);
   return *this;
 }
     }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    append(size_type __n, _CharT __c)
    {
      if (__n)
 {
   _M_check_length(size_type(0), __n, "basic_string::append");
   const size_type __len = __n + this->size();
   if (__len > this->capacity() || _M_rep()->_M_is_shared())
     this->reserve(__len);
   _M_assign(_M_data() + this->size(), __n, __c);
   _M_rep()->_M_set_length_and_sharable(__len);
 }
      return *this;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    append(const _CharT* __s, size_type __n)
    {
      ;
      if (__n)
 {
   _M_check_length(size_type(0), __n, "basic_string::append");
   const size_type __len = __n + this->size();
   if (__len > this->capacity() || _M_rep()->_M_is_shared())
     {
       if (_M_disjunct(__s))
  this->reserve(__len);
       else
  {
    const size_type __off = __s - _M_data();
    this->reserve(__len);
    __s = _M_data() + __off;
  }
     }
   _M_copy(_M_data() + this->size(), __s, __n);
   _M_rep()->_M_set_length_and_sharable(__len);
 }
      return *this;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    append(const basic_string& __str)
    {
      const size_type __size = __str.size();
      if (__size)
 {
   const size_type __len = __size + this->size();
   if (__len > this->capacity() || _M_rep()->_M_is_shared())
     this->reserve(__len);
   _M_copy(_M_data() + this->size(), __str._M_data(), __size);
   _M_rep()->_M_set_length_and_sharable(__len);
 }
      return *this;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    append(const basic_string& __str, size_type __pos, size_type __n)
    {
      __str._M_check(__pos, "basic_string::append");
      __n = __str._M_limit(__pos, __n);
      if (__n)
 {
   const size_type __len = __n + this->size();
   if (__len > this->capacity() || _M_rep()->_M_is_shared())
     this->reserve(__len);
   _M_copy(_M_data() + this->size(), __str._M_data() + __pos, __n);
   _M_rep()->_M_set_length_and_sharable(__len);
 }
      return *this;
    }
   template<typename _CharT, typename _Traits, typename _Alloc>
     basic_string<_CharT, _Traits, _Alloc>&
     basic_string<_CharT, _Traits, _Alloc>::
     insert(size_type __pos, const _CharT* __s, size_type __n)
     {
       ;
       _M_check(__pos, "basic_string::insert");
       _M_check_length(size_type(0), __n, "basic_string::insert");
       if (_M_disjunct(__s) || _M_rep()->_M_is_shared())
         return _M_replace_safe(__pos, size_type(0), __s, __n);
       else
         {
           const size_type __off = __s - _M_data();
           _M_mutate(__pos, 0, __n);
           __s = _M_data() + __off;
           _CharT* __p = _M_data() + __pos;
           if (__s + __n <= __p)
             _M_copy(__p, __s, __n);
           else if (__s >= __p)
             _M_copy(__p, __s + __n, __n);
           else
             {
        const size_type __nleft = __p - __s;
               _M_copy(__p, __s, __nleft);
               _M_copy(__p + __nleft, __p + __n, __n - __nleft);
             }
           return *this;
         }
     }
   template<typename _CharT, typename _Traits, typename _Alloc>
     typename basic_string<_CharT, _Traits, _Alloc>::iterator
     basic_string<_CharT, _Traits, _Alloc>::
     erase(iterator __first, iterator __last)
     {
       ;
       const size_type __size = __last - __first;
       if (__size)
  {
    const size_type __pos = __first - _M_ibegin();
    _M_mutate(__pos, __size, size_type(0));
    _M_rep()->_M_set_leaked();
    return iterator(_M_data() + __pos);
  }
       else
  return __first;
     }
   template<typename _CharT, typename _Traits, typename _Alloc>
     basic_string<_CharT, _Traits, _Alloc>&
     basic_string<_CharT, _Traits, _Alloc>::
     replace(size_type __pos, size_type __n1, const _CharT* __s,
      size_type __n2)
     {
       ;
       _M_check(__pos, "basic_string::replace");
       __n1 = _M_limit(__pos, __n1);
       _M_check_length(__n1, __n2, "basic_string::replace");
       bool __left;
       if (_M_disjunct(__s) || _M_rep()->_M_is_shared())
         return _M_replace_safe(__pos, __n1, __s, __n2);
       else if ((__left = __s + __n2 <= _M_data() + __pos)
  || _M_data() + __pos + __n1 <= __s)
  {
    size_type __off = __s - _M_data();
    __left ? __off : (__off += __n2 - __n1);
    _M_mutate(__pos, __n1, __n2);
    _M_copy(_M_data() + __pos, _M_data() + __off, __n2);
    return *this;
  }
       else
  {
    const basic_string __tmp(__s, __n2);
    return _M_replace_safe(__pos, __n1, __tmp._M_data(), __n2);
  }
     }
  template<typename _CharT, typename _Traits, typename _Alloc>
    void
    basic_string<_CharT, _Traits, _Alloc>::_Rep::
    _M_destroy(const _Alloc& __a) throw ()
    {
      const size_type __size = sizeof(_Rep_base) +
                        (this->_M_capacity + 1) * sizeof(_CharT);
      _Raw_bytes_alloc(__a).deallocate(reinterpret_cast<char*>(this), __size);
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    void
    basic_string<_CharT, _Traits, _Alloc>::
    _M_leak_hard()
    {
      if (_M_rep() == &_S_empty_rep())
 return;
      if (_M_rep()->_M_is_shared())
 _M_mutate(0, 0, 0);
      _M_rep()->_M_set_leaked();
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    void
    basic_string<_CharT, _Traits, _Alloc>::
    _M_mutate(size_type __pos, size_type __len1, size_type __len2)
    {
      const size_type __old_size = this->size();
      const size_type __new_size = __old_size + __len2 - __len1;
      const size_type __how_much = __old_size - __pos - __len1;
      if (__new_size > this->capacity() || _M_rep()->_M_is_shared())
 {
   const allocator_type __a = get_allocator();
   _Rep* __r = _Rep::_S_create(__new_size, this->capacity(), __a);
   if (__pos)
     _M_copy(__r->_M_refdata(), _M_data(), __pos);
   if (__how_much)
     _M_copy(__r->_M_refdata() + __pos + __len2,
      _M_data() + __pos + __len1, __how_much);
   _M_rep()->_M_dispose(__a);
   _M_data(__r->_M_refdata());
 }
      else if (__how_much && __len1 != __len2)
 {
   _M_move(_M_data() + __pos + __len2,
    _M_data() + __pos + __len1, __how_much);
 }
      _M_rep()->_M_set_length_and_sharable(__new_size);
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    void
    basic_string<_CharT, _Traits, _Alloc>::
    reserve(size_type __res)
    {
      if (__res != this->capacity() || _M_rep()->_M_is_shared())
        {
   if (__res < this->size())
     __res = this->size();
   const allocator_type __a = get_allocator();
   _CharT* __tmp = _M_rep()->_M_clone(__a, __res - this->size());
   _M_rep()->_M_dispose(__a);
   _M_data(__tmp);
        }
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    void
    basic_string<_CharT, _Traits, _Alloc>::
    swap(basic_string& __s)
    {
      if (_M_rep()->_M_is_leaked())
 _M_rep()->_M_set_sharable();
      if (__s._M_rep()->_M_is_leaked())
 __s._M_rep()->_M_set_sharable();
      if (this->get_allocator() == __s.get_allocator())
 {
   _CharT* __tmp = _M_data();
   _M_data(__s._M_data());
   __s._M_data(__tmp);
 }
      else
 {
   const basic_string __tmp1(_M_ibegin(), _M_iend(),
        __s.get_allocator());
   const basic_string __tmp2(__s._M_ibegin(), __s._M_iend(),
        this->get_allocator());
   *this = __tmp2;
   __s = __tmp1;
 }
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::_Rep*
    basic_string<_CharT, _Traits, _Alloc>::_Rep::
    _S_create(size_type __capacity, size_type __old_capacity,
       const _Alloc& __alloc)
    {
      if (__capacity > _S_max_size)
 __throw_length_error(("basic_string::_S_create"));
      const size_type __pagesize = 4096;
      const size_type __malloc_header_size = 4 * sizeof(void*);
      if (__capacity > __old_capacity && __capacity < 2 * __old_capacity)
 __capacity = 2 * __old_capacity;
      size_type __size = (__capacity + 1) * sizeof(_CharT) + sizeof(_Rep);
      const size_type __adj_size = __size + __malloc_header_size;
      if (__adj_size > __pagesize && __capacity > __old_capacity)
 {
   const size_type __extra = __pagesize - __adj_size % __pagesize;
   __capacity += __extra / sizeof(_CharT);
   if (__capacity > _S_max_size)
     __capacity = _S_max_size;
   __size = (__capacity + 1) * sizeof(_CharT) + sizeof(_Rep);
 }
      void* __place = _Raw_bytes_alloc(__alloc).allocate(__size);
      _Rep *__p = new (__place) _Rep;
      __p->_M_capacity = __capacity;
      __p->_M_set_sharable();
      return __p;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    _CharT*
    basic_string<_CharT, _Traits, _Alloc>::_Rep::
    _M_clone(const _Alloc& __alloc, size_type __res)
    {
      const size_type __requested_cap = this->_M_length + __res;
      _Rep* __r = _Rep::_S_create(__requested_cap, this->_M_capacity,
      __alloc);
      if (this->_M_length)
 _M_copy(__r->_M_refdata(), _M_refdata(), this->_M_length);
      __r->_M_set_length_and_sharable(this->_M_length);
      return __r->_M_refdata();
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    void
    basic_string<_CharT, _Traits, _Alloc>::
    resize(size_type __n, _CharT __c)
    {
      const size_type __size = this->size();
      _M_check_length(__size, __n, "basic_string::resize");
      if (__size < __n)
 this->append(__n - __size, __c);
      else if (__n < __size)
 this->erase(__n);
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    template<typename _InputIterator>
      basic_string<_CharT, _Traits, _Alloc>&
      basic_string<_CharT, _Traits, _Alloc>::
      _M_replace_dispatch(iterator __i1, iterator __i2, _InputIterator __k1,
     _InputIterator __k2, __false_type)
      {
 const basic_string __s(__k1, __k2);
 const size_type __n1 = __i2 - __i1;
 _M_check_length(__n1, __s.size(), "basic_string::_M_replace_dispatch");
 return _M_replace_safe(__i1 - _M_ibegin(), __n1, __s._M_data(),
          __s.size());
      }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    _M_replace_aux(size_type __pos1, size_type __n1, size_type __n2,
     _CharT __c)
    {
      _M_check_length(__n1, __n2, "basic_string::_M_replace_aux");
      _M_mutate(__pos1, __n1, __n2);
      if (__n2)
 _M_assign(_M_data() + __pos1, __n2, __c);
      return *this;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>&
    basic_string<_CharT, _Traits, _Alloc>::
    _M_replace_safe(size_type __pos1, size_type __n1, const _CharT* __s,
      size_type __n2)
    {
      _M_mutate(__pos1, __n1, __n2);
      if (__n2)
 _M_copy(_M_data() + __pos1, __s, __n2);
      return *this;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>
    operator+(const _CharT* __lhs,
       const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    {
      ;
      typedef basic_string<_CharT, _Traits, _Alloc> __string_type;
      typedef typename __string_type::size_type __size_type;
      const __size_type __len = _Traits::length(__lhs);
      __string_type __str;
      __str.reserve(__len + __rhs.size());
      __str.append(__lhs, __len);
      __str.append(__rhs);
      return __str;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_string<_CharT, _Traits, _Alloc>
    operator+(_CharT __lhs, const basic_string<_CharT, _Traits, _Alloc>& __rhs)
    {
      typedef basic_string<_CharT, _Traits, _Alloc> __string_type;
      typedef typename __string_type::size_type __size_type;
      __string_type __str;
      const __size_type __len = __rhs.size();
      __str.reserve(__len + 1);
      __str.append(__size_type(1), __lhs);
      __str.append(__rhs);
      return __str;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    copy(_CharT* __s, size_type __n, size_type __pos) const
    {
      _M_check(__pos, "basic_string::copy");
      __n = _M_limit(__pos, __n);
      ;
      if (__n)
 _M_copy(__s, _M_data() + __pos, __n);
      return __n;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find(const _CharT* __s, size_type __pos, size_type __n) const
    {
      ;
      const size_type __size = this->size();
      const _CharT* __data = _M_data();
      if (__n == 0)
 return __pos <= __size ? __pos : npos;
      if (__n <= __size)
 {
   for (; __pos <= __size - __n; ++__pos)
     if (traits_type::eq(__data[__pos], __s[0])
  && traits_type::compare(__data + __pos + 1,
     __s + 1, __n - 1) == 0)
       return __pos;
 }
      return npos;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find(_CharT __c, size_type __pos) const noexcept
    {
      size_type __ret = npos;
      const size_type __size = this->size();
      if (__pos < __size)
 {
   const _CharT* __data = _M_data();
   const size_type __n = __size - __pos;
   const _CharT* __p = traits_type::find(__data + __pos, __n, __c);
   if (__p)
     __ret = __p - __data;
 }
      return __ret;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    rfind(const _CharT* __s, size_type __pos, size_type __n) const
    {
      ;
      const size_type __size = this->size();
      if (__n <= __size)
 {
   __pos = std::min(size_type(__size - __n), __pos);
   const _CharT* __data = _M_data();
   do
     {
       if (traits_type::compare(__data + __pos, __s, __n) == 0)
  return __pos;
     }
   while (__pos-- > 0);
 }
      return npos;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    rfind(_CharT __c, size_type __pos) const noexcept
    {
      size_type __size = this->size();
      if (__size)
 {
   if (--__size > __pos)
     __size = __pos;
   for (++__size; __size-- > 0; )
     if (traits_type::eq(_M_data()[__size], __c))
       return __size;
 }
      return npos;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find_first_of(const _CharT* __s, size_type __pos, size_type __n) const
    {
      ;
      for (; __n && __pos < this->size(); ++__pos)
 {
   const _CharT* __p = traits_type::find(__s, __n, _M_data()[__pos]);
   if (__p)
     return __pos;
 }
      return npos;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find_last_of(const _CharT* __s, size_type __pos, size_type __n) const
    {
      ;
      size_type __size = this->size();
      if (__size && __n)
 {
   if (--__size > __pos)
     __size = __pos;
   do
     {
       if (traits_type::find(__s, __n, _M_data()[__size]))
  return __size;
     }
   while (__size-- != 0);
 }
      return npos;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find_first_not_of(const _CharT* __s, size_type __pos, size_type __n) const
    {
      ;
      for (; __pos < this->size(); ++__pos)
 if (!traits_type::find(__s, __n, _M_data()[__pos]))
   return __pos;
      return npos;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find_first_not_of(_CharT __c, size_type __pos) const noexcept
    {
      for (; __pos < this->size(); ++__pos)
 if (!traits_type::eq(_M_data()[__pos], __c))
   return __pos;
      return npos;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find_last_not_of(const _CharT* __s, size_type __pos, size_type __n) const
    {
      ;
      size_type __size = this->size();
      if (__size)
 {
   if (--__size > __pos)
     __size = __pos;
   do
     {
       if (!traits_type::find(__s, __n, _M_data()[__size]))
  return __size;
     }
   while (__size--);
 }
      return npos;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    typename basic_string<_CharT, _Traits, _Alloc>::size_type
    basic_string<_CharT, _Traits, _Alloc>::
    find_last_not_of(_CharT __c, size_type __pos) const noexcept
    {
      size_type __size = this->size();
      if (__size)
 {
   if (--__size > __pos)
     __size = __pos;
   do
     {
       if (!traits_type::eq(_M_data()[__size], __c))
  return __size;
     }
   while (__size--);
 }
      return npos;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    int
    basic_string<_CharT, _Traits, _Alloc>::
    compare(size_type __pos, size_type __n, const basic_string& __str) const
    {
      _M_check(__pos, "basic_string::compare");
      __n = _M_limit(__pos, __n);
      const size_type __osize = __str.size();
      const size_type __len = std::min(__n, __osize);
      int __r = traits_type::compare(_M_data() + __pos, __str.data(), __len);
      if (!__r)
 __r = _S_compare(__n, __osize);
      return __r;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    int
    basic_string<_CharT, _Traits, _Alloc>::
    compare(size_type __pos1, size_type __n1, const basic_string& __str,
     size_type __pos2, size_type __n2) const
    {
      _M_check(__pos1, "basic_string::compare");
      __str._M_check(__pos2, "basic_string::compare");
      __n1 = _M_limit(__pos1, __n1);
      __n2 = __str._M_limit(__pos2, __n2);
      const size_type __len = std::min(__n1, __n2);
      int __r = traits_type::compare(_M_data() + __pos1,
         __str.data() + __pos2, __len);
      if (!__r)
 __r = _S_compare(__n1, __n2);
      return __r;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    int
    basic_string<_CharT, _Traits, _Alloc>::
    compare(const _CharT* __s) const
    {
      ;
      const size_type __size = this->size();
      const size_type __osize = traits_type::length(__s);
      const size_type __len = std::min(__size, __osize);
      int __r = traits_type::compare(_M_data(), __s, __len);
      if (!__r)
 __r = _S_compare(__size, __osize);
      return __r;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    int
    basic_string <_CharT, _Traits, _Alloc>::
    compare(size_type __pos, size_type __n1, const _CharT* __s) const
    {
      ;
      _M_check(__pos, "basic_string::compare");
      __n1 = _M_limit(__pos, __n1);
      const size_type __osize = traits_type::length(__s);
      const size_type __len = std::min(__n1, __osize);
      int __r = traits_type::compare(_M_data() + __pos, __s, __len);
      if (!__r)
 __r = _S_compare(__n1, __osize);
      return __r;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    int
    basic_string <_CharT, _Traits, _Alloc>::
    compare(size_type __pos, size_type __n1, const _CharT* __s,
     size_type __n2) const
    {
      ;
      _M_check(__pos, "basic_string::compare");
      __n1 = _M_limit(__pos, __n1);
      const size_type __len = std::min(__n1, __n2);
      int __r = traits_type::compare(_M_data() + __pos, __s, __len);
      if (!__r)
 __r = _S_compare(__n1, __n2);
      return __r;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>& __in,
        basic_string<_CharT, _Traits, _Alloc>& __str)
    {
      typedef basic_istream<_CharT, _Traits> __istream_type;
      typedef basic_string<_CharT, _Traits, _Alloc> __string_type;
      typedef typename __istream_type::ios_base __ios_base;
      typedef typename __istream_type::int_type __int_type;
      typedef typename __string_type::size_type __size_type;
      typedef ctype<_CharT> __ctype_type;
      typedef typename __ctype_type::ctype_base __ctype_base;
      __size_type __extracted = 0;
      typename __ios_base::iostate __err = __ios_base::goodbit;
      typename __istream_type::sentry __cerb(__in, false);
      if (__cerb)
 {
   try
     {
       __str.erase();
       _CharT __buf[128];
       __size_type __len = 0;
       const streamsize __w = __in.width();
       const __size_type __n = __w > 0 ? static_cast<__size_type>(__w)
                                : __str.max_size();
       const __ctype_type& __ct = use_facet<__ctype_type>(__in.getloc());
       const __int_type __eof = _Traits::eof();
       __int_type __c = __in.rdbuf()->sgetc();
       while (__extracted < __n
       && !_Traits::eq_int_type(__c, __eof)
       && !__ct.is(__ctype_base::space,
     _Traits::to_char_type(__c)))
  {
    if (__len == sizeof(__buf) / sizeof(_CharT))
      {
        __str.append(__buf, sizeof(__buf) / sizeof(_CharT));
        __len = 0;
      }
    __buf[__len++] = _Traits::to_char_type(__c);
    ++__extracted;
    __c = __in.rdbuf()->snextc();
  }
       __str.append(__buf, __len);
       if (_Traits::eq_int_type(__c, __eof))
  __err |= __ios_base::eofbit;
       __in.width(0);
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       __in._M_setstate(__ios_base::badbit);
       throw;
     }
   catch(...)
     {
       __in._M_setstate(__ios_base::badbit);
     }
 }
      if (!__extracted)
 __err |= __ios_base::failbit;
      if (__err)
 __in.setstate(__err);
      return __in;
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    basic_istream<_CharT, _Traits>&
    getline(basic_istream<_CharT, _Traits>& __in,
     basic_string<_CharT, _Traits, _Alloc>& __str, _CharT __delim)
    {
      typedef basic_istream<_CharT, _Traits> __istream_type;
      typedef basic_string<_CharT, _Traits, _Alloc> __string_type;
      typedef typename __istream_type::ios_base __ios_base;
      typedef typename __istream_type::int_type __int_type;
      typedef typename __string_type::size_type __size_type;
      __size_type __extracted = 0;
      const __size_type __n = __str.max_size();
      typename __ios_base::iostate __err = __ios_base::goodbit;
      typename __istream_type::sentry __cerb(__in, true);
      if (__cerb)
 {
   try
     {
       __str.erase();
       const __int_type __idelim = _Traits::to_int_type(__delim);
       const __int_type __eof = _Traits::eof();
       __int_type __c = __in.rdbuf()->sgetc();
       while (__extracted < __n
       && !_Traits::eq_int_type(__c, __eof)
       && !_Traits::eq_int_type(__c, __idelim))
  {
    __str += _Traits::to_char_type(__c);
    ++__extracted;
    __c = __in.rdbuf()->snextc();
  }
       if (_Traits::eq_int_type(__c, __eof))
  __err |= __ios_base::eofbit;
       else if (_Traits::eq_int_type(__c, __idelim))
  {
    ++__extracted;
    __in.rdbuf()->sbumpc();
  }
       else
  __err |= __ios_base::failbit;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       __in._M_setstate(__ios_base::badbit);
       throw;
     }
   catch(...)
     {
       __in._M_setstate(__ios_base::badbit);
     }
 }
      if (!__extracted)
 __err |= __ios_base::failbit;
      if (__err)
 __in.setstate(__err);
      return __in;
    }
  extern template class basic_string<char>;
  extern template
    basic_istream<char>&
    operator>>(basic_istream<char>&, string&);
  extern template
    basic_ostream<char>&
    operator<<(basic_ostream<char>&, const string&);
  extern template
    basic_istream<char>&
    getline(basic_istream<char>&, string&, char);
  extern template
    basic_istream<char>&
    getline(basic_istream<char>&, string&);
  extern template class basic_string<wchar_t>;
  extern template
    basic_istream<wchar_t>&
    operator>>(basic_istream<wchar_t>&, wstring&);
  extern template
    basic_ostream<wchar_t>&
    operator<<(basic_ostream<wchar_t>&, const wstring&);
  extern template
    basic_istream<wchar_t>&
    getline(basic_istream<wchar_t>&, wstring&, wchar_t);
  extern template
    basic_istream<wchar_t>&
    getline(basic_istream<wchar_t>&, wstring&);

}
       
       
       
       
       
namespace std __attribute__ ((__visibility__ ("default")))
{

  class locale
  {
  public:
    typedef int category;
    class facet;
    class id;
    class _Impl;
    friend class facet;
    friend class _Impl;
    template<typename _Facet>
      friend bool
      has_facet(const locale&) throw();
    template<typename _Facet>
      friend const _Facet&
      use_facet(const locale&);
    template<typename _Cache>
      friend struct __use_cache;
    static const category none = 0;
    static const category ctype = 1L << 0;
    static const category numeric = 1L << 1;
    static const category collate = 1L << 2;
    static const category time = 1L << 3;
    static const category monetary = 1L << 4;
    static const category messages = 1L << 5;
    static const category all = (ctype | numeric | collate |
        time | monetary | messages);
    locale() throw();
    locale(const locale& __other) throw();
    explicit
    locale(const char* __s);
    locale(const locale& __base, const char* __s, category __cat);
    locale(const locale& __base, const locale& __add, category __cat);
    template<typename _Facet>
      locale(const locale& __other, _Facet* __f);
    ~locale() throw();
    const locale&
    operator=(const locale& __other) throw();
    template<typename _Facet>
      locale
      combine(const locale& __other) const;
    string
    name() const;
    bool
    operator==(const locale& __other) const throw();
    bool
    operator!=(const locale& __other) const throw()
    { return !(this->operator==(__other)); }
    template<typename _Char, typename _Traits, typename _Alloc>
      bool
      operator()(const basic_string<_Char, _Traits, _Alloc>& __s1,
   const basic_string<_Char, _Traits, _Alloc>& __s2) const;
    static locale
    global(const locale& __loc);
    static const locale&
    classic();
  private:
    _Impl* _M_impl;
    static _Impl* _S_classic;
    static _Impl* _S_global;
    static const char* const* const _S_categories;
    enum { _S_categories_size = 6 + 6 };
    static __gthread_once_t _S_once;
    explicit
    locale(_Impl*) throw();
    static void
    _S_initialize();
    static void
    _S_initialize_once() throw();
    static category
    _S_normalize_category(category);
    void
    _M_coalesce(const locale& __base, const locale& __add, category __cat);
  };
  class locale::facet
  {
  private:
    friend class locale;
    friend class locale::_Impl;
    mutable _Atomic_word _M_refcount;
    static __c_locale _S_c_locale;
    static const char _S_c_name[2];
    static __gthread_once_t _S_once;
    static void
    _S_initialize_once();
  protected:
    explicit
    facet(size_t __refs = 0) throw() : _M_refcount(__refs ? 1 : 0)
    { }
    virtual
    ~facet();
    static void
    _S_create_c_locale(__c_locale& __cloc, const char* __s,
         __c_locale __old = 0);
    static __c_locale
    _S_clone_c_locale(__c_locale& __cloc) throw();
    static void
    _S_destroy_c_locale(__c_locale& __cloc);
    static __c_locale
    _S_lc_ctype_c_locale(__c_locale __cloc, const char* __s);
    static __c_locale
    _S_get_c_locale();
    __attribute__ ((__const__)) static const char*
    _S_get_c_name() throw();
  private:
    void
    _M_add_reference() const throw()
    { __gnu_cxx::__atomic_add_dispatch(&_M_refcount, 1); }
    void
    _M_remove_reference() const throw()
    {
      ;
      if (__gnu_cxx::__exchange_and_add_dispatch(&_M_refcount, -1) == 1)
 {
          ;
   try
     { delete this; }
   catch(...)
     { }
 }
    }
    facet(const facet&);
    facet&
    operator=(const facet&);
  };
  class locale::id
  {
  private:
    friend class locale;
    friend class locale::_Impl;
    template<typename _Facet>
      friend const _Facet&
      use_facet(const locale&);
    template<typename _Facet>
      friend bool
      has_facet(const locale&) throw();
    mutable size_t _M_index;
    static _Atomic_word _S_refcount;
    void
    operator=(const id&);
    id(const id&);
  public:
    id() { }
    size_t
    _M_id() const throw();
  };
  class locale::_Impl
  {
  public:
    friend class locale;
    friend class locale::facet;
    template<typename _Facet>
      friend bool
      has_facet(const locale&) throw();
    template<typename _Facet>
      friend const _Facet&
      use_facet(const locale&);
    template<typename _Cache>
      friend struct __use_cache;
  private:
    _Atomic_word _M_refcount;
    const facet** _M_facets;
    size_t _M_facets_size;
    const facet** _M_caches;
    char** _M_names;
    static const locale::id* const _S_id_ctype[];
    static const locale::id* const _S_id_numeric[];
    static const locale::id* const _S_id_collate[];
    static const locale::id* const _S_id_time[];
    static const locale::id* const _S_id_monetary[];
    static const locale::id* const _S_id_messages[];
    static const locale::id* const* const _S_facet_categories[];
    void
    _M_add_reference() throw()
    { __gnu_cxx::__atomic_add_dispatch(&_M_refcount, 1); }
    void
    _M_remove_reference() throw()
    {
      ;
      if (__gnu_cxx::__exchange_and_add_dispatch(&_M_refcount, -1) == 1)
 {
          ;
   try
     { delete this; }
   catch(...)
     { }
 }
    }
    _Impl(const _Impl&, size_t);
    _Impl(const char*, size_t);
    _Impl(size_t) throw();
   ~_Impl() throw();
    _Impl(const _Impl&);
    void
    operator=(const _Impl&);
    bool
    _M_check_same_name()
    {
      bool __ret = true;
      if (_M_names[1])
 for (size_t __i = 0; __ret && __i < _S_categories_size - 1; ++__i)
   __ret = __builtin_strcmp(_M_names[__i], _M_names[__i + 1]) == 0;
      return __ret;
    }
    void
    _M_replace_categories(const _Impl*, category);
    void
    _M_replace_category(const _Impl*, const locale::id* const*);
    void
    _M_replace_facet(const _Impl*, const locale::id*);
    void
    _M_install_facet(const locale::id*, const facet*);
    template<typename _Facet>
      void
      _M_init_facet(_Facet* __facet)
      { _M_install_facet(&_Facet::id, __facet); }
    void
    _M_install_cache(const facet*, size_t);
  };
  template<typename _CharT>
    class collate : public locale::facet
    {
    public:
      typedef _CharT char_type;
      typedef basic_string<_CharT> string_type;
    protected:
      __c_locale _M_c_locale_collate;
    public:
      static locale::id id;
      explicit
      collate(size_t __refs = 0)
      : facet(__refs), _M_c_locale_collate(_S_get_c_locale())
      { }
      explicit
      collate(__c_locale __cloc, size_t __refs = 0)
      : facet(__refs), _M_c_locale_collate(_S_clone_c_locale(__cloc))
      { }
      int
      compare(const _CharT* __lo1, const _CharT* __hi1,
       const _CharT* __lo2, const _CharT* __hi2) const
      { return this->do_compare(__lo1, __hi1, __lo2, __hi2); }
      string_type
      transform(const _CharT* __lo, const _CharT* __hi) const
      { return this->do_transform(__lo, __hi); }
      long
      hash(const _CharT* __lo, const _CharT* __hi) const
      { return this->do_hash(__lo, __hi); }
      int
      _M_compare(const _CharT*, const _CharT*) const throw();
      size_t
      _M_transform(_CharT*, const _CharT*, size_t) const throw();
  protected:
      virtual
      ~collate()
      { _S_destroy_c_locale(_M_c_locale_collate); }
      virtual int
      do_compare(const _CharT* __lo1, const _CharT* __hi1,
   const _CharT* __lo2, const _CharT* __hi2) const;
      virtual string_type
      do_transform(const _CharT* __lo, const _CharT* __hi) const;
      virtual long
      do_hash(const _CharT* __lo, const _CharT* __hi) const;
    };
  template<typename _CharT>
    locale::id collate<_CharT>::id;
  template<>
    int
    collate<char>::_M_compare(const char*, const char*) const throw();
  template<>
    size_t
    collate<char>::_M_transform(char*, const char*, size_t) const throw();
  template<>
    int
    collate<wchar_t>::_M_compare(const wchar_t*, const wchar_t*) const throw();
  template<>
    size_t
    collate<wchar_t>::_M_transform(wchar_t*, const wchar_t*, size_t) const throw();
  template<typename _CharT>
    class collate_byname : public collate<_CharT>
    {
    public:
      typedef _CharT char_type;
      typedef basic_string<_CharT> string_type;
      explicit
      collate_byname(const char* __s, size_t __refs = 0)
      : collate<_CharT>(__refs)
      {
 if (__builtin_strcmp(__s, "C") != 0
     && __builtin_strcmp(__s, "POSIX") != 0)
   {
     this->_S_destroy_c_locale(this->_M_c_locale_collate);
     this->_S_create_c_locale(this->_M_c_locale_collate, __s);
   }
      }
    protected:
      virtual
      ~collate_byname() { }
    };

}
       
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename _Facet>
    locale::
    locale(const locale& __other, _Facet* __f)
    {
      _M_impl = new _Impl(*__other._M_impl, 1);
      try
 { _M_impl->_M_install_facet(&_Facet::id, __f); }
      catch(...)
 {
   _M_impl->_M_remove_reference();
   throw;
 }
      delete [] _M_impl->_M_names[0];
      _M_impl->_M_names[0] = 0;
    }
  template<typename _Facet>
    locale
    locale::
    combine(const locale& __other) const
    {
      _Impl* __tmp = new _Impl(*_M_impl, 1);
      try
 {
   __tmp->_M_replace_facet(__other._M_impl, &_Facet::id);
 }
      catch(...)
 {
   __tmp->_M_remove_reference();
   throw;
 }
      return locale(__tmp);
    }
  template<typename _CharT, typename _Traits, typename _Alloc>
    bool
    locale::
    operator()(const basic_string<_CharT, _Traits, _Alloc>& __s1,
        const basic_string<_CharT, _Traits, _Alloc>& __s2) const
    {
      typedef std::collate<_CharT> __collate_type;
      const __collate_type& __collate = use_facet<__collate_type>(*this);
      return (__collate.compare(__s1.data(), __s1.data() + __s1.length(),
    __s2.data(), __s2.data() + __s2.length()) < 0);
    }
  template<typename _Facet>
    bool
    has_facet(const locale& __loc) throw()
    {
      const size_t __i = _Facet::id._M_id();
      const locale::facet** __facets = __loc._M_impl->_M_facets;
      return (__i < __loc._M_impl->_M_facets_size
       && dynamic_cast<const _Facet*>(__facets[__i]));
    }
  template<typename _Facet>
    const _Facet&
    use_facet(const locale& __loc)
    {
      const size_t __i = _Facet::id._M_id();
      const locale::facet** __facets = __loc._M_impl->_M_facets;
      if (__i >= __loc._M_impl->_M_facets_size || !__facets[__i])
        __throw_bad_cast();
      return dynamic_cast<const _Facet&>(*__facets[__i]);
    }
  template<typename _CharT>
    int
    collate<_CharT>::_M_compare(const _CharT*, const _CharT*) const throw ()
    { return 0; }
  template<typename _CharT>
    size_t
    collate<_CharT>::_M_transform(_CharT*, const _CharT*, size_t) const throw ()
    { return 0; }
  template<typename _CharT>
    int
    collate<_CharT>::
    do_compare(const _CharT* __lo1, const _CharT* __hi1,
        const _CharT* __lo2, const _CharT* __hi2) const
    {
      const string_type __one(__lo1, __hi1);
      const string_type __two(__lo2, __hi2);
      const _CharT* __p = __one.c_str();
      const _CharT* __pend = __one.data() + __one.length();
      const _CharT* __q = __two.c_str();
      const _CharT* __qend = __two.data() + __two.length();
      for (;;)
 {
   const int __res = _M_compare(__p, __q);
   if (__res)
     return __res;
   __p += char_traits<_CharT>::length(__p);
   __q += char_traits<_CharT>::length(__q);
   if (__p == __pend && __q == __qend)
     return 0;
   else if (__p == __pend)
     return -1;
   else if (__q == __qend)
     return 1;
   __p++;
   __q++;
 }
    }
  template<typename _CharT>
    typename collate<_CharT>::string_type
    collate<_CharT>::
    do_transform(const _CharT* __lo, const _CharT* __hi) const
    {
      string_type __ret;
      const string_type __str(__lo, __hi);
      const _CharT* __p = __str.c_str();
      const _CharT* __pend = __str.data() + __str.length();
      size_t __len = (__hi - __lo) * 2;
      _CharT* __c = new _CharT[__len];
      try
 {
   for (;;)
     {
       size_t __res = _M_transform(__c, __p, __len);
       if (__res >= __len)
  {
    __len = __res + 1;
    delete [] __c, __c = 0;
    __c = new _CharT[__len];
    __res = _M_transform(__c, __p, __len);
  }
       __ret.append(__c, __res);
       __p += char_traits<_CharT>::length(__p);
       if (__p == __pend)
  break;
       __p++;
       __ret.push_back(_CharT());
     }
 }
      catch(...)
 {
   delete [] __c;
   throw;
 }
      delete [] __c;
      return __ret;
    }
  template<typename _CharT>
    long
    collate<_CharT>::
    do_hash(const _CharT* __lo, const _CharT* __hi) const
    {
      unsigned long __val = 0;
      for (; __lo < __hi; ++__lo)
 __val =
   *__lo + ((__val << 7)
     | (__val >> (__gnu_cxx::__numeric_traits<unsigned long>::
    __digits - 7)));
      return static_cast<long>(__val);
    }
  extern template class collate<char>;
  extern template class collate_byname<char>;
  extern template
    const collate<char>&
    use_facet<collate<char> >(const locale&);
  extern template
    bool
    has_facet<collate<char> >(const locale&);
  extern template class collate<wchar_t>;
  extern template class collate_byname<wchar_t>;
  extern template
    const collate<wchar_t>&
    use_facet<collate<wchar_t> >(const locale&);
  extern template
    bool
    has_facet<collate<wchar_t> >(const locale&);

}
namespace std __attribute__ ((__visibility__ ("default")))
{

  enum _Ios_Fmtflags
    {
      _S_boolalpha = 1L << 0,
      _S_dec = 1L << 1,
      _S_fixed = 1L << 2,
      _S_hex = 1L << 3,
      _S_internal = 1L << 4,
      _S_left = 1L << 5,
      _S_oct = 1L << 6,
      _S_right = 1L << 7,
      _S_scientific = 1L << 8,
      _S_showbase = 1L << 9,
      _S_showpoint = 1L << 10,
      _S_showpos = 1L << 11,
      _S_skipws = 1L << 12,
      _S_unitbuf = 1L << 13,
      _S_uppercase = 1L << 14,
      _S_adjustfield = _S_left | _S_right | _S_internal,
      _S_basefield = _S_dec | _S_oct | _S_hex,
      _S_floatfield = _S_scientific | _S_fixed,
      _S_ios_fmtflags_end = 1L << 16
    };
  inline constexpr _Ios_Fmtflags
  operator&(_Ios_Fmtflags __a, _Ios_Fmtflags __b)
  { return _Ios_Fmtflags(static_cast<int>(__a) & static_cast<int>(__b)); }
  inline constexpr _Ios_Fmtflags
  operator|(_Ios_Fmtflags __a, _Ios_Fmtflags __b)
  { return _Ios_Fmtflags(static_cast<int>(__a) | static_cast<int>(__b)); }
  inline constexpr _Ios_Fmtflags
  operator^(_Ios_Fmtflags __a, _Ios_Fmtflags __b)
  { return _Ios_Fmtflags(static_cast<int>(__a) ^ static_cast<int>(__b)); }
  inline constexpr _Ios_Fmtflags
  operator~(_Ios_Fmtflags __a)
  { return _Ios_Fmtflags(~static_cast<int>(__a)); }
  inline const _Ios_Fmtflags&
  operator|=(_Ios_Fmtflags& __a, _Ios_Fmtflags __b)
  { return __a = __a | __b; }
  inline const _Ios_Fmtflags&
  operator&=(_Ios_Fmtflags& __a, _Ios_Fmtflags __b)
  { return __a = __a & __b; }
  inline const _Ios_Fmtflags&
  operator^=(_Ios_Fmtflags& __a, _Ios_Fmtflags __b)
  { return __a = __a ^ __b; }
  enum _Ios_Openmode
    {
      _S_app = 1L << 0,
      _S_ate = 1L << 1,
      _S_bin = 1L << 2,
      _S_in = 1L << 3,
      _S_out = 1L << 4,
      _S_trunc = 1L << 5,
      _S_ios_openmode_end = 1L << 16
    };
  inline constexpr _Ios_Openmode
  operator&(_Ios_Openmode __a, _Ios_Openmode __b)
  { return _Ios_Openmode(static_cast<int>(__a) & static_cast<int>(__b)); }
  inline constexpr _Ios_Openmode
  operator|(_Ios_Openmode __a, _Ios_Openmode __b)
  { return _Ios_Openmode(static_cast<int>(__a) | static_cast<int>(__b)); }
  inline constexpr _Ios_Openmode
  operator^(_Ios_Openmode __a, _Ios_Openmode __b)
  { return _Ios_Openmode(static_cast<int>(__a) ^ static_cast<int>(__b)); }
  inline constexpr _Ios_Openmode
  operator~(_Ios_Openmode __a)
  { return _Ios_Openmode(~static_cast<int>(__a)); }
  inline const _Ios_Openmode&
  operator|=(_Ios_Openmode& __a, _Ios_Openmode __b)
  { return __a = __a | __b; }
  inline const _Ios_Openmode&
  operator&=(_Ios_Openmode& __a, _Ios_Openmode __b)
  { return __a = __a & __b; }
  inline const _Ios_Openmode&
  operator^=(_Ios_Openmode& __a, _Ios_Openmode __b)
  { return __a = __a ^ __b; }
  enum _Ios_Iostate
    {
      _S_goodbit = 0,
      _S_badbit = 1L << 0,
      _S_eofbit = 1L << 1,
      _S_failbit = 1L << 2,
      _S_ios_iostate_end = 1L << 16
    };
  inline constexpr _Ios_Iostate
  operator&(_Ios_Iostate __a, _Ios_Iostate __b)
  { return _Ios_Iostate(static_cast<int>(__a) & static_cast<int>(__b)); }
  inline constexpr _Ios_Iostate
  operator|(_Ios_Iostate __a, _Ios_Iostate __b)
  { return _Ios_Iostate(static_cast<int>(__a) | static_cast<int>(__b)); }
  inline constexpr _Ios_Iostate
  operator^(_Ios_Iostate __a, _Ios_Iostate __b)
  { return _Ios_Iostate(static_cast<int>(__a) ^ static_cast<int>(__b)); }
  inline constexpr _Ios_Iostate
  operator~(_Ios_Iostate __a)
  { return _Ios_Iostate(~static_cast<int>(__a)); }
  inline const _Ios_Iostate&
  operator|=(_Ios_Iostate& __a, _Ios_Iostate __b)
  { return __a = __a | __b; }
  inline const _Ios_Iostate&
  operator&=(_Ios_Iostate& __a, _Ios_Iostate __b)
  { return __a = __a & __b; }
  inline const _Ios_Iostate&
  operator^=(_Ios_Iostate& __a, _Ios_Iostate __b)
  { return __a = __a ^ __b; }
  enum _Ios_Seekdir
    {
      _S_beg = 0,
      _S_cur = 1,
      _S_end = 2,
      _S_ios_seekdir_end = 1L << 16
    };
  class ios_base
  {
  public:
    class failure : public exception
    {
    public:
      explicit
      failure(const string& __str) throw();
      virtual
      ~failure() throw();
      virtual const char*
      what() const throw();
    private:
      string _M_msg;
    };
    typedef _Ios_Fmtflags fmtflags;
    static const fmtflags boolalpha = _S_boolalpha;
    static const fmtflags dec = _S_dec;
    static const fmtflags fixed = _S_fixed;
    static const fmtflags hex = _S_hex;
    static const fmtflags internal = _S_internal;
    static const fmtflags left = _S_left;
    static const fmtflags oct = _S_oct;
    static const fmtflags right = _S_right;
    static const fmtflags scientific = _S_scientific;
    static const fmtflags showbase = _S_showbase;
    static const fmtflags showpoint = _S_showpoint;
    static const fmtflags showpos = _S_showpos;
    static const fmtflags skipws = _S_skipws;
    static const fmtflags unitbuf = _S_unitbuf;
    static const fmtflags uppercase = _S_uppercase;
    static const fmtflags adjustfield = _S_adjustfield;
    static const fmtflags basefield = _S_basefield;
    static const fmtflags floatfield = _S_floatfield;
    typedef _Ios_Iostate iostate;
    static const iostate badbit = _S_badbit;
    static const iostate eofbit = _S_eofbit;
    static const iostate failbit = _S_failbit;
    static const iostate goodbit = _S_goodbit;
    typedef _Ios_Openmode openmode;
    static const openmode app = _S_app;
    static const openmode ate = _S_ate;
    static const openmode binary = _S_bin;
    static const openmode in = _S_in;
    static const openmode out = _S_out;
    static const openmode trunc = _S_trunc;
    typedef _Ios_Seekdir seekdir;
    static const seekdir beg = _S_beg;
    static const seekdir cur = _S_cur;
    static const seekdir end = _S_end;
    typedef int io_state;
    typedef int open_mode;
    typedef int seek_dir;
    typedef std::streampos streampos;
    typedef std::streamoff streamoff;
    enum event
    {
      erase_event,
      imbue_event,
      copyfmt_event
    };
    typedef void (*event_callback) (event __e, ios_base& __b, int __i);
    void
    register_callback(event_callback __fn, int __index);
  protected:
    streamsize _M_precision;
    streamsize _M_width;
    fmtflags _M_flags;
    iostate _M_exception;
    iostate _M_streambuf_state;
    struct _Callback_list
    {
      _Callback_list* _M_next;
      ios_base::event_callback _M_fn;
      int _M_index;
      _Atomic_word _M_refcount;
      _Callback_list(ios_base::event_callback __fn, int __index,
       _Callback_list* __cb)
      : _M_next(__cb), _M_fn(__fn), _M_index(__index), _M_refcount(0) { }
      void
      _M_add_reference() { __gnu_cxx::__atomic_add_dispatch(&_M_refcount, 1); }
      int
      _M_remove_reference()
      {
        ;
        int __res = __gnu_cxx::__exchange_and_add_dispatch(&_M_refcount, -1);
        if (__res == 0)
          {
            ;
          }
        return __res;
      }
    };
     _Callback_list* _M_callbacks;
    void
    _M_call_callbacks(event __ev) throw();
    void
    _M_dispose_callbacks(void) throw();
    struct _Words
    {
      void* _M_pword;
      long _M_iword;
      _Words() : _M_pword(0), _M_iword(0) { }
    };
    _Words _M_word_zero;
    enum { _S_local_word_size = 8 };
    _Words _M_local_word[_S_local_word_size];
    int _M_word_size;
    _Words* _M_word;
    _Words&
    _M_grow_words(int __index, bool __iword);
    locale _M_ios_locale;
    void
    _M_init() throw();
  public:
    class Init
    {
      friend class ios_base;
    public:
      Init();
      ~Init();
    private:
      static _Atomic_word _S_refcount;
      static bool _S_synced_with_stdio;
    };
    fmtflags
    flags() const
    { return _M_flags; }
    fmtflags
    flags(fmtflags __fmtfl)
    {
      fmtflags __old = _M_flags;
      _M_flags = __fmtfl;
      return __old;
    }
    fmtflags
    setf(fmtflags __fmtfl)
    {
      fmtflags __old = _M_flags;
      _M_flags |= __fmtfl;
      return __old;
    }
    fmtflags
    setf(fmtflags __fmtfl, fmtflags __mask)
    {
      fmtflags __old = _M_flags;
      _M_flags &= ~__mask;
      _M_flags |= (__fmtfl & __mask);
      return __old;
    }
    void
    unsetf(fmtflags __mask)
    { _M_flags &= ~__mask; }
    streamsize
    precision() const
    { return _M_precision; }
    streamsize
    precision(streamsize __prec)
    {
      streamsize __old = _M_precision;
      _M_precision = __prec;
      return __old;
    }
    streamsize
    width() const
    { return _M_width; }
    streamsize
    width(streamsize __wide)
    {
      streamsize __old = _M_width;
      _M_width = __wide;
      return __old;
    }
    static bool
    sync_with_stdio(bool __sync = true);
    locale
    imbue(const locale& __loc) throw();
    locale
    getloc() const
    { return _M_ios_locale; }
    const locale&
    _M_getloc() const
    { return _M_ios_locale; }
    static int
    xalloc() throw();
    long&
    iword(int __ix)
    {
      _Words& __word = (__ix < _M_word_size)
   ? _M_word[__ix] : _M_grow_words(__ix, true);
      return __word._M_iword;
    }
    void*&
    pword(int __ix)
    {
      _Words& __word = (__ix < _M_word_size)
   ? _M_word[__ix] : _M_grow_words(__ix, false);
      return __word._M_pword;
    }
    virtual ~ios_base();
  protected:
    ios_base() throw ();
  private:
    ios_base(const ios_base&);
    ios_base&
    operator=(const ios_base&);
  };
  inline ios_base&
  boolalpha(ios_base& __base)
  {
    __base.setf(ios_base::boolalpha);
    return __base;
  }
  inline ios_base&
  noboolalpha(ios_base& __base)
  {
    __base.unsetf(ios_base::boolalpha);
    return __base;
  }
  inline ios_base&
  showbase(ios_base& __base)
  {
    __base.setf(ios_base::showbase);
    return __base;
  }
  inline ios_base&
  noshowbase(ios_base& __base)
  {
    __base.unsetf(ios_base::showbase);
    return __base;
  }
  inline ios_base&
  showpoint(ios_base& __base)
  {
    __base.setf(ios_base::showpoint);
    return __base;
  }
  inline ios_base&
  noshowpoint(ios_base& __base)
  {
    __base.unsetf(ios_base::showpoint);
    return __base;
  }
  inline ios_base&
  showpos(ios_base& __base)
  {
    __base.setf(ios_base::showpos);
    return __base;
  }
  inline ios_base&
  noshowpos(ios_base& __base)
  {
    __base.unsetf(ios_base::showpos);
    return __base;
  }
  inline ios_base&
  skipws(ios_base& __base)
  {
    __base.setf(ios_base::skipws);
    return __base;
  }
  inline ios_base&
  noskipws(ios_base& __base)
  {
    __base.unsetf(ios_base::skipws);
    return __base;
  }
  inline ios_base&
  uppercase(ios_base& __base)
  {
    __base.setf(ios_base::uppercase);
    return __base;
  }
  inline ios_base&
  nouppercase(ios_base& __base)
  {
    __base.unsetf(ios_base::uppercase);
    return __base;
  }
  inline ios_base&
  unitbuf(ios_base& __base)
  {
     __base.setf(ios_base::unitbuf);
     return __base;
  }
  inline ios_base&
  nounitbuf(ios_base& __base)
  {
     __base.unsetf(ios_base::unitbuf);
     return __base;
  }
  inline ios_base&
  internal(ios_base& __base)
  {
     __base.setf(ios_base::internal, ios_base::adjustfield);
     return __base;
  }
  inline ios_base&
  left(ios_base& __base)
  {
    __base.setf(ios_base::left, ios_base::adjustfield);
    return __base;
  }
  inline ios_base&
  right(ios_base& __base)
  {
    __base.setf(ios_base::right, ios_base::adjustfield);
    return __base;
  }
  inline ios_base&
  dec(ios_base& __base)
  {
    __base.setf(ios_base::dec, ios_base::basefield);
    return __base;
  }
  inline ios_base&
  hex(ios_base& __base)
  {
    __base.setf(ios_base::hex, ios_base::basefield);
    return __base;
  }
  inline ios_base&
  oct(ios_base& __base)
  {
    __base.setf(ios_base::oct, ios_base::basefield);
    return __base;
  }
  inline ios_base&
  fixed(ios_base& __base)
  {
    __base.setf(ios_base::fixed, ios_base::floatfield);
    return __base;
  }
  inline ios_base&
  scientific(ios_base& __base)
  {
    __base.setf(ios_base::scientific, ios_base::floatfield);
    return __base;
  }

}
       
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename _CharT, typename _Traits>
    streamsize
    __copy_streambufs_eof(basic_streambuf<_CharT, _Traits>*,
     basic_streambuf<_CharT, _Traits>*, bool&);
  template<typename _CharT, typename _Traits>
    class basic_streambuf
    {
    public:
      typedef _CharT char_type;
      typedef _Traits traits_type;
      typedef typename traits_type::int_type int_type;
      typedef typename traits_type::pos_type pos_type;
      typedef typename traits_type::off_type off_type;
      typedef basic_streambuf<char_type, traits_type> __streambuf_type;
      friend class basic_ios<char_type, traits_type>;
      friend class basic_istream<char_type, traits_type>;
      friend class basic_ostream<char_type, traits_type>;
      friend class istreambuf_iterator<char_type, traits_type>;
      friend class ostreambuf_iterator<char_type, traits_type>;
      friend streamsize
      __copy_streambufs_eof<>(basic_streambuf*, basic_streambuf*, bool&);
      template<bool _IsMove, typename _CharT2>
        friend typename __gnu_cxx::__enable_if<__is_char<_CharT2>::__value,
            _CharT2*>::__type
        __copy_move_a2(istreambuf_iterator<_CharT2>,
         istreambuf_iterator<_CharT2>, _CharT2*);
      template<typename _CharT2>
        friend typename __gnu_cxx::__enable_if<__is_char<_CharT2>::__value,
      istreambuf_iterator<_CharT2> >::__type
        find(istreambuf_iterator<_CharT2>, istreambuf_iterator<_CharT2>,
      const _CharT2&);
      template<typename _CharT2, typename _Traits2>
        friend basic_istream<_CharT2, _Traits2>&
        operator>>(basic_istream<_CharT2, _Traits2>&, _CharT2*);
      template<typename _CharT2, typename _Traits2, typename _Alloc>
        friend basic_istream<_CharT2, _Traits2>&
        operator>>(basic_istream<_CharT2, _Traits2>&,
     basic_string<_CharT2, _Traits2, _Alloc>&);
      template<typename _CharT2, typename _Traits2, typename _Alloc>
        friend basic_istream<_CharT2, _Traits2>&
        getline(basic_istream<_CharT2, _Traits2>&,
  basic_string<_CharT2, _Traits2, _Alloc>&, _CharT2);
    protected:
      char_type* _M_in_beg;
      char_type* _M_in_cur;
      char_type* _M_in_end;
      char_type* _M_out_beg;
      char_type* _M_out_cur;
      char_type* _M_out_end;
      locale _M_buf_locale;
  public:
      virtual
      ~basic_streambuf()
      { }
      locale
      pubimbue(const locale& __loc)
      {
 locale __tmp(this->getloc());
 this->imbue(__loc);
 _M_buf_locale = __loc;
 return __tmp;
      }
      locale
      getloc() const
      { return _M_buf_locale; }
      basic_streambuf*
      pubsetbuf(char_type* __s, streamsize __n)
      { return this->setbuf(__s, __n); }
      pos_type
      pubseekoff(off_type __off, ios_base::seekdir __way,
   ios_base::openmode __mode = ios_base::in | ios_base::out)
      { return this->seekoff(__off, __way, __mode); }
      pos_type
      pubseekpos(pos_type __sp,
   ios_base::openmode __mode = ios_base::in | ios_base::out)
      { return this->seekpos(__sp, __mode); }
      int
      pubsync() { return this->sync(); }
      streamsize
      in_avail()
      {
 const streamsize __ret = this->egptr() - this->gptr();
 return __ret ? __ret : this->showmanyc();
      }
      int_type
      snextc()
      {
 int_type __ret = traits_type::eof();
 if (__builtin_expect(!traits_type::eq_int_type(this->sbumpc(),
             __ret), true))
   __ret = this->sgetc();
 return __ret;
      }
      int_type
      sbumpc()
      {
 int_type __ret;
 if (__builtin_expect(this->gptr() < this->egptr(), true))
   {
     __ret = traits_type::to_int_type(*this->gptr());
     this->gbump(1);
   }
 else
   __ret = this->uflow();
 return __ret;
      }
      int_type
      sgetc()
      {
 int_type __ret;
 if (__builtin_expect(this->gptr() < this->egptr(), true))
   __ret = traits_type::to_int_type(*this->gptr());
 else
   __ret = this->underflow();
 return __ret;
      }
      streamsize
      sgetn(char_type* __s, streamsize __n)
      { return this->xsgetn(__s, __n); }
      int_type
      sputbackc(char_type __c)
      {
 int_type __ret;
 const bool __testpos = this->eback() < this->gptr();
 if (__builtin_expect(!__testpos ||
        !traits_type::eq(__c, this->gptr()[-1]), false))
   __ret = this->pbackfail(traits_type::to_int_type(__c));
 else
   {
     this->gbump(-1);
     __ret = traits_type::to_int_type(*this->gptr());
   }
 return __ret;
      }
      int_type
      sungetc()
      {
 int_type __ret;
 if (__builtin_expect(this->eback() < this->gptr(), true))
   {
     this->gbump(-1);
     __ret = traits_type::to_int_type(*this->gptr());
   }
 else
   __ret = this->pbackfail();
 return __ret;
      }
      int_type
      sputc(char_type __c)
      {
 int_type __ret;
 if (__builtin_expect(this->pptr() < this->epptr(), true))
   {
     *this->pptr() = __c;
     this->pbump(1);
     __ret = traits_type::to_int_type(__c);
   }
 else
   __ret = this->overflow(traits_type::to_int_type(__c));
 return __ret;
      }
      streamsize
      sputn(const char_type* __s, streamsize __n)
      { return this->xsputn(__s, __n); }
    protected:
      basic_streambuf()
      : _M_in_beg(0), _M_in_cur(0), _M_in_end(0),
      _M_out_beg(0), _M_out_cur(0), _M_out_end(0),
      _M_buf_locale(locale())
      { }
      char_type*
      eback() const { return _M_in_beg; }
      char_type*
      gptr() const { return _M_in_cur; }
      char_type*
      egptr() const { return _M_in_end; }
      void
      gbump(int __n) { _M_in_cur += __n; }
      void
      setg(char_type* __gbeg, char_type* __gnext, char_type* __gend)
      {
 _M_in_beg = __gbeg;
 _M_in_cur = __gnext;
 _M_in_end = __gend;
      }
      char_type*
      pbase() const { return _M_out_beg; }
      char_type*
      pptr() const { return _M_out_cur; }
      char_type*
      epptr() const { return _M_out_end; }
      void
      pbump(int __n) { _M_out_cur += __n; }
      void
      setp(char_type* __pbeg, char_type* __pend)
      {
 _M_out_beg = _M_out_cur = __pbeg;
 _M_out_end = __pend;
      }
      virtual void
      imbue(const locale& __loc)
      { }
      virtual basic_streambuf<char_type,_Traits>*
      setbuf(char_type*, streamsize)
      { return this; }
      virtual pos_type
      seekoff(off_type, ios_base::seekdir,
       ios_base::openmode = ios_base::in | ios_base::out)
      { return pos_type(off_type(-1)); }
      virtual pos_type
      seekpos(pos_type,
       ios_base::openmode = ios_base::in | ios_base::out)
      { return pos_type(off_type(-1)); }
      virtual int
      sync() { return 0; }
      virtual streamsize
      showmanyc() { return 0; }
      virtual streamsize
      xsgetn(char_type* __s, streamsize __n);
      virtual int_type
      underflow()
      { return traits_type::eof(); }
      virtual int_type
      uflow()
      {
 int_type __ret = traits_type::eof();
 const bool __testeof = traits_type::eq_int_type(this->underflow(),
       __ret);
 if (!__testeof)
   {
     __ret = traits_type::to_int_type(*this->gptr());
     this->gbump(1);
   }
 return __ret;
      }
      virtual int_type
      pbackfail(int_type __c = traits_type::eof())
      { return traits_type::eof(); }
      virtual streamsize
      xsputn(const char_type* __s, streamsize __n);
      virtual int_type
      overflow(int_type __c = traits_type::eof())
      { return traits_type::eof(); }
    public:
      void
      stossc()
      {
 if (this->gptr() < this->egptr())
   this->gbump(1);
 else
   this->uflow();
      }
      void
      __safe_gbump(streamsize __n) { _M_in_cur += __n; }
      void
      __safe_pbump(streamsize __n) { _M_out_cur += __n; }
    private:
      basic_streambuf(const basic_streambuf& __sb)
      : _M_in_beg(__sb._M_in_beg), _M_in_cur(__sb._M_in_cur),
      _M_in_end(__sb._M_in_end), _M_out_beg(__sb._M_out_beg),
      _M_out_cur(__sb._M_out_cur), _M_out_end(__sb._M_out_cur),
      _M_buf_locale(__sb._M_buf_locale)
      { }
      basic_streambuf&
      operator=(const basic_streambuf&) { return *this; };
    };
  template<>
    streamsize
    __copy_streambufs_eof(basic_streambuf<char>* __sbin,
     basic_streambuf<char>* __sbout, bool& __ineof);
  template<>
    streamsize
    __copy_streambufs_eof(basic_streambuf<wchar_t>* __sbin,
     basic_streambuf<wchar_t>* __sbout, bool& __ineof);

}
       
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename _CharT, typename _Traits>
    streamsize
    basic_streambuf<_CharT, _Traits>::
    xsgetn(char_type* __s, streamsize __n)
    {
      streamsize __ret = 0;
      while (__ret < __n)
 {
   const streamsize __buf_len = this->egptr() - this->gptr();
   if (__buf_len)
     {
       const streamsize __remaining = __n - __ret;
       const streamsize __len = std::min(__buf_len, __remaining);
       traits_type::copy(__s, this->gptr(), __len);
       __ret += __len;
       __s += __len;
       this->__safe_gbump(__len);
     }
   if (__ret < __n)
     {
       const int_type __c = this->uflow();
       if (!traits_type::eq_int_type(__c, traits_type::eof()))
  {
    traits_type::assign(*__s++, traits_type::to_char_type(__c));
    ++__ret;
  }
       else
  break;
     }
 }
      return __ret;
    }
  template<typename _CharT, typename _Traits>
    streamsize
    basic_streambuf<_CharT, _Traits>::
    xsputn(const char_type* __s, streamsize __n)
    {
      streamsize __ret = 0;
      while (__ret < __n)
 {
   const streamsize __buf_len = this->epptr() - this->pptr();
   if (__buf_len)
     {
       const streamsize __remaining = __n - __ret;
       const streamsize __len = std::min(__buf_len, __remaining);
       traits_type::copy(this->pptr(), __s, __len);
       __ret += __len;
       __s += __len;
       this->__safe_pbump(__len);
     }
   if (__ret < __n)
     {
       int_type __c = this->overflow(traits_type::to_int_type(*__s));
       if (!traits_type::eq_int_type(__c, traits_type::eof()))
  {
    ++__ret;
    ++__s;
  }
       else
  break;
     }
 }
      return __ret;
    }
  template<typename _CharT, typename _Traits>
    streamsize
    __copy_streambufs_eof(basic_streambuf<_CharT, _Traits>* __sbin,
     basic_streambuf<_CharT, _Traits>* __sbout,
     bool& __ineof)
    {
      streamsize __ret = 0;
      __ineof = true;
      typename _Traits::int_type __c = __sbin->sgetc();
      while (!_Traits::eq_int_type(__c, _Traits::eof()))
 {
   __c = __sbout->sputc(_Traits::to_char_type(__c));
   if (_Traits::eq_int_type(__c, _Traits::eof()))
     {
       __ineof = false;
       break;
     }
   ++__ret;
   __c = __sbin->snextc();
 }
      return __ret;
    }
  template<typename _CharT, typename _Traits>
    inline streamsize
    __copy_streambufs(basic_streambuf<_CharT, _Traits>* __sbin,
        basic_streambuf<_CharT, _Traits>* __sbout)
    {
      bool __ineof;
      return __copy_streambufs_eof(__sbin, __sbout, __ineof);
    }
  extern template class basic_streambuf<char>;
  extern template
    streamsize
    __copy_streambufs(basic_streambuf<char>*,
        basic_streambuf<char>*);
  extern template
    streamsize
    __copy_streambufs_eof(basic_streambuf<char>*,
     basic_streambuf<char>*, bool&);
  extern template class basic_streambuf<wchar_t>;
  extern template
    streamsize
    __copy_streambufs(basic_streambuf<wchar_t>*,
        basic_streambuf<wchar_t>*);
  extern template
    streamsize
    __copy_streambufs_eof(basic_streambuf<wchar_t>*,
     basic_streambuf<wchar_t>*, bool&);

}
       
       
       

typedef unsigned long int wctype_t;

enum
{
  __ISwupper = 0,
  __ISwlower = 1,
  __ISwalpha = 2,
  __ISwdigit = 3,
  __ISwxdigit = 4,
  __ISwspace = 5,
  __ISwprint = 6,
  __ISwgraph = 7,
  __ISwblank = 8,
  __ISwcntrl = 9,
  __ISwpunct = 10,
  __ISwalnum = 11,
  _ISwupper = ((__ISwupper) < 8 ? (int) ((1UL << (__ISwupper)) << 24) : ((__ISwupper) < 16 ? (int) ((1UL << (__ISwupper)) << 8) : ((__ISwupper) < 24 ? (int) ((1UL << (__ISwupper)) >> 8) : (int) ((1UL << (__ISwupper)) >> 24)))),
  _ISwlower = ((__ISwlower) < 8 ? (int) ((1UL << (__ISwlower)) << 24) : ((__ISwlower) < 16 ? (int) ((1UL << (__ISwlower)) << 8) : ((__ISwlower) < 24 ? (int) ((1UL << (__ISwlower)) >> 8) : (int) ((1UL << (__ISwlower)) >> 24)))),
  _ISwalpha = ((__ISwalpha) < 8 ? (int) ((1UL << (__ISwalpha)) << 24) : ((__ISwalpha) < 16 ? (int) ((1UL << (__ISwalpha)) << 8) : ((__ISwalpha) < 24 ? (int) ((1UL << (__ISwalpha)) >> 8) : (int) ((1UL << (__ISwalpha)) >> 24)))),
  _ISwdigit = ((__ISwdigit) < 8 ? (int) ((1UL << (__ISwdigit)) << 24) : ((__ISwdigit) < 16 ? (int) ((1UL << (__ISwdigit)) << 8) : ((__ISwdigit) < 24 ? (int) ((1UL << (__ISwdigit)) >> 8) : (int) ((1UL << (__ISwdigit)) >> 24)))),
  _ISwxdigit = ((__ISwxdigit) < 8 ? (int) ((1UL << (__ISwxdigit)) << 24) : ((__ISwxdigit) < 16 ? (int) ((1UL << (__ISwxdigit)) << 8) : ((__ISwxdigit) < 24 ? (int) ((1UL << (__ISwxdigit)) >> 8) : (int) ((1UL << (__ISwxdigit)) >> 24)))),
  _ISwspace = ((__ISwspace) < 8 ? (int) ((1UL << (__ISwspace)) << 24) : ((__ISwspace) < 16 ? (int) ((1UL << (__ISwspace)) << 8) : ((__ISwspace) < 24 ? (int) ((1UL << (__ISwspace)) >> 8) : (int) ((1UL << (__ISwspace)) >> 24)))),
  _ISwprint = ((__ISwprint) < 8 ? (int) ((1UL << (__ISwprint)) << 24) : ((__ISwprint) < 16 ? (int) ((1UL << (__ISwprint)) << 8) : ((__ISwprint) < 24 ? (int) ((1UL << (__ISwprint)) >> 8) : (int) ((1UL << (__ISwprint)) >> 24)))),
  _ISwgraph = ((__ISwgraph) < 8 ? (int) ((1UL << (__ISwgraph)) << 24) : ((__ISwgraph) < 16 ? (int) ((1UL << (__ISwgraph)) << 8) : ((__ISwgraph) < 24 ? (int) ((1UL << (__ISwgraph)) >> 8) : (int) ((1UL << (__ISwgraph)) >> 24)))),
  _ISwblank = ((__ISwblank) < 8 ? (int) ((1UL << (__ISwblank)) << 24) : ((__ISwblank) < 16 ? (int) ((1UL << (__ISwblank)) << 8) : ((__ISwblank) < 24 ? (int) ((1UL << (__ISwblank)) >> 8) : (int) ((1UL << (__ISwblank)) >> 24)))),
  _ISwcntrl = ((__ISwcntrl) < 8 ? (int) ((1UL << (__ISwcntrl)) << 24) : ((__ISwcntrl) < 16 ? (int) ((1UL << (__ISwcntrl)) << 8) : ((__ISwcntrl) < 24 ? (int) ((1UL << (__ISwcntrl)) >> 8) : (int) ((1UL << (__ISwcntrl)) >> 24)))),
  _ISwpunct = ((__ISwpunct) < 8 ? (int) ((1UL << (__ISwpunct)) << 24) : ((__ISwpunct) < 16 ? (int) ((1UL << (__ISwpunct)) << 8) : ((__ISwpunct) < 24 ? (int) ((1UL << (__ISwpunct)) >> 8) : (int) ((1UL << (__ISwpunct)) >> 24)))),
  _ISwalnum = ((__ISwalnum) < 8 ? (int) ((1UL << (__ISwalnum)) << 24) : ((__ISwalnum) < 16 ? (int) ((1UL << (__ISwalnum)) << 8) : ((__ISwalnum) < 24 ? (int) ((1UL << (__ISwalnum)) >> 8) : (int) ((1UL << (__ISwalnum)) >> 24))))
};
extern "C" {

extern int iswalnum (wint_t __wc) throw ();
extern int iswalpha (wint_t __wc) throw ();
extern int iswcntrl (wint_t __wc) throw ();
extern int iswdigit (wint_t __wc) throw ();
extern int iswgraph (wint_t __wc) throw ();
extern int iswlower (wint_t __wc) throw ();
extern int iswprint (wint_t __wc) throw ();
extern int iswpunct (wint_t __wc) throw ();
extern int iswspace (wint_t __wc) throw ();
extern int iswupper (wint_t __wc) throw ();
extern int iswxdigit (wint_t __wc) throw ();
extern int iswblank (wint_t __wc) throw ();
extern wctype_t wctype (const char *__property) throw ();
extern int iswctype (wint_t __wc, wctype_t __desc) throw ();


typedef const __int32_t *wctrans_t;



extern wint_t towlower (wint_t __wc) throw ();
extern wint_t towupper (wint_t __wc) throw ();

}
extern "C" {

extern wctrans_t wctrans (const char *__property) throw ();
extern wint_t towctrans (wint_t __wc, wctrans_t __desc) throw ();

extern int iswalnum_l (wint_t __wc, __locale_t __locale) throw ();
extern int iswalpha_l (wint_t __wc, __locale_t __locale) throw ();
extern int iswcntrl_l (wint_t __wc, __locale_t __locale) throw ();
extern int iswdigit_l (wint_t __wc, __locale_t __locale) throw ();
extern int iswgraph_l (wint_t __wc, __locale_t __locale) throw ();
extern int iswlower_l (wint_t __wc, __locale_t __locale) throw ();
extern int iswprint_l (wint_t __wc, __locale_t __locale) throw ();
extern int iswpunct_l (wint_t __wc, __locale_t __locale) throw ();
extern int iswspace_l (wint_t __wc, __locale_t __locale) throw ();
extern int iswupper_l (wint_t __wc, __locale_t __locale) throw ();
extern int iswxdigit_l (wint_t __wc, __locale_t __locale) throw ();
extern int iswblank_l (wint_t __wc, __locale_t __locale) throw ();
extern wctype_t wctype_l (const char *__property, __locale_t __locale)
     throw ();
extern int iswctype_l (wint_t __wc, wctype_t __desc, __locale_t __locale)
     throw ();
extern wint_t towlower_l (wint_t __wc, __locale_t __locale) throw ();
extern wint_t towupper_l (wint_t __wc, __locale_t __locale) throw ();
extern wctrans_t wctrans_l (const char *__property, __locale_t __locale)
     throw ();
extern wint_t towctrans_l (wint_t __wc, wctrans_t __desc,
      __locale_t __locale) throw ();
}
namespace std
{
  using ::wctrans_t;
  using ::wctype_t;
  using ::wint_t;
  using ::iswalnum;
  using ::iswalpha;
  using ::iswblank;
  using ::iswcntrl;
  using ::iswctype;
  using ::iswdigit;
  using ::iswgraph;
  using ::iswlower;
  using ::iswprint;
  using ::iswpunct;
  using ::iswspace;
  using ::iswupper;
  using ::iswxdigit;
  using ::towctrans;
  using ::towlower;
  using ::towupper;
  using ::wctrans;
  using ::wctype;
}
       
namespace std __attribute__ ((__visibility__ ("default")))
{

  struct ctype_base
  {
    typedef const int* __to_type;
    typedef unsigned short mask;
    static const mask upper = _ISupper;
    static const mask lower = _ISlower;
    static const mask alpha = _ISalpha;
    static const mask digit = _ISdigit;
    static const mask xdigit = _ISxdigit;
    static const mask space = _ISspace;
    static const mask print = _ISprint;
    static const mask graph = _ISalpha | _ISdigit | _ISpunct;
    static const mask cntrl = _IScntrl;
    static const mask punct = _ISpunct;
    static const mask alnum = _ISalpha | _ISdigit;
  };

}
       
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename _CharT, typename _Traits>
    class istreambuf_iterator
    : public iterator<input_iterator_tag, _CharT, typename _Traits::off_type,
                      _CharT*,
        _CharT>
    {
    public:
      typedef _CharT char_type;
      typedef _Traits traits_type;
      typedef typename _Traits::int_type int_type;
      typedef basic_streambuf<_CharT, _Traits> streambuf_type;
      typedef basic_istream<_CharT, _Traits> istream_type;
      template<typename _CharT2>
 friend typename __gnu_cxx::__enable_if<__is_char<_CharT2>::__value,
                      ostreambuf_iterator<_CharT2> >::__type
 copy(istreambuf_iterator<_CharT2>, istreambuf_iterator<_CharT2>,
      ostreambuf_iterator<_CharT2>);
      template<bool _IsMove, typename _CharT2>
 friend typename __gnu_cxx::__enable_if<__is_char<_CharT2>::__value,
            _CharT2*>::__type
 __copy_move_a2(istreambuf_iterator<_CharT2>,
         istreambuf_iterator<_CharT2>, _CharT2*);
      template<typename _CharT2>
 friend typename __gnu_cxx::__enable_if<__is_char<_CharT2>::__value,
               istreambuf_iterator<_CharT2> >::__type
 find(istreambuf_iterator<_CharT2>, istreambuf_iterator<_CharT2>,
      const _CharT2&);
    private:
      mutable streambuf_type* _M_sbuf;
      mutable int_type _M_c;
    public:
      constexpr istreambuf_iterator() noexcept
      : _M_sbuf(0), _M_c(traits_type::eof()) { }
      istreambuf_iterator(const istreambuf_iterator&) noexcept = default;
      ~istreambuf_iterator() = default;
      istreambuf_iterator(istream_type& __s) noexcept
      : _M_sbuf(__s.rdbuf()), _M_c(traits_type::eof()) { }
      istreambuf_iterator(streambuf_type* __s) noexcept
      : _M_sbuf(__s), _M_c(traits_type::eof()) { }
      char_type
      operator*() const
      {
 return traits_type::to_char_type(_M_get());
      }
      istreambuf_iterator&
      operator++()
      {
 ;
 if (_M_sbuf)
   {
     _M_sbuf->sbumpc();
     _M_c = traits_type::eof();
   }
 return *this;
      }
      istreambuf_iterator
      operator++(int)
      {
 ;
 istreambuf_iterator __old = *this;
 if (_M_sbuf)
   {
     __old._M_c = _M_sbuf->sbumpc();
     _M_c = traits_type::eof();
   }
 return __old;
      }
      bool
      equal(const istreambuf_iterator& __b) const
      { return _M_at_eof() == __b._M_at_eof(); }
    private:
      int_type
      _M_get() const
      {
 const int_type __eof = traits_type::eof();
 int_type __ret = __eof;
 if (_M_sbuf)
   {
     if (!traits_type::eq_int_type(_M_c, __eof))
       __ret = _M_c;
     else if (!traits_type::eq_int_type((__ret = _M_sbuf->sgetc()),
            __eof))
       _M_c = __ret;
     else
       _M_sbuf = 0;
   }
 return __ret;
      }
      bool
      _M_at_eof() const
      {
 const int_type __eof = traits_type::eof();
 return traits_type::eq_int_type(_M_get(), __eof);
      }
    };
  template<typename _CharT, typename _Traits>
    inline bool
    operator==(const istreambuf_iterator<_CharT, _Traits>& __a,
        const istreambuf_iterator<_CharT, _Traits>& __b)
    { return __a.equal(__b); }
  template<typename _CharT, typename _Traits>
    inline bool
    operator!=(const istreambuf_iterator<_CharT, _Traits>& __a,
        const istreambuf_iterator<_CharT, _Traits>& __b)
    { return !__a.equal(__b); }
  template<typename _CharT, typename _Traits>
    class ostreambuf_iterator
    : public iterator<output_iterator_tag, void, void, void, void>
    {
    public:
      typedef _CharT char_type;
      typedef _Traits traits_type;
      typedef basic_streambuf<_CharT, _Traits> streambuf_type;
      typedef basic_ostream<_CharT, _Traits> ostream_type;
      template<typename _CharT2>
 friend typename __gnu_cxx::__enable_if<__is_char<_CharT2>::__value,
                      ostreambuf_iterator<_CharT2> >::__type
 copy(istreambuf_iterator<_CharT2>, istreambuf_iterator<_CharT2>,
      ostreambuf_iterator<_CharT2>);
    private:
      streambuf_type* _M_sbuf;
      bool _M_failed;
    public:
      ostreambuf_iterator(ostream_type& __s) noexcept
      : _M_sbuf(__s.rdbuf()), _M_failed(!_M_sbuf) { }
      ostreambuf_iterator(streambuf_type* __s) noexcept
      : _M_sbuf(__s), _M_failed(!_M_sbuf) { }
      ostreambuf_iterator&
      operator=(_CharT __c)
      {
 if (!_M_failed &&
     _Traits::eq_int_type(_M_sbuf->sputc(__c), _Traits::eof()))
   _M_failed = true;
 return *this;
      }
      ostreambuf_iterator&
      operator*()
      { return *this; }
      ostreambuf_iterator&
      operator++(int)
      { return *this; }
      ostreambuf_iterator&
      operator++()
      { return *this; }
      bool
      failed() const noexcept
      { return _M_failed; }
      ostreambuf_iterator&
      _M_put(const _CharT* __ws, streamsize __len)
      {
 if (__builtin_expect(!_M_failed, true)
     && __builtin_expect(this->_M_sbuf->sputn(__ws, __len) != __len,
    false))
   _M_failed = true;
 return *this;
      }
    };
  template<typename _CharT>
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value,
                           ostreambuf_iterator<_CharT> >::__type
    copy(istreambuf_iterator<_CharT> __first,
  istreambuf_iterator<_CharT> __last,
  ostreambuf_iterator<_CharT> __result)
    {
      if (__first._M_sbuf && !__last._M_sbuf && !__result._M_failed)
 {
   bool __ineof;
   __copy_streambufs_eof(__first._M_sbuf, __result._M_sbuf, __ineof);
   if (!__ineof)
     __result._M_failed = true;
 }
      return __result;
    }
  template<bool _IsMove, typename _CharT>
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value,
            ostreambuf_iterator<_CharT> >::__type
    __copy_move_a2(_CharT* __first, _CharT* __last,
     ostreambuf_iterator<_CharT> __result)
    {
      const streamsize __num = __last - __first;
      if (__num > 0)
 __result._M_put(__first, __num);
      return __result;
    }
  template<bool _IsMove, typename _CharT>
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value,
        ostreambuf_iterator<_CharT> >::__type
    __copy_move_a2(const _CharT* __first, const _CharT* __last,
     ostreambuf_iterator<_CharT> __result)
    {
      const streamsize __num = __last - __first;
      if (__num > 0)
 __result._M_put(__first, __num);
      return __result;
    }
  template<bool _IsMove, typename _CharT>
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value,
            _CharT*>::__type
    __copy_move_a2(istreambuf_iterator<_CharT> __first,
     istreambuf_iterator<_CharT> __last, _CharT* __result)
    {
      typedef istreambuf_iterator<_CharT> __is_iterator_type;
      typedef typename __is_iterator_type::traits_type traits_type;
      typedef typename __is_iterator_type::streambuf_type streambuf_type;
      typedef typename traits_type::int_type int_type;
      if (__first._M_sbuf && !__last._M_sbuf)
 {
   streambuf_type* __sb = __first._M_sbuf;
   int_type __c = __sb->sgetc();
   while (!traits_type::eq_int_type(__c, traits_type::eof()))
     {
       const streamsize __n = __sb->egptr() - __sb->gptr();
       if (__n > 1)
  {
    traits_type::copy(__result, __sb->gptr(), __n);
    __sb->__safe_gbump(__n);
    __result += __n;
    __c = __sb->underflow();
  }
       else
  {
    *__result++ = traits_type::to_char_type(__c);
    __c = __sb->snextc();
  }
     }
 }
      return __result;
    }
  template<typename _CharT>
    typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value,
          istreambuf_iterator<_CharT> >::__type
    find(istreambuf_iterator<_CharT> __first,
  istreambuf_iterator<_CharT> __last, const _CharT& __val)
    {
      typedef istreambuf_iterator<_CharT> __is_iterator_type;
      typedef typename __is_iterator_type::traits_type traits_type;
      typedef typename __is_iterator_type::streambuf_type streambuf_type;
      typedef typename traits_type::int_type int_type;
      if (__first._M_sbuf && !__last._M_sbuf)
 {
   const int_type __ival = traits_type::to_int_type(__val);
   streambuf_type* __sb = __first._M_sbuf;
   int_type __c = __sb->sgetc();
   while (!traits_type::eq_int_type(__c, traits_type::eof())
   && !traits_type::eq_int_type(__c, __ival))
     {
       streamsize __n = __sb->egptr() - __sb->gptr();
       if (__n > 1)
  {
    const _CharT* __p = traits_type::find(__sb->gptr(),
       __n, __val);
    if (__p)
      __n = __p - __sb->gptr();
    __sb->__safe_gbump(__n);
    __c = __sb->sgetc();
  }
       else
  __c = __sb->snextc();
     }
   if (!traits_type::eq_int_type(__c, traits_type::eof()))
     __first._M_c = __c;
   else
     __first._M_sbuf = 0;
 }
      return __first;
    }

}
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename _Tp>
    void
    __convert_to_v(const char*, _Tp&, ios_base::iostate&,
     const __c_locale&) throw();
  template<>
    void
    __convert_to_v(const char*, float&, ios_base::iostate&,
     const __c_locale&) throw();
  template<>
    void
    __convert_to_v(const char*, double&, ios_base::iostate&,
     const __c_locale&) throw();
  template<>
    void
    __convert_to_v(const char*, long double&, ios_base::iostate&,
     const __c_locale&) throw();
  template<typename _CharT, typename _Traits>
    struct __pad
    {
      static void
      _S_pad(ios_base& __io, _CharT __fill, _CharT* __news,
      const _CharT* __olds, streamsize __newlen, streamsize __oldlen);
    };
  template<typename _CharT>
    _CharT*
    __add_grouping(_CharT* __s, _CharT __sep,
     const char* __gbeg, size_t __gsize,
     const _CharT* __first, const _CharT* __last);
  template<typename _CharT>
    inline
    ostreambuf_iterator<_CharT>
    __write(ostreambuf_iterator<_CharT> __s, const _CharT* __ws, int __len)
    {
      __s._M_put(__ws, __len);
      return __s;
    }
  template<typename _CharT, typename _OutIter>
    inline
    _OutIter
    __write(_OutIter __s, const _CharT* __ws, int __len)
    {
      for (int __j = 0; __j < __len; __j++, ++__s)
 *__s = __ws[__j];
      return __s;
    }
  template<typename _CharT>
    class __ctype_abstract_base : public locale::facet, public ctype_base
    {
    public:
      typedef _CharT char_type;
      bool
      is(mask __m, char_type __c) const
      { return this->do_is(__m, __c); }
      const char_type*
      is(const char_type *__lo, const char_type *__hi, mask *__vec) const
      { return this->do_is(__lo, __hi, __vec); }
      const char_type*
      scan_is(mask __m, const char_type* __lo, const char_type* __hi) const
      { return this->do_scan_is(__m, __lo, __hi); }
      const char_type*
      scan_not(mask __m, const char_type* __lo, const char_type* __hi) const
      { return this->do_scan_not(__m, __lo, __hi); }
      char_type
      toupper(char_type __c) const
      { return this->do_toupper(__c); }
      const char_type*
      toupper(char_type *__lo, const char_type* __hi) const
      { return this->do_toupper(__lo, __hi); }
      char_type
      tolower(char_type __c) const
      { return this->do_tolower(__c); }
      const char_type*
      tolower(char_type* __lo, const char_type* __hi) const
      { return this->do_tolower(__lo, __hi); }
      char_type
      widen(char __c) const
      { return this->do_widen(__c); }
      const char*
      widen(const char* __lo, const char* __hi, char_type* __to) const
      { return this->do_widen(__lo, __hi, __to); }
      char
      narrow(char_type __c, char __dfault) const
      { return this->do_narrow(__c, __dfault); }
      const char_type*
      narrow(const char_type* __lo, const char_type* __hi,
       char __dfault, char* __to) const
      { return this->do_narrow(__lo, __hi, __dfault, __to); }
    protected:
      explicit
      __ctype_abstract_base(size_t __refs = 0): facet(__refs) { }
      virtual
      ~__ctype_abstract_base() { }
      virtual bool
      do_is(mask __m, char_type __c) const = 0;
      virtual const char_type*
      do_is(const char_type* __lo, const char_type* __hi,
     mask* __vec) const = 0;
      virtual const char_type*
      do_scan_is(mask __m, const char_type* __lo,
   const char_type* __hi) const = 0;
      virtual const char_type*
      do_scan_not(mask __m, const char_type* __lo,
    const char_type* __hi) const = 0;
      virtual char_type
      do_toupper(char_type __c) const = 0;
      virtual const char_type*
      do_toupper(char_type* __lo, const char_type* __hi) const = 0;
      virtual char_type
      do_tolower(char_type __c) const = 0;
      virtual const char_type*
      do_tolower(char_type* __lo, const char_type* __hi) const = 0;
      virtual char_type
      do_widen(char __c) const = 0;
      virtual const char*
      do_widen(const char* __lo, const char* __hi, char_type* __to) const = 0;
      virtual char
      do_narrow(char_type __c, char __dfault) const = 0;
      virtual const char_type*
      do_narrow(const char_type* __lo, const char_type* __hi,
  char __dfault, char* __to) const = 0;
    };
  template<typename _CharT>
    class ctype : public __ctype_abstract_base<_CharT>
    {
    public:
      typedef _CharT char_type;
      typedef typename __ctype_abstract_base<_CharT>::mask mask;
      static locale::id id;
      explicit
      ctype(size_t __refs = 0) : __ctype_abstract_base<_CharT>(__refs) { }
   protected:
      virtual
      ~ctype();
      virtual bool
      do_is(mask __m, char_type __c) const;
      virtual const char_type*
      do_is(const char_type* __lo, const char_type* __hi, mask* __vec) const;
      virtual const char_type*
      do_scan_is(mask __m, const char_type* __lo, const char_type* __hi) const;
      virtual const char_type*
      do_scan_not(mask __m, const char_type* __lo,
    const char_type* __hi) const;
      virtual char_type
      do_toupper(char_type __c) const;
      virtual const char_type*
      do_toupper(char_type* __lo, const char_type* __hi) const;
      virtual char_type
      do_tolower(char_type __c) const;
      virtual const char_type*
      do_tolower(char_type* __lo, const char_type* __hi) const;
      virtual char_type
      do_widen(char __c) const;
      virtual const char*
      do_widen(const char* __lo, const char* __hi, char_type* __dest) const;
      virtual char
      do_narrow(char_type, char __dfault) const;
      virtual const char_type*
      do_narrow(const char_type* __lo, const char_type* __hi,
  char __dfault, char* __to) const;
    };
  template<typename _CharT>
    locale::id ctype<_CharT>::id;
  template<>
    class ctype<char> : public locale::facet, public ctype_base
    {
    public:
      typedef char char_type;
    protected:
      __c_locale _M_c_locale_ctype;
      bool _M_del;
      __to_type _M_toupper;
      __to_type _M_tolower;
      const mask* _M_table;
      mutable char _M_widen_ok;
      mutable char _M_widen[1 + static_cast<unsigned char>(-1)];
      mutable char _M_narrow[1 + static_cast<unsigned char>(-1)];
      mutable char _M_narrow_ok;
    public:
      static locale::id id;
      static const size_t table_size = 1 + static_cast<unsigned char>(-1);
      explicit
      ctype(const mask* __table = 0, bool __del = false, size_t __refs = 0);
      explicit
      ctype(__c_locale __cloc, const mask* __table = 0, bool __del = false,
     size_t __refs = 0);
      inline bool
      is(mask __m, char __c) const;
      inline const char*
      is(const char* __lo, const char* __hi, mask* __vec) const;
      inline const char*
      scan_is(mask __m, const char* __lo, const char* __hi) const;
      inline const char*
      scan_not(mask __m, const char* __lo, const char* __hi) const;
      char_type
      toupper(char_type __c) const
      { return this->do_toupper(__c); }
      const char_type*
      toupper(char_type *__lo, const char_type* __hi) const
      { return this->do_toupper(__lo, __hi); }
      char_type
      tolower(char_type __c) const
      { return this->do_tolower(__c); }
      const char_type*
      tolower(char_type* __lo, const char_type* __hi) const
      { return this->do_tolower(__lo, __hi); }
      char_type
      widen(char __c) const
      {
 if (_M_widen_ok)
   return _M_widen[static_cast<unsigned char>(__c)];
 this->_M_widen_init();
 return this->do_widen(__c);
      }
      const char*
      widen(const char* __lo, const char* __hi, char_type* __to) const
      {
 if (_M_widen_ok == 1)
   {
     __builtin_memcpy(__to, __lo, __hi - __lo);
     return __hi;
   }
 if (!_M_widen_ok)
   _M_widen_init();
 return this->do_widen(__lo, __hi, __to);
      }
      char
      narrow(char_type __c, char __dfault) const
      {
 if (_M_narrow[static_cast<unsigned char>(__c)])
   return _M_narrow[static_cast<unsigned char>(__c)];
 const char __t = do_narrow(__c, __dfault);
 if (__t != __dfault)
   _M_narrow[static_cast<unsigned char>(__c)] = __t;
 return __t;
      }
      const char_type*
      narrow(const char_type* __lo, const char_type* __hi,
      char __dfault, char* __to) const
      {
 if (__builtin_expect(_M_narrow_ok == 1, true))
   {
     __builtin_memcpy(__to, __lo, __hi - __lo);
     return __hi;
   }
 if (!_M_narrow_ok)
   _M_narrow_init();
 return this->do_narrow(__lo, __hi, __dfault, __to);
      }
      const mask*
      table() const throw()
      { return _M_table; }
      static const mask*
      classic_table() throw();
    protected:
      virtual
      ~ctype();
      virtual char_type
      do_toupper(char_type __c) const;
      virtual const char_type*
      do_toupper(char_type* __lo, const char_type* __hi) const;
      virtual char_type
      do_tolower(char_type __c) const;
      virtual const char_type*
      do_tolower(char_type* __lo, const char_type* __hi) const;
      virtual char_type
      do_widen(char __c) const
      { return __c; }
      virtual const char*
      do_widen(const char* __lo, const char* __hi, char_type* __to) const
      {
 __builtin_memcpy(__to, __lo, __hi - __lo);
 return __hi;
      }
      virtual char
      do_narrow(char_type __c, char __dfault) const
      { return __c; }
      virtual const char_type*
      do_narrow(const char_type* __lo, const char_type* __hi,
  char __dfault, char* __to) const
      {
 __builtin_memcpy(__to, __lo, __hi - __lo);
 return __hi;
      }
    private:
      void _M_narrow_init() const;
      void _M_widen_init() const;
    };
  template<>
    class ctype<wchar_t> : public __ctype_abstract_base<wchar_t>
    {
    public:
      typedef wchar_t char_type;
      typedef wctype_t __wmask_type;
    protected:
      __c_locale _M_c_locale_ctype;
      bool _M_narrow_ok;
      char _M_narrow[128];
      wint_t _M_widen[1 + static_cast<unsigned char>(-1)];
      mask _M_bit[16];
      __wmask_type _M_wmask[16];
    public:
      static locale::id id;
      explicit
      ctype(size_t __refs = 0);
      explicit
      ctype(__c_locale __cloc, size_t __refs = 0);
    protected:
      __wmask_type
      _M_convert_to_wmask(const mask __m) const throw();
      virtual
      ~ctype();
      virtual bool
      do_is(mask __m, char_type __c) const;
      virtual const char_type*
      do_is(const char_type* __lo, const char_type* __hi, mask* __vec) const;
      virtual const char_type*
      do_scan_is(mask __m, const char_type* __lo, const char_type* __hi) const;
      virtual const char_type*
      do_scan_not(mask __m, const char_type* __lo,
    const char_type* __hi) const;
      virtual char_type
      do_toupper(char_type __c) const;
      virtual const char_type*
      do_toupper(char_type* __lo, const char_type* __hi) const;
      virtual char_type
      do_tolower(char_type __c) const;
      virtual const char_type*
      do_tolower(char_type* __lo, const char_type* __hi) const;
      virtual char_type
      do_widen(char __c) const;
      virtual const char*
      do_widen(const char* __lo, const char* __hi, char_type* __to) const;
      virtual char
      do_narrow(char_type __c, char __dfault) const;
      virtual const char_type*
      do_narrow(const char_type* __lo, const char_type* __hi,
  char __dfault, char* __to) const;
      void
      _M_initialize_ctype() throw();
    };
  template<typename _CharT>
    class ctype_byname : public ctype<_CharT>
    {
    public:
      typedef typename ctype<_CharT>::mask mask;
      explicit
      ctype_byname(const char* __s, size_t __refs = 0);
    protected:
      virtual
      ~ctype_byname() { };
    };
  template<>
    class ctype_byname<char> : public ctype<char>
    {
    public:
      explicit
      ctype_byname(const char* __s, size_t __refs = 0);
    protected:
      virtual
      ~ctype_byname();
    };
  template<>
    class ctype_byname<wchar_t> : public ctype<wchar_t>
    {
    public:
      explicit
      ctype_byname(const char* __s, size_t __refs = 0);
    protected:
      virtual
      ~ctype_byname();
    };

}
namespace std __attribute__ ((__visibility__ ("default")))
{

  bool
  ctype<char>::
  is(mask __m, char __c) const
  { return _M_table[static_cast<unsigned char>(__c)] & __m; }
  const char*
  ctype<char>::
  is(const char* __low, const char* __high, mask* __vec) const
  {
    while (__low < __high)
      *__vec++ = _M_table[static_cast<unsigned char>(*__low++)];
    return __high;
  }
  const char*
  ctype<char>::
  scan_is(mask __m, const char* __low, const char* __high) const
  {
    while (__low < __high
    && !(_M_table[static_cast<unsigned char>(*__low)] & __m))
      ++__low;
    return __low;
  }
  const char*
  ctype<char>::
  scan_not(mask __m, const char* __low, const char* __high) const
  {
    while (__low < __high
    && (_M_table[static_cast<unsigned char>(*__low)] & __m) != 0)
      ++__low;
    return __low;
  }

}
namespace std __attribute__ ((__visibility__ ("default")))
{

  class __num_base
  {
  public:
    enum
      {
 _S_ominus,
 _S_oplus,
 _S_ox,
 _S_oX,
 _S_odigits,
 _S_odigits_end = _S_odigits + 16,
 _S_oudigits = _S_odigits_end,
 _S_oudigits_end = _S_oudigits + 16,
 _S_oe = _S_odigits + 14,
 _S_oE = _S_oudigits + 14,
 _S_oend = _S_oudigits_end
      };
    static const char* _S_atoms_out;
    static const char* _S_atoms_in;
    enum
    {
      _S_iminus,
      _S_iplus,
      _S_ix,
      _S_iX,
      _S_izero,
      _S_ie = _S_izero + 14,
      _S_iE = _S_izero + 20,
      _S_iend = 26
    };
    static void
    _S_format_float(const ios_base& __io, char* __fptr, char __mod) throw();
  };
  template<typename _CharT>
    struct __numpunct_cache : public locale::facet
    {
      const char* _M_grouping;
      size_t _M_grouping_size;
      bool _M_use_grouping;
      const _CharT* _M_truename;
      size_t _M_truename_size;
      const _CharT* _M_falsename;
      size_t _M_falsename_size;
      _CharT _M_decimal_point;
      _CharT _M_thousands_sep;
      _CharT _M_atoms_out[__num_base::_S_oend];
      _CharT _M_atoms_in[__num_base::_S_iend];
      bool _M_allocated;
      __numpunct_cache(size_t __refs = 0)
      : facet(__refs), _M_grouping(0), _M_grouping_size(0),
 _M_use_grouping(false),
 _M_truename(0), _M_truename_size(0), _M_falsename(0),
 _M_falsename_size(0), _M_decimal_point(_CharT()),
 _M_thousands_sep(_CharT()), _M_allocated(false)
 { }
      ~__numpunct_cache();
      void
      _M_cache(const locale& __loc);
    private:
      __numpunct_cache&
      operator=(const __numpunct_cache&);
      explicit
      __numpunct_cache(const __numpunct_cache&);
    };
  template<typename _CharT>
    __numpunct_cache<_CharT>::~__numpunct_cache()
    {
      if (_M_allocated)
 {
   delete [] _M_grouping;
   delete [] _M_truename;
   delete [] _M_falsename;
 }
    }
  template<typename _CharT>
    class numpunct : public locale::facet
    {
    public:
      typedef _CharT char_type;
      typedef basic_string<_CharT> string_type;
      typedef __numpunct_cache<_CharT> __cache_type;
    protected:
      __cache_type* _M_data;
    public:
      static locale::id id;
      explicit
      numpunct(size_t __refs = 0)
      : facet(__refs), _M_data(0)
      { _M_initialize_numpunct(); }
      explicit
      numpunct(__cache_type* __cache, size_t __refs = 0)
      : facet(__refs), _M_data(__cache)
      { _M_initialize_numpunct(); }
      explicit
      numpunct(__c_locale __cloc, size_t __refs = 0)
      : facet(__refs), _M_data(0)
      { _M_initialize_numpunct(__cloc); }
      char_type
      decimal_point() const
      { return this->do_decimal_point(); }
      char_type
      thousands_sep() const
      { return this->do_thousands_sep(); }
      string
      grouping() const
      { return this->do_grouping(); }
      string_type
      truename() const
      { return this->do_truename(); }
      string_type
      falsename() const
      { return this->do_falsename(); }
    protected:
      virtual
      ~numpunct();
      virtual char_type
      do_decimal_point() const
      { return _M_data->_M_decimal_point; }
      virtual char_type
      do_thousands_sep() const
      { return _M_data->_M_thousands_sep; }
      virtual string
      do_grouping() const
      { return _M_data->_M_grouping; }
      virtual string_type
      do_truename() const
      { return _M_data->_M_truename; }
      virtual string_type
      do_falsename() const
      { return _M_data->_M_falsename; }
      void
      _M_initialize_numpunct(__c_locale __cloc = 0);
    };
  template<typename _CharT>
    locale::id numpunct<_CharT>::id;
  template<>
    numpunct<char>::~numpunct();
  template<>
    void
    numpunct<char>::_M_initialize_numpunct(__c_locale __cloc);
  template<>
    numpunct<wchar_t>::~numpunct();
  template<>
    void
    numpunct<wchar_t>::_M_initialize_numpunct(__c_locale __cloc);
  template<typename _CharT>
    class numpunct_byname : public numpunct<_CharT>
    {
    public:
      typedef _CharT char_type;
      typedef basic_string<_CharT> string_type;
      explicit
      numpunct_byname(const char* __s, size_t __refs = 0)
      : numpunct<_CharT>(__refs)
      {
 if (__builtin_strcmp(__s, "C") != 0
     && __builtin_strcmp(__s, "POSIX") != 0)
   {
     __c_locale __tmp;
     this->_S_create_c_locale(__tmp, __s);
     this->_M_initialize_numpunct(__tmp);
     this->_S_destroy_c_locale(__tmp);
   }
      }
    protected:
      virtual
      ~numpunct_byname() { }
    };

  template<typename _CharT, typename _InIter>
    class num_get : public locale::facet
    {
    public:
      typedef _CharT char_type;
      typedef _InIter iter_type;
      static locale::id id;
      explicit
      num_get(size_t __refs = 0) : facet(__refs) { }
      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
   ios_base::iostate& __err, bool& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }
      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
   ios_base::iostate& __err, long& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }
      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
   ios_base::iostate& __err, unsigned short& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }
      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
   ios_base::iostate& __err, unsigned int& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }
      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
   ios_base::iostate& __err, unsigned long& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }
      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
   ios_base::iostate& __err, long long& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }
      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
   ios_base::iostate& __err, unsigned long long& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }
      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
   ios_base::iostate& __err, float& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }
      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
   ios_base::iostate& __err, double& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }
      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
   ios_base::iostate& __err, long double& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }
      iter_type
      get(iter_type __in, iter_type __end, ios_base& __io,
   ios_base::iostate& __err, void*& __v) const
      { return this->do_get(__in, __end, __io, __err, __v); }
    protected:
      virtual ~num_get() { }
      iter_type
      _M_extract_float(iter_type, iter_type, ios_base&, ios_base::iostate&,
         string&) const;
      template<typename _ValueT>
 iter_type
 _M_extract_int(iter_type, iter_type, ios_base&, ios_base::iostate&,
         _ValueT&) const;
      template<typename _CharT2>
      typename __gnu_cxx::__enable_if<__is_char<_CharT2>::__value, int>::__type
 _M_find(const _CharT2*, size_t __len, _CharT2 __c) const
 {
   int __ret = -1;
   if (__len <= 10)
     {
       if (__c >= _CharT2('0') && __c < _CharT2(_CharT2('0') + __len))
  __ret = __c - _CharT2('0');
     }
   else
     {
       if (__c >= _CharT2('0') && __c <= _CharT2('9'))
  __ret = __c - _CharT2('0');
       else if (__c >= _CharT2('a') && __c <= _CharT2('f'))
  __ret = 10 + (__c - _CharT2('a'));
       else if (__c >= _CharT2('A') && __c <= _CharT2('F'))
  __ret = 10 + (__c - _CharT2('A'));
     }
   return __ret;
 }
      template<typename _CharT2>
      typename __gnu_cxx::__enable_if<!__is_char<_CharT2>::__value,
          int>::__type
 _M_find(const _CharT2* __zero, size_t __len, _CharT2 __c) const
 {
   int __ret = -1;
   const char_type* __q = char_traits<_CharT2>::find(__zero, __len, __c);
   if (__q)
     {
       __ret = __q - __zero;
       if (__ret > 15)
  __ret -= 6;
     }
   return __ret;
 }
      virtual iter_type
      do_get(iter_type, iter_type, ios_base&, ios_base::iostate&, bool&) const;
      virtual iter_type
      do_get(iter_type __beg, iter_type __end, ios_base& __io,
      ios_base::iostate& __err, long& __v) const
      { return _M_extract_int(__beg, __end, __io, __err, __v); }
      virtual iter_type
      do_get(iter_type __beg, iter_type __end, ios_base& __io,
      ios_base::iostate& __err, unsigned short& __v) const
      { return _M_extract_int(__beg, __end, __io, __err, __v); }
      virtual iter_type
      do_get(iter_type __beg, iter_type __end, ios_base& __io,
      ios_base::iostate& __err, unsigned int& __v) const
      { return _M_extract_int(__beg, __end, __io, __err, __v); }
      virtual iter_type
      do_get(iter_type __beg, iter_type __end, ios_base& __io,
      ios_base::iostate& __err, unsigned long& __v) const
      { return _M_extract_int(__beg, __end, __io, __err, __v); }
      virtual iter_type
      do_get(iter_type __beg, iter_type __end, ios_base& __io,
      ios_base::iostate& __err, long long& __v) const
      { return _M_extract_int(__beg, __end, __io, __err, __v); }
      virtual iter_type
      do_get(iter_type __beg, iter_type __end, ios_base& __io,
      ios_base::iostate& __err, unsigned long long& __v) const
      { return _M_extract_int(__beg, __end, __io, __err, __v); }
      virtual iter_type
      do_get(iter_type, iter_type, ios_base&, ios_base::iostate&, float&) const;
      virtual iter_type
      do_get(iter_type, iter_type, ios_base&, ios_base::iostate&,
      double&) const;
      virtual iter_type
      do_get(iter_type, iter_type, ios_base&, ios_base::iostate&,
      long double&) const;
      virtual iter_type
      do_get(iter_type, iter_type, ios_base&, ios_base::iostate&, void*&) const;
    };
  template<typename _CharT, typename _InIter>
    locale::id num_get<_CharT, _InIter>::id;
  template<typename _CharT, typename _OutIter>
    class num_put : public locale::facet
    {
    public:
      typedef _CharT char_type;
      typedef _OutIter iter_type;
      static locale::id id;
      explicit
      num_put(size_t __refs = 0) : facet(__refs) { }
      iter_type
      put(iter_type __s, ios_base& __io, char_type __fill, bool __v) const
      { return this->do_put(__s, __io, __fill, __v); }
      iter_type
      put(iter_type __s, ios_base& __io, char_type __fill, long __v) const
      { return this->do_put(__s, __io, __fill, __v); }
      iter_type
      put(iter_type __s, ios_base& __io, char_type __fill,
   unsigned long __v) const
      { return this->do_put(__s, __io, __fill, __v); }
      iter_type
      put(iter_type __s, ios_base& __io, char_type __fill, long long __v) const
      { return this->do_put(__s, __io, __fill, __v); }
      iter_type
      put(iter_type __s, ios_base& __io, char_type __fill,
   unsigned long long __v) const
      { return this->do_put(__s, __io, __fill, __v); }
      iter_type
      put(iter_type __s, ios_base& __io, char_type __fill, double __v) const
      { return this->do_put(__s, __io, __fill, __v); }
      iter_type
      put(iter_type __s, ios_base& __io, char_type __fill,
   long double __v) const
      { return this->do_put(__s, __io, __fill, __v); }
      iter_type
      put(iter_type __s, ios_base& __io, char_type __fill,
   const void* __v) const
      { return this->do_put(__s, __io, __fill, __v); }
    protected:
      template<typename _ValueT>
 iter_type
 _M_insert_float(iter_type, ios_base& __io, char_type __fill,
   char __mod, _ValueT __v) const;
      void
      _M_group_float(const char* __grouping, size_t __grouping_size,
       char_type __sep, const char_type* __p, char_type* __new,
       char_type* __cs, int& __len) const;
      template<typename _ValueT>
 iter_type
 _M_insert_int(iter_type, ios_base& __io, char_type __fill,
        _ValueT __v) const;
      void
      _M_group_int(const char* __grouping, size_t __grouping_size,
     char_type __sep, ios_base& __io, char_type* __new,
     char_type* __cs, int& __len) const;
      void
      _M_pad(char_type __fill, streamsize __w, ios_base& __io,
      char_type* __new, const char_type* __cs, int& __len) const;
      virtual
      ~num_put() { };
      virtual iter_type
      do_put(iter_type __s, ios_base& __io, char_type __fill, bool __v) const;
      virtual iter_type
      do_put(iter_type __s, ios_base& __io, char_type __fill, long __v) const
      { return _M_insert_int(__s, __io, __fill, __v); }
      virtual iter_type
      do_put(iter_type __s, ios_base& __io, char_type __fill,
      unsigned long __v) const
      { return _M_insert_int(__s, __io, __fill, __v); }
      virtual iter_type
      do_put(iter_type __s, ios_base& __io, char_type __fill,
      long long __v) const
      { return _M_insert_int(__s, __io, __fill, __v); }
      virtual iter_type
      do_put(iter_type __s, ios_base& __io, char_type __fill,
      unsigned long long __v) const
      { return _M_insert_int(__s, __io, __fill, __v); }
      virtual iter_type
      do_put(iter_type, ios_base&, char_type, double) const;
      virtual iter_type
      do_put(iter_type, ios_base&, char_type, long double) const;
      virtual iter_type
      do_put(iter_type, ios_base&, char_type, const void*) const;
    };
  template <typename _CharT, typename _OutIter>
    locale::id num_put<_CharT, _OutIter>::id;

  template<typename _CharT>
    inline bool
    isspace(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::space, __c); }
  template<typename _CharT>
    inline bool
    isprint(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::print, __c); }
  template<typename _CharT>
    inline bool
    iscntrl(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::cntrl, __c); }
  template<typename _CharT>
    inline bool
    isupper(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::upper, __c); }
  template<typename _CharT>
    inline bool
    islower(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::lower, __c); }
  template<typename _CharT>
    inline bool
    isalpha(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::alpha, __c); }
  template<typename _CharT>
    inline bool
    isdigit(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::digit, __c); }
  template<typename _CharT>
    inline bool
    ispunct(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::punct, __c); }
  template<typename _CharT>
    inline bool
    isxdigit(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::xdigit, __c); }
  template<typename _CharT>
    inline bool
    isalnum(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::alnum, __c); }
  template<typename _CharT>
    inline bool
    isgraph(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).is(ctype_base::graph, __c); }
  template<typename _CharT>
    inline _CharT
    toupper(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).toupper(__c); }
  template<typename _CharT>
    inline _CharT
    tolower(_CharT __c, const locale& __loc)
    { return use_facet<ctype<_CharT> >(__loc).tolower(__c); }

}
       
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename _Facet>
    struct __use_cache
    {
      const _Facet*
      operator() (const locale& __loc) const;
    };
  template<typename _CharT>
    struct __use_cache<__numpunct_cache<_CharT> >
    {
      const __numpunct_cache<_CharT>*
      operator() (const locale& __loc) const
      {
 const size_t __i = numpunct<_CharT>::id._M_id();
 const locale::facet** __caches = __loc._M_impl->_M_caches;
 if (!__caches[__i])
   {
     __numpunct_cache<_CharT>* __tmp = 0;
     try
       {
  __tmp = new __numpunct_cache<_CharT>;
  __tmp->_M_cache(__loc);
       }
     catch(...)
       {
  delete __tmp;
  throw;
       }
     __loc._M_impl->_M_install_cache(__tmp, __i);
   }
 return static_cast<const __numpunct_cache<_CharT>*>(__caches[__i]);
      }
    };
  template<typename _CharT>
    void
    __numpunct_cache<_CharT>::_M_cache(const locale& __loc)
    {
      _M_allocated = true;
      const numpunct<_CharT>& __np = use_facet<numpunct<_CharT> >(__loc);
      char* __grouping = 0;
      _CharT* __truename = 0;
      _CharT* __falsename = 0;
      try
 {
   _M_grouping_size = __np.grouping().size();
   __grouping = new char[_M_grouping_size];
   __np.grouping().copy(__grouping, _M_grouping_size);
   _M_grouping = __grouping;
   _M_use_grouping = (_M_grouping_size
        && static_cast<signed char>(_M_grouping[0]) > 0
        && (_M_grouping[0]
     != __gnu_cxx::__numeric_traits<char>::__max));
   _M_truename_size = __np.truename().size();
   __truename = new _CharT[_M_truename_size];
   __np.truename().copy(__truename, _M_truename_size);
   _M_truename = __truename;
   _M_falsename_size = __np.falsename().size();
   __falsename = new _CharT[_M_falsename_size];
   __np.falsename().copy(__falsename, _M_falsename_size);
   _M_falsename = __falsename;
   _M_decimal_point = __np.decimal_point();
   _M_thousands_sep = __np.thousands_sep();
   const ctype<_CharT>& __ct = use_facet<ctype<_CharT> >(__loc);
   __ct.widen(__num_base::_S_atoms_out,
       __num_base::_S_atoms_out
       + __num_base::_S_oend, _M_atoms_out);
   __ct.widen(__num_base::_S_atoms_in,
       __num_base::_S_atoms_in
       + __num_base::_S_iend, _M_atoms_in);
 }
      catch(...)
 {
   delete [] __grouping;
   delete [] __truename;
   delete [] __falsename;
   throw;
 }
    }
  __attribute__ ((__pure__)) bool
  __verify_grouping(const char* __grouping, size_t __grouping_size,
      const string& __grouping_tmp) throw ();

  template<typename _CharT, typename _InIter>
    _InIter
    num_get<_CharT, _InIter>::
    _M_extract_float(_InIter __beg, _InIter __end, ios_base& __io,
       ios_base::iostate& __err, string& __xtrc) const
    {
      typedef char_traits<_CharT> __traits_type;
      typedef __numpunct_cache<_CharT> __cache_type;
      __use_cache<__cache_type> __uc;
      const locale& __loc = __io._M_getloc();
      const __cache_type* __lc = __uc(__loc);
      const _CharT* __lit = __lc->_M_atoms_in;
      char_type __c = char_type();
      bool __testeof = __beg == __end;
      if (!__testeof)
 {
   __c = *__beg;
   const bool __plus = __c == __lit[__num_base::_S_iplus];
   if ((__plus || __c == __lit[__num_base::_S_iminus])
       && !(__lc->_M_use_grouping && __c == __lc->_M_thousands_sep)
       && !(__c == __lc->_M_decimal_point))
     {
       __xtrc += __plus ? '+' : '-';
       if (++__beg != __end)
  __c = *__beg;
       else
  __testeof = true;
     }
 }
      bool __found_mantissa = false;
      int __sep_pos = 0;
      while (!__testeof)
 {
   if ((__lc->_M_use_grouping && __c == __lc->_M_thousands_sep)
       || __c == __lc->_M_decimal_point)
     break;
   else if (__c == __lit[__num_base::_S_izero])
     {
       if (!__found_mantissa)
  {
    __xtrc += '0';
    __found_mantissa = true;
  }
       ++__sep_pos;
       if (++__beg != __end)
  __c = *__beg;
       else
  __testeof = true;
     }
   else
     break;
 }
      bool __found_dec = false;
      bool __found_sci = false;
      string __found_grouping;
      if (__lc->_M_use_grouping)
 __found_grouping.reserve(32);
      const char_type* __lit_zero = __lit + __num_base::_S_izero;
      if (!__lc->_M_allocated)
 while (!__testeof)
   {
     const int __digit = _M_find(__lit_zero, 10, __c);
     if (__digit != -1)
       {
  __xtrc += '0' + __digit;
  __found_mantissa = true;
       }
     else if (__c == __lc->_M_decimal_point
       && !__found_dec && !__found_sci)
       {
  __xtrc += '.';
  __found_dec = true;
       }
     else if ((__c == __lit[__num_base::_S_ie]
        || __c == __lit[__num_base::_S_iE])
       && !__found_sci && __found_mantissa)
       {
  __xtrc += 'e';
  __found_sci = true;
  if (++__beg != __end)
    {
      __c = *__beg;
      const bool __plus = __c == __lit[__num_base::_S_iplus];
      if (__plus || __c == __lit[__num_base::_S_iminus])
        __xtrc += __plus ? '+' : '-';
      else
        continue;
    }
  else
    {
      __testeof = true;
      break;
    }
       }
     else
       break;
     if (++__beg != __end)
       __c = *__beg;
     else
       __testeof = true;
   }
      else
 while (!__testeof)
   {
     if (__lc->_M_use_grouping && __c == __lc->_M_thousands_sep)
       {
  if (!__found_dec && !__found_sci)
    {
      if (__sep_pos)
        {
   __found_grouping += static_cast<char>(__sep_pos);
   __sep_pos = 0;
        }
      else
        {
   __xtrc.clear();
   break;
        }
    }
  else
    break;
       }
     else if (__c == __lc->_M_decimal_point)
       {
  if (!__found_dec && !__found_sci)
    {
      if (__found_grouping.size())
        __found_grouping += static_cast<char>(__sep_pos);
      __xtrc += '.';
      __found_dec = true;
    }
  else
    break;
       }
     else
       {
  const char_type* __q =
    __traits_type::find(__lit_zero, 10, __c);
  if (__q)
    {
      __xtrc += '0' + (__q - __lit_zero);
      __found_mantissa = true;
      ++__sep_pos;
    }
  else if ((__c == __lit[__num_base::_S_ie]
     || __c == __lit[__num_base::_S_iE])
    && !__found_sci && __found_mantissa)
    {
      if (__found_grouping.size() && !__found_dec)
        __found_grouping += static_cast<char>(__sep_pos);
      __xtrc += 'e';
      __found_sci = true;
      if (++__beg != __end)
        {
   __c = *__beg;
   const bool __plus = __c == __lit[__num_base::_S_iplus];
   if ((__plus || __c == __lit[__num_base::_S_iminus])
       && !(__lc->_M_use_grouping
     && __c == __lc->_M_thousands_sep)
       && !(__c == __lc->_M_decimal_point))
        __xtrc += __plus ? '+' : '-';
   else
     continue;
        }
      else
        {
   __testeof = true;
   break;
        }
    }
  else
    break;
       }
     if (++__beg != __end)
       __c = *__beg;
     else
       __testeof = true;
   }
      if (__found_grouping.size())
        {
   if (!__found_dec && !__found_sci)
     __found_grouping += static_cast<char>(__sep_pos);
          if (!std::__verify_grouping(__lc->_M_grouping,
          __lc->_M_grouping_size,
          __found_grouping))
     __err = ios_base::failbit;
        }
      return __beg;
    }
  template<typename _CharT, typename _InIter>
    template<typename _ValueT>
      _InIter
      num_get<_CharT, _InIter>::
      _M_extract_int(_InIter __beg, _InIter __end, ios_base& __io,
       ios_base::iostate& __err, _ValueT& __v) const
      {
        typedef char_traits<_CharT> __traits_type;
 using __gnu_cxx::__add_unsigned;
 typedef typename __add_unsigned<_ValueT>::__type __unsigned_type;
 typedef __numpunct_cache<_CharT> __cache_type;
 __use_cache<__cache_type> __uc;
 const locale& __loc = __io._M_getloc();
 const __cache_type* __lc = __uc(__loc);
 const _CharT* __lit = __lc->_M_atoms_in;
 char_type __c = char_type();
 const ios_base::fmtflags __basefield = __io.flags()
                                        & ios_base::basefield;
 const bool __oct = __basefield == ios_base::oct;
 int __base = __oct ? 8 : (__basefield == ios_base::hex ? 16 : 10);
 bool __testeof = __beg == __end;
 bool __negative = false;
 if (!__testeof)
   {
     __c = *__beg;
     __negative = __c == __lit[__num_base::_S_iminus];
     if ((__negative || __c == __lit[__num_base::_S_iplus])
  && !(__lc->_M_use_grouping && __c == __lc->_M_thousands_sep)
  && !(__c == __lc->_M_decimal_point))
       {
  if (++__beg != __end)
    __c = *__beg;
  else
    __testeof = true;
       }
   }
 bool __found_zero = false;
 int __sep_pos = 0;
 while (!__testeof)
   {
     if ((__lc->_M_use_grouping && __c == __lc->_M_thousands_sep)
  || __c == __lc->_M_decimal_point)
       break;
     else if (__c == __lit[__num_base::_S_izero]
       && (!__found_zero || __base == 10))
       {
  __found_zero = true;
  ++__sep_pos;
  if (__basefield == 0)
    __base = 8;
  if (__base == 8)
    __sep_pos = 0;
       }
     else if (__found_zero
       && (__c == __lit[__num_base::_S_ix]
    || __c == __lit[__num_base::_S_iX]))
       {
  if (__basefield == 0)
    __base = 16;
  if (__base == 16)
    {
      __found_zero = false;
      __sep_pos = 0;
    }
  else
    break;
       }
     else
       break;
     if (++__beg != __end)
       {
  __c = *__beg;
  if (!__found_zero)
    break;
       }
     else
       __testeof = true;
   }
 const size_t __len = (__base == 16 ? __num_base::_S_iend
         - __num_base::_S_izero : __base);
 string __found_grouping;
 if (__lc->_M_use_grouping)
   __found_grouping.reserve(32);
 bool __testfail = false;
 bool __testoverflow = false;
 const __unsigned_type __max =
   (__negative && __gnu_cxx::__numeric_traits<_ValueT>::__is_signed)
   ? -__gnu_cxx::__numeric_traits<_ValueT>::__min
   : __gnu_cxx::__numeric_traits<_ValueT>::__max;
 const __unsigned_type __smax = __max / __base;
 __unsigned_type __result = 0;
 int __digit = 0;
 const char_type* __lit_zero = __lit + __num_base::_S_izero;
 if (!__lc->_M_allocated)
   while (!__testeof)
     {
       __digit = _M_find(__lit_zero, __len, __c);
       if (__digit == -1)
  break;
       if (__result > __smax)
  __testoverflow = true;
       else
  {
    __result *= __base;
    __testoverflow |= __result > __max - __digit;
    __result += __digit;
    ++__sep_pos;
  }
       if (++__beg != __end)
  __c = *__beg;
       else
  __testeof = true;
     }
 else
   while (!__testeof)
     {
       if (__lc->_M_use_grouping && __c == __lc->_M_thousands_sep)
  {
    if (__sep_pos)
      {
        __found_grouping += static_cast<char>(__sep_pos);
        __sep_pos = 0;
      }
    else
      {
        __testfail = true;
        break;
      }
  }
       else if (__c == __lc->_M_decimal_point)
  break;
       else
  {
    const char_type* __q =
      __traits_type::find(__lit_zero, __len, __c);
    if (!__q)
      break;
    __digit = __q - __lit_zero;
    if (__digit > 15)
      __digit -= 6;
    if (__result > __smax)
      __testoverflow = true;
    else
      {
        __result *= __base;
        __testoverflow |= __result > __max - __digit;
        __result += __digit;
        ++__sep_pos;
      }
  }
       if (++__beg != __end)
  __c = *__beg;
       else
  __testeof = true;
     }
 if (__found_grouping.size())
   {
     __found_grouping += static_cast<char>(__sep_pos);
     if (!std::__verify_grouping(__lc->_M_grouping,
     __lc->_M_grouping_size,
     __found_grouping))
       __err = ios_base::failbit;
   }
 if ((!__sep_pos && !__found_zero && !__found_grouping.size())
     || __testfail)
   {
     __v = 0;
     __err = ios_base::failbit;
   }
 else if (__testoverflow)
   {
     if (__negative
  && __gnu_cxx::__numeric_traits<_ValueT>::__is_signed)
       __v = __gnu_cxx::__numeric_traits<_ValueT>::__min;
     else
       __v = __gnu_cxx::__numeric_traits<_ValueT>::__max;
     __err = ios_base::failbit;
   }
 else
   __v = __negative ? -__result : __result;
 if (__testeof)
   __err |= ios_base::eofbit;
 return __beg;
      }
  template<typename _CharT, typename _InIter>
    _InIter
    num_get<_CharT, _InIter>::
    do_get(iter_type __beg, iter_type __end, ios_base& __io,
           ios_base::iostate& __err, bool& __v) const
    {
      if (!(__io.flags() & ios_base::boolalpha))
        {
   long __l = -1;
          __beg = _M_extract_int(__beg, __end, __io, __err, __l);
   if (__l == 0 || __l == 1)
     __v = bool(__l);
   else
     {
       __v = true;
       __err = ios_base::failbit;
       if (__beg == __end)
  __err |= ios_base::eofbit;
     }
        }
      else
        {
   typedef __numpunct_cache<_CharT> __cache_type;
   __use_cache<__cache_type> __uc;
   const locale& __loc = __io._M_getloc();
   const __cache_type* __lc = __uc(__loc);
   bool __testf = true;
   bool __testt = true;
   bool __donef = __lc->_M_falsename_size == 0;
   bool __donet = __lc->_M_truename_size == 0;
   bool __testeof = false;
   size_t __n = 0;
   while (!__donef || !__donet)
     {
       if (__beg == __end)
  {
    __testeof = true;
    break;
  }
       const char_type __c = *__beg;
       if (!__donef)
  __testf = __c == __lc->_M_falsename[__n];
       if (!__testf && __donet)
  break;
       if (!__donet)
  __testt = __c == __lc->_M_truename[__n];
       if (!__testt && __donef)
  break;
       if (!__testt && !__testf)
  break;
       ++__n;
       ++__beg;
       __donef = !__testf || __n >= __lc->_M_falsename_size;
       __donet = !__testt || __n >= __lc->_M_truename_size;
     }
   if (__testf && __n == __lc->_M_falsename_size && __n)
     {
       __v = false;
       if (__testt && __n == __lc->_M_truename_size)
  __err = ios_base::failbit;
       else
  __err = __testeof ? ios_base::eofbit : ios_base::goodbit;
     }
   else if (__testt && __n == __lc->_M_truename_size && __n)
     {
       __v = true;
       __err = __testeof ? ios_base::eofbit : ios_base::goodbit;
     }
   else
     {
       __v = false;
       __err = ios_base::failbit;
       if (__testeof)
  __err |= ios_base::eofbit;
     }
 }
      return __beg;
    }
  template<typename _CharT, typename _InIter>
    _InIter
    num_get<_CharT, _InIter>::
    do_get(iter_type __beg, iter_type __end, ios_base& __io,
    ios_base::iostate& __err, float& __v) const
    {
      string __xtrc;
      __xtrc.reserve(32);
      __beg = _M_extract_float(__beg, __end, __io, __err, __xtrc);
      std::__convert_to_v(__xtrc.c_str(), __v, __err, _S_get_c_locale());
      if (__beg == __end)
 __err |= ios_base::eofbit;
      return __beg;
    }
  template<typename _CharT, typename _InIter>
    _InIter
    num_get<_CharT, _InIter>::
    do_get(iter_type __beg, iter_type __end, ios_base& __io,
           ios_base::iostate& __err, double& __v) const
    {
      string __xtrc;
      __xtrc.reserve(32);
      __beg = _M_extract_float(__beg, __end, __io, __err, __xtrc);
      std::__convert_to_v(__xtrc.c_str(), __v, __err, _S_get_c_locale());
      if (__beg == __end)
 __err |= ios_base::eofbit;
      return __beg;
    }
  template<typename _CharT, typename _InIter>
    _InIter
    num_get<_CharT, _InIter>::
    do_get(iter_type __beg, iter_type __end, ios_base& __io,
           ios_base::iostate& __err, long double& __v) const
    {
      string __xtrc;
      __xtrc.reserve(32);
      __beg = _M_extract_float(__beg, __end, __io, __err, __xtrc);
      std::__convert_to_v(__xtrc.c_str(), __v, __err, _S_get_c_locale());
      if (__beg == __end)
 __err |= ios_base::eofbit;
      return __beg;
    }
  template<typename _CharT, typename _InIter>
    _InIter
    num_get<_CharT, _InIter>::
    do_get(iter_type __beg, iter_type __end, ios_base& __io,
           ios_base::iostate& __err, void*& __v) const
    {
      typedef ios_base::fmtflags fmtflags;
      const fmtflags __fmt = __io.flags();
      __io.flags((__fmt & ~ios_base::basefield) | ios_base::hex);
      typedef __gnu_cxx::__conditional_type<(sizeof(void*)
          <= sizeof(unsigned long)),
 unsigned long, unsigned long long>::__type _UIntPtrType;
      _UIntPtrType __ul;
      __beg = _M_extract_int(__beg, __end, __io, __err, __ul);
      __io.flags(__fmt);
      __v = reinterpret_cast<void*>(__ul);
      return __beg;
    }
  template<typename _CharT, typename _OutIter>
    void
    num_put<_CharT, _OutIter>::
    _M_pad(_CharT __fill, streamsize __w, ios_base& __io,
    _CharT* __new, const _CharT* __cs, int& __len) const
    {
      __pad<_CharT, char_traits<_CharT> >::_S_pad(__io, __fill, __new,
        __cs, __w, __len);
      __len = static_cast<int>(__w);
    }

  template<typename _CharT, typename _ValueT>
    int
    __int_to_char(_CharT* __bufend, _ValueT __v, const _CharT* __lit,
    ios_base::fmtflags __flags, bool __dec)
    {
      _CharT* __buf = __bufend;
      if (__builtin_expect(__dec, true))
 {
   do
     {
       *--__buf = __lit[(__v % 10) + __num_base::_S_odigits];
       __v /= 10;
     }
   while (__v != 0);
 }
      else if ((__flags & ios_base::basefield) == ios_base::oct)
 {
   do
     {
       *--__buf = __lit[(__v & 0x7) + __num_base::_S_odigits];
       __v >>= 3;
     }
   while (__v != 0);
 }
      else
 {
   const bool __uppercase = __flags & ios_base::uppercase;
   const int __case_offset = __uppercase ? __num_base::_S_oudigits
                                         : __num_base::_S_odigits;
   do
     {
       *--__buf = __lit[(__v & 0xf) + __case_offset];
       __v >>= 4;
     }
   while (__v != 0);
 }
      return __bufend - __buf;
    }

  template<typename _CharT, typename _OutIter>
    void
    num_put<_CharT, _OutIter>::
    _M_group_int(const char* __grouping, size_t __grouping_size, _CharT __sep,
   ios_base&, _CharT* __new, _CharT* __cs, int& __len) const
    {
      _CharT* __p = std::__add_grouping(__new, __sep, __grouping,
     __grouping_size, __cs, __cs + __len);
      __len = __p - __new;
    }
  template<typename _CharT, typename _OutIter>
    template<typename _ValueT>
      _OutIter
      num_put<_CharT, _OutIter>::
      _M_insert_int(_OutIter __s, ios_base& __io, _CharT __fill,
      _ValueT __v) const
      {
 using __gnu_cxx::__add_unsigned;
 typedef typename __add_unsigned<_ValueT>::__type __unsigned_type;
 typedef __numpunct_cache<_CharT> __cache_type;
 __use_cache<__cache_type> __uc;
 const locale& __loc = __io._M_getloc();
 const __cache_type* __lc = __uc(__loc);
 const _CharT* __lit = __lc->_M_atoms_out;
 const ios_base::fmtflags __flags = __io.flags();
 const int __ilen = 5 * sizeof(_ValueT);
 _CharT* __cs = static_cast<_CharT*>(__builtin_alloca(sizeof(_CharT)
            * __ilen));
 const ios_base::fmtflags __basefield = __flags & ios_base::basefield;
 const bool __dec = (__basefield != ios_base::oct
       && __basefield != ios_base::hex);
 const __unsigned_type __u = ((__v > 0 || !__dec)
         ? __unsigned_type(__v)
         : -__unsigned_type(__v));
  int __len = __int_to_char(__cs + __ilen, __u, __lit, __flags, __dec);
 __cs += __ilen - __len;
 if (__lc->_M_use_grouping)
   {
     _CharT* __cs2 = static_cast<_CharT*>(__builtin_alloca(sizeof(_CharT)
          * (__len + 1)
          * 2));
     _M_group_int(__lc->_M_grouping, __lc->_M_grouping_size,
    __lc->_M_thousands_sep, __io, __cs2 + 2, __cs, __len);
     __cs = __cs2 + 2;
   }
 if (__builtin_expect(__dec, true))
   {
     if (__v >= 0)
       {
  if (bool(__flags & ios_base::showpos)
      && __gnu_cxx::__numeric_traits<_ValueT>::__is_signed)
    *--__cs = __lit[__num_base::_S_oplus], ++__len;
       }
     else
       *--__cs = __lit[__num_base::_S_ominus], ++__len;
   }
 else if (bool(__flags & ios_base::showbase) && __v)
   {
     if (__basefield == ios_base::oct)
       *--__cs = __lit[__num_base::_S_odigits], ++__len;
     else
       {
  const bool __uppercase = __flags & ios_base::uppercase;
  *--__cs = __lit[__num_base::_S_ox + __uppercase];
  *--__cs = __lit[__num_base::_S_odigits];
  __len += 2;
       }
   }
 const streamsize __w = __io.width();
 if (__w > static_cast<streamsize>(__len))
   {
     _CharT* __cs3 = static_cast<_CharT*>(__builtin_alloca(sizeof(_CharT)
          * __w));
     _M_pad(__fill, __w, __io, __cs3, __cs, __len);
     __cs = __cs3;
   }
 __io.width(0);
 return std::__write(__s, __cs, __len);
      }
  template<typename _CharT, typename _OutIter>
    void
    num_put<_CharT, _OutIter>::
    _M_group_float(const char* __grouping, size_t __grouping_size,
     _CharT __sep, const _CharT* __p, _CharT* __new,
     _CharT* __cs, int& __len) const
    {
      const int __declen = __p ? __p - __cs : __len;
      _CharT* __p2 = std::__add_grouping(__new, __sep, __grouping,
      __grouping_size,
      __cs, __cs + __declen);
      int __newlen = __p2 - __new;
      if (__p)
 {
   char_traits<_CharT>::copy(__p2, __p, __len - __declen);
   __newlen += __len - __declen;
 }
      __len = __newlen;
    }
  template<typename _CharT, typename _OutIter>
    template<typename _ValueT>
      _OutIter
      num_put<_CharT, _OutIter>::
      _M_insert_float(_OutIter __s, ios_base& __io, _CharT __fill, char __mod,
         _ValueT __v) const
      {
 typedef __numpunct_cache<_CharT> __cache_type;
 __use_cache<__cache_type> __uc;
 const locale& __loc = __io._M_getloc();
 const __cache_type* __lc = __uc(__loc);
 const streamsize __prec = __io.precision() < 0 ? 6 : __io.precision();
 const int __max_digits =
   __gnu_cxx::__numeric_traits<_ValueT>::__digits10;
 int __len;
 char __fbuf[16];
 __num_base::_S_format_float(__io, __fbuf, __mod);
 int __cs_size = __max_digits * 3;
 char* __cs = static_cast<char*>(__builtin_alloca(__cs_size));
 __len = std::__convert_from_v(_S_get_c_locale(), __cs, __cs_size,
          __fbuf, __prec, __v);
 if (__len >= __cs_size)
   {
     __cs_size = __len + 1;
     __cs = static_cast<char*>(__builtin_alloca(__cs_size));
     __len = std::__convert_from_v(_S_get_c_locale(), __cs, __cs_size,
       __fbuf, __prec, __v);
   }
 const ctype<_CharT>& __ctype = use_facet<ctype<_CharT> >(__loc);
 _CharT* __ws = static_cast<_CharT*>(__builtin_alloca(sizeof(_CharT)
            * __len));
 __ctype.widen(__cs, __cs + __len, __ws);
 _CharT* __wp = 0;
 const char* __p = char_traits<char>::find(__cs, __len, '.');
 if (__p)
   {
     __wp = __ws + (__p - __cs);
     *__wp = __lc->_M_decimal_point;
   }
 if (__lc->_M_use_grouping
     && (__wp || __len < 3 || (__cs[1] <= '9' && __cs[2] <= '9'
          && __cs[1] >= '0' && __cs[2] >= '0')))
   {
     _CharT* __ws2 = static_cast<_CharT*>(__builtin_alloca(sizeof(_CharT)
          * __len * 2));
     streamsize __off = 0;
     if (__cs[0] == '-' || __cs[0] == '+')
       {
  __off = 1;
  __ws2[0] = __ws[0];
  __len -= 1;
       }
     _M_group_float(__lc->_M_grouping, __lc->_M_grouping_size,
      __lc->_M_thousands_sep, __wp, __ws2 + __off,
      __ws + __off, __len);
     __len += __off;
     __ws = __ws2;
   }
 const streamsize __w = __io.width();
 if (__w > static_cast<streamsize>(__len))
   {
     _CharT* __ws3 = static_cast<_CharT*>(__builtin_alloca(sizeof(_CharT)
          * __w));
     _M_pad(__fill, __w, __io, __ws3, __ws, __len);
     __ws = __ws3;
   }
 __io.width(0);
 return std::__write(__s, __ws, __len);
      }
  template<typename _CharT, typename _OutIter>
    _OutIter
    num_put<_CharT, _OutIter>::
    do_put(iter_type __s, ios_base& __io, char_type __fill, bool __v) const
    {
      const ios_base::fmtflags __flags = __io.flags();
      if ((__flags & ios_base::boolalpha) == 0)
        {
          const long __l = __v;
          __s = _M_insert_int(__s, __io, __fill, __l);
        }
      else
        {
   typedef __numpunct_cache<_CharT> __cache_type;
   __use_cache<__cache_type> __uc;
   const locale& __loc = __io._M_getloc();
   const __cache_type* __lc = __uc(__loc);
   const _CharT* __name = __v ? __lc->_M_truename
                              : __lc->_M_falsename;
   int __len = __v ? __lc->_M_truename_size
                   : __lc->_M_falsename_size;
   const streamsize __w = __io.width();
   if (__w > static_cast<streamsize>(__len))
     {
       const streamsize __plen = __w - __len;
       _CharT* __ps
  = static_cast<_CharT*>(__builtin_alloca(sizeof(_CharT)
       * __plen));
       char_traits<_CharT>::assign(__ps, __plen, __fill);
       __io.width(0);
       if ((__flags & ios_base::adjustfield) == ios_base::left)
  {
    __s = std::__write(__s, __name, __len);
    __s = std::__write(__s, __ps, __plen);
  }
       else
  {
    __s = std::__write(__s, __ps, __plen);
    __s = std::__write(__s, __name, __len);
  }
       return __s;
     }
   __io.width(0);
   __s = std::__write(__s, __name, __len);
 }
      return __s;
    }
  template<typename _CharT, typename _OutIter>
    _OutIter
    num_put<_CharT, _OutIter>::
    do_put(iter_type __s, ios_base& __io, char_type __fill, double __v) const
    { return _M_insert_float(__s, __io, __fill, char(), __v); }
  template<typename _CharT, typename _OutIter>
    _OutIter
    num_put<_CharT, _OutIter>::
    do_put(iter_type __s, ios_base& __io, char_type __fill,
    long double __v) const
    { return _M_insert_float(__s, __io, __fill, 'L', __v); }
  template<typename _CharT, typename _OutIter>
    _OutIter
    num_put<_CharT, _OutIter>::
    do_put(iter_type __s, ios_base& __io, char_type __fill,
           const void* __v) const
    {
      const ios_base::fmtflags __flags = __io.flags();
      const ios_base::fmtflags __fmt = ~(ios_base::basefield
      | ios_base::uppercase);
      __io.flags((__flags & __fmt) | (ios_base::hex | ios_base::showbase));
      typedef __gnu_cxx::__conditional_type<(sizeof(const void*)
          <= sizeof(unsigned long)),
 unsigned long, unsigned long long>::__type _UIntPtrType;
      __s = _M_insert_int(__s, __io, __fill,
     reinterpret_cast<_UIntPtrType>(__v));
      __io.flags(__flags);
      return __s;
    }

  template<typename _CharT, typename _Traits>
    void
    __pad<_CharT, _Traits>::_S_pad(ios_base& __io, _CharT __fill,
       _CharT* __news, const _CharT* __olds,
       streamsize __newlen, streamsize __oldlen)
    {
      const size_t __plen = static_cast<size_t>(__newlen - __oldlen);
      const ios_base::fmtflags __adjust = __io.flags() & ios_base::adjustfield;
      if (__adjust == ios_base::left)
 {
   _Traits::copy(__news, __olds, __oldlen);
   _Traits::assign(__news + __oldlen, __plen, __fill);
   return;
 }
      size_t __mod = 0;
      if (__adjust == ios_base::internal)
 {
          const locale& __loc = __io._M_getloc();
   const ctype<_CharT>& __ctype = use_facet<ctype<_CharT> >(__loc);
   if (__ctype.widen('-') == __olds[0]
       || __ctype.widen('+') == __olds[0])
     {
       __news[0] = __olds[0];
       __mod = 1;
       ++__news;
     }
   else if (__ctype.widen('0') == __olds[0]
     && __oldlen > 1
     && (__ctype.widen('x') == __olds[1]
         || __ctype.widen('X') == __olds[1]))
     {
       __news[0] = __olds[0];
       __news[1] = __olds[1];
       __mod = 2;
       __news += 2;
     }
 }
      _Traits::assign(__news, __plen, __fill);
      _Traits::copy(__news + __plen, __olds + __mod, __oldlen - __mod);
    }
  template<typename _CharT>
    _CharT*
    __add_grouping(_CharT* __s, _CharT __sep,
     const char* __gbeg, size_t __gsize,
     const _CharT* __first, const _CharT* __last)
    {
      size_t __idx = 0;
      size_t __ctr = 0;
      while (__last - __first > __gbeg[__idx]
      && static_cast<signed char>(__gbeg[__idx]) > 0
      && __gbeg[__idx] != __gnu_cxx::__numeric_traits<char>::__max)
 {
   __last -= __gbeg[__idx];
   __idx < __gsize - 1 ? ++__idx : ++__ctr;
 }
      while (__first != __last)
 *__s++ = *__first++;
      while (__ctr--)
 {
   *__s++ = __sep;
   for (char __i = __gbeg[__idx]; __i > 0; --__i)
     *__s++ = *__first++;
 }
      while (__idx--)
 {
   *__s++ = __sep;
   for (char __i = __gbeg[__idx]; __i > 0; --__i)
     *__s++ = *__first++;
 }
      return __s;
    }
  extern template class numpunct<char>;
  extern template class numpunct_byname<char>;
  extern template class num_get<char>;
  extern template class num_put<char>;
  extern template class ctype_byname<char>;
  extern template
    const ctype<char>&
    use_facet<ctype<char> >(const locale&);
  extern template
    const numpunct<char>&
    use_facet<numpunct<char> >(const locale&);
  extern template
    const num_put<char>&
    use_facet<num_put<char> >(const locale&);
  extern template
    const num_get<char>&
    use_facet<num_get<char> >(const locale&);
  extern template
    bool
    has_facet<ctype<char> >(const locale&);
  extern template
    bool
    has_facet<numpunct<char> >(const locale&);
  extern template
    bool
    has_facet<num_put<char> >(const locale&);
  extern template
    bool
    has_facet<num_get<char> >(const locale&);
  extern template class numpunct<wchar_t>;
  extern template class numpunct_byname<wchar_t>;
  extern template class num_get<wchar_t>;
  extern template class num_put<wchar_t>;
  extern template class ctype_byname<wchar_t>;
  extern template
    const ctype<wchar_t>&
    use_facet<ctype<wchar_t> >(const locale&);
  extern template
    const numpunct<wchar_t>&
    use_facet<numpunct<wchar_t> >(const locale&);
  extern template
    const num_put<wchar_t>&
    use_facet<num_put<wchar_t> >(const locale&);
  extern template
    const num_get<wchar_t>&
    use_facet<num_get<wchar_t> >(const locale&);
 extern template
    bool
    has_facet<ctype<wchar_t> >(const locale&);
  extern template
    bool
    has_facet<numpunct<wchar_t> >(const locale&);
  extern template
    bool
    has_facet<num_put<wchar_t> >(const locale&);
  extern template
    bool
    has_facet<num_get<wchar_t> >(const locale&);

}
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename _Facet>
    inline const _Facet&
    __check_facet(const _Facet* __f)
    {
      if (!__f)
 __throw_bad_cast();
      return *__f;
    }
  template<typename _CharT, typename _Traits>
    class basic_ios : public ios_base
    {
    public:
      typedef _CharT char_type;
      typedef typename _Traits::int_type int_type;
      typedef typename _Traits::pos_type pos_type;
      typedef typename _Traits::off_type off_type;
      typedef _Traits traits_type;
      typedef ctype<_CharT> __ctype_type;
      typedef num_put<_CharT, ostreambuf_iterator<_CharT, _Traits> >
           __num_put_type;
      typedef num_get<_CharT, istreambuf_iterator<_CharT, _Traits> >
           __num_get_type;
    protected:
      basic_ostream<_CharT, _Traits>* _M_tie;
      mutable char_type _M_fill;
      mutable bool _M_fill_init;
      basic_streambuf<_CharT, _Traits>* _M_streambuf;
      const __ctype_type* _M_ctype;
      const __num_put_type* _M_num_put;
      const __num_get_type* _M_num_get;
    public:
      operator void*() const
      { return this->fail() ? 0 : const_cast<basic_ios*>(this); }
      bool
      operator!() const
      { return this->fail(); }
      iostate
      rdstate() const
      { return _M_streambuf_state; }
      void
      clear(iostate __state = goodbit);
      void
      setstate(iostate __state)
      { this->clear(this->rdstate() | __state); }
      void
      _M_setstate(iostate __state)
      {
 _M_streambuf_state |= __state;
 if (this->exceptions() & __state)
   throw;
      }
      bool
      good() const
      { return this->rdstate() == 0; }
      bool
      eof() const
      { return (this->rdstate() & eofbit) != 0; }
      bool
      fail() const
      { return (this->rdstate() & (badbit | failbit)) != 0; }
      bool
      bad() const
      { return (this->rdstate() & badbit) != 0; }
      iostate
      exceptions() const
      { return _M_exception; }
      void
      exceptions(iostate __except)
      {
        _M_exception = __except;
        this->clear(_M_streambuf_state);
      }
      explicit
      basic_ios(basic_streambuf<_CharT, _Traits>* __sb)
      : ios_base(), _M_tie(0), _M_fill(), _M_fill_init(false), _M_streambuf(0),
 _M_ctype(0), _M_num_put(0), _M_num_get(0)
      { this->init(__sb); }
      virtual
      ~basic_ios() { }
      basic_ostream<_CharT, _Traits>*
      tie() const
      { return _M_tie; }
      basic_ostream<_CharT, _Traits>*
      tie(basic_ostream<_CharT, _Traits>* __tiestr)
      {
        basic_ostream<_CharT, _Traits>* __old = _M_tie;
        _M_tie = __tiestr;
        return __old;
      }
      basic_streambuf<_CharT, _Traits>*
      rdbuf() const
      { return _M_streambuf; }
      basic_streambuf<_CharT, _Traits>*
      rdbuf(basic_streambuf<_CharT, _Traits>* __sb);
      basic_ios&
      copyfmt(const basic_ios& __rhs);
      char_type
      fill() const
      {
 if (!_M_fill_init)
   {
     _M_fill = this->widen(' ');
     _M_fill_init = true;
   }
 return _M_fill;
      }
      char_type
      fill(char_type __ch)
      {
 char_type __old = this->fill();
 _M_fill = __ch;
 return __old;
      }
      locale
      imbue(const locale& __loc);
      char
      narrow(char_type __c, char __dfault) const
      { return __check_facet(_M_ctype).narrow(__c, __dfault); }
      char_type
      widen(char __c) const
      { return __check_facet(_M_ctype).widen(__c); }
    protected:
      basic_ios()
      : ios_base(), _M_tie(0), _M_fill(char_type()), _M_fill_init(false),
 _M_streambuf(0), _M_ctype(0), _M_num_put(0), _M_num_get(0)
      { }
      void
      init(basic_streambuf<_CharT, _Traits>* __sb);
      void
      _M_cache_locale(const locale& __loc);
    };

}
       
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename _CharT, typename _Traits>
    void
    basic_ios<_CharT, _Traits>::clear(iostate __state)
    {
      if (this->rdbuf())
 _M_streambuf_state = __state;
      else
   _M_streambuf_state = __state | badbit;
      if (this->exceptions() & this->rdstate())
 __throw_ios_failure(("basic_ios::clear"));
    }
  template<typename _CharT, typename _Traits>
    basic_streambuf<_CharT, _Traits>*
    basic_ios<_CharT, _Traits>::rdbuf(basic_streambuf<_CharT, _Traits>* __sb)
    {
      basic_streambuf<_CharT, _Traits>* __old = _M_streambuf;
      _M_streambuf = __sb;
      this->clear();
      return __old;
    }
  template<typename _CharT, typename _Traits>
    basic_ios<_CharT, _Traits>&
    basic_ios<_CharT, _Traits>::copyfmt(const basic_ios& __rhs)
    {
      if (this != &__rhs)
 {
   _Words* __words = (__rhs._M_word_size <= _S_local_word_size) ?
                      _M_local_word : new _Words[__rhs._M_word_size];
   _Callback_list* __cb = __rhs._M_callbacks;
   if (__cb)
     __cb->_M_add_reference();
   _M_call_callbacks(erase_event);
   if (_M_word != _M_local_word)
     {
       delete [] _M_word;
       _M_word = 0;
     }
   _M_dispose_callbacks();
   _M_callbacks = __cb;
   for (int __i = 0; __i < __rhs._M_word_size; ++__i)
     __words[__i] = __rhs._M_word[__i];
   _M_word = __words;
   _M_word_size = __rhs._M_word_size;
   this->flags(__rhs.flags());
   this->width(__rhs.width());
   this->precision(__rhs.precision());
   this->tie(__rhs.tie());
   this->fill(__rhs.fill());
   _M_ios_locale = __rhs.getloc();
   _M_cache_locale(_M_ios_locale);
   _M_call_callbacks(copyfmt_event);
   this->exceptions(__rhs.exceptions());
 }
      return *this;
    }
  template<typename _CharT, typename _Traits>
    locale
    basic_ios<_CharT, _Traits>::imbue(const locale& __loc)
    {
      locale __old(this->getloc());
      ios_base::imbue(__loc);
      _M_cache_locale(__loc);
      if (this->rdbuf() != 0)
 this->rdbuf()->pubimbue(__loc);
      return __old;
    }
  template<typename _CharT, typename _Traits>
    void
    basic_ios<_CharT, _Traits>::init(basic_streambuf<_CharT, _Traits>* __sb)
    {
      ios_base::_M_init();
      _M_cache_locale(_M_ios_locale);
      _M_fill = _CharT();
      _M_fill_init = false;
      _M_tie = 0;
      _M_exception = goodbit;
      _M_streambuf = __sb;
      _M_streambuf_state = __sb ? goodbit : badbit;
    }
  template<typename _CharT, typename _Traits>
    void
    basic_ios<_CharT, _Traits>::_M_cache_locale(const locale& __loc)
    {
      if (__builtin_expect(has_facet<__ctype_type>(__loc), true))
 _M_ctype = &use_facet<__ctype_type>(__loc);
      else
 _M_ctype = 0;
      if (__builtin_expect(has_facet<__num_put_type>(__loc), true))
 _M_num_put = &use_facet<__num_put_type>(__loc);
      else
 _M_num_put = 0;
      if (__builtin_expect(has_facet<__num_get_type>(__loc), true))
 _M_num_get = &use_facet<__num_get_type>(__loc);
      else
 _M_num_get = 0;
    }
  extern template class basic_ios<char>;
  extern template class basic_ios<wchar_t>;

}
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename _CharT, typename _Traits>
    class basic_ostream : virtual public basic_ios<_CharT, _Traits>
    {
    public:
      typedef _CharT char_type;
      typedef typename _Traits::int_type int_type;
      typedef typename _Traits::pos_type pos_type;
      typedef typename _Traits::off_type off_type;
      typedef _Traits traits_type;
      typedef basic_streambuf<_CharT, _Traits> __streambuf_type;
      typedef basic_ios<_CharT, _Traits> __ios_type;
      typedef basic_ostream<_CharT, _Traits> __ostream_type;
      typedef num_put<_CharT, ostreambuf_iterator<_CharT, _Traits> >
             __num_put_type;
      typedef ctype<_CharT> __ctype_type;
      explicit
      basic_ostream(__streambuf_type* __sb)
      { this->init(__sb); }
      virtual
      ~basic_ostream() { }
      class sentry;
      friend class sentry;
      __ostream_type&
      operator<<(__ostream_type& (*__pf)(__ostream_type&))
      {
 return __pf(*this);
      }
      __ostream_type&
      operator<<(__ios_type& (*__pf)(__ios_type&))
      {
 __pf(*this);
 return *this;
      }
      __ostream_type&
      operator<<(ios_base& (*__pf) (ios_base&))
      {
 __pf(*this);
 return *this;
      }
      __ostream_type&
      operator<<(long __n)
      { return _M_insert(__n); }
      __ostream_type&
      operator<<(unsigned long __n)
      { return _M_insert(__n); }
      __ostream_type&
      operator<<(bool __n)
      { return _M_insert(__n); }
      __ostream_type&
      operator<<(short __n);
      __ostream_type&
      operator<<(unsigned short __n)
      {
 return _M_insert(static_cast<unsigned long>(__n));
      }
      __ostream_type&
      operator<<(int __n);
      __ostream_type&
      operator<<(unsigned int __n)
      {
 return _M_insert(static_cast<unsigned long>(__n));
      }
      __ostream_type&
      operator<<(long long __n)
      { return _M_insert(__n); }
      __ostream_type&
      operator<<(unsigned long long __n)
      { return _M_insert(__n); }
      __ostream_type&
      operator<<(double __f)
      { return _M_insert(__f); }
      __ostream_type&
      operator<<(float __f)
      {
 return _M_insert(static_cast<double>(__f));
      }
      __ostream_type&
      operator<<(long double __f)
      { return _M_insert(__f); }
      __ostream_type&
      operator<<(const void* __p)
      { return _M_insert(__p); }
      __ostream_type&
      operator<<(__streambuf_type* __sb);
      __ostream_type&
      put(char_type __c);
      void
      _M_write(const char_type* __s, streamsize __n)
      {
 const streamsize __put = this->rdbuf()->sputn(__s, __n);
 if (__put != __n)
   this->setstate(ios_base::badbit);
      }
      __ostream_type&
      write(const char_type* __s, streamsize __n);
      __ostream_type&
      flush();
      pos_type
      tellp();
      __ostream_type&
      seekp(pos_type);
       __ostream_type&
      seekp(off_type, ios_base::seekdir);
    protected:
      basic_ostream()
      { this->init(0); }
      template<typename _ValueT>
 __ostream_type&
 _M_insert(_ValueT __v);
    };
  template <typename _CharT, typename _Traits>
    class basic_ostream<_CharT, _Traits>::sentry
    {
      bool _M_ok;
      basic_ostream<_CharT, _Traits>& _M_os;
    public:
      explicit
      sentry(basic_ostream<_CharT, _Traits>& __os);
      ~sentry()
      {
 if (bool(_M_os.flags() & ios_base::unitbuf) && !uncaught_exception())
   {
     if (_M_os.rdbuf() && _M_os.rdbuf()->pubsync() == -1)
       _M_os.setstate(ios_base::badbit);
   }
      }
      explicit
      operator bool() const
      { return _M_ok; }
    };
  template<typename _CharT, typename _Traits>
    inline basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& __out, _CharT __c)
    { return __ostream_insert(__out, &__c, 1); }
  template<typename _CharT, typename _Traits>
    inline basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& __out, char __c)
    { return (__out << __out.widen(__c)); }
  template <class _Traits>
    inline basic_ostream<char, _Traits>&
    operator<<(basic_ostream<char, _Traits>& __out, char __c)
    { return __ostream_insert(__out, &__c, 1); }
  template<class _Traits>
    inline basic_ostream<char, _Traits>&
    operator<<(basic_ostream<char, _Traits>& __out, signed char __c)
    { return (__out << static_cast<char>(__c)); }
  template<class _Traits>
    inline basic_ostream<char, _Traits>&
    operator<<(basic_ostream<char, _Traits>& __out, unsigned char __c)
    { return (__out << static_cast<char>(__c)); }
  template<typename _CharT, typename _Traits>
    inline basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& __out, const _CharT* __s)
    {
      if (!__s)
 __out.setstate(ios_base::badbit);
      else
 __ostream_insert(__out, __s,
    static_cast<streamsize>(_Traits::length(__s)));
      return __out;
    }
  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits> &
    operator<<(basic_ostream<_CharT, _Traits>& __out, const char* __s);
  template<class _Traits>
    inline basic_ostream<char, _Traits>&
    operator<<(basic_ostream<char, _Traits>& __out, const char* __s)
    {
      if (!__s)
 __out.setstate(ios_base::badbit);
      else
 __ostream_insert(__out, __s,
    static_cast<streamsize>(_Traits::length(__s)));
      return __out;
    }
  template<class _Traits>
    inline basic_ostream<char, _Traits>&
    operator<<(basic_ostream<char, _Traits>& __out, const signed char* __s)
    { return (__out << reinterpret_cast<const char*>(__s)); }
  template<class _Traits>
    inline basic_ostream<char, _Traits> &
    operator<<(basic_ostream<char, _Traits>& __out, const unsigned char* __s)
    { return (__out << reinterpret_cast<const char*>(__s)); }
  template<typename _CharT, typename _Traits>
    inline basic_ostream<_CharT, _Traits>&
    endl(basic_ostream<_CharT, _Traits>& __os)
    { return flush(__os.put(__os.widen('\n'))); }
  template<typename _CharT, typename _Traits>
    inline basic_ostream<_CharT, _Traits>&
    ends(basic_ostream<_CharT, _Traits>& __os)
    { return __os.put(_CharT()); }
  template<typename _CharT, typename _Traits>
    inline basic_ostream<_CharT, _Traits>&
    flush(basic_ostream<_CharT, _Traits>& __os)
    { return __os.flush(); }
  template<typename _CharT, typename _Traits, typename _Tp>
    inline basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>&& __os, const _Tp& __x)
    { return (__os << __x); }

}
       
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>::sentry::
    sentry(basic_ostream<_CharT, _Traits>& __os)
    : _M_ok(false), _M_os(__os)
    {
      if (__os.tie() && __os.good())
 __os.tie()->flush();
      if (__os.good())
 _M_ok = true;
      else
 __os.setstate(ios_base::failbit);
    }
  template<typename _CharT, typename _Traits>
    template<typename _ValueT>
      basic_ostream<_CharT, _Traits>&
      basic_ostream<_CharT, _Traits>::
      _M_insert(_ValueT __v)
      {
 sentry __cerb(*this);
 if (__cerb)
   {
     ios_base::iostate __err = ios_base::goodbit;
     try
       {
  const __num_put_type& __np = __check_facet(this->_M_num_put);
  if (__np.put(*this, *this, this->fill(), __v).failed())
    __err |= ios_base::badbit;
       }
     catch(__cxxabiv1::__forced_unwind&)
       {
  this->_M_setstate(ios_base::badbit);
  throw;
       }
     catch(...)
       { this->_M_setstate(ios_base::badbit); }
     if (__err)
       this->setstate(__err);
   }
 return *this;
      }
  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    basic_ostream<_CharT, _Traits>::
    operator<<(short __n)
    {
      const ios_base::fmtflags __fmt = this->flags() & ios_base::basefield;
      if (__fmt == ios_base::oct || __fmt == ios_base::hex)
 return _M_insert(static_cast<long>(static_cast<unsigned short>(__n)));
      else
 return _M_insert(static_cast<long>(__n));
    }
  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    basic_ostream<_CharT, _Traits>::
    operator<<(int __n)
    {
      const ios_base::fmtflags __fmt = this->flags() & ios_base::basefield;
      if (__fmt == ios_base::oct || __fmt == ios_base::hex)
 return _M_insert(static_cast<long>(static_cast<unsigned int>(__n)));
      else
 return _M_insert(static_cast<long>(__n));
    }
  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    basic_ostream<_CharT, _Traits>::
    operator<<(__streambuf_type* __sbin)
    {
      ios_base::iostate __err = ios_base::goodbit;
      sentry __cerb(*this);
      if (__cerb && __sbin)
 {
   try
     {
       if (!__copy_streambufs(__sbin, this->rdbuf()))
  __err |= ios_base::failbit;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::failbit); }
 }
      else if (!__sbin)
 __err |= ios_base::badbit;
      if (__err)
 this->setstate(__err);
      return *this;
    }
  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    basic_ostream<_CharT, _Traits>::
    put(char_type __c)
    {
      sentry __cerb(*this);
      if (__cerb)
 {
   ios_base::iostate __err = ios_base::goodbit;
   try
     {
       const int_type __put = this->rdbuf()->sputc(__c);
       if (traits_type::eq_int_type(__put, traits_type::eof()))
  __err |= ios_base::badbit;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
   if (__err)
     this->setstate(__err);
 }
      return *this;
    }
  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    basic_ostream<_CharT, _Traits>::
    write(const _CharT* __s, streamsize __n)
    {
      sentry __cerb(*this);
      if (__cerb)
 {
   try
     { _M_write(__s, __n); }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
 }
      return *this;
    }
  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    basic_ostream<_CharT, _Traits>::
    flush()
    {
      ios_base::iostate __err = ios_base::goodbit;
      try
 {
   if (this->rdbuf() && this->rdbuf()->pubsync() == -1)
     __err |= ios_base::badbit;
 }
      catch(__cxxabiv1::__forced_unwind&)
 {
   this->_M_setstate(ios_base::badbit);
   throw;
 }
      catch(...)
 { this->_M_setstate(ios_base::badbit); }
      if (__err)
 this->setstate(__err);
      return *this;
    }
  template<typename _CharT, typename _Traits>
    typename basic_ostream<_CharT, _Traits>::pos_type
    basic_ostream<_CharT, _Traits>::
    tellp()
    {
      pos_type __ret = pos_type(-1);
      try
 {
   if (!this->fail())
     __ret = this->rdbuf()->pubseekoff(0, ios_base::cur, ios_base::out);
 }
      catch(__cxxabiv1::__forced_unwind&)
 {
   this->_M_setstate(ios_base::badbit);
   throw;
 }
      catch(...)
 { this->_M_setstate(ios_base::badbit); }
      return __ret;
    }
  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    basic_ostream<_CharT, _Traits>::
    seekp(pos_type __pos)
    {
      ios_base::iostate __err = ios_base::goodbit;
      try
 {
   if (!this->fail())
     {
       const pos_type __p = this->rdbuf()->pubseekpos(__pos,
            ios_base::out);
       if (__p == pos_type(off_type(-1)))
  __err |= ios_base::failbit;
     }
 }
      catch(__cxxabiv1::__forced_unwind&)
 {
   this->_M_setstate(ios_base::badbit);
   throw;
 }
      catch(...)
 { this->_M_setstate(ios_base::badbit); }
      if (__err)
 this->setstate(__err);
      return *this;
    }
  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    basic_ostream<_CharT, _Traits>::
    seekp(off_type __off, ios_base::seekdir __dir)
    {
      ios_base::iostate __err = ios_base::goodbit;
      try
 {
   if (!this->fail())
     {
       const pos_type __p = this->rdbuf()->pubseekoff(__off, __dir,
            ios_base::out);
       if (__p == pos_type(off_type(-1)))
  __err |= ios_base::failbit;
     }
 }
      catch(__cxxabiv1::__forced_unwind&)
 {
   this->_M_setstate(ios_base::badbit);
   throw;
 }
      catch(...)
 { this->_M_setstate(ios_base::badbit); }
      if (__err)
 this->setstate(__err);
      return *this;
    }
  template<typename _CharT, typename _Traits>
    basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& __out, const char* __s)
    {
      if (!__s)
 __out.setstate(ios_base::badbit);
      else
 {
   const size_t __clen = char_traits<char>::length(__s);
   try
     {
       struct __ptr_guard
       {
  _CharT *__p;
  __ptr_guard (_CharT *__ip): __p(__ip) { }
  ~__ptr_guard() { delete[] __p; }
  _CharT* __get() { return __p; }
       } __pg (new _CharT[__clen]);
       _CharT *__ws = __pg.__get();
       for (size_t __i = 0; __i < __clen; ++__i)
  __ws[__i] = __out.widen(__s[__i]);
       __ostream_insert(__out, __ws, __clen);
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       __out._M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { __out._M_setstate(ios_base::badbit); }
 }
      return __out;
    }
  extern template class basic_ostream<char>;
  extern template ostream& endl(ostream&);
  extern template ostream& ends(ostream&);
  extern template ostream& flush(ostream&);
  extern template ostream& operator<<(ostream&, char);
  extern template ostream& operator<<(ostream&, unsigned char);
  extern template ostream& operator<<(ostream&, signed char);
  extern template ostream& operator<<(ostream&, const char*);
  extern template ostream& operator<<(ostream&, const unsigned char*);
  extern template ostream& operator<<(ostream&, const signed char*);
  extern template ostream& ostream::_M_insert(long);
  extern template ostream& ostream::_M_insert(unsigned long);
  extern template ostream& ostream::_M_insert(bool);
  extern template ostream& ostream::_M_insert(long long);
  extern template ostream& ostream::_M_insert(unsigned long long);
  extern template ostream& ostream::_M_insert(double);
  extern template ostream& ostream::_M_insert(long double);
  extern template ostream& ostream::_M_insert(const void*);
  extern template class basic_ostream<wchar_t>;
  extern template wostream& endl(wostream&);
  extern template wostream& ends(wostream&);
  extern template wostream& flush(wostream&);
  extern template wostream& operator<<(wostream&, wchar_t);
  extern template wostream& operator<<(wostream&, char);
  extern template wostream& operator<<(wostream&, const wchar_t*);
  extern template wostream& operator<<(wostream&, const char*);
  extern template wostream& wostream::_M_insert(long);
  extern template wostream& wostream::_M_insert(unsigned long);
  extern template wostream& wostream::_M_insert(bool);
  extern template wostream& wostream::_M_insert(long long);
  extern template wostream& wostream::_M_insert(unsigned long long);
  extern template wostream& wostream::_M_insert(double);
  extern template wostream& wostream::_M_insert(long double);
  extern template wostream& wostream::_M_insert(const void*);

}
       
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename _CharT, typename _Traits>
    class basic_istream : virtual public basic_ios<_CharT, _Traits>
    {
    public:
      typedef _CharT char_type;
      typedef typename _Traits::int_type int_type;
      typedef typename _Traits::pos_type pos_type;
      typedef typename _Traits::off_type off_type;
      typedef _Traits traits_type;
      typedef basic_streambuf<_CharT, _Traits> __streambuf_type;
      typedef basic_ios<_CharT, _Traits> __ios_type;
      typedef basic_istream<_CharT, _Traits> __istream_type;
      typedef num_get<_CharT, istreambuf_iterator<_CharT, _Traits> >
        __num_get_type;
      typedef ctype<_CharT> __ctype_type;
    protected:
      streamsize _M_gcount;
    public:
      explicit
      basic_istream(__streambuf_type* __sb)
      : _M_gcount(streamsize(0))
      { this->init(__sb); }
      virtual
      ~basic_istream()
      { _M_gcount = streamsize(0); }
      class sentry;
      friend class sentry;
      __istream_type&
      operator>>(__istream_type& (*__pf)(__istream_type&))
      { return __pf(*this); }
      __istream_type&
      operator>>(__ios_type& (*__pf)(__ios_type&))
      {
 __pf(*this);
 return *this;
      }
      __istream_type&
      operator>>(ios_base& (*__pf)(ios_base&))
      {
 __pf(*this);
 return *this;
      }
      __istream_type&
      operator>>(bool& __n)
      { return _M_extract(__n); }
      __istream_type&
      operator>>(short& __n);
      __istream_type&
      operator>>(unsigned short& __n)
      { return _M_extract(__n); }
      __istream_type&
      operator>>(int& __n);
      __istream_type&
      operator>>(unsigned int& __n)
      { return _M_extract(__n); }
      __istream_type&
      operator>>(long& __n)
      { return _M_extract(__n); }
      __istream_type&
      operator>>(unsigned long& __n)
      { return _M_extract(__n); }
      __istream_type&
      operator>>(long long& __n)
      { return _M_extract(__n); }
      __istream_type&
      operator>>(unsigned long long& __n)
      { return _M_extract(__n); }
      __istream_type&
      operator>>(float& __f)
      { return _M_extract(__f); }
      __istream_type&
      operator>>(double& __f)
      { return _M_extract(__f); }
      __istream_type&
      operator>>(long double& __f)
      { return _M_extract(__f); }
      __istream_type&
      operator>>(void*& __p)
      { return _M_extract(__p); }
      __istream_type&
      operator>>(__streambuf_type* __sb);
      streamsize
      gcount() const
      { return _M_gcount; }
      int_type
      get();
      __istream_type&
      get(char_type& __c);
      __istream_type&
      get(char_type* __s, streamsize __n, char_type __delim);
      __istream_type&
      get(char_type* __s, streamsize __n)
      { return this->get(__s, __n, this->widen('\n')); }
      __istream_type&
      get(__streambuf_type& __sb, char_type __delim);
      __istream_type&
      get(__streambuf_type& __sb)
      { return this->get(__sb, this->widen('\n')); }
      __istream_type&
      getline(char_type* __s, streamsize __n, char_type __delim);
      __istream_type&
      getline(char_type* __s, streamsize __n)
      { return this->getline(__s, __n, this->widen('\n')); }
      __istream_type&
      ignore(streamsize __n, int_type __delim);
      __istream_type&
      ignore(streamsize __n);
      __istream_type&
      ignore();
      int_type
      peek();
      __istream_type&
      read(char_type* __s, streamsize __n);
      streamsize
      readsome(char_type* __s, streamsize __n);
      __istream_type&
      putback(char_type __c);
      __istream_type&
      unget();
      int
      sync();
      pos_type
      tellg();
      __istream_type&
      seekg(pos_type);
      __istream_type&
      seekg(off_type, ios_base::seekdir);
    protected:
      basic_istream()
      : _M_gcount(streamsize(0))
      { this->init(0); }
      template<typename _ValueT>
 __istream_type&
 _M_extract(_ValueT& __v);
    };
  template<>
    basic_istream<char>&
    basic_istream<char>::
    getline(char_type* __s, streamsize __n, char_type __delim);
  template<>
    basic_istream<char>&
    basic_istream<char>::
    ignore(streamsize __n);
  template<>
    basic_istream<char>&
    basic_istream<char>::
    ignore(streamsize __n, int_type __delim);
  template<>
    basic_istream<wchar_t>&
    basic_istream<wchar_t>::
    getline(char_type* __s, streamsize __n, char_type __delim);
  template<>
    basic_istream<wchar_t>&
    basic_istream<wchar_t>::
    ignore(streamsize __n);
  template<>
    basic_istream<wchar_t>&
    basic_istream<wchar_t>::
    ignore(streamsize __n, int_type __delim);
  template<typename _CharT, typename _Traits>
    class basic_istream<_CharT, _Traits>::sentry
    {
      bool _M_ok;
    public:
      typedef _Traits traits_type;
      typedef basic_streambuf<_CharT, _Traits> __streambuf_type;
      typedef basic_istream<_CharT, _Traits> __istream_type;
      typedef typename __istream_type::__ctype_type __ctype_type;
      typedef typename _Traits::int_type __int_type;
      explicit
      sentry(basic_istream<_CharT, _Traits>& __is, bool __noskipws = false);
      explicit
      operator bool() const
      { return _M_ok; }
    };
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>& __in, _CharT& __c);
  template<class _Traits>
    inline basic_istream<char, _Traits>&
    operator>>(basic_istream<char, _Traits>& __in, unsigned char& __c)
    { return (__in >> reinterpret_cast<char&>(__c)); }
  template<class _Traits>
    inline basic_istream<char, _Traits>&
    operator>>(basic_istream<char, _Traits>& __in, signed char& __c)
    { return (__in >> reinterpret_cast<char&>(__c)); }
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>& __in, _CharT* __s);
  template<>
    basic_istream<char>&
    operator>>(basic_istream<char>& __in, char* __s);
  template<class _Traits>
    inline basic_istream<char, _Traits>&
    operator>>(basic_istream<char, _Traits>& __in, unsigned char* __s)
    { return (__in >> reinterpret_cast<char*>(__s)); }
  template<class _Traits>
    inline basic_istream<char, _Traits>&
    operator>>(basic_istream<char, _Traits>& __in, signed char* __s)
    { return (__in >> reinterpret_cast<char*>(__s)); }
  template<typename _CharT, typename _Traits>
    class basic_iostream
    : public basic_istream<_CharT, _Traits>,
      public basic_ostream<_CharT, _Traits>
    {
    public:
      typedef _CharT char_type;
      typedef typename _Traits::int_type int_type;
      typedef typename _Traits::pos_type pos_type;
      typedef typename _Traits::off_type off_type;
      typedef _Traits traits_type;
      typedef basic_istream<_CharT, _Traits> __istream_type;
      typedef basic_ostream<_CharT, _Traits> __ostream_type;
      explicit
      basic_iostream(basic_streambuf<_CharT, _Traits>* __sb)
      : __istream_type(__sb), __ostream_type(__sb) { }
      virtual
      ~basic_iostream() { }
    protected:
      basic_iostream()
      : __istream_type(), __ostream_type() { }
    };
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    ws(basic_istream<_CharT, _Traits>& __is);
  template<typename _CharT, typename _Traits, typename _Tp>
    inline basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>&& __is, _Tp& __x)
    { return (__is >> __x); }

}
       
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>::sentry::
    sentry(basic_istream<_CharT, _Traits>& __in, bool __noskip) : _M_ok(false)
    {
      ios_base::iostate __err = ios_base::goodbit;
      if (__in.good())
 {
   if (__in.tie())
     __in.tie()->flush();
   if (!__noskip && bool(__in.flags() & ios_base::skipws))
     {
       const __int_type __eof = traits_type::eof();
       __streambuf_type* __sb = __in.rdbuf();
       __int_type __c = __sb->sgetc();
       const __ctype_type& __ct = __check_facet(__in._M_ctype);
       while (!traits_type::eq_int_type(__c, __eof)
       && __ct.is(ctype_base::space,
    traits_type::to_char_type(__c)))
  __c = __sb->snextc();
       if (traits_type::eq_int_type(__c, __eof))
  __err |= ios_base::eofbit;
     }
 }
      if (__in.good() && __err == ios_base::goodbit)
 _M_ok = true;
      else
 {
   __err |= ios_base::failbit;
   __in.setstate(__err);
 }
    }
  template<typename _CharT, typename _Traits>
    template<typename _ValueT>
      basic_istream<_CharT, _Traits>&
      basic_istream<_CharT, _Traits>::
      _M_extract(_ValueT& __v)
      {
 sentry __cerb(*this, false);
 if (__cerb)
   {
     ios_base::iostate __err = ios_base::goodbit;
     try
       {
  const __num_get_type& __ng = __check_facet(this->_M_num_get);
  __ng.get(*this, 0, *this, __err, __v);
       }
     catch(__cxxabiv1::__forced_unwind&)
       {
  this->_M_setstate(ios_base::badbit);
  throw;
       }
     catch(...)
       { this->_M_setstate(ios_base::badbit); }
     if (__err)
       this->setstate(__err);
   }
 return *this;
      }
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    operator>>(short& __n)
    {
      sentry __cerb(*this, false);
      if (__cerb)
 {
   ios_base::iostate __err = ios_base::goodbit;
   try
     {
       long __l;
       const __num_get_type& __ng = __check_facet(this->_M_num_get);
       __ng.get(*this, 0, *this, __err, __l);
       if (__l < __gnu_cxx::__numeric_traits<short>::__min)
  {
    __err |= ios_base::failbit;
    __n = __gnu_cxx::__numeric_traits<short>::__min;
  }
       else if (__l > __gnu_cxx::__numeric_traits<short>::__max)
  {
    __err |= ios_base::failbit;
    __n = __gnu_cxx::__numeric_traits<short>::__max;
  }
       else
  __n = short(__l);
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
   if (__err)
     this->setstate(__err);
 }
      return *this;
    }
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    operator>>(int& __n)
    {
      sentry __cerb(*this, false);
      if (__cerb)
 {
   ios_base::iostate __err = ios_base::goodbit;
   try
     {
       long __l;
       const __num_get_type& __ng = __check_facet(this->_M_num_get);
       __ng.get(*this, 0, *this, __err, __l);
       if (__l < __gnu_cxx::__numeric_traits<int>::__min)
  {
    __err |= ios_base::failbit;
    __n = __gnu_cxx::__numeric_traits<int>::__min;
  }
       else if (__l > __gnu_cxx::__numeric_traits<int>::__max)
  {
    __err |= ios_base::failbit;
    __n = __gnu_cxx::__numeric_traits<int>::__max;
  }
       else
  __n = int(__l);
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
   if (__err)
     this->setstate(__err);
 }
      return *this;
    }
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    operator>>(__streambuf_type* __sbout)
    {
      ios_base::iostate __err = ios_base::goodbit;
      sentry __cerb(*this, false);
      if (__cerb && __sbout)
 {
   try
     {
       bool __ineof;
       if (!__copy_streambufs_eof(this->rdbuf(), __sbout, __ineof))
  __err |= ios_base::failbit;
       if (__ineof)
  __err |= ios_base::eofbit;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::failbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::failbit); }
 }
      else if (!__sbout)
 __err |= ios_base::failbit;
      if (__err)
 this->setstate(__err);
      return *this;
    }
  template<typename _CharT, typename _Traits>
    typename basic_istream<_CharT, _Traits>::int_type
    basic_istream<_CharT, _Traits>::
    get(void)
    {
      const int_type __eof = traits_type::eof();
      int_type __c = __eof;
      _M_gcount = 0;
      ios_base::iostate __err = ios_base::goodbit;
      sentry __cerb(*this, true);
      if (__cerb)
 {
   try
     {
       __c = this->rdbuf()->sbumpc();
       if (!traits_type::eq_int_type(__c, __eof))
  _M_gcount = 1;
       else
  __err |= ios_base::eofbit;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
 }
      if (!_M_gcount)
 __err |= ios_base::failbit;
      if (__err)
 this->setstate(__err);
      return __c;
    }
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    get(char_type& __c)
    {
      _M_gcount = 0;
      ios_base::iostate __err = ios_base::goodbit;
      sentry __cerb(*this, true);
      if (__cerb)
 {
   try
     {
       const int_type __cb = this->rdbuf()->sbumpc();
       if (!traits_type::eq_int_type(__cb, traits_type::eof()))
  {
    _M_gcount = 1;
    __c = traits_type::to_char_type(__cb);
  }
       else
  __err |= ios_base::eofbit;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
 }
      if (!_M_gcount)
 __err |= ios_base::failbit;
      if (__err)
 this->setstate(__err);
      return *this;
    }
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    get(char_type* __s, streamsize __n, char_type __delim)
    {
      _M_gcount = 0;
      ios_base::iostate __err = ios_base::goodbit;
      sentry __cerb(*this, true);
      if (__cerb)
 {
   try
     {
       const int_type __idelim = traits_type::to_int_type(__delim);
       const int_type __eof = traits_type::eof();
       __streambuf_type* __sb = this->rdbuf();
       int_type __c = __sb->sgetc();
       while (_M_gcount + 1 < __n
       && !traits_type::eq_int_type(__c, __eof)
       && !traits_type::eq_int_type(__c, __idelim))
  {
    *__s++ = traits_type::to_char_type(__c);
    ++_M_gcount;
    __c = __sb->snextc();
  }
       if (traits_type::eq_int_type(__c, __eof))
  __err |= ios_base::eofbit;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
 }
      if (__n > 0)
 *__s = char_type();
      if (!_M_gcount)
 __err |= ios_base::failbit;
      if (__err)
 this->setstate(__err);
      return *this;
    }
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    get(__streambuf_type& __sb, char_type __delim)
    {
      _M_gcount = 0;
      ios_base::iostate __err = ios_base::goodbit;
      sentry __cerb(*this, true);
      if (__cerb)
 {
   try
     {
       const int_type __idelim = traits_type::to_int_type(__delim);
       const int_type __eof = traits_type::eof();
       __streambuf_type* __this_sb = this->rdbuf();
       int_type __c = __this_sb->sgetc();
       char_type __c2 = traits_type::to_char_type(__c);
       while (!traits_type::eq_int_type(__c, __eof)
       && !traits_type::eq_int_type(__c, __idelim)
       && !traits_type::eq_int_type(__sb.sputc(__c2), __eof))
  {
    ++_M_gcount;
    __c = __this_sb->snextc();
    __c2 = traits_type::to_char_type(__c);
  }
       if (traits_type::eq_int_type(__c, __eof))
  __err |= ios_base::eofbit;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
 }
      if (!_M_gcount)
 __err |= ios_base::failbit;
      if (__err)
 this->setstate(__err);
      return *this;
    }
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    getline(char_type* __s, streamsize __n, char_type __delim)
    {
      _M_gcount = 0;
      ios_base::iostate __err = ios_base::goodbit;
      sentry __cerb(*this, true);
      if (__cerb)
        {
          try
            {
              const int_type __idelim = traits_type::to_int_type(__delim);
              const int_type __eof = traits_type::eof();
              __streambuf_type* __sb = this->rdbuf();
              int_type __c = __sb->sgetc();
              while (_M_gcount + 1 < __n
                     && !traits_type::eq_int_type(__c, __eof)
                     && !traits_type::eq_int_type(__c, __idelim))
                {
                  *__s++ = traits_type::to_char_type(__c);
                  __c = __sb->snextc();
                  ++_M_gcount;
                }
              if (traits_type::eq_int_type(__c, __eof))
                __err |= ios_base::eofbit;
              else
                {
                  if (traits_type::eq_int_type(__c, __idelim))
                    {
                      __sb->sbumpc();
                      ++_M_gcount;
                    }
                  else
                    __err |= ios_base::failbit;
                }
            }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
          catch(...)
            { this->_M_setstate(ios_base::badbit); }
        }
      if (__n > 0)
 *__s = char_type();
      if (!_M_gcount)
        __err |= ios_base::failbit;
      if (__err)
        this->setstate(__err);
      return *this;
    }
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    ignore(void)
    {
      _M_gcount = 0;
      sentry __cerb(*this, true);
      if (__cerb)
 {
   ios_base::iostate __err = ios_base::goodbit;
   try
     {
       const int_type __eof = traits_type::eof();
       __streambuf_type* __sb = this->rdbuf();
       if (traits_type::eq_int_type(__sb->sbumpc(), __eof))
  __err |= ios_base::eofbit;
       else
  _M_gcount = 1;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
   if (__err)
     this->setstate(__err);
 }
      return *this;
    }
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    ignore(streamsize __n)
    {
      _M_gcount = 0;
      sentry __cerb(*this, true);
      if (__cerb && __n > 0)
        {
          ios_base::iostate __err = ios_base::goodbit;
          try
            {
              const int_type __eof = traits_type::eof();
              __streambuf_type* __sb = this->rdbuf();
              int_type __c = __sb->sgetc();
       bool __large_ignore = false;
       while (true)
  {
    while (_M_gcount < __n
    && !traits_type::eq_int_type(__c, __eof))
      {
        ++_M_gcount;
        __c = __sb->snextc();
      }
    if (__n == __gnu_cxx::__numeric_traits<streamsize>::__max
        && !traits_type::eq_int_type(__c, __eof))
      {
        _M_gcount =
   __gnu_cxx::__numeric_traits<streamsize>::__min;
        __large_ignore = true;
      }
    else
      break;
  }
       if (__large_ignore)
  _M_gcount = __gnu_cxx::__numeric_traits<streamsize>::__max;
       if (traits_type::eq_int_type(__c, __eof))
                __err |= ios_base::eofbit;
            }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
          catch(...)
            { this->_M_setstate(ios_base::badbit); }
          if (__err)
            this->setstate(__err);
        }
      return *this;
    }
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    ignore(streamsize __n, int_type __delim)
    {
      _M_gcount = 0;
      sentry __cerb(*this, true);
      if (__cerb && __n > 0)
        {
          ios_base::iostate __err = ios_base::goodbit;
          try
            {
              const int_type __eof = traits_type::eof();
              __streambuf_type* __sb = this->rdbuf();
              int_type __c = __sb->sgetc();
       bool __large_ignore = false;
       while (true)
  {
    while (_M_gcount < __n
    && !traits_type::eq_int_type(__c, __eof)
    && !traits_type::eq_int_type(__c, __delim))
      {
        ++_M_gcount;
        __c = __sb->snextc();
      }
    if (__n == __gnu_cxx::__numeric_traits<streamsize>::__max
        && !traits_type::eq_int_type(__c, __eof)
        && !traits_type::eq_int_type(__c, __delim))
      {
        _M_gcount =
   __gnu_cxx::__numeric_traits<streamsize>::__min;
        __large_ignore = true;
      }
    else
      break;
  }
       if (__large_ignore)
  _M_gcount = __gnu_cxx::__numeric_traits<streamsize>::__max;
              if (traits_type::eq_int_type(__c, __eof))
                __err |= ios_base::eofbit;
       else if (traits_type::eq_int_type(__c, __delim))
  {
    if (_M_gcount
        < __gnu_cxx::__numeric_traits<streamsize>::__max)
      ++_M_gcount;
    __sb->sbumpc();
  }
            }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
          catch(...)
            { this->_M_setstate(ios_base::badbit); }
          if (__err)
            this->setstate(__err);
        }
      return *this;
    }
  template<typename _CharT, typename _Traits>
    typename basic_istream<_CharT, _Traits>::int_type
    basic_istream<_CharT, _Traits>::
    peek(void)
    {
      int_type __c = traits_type::eof();
      _M_gcount = 0;
      sentry __cerb(*this, true);
      if (__cerb)
 {
   ios_base::iostate __err = ios_base::goodbit;
   try
     {
       __c = this->rdbuf()->sgetc();
       if (traits_type::eq_int_type(__c, traits_type::eof()))
  __err |= ios_base::eofbit;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
   if (__err)
     this->setstate(__err);
 }
      return __c;
    }
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    read(char_type* __s, streamsize __n)
    {
      _M_gcount = 0;
      sentry __cerb(*this, true);
      if (__cerb)
 {
   ios_base::iostate __err = ios_base::goodbit;
   try
     {
       _M_gcount = this->rdbuf()->sgetn(__s, __n);
       if (_M_gcount != __n)
  __err |= (ios_base::eofbit | ios_base::failbit);
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
   if (__err)
     this->setstate(__err);
 }
      return *this;
    }
  template<typename _CharT, typename _Traits>
    streamsize
    basic_istream<_CharT, _Traits>::
    readsome(char_type* __s, streamsize __n)
    {
      _M_gcount = 0;
      sentry __cerb(*this, true);
      if (__cerb)
 {
   ios_base::iostate __err = ios_base::goodbit;
   try
     {
       const streamsize __num = this->rdbuf()->in_avail();
       if (__num > 0)
  _M_gcount = this->rdbuf()->sgetn(__s, std::min(__num, __n));
       else if (__num == -1)
  __err |= ios_base::eofbit;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
   if (__err)
     this->setstate(__err);
 }
      return _M_gcount;
    }
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    putback(char_type __c)
    {
      _M_gcount = 0;
      this->clear(this->rdstate() & ~ios_base::eofbit);
      sentry __cerb(*this, true);
      if (__cerb)
 {
   ios_base::iostate __err = ios_base::goodbit;
   try
     {
       const int_type __eof = traits_type::eof();
       __streambuf_type* __sb = this->rdbuf();
       if (!__sb
    || traits_type::eq_int_type(__sb->sputbackc(__c), __eof))
  __err |= ios_base::badbit;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
   if (__err)
     this->setstate(__err);
 }
      return *this;
    }
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    unget(void)
    {
      _M_gcount = 0;
      this->clear(this->rdstate() & ~ios_base::eofbit);
      sentry __cerb(*this, true);
      if (__cerb)
 {
   ios_base::iostate __err = ios_base::goodbit;
   try
     {
       const int_type __eof = traits_type::eof();
       __streambuf_type* __sb = this->rdbuf();
       if (!__sb
    || traits_type::eq_int_type(__sb->sungetc(), __eof))
  __err |= ios_base::badbit;
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
   if (__err)
     this->setstate(__err);
 }
      return *this;
    }
  template<typename _CharT, typename _Traits>
    int
    basic_istream<_CharT, _Traits>::
    sync(void)
    {
      int __ret = -1;
      sentry __cerb(*this, true);
      if (__cerb)
 {
   ios_base::iostate __err = ios_base::goodbit;
   try
     {
       __streambuf_type* __sb = this->rdbuf();
       if (__sb)
  {
    if (__sb->pubsync() == -1)
      __err |= ios_base::badbit;
    else
      __ret = 0;
  }
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
   if (__err)
     this->setstate(__err);
 }
      return __ret;
    }
  template<typename _CharT, typename _Traits>
    typename basic_istream<_CharT, _Traits>::pos_type
    basic_istream<_CharT, _Traits>::
    tellg(void)
    {
      pos_type __ret = pos_type(-1);
      sentry __cerb(*this, true);
      if (__cerb)
 {
   try
     {
       if (!this->fail())
  __ret = this->rdbuf()->pubseekoff(0, ios_base::cur,
        ios_base::in);
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
 }
      return __ret;
    }
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    seekg(pos_type __pos)
    {
      this->clear(this->rdstate() & ~ios_base::eofbit);
      sentry __cerb(*this, true);
      if (__cerb)
 {
   ios_base::iostate __err = ios_base::goodbit;
   try
     {
       if (!this->fail())
  {
    const pos_type __p = this->rdbuf()->pubseekpos(__pos,
         ios_base::in);
    if (__p == pos_type(off_type(-1)))
      __err |= ios_base::failbit;
  }
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
   if (__err)
     this->setstate(__err);
 }
      return *this;
    }
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    basic_istream<_CharT, _Traits>::
    seekg(off_type __off, ios_base::seekdir __dir)
    {
      this->clear(this->rdstate() & ~ios_base::eofbit);
      sentry __cerb(*this, true);
      if (__cerb)
 {
   ios_base::iostate __err = ios_base::goodbit;
   try
     {
       if (!this->fail())
  {
    const pos_type __p = this->rdbuf()->pubseekoff(__off, __dir,
         ios_base::in);
    if (__p == pos_type(off_type(-1)))
      __err |= ios_base::failbit;
  }
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       this->_M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { this->_M_setstate(ios_base::badbit); }
   if (__err)
     this->setstate(__err);
 }
      return *this;
    }
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>& __in, _CharT& __c)
    {
      typedef basic_istream<_CharT, _Traits> __istream_type;
      typedef typename __istream_type::int_type __int_type;
      typename __istream_type::sentry __cerb(__in, false);
      if (__cerb)
 {
   ios_base::iostate __err = ios_base::goodbit;
   try
     {
       const __int_type __cb = __in.rdbuf()->sbumpc();
       if (!_Traits::eq_int_type(__cb, _Traits::eof()))
  __c = _Traits::to_char_type(__cb);
       else
  __err |= (ios_base::eofbit | ios_base::failbit);
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       __in._M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { __in._M_setstate(ios_base::badbit); }
   if (__err)
     __in.setstate(__err);
 }
      return __in;
    }
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    operator>>(basic_istream<_CharT, _Traits>& __in, _CharT* __s)
    {
      typedef basic_istream<_CharT, _Traits> __istream_type;
      typedef basic_streambuf<_CharT, _Traits> __streambuf_type;
      typedef typename _Traits::int_type int_type;
      typedef _CharT char_type;
      typedef ctype<_CharT> __ctype_type;
      streamsize __extracted = 0;
      ios_base::iostate __err = ios_base::goodbit;
      typename __istream_type::sentry __cerb(__in, false);
      if (__cerb)
 {
   try
     {
       streamsize __num = __in.width();
       if (__num <= 0)
  __num = __gnu_cxx::__numeric_traits<streamsize>::__max;
       const __ctype_type& __ct = use_facet<__ctype_type>(__in.getloc());
       const int_type __eof = _Traits::eof();
       __streambuf_type* __sb = __in.rdbuf();
       int_type __c = __sb->sgetc();
       while (__extracted < __num - 1
       && !_Traits::eq_int_type(__c, __eof)
       && !__ct.is(ctype_base::space,
     _Traits::to_char_type(__c)))
  {
    *__s++ = _Traits::to_char_type(__c);
    ++__extracted;
    __c = __sb->snextc();
  }
       if (_Traits::eq_int_type(__c, __eof))
  __err |= ios_base::eofbit;
       *__s = char_type();
       __in.width(0);
     }
   catch(__cxxabiv1::__forced_unwind&)
     {
       __in._M_setstate(ios_base::badbit);
       throw;
     }
   catch(...)
     { __in._M_setstate(ios_base::badbit); }
 }
      if (!__extracted)
 __err |= ios_base::failbit;
      if (__err)
 __in.setstate(__err);
      return __in;
    }
  template<typename _CharT, typename _Traits>
    basic_istream<_CharT, _Traits>&
    ws(basic_istream<_CharT, _Traits>& __in)
    {
      typedef basic_istream<_CharT, _Traits> __istream_type;
      typedef basic_streambuf<_CharT, _Traits> __streambuf_type;
      typedef typename __istream_type::int_type __int_type;
      typedef ctype<_CharT> __ctype_type;
      const __ctype_type& __ct = use_facet<__ctype_type>(__in.getloc());
      const __int_type __eof = _Traits::eof();
      __streambuf_type* __sb = __in.rdbuf();
      __int_type __c = __sb->sgetc();
      while (!_Traits::eq_int_type(__c, __eof)
      && __ct.is(ctype_base::space, _Traits::to_char_type(__c)))
 __c = __sb->snextc();
       if (_Traits::eq_int_type(__c, __eof))
  __in.setstate(ios_base::eofbit);
      return __in;
    }
  extern template class basic_istream<char>;
  extern template istream& ws(istream&);
  extern template istream& operator>>(istream&, char&);
  extern template istream& operator>>(istream&, char*);
  extern template istream& operator>>(istream&, unsigned char&);
  extern template istream& operator>>(istream&, signed char&);
  extern template istream& operator>>(istream&, unsigned char*);
  extern template istream& operator>>(istream&, signed char*);
  extern template istream& istream::_M_extract(unsigned short&);
  extern template istream& istream::_M_extract(unsigned int&);
  extern template istream& istream::_M_extract(long&);
  extern template istream& istream::_M_extract(unsigned long&);
  extern template istream& istream::_M_extract(bool&);
  extern template istream& istream::_M_extract(long long&);
  extern template istream& istream::_M_extract(unsigned long long&);
  extern template istream& istream::_M_extract(float&);
  extern template istream& istream::_M_extract(double&);
  extern template istream& istream::_M_extract(long double&);
  extern template istream& istream::_M_extract(void*&);
  extern template class basic_iostream<char>;
  extern template class basic_istream<wchar_t>;
  extern template wistream& ws(wistream&);
  extern template wistream& operator>>(wistream&, wchar_t&);
  extern template wistream& operator>>(wistream&, wchar_t*);
  extern template wistream& wistream::_M_extract(unsigned short&);
  extern template wistream& wistream::_M_extract(unsigned int&);
  extern template wistream& wistream::_M_extract(long&);
  extern template wistream& wistream::_M_extract(unsigned long&);
  extern template wistream& wistream::_M_extract(bool&);
  extern template wistream& wistream::_M_extract(long long&);
  extern template wistream& wistream::_M_extract(unsigned long long&);
  extern template wistream& wistream::_M_extract(float&);
  extern template wistream& wistream::_M_extract(double&);
  extern template wistream& wistream::_M_extract(long double&);
  extern template wistream& wistream::_M_extract(void*&);
  extern template class basic_iostream<wchar_t>;

}
       
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename _Tp, typename _CharT = char,
           typename _Traits = char_traits<_CharT>, typename _Dist = ptrdiff_t>
    class istream_iterator
    : public iterator<input_iterator_tag, _Tp, _Dist, const _Tp*, const _Tp&>
    {
    public:
      typedef _CharT char_type;
      typedef _Traits traits_type;
      typedef basic_istream<_CharT, _Traits> istream_type;
    private:
      istream_type* _M_stream;
      _Tp _M_value;
      bool _M_ok;
    public:
      constexpr istream_iterator()
      : _M_stream(0), _M_value(), _M_ok(false) {}
      istream_iterator(istream_type& __s)
      : _M_stream(&__s)
      { _M_read(); }
      istream_iterator(const istream_iterator& __obj)
      : _M_stream(__obj._M_stream), _M_value(__obj._M_value),
        _M_ok(__obj._M_ok)
      { }
      const _Tp&
      operator*() const
      {
 ;
 return _M_value;
      }
      const _Tp*
      operator->() const { return &(operator*()); }
      istream_iterator&
      operator++()
      {
 ;
 _M_read();
 return *this;
      }
      istream_iterator
      operator++(int)
      {
 ;
 istream_iterator __tmp = *this;
 _M_read();
 return __tmp;
      }
      bool
      _M_equal(const istream_iterator& __x) const
      { return (_M_ok == __x._M_ok) && (!_M_ok || _M_stream == __x._M_stream); }
    private:
      void
      _M_read()
      {
 _M_ok = (_M_stream && *_M_stream) ? true : false;
 if (_M_ok)
   {
     *_M_stream >> _M_value;
     _M_ok = *_M_stream ? true : false;
   }
      }
    };
  template<typename _Tp, typename _CharT, typename _Traits, typename _Dist>
    inline bool
    operator==(const istream_iterator<_Tp, _CharT, _Traits, _Dist>& __x,
        const istream_iterator<_Tp, _CharT, _Traits, _Dist>& __y)
    { return __x._M_equal(__y); }
  template <class _Tp, class _CharT, class _Traits, class _Dist>
    inline bool
    operator!=(const istream_iterator<_Tp, _CharT, _Traits, _Dist>& __x,
        const istream_iterator<_Tp, _CharT, _Traits, _Dist>& __y)
    { return !__x._M_equal(__y); }
  template<typename _Tp, typename _CharT = char,
           typename _Traits = char_traits<_CharT> >
    class ostream_iterator
    : public iterator<output_iterator_tag, void, void, void, void>
    {
    public:
      typedef _CharT char_type;
      typedef _Traits traits_type;
      typedef basic_ostream<_CharT, _Traits> ostream_type;
    private:
      ostream_type* _M_stream;
      const _CharT* _M_string;
    public:
      ostream_iterator(ostream_type& __s) : _M_stream(&__s), _M_string(0) {}
      ostream_iterator(ostream_type& __s, const _CharT* __c)
      : _M_stream(&__s), _M_string(__c) { }
      ostream_iterator(const ostream_iterator& __obj)
      : _M_stream(__obj._M_stream), _M_string(__obj._M_string) { }
      ostream_iterator&
      operator=(const _Tp& __value)
      {
 ;
 *_M_stream << __value;
 if (_M_string) *_M_stream << _M_string;
 return *this;
      }
      ostream_iterator&
      operator*()
      { return *this; }
      ostream_iterator&
      operator++()
      { return *this; }
      ostream_iterator&
      operator++(int)
      { return *this; }
    };

}
       
namespace std __attribute__ ((__visibility__ ("default")))
{
  namespace rel_ops
  {
 
    template <class _Tp>
      inline bool
      operator!=(const _Tp& __x, const _Tp& __y)
      { return !(__x == __y); }
    template <class _Tp>
      inline bool
      operator>(const _Tp& __x, const _Tp& __y)
      { return __y < __x; }
    template <class _Tp>
      inline bool
      operator<=(const _Tp& __x, const _Tp& __y)
      { return !(__y < __x); }
    template <class _Tp>
      inline bool
      operator>=(const _Tp& __x, const _Tp& __y)
      { return !(__x < __y); }
 
  }
}
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<class _Tp>
    class tuple_size;
  template<std::size_t _Int, class _Tp>
    class tuple_element;
  template<class _Tp1, class _Tp2>
    struct tuple_size<std::pair<_Tp1, _Tp2>>
    : public integral_constant<std::size_t, 2> { };
  template<class _Tp1, class _Tp2>
    struct tuple_element<0, std::pair<_Tp1, _Tp2>>
    { typedef _Tp1 type; };
  template<class _Tp1, class _Tp2>
    struct tuple_element<1, std::pair<_Tp1, _Tp2>>
    { typedef _Tp2 type; };
  template<std::size_t _Int>
    struct __pair_get;
  template<>
    struct __pair_get<0>
    {
      template<typename _Tp1, typename _Tp2>
        static constexpr _Tp1&
        __get(std::pair<_Tp1, _Tp2>& __pair) noexcept
        { return __pair.first; }
      template<typename _Tp1, typename _Tp2>
        static constexpr _Tp1&&
        __move_get(std::pair<_Tp1, _Tp2>&& __pair) noexcept
        { return std::forward<_Tp1>(__pair.first); }
      template<typename _Tp1, typename _Tp2>
        static constexpr const _Tp1&
        __const_get(const std::pair<_Tp1, _Tp2>& __pair) noexcept
        { return __pair.first; }
    };
  template<>
    struct __pair_get<1>
    {
      template<typename _Tp1, typename _Tp2>
        static constexpr _Tp2&
        __get(std::pair<_Tp1, _Tp2>& __pair) noexcept
        { return __pair.second; }
      template<typename _Tp1, typename _Tp2>
        static constexpr _Tp2&&
        __move_get(std::pair<_Tp1, _Tp2>&& __pair) noexcept
        { return std::forward<_Tp2>(__pair.second); }
      template<typename _Tp1, typename _Tp2>
        static constexpr const _Tp2&
        __const_get(const std::pair<_Tp1, _Tp2>& __pair) noexcept
        { return __pair.second; }
    };
  template<std::size_t _Int, class _Tp1, class _Tp2>
    constexpr typename tuple_element<_Int, std::pair<_Tp1, _Tp2>>::type&
    get(std::pair<_Tp1, _Tp2>& __in) noexcept
    { return __pair_get<_Int>::__get(__in); }
  template<std::size_t _Int, class _Tp1, class _Tp2>
    constexpr typename tuple_element<_Int, std::pair<_Tp1, _Tp2>>::type&&
    get(std::pair<_Tp1, _Tp2>&& __in) noexcept
    { return __pair_get<_Int>::__move_get(std::move(__in)); }
  template<std::size_t _Int, class _Tp1, class _Tp2>
    constexpr const typename tuple_element<_Int, std::pair<_Tp1, _Tp2>>::type&
    get(const std::pair<_Tp1, _Tp2>& __in) noexcept
    { return __pair_get<_Int>::__const_get(__in); }
  template<size_t... _Indexes>
    struct _Index_tuple
    {
      typedef _Index_tuple<_Indexes..., sizeof...(_Indexes)> __next;
    };
  template<size_t _Num>
    struct _Build_index_tuple
    {
      typedef typename _Build_index_tuple<_Num - 1>::__type::__next __type;
    };
  template<>
    struct _Build_index_tuple<0>
    {
      typedef _Index_tuple<> __type;
    };

}
namespace rapidjson {
template <typename Encoding, typename Allocator>
class GenericValue;
template <typename Encoding, typename Allocator>
struct GenericMember {
    GenericValue<Encoding, Allocator> name;
    GenericValue<Encoding, Allocator> value;
};
template <bool Const, typename Encoding, typename Allocator>
class GenericMemberIterator
    : public std::iterator<std::random_access_iterator_tag
        , typename internal::MaybeAddConst<Const,GenericMember<Encoding,Allocator> >::Type> {
    friend class GenericValue<Encoding,Allocator>;
    template <bool, typename, typename> friend class GenericMemberIterator;
    typedef GenericMember<Encoding,Allocator> PlainType;
    typedef typename internal::MaybeAddConst<Const,PlainType>::Type ValueType;
    typedef std::iterator<std::random_access_iterator_tag,ValueType> BaseType;
public:
    typedef GenericMemberIterator Iterator;
    typedef GenericMemberIterator<true,Encoding,Allocator> ConstIterator;
    typedef GenericMemberIterator<false,Encoding,Allocator> NonConstIterator;
    typedef typename BaseType::pointer Pointer;
    typedef typename BaseType::reference Reference;
    typedef typename BaseType::difference_type DifferenceType;
    GenericMemberIterator() : ptr_() {}
    GenericMemberIterator(const NonConstIterator & it) : ptr_(it.ptr_) {}
    Iterator& operator++(){ ++ptr_; return *this; }
    Iterator& operator--(){ --ptr_; return *this; }
    Iterator operator++(int){ Iterator old(*this); ++ptr_; return old; }
    Iterator operator--(int){ Iterator old(*this); --ptr_; return old; }
    Iterator operator+(DifferenceType n) const { return Iterator(ptr_+n); }
    Iterator operator-(DifferenceType n) const { return Iterator(ptr_-n); }
    Iterator& operator+=(DifferenceType n) { ptr_+=n; return *this; }
    Iterator& operator-=(DifferenceType n) { ptr_-=n; return *this; }
    bool operator==(ConstIterator that) const { return ptr_ == that.ptr_; }
    bool operator!=(ConstIterator that) const { return ptr_ != that.ptr_; }
    bool operator<=(ConstIterator that) const { return ptr_ <= that.ptr_; }
    bool operator>=(ConstIterator that) const { return ptr_ >= that.ptr_; }
    bool operator< (ConstIterator that) const { return ptr_ < that.ptr_; }
    bool operator> (ConstIterator that) const { return ptr_ > that.ptr_; }
    Reference operator*() const { return *ptr_; }
    Pointer operator->() const { return ptr_; }
    Reference operator[](DifferenceType n) const { return ptr_[n]; }
    DifferenceType operator-(ConstIterator that) const { return ptr_-that.ptr_; }
private:
    explicit GenericMemberIterator(Pointer p) : ptr_(p) {}
    Pointer ptr_;
};
template<typename CharType>
struct GenericStringRef {
    typedef CharType Ch;
    template<SizeType N>
    GenericStringRef(const CharType (&str)[N]) noexcept
        : s(str), length(N-1) {}
    explicit GenericStringRef(const CharType* str)
        : s(str), length(internal::StrLen(str)){ ((s != __null) ? static_cast<void> (0) : __assert_fail ("s != __null", "aapt/rapidjson/document.h", 309, __PRETTY_FUNCTION__)); }
    GenericStringRef(const CharType* str, SizeType len)
        : s(str), length(len) { ((s != __null) ? static_cast<void> (0) : __assert_fail ("s != __null", "aapt/rapidjson/document.h", 319, __PRETTY_FUNCTION__)); }
    operator const Ch *() const { return s; }
    const Ch* const s;
    const SizeType length;
private:
    GenericStringRef operator=(const GenericStringRef&);
    template<SizeType N>
    GenericStringRef(CharType (&str)[N]) ;
};
template<typename CharType>
inline GenericStringRef<CharType> StringRef(const CharType* str) {
    return GenericStringRef<CharType>(str, internal::StrLen(str));
}
template<typename CharType>
inline GenericStringRef<CharType> StringRef(const CharType* str, size_t length) {
    return GenericStringRef<CharType>(str, SizeType(length));
}
namespace internal {
template <typename T, typename Encoding = void, typename Allocator = void>
struct IsGenericValueImpl : FalseType {};
template <typename T> struct IsGenericValueImpl<T, typename Void<typename T::EncodingType>::Type, typename Void<typename T::AllocatorType>::Type>
    : IsBaseOf<GenericValue<typename T::EncodingType, typename T::AllocatorType>, T>::Type {};
template <typename T> struct IsGenericValue : IsGenericValueImpl<T>::Type {};
}
template <typename Encoding, typename Allocator = MemoryPoolAllocator<> >
class GenericValue {
public:
    typedef GenericMember<Encoding, Allocator> Member;
    typedef Encoding EncodingType;
    typedef Allocator AllocatorType;
    typedef typename Encoding::Ch Ch;
    typedef GenericStringRef<Ch> StringRefType;
    typedef typename GenericMemberIterator<false,Encoding,Allocator>::Iterator MemberIterator;
    typedef typename GenericMemberIterator<true,Encoding,Allocator>::Iterator ConstMemberIterator;
    typedef GenericValue* ValueIterator;
    typedef const GenericValue* ConstValueIterator;
    GenericValue() noexcept : data_(), flags_(kNullFlag) {}
    GenericValue(GenericValue&& rhs) noexcept : data_(rhs.data_), flags_(rhs.flags_) {
        rhs.flags_ = kNullFlag;
    }
private:
    GenericValue(const GenericValue& rhs);
public:
    explicit GenericValue(Type type) noexcept : data_(), flags_() {
        static const unsigned defaultFlags[7] = {
            kNullFlag, kFalseFlag, kTrueFlag, kObjectFlag, kArrayFlag, kConstStringFlag,
            kNumberAnyFlag
        };
        ((type <= kNumberType) ? static_cast<void> (0) : __assert_fail ("type <= kNumberType", "aapt/rapidjson/document.h", 463, __PRETTY_FUNCTION__));
        flags_ = defaultFlags[type];
    }
    template< typename SourceAllocator >
    GenericValue(const GenericValue<Encoding, SourceAllocator>& rhs, Allocator & allocator);
    template <typename T>
    explicit GenericValue(T b, typename ::rapidjson::internal::EnableIf <typename ::rapidjson::internal::RemoveSfinaeTag < ::rapidjson::internal::SfinaeTag&(*) (internal::IsSame<T,bool>)>::Type>::Type * = __null) noexcept
        : data_(), flags_(b ? kTrueFlag : kFalseFlag) {
            typedef ::rapidjson::StaticAssertTest< sizeof(::rapidjson::STATIC_ASSERTION_FAILURE<bool((internal::IsSame<bool,T>::Value)) >)> StaticAssertTypedef491 __attribute__((unused));
    }
    explicit GenericValue(int i) noexcept : data_(), flags_(kNumberIntFlag) {
        data_.n.i64 = i;
        if (i >= 0)
            flags_ |= kUintFlag | kUint64Flag;
    }
    explicit GenericValue(unsigned u) noexcept : data_(), flags_(kNumberUintFlag) {
        data_.n.u64 = u;
        if (!(u & 0x80000000))
            flags_ |= kIntFlag | kInt64Flag;
    }
    explicit GenericValue(int64_t i64) noexcept : data_(), flags_(kNumberInt64Flag) {
        data_.n.i64 = i64;
        if (i64 >= 0) {
            flags_ |= kNumberUint64Flag;
            if (!(static_cast<uint64_t>(i64) & ((static_cast<uint64_t>(0xFFFFFFFF) << 32) | static_cast<uint64_t>(0x00000000))))
                flags_ |= kUintFlag;
            if (!(static_cast<uint64_t>(i64) & ((static_cast<uint64_t>(0xFFFFFFFF) << 32) | static_cast<uint64_t>(0x80000000))))
                flags_ |= kIntFlag;
        }
        else if (i64 >= static_cast<int64_t>(((static_cast<uint64_t>(0xFFFFFFFF) << 32) | static_cast<uint64_t>(0x80000000))))
            flags_ |= kIntFlag;
    }
    explicit GenericValue(uint64_t u64) noexcept : data_(), flags_(kNumberUint64Flag) {
        data_.n.u64 = u64;
        if (!(u64 & ((static_cast<uint64_t>(0x80000000) << 32) | static_cast<uint64_t>(0x00000000))))
            flags_ |= kInt64Flag;
        if (!(u64 & ((static_cast<uint64_t>(0xFFFFFFFF) << 32) | static_cast<uint64_t>(0x00000000))))
            flags_ |= kUintFlag;
        if (!(u64 & ((static_cast<uint64_t>(0xFFFFFFFF) << 32) | static_cast<uint64_t>(0x80000000))))
            flags_ |= kIntFlag;
    }
    explicit GenericValue(double d) noexcept : data_(), flags_(kNumberDoubleFlag) { data_.n.d = d; }
    GenericValue(const Ch* s, SizeType length) noexcept : data_(), flags_() { SetStringRaw(StringRef(s, length)); }
    explicit GenericValue(StringRefType s) noexcept : data_(), flags_() { SetStringRaw(s); }
    GenericValue(const Ch* s, SizeType length, Allocator& allocator) : data_(), flags_() { SetStringRaw(StringRef(s, length), allocator); }
    GenericValue(const Ch*s, Allocator& allocator) : data_(), flags_() { SetStringRaw(StringRef(s), allocator); }
    ~GenericValue() {
        if (Allocator::kNeedFree) {
            switch(flags_) {
            case kArrayFlag:
                for (GenericValue* v = data_.a.elements; v != data_.a.elements + data_.a.size; ++v)
                    v->~GenericValue();
                Allocator::Free(data_.a.elements);
                break;
            case kObjectFlag:
                for (MemberIterator m = MemberBegin(); m != MemberEnd(); ++m)
                    m->~Member();
                Allocator::Free(data_.o.members);
                break;
            case kCopyStringFlag:
                Allocator::Free(const_cast<Ch*>(data_.s.str));
                break;
            default:
                break;
            }
        }
    }
    GenericValue& operator=(GenericValue& rhs) noexcept {
        ((this != &rhs) ? static_cast<void> (0) : __assert_fail ("this != &rhs", "aapt/rapidjson/document.h", 592, __PRETTY_FUNCTION__));
        this->~GenericValue();
        RawAssign(rhs);
        return *this;
    }
    GenericValue& operator=(GenericValue&& rhs) noexcept {
        return *this = rhs.Move();
    }
    GenericValue& operator=(StringRefType str) noexcept {
        GenericValue s(str);
        return *this = s;
    }
    template <typename T>
    typename ::rapidjson::internal::DisableIf <typename ::rapidjson::internal::RemoveSfinaeTag < ::rapidjson::internal::SfinaeTag&(*) (internal::IsPointer<T>)>::Type, typename ::rapidjson::internal::RemoveSfinaeTag < ::rapidjson::internal::SfinaeTag&(*) (GenericValue&)>::Type>::Type
    operator=(T value) {
        GenericValue v(value);
        return *this = v;
    }
    template <typename SourceAllocator>
    GenericValue& CopyFrom(const GenericValue<Encoding, SourceAllocator>& rhs, Allocator& allocator) {
        (((void*)this != (void const*)&rhs) ? static_cast<void> (0) : __assert_fail ("(void*)this != (void const*)&rhs", "aapt/rapidjson/document.h", 642, __PRETTY_FUNCTION__));
        this->~GenericValue();
        new (this) GenericValue(rhs, allocator);
        return *this;
    }
    GenericValue& Swap(GenericValue& other) noexcept {
        GenericValue temp;
        temp.RawAssign(*this);
        RawAssign(other);
        other.RawAssign(temp);
        return *this;
    }
    GenericValue& Move() noexcept { return *this; }
    template <typename SourceAllocator>
    bool operator==(const GenericValue<Encoding, SourceAllocator>& rhs) const {
        typedef GenericValue<Encoding, SourceAllocator> RhsType;
        if (GetType() != rhs.GetType())
            return false;
        switch (GetType()) {
        case kObjectType:
            if (data_.o.size != rhs.data_.o.size)
                return false;
            for (ConstMemberIterator lhsMemberItr = MemberBegin(); lhsMemberItr != MemberEnd(); ++lhsMemberItr) {
                typename RhsType::ConstMemberIterator rhsMemberItr = rhs.FindMember(lhsMemberItr->name);
                if (rhsMemberItr == rhs.MemberEnd() || lhsMemberItr->value != rhsMemberItr->value)
                    return false;
            }
            return true;
        case kArrayType:
            if (data_.a.size != rhs.data_.a.size)
                return false;
            for (SizeType i = 0; i < data_.a.size; i++)
                if ((*this)[i] != rhs[i])
                    return false;
            return true;
        case kStringType:
            return StringEqual(rhs);
        case kNumberType:
            if (IsDouble() || rhs.IsDouble())
                return GetDouble() == rhs.GetDouble();
            else
                return data_.n.u64 == rhs.data_.n.u64;
        default:
            return true;
        }
    }
    bool operator==(const Ch* rhs) const { return *this == GenericValue(StringRef(rhs)); }
    template <typename T> typename ::rapidjson::internal::DisableIf <typename ::rapidjson::internal::RemoveSfinaeTag < ::rapidjson::internal::SfinaeTag&(*) (internal::OrExpr<internal::IsPointer<T>,internal::IsGenericValue<T> >)>::Type, typename ::rapidjson::internal::RemoveSfinaeTag < ::rapidjson::internal::SfinaeTag&(*) (bool)>::Type>::Type operator==(const T& rhs) const { return *this == GenericValue(rhs); }
    template <typename SourceAllocator>
    bool operator!=(const GenericValue<Encoding, SourceAllocator>& rhs) const { return !(*this == rhs); }
    bool operator!=(const Ch* rhs) const { return !(*this == rhs); }
    template <typename T> typename ::rapidjson::internal::DisableIf <typename ::rapidjson::internal::RemoveSfinaeTag < ::rapidjson::internal::SfinaeTag&(*) (internal::IsGenericValue<T>)>::Type, typename ::rapidjson::internal::RemoveSfinaeTag < ::rapidjson::internal::SfinaeTag&(*) (bool)>::Type>::Type operator!=(const T& rhs) const { return !(*this == rhs); }
    template <typename T> friend typename ::rapidjson::internal::DisableIf <typename ::rapidjson::internal::RemoveSfinaeTag < ::rapidjson::internal::SfinaeTag&(*) (internal::IsGenericValue<T>)>::Type, typename ::rapidjson::internal::RemoveSfinaeTag < ::rapidjson::internal::SfinaeTag&(*) (bool)>::Type>::Type operator==(const T& lhs, const GenericValue& rhs) { return rhs == lhs; }
    template <typename T> friend typename ::rapidjson::internal::DisableIf <typename ::rapidjson::internal::RemoveSfinaeTag < ::rapidjson::internal::SfinaeTag&(*) (internal::IsGenericValue<T>)>::Type, typename ::rapidjson::internal::RemoveSfinaeTag < ::rapidjson::internal::SfinaeTag&(*) (bool)>::Type>::Type operator!=(const T& lhs, const GenericValue& rhs) { return !(rhs == lhs); }
    Type GetType() const { return static_cast<Type>(flags_ & kTypeMask); }
    bool IsNull() const { return flags_ == kNullFlag; }
    bool IsFalse() const { return flags_ == kFalseFlag; }
    bool IsTrue() const { return flags_ == kTrueFlag; }
    bool IsBool() const { return (flags_ & kBoolFlag) != 0; }
    bool IsObject() const { return flags_ == kObjectFlag; }
    bool IsArray() const { return flags_ == kArrayFlag; }
    bool IsNumber() const { return (flags_ & kNumberFlag) != 0; }
    bool IsInt() const { return (flags_ & kIntFlag) != 0; }
    bool IsUint() const { return (flags_ & kUintFlag) != 0; }
    bool IsInt64() const { return (flags_ & kInt64Flag) != 0; }
    bool IsUint64() const { return (flags_ & kUint64Flag) != 0; }
    bool IsDouble() const { return (flags_ & kDoubleFlag) != 0; }
    bool IsString() const { return (flags_ & kStringFlag) != 0; }
    GenericValue& SetNull() { this->~GenericValue(); new (this) GenericValue(); return *this; }
    bool GetBool() const { ((IsBool()) ? static_cast<void> (0) : __assert_fail ("IsBool()", "aapt/rapidjson/document.h", 782, __PRETTY_FUNCTION__)); return flags_ == kTrueFlag; }
    GenericValue& SetBool(bool b) { this->~GenericValue(); new (this) GenericValue(b); return *this; }
    GenericValue& SetObject() { this->~GenericValue(); new (this) GenericValue(kObjectType); return *this; }
    SizeType MemberCount() const { ((IsObject()) ? static_cast<void> (0) : __assert_fail ("IsObject()", "aapt/rapidjson/document.h", 797, __PRETTY_FUNCTION__)); return data_.o.size; }
    bool ObjectEmpty() const { ((IsObject()) ? static_cast<void> (0) : __assert_fail ("IsObject()", "aapt/rapidjson/document.h", 800, __PRETTY_FUNCTION__)); return data_.o.size == 0; }
    template <typename T>
    typename ::rapidjson::internal::DisableIf <typename ::rapidjson::internal::RemoveSfinaeTag < ::rapidjson::internal::SfinaeTag&(*) (internal::NotExpr<internal::IsSame<typename internal::RemoveConst<T>::Type, Ch> >)>::Type, typename ::rapidjson::internal::RemoveSfinaeTag < ::rapidjson::internal::SfinaeTag&(*) (GenericValue&)>::Type>::Type operator[](T* name) {
        GenericValue n(StringRef(name));
        return (*this)[n];
    }
    template <typename T>
    typename ::rapidjson::internal::DisableIf <typename ::rapidjson::internal::RemoveSfinaeTag < ::rapidjson::internal::SfinaeTag&(*) (internal::NotExpr<internal::IsSame<typename internal::RemoveConst<T>::Type, Ch> >)>::Type, typename ::rapidjson::internal::RemoveSfinaeTag < ::rapidjson::internal::SfinaeTag&(*) (const GenericValue&)>::Type>::Type operator[](T* name) const { return const_cast<GenericValue&>(*this)[name]; }
    template <typename SourceAllocator>
    GenericValue& operator[](const GenericValue<Encoding, SourceAllocator>& name) {
        MemberIterator member = FindMember(name);
        if (member != MemberEnd())
            return member->value;
        else {
            ((false) ? static_cast<void> (0) : __assert_fail ("false", "aapt/rapidjson/document.h", 834, __PRETTY_FUNCTION__));
            static GenericValue NullValue;
            return NullValue;
        }
    }
    template <typename SourceAllocator>
    const GenericValue& operator[](const GenericValue<Encoding, SourceAllocator>& name) const { return const_cast<GenericValue&>(*this)[name]; }
    ConstMemberIterator MemberBegin() const { ((IsObject()) ? static_cast<void> (0) : __assert_fail ("IsObject()", "aapt/rapidjson/document.h", 844, __PRETTY_FUNCTION__)); return ConstMemberIterator(data_.o.members); }
    ConstMemberIterator MemberEnd() const { ((IsObject()) ? static_cast<void> (0) : __assert_fail ("IsObject()", "aapt/rapidjson/document.h", 847, __PRETTY_FUNCTION__)); return ConstMemberIterator(data_.o.members + data_.o.size); }
    MemberIterator MemberBegin() { ((IsObject()) ? static_cast<void> (0) : __assert_fail ("IsObject()", "aapt/rapidjson/document.h", 850, __PRETTY_FUNCTION__)); return MemberIterator(data_.o.members); }
    MemberIterator MemberEnd() { ((IsObject()) ? static_cast<void> (0) : __assert_fail ("IsObject()", "aapt/rapidjson/document.h", 853, __PRETTY_FUNCTION__)); return MemberIterator(data_.o.members + data_.o.size); }
    bool HasMember(const Ch* name) const { return FindMember(name) != MemberEnd(); }
    template <typename SourceAllocator>
    bool HasMember(const GenericValue<Encoding, SourceAllocator>& name) const { return FindMember(name) != MemberEnd(); }
    MemberIterator FindMember(const Ch* name) {
        GenericValue n(StringRef(name));
        return FindMember(n);
    }
    ConstMemberIterator FindMember(const Ch* name) const { return const_cast<GenericValue&>(*this).FindMember(name); }
    template <typename SourceAllocator>
    MemberIterator FindMember(const GenericValue<Encoding, SourceAllocator>& name) {
        ((IsObject()) ? static_cast<void> (0) : __assert_fail ("IsObject()", "aapt/rapidjson/document.h", 911, __PRETTY_FUNCTION__));
        ((name.IsString()) ? static_cast<void> (0) : __assert_fail ("name.IsString()", "aapt/rapidjson/document.h", 912, __PRETTY_FUNCTION__));
        MemberIterator member = MemberBegin();
        for ( ; member != MemberEnd(); ++member)
            if (name.StringEqual(member->name))
                break;
        return member;
    }
    template <typename SourceAllocator> ConstMemberIterator FindMember(const GenericValue<Encoding, SourceAllocator>& name) const { return const_cast<GenericValue&>(*this).FindMember(name); }
    GenericValue& AddMember(GenericValue& name, GenericValue& value, Allocator& allocator) {
        ((IsObject()) ? static_cast<void> (0) : __assert_fail ("IsObject()", "aapt/rapidjson/document.h", 932, __PRETTY_FUNCTION__));
        ((name.IsString()) ? static_cast<void> (0) : __assert_fail ("name.IsString()", "aapt/rapidjson/document.h", 933, __PRETTY_FUNCTION__));
        Object& o = data_.o;
        if (o.size >= o.capacity) {
            if (o.capacity == 0) {
                o.capacity = kDefaultObjectCapacity;
                o.members = reinterpret_cast<Member*>(allocator.Malloc(o.capacity * sizeof(Member)));
            }
            else {
                SizeType oldCapacity = o.capacity;
                o.capacity += (oldCapacity + 1) / 2;
                o.members = reinterpret_cast<Member*>(allocator.Realloc(o.members, oldCapacity * sizeof(Member), o.capacity * sizeof(Member)));
            }
        }
        o.members[o.size].name.RawAssign(name);
        o.members[o.size].value.RawAssign(value);
        o.size++;
        return *this;
    }
    GenericValue& AddMember(GenericValue&& name, GenericValue&& value, Allocator& allocator) {
        return AddMember(name, value, allocator);
    }
    GenericValue& AddMember(GenericValue&& name, GenericValue& value, Allocator& allocator) {
        return AddMember(name, value, allocator);
    }
    GenericValue& AddMember(GenericValue& name, GenericValue&& value, Allocator& allocator) {
        return AddMember(name, value, allocator);
    }
    GenericValue& AddMember(StringRefType name, GenericValue&& value, Allocator& allocator) {
        GenericValue n(name);
        return AddMember(n, value, allocator);
    }
    GenericValue& AddMember(StringRefType name, GenericValue& value, Allocator& allocator) {
        GenericValue n(name);
        return AddMember(n, value, allocator);
    }
    GenericValue& AddMember(StringRefType name, StringRefType value, Allocator& allocator) {
        GenericValue v(value);
        return AddMember(name, v, allocator);
    }
    template <typename T>
    typename ::rapidjson::internal::DisableIf <typename ::rapidjson::internal::RemoveSfinaeTag < ::rapidjson::internal::SfinaeTag&(*) (internal::OrExpr<internal::IsPointer<T>, internal::IsGenericValue<T> >)>::Type, typename ::rapidjson::internal::RemoveSfinaeTag < ::rapidjson::internal::SfinaeTag&(*) (GenericValue&)>::Type>::Type
    AddMember(StringRefType name, T value, Allocator& allocator) {
        GenericValue n(name);
        GenericValue v(value);
        return AddMember(n, v, allocator);
    }
    void RemoveAllMembers() {
        ((IsObject()) ? static_cast<void> (0) : __assert_fail ("IsObject()", "aapt/rapidjson/document.h", 1029, __PRETTY_FUNCTION__));
        for (MemberIterator m = MemberBegin(); m != MemberEnd(); ++m)
            m->~Member();
        data_.o.size = 0;
    }
    bool RemoveMember(const Ch* name) {
        GenericValue n(StringRef(name));
        return RemoveMember(n);
    }
    template <typename SourceAllocator>
    bool RemoveMember(const GenericValue<Encoding, SourceAllocator>& name) {
        MemberIterator m = FindMember(name);
        if (m != MemberEnd()) {
            RemoveMember(m);
            return true;
        }
        else
            return false;
    }
    MemberIterator RemoveMember(MemberIterator m) {
        ((IsObject()) ? static_cast<void> (0) : __assert_fail ("IsObject()", "aapt/rapidjson/document.h", 1068, __PRETTY_FUNCTION__));
        ((data_.o.size > 0) ? static_cast<void> (0) : __assert_fail ("data_.o.size > 0", "aapt/rapidjson/document.h", 1069, __PRETTY_FUNCTION__));
        ((data_.o.members != 0) ? static_cast<void> (0) : __assert_fail ("data_.o.members != 0", "aapt/rapidjson/document.h", 1070, __PRETTY_FUNCTION__));
        ((m >= MemberBegin() && m < MemberEnd()) ? static_cast<void> (0) : __assert_fail ("m >= MemberBegin() && m < MemberEnd()", "aapt/rapidjson/document.h", 1071, __PRETTY_FUNCTION__));
        MemberIterator last(data_.o.members + (data_.o.size - 1));
        if (data_.o.size > 1 && m != last) {
            *m = *last;
        }
        else {
            m->~Member();
        }
        --data_.o.size;
        return m;
    }
    MemberIterator EraseMember(ConstMemberIterator pos) {
        return EraseMember(pos, pos +1);
    }
    MemberIterator EraseMember(ConstMemberIterator first, ConstMemberIterator last) {
        ((IsObject()) ? static_cast<void> (0) : __assert_fail ("IsObject()", "aapt/rapidjson/document.h", 1109, __PRETTY_FUNCTION__));
        ((data_.o.size > 0) ? static_cast<void> (0) : __assert_fail ("data_.o.size > 0", "aapt/rapidjson/document.h", 1110, __PRETTY_FUNCTION__));
        ((data_.o.members != 0) ? static_cast<void> (0) : __assert_fail ("data_.o.members != 0", "aapt/rapidjson/document.h", 1111, __PRETTY_FUNCTION__));
        ((first >= MemberBegin()) ? static_cast<void> (0) : __assert_fail ("first >= MemberBegin()", "aapt/rapidjson/document.h", 1112, __PRETTY_FUNCTION__));
        ((first <= last) ? static_cast<void> (0) : __assert_fail ("first <= last", "aapt/rapidjson/document.h", 1113, __PRETTY_FUNCTION__));
        ((last <= MemberEnd()) ? static_cast<void> (0) : __assert_fail ("last <= MemberEnd()", "aapt/rapidjson/document.h", 1114, __PRETTY_FUNCTION__));
        MemberIterator pos = MemberBegin() + (first - MemberBegin());
        for (MemberIterator itr = pos; itr != last; ++itr)
            itr->~Member();
        std::memmove(&*pos, &*last, (MemberEnd() - last) * sizeof(Member));
        data_.o.size -= (last - first);
        return pos;
    }
    GenericValue& SetArray() { this->~GenericValue(); new (this) GenericValue(kArrayType); return *this; }
    SizeType Size() const { ((IsArray()) ? static_cast<void> (0) : __assert_fail ("IsArray()", "aapt/rapidjson/document.h", 1134, __PRETTY_FUNCTION__)); return data_.a.size; }
    SizeType Capacity() const { ((IsArray()) ? static_cast<void> (0) : __assert_fail ("IsArray()", "aapt/rapidjson/document.h", 1137, __PRETTY_FUNCTION__)); return data_.a.capacity; }
    bool Empty() const { ((IsArray()) ? static_cast<void> (0) : __assert_fail ("IsArray()", "aapt/rapidjson/document.h", 1140, __PRETTY_FUNCTION__)); return data_.a.size == 0; }
    void Clear() {
        ((IsArray()) ? static_cast<void> (0) : __assert_fail ("IsArray()", "aapt/rapidjson/document.h", 1147, __PRETTY_FUNCTION__));
        for (SizeType i = 0; i < data_.a.size; ++i)
            data_.a.elements[i].~GenericValue();
        data_.a.size = 0;
    }
    GenericValue& operator[](SizeType index) {
        ((IsArray()) ? static_cast<void> (0) : __assert_fail ("IsArray()", "aapt/rapidjson/document.h", 1159, __PRETTY_FUNCTION__));
        ((index < data_.a.size) ? static_cast<void> (0) : __assert_fail ("index < data_.a.size", "aapt/rapidjson/document.h", 1160, __PRETTY_FUNCTION__));
        return data_.a.elements[index];
    }
    const GenericValue& operator[](SizeType index) const { return const_cast<GenericValue&>(*this)[index]; }
    ValueIterator Begin() { ((IsArray()) ? static_cast<void> (0) : __assert_fail ("IsArray()", "aapt/rapidjson/document.h", 1167, __PRETTY_FUNCTION__)); return data_.a.elements; }
    ValueIterator End() { ((IsArray()) ? static_cast<void> (0) : __assert_fail ("IsArray()", "aapt/rapidjson/document.h", 1170, __PRETTY_FUNCTION__)); return data_.a.elements + data_.a.size; }
    ConstValueIterator Begin() const { return const_cast<GenericValue&>(*this).Begin(); }
    ConstValueIterator End() const { return const_cast<GenericValue&>(*this).End(); }
    GenericValue& Reserve(SizeType newCapacity, Allocator &allocator) {
        ((IsArray()) ? static_cast<void> (0) : __assert_fail ("IsArray()", "aapt/rapidjson/document.h", 1185, __PRETTY_FUNCTION__));
        if (newCapacity > data_.a.capacity) {
            data_.a.elements = (GenericValue*)allocator.Realloc(data_.a.elements, data_.a.capacity * sizeof(GenericValue), newCapacity * sizeof(GenericValue));
            data_.a.capacity = newCapacity;
        }
        return *this;
    }
    GenericValue& PushBack(GenericValue& value, Allocator& allocator) {
        ((IsArray()) ? static_cast<void> (0) : __assert_fail ("IsArray()", "aapt/rapidjson/document.h", 1204, __PRETTY_FUNCTION__));
        if (data_.a.size >= data_.a.capacity)
            Reserve(data_.a.capacity == 0 ? kDefaultArrayCapacity : (data_.a.capacity + (data_.a.capacity + 1) / 2), allocator);
        data_.a.elements[data_.a.size++].RawAssign(value);
        return *this;
    }
    GenericValue& PushBack(GenericValue&& value, Allocator& allocator) {
        return PushBack(value, allocator);
    }
    GenericValue& PushBack(StringRefType value, Allocator& allocator) {
        return (*this).template PushBack<StringRefType>(value, allocator);
    }
    template <typename T>
    typename ::rapidjson::internal::DisableIf <typename ::rapidjson::internal::RemoveSfinaeTag < ::rapidjson::internal::SfinaeTag&(*) (internal::OrExpr<internal::IsPointer<T>, internal::IsGenericValue<T> >)>::Type, typename ::rapidjson::internal::RemoveSfinaeTag < ::rapidjson::internal::SfinaeTag&(*) (GenericValue&)>::Type>::Type
    PushBack(T value, Allocator& allocator) {
        GenericValue v(value);
        return PushBack(v, allocator);
    }
    GenericValue& PopBack() {
        ((IsArray()) ? static_cast<void> (0) : __assert_fail ("IsArray()", "aapt/rapidjson/document.h", 1259, __PRETTY_FUNCTION__));
        ((!Empty()) ? static_cast<void> (0) : __assert_fail ("!Empty()", "aapt/rapidjson/document.h", 1260, __PRETTY_FUNCTION__));
        data_.a.elements[--data_.a.size].~GenericValue();
        return *this;
    }
    ValueIterator Erase(ConstValueIterator pos) {
        return Erase(pos, pos + 1);
    }
    ValueIterator Erase(ConstValueIterator first, ConstValueIterator last) {
        ((IsArray()) ? static_cast<void> (0) : __assert_fail ("IsArray()", "aapt/rapidjson/document.h", 1285, __PRETTY_FUNCTION__));
        ((data_.a.size > 0) ? static_cast<void> (0) : __assert_fail ("data_.a.size > 0", "aapt/rapidjson/document.h", 1286, __PRETTY_FUNCTION__));
        ((data_.a.elements != 0) ? static_cast<void> (0) : __assert_fail ("data_.a.elements != 0", "aapt/rapidjson/document.h", 1287, __PRETTY_FUNCTION__));
        ((first >= Begin()) ? static_cast<void> (0) : __assert_fail ("first >= Begin()", "aapt/rapidjson/document.h", 1288, __PRETTY_FUNCTION__));
        ((first <= last) ? static_cast<void> (0) : __assert_fail ("first <= last", "aapt/rapidjson/document.h", 1289, __PRETTY_FUNCTION__));
        ((last <= End()) ? static_cast<void> (0) : __assert_fail ("last <= End()", "aapt/rapidjson/document.h", 1290, __PRETTY_FUNCTION__));
        ValueIterator pos = Begin() + (first - Begin());
        for (ValueIterator itr = pos; itr != last; ++itr)
            itr->~GenericValue();
        std::memmove(pos, last, (End() - last) * sizeof(GenericValue));
        data_.a.size -= (last - first);
        return pos;
    }
    int GetInt() const { ((flags_ & kIntFlag) ? static_cast<void> (0) : __assert_fail ("flags_ & kIntFlag", "aapt/rapidjson/document.h", 1304, __PRETTY_FUNCTION__)); return data_.n.i.i; }
    unsigned GetUint() const { ((flags_ & kUintFlag) ? static_cast<void> (0) : __assert_fail ("flags_ & kUintFlag", "aapt/rapidjson/document.h", 1305, __PRETTY_FUNCTION__)); return data_.n.u.u; }
    int64_t GetInt64() const { ((flags_ & kInt64Flag) ? static_cast<void> (0) : __assert_fail ("flags_ & kInt64Flag", "aapt/rapidjson/document.h", 1306, __PRETTY_FUNCTION__)); return data_.n.i64; }
    uint64_t GetUint64() const { ((flags_ & kUint64Flag) ? static_cast<void> (0) : __assert_fail ("flags_ & kUint64Flag", "aapt/rapidjson/document.h", 1307, __PRETTY_FUNCTION__)); return data_.n.u64; }
    double GetDouble() const {
        ((IsNumber()) ? static_cast<void> (0) : __assert_fail ("IsNumber()", "aapt/rapidjson/document.h", 1310, __PRETTY_FUNCTION__));
        if ((flags_ & kDoubleFlag) != 0) return data_.n.d;
        if ((flags_ & kIntFlag) != 0) return data_.n.i.i;
        if ((flags_ & kUintFlag) != 0) return data_.n.u.u;
        if ((flags_ & kInt64Flag) != 0) return (double)data_.n.i64;
        (((flags_ & kUint64Flag) != 0) ? static_cast<void> (0) : __assert_fail ("(flags_ & kUint64Flag) != 0", "aapt/rapidjson/document.h", 1315, __PRETTY_FUNCTION__)); return (double)data_.n.u64;
    }
    GenericValue& SetInt(int i) { this->~GenericValue(); new (this) GenericValue(i); return *this; }
    GenericValue& SetUint(unsigned u) { this->~GenericValue(); new (this) GenericValue(u); return *this; }
    GenericValue& SetInt64(int64_t i64) { this->~GenericValue(); new (this) GenericValue(i64); return *this; }
    GenericValue& SetUint64(uint64_t u64) { this->~GenericValue(); new (this) GenericValue(u64); return *this; }
    GenericValue& SetDouble(double d) { this->~GenericValue(); new (this) GenericValue(d); return *this; }
    const Ch* GetString() const { ((IsString()) ? static_cast<void> (0) : __assert_fail ("IsString()", "aapt/rapidjson/document.h", 1329, __PRETTY_FUNCTION__)); return ((flags_ & kInlineStrFlag) ? data_.ss.str : data_.s.str); }
    SizeType GetStringLength() const { ((IsString()) ? static_cast<void> (0) : __assert_fail ("IsString()", "aapt/rapidjson/document.h", 1334, __PRETTY_FUNCTION__)); return ((flags_ & kInlineStrFlag) ? (data_.ss.GetLength()) : data_.s.length); }
    GenericValue& SetString(const Ch* s, SizeType length) { return SetString(StringRef(s, length)); }
    GenericValue& SetString(StringRefType s) { this->~GenericValue(); SetStringRaw(s); return *this; }
    GenericValue& SetString(const Ch* s, SizeType length, Allocator& allocator) { this->~GenericValue(); SetStringRaw(StringRef(s, length), allocator); return *this; }
    GenericValue& SetString(const Ch* s, Allocator& allocator) { return SetString(s, internal::StrLen(s), allocator); }
    template <typename Handler>
    bool Accept(Handler& handler) const {
        switch(GetType()) {
        case kNullType: return handler.Null();
        case kFalseType: return handler.Bool(false);
        case kTrueType: return handler.Bool(true);
        case kObjectType:
            if (!handler.StartObject())
                return false;
            for (ConstMemberIterator m = MemberBegin(); m != MemberEnd(); ++m) {
                if (!handler.Key(m->name.GetString(), m->name.GetStringLength(), (m->name.flags_ & kCopyFlag) != 0))
                    return false;
                if (!m->value.Accept(handler))
                    return false;
            }
            return handler.EndObject(data_.o.size);
        case kArrayType:
            if (!handler.StartArray())
                return false;
            for (GenericValue* v = data_.a.elements; v != data_.a.elements + data_.a.size; ++v)
                if (!v->Accept(handler))
                    return false;
            return handler.EndArray(data_.a.size);
        case kStringType:
            return handler.String(GetString(), GetStringLength(), (flags_ & kCopyFlag) != 0);
        case kNumberType:
            if (IsInt()) return handler.Int(data_.n.i.i);
            else if (IsUint()) return handler.Uint(data_.n.u.u);
            else if (IsInt64()) return handler.Int64(data_.n.i64);
            else if (IsUint64()) return handler.Uint64(data_.n.u64);
            else return handler.Double(data_.n.d);
        default:
            ((false) ? static_cast<void> (0) : __assert_fail ("false", "aapt/rapidjson/document.h", 1428, __PRETTY_FUNCTION__));
        }
        return false;
    }
private:
    template <typename, typename> friend class GenericValue;
    template <typename, typename, typename> friend class GenericDocument;
    enum {
        kBoolFlag = 0x100,
        kNumberFlag = 0x200,
        kIntFlag = 0x400,
        kUintFlag = 0x800,
        kInt64Flag = 0x1000,
        kUint64Flag = 0x2000,
        kDoubleFlag = 0x4000,
        kStringFlag = 0x100000,
        kCopyFlag = 0x200000,
        kInlineStrFlag = 0x400000,
        kNullFlag = kNullType,
        kTrueFlag = kTrueType | kBoolFlag,
        kFalseFlag = kFalseType | kBoolFlag,
        kNumberIntFlag = kNumberType | kNumberFlag | kIntFlag | kInt64Flag,
        kNumberUintFlag = kNumberType | kNumberFlag | kUintFlag | kUint64Flag | kInt64Flag,
        kNumberInt64Flag = kNumberType | kNumberFlag | kInt64Flag,
        kNumberUint64Flag = kNumberType | kNumberFlag | kUint64Flag,
        kNumberDoubleFlag = kNumberType | kNumberFlag | kDoubleFlag,
        kNumberAnyFlag = kNumberType | kNumberFlag | kIntFlag | kInt64Flag | kUintFlag | kUint64Flag | kDoubleFlag,
        kConstStringFlag = kStringType | kStringFlag,
        kCopyStringFlag = kStringType | kStringFlag | kCopyFlag,
        kShortStringFlag = kStringType | kStringFlag | kCopyFlag | kInlineStrFlag,
        kObjectFlag = kObjectType,
        kArrayFlag = kArrayType,
        kTypeMask = 0xFF
    };
    static const SizeType kDefaultArrayCapacity = 16;
    static const SizeType kDefaultObjectCapacity = 16;
    struct String {
        const Ch* str;
        SizeType length;
        unsigned hashcode;
    };
    struct ShortString {
        enum { MaxChars = sizeof(String) / sizeof(Ch), MaxSize = MaxChars - 1, LenPos = MaxSize };
        Ch str[MaxChars];
        inline static bool Usable(SizeType len) { return (MaxSize >= len); }
        inline void SetLength(SizeType len) { str[LenPos] = (Ch)(MaxSize - len); }
        inline SizeType GetLength() const { return (SizeType)(MaxSize - str[LenPos]); }
    };
    union Number {
        struct I {
            int i;
            char padding[4];
        }i;
        struct U {
            unsigned u;
            char padding2[4];
        }u;
        int64_t i64;
        uint64_t u64;
        double d;
    };
    struct Object {
        Member* members;
        SizeType size;
        SizeType capacity;
    };
    struct Array {
        GenericValue* elements;
        SizeType size;
        SizeType capacity;
    };
    union Data {
        String s;
        ShortString ss;
        Number n;
        Object o;
        Array a;
    };
    void SetArrayRaw(GenericValue* values, SizeType count, Allocator& allocator) {
        flags_ = kArrayFlag;
        data_.a.elements = (GenericValue*)allocator.Malloc(count * sizeof(GenericValue));
        std::memcpy(data_.a.elements, values, count * sizeof(GenericValue));
        data_.a.size = data_.a.capacity = count;
    }
    void SetObjectRaw(Member* members, SizeType count, Allocator& allocator) {
        flags_ = kObjectFlag;
        data_.o.members = (Member*)allocator.Malloc(count * sizeof(Member));
        std::memcpy(data_.o.members, members, count * sizeof(Member));
        data_.o.size = data_.o.capacity = count;
    }
    void SetStringRaw(StringRefType s) noexcept {
        flags_ = kConstStringFlag;
        data_.s.str = s;
        data_.s.length = s.length;
    }
    void SetStringRaw(StringRefType s, Allocator& allocator) {
        Ch* str = __null;
        if(ShortString::Usable(s.length)) {
            flags_ = kShortStringFlag;
            data_.ss.SetLength(s.length);
            str = data_.ss.str;
        } else {
            flags_ = kCopyStringFlag;
            data_.s.length = s.length;
            str = (Ch *)allocator.Malloc((s.length + 1) * sizeof(Ch));
            data_.s.str = str;
        }
        std::memcpy(str, s, s.length * sizeof(Ch));
        str[s.length] = '\0';
    }
    void RawAssign(GenericValue& rhs) noexcept {
        data_ = rhs.data_;
        flags_ = rhs.flags_;
        rhs.flags_ = kNullFlag;
    }
    template <typename SourceAllocator>
    bool StringEqual(const GenericValue<Encoding, SourceAllocator>& rhs) const {
        ((IsString()) ? static_cast<void> (0) : __assert_fail ("IsString()", "aapt/rapidjson/document.h", 1589, __PRETTY_FUNCTION__));
        ((rhs.IsString()) ? static_cast<void> (0) : __assert_fail ("rhs.IsString()", "aapt/rapidjson/document.h", 1590, __PRETTY_FUNCTION__));
        const SizeType len1 = GetStringLength();
        const SizeType len2 = rhs.GetStringLength();
        if(len1 != len2) { return false; }
        const Ch* const str1 = GetString();
        const Ch* const str2 = rhs.GetString();
        if(str1 == str2) { return true; }
        return (std::memcmp(str1, str2, sizeof(Ch) * len1) == 0);
    }
    Data data_;
    unsigned flags_;
};
typedef GenericValue<UTF8<> > Value;
template <typename Encoding, typename Allocator = MemoryPoolAllocator<>, typename StackAllocator = CrtAllocator>
class GenericDocument : public GenericValue<Encoding, Allocator> {
public:
    typedef typename Encoding::Ch Ch;
    typedef GenericValue<Encoding, Allocator> ValueType;
    typedef Allocator AllocatorType;
    GenericDocument(Allocator* allocator = 0, size_t stackCapacity = kDefaultStackCapacity, StackAllocator* stackAllocator = 0) :
        allocator_(allocator), ownAllocator_(0), stack_(stackAllocator, stackCapacity), parseResult_()
    {
        if (!allocator_)
            ownAllocator_ = allocator_ = new Allocator();
    }
    GenericDocument(GenericDocument&& rhs) noexcept
        : ValueType(std::move(rhs)),
          allocator_(rhs.allocator_),
          ownAllocator_(rhs.ownAllocator_),
          stack_(std::move(rhs.stack_)),
          parseResult_(rhs.parseResult_)
    {
        rhs.allocator_ = 0;
        rhs.ownAllocator_ = 0;
        rhs.parseResult_ = ParseResult();
    }
    ~GenericDocument() {
        Destroy();
    }
    GenericDocument& operator=(GenericDocument&& rhs) noexcept
    {
        ValueType::operator=(std::forward<ValueType>(rhs));
        Destroy();
        allocator_ = rhs.allocator_;
        ownAllocator_ = rhs.ownAllocator_;
        stack_ = std::move(rhs.stack_);
        parseResult_ = rhs.parseResult_;
        rhs.allocator_ = 0;
        rhs.ownAllocator_ = 0;
        rhs.parseResult_ = ParseResult();
        return *this;
    }
    template <unsigned parseFlags, typename SourceEncoding, typename InputStream>
    GenericDocument& ParseStream(InputStream& is) {
        ValueType::SetNull();
        GenericReader<SourceEncoding, Encoding, Allocator> reader(&GetAllocator());
        ClearStackOnExit scope(*this);
        parseResult_ = reader.template Parse<parseFlags>(is, *this);
        if (parseResult_) {
            ((stack_.GetSize() == sizeof(ValueType)) ? static_cast<void> (0) : __assert_fail ("stack_.GetSize() == sizeof(ValueType)", "aapt/rapidjson/document.h", 1700, __PRETTY_FUNCTION__));
            this->RawAssign(*stack_.template Pop<ValueType>(1));
        }
        return *this;
    }
    template <unsigned parseFlags, typename InputStream>
    GenericDocument& ParseStream(InputStream& is) {
        return ParseStream<parseFlags,Encoding,InputStream>(is);
    }
    template <typename InputStream>
    GenericDocument& ParseStream(InputStream& is) {
        return ParseStream<kParseDefaultFlags, Encoding, InputStream>(is);
    }
    template <unsigned parseFlags, typename SourceEncoding>
    GenericDocument& ParseInsitu(Ch* str) {
        GenericInsituStringStream<Encoding> s(str);
        return ParseStream<parseFlags | kParseInsituFlag, SourceEncoding>(s);
    }
    template <unsigned parseFlags>
    GenericDocument& ParseInsitu(Ch* str) {
        return ParseInsitu<parseFlags, Encoding>(str);
    }
    GenericDocument& ParseInsitu(Ch* str) {
        return ParseInsitu<kParseDefaultFlags, Encoding>(str);
    }
    template <unsigned parseFlags, typename SourceEncoding>
    GenericDocument& Parse(const Ch* str) {
        ((!(parseFlags & kParseInsituFlag)) ? static_cast<void> (0) : __assert_fail ("!(parseFlags & kParseInsituFlag)", "aapt/rapidjson/document.h", 1772, __PRETTY_FUNCTION__));
        GenericStringStream<SourceEncoding> s(str);
        return ParseStream<parseFlags, SourceEncoding>(s);
    }
    template <unsigned parseFlags>
    GenericDocument& Parse(const Ch* str) {
        return Parse<parseFlags, Encoding>(str);
    }
    GenericDocument& Parse(const Ch* str) {
        return Parse<kParseDefaultFlags>(str);
    }
    bool HasParseError() const { return parseResult_.IsError(); }
    ParseErrorCode GetParseError() const { return parseResult_.Code(); }
    size_t GetErrorOffset() const { return parseResult_.Offset(); }
    Allocator& GetAllocator() { return *allocator_; }
    size_t GetStackCapacity() const { return stack_.GetCapacity(); }
private:
    struct ClearStackOnExit {
        explicit ClearStackOnExit(GenericDocument& d) : d_(d) {}
        ~ClearStackOnExit() { d_.ClearStack(); }
    private:
        ClearStackOnExit(const ClearStackOnExit&);
        ClearStackOnExit& operator=(const ClearStackOnExit&);
        GenericDocument& d_;
    };
    template <typename,typename,typename> friend class GenericReader;
    template <typename, typename> friend class GenericValue;
    bool Null() { new (stack_.template Push<ValueType>()) ValueType(); return true; }
    bool Bool(bool b) { new (stack_.template Push<ValueType>()) ValueType(b); return true; }
    bool Int(int i) { new (stack_.template Push<ValueType>()) ValueType(i); return true; }
    bool Uint(unsigned i) { new (stack_.template Push<ValueType>()) ValueType(i); return true; }
    bool Int64(int64_t i) { new (stack_.template Push<ValueType>()) ValueType(i); return true; }
    bool Uint64(uint64_t i) { new (stack_.template Push<ValueType>()) ValueType(i); return true; }
    bool Double(double d) { new (stack_.template Push<ValueType>()) ValueType(d); return true; }
    bool String(const Ch* str, SizeType length, bool copy) {
        if (copy)
            new (stack_.template Push<ValueType>()) ValueType(str, length, GetAllocator());
        else
            new (stack_.template Push<ValueType>()) ValueType(str, length);
        return true;
    }
    bool StartObject() { new (stack_.template Push<ValueType>()) ValueType(kObjectType); return true; }
    bool Key(const Ch* str, SizeType length, bool copy) { return String(str, length, copy); }
    bool EndObject(SizeType memberCount) {
        typename ValueType::Member* members = stack_.template Pop<typename ValueType::Member>(memberCount);
        stack_.template Top<ValueType>()->SetObjectRaw(members, (SizeType)memberCount, GetAllocator());
        return true;
    }
    bool StartArray() { new (stack_.template Push<ValueType>()) ValueType(kArrayType); return true; }
    bool EndArray(SizeType elementCount) {
        ValueType* elements = stack_.template Pop<ValueType>(elementCount);
        stack_.template Top<ValueType>()->SetArrayRaw(elements, elementCount, GetAllocator());
        return true;
    }
private:
    GenericDocument(const GenericDocument&);
    GenericDocument& operator=(const GenericDocument&);
    void ClearStack() {
        if (Allocator::kNeedFree)
            while (stack_.GetSize() > 0)
                (stack_.template Pop<ValueType>(1))->~ValueType();
        else
            stack_.Clear();
        stack_.ShrinkToFit();
    }
    void Destroy() {
        delete ownAllocator_;
    }
    static const size_t kDefaultStackCapacity = 1024;
    Allocator* allocator_;
    Allocator* ownAllocator_;
    internal::Stack<StackAllocator> stack_;
    ParseResult parseResult_;
};
typedef GenericDocument<UTF8<> > Document;
template <typename Encoding, typename Allocator>
template <typename SourceAllocator>
inline
GenericValue<Encoding,Allocator>::GenericValue(const GenericValue<Encoding,SourceAllocator>& rhs, Allocator& allocator)
{
    switch (rhs.GetType()) {
    case kObjectType:
    case kArrayType: {
            GenericDocument<Encoding,Allocator> d(&allocator);
            rhs.Accept(d);
            RawAssign(*d.stack_.template Pop<GenericValue>(1));
        }
        break;
    case kStringType:
        if (rhs.flags_ == kConstStringFlag) {
            flags_ = rhs.flags_;
            data_ = *reinterpret_cast<const Data*>(&rhs.data_);
        } else {
            SetStringRaw(StringRef(rhs.GetString(), rhs.GetStringLength()), allocator);
        }
        break;
    default:
        flags_ = rhs.flags_;
        data_ = *reinterpret_cast<const Data*>(&rhs.data_);
    }
}
}

#pragma GCC diagnostic pop

namespace rapidjson {
namespace internal {
inline const char* GetDigitsLut() {
    static const char cDigitsLut[200] = {
        '0','0','0','1','0','2','0','3','0','4','0','5','0','6','0','7','0','8','0','9',
        '1','0','1','1','1','2','1','3','1','4','1','5','1','6','1','7','1','8','1','9',
        '2','0','2','1','2','2','2','3','2','4','2','5','2','6','2','7','2','8','2','9',
        '3','0','3','1','3','2','3','3','3','4','3','5','3','6','3','7','3','8','3','9',
        '4','0','4','1','4','2','4','3','4','4','4','5','4','6','4','7','4','8','4','9',
        '5','0','5','1','5','2','5','3','5','4','5','5','5','6','5','7','5','8','5','9',
        '6','0','6','1','6','2','6','3','6','4','6','5','6','6','6','7','6','8','6','9',
        '7','0','7','1','7','2','7','3','7','4','7','5','7','6','7','7','7','8','7','9',
        '8','0','8','1','8','2','8','3','8','4','8','5','8','6','8','7','8','8','8','9',
        '9','0','9','1','9','2','9','3','9','4','9','5','9','6','9','7','9','8','9','9'
    };
    return cDigitsLut;
}
inline char* u32toa(uint32_t value, char* buffer) {
    const char* cDigitsLut = GetDigitsLut();
    if (value < 10000) {
        const uint32_t d1 = (value / 100) << 1;
        const uint32_t d2 = (value % 100) << 1;
        if (value >= 1000)
            *buffer++ = cDigitsLut[d1];
        if (value >= 100)
            *buffer++ = cDigitsLut[d1 + 1];
        if (value >= 10)
            *buffer++ = cDigitsLut[d2];
        *buffer++ = cDigitsLut[d2 + 1];
    }
    else if (value < 100000000) {
        const uint32_t b = value / 10000;
        const uint32_t c = value % 10000;
        const uint32_t d1 = (b / 100) << 1;
        const uint32_t d2 = (b % 100) << 1;
        const uint32_t d3 = (c / 100) << 1;
        const uint32_t d4 = (c % 100) << 1;
        if (value >= 10000000)
            *buffer++ = cDigitsLut[d1];
        if (value >= 1000000)
            *buffer++ = cDigitsLut[d1 + 1];
        if (value >= 100000)
            *buffer++ = cDigitsLut[d2];
        *buffer++ = cDigitsLut[d2 + 1];
        *buffer++ = cDigitsLut[d3];
        *buffer++ = cDigitsLut[d3 + 1];
        *buffer++ = cDigitsLut[d4];
        *buffer++ = cDigitsLut[d4 + 1];
    }
    else {
        const uint32_t a = value / 100000000;
        value %= 100000000;
        if (a >= 10) {
            const unsigned i = a << 1;
            *buffer++ = cDigitsLut[i];
            *buffer++ = cDigitsLut[i + 1];
        }
        else
            *buffer++ = static_cast<char>('0' + static_cast<char>(a));
        const uint32_t b = value / 10000;
        const uint32_t c = value % 10000;
        const uint32_t d1 = (b / 100) << 1;
        const uint32_t d2 = (b % 100) << 1;
        const uint32_t d3 = (c / 100) << 1;
        const uint32_t d4 = (c % 100) << 1;
        *buffer++ = cDigitsLut[d1];
        *buffer++ = cDigitsLut[d1 + 1];
        *buffer++ = cDigitsLut[d2];
        *buffer++ = cDigitsLut[d2 + 1];
        *buffer++ = cDigitsLut[d3];
        *buffer++ = cDigitsLut[d3 + 1];
        *buffer++ = cDigitsLut[d4];
        *buffer++ = cDigitsLut[d4 + 1];
    }
    return buffer;
}
inline char* i32toa(int32_t value, char* buffer) {
    if (value < 0) {
        *buffer++ = '-';
        value = -value;
    }
    return u32toa(static_cast<uint32_t>(value), buffer);
}
inline char* u64toa(uint64_t value, char* buffer) {
    const char* cDigitsLut = GetDigitsLut();
    const uint64_t kTen8 = 100000000;
    const uint64_t kTen9 = kTen8 * 10;
    const uint64_t kTen10 = kTen8 * 100;
    const uint64_t kTen11 = kTen8 * 1000;
    const uint64_t kTen12 = kTen8 * 10000;
    const uint64_t kTen13 = kTen8 * 100000;
    const uint64_t kTen14 = kTen8 * 1000000;
    const uint64_t kTen15 = kTen8 * 10000000;
    const uint64_t kTen16 = kTen8 * kTen8;
    if (value < kTen8) {
        uint32_t v = static_cast<uint32_t>(value);
        if (v < 10000) {
            const uint32_t d1 = (v / 100) << 1;
            const uint32_t d2 = (v % 100) << 1;
            if (v >= 1000)
                *buffer++ = cDigitsLut[d1];
            if (v >= 100)
                *buffer++ = cDigitsLut[d1 + 1];
            if (v >= 10)
                *buffer++ = cDigitsLut[d2];
            *buffer++ = cDigitsLut[d2 + 1];
        }
        else {
            const uint32_t b = v / 10000;
            const uint32_t c = v % 10000;
            const uint32_t d1 = (b / 100) << 1;
            const uint32_t d2 = (b % 100) << 1;
            const uint32_t d3 = (c / 100) << 1;
            const uint32_t d4 = (c % 100) << 1;
            if (value >= 10000000)
                *buffer++ = cDigitsLut[d1];
            if (value >= 1000000)
                *buffer++ = cDigitsLut[d1 + 1];
            if (value >= 100000)
                *buffer++ = cDigitsLut[d2];
            *buffer++ = cDigitsLut[d2 + 1];
            *buffer++ = cDigitsLut[d3];
            *buffer++ = cDigitsLut[d3 + 1];
            *buffer++ = cDigitsLut[d4];
            *buffer++ = cDigitsLut[d4 + 1];
        }
    }
    else if (value < kTen16) {
        const uint32_t v0 = static_cast<uint32_t>(value / kTen8);
        const uint32_t v1 = static_cast<uint32_t>(value % kTen8);
        const uint32_t b0 = v0 / 10000;
        const uint32_t c0 = v0 % 10000;
        const uint32_t d1 = (b0 / 100) << 1;
        const uint32_t d2 = (b0 % 100) << 1;
        const uint32_t d3 = (c0 / 100) << 1;
        const uint32_t d4 = (c0 % 100) << 1;
        const uint32_t b1 = v1 / 10000;
        const uint32_t c1 = v1 % 10000;
        const uint32_t d5 = (b1 / 100) << 1;
        const uint32_t d6 = (b1 % 100) << 1;
        const uint32_t d7 = (c1 / 100) << 1;
        const uint32_t d8 = (c1 % 100) << 1;
        if (value >= kTen15)
            *buffer++ = cDigitsLut[d1];
        if (value >= kTen14)
            *buffer++ = cDigitsLut[d1 + 1];
        if (value >= kTen13)
            *buffer++ = cDigitsLut[d2];
        if (value >= kTen12)
            *buffer++ = cDigitsLut[d2 + 1];
        if (value >= kTen11)
            *buffer++ = cDigitsLut[d3];
        if (value >= kTen10)
            *buffer++ = cDigitsLut[d3 + 1];
        if (value >= kTen9)
            *buffer++ = cDigitsLut[d4];
        if (value >= kTen8)
            *buffer++ = cDigitsLut[d4 + 1];
        *buffer++ = cDigitsLut[d5];
        *buffer++ = cDigitsLut[d5 + 1];
        *buffer++ = cDigitsLut[d6];
        *buffer++ = cDigitsLut[d6 + 1];
        *buffer++ = cDigitsLut[d7];
        *buffer++ = cDigitsLut[d7 + 1];
        *buffer++ = cDigitsLut[d8];
        *buffer++ = cDigitsLut[d8 + 1];
    }
    else {
        const uint32_t a = static_cast<uint32_t>(value / kTen16);
        value %= kTen16;
        if (a < 10)
            *buffer++ = static_cast<char>('0' + static_cast<char>(a));
        else if (a < 100) {
            const uint32_t i = a << 1;
            *buffer++ = cDigitsLut[i];
            *buffer++ = cDigitsLut[i + 1];
        }
        else if (a < 1000) {
            *buffer++ = static_cast<char>('0' + static_cast<char>(a / 100));
            const uint32_t i = (a % 100) << 1;
            *buffer++ = cDigitsLut[i];
            *buffer++ = cDigitsLut[i + 1];
        }
        else {
            const uint32_t i = (a / 100) << 1;
            const uint32_t j = (a % 100) << 1;
            *buffer++ = cDigitsLut[i];
            *buffer++ = cDigitsLut[i + 1];
            *buffer++ = cDigitsLut[j];
            *buffer++ = cDigitsLut[j + 1];
        }
        const uint32_t v0 = static_cast<uint32_t>(value / kTen8);
        const uint32_t v1 = static_cast<uint32_t>(value % kTen8);
        const uint32_t b0 = v0 / 10000;
        const uint32_t c0 = v0 % 10000;
        const uint32_t d1 = (b0 / 100) << 1;
        const uint32_t d2 = (b0 % 100) << 1;
        const uint32_t d3 = (c0 / 100) << 1;
        const uint32_t d4 = (c0 % 100) << 1;
        const uint32_t b1 = v1 / 10000;
        const uint32_t c1 = v1 % 10000;
        const uint32_t d5 = (b1 / 100) << 1;
        const uint32_t d6 = (b1 % 100) << 1;
        const uint32_t d7 = (c1 / 100) << 1;
        const uint32_t d8 = (c1 % 100) << 1;
        *buffer++ = cDigitsLut[d1];
        *buffer++ = cDigitsLut[d1 + 1];
        *buffer++ = cDigitsLut[d2];
        *buffer++ = cDigitsLut[d2 + 1];
        *buffer++ = cDigitsLut[d3];
        *buffer++ = cDigitsLut[d3 + 1];
        *buffer++ = cDigitsLut[d4];
        *buffer++ = cDigitsLut[d4 + 1];
        *buffer++ = cDigitsLut[d5];
        *buffer++ = cDigitsLut[d5 + 1];
        *buffer++ = cDigitsLut[d6];
        *buffer++ = cDigitsLut[d6 + 1];
        *buffer++ = cDigitsLut[d7];
        *buffer++ = cDigitsLut[d7 + 1];
        *buffer++ = cDigitsLut[d8];
        *buffer++ = cDigitsLut[d8 + 1];
    }
    return buffer;
}
inline char* i64toa(int64_t value, char* buffer) {
    if (value < 0) {
        *buffer++ = '-';
        value = -value;
    }
    return u64toa(static_cast<uint64_t>(value), buffer);
}
}
}
namespace rapidjson {
namespace internal {

#pragma GCC diagnostic push


#pragma GCC diagnostic ignored "-Weffc++"

inline void GrisuRound(char* buffer, int len, uint64_t delta, uint64_t rest, uint64_t ten_kappa, uint64_t wp_w) {
    while (rest < wp_w && delta - rest >= ten_kappa &&
           (rest + ten_kappa < wp_w ||
            wp_w - rest > rest + ten_kappa - wp_w)) {
        buffer[len - 1]--;
        rest += ten_kappa;
    }
}
inline unsigned CountDecimalDigit32(uint32_t n) {
    if (n < 10) return 1;
    if (n < 100) return 2;
    if (n < 1000) return 3;
    if (n < 10000) return 4;
    if (n < 100000) return 5;
    if (n < 1000000) return 6;
    if (n < 10000000) return 7;
    if (n < 100000000) return 8;
    if (n < 1000000000) return 9;
    return 10;
}
inline void DigitGen(const DiyFp& W, const DiyFp& Mp, uint64_t delta, char* buffer, int* len, int* K) {
    static const uint32_t kPow10[] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000 };
    const DiyFp one(uint64_t(1) << -Mp.e, Mp.e);
    const DiyFp wp_w = Mp - W;
    uint32_t p1 = static_cast<uint32_t>(Mp.f >> -one.e);
    uint64_t p2 = Mp.f & (one.f - 1);
    int kappa = CountDecimalDigit32(p1);
    *len = 0;
    while (kappa > 0) {
        uint32_t d;
        switch (kappa) {
            case 10: d = p1 / 1000000000; p1 %= 1000000000; break;
            case 9: d = p1 / 100000000; p1 %= 100000000; break;
            case 8: d = p1 / 10000000; p1 %= 10000000; break;
            case 7: d = p1 / 1000000; p1 %= 1000000; break;
            case 6: d = p1 / 100000; p1 %= 100000; break;
            case 5: d = p1 / 10000; p1 %= 10000; break;
            case 4: d = p1 / 1000; p1 %= 1000; break;
            case 3: d = p1 / 100; p1 %= 100; break;
            case 2: d = p1 / 10; p1 %= 10; break;
            case 1: d = p1; p1 = 0; break;
            default:
                __builtin_unreachable();
        }
        if (d || *len)
            buffer[(*len)++] = static_cast<char>('0' + static_cast<char>(d));
        kappa--;
        uint64_t tmp = (static_cast<uint64_t>(p1) << -one.e) + p2;
        if (tmp <= delta) {
            *K += kappa;
            GrisuRound(buffer, *len, delta, tmp, static_cast<uint64_t>(kPow10[kappa]) << -one.e, wp_w.f);
            return;
        }
    }
    for (;;) {
        p2 *= 10;
        delta *= 10;
        char d = static_cast<char>(p2 >> -one.e);
        if (d || *len)
            buffer[(*len)++] = static_cast<char>('0' + d);
        p2 &= one.f - 1;
        kappa--;
        if (p2 < delta) {
            *K += kappa;
            GrisuRound(buffer, *len, delta, p2, one.f, wp_w.f * kPow10[-kappa]);
            return;
        }
    }
}
inline void Grisu2(double value, char* buffer, int* length, int* K) {
    const DiyFp v(value);
    DiyFp w_m, w_p;
    v.NormalizedBoundaries(&w_m, &w_p);
    const DiyFp c_mk = GetCachedPower(w_p.e, K);
    const DiyFp W = v.Normalize() * c_mk;
    DiyFp Wp = w_p * c_mk;
    DiyFp Wm = w_m * c_mk;
    Wm.f++;
    Wp.f--;
    DigitGen(W, Wp, Wp.f - Wm.f, buffer, length, K);
}
inline char* WriteExponent(int K, char* buffer) {
    if (K < 0) {
        *buffer++ = '-';
        K = -K;
    }
    if (K >= 100) {
        *buffer++ = static_cast<char>('0' + static_cast<char>(K / 100));
        K %= 100;
        const char* d = GetDigitsLut() + K * 2;
        *buffer++ = d[0];
        *buffer++ = d[1];
    }
    else if (K >= 10) {
        const char* d = GetDigitsLut() + K * 2;
        *buffer++ = d[0];
        *buffer++ = d[1];
    }
    else
        *buffer++ = static_cast<char>('0' + static_cast<char>(K));
    return buffer;
}
inline char* Prettify(char* buffer, int length, int k) {
    const int kk = length + k;
    if (length <= kk && kk <= 21) {
        for (int i = length; i < kk; i++)
            buffer[i] = '0';
        buffer[kk] = '.';
        buffer[kk + 1] = '0';
        return &buffer[kk + 2];
    }
    else if (0 < kk && kk <= 21) {
        std::memmove(&buffer[kk + 1], &buffer[kk], length - kk);
        buffer[kk] = '.';
        return &buffer[length + 1];
    }
    else if (-6 < kk && kk <= 0) {
        const int offset = 2 - kk;
        std::memmove(&buffer[offset], &buffer[0], length);
        buffer[0] = '0';
        buffer[1] = '.';
        for (int i = 2; i < offset; i++)
            buffer[i] = '0';
        return &buffer[length + offset];
    }
    else if (length == 1) {
        buffer[1] = 'e';
        return WriteExponent(kk - 1, &buffer[2]);
    }
    else {
        std::memmove(&buffer[2], &buffer[1], length - 1);
        buffer[1] = '.';
        buffer[length + 1] = 'e';
        return WriteExponent(kk - 1, &buffer[0 + length + 2]);
    }
}
inline char* dtoa(double value, char* buffer) {
    if (value == 0) {
        buffer[0] = '0';
        buffer[1] = '.';
        buffer[2] = '0';
        return &buffer[3];
    }
    else {
        if (value < 0) {
            *buffer++ = '-';
            value = -value;
        }
        int length, K;
        Grisu2(value, buffer, &length, &K);
        return Prettify(buffer, length, K);
    }
}

#pragma GCC diagnostic pop

}
}
namespace rapidjson {
template <typename Encoding, typename Allocator = CrtAllocator>
class GenericStringBuffer {
public:
    typedef typename Encoding::Ch Ch;
    GenericStringBuffer(Allocator* allocator = 0, size_t capacity = kDefaultCapacity) : stack_(allocator, capacity) {}
    GenericStringBuffer(GenericStringBuffer&& rhs) : stack_(std::move(rhs.stack_)) {}
    GenericStringBuffer& operator=(GenericStringBuffer&& rhs) {
        if (&rhs != this)
            stack_ = std::move(rhs.stack_);
        return *this;
    }
    void Put(Ch c) { *stack_.template Push<Ch>() = c; }
    void Flush() {}
    void Clear() { stack_.Clear(); }
    void ShrinkToFit() {
        *stack_.template Push<Ch>() = '\0';
        stack_.ShrinkToFit();
        stack_.template Pop<Ch>(1);
    }
    Ch* Push(size_t count) { return stack_.template Push<Ch>(count); }
    void Pop(size_t count) { stack_.template Pop<Ch>(count); }
    const Ch* GetString() const {
        *stack_.template Push<Ch>() = '\0';
        stack_.template Pop<Ch>(1);
        return stack_.template Bottom<Ch>();
    }
    size_t GetSize() const { return stack_.GetSize(); }
    static const size_t kDefaultCapacity = 256;
    mutable internal::Stack<Allocator> stack_;
private:
    GenericStringBuffer(const GenericStringBuffer&);
    GenericStringBuffer& operator=(const GenericStringBuffer&);
};
typedef GenericStringBuffer<UTF8<> > StringBuffer;
template<>
inline void PutN(GenericStringBuffer<UTF8<> >& stream, char c, size_t n) {
    std::memset(stream.stack_.Push<char>(n), c, n * sizeof(c));
}
}
namespace rapidjson {
template<typename OutputStream, typename SourceEncoding = UTF8<>, typename TargetEncoding = UTF8<>, typename StackAllocator = CrtAllocator>
class Writer {
public:
    typedef typename SourceEncoding::Ch Ch;
    explicit
    Writer(OutputStream& os, StackAllocator* stackAllocator = 0, size_t levelDepth = kDefaultLevelDepth) :
        os_(&os), level_stack_(stackAllocator, levelDepth * sizeof(Level)), hasRoot_(false) {}
    explicit
    Writer(StackAllocator* allocator = 0, size_t levelDepth = kDefaultLevelDepth) :
        os_(0), level_stack_(allocator, levelDepth * sizeof(Level)), hasRoot_(false) {}
    void Reset(OutputStream& os) {
        os_ = &os;
        hasRoot_ = false;
        level_stack_.Clear();
    }
    bool IsComplete() const {
        return hasRoot_ && level_stack_.Empty();
    }
    bool Null() { Prefix(kNullType); return WriteNull(); }
    bool Bool(bool b) { Prefix(b ? kTrueType : kFalseType); return WriteBool(b); }
    bool Int(int i) { Prefix(kNumberType); return WriteInt(i); }
    bool Uint(unsigned u) { Prefix(kNumberType); return WriteUint(u); }
    bool Int64(int64_t i64) { Prefix(kNumberType); return WriteInt64(i64); }
    bool Uint64(uint64_t u64) { Prefix(kNumberType); return WriteUint64(u64); }
    bool Double(double d) { Prefix(kNumberType); return WriteDouble(d); }
    bool String(const Ch* str, SizeType length, bool copy = false) {
        (void)copy;
        Prefix(kStringType);
        return WriteString(str, length);
    }
    bool StartObject() {
        Prefix(kObjectType);
        new (level_stack_.template Push<Level>()) Level(false);
        return WriteStartObject();
    }
    bool Key(const Ch* str, SizeType length, bool copy = false) { return String(str, length, copy); }
    bool EndObject(SizeType memberCount = 0) {
        (void)memberCount;
        ((level_stack_.GetSize() >= sizeof(Level)) ? static_cast<void> (0) : __assert_fail ("level_stack_.GetSize() >= sizeof(Level)", "aapt/rapidjson/writer.h", 140, __PRETTY_FUNCTION__));
        ((!level_stack_.template Top<Level>()->inArray) ? static_cast<void> (0) : __assert_fail ("!level_stack_.template Top<Level>()->inArray", "aapt/rapidjson/writer.h", 141, __PRETTY_FUNCTION__));
        level_stack_.template Pop<Level>(1);
        bool ret = WriteEndObject();
        if (level_stack_.Empty())
            os_->Flush();
        return ret;
    }
    bool StartArray() {
        Prefix(kArrayType);
        new (level_stack_.template Push<Level>()) Level(true);
        return WriteStartArray();
    }
    bool EndArray(SizeType elementCount = 0) {
        (void)elementCount;
        ((level_stack_.GetSize() >= sizeof(Level)) ? static_cast<void> (0) : __assert_fail ("level_stack_.GetSize() >= sizeof(Level)", "aapt/rapidjson/writer.h", 157, __PRETTY_FUNCTION__));
        ((level_stack_.template Top<Level>()->inArray) ? static_cast<void> (0) : __assert_fail ("level_stack_.template Top<Level>()->inArray", "aapt/rapidjson/writer.h", 158, __PRETTY_FUNCTION__));
        level_stack_.template Pop<Level>(1);
        bool ret = WriteEndArray();
        if (level_stack_.Empty())
            os_->Flush();
        return ret;
    }
    bool String(const Ch* str) { return String(str, internal::StrLen(str)); }
    bool Key(const Ch* str) { return Key(str, internal::StrLen(str)); }
protected:
    struct Level {
        Level(bool inArray_) : valueCount(0), inArray(inArray_) {}
        size_t valueCount;
        bool inArray;
    };
    static const size_t kDefaultLevelDepth = 32;
    bool WriteNull() {
        os_->Put('n'); os_->Put('u'); os_->Put('l'); os_->Put('l'); return true;
    }
    bool WriteBool(bool b) {
        if (b) {
            os_->Put('t'); os_->Put('r'); os_->Put('u'); os_->Put('e');
        }
        else {
            os_->Put('f'); os_->Put('a'); os_->Put('l'); os_->Put('s'); os_->Put('e');
        }
        return true;
    }
    bool WriteInt(int i) {
        char buffer[11];
        const char* end = internal::i32toa(i, buffer);
        for (const char* p = buffer; p != end; ++p)
            os_->Put(*p);
        return true;
    }
    bool WriteUint(unsigned u) {
        char buffer[10];
        const char* end = internal::u32toa(u, buffer);
        for (const char* p = buffer; p != end; ++p)
            os_->Put(*p);
        return true;
    }
    bool WriteInt64(int64_t i64) {
        char buffer[21];
        const char* end = internal::i64toa(i64, buffer);
        for (const char* p = buffer; p != end; ++p)
            os_->Put(*p);
        return true;
    }
    bool WriteUint64(uint64_t u64) {
        char buffer[20];
        char* end = internal::u64toa(u64, buffer);
        for (char* p = buffer; p != end; ++p)
            os_->Put(*p);
        return true;
    }
    bool WriteDouble(double d) {
        char buffer[25];
        char* end = internal::dtoa(d, buffer);
        for (char* p = buffer; p != end; ++p)
            os_->Put(*p);
        return true;
    }
    bool WriteString(const Ch* str, SizeType length) {
        static const char hexDigits[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
        static const char escape[256] = {
            'u', 'u', 'u', 'u', 'u', 'u', 'u', 'u', 'b', 't', 'n', 'u', 'f', 'r', 'u', 'u',
            'u', 'u', 'u', 'u', 'u', 'u', 'u', 'u', 'u', 'u', 'u', 'u', 'u', 'u', 'u', 'u',
              0, 0, '"', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
              0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'\\', 0, 0, 0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
        };
        os_->Put('\"');
        GenericStringStream<SourceEncoding> is(str);
        while (is.Tell() < length) {
            const Ch c = is.Peek();
            if (!TargetEncoding::supportUnicode && (unsigned)c >= 0x80) {
                unsigned codepoint;
                if (!SourceEncoding::Decode(is, &codepoint))
                    return false;
                os_->Put('\\');
                os_->Put('u');
                if (codepoint <= 0xD7FF || (codepoint >= 0xE000 && codepoint <= 0xFFFF)) {
                    os_->Put(hexDigits[(codepoint >> 12) & 15]);
                    os_->Put(hexDigits[(codepoint >> 8) & 15]);
                    os_->Put(hexDigits[(codepoint >> 4) & 15]);
                    os_->Put(hexDigits[(codepoint ) & 15]);
                }
                else if (codepoint >= 0x010000 && codepoint <= 0x10FFFF) {
                    unsigned s = codepoint - 0x010000;
                    unsigned lead = (s >> 10) + 0xD800;
                    unsigned trail = (s & 0x3FF) + 0xDC00;
                    os_->Put(hexDigits[(lead >> 12) & 15]);
                    os_->Put(hexDigits[(lead >> 8) & 15]);
                    os_->Put(hexDigits[(lead >> 4) & 15]);
                    os_->Put(hexDigits[(lead ) & 15]);
                    os_->Put('\\');
                    os_->Put('u');
                    os_->Put(hexDigits[(trail >> 12) & 15]);
                    os_->Put(hexDigits[(trail >> 8) & 15]);
                    os_->Put(hexDigits[(trail >> 4) & 15]);
                    os_->Put(hexDigits[(trail ) & 15]);
                }
                else
                    return false;
            }
            else if ((sizeof(Ch) == 1 || (unsigned)c < 256) && escape[(unsigned char)c]) {
                is.Take();
                os_->Put('\\');
                os_->Put(escape[(unsigned char)c]);
                if (escape[(unsigned char)c] == 'u') {
                    os_->Put('0');
                    os_->Put('0');
                    os_->Put(hexDigits[(unsigned char)c >> 4]);
                    os_->Put(hexDigits[(unsigned char)c & 0xF]);
                }
            }
            else
                Transcoder<SourceEncoding, TargetEncoding>::Transcode(is, *os_);
        }
        os_->Put('\"');
        return true;
    }
    bool WriteStartObject() { os_->Put('{'); return true; }
    bool WriteEndObject() { os_->Put('}'); return true; }
    bool WriteStartArray() { os_->Put('['); return true; }
    bool WriteEndArray() { os_->Put(']'); return true; }
    void Prefix(Type type) {
        (void)type;
        if (level_stack_.GetSize() != 0) {
            Level* level = level_stack_.template Top<Level>();
            if (level->valueCount > 0) {
                if (level->inArray)
                    os_->Put(',');
                else
                    os_->Put((level->valueCount % 2 == 0) ? ',' : ':');
            }
            if (!level->inArray && level->valueCount % 2 == 0)
                ((type == kStringType) ? static_cast<void> (0) : __assert_fail ("type == kStringType", "aapt/rapidjson/writer.h", 324, __PRETTY_FUNCTION__));
            level->valueCount++;
        }
        else {
            ((!hasRoot_) ? static_cast<void> (0) : __assert_fail ("!hasRoot_", "aapt/rapidjson/writer.h", 328, __PRETTY_FUNCTION__));
            hasRoot_ = true;
        }
    }
    OutputStream* os_;
    internal::Stack<StackAllocator> level_stack_;
    bool hasRoot_;
private:
    Writer(const Writer&);
    Writer& operator=(const Writer&);
};
template<>
inline bool Writer<StringBuffer>::WriteInt(int i) {
    char *buffer = os_->Push(11);
    const char* end = internal::i32toa(i, buffer);
    os_->Pop(11 - (end - buffer));
    return true;
}
template<>
inline bool Writer<StringBuffer>::WriteUint(unsigned u) {
    char *buffer = os_->Push(10);
    const char* end = internal::u32toa(u, buffer);
    os_->Pop(10 - (end - buffer));
    return true;
}
template<>
inline bool Writer<StringBuffer>::WriteInt64(int64_t i64) {
    char *buffer = os_->Push(21);
    const char* end = internal::i64toa(i64, buffer);
    os_->Pop(21 - (end - buffer));
    return true;
}
template<>
inline bool Writer<StringBuffer>::WriteUint64(uint64_t u) {
    char *buffer = os_->Push(20);
    const char* end = internal::u64toa(u, buffer);
    os_->Pop(20 - (end - buffer));
    return true;
}
template<>
inline bool Writer<StringBuffer>::WriteDouble(double d) {
    char *buffer = os_->Push(25);
    char* end = internal::dtoa(d, buffer);
    os_->Pop(25 - (end - buffer));
    return true;
}
}
       
       
       
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename _Alloc, typename _Tp>
    class __alloctr_rebind_helper
    {
      template<typename _Alloc2, typename _Tp2>
 static constexpr true_type
 _S_chk(typename _Alloc2::template rebind<_Tp2>::other*);
      template<typename, typename>
 static constexpr false_type
 _S_chk(...);
    public:
      using __type = decltype(_S_chk<_Alloc, _Tp>(nullptr));
    };
  template<typename _Alloc, typename _Tp,
    bool = __alloctr_rebind_helper<_Alloc, _Tp>::__type::value>
    struct __alloctr_rebind;
  template<typename _Alloc, typename _Tp>
    struct __alloctr_rebind<_Alloc, _Tp, true>
    {
      typedef typename _Alloc::template rebind<_Tp>::other __type;
    };
  template<template<typename, typename...> class _Alloc, typename _Tp,
    typename _Up, typename... _Args>
    struct __alloctr_rebind<_Alloc<_Up, _Args...>, _Tp, false>
    {
      typedef _Alloc<_Tp, _Args...> __type;
    };
  template<typename _Alloc>
    struct allocator_traits
    {
      typedef _Alloc allocator_type;
      typedef typename _Alloc::value_type value_type;
private: template<typename _Tp> static typename _Tp::pointer _S_pointer_helper(_Tp*); static value_type* _S_pointer_helper(...); typedef decltype(_S_pointer_helper((_Alloc*)0)) __pointer; public:
      typedef __pointer pointer;
private: template<typename _Tp> static typename _Tp::const_pointer _S_const_pointer_helper(_Tp*); static typename pointer_traits<pointer>::template rebind<const value_type> _S_const_pointer_helper(...); typedef decltype(_S_const_pointer_helper((_Alloc*)0)) __const_pointer; public:
      typedef __const_pointer const_pointer;
private: template<typename _Tp> static typename _Tp::void_pointer _S_void_pointer_helper(_Tp*); static typename pointer_traits<pointer>::template rebind<void> _S_void_pointer_helper(...); typedef decltype(_S_void_pointer_helper((_Alloc*)0)) __void_pointer; public:
      typedef __void_pointer void_pointer;
private: template<typename _Tp> static typename _Tp::const_void_pointer _S_const_void_pointer_helper(_Tp*); static typename pointer_traits<pointer>::template rebind<const void> _S_const_void_pointer_helper(...); typedef decltype(_S_const_void_pointer_helper((_Alloc*)0)) __const_void_pointer; public:
      typedef __const_void_pointer const_void_pointer;
private: template<typename _Tp> static typename _Tp::difference_type _S_difference_type_helper(_Tp*); static typename pointer_traits<pointer>::difference_type _S_difference_type_helper(...); typedef decltype(_S_difference_type_helper((_Alloc*)0)) __difference_type; public:
      typedef __difference_type difference_type;
private: template<typename _Tp> static typename _Tp::size_type _S_size_type_helper(_Tp*); static typename make_unsigned<difference_type>::type _S_size_type_helper(...); typedef decltype(_S_size_type_helper((_Alloc*)0)) __size_type; public:
      typedef __size_type size_type;
private: template<typename _Tp> static typename _Tp::propagate_on_container_copy_assignment _S_propagate_on_container_copy_assignment_helper(_Tp*); static false_type _S_propagate_on_container_copy_assignment_helper(...); typedef decltype(_S_propagate_on_container_copy_assignment_helper((_Alloc*)0)) __propagate_on_container_copy_assignment; public:
      typedef __propagate_on_container_copy_assignment
 propagate_on_container_copy_assignment;
private: template<typename _Tp> static typename _Tp::propagate_on_container_move_assignment _S_propagate_on_container_move_assignment_helper(_Tp*); static false_type _S_propagate_on_container_move_assignment_helper(...); typedef decltype(_S_propagate_on_container_move_assignment_helper((_Alloc*)0)) __propagate_on_container_move_assignment; public:
      typedef __propagate_on_container_move_assignment
 propagate_on_container_move_assignment;
private: template<typename _Tp> static typename _Tp::propagate_on_container_swap _S_propagate_on_container_swap_helper(_Tp*); static false_type _S_propagate_on_container_swap_helper(...); typedef decltype(_S_propagate_on_container_swap_helper((_Alloc*)0)) __propagate_on_container_swap; public:
      typedef __propagate_on_container_swap propagate_on_container_swap;
      template<typename _Tp>
 using rebind_alloc = typename __alloctr_rebind<_Alloc, _Tp>::__type;
      template<typename _Tp>
 using rebind_traits = allocator_traits<rebind_alloc<_Tp>>;
    private:
      template<typename _Alloc2>
 struct __allocate_helper
 {
   template<typename _Alloc3,
     typename = decltype(std::declval<_Alloc3*>()->allocate(
    std::declval<size_type>(),
    std::declval<const_void_pointer>()))>
     static true_type __test(int);
   template<typename>
     static false_type __test(...);
   using type = decltype(__test<_Alloc>(0));
 };
      template<typename _Alloc2>
 using __has_allocate = typename __allocate_helper<_Alloc2>::type;
      template<typename _Alloc2,
        typename = _Require<__has_allocate<_Alloc2>>>
 static pointer
 _S_allocate(_Alloc2& __a, size_type __n, const_void_pointer __hint)
 { return __a.allocate(__n, __hint); }
      template<typename _Alloc2, typename _UnusedHint,
        typename = _Require<__not_<__has_allocate<_Alloc2>>>>
 static pointer
 _S_allocate(_Alloc2& __a, size_type __n, _UnusedHint)
 { return __a.allocate(__n); }
      template<typename _Tp, typename... _Args>
 struct __construct_helper
 {
   template<typename _Alloc2,
     typename = decltype(std::declval<_Alloc2*>()->construct(
    std::declval<_Tp*>(), std::declval<_Args>()...))>
     static true_type __test(int);
   template<typename>
     static false_type __test(...);
   using type = decltype(__test<_Alloc>(0));
 };
      template<typename _Tp, typename... _Args>
 using __has_construct
   = typename __construct_helper<_Tp, _Args...>::type;
      template<typename _Tp, typename... _Args>
 static _Require<__has_construct<_Tp, _Args...>>
 _S_construct(_Alloc& __a, _Tp* __p, _Args&&... __args)
 { __a.construct(__p, std::forward<_Args>(__args)...); }
      template<typename _Tp, typename... _Args>
 static
 _Require<__and_<__not_<__has_construct<_Tp, _Args...>>,
          is_constructible<_Tp, _Args...>>>
 _S_construct(_Alloc&, _Tp* __p, _Args&&... __args)
 { ::new((void*)__p) _Tp(std::forward<_Args>(__args)...); }
      template<typename _Tp>
 struct __destroy_helper
 {
   template<typename _Alloc2,
     typename = decltype(std::declval<_Alloc2*>()->destroy(
    std::declval<_Tp*>()))>
     static true_type __test(int);
   template<typename>
     static false_type __test(...);
   using type = decltype(__test<_Alloc>(0));
 };
      template<typename _Tp>
 using __has_destroy = typename __destroy_helper<_Tp>::type;
      template<typename _Tp>
 static _Require<__has_destroy<_Tp>>
 _S_destroy(_Alloc& __a, _Tp* __p)
 { __a.destroy(__p); }
      template<typename _Tp>
 static _Require<__not_<__has_destroy<_Tp>>>
 _S_destroy(_Alloc&, _Tp* __p)
 { __p->~_Tp(); }
      template<typename _Alloc2>
 struct __maxsize_helper
 {
   template<typename _Alloc3,
     typename = decltype(std::declval<_Alloc3*>()->max_size())>
     static true_type __test(int);
   template<typename>
     static false_type __test(...);
   using type = decltype(__test<_Alloc2>(0));
 };
      template<typename _Alloc2>
 using __has_max_size = typename __maxsize_helper<_Alloc2>::type;
      template<typename _Alloc2,
        typename = _Require<__has_max_size<_Alloc2>>>
 static size_type
 _S_max_size(_Alloc2& __a, int)
 { return __a.max_size(); }
      template<typename _Alloc2,
        typename = _Require<__not_<__has_max_size<_Alloc2>>>>
 static size_type
 _S_max_size(_Alloc2&, ...)
 { return __gnu_cxx::__numeric_traits<size_type>::__max; }
      template<typename _Alloc2>
 struct __select_helper
 {
   template<typename _Alloc3, typename
     = decltype(std::declval<_Alloc3*>()
  ->select_on_container_copy_construction())>
     static true_type __test(int);
   template<typename>
     static false_type __test(...);
   using type = decltype(__test<_Alloc2>(0));
 };
      template<typename _Alloc2>
 using __has_soccc = typename __select_helper<_Alloc2>::type;
      template<typename _Alloc2,
        typename = _Require<__has_soccc<_Alloc2>>>
 static _Alloc2
 _S_select(_Alloc2& __a, int)
 { return __a.select_on_container_copy_construction(); }
      template<typename _Alloc2,
        typename = _Require<__not_<__has_soccc<_Alloc2>>>>
 static _Alloc2
 _S_select(_Alloc2& __a, ...)
 { return __a; }
    public:
      static pointer
      allocate(_Alloc& __a, size_type __n)
      { return __a.allocate(__n); }
      static pointer
      allocate(_Alloc& __a, size_type __n, const_void_pointer __hint)
      { return _S_allocate(__a, __n, __hint); }
      static void deallocate(_Alloc& __a, pointer __p, size_type __n)
      { __a.deallocate(__p, __n); }
      template<typename _Tp, typename... _Args>
 static auto construct(_Alloc& __a, _Tp* __p, _Args&&... __args)
 -> decltype(_S_construct(__a, __p, std::forward<_Args>(__args)...))
 { _S_construct(__a, __p, std::forward<_Args>(__args)...); }
      template <class _Tp>
 static void destroy(_Alloc& __a, _Tp* __p)
 { _S_destroy(__a, __p); }
      static size_type max_size(const _Alloc& __a) noexcept
      { return _S_max_size(__a, 0); }
      static _Alloc
      select_on_container_copy_construction(const _Alloc& __rhs)
      { return _S_select(__rhs, 0); }
    };
  template<typename _Alloc>
    inline void
    __do_alloc_on_copy(_Alloc& __one, const _Alloc& __two, true_type)
    { __one = __two; }
  template<typename _Alloc>
    inline void
    __do_alloc_on_copy(_Alloc&, const _Alloc&, false_type)
    { }
  template<typename _Alloc>
    inline void __alloc_on_copy(_Alloc& __one, const _Alloc& __two)
    {
      typedef allocator_traits<_Alloc> __traits;
      typedef typename __traits::propagate_on_container_copy_assignment __pocca;
      __do_alloc_on_copy(__one, __two, __pocca());
    }
  template<typename _Alloc>
    inline _Alloc __alloc_on_copy(const _Alloc& __a)
    {
      typedef allocator_traits<_Alloc> __traits;
      return __traits::select_on_container_copy_construction(__a);
    }
  template<typename _Alloc>
    inline void __do_alloc_on_move(_Alloc& __one, _Alloc& __two, true_type)
    { __one = std::move(__two); }
  template<typename _Alloc>
    inline void __do_alloc_on_move(_Alloc&, _Alloc&, false_type)
    { }
  template<typename _Alloc>
    inline void __alloc_on_move(_Alloc& __one, _Alloc& __two)
    {
      typedef allocator_traits<_Alloc> __traits;
      typedef typename __traits::propagate_on_container_move_assignment __pocma;
      __do_alloc_on_move(__one, __two, __pocma());
    }
  template<typename _Alloc>
    inline void __do_alloc_on_swap(_Alloc& __one, _Alloc& __two, true_type)
    {
      using std::swap;
      swap(__one, __two);
    }
  template<typename _Alloc>
    inline void __do_alloc_on_swap(_Alloc&, _Alloc&, false_type)
    { }
  template<typename _Alloc>
    inline void __alloc_on_swap(_Alloc& __one, _Alloc& __two)
    {
      typedef allocator_traits<_Alloc> __traits;
      typedef typename __traits::propagate_on_container_swap __pocs;
      __do_alloc_on_swap(__one, __two, __pocs());
    }
  template<typename _Alloc>
    class __is_copy_insertable_impl
    {
      typedef allocator_traits<_Alloc> _Traits;
      template<typename _Up, typename
        = decltype(_Traits::construct(std::declval<_Alloc&>(),
          std::declval<_Up*>(),
          std::declval<const _Up&>()))>
 static true_type
 _M_select(int);
      template<typename _Up>
 static false_type
 _M_select(...);
    public:
      typedef decltype(_M_select<typename _Alloc::value_type>(0)) type;
    };
  template<typename _Alloc>
    struct __is_copy_insertable
    : __is_copy_insertable_impl<_Alloc>::type
    { };
  template<typename _Tp>
    struct __is_copy_insertable<allocator<_Tp>>
    : is_copy_constructible<_Tp>
    { };

}
namespace __gnu_cxx __attribute__ ((__visibility__ ("default")))
{

  template<typename _Alloc>
    struct __allocator_always_compares_equal : std::false_type { };
  template<typename _Tp>
    struct __allocator_always_compares_equal<std::allocator<_Tp>>
    : std::true_type { };
  template<typename, typename> struct array_allocator;
  template<typename _Tp, typename _Array>
    struct __allocator_always_compares_equal<array_allocator<_Tp, _Array>>
    : std::true_type { };
  template<typename> struct bitmap_allocator;
  template<typename _Tp>
    struct __allocator_always_compares_equal<bitmap_allocator<_Tp>>
    : std::true_type { };
  template<typename> struct malloc_allocator;
  template<typename _Tp>
    struct __allocator_always_compares_equal<malloc_allocator<_Tp>>
    : std::true_type { };
  template<typename> struct mt_allocator;
  template<typename _Tp>
    struct __allocator_always_compares_equal<mt_allocator<_Tp>>
    : std::true_type { };
  template<typename> struct new_allocator;
  template<typename _Tp>
    struct __allocator_always_compares_equal<new_allocator<_Tp>>
    : std::true_type { };
  template<typename> struct pool_allocator;
  template<typename _Tp>
    struct __allocator_always_compares_equal<pool_allocator<_Tp>>
    : std::true_type { };
template<typename _Alloc>
  struct __alloc_traits
  : std::allocator_traits<_Alloc>
  {
    typedef _Alloc allocator_type;
    typedef std::allocator_traits<_Alloc> _Base_type;
    typedef typename _Base_type::value_type value_type;
    typedef typename _Base_type::pointer pointer;
    typedef typename _Base_type::const_pointer const_pointer;
    typedef typename _Base_type::size_type size_type;
    typedef typename _Base_type::difference_type difference_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    using _Base_type::allocate;
    using _Base_type::deallocate;
    using _Base_type::construct;
    using _Base_type::destroy;
    using _Base_type::max_size;
  private:
    template<typename _Ptr>
      using __is_custom_pointer
 = std::__and_<std::is_same<pointer, _Ptr>,
        std::__not_<std::is_pointer<_Ptr>>>;
  public:
    template<typename _Ptr, typename... _Args>
      static typename std::enable_if<__is_custom_pointer<_Ptr>::value>::type
      construct(_Alloc& __a, _Ptr __p, _Args&&... __args)
      {
 _Base_type::construct(__a, std::addressof(*__p),
         std::forward<_Args>(__args)...);
      }
    template<typename _Ptr>
      static typename std::enable_if<__is_custom_pointer<_Ptr>::value>::type
      destroy(_Alloc& __a, _Ptr __p)
      { _Base_type::destroy(__a, std::addressof(*__p)); }
    static _Alloc _S_select_on_copy(const _Alloc& __a)
    { return _Base_type::select_on_container_copy_construction(__a); }
    static void _S_on_swap(_Alloc& __a, _Alloc& __b)
    { std::__alloc_on_swap(__a, __b); }
    static constexpr bool _S_propagate_on_copy_assign()
    { return _Base_type::propagate_on_container_copy_assignment::value; }
    static constexpr bool _S_propagate_on_move_assign()
    { return _Base_type::propagate_on_container_move_assignment::value; }
    static constexpr bool _S_propagate_on_swap()
    { return _Base_type::propagate_on_container_swap::value; }
    static constexpr bool _S_always_equal()
    { return __allocator_always_compares_equal<_Alloc>::value; }
    static constexpr bool _S_nothrow_move()
    { return _S_propagate_on_move_assign() || _S_always_equal(); }
    static constexpr bool _S_nothrow_swap()
    {
      using std::swap;
      return !_S_propagate_on_swap()
        || noexcept(swap(std::declval<_Alloc&>(), std::declval<_Alloc&>()));
    }
    template<typename _Tp>
      struct rebind
      { typedef typename _Base_type::template rebind_alloc<_Tp> other; };
  };

}
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename _T1, typename... _Args>
    inline void
    _Construct(_T1* __p, _Args&&... __args)
    { ::new(static_cast<void*>(__p)) _T1(std::forward<_Args>(__args)...); }
  template<typename _Tp>
    inline void
    _Destroy(_Tp* __pointer)
    { __pointer->~_Tp(); }
  template<bool>
    struct _Destroy_aux
    {
      template<typename _ForwardIterator>
        static void
        __destroy(_ForwardIterator __first, _ForwardIterator __last)
 {
   for (; __first != __last; ++__first)
     std::_Destroy(std::__addressof(*__first));
 }
    };
  template<>
    struct _Destroy_aux<true>
    {
      template<typename _ForwardIterator>
        static void
        __destroy(_ForwardIterator, _ForwardIterator) { }
    };
  template<typename _ForwardIterator>
    inline void
    _Destroy(_ForwardIterator __first, _ForwardIterator __last)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
                       _Value_type;
      std::_Destroy_aux<__has_trivial_destructor(_Value_type)>::
 __destroy(__first, __last);
    }
  template<typename _ForwardIterator, typename _Allocator>
    void
    _Destroy(_ForwardIterator __first, _ForwardIterator __last,
      _Allocator& __alloc)
    {
      typedef __gnu_cxx::__alloc_traits<_Allocator> __traits;
      for (; __first != __last; ++__first)
 __traits::destroy(__alloc, std::__addressof(*__first));
    }
  template<typename _ForwardIterator, typename _Tp>
    inline void
    _Destroy(_ForwardIterator __first, _ForwardIterator __last,
      allocator<_Tp>&)
    {
      _Destroy(__first, __last);
    }

}
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<bool _TrivialValueTypes>
    struct __uninitialized_copy
    {
      template<typename _InputIterator, typename _ForwardIterator>
        static _ForwardIterator
        __uninit_copy(_InputIterator __first, _InputIterator __last,
        _ForwardIterator __result)
        {
   _ForwardIterator __cur = __result;
   try
     {
       for (; __first != __last; ++__first, ++__cur)
  std::_Construct(std::__addressof(*__cur), *__first);
       return __cur;
     }
   catch(...)
     {
       std::_Destroy(__result, __cur);
       throw;
     }
 }
    };
  template<>
    struct __uninitialized_copy<true>
    {
      template<typename _InputIterator, typename _ForwardIterator>
        static _ForwardIterator
        __uninit_copy(_InputIterator __first, _InputIterator __last,
        _ForwardIterator __result)
        { return std::copy(__first, __last, __result); }
    };
  template<typename _InputIterator, typename _ForwardIterator>
    inline _ForwardIterator
    uninitialized_copy(_InputIterator __first, _InputIterator __last,
         _ForwardIterator __result)
    {
      typedef typename iterator_traits<_InputIterator>::value_type
 _ValueType1;
      typedef typename iterator_traits<_ForwardIterator>::value_type
 _ValueType2;
      typedef typename iterator_traits<_InputIterator>::reference _RefType;
      const bool __assignable = is_assignable<_ValueType1, _RefType>::value;
      return std::__uninitialized_copy<__is_trivial(_ValueType1)
           && __is_trivial(_ValueType2)
           && __assignable>::
 __uninit_copy(__first, __last, __result);
    }
  template<bool _TrivialValueType>
    struct __uninitialized_fill
    {
      template<typename _ForwardIterator, typename _Tp>
        static void
        __uninit_fill(_ForwardIterator __first, _ForwardIterator __last,
        const _Tp& __x)
        {
   _ForwardIterator __cur = __first;
   try
     {
       for (; __cur != __last; ++__cur)
  std::_Construct(std::__addressof(*__cur), __x);
     }
   catch(...)
     {
       std::_Destroy(__first, __cur);
       throw;
     }
 }
    };
  template<>
    struct __uninitialized_fill<true>
    {
      template<typename _ForwardIterator, typename _Tp>
        static void
        __uninit_fill(_ForwardIterator __first, _ForwardIterator __last,
        const _Tp& __x)
        { std::fill(__first, __last, __x); }
    };
  template<typename _ForwardIterator, typename _Tp>
    inline void
    uninitialized_fill(_ForwardIterator __first, _ForwardIterator __last,
         const _Tp& __x)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
 _ValueType;
      const bool __assignable = is_copy_assignable<_ValueType>::value;
      std::__uninitialized_fill<__is_trivial(_ValueType) && __assignable>::
 __uninit_fill(__first, __last, __x);
    }
  template<bool _TrivialValueType>
    struct __uninitialized_fill_n
    {
      template<typename _ForwardIterator, typename _Size, typename _Tp>
        static void
        __uninit_fill_n(_ForwardIterator __first, _Size __n,
   const _Tp& __x)
        {
   _ForwardIterator __cur = __first;
   try
     {
       for (; __n > 0; --__n, ++__cur)
  std::_Construct(std::__addressof(*__cur), __x);
     }
   catch(...)
     {
       std::_Destroy(__first, __cur);
       throw;
     }
 }
    };
  template<>
    struct __uninitialized_fill_n<true>
    {
      template<typename _ForwardIterator, typename _Size, typename _Tp>
        static void
        __uninit_fill_n(_ForwardIterator __first, _Size __n,
   const _Tp& __x)
        { std::fill_n(__first, __n, __x); }
    };
  template<typename _ForwardIterator, typename _Size, typename _Tp>
    inline void
    uninitialized_fill_n(_ForwardIterator __first, _Size __n, const _Tp& __x)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
 _ValueType;
      const bool __assignable = is_copy_assignable<_ValueType>::value;
      std::__uninitialized_fill_n<__is_trivial(_ValueType) && __assignable>::
 __uninit_fill_n(__first, __n, __x);
    }
  template<typename _InputIterator, typename _ForwardIterator,
    typename _Allocator>
    _ForwardIterator
    __uninitialized_copy_a(_InputIterator __first, _InputIterator __last,
      _ForwardIterator __result, _Allocator& __alloc)
    {
      _ForwardIterator __cur = __result;
      try
 {
   typedef __gnu_cxx::__alloc_traits<_Allocator> __traits;
   for (; __first != __last; ++__first, ++__cur)
     __traits::construct(__alloc, std::__addressof(*__cur), *__first);
   return __cur;
 }
      catch(...)
 {
   std::_Destroy(__result, __cur, __alloc);
   throw;
 }
    }
  template<typename _InputIterator, typename _ForwardIterator, typename _Tp>
    inline _ForwardIterator
    __uninitialized_copy_a(_InputIterator __first, _InputIterator __last,
      _ForwardIterator __result, allocator<_Tp>&)
    { return std::uninitialized_copy(__first, __last, __result); }
  template<typename _InputIterator, typename _ForwardIterator,
    typename _Allocator>
    inline _ForwardIterator
    __uninitialized_move_a(_InputIterator __first, _InputIterator __last,
      _ForwardIterator __result, _Allocator& __alloc)
    {
      return std::__uninitialized_copy_a(std::make_move_iterator(__first),
      std::make_move_iterator(__last),
      __result, __alloc);
    }
  template<typename _InputIterator, typename _ForwardIterator,
    typename _Allocator>
    inline _ForwardIterator
    __uninitialized_move_if_noexcept_a(_InputIterator __first,
           _InputIterator __last,
           _ForwardIterator __result,
           _Allocator& __alloc)
    {
      return std::__uninitialized_copy_a
 (std::__make_move_if_noexcept_iterator(__first),
  std::__make_move_if_noexcept_iterator(__last), __result, __alloc);
    }
  template<typename _ForwardIterator, typename _Tp, typename _Allocator>
    void
    __uninitialized_fill_a(_ForwardIterator __first, _ForwardIterator __last,
      const _Tp& __x, _Allocator& __alloc)
    {
      _ForwardIterator __cur = __first;
      try
 {
   typedef __gnu_cxx::__alloc_traits<_Allocator> __traits;
   for (; __cur != __last; ++__cur)
     __traits::construct(__alloc, std::__addressof(*__cur), __x);
 }
      catch(...)
 {
   std::_Destroy(__first, __cur, __alloc);
   throw;
 }
    }
  template<typename _ForwardIterator, typename _Tp, typename _Tp2>
    inline void
    __uninitialized_fill_a(_ForwardIterator __first, _ForwardIterator __last,
      const _Tp& __x, allocator<_Tp2>&)
    { std::uninitialized_fill(__first, __last, __x); }
  template<typename _ForwardIterator, typename _Size, typename _Tp,
    typename _Allocator>
    void
    __uninitialized_fill_n_a(_ForwardIterator __first, _Size __n,
        const _Tp& __x, _Allocator& __alloc)
    {
      _ForwardIterator __cur = __first;
      try
 {
   typedef __gnu_cxx::__alloc_traits<_Allocator> __traits;
   for (; __n > 0; --__n, ++__cur)
     __traits::construct(__alloc, std::__addressof(*__cur), __x);
 }
      catch(...)
 {
   std::_Destroy(__first, __cur, __alloc);
   throw;
 }
    }
  template<typename _ForwardIterator, typename _Size, typename _Tp,
    typename _Tp2>
    inline void
    __uninitialized_fill_n_a(_ForwardIterator __first, _Size __n,
        const _Tp& __x, allocator<_Tp2>&)
    { std::uninitialized_fill_n(__first, __n, __x); }
  template<typename _InputIterator1, typename _InputIterator2,
    typename _ForwardIterator, typename _Allocator>
    inline _ForwardIterator
    __uninitialized_copy_move(_InputIterator1 __first1,
         _InputIterator1 __last1,
         _InputIterator2 __first2,
         _InputIterator2 __last2,
         _ForwardIterator __result,
         _Allocator& __alloc)
    {
      _ForwardIterator __mid = std::__uninitialized_copy_a(__first1, __last1,
          __result,
          __alloc);
      try
 {
   return std::__uninitialized_move_a(__first2, __last2, __mid, __alloc);
 }
      catch(...)
 {
   std::_Destroy(__result, __mid, __alloc);
   throw;
 }
    }
  template<typename _InputIterator1, typename _InputIterator2,
    typename _ForwardIterator, typename _Allocator>
    inline _ForwardIterator
    __uninitialized_move_copy(_InputIterator1 __first1,
         _InputIterator1 __last1,
         _InputIterator2 __first2,
         _InputIterator2 __last2,
         _ForwardIterator __result,
         _Allocator& __alloc)
    {
      _ForwardIterator __mid = std::__uninitialized_move_a(__first1, __last1,
          __result,
          __alloc);
      try
 {
   return std::__uninitialized_copy_a(__first2, __last2, __mid, __alloc);
 }
      catch(...)
 {
   std::_Destroy(__result, __mid, __alloc);
   throw;
 }
    }
  template<typename _ForwardIterator, typename _Tp, typename _InputIterator,
    typename _Allocator>
    inline _ForwardIterator
    __uninitialized_fill_move(_ForwardIterator __result, _ForwardIterator __mid,
         const _Tp& __x, _InputIterator __first,
         _InputIterator __last, _Allocator& __alloc)
    {
      std::__uninitialized_fill_a(__result, __mid, __x, __alloc);
      try
 {
   return std::__uninitialized_move_a(__first, __last, __mid, __alloc);
 }
      catch(...)
 {
   std::_Destroy(__result, __mid, __alloc);
   throw;
 }
    }
  template<typename _InputIterator, typename _ForwardIterator, typename _Tp,
    typename _Allocator>
    inline void
    __uninitialized_move_fill(_InputIterator __first1, _InputIterator __last1,
         _ForwardIterator __first2,
         _ForwardIterator __last2, const _Tp& __x,
         _Allocator& __alloc)
    {
      _ForwardIterator __mid2 = std::__uninitialized_move_a(__first1, __last1,
           __first2,
           __alloc);
      try
 {
   std::__uninitialized_fill_a(__mid2, __last2, __x, __alloc);
 }
      catch(...)
 {
   std::_Destroy(__first2, __mid2, __alloc);
   throw;
 }
    }
  template<bool _TrivialValueType>
    struct __uninitialized_default_1
    {
      template<typename _ForwardIterator>
        static void
        __uninit_default(_ForwardIterator __first, _ForwardIterator __last)
        {
   _ForwardIterator __cur = __first;
   try
     {
       for (; __cur != __last; ++__cur)
  std::_Construct(std::__addressof(*__cur));
     }
   catch(...)
     {
       std::_Destroy(__first, __cur);
       throw;
     }
 }
    };
  template<>
    struct __uninitialized_default_1<true>
    {
      template<typename _ForwardIterator>
        static void
        __uninit_default(_ForwardIterator __first, _ForwardIterator __last)
        {
   typedef typename iterator_traits<_ForwardIterator>::value_type
     _ValueType;
   std::fill(__first, __last, _ValueType());
 }
    };
  template<bool _TrivialValueType>
    struct __uninitialized_default_n_1
    {
      template<typename _ForwardIterator, typename _Size>
        static void
        __uninit_default_n(_ForwardIterator __first, _Size __n)
        {
   _ForwardIterator __cur = __first;
   try
     {
       for (; __n > 0; --__n, ++__cur)
  std::_Construct(std::__addressof(*__cur));
     }
   catch(...)
     {
       std::_Destroy(__first, __cur);
       throw;
     }
 }
    };
  template<>
    struct __uninitialized_default_n_1<true>
    {
      template<typename _ForwardIterator, typename _Size>
        static void
        __uninit_default_n(_ForwardIterator __first, _Size __n)
        {
   typedef typename iterator_traits<_ForwardIterator>::value_type
     _ValueType;
   std::fill_n(__first, __n, _ValueType());
 }
    };
  template<typename _ForwardIterator>
    inline void
    __uninitialized_default(_ForwardIterator __first,
       _ForwardIterator __last)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
 _ValueType;
      const bool __assignable = is_copy_assignable<_ValueType>::value;
      std::__uninitialized_default_1<__is_trivial(_ValueType)
         && __assignable>::
 __uninit_default(__first, __last);
    }
  template<typename _ForwardIterator, typename _Size>
    inline void
    __uninitialized_default_n(_ForwardIterator __first, _Size __n)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
 _ValueType;
      const bool __assignable = is_copy_assignable<_ValueType>::value;
      std::__uninitialized_default_n_1<__is_trivial(_ValueType)
           && __assignable>::
 __uninit_default_n(__first, __n);
    }
  template<typename _ForwardIterator, typename _Allocator>
    void
    __uninitialized_default_a(_ForwardIterator __first,
         _ForwardIterator __last,
         _Allocator& __alloc)
    {
      _ForwardIterator __cur = __first;
      try
 {
   typedef __gnu_cxx::__alloc_traits<_Allocator> __traits;
   for (; __cur != __last; ++__cur)
     __traits::construct(__alloc, std::__addressof(*__cur));
 }
      catch(...)
 {
   std::_Destroy(__first, __cur, __alloc);
   throw;
 }
    }
  template<typename _ForwardIterator, typename _Tp>
    inline void
    __uninitialized_default_a(_ForwardIterator __first,
         _ForwardIterator __last,
         allocator<_Tp>&)
    { std::__uninitialized_default(__first, __last); }
  template<typename _ForwardIterator, typename _Size, typename _Allocator>
    void
    __uninitialized_default_n_a(_ForwardIterator __first, _Size __n,
    _Allocator& __alloc)
    {
      _ForwardIterator __cur = __first;
      try
 {
   typedef __gnu_cxx::__alloc_traits<_Allocator> __traits;
   for (; __n > 0; --__n, ++__cur)
     __traits::construct(__alloc, std::__addressof(*__cur));
 }
      catch(...)
 {
   std::_Destroy(__first, __cur, __alloc);
   throw;
 }
    }
  template<typename _ForwardIterator, typename _Size, typename _Tp>
    inline void
    __uninitialized_default_n_a(_ForwardIterator __first, _Size __n,
    allocator<_Tp>&)
    { std::__uninitialized_default_n(__first, __n); }
  template<typename _InputIterator, typename _Size,
    typename _ForwardIterator>
    _ForwardIterator
    __uninitialized_copy_n(_InputIterator __first, _Size __n,
      _ForwardIterator __result, input_iterator_tag)
    {
      _ForwardIterator __cur = __result;
      try
 {
   for (; __n > 0; --__n, ++__first, ++__cur)
     std::_Construct(std::__addressof(*__cur), *__first);
   return __cur;
 }
      catch(...)
 {
   std::_Destroy(__result, __cur);
   throw;
 }
    }
  template<typename _RandomAccessIterator, typename _Size,
    typename _ForwardIterator>
    inline _ForwardIterator
    __uninitialized_copy_n(_RandomAccessIterator __first, _Size __n,
      _ForwardIterator __result,
      random_access_iterator_tag)
    { return std::uninitialized_copy(__first, __first + __n, __result); }
  template<typename _InputIterator, typename _Size, typename _ForwardIterator>
    inline _ForwardIterator
    uninitialized_copy_n(_InputIterator __first, _Size __n,
    _ForwardIterator __result)
    { return std::__uninitialized_copy_n(__first, __n, __result,
      std::__iterator_category(__first)); }

}
namespace std __attribute__ ((__visibility__ ("default")))
{

  inline size_t
  __deque_buf_size(size_t __size)
  { return (__size < 512
     ? size_t(512 / __size) : size_t(1)); }
  template<typename _Tp, typename _Ref, typename _Ptr>
    struct _Deque_iterator
    {
      typedef _Deque_iterator<_Tp, _Tp&, _Tp*> iterator;
      typedef _Deque_iterator<_Tp, const _Tp&, const _Tp*> const_iterator;
      static size_t _S_buffer_size() noexcept
      { return __deque_buf_size(sizeof(_Tp)); }
      typedef std::random_access_iterator_tag iterator_category;
      typedef _Tp value_type;
      typedef _Ptr pointer;
      typedef _Ref reference;
      typedef size_t size_type;
      typedef ptrdiff_t difference_type;
      typedef _Tp** _Map_pointer;
      typedef _Deque_iterator _Self;
      _Tp* _M_cur;
      _Tp* _M_first;
      _Tp* _M_last;
      _Map_pointer _M_node;
      _Deque_iterator(_Tp* __x, _Map_pointer __y) noexcept
      : _M_cur(__x), _M_first(*__y),
        _M_last(*__y + _S_buffer_size()), _M_node(__y) { }
      _Deque_iterator() noexcept
      : _M_cur(0), _M_first(0), _M_last(0), _M_node(0) { }
      _Deque_iterator(const iterator& __x) noexcept
      : _M_cur(__x._M_cur), _M_first(__x._M_first),
        _M_last(__x._M_last), _M_node(__x._M_node) { }
      iterator
      _M_const_cast() const noexcept
      { return iterator(_M_cur, _M_node); }
      reference
      operator*() const noexcept
      { return *_M_cur; }
      pointer
      operator->() const noexcept
      { return _M_cur; }
      _Self&
      operator++() noexcept
      {
 ++_M_cur;
 if (_M_cur == _M_last)
   {
     _M_set_node(_M_node + 1);
     _M_cur = _M_first;
   }
 return *this;
      }
      _Self
      operator++(int) noexcept
      {
 _Self __tmp = *this;
 ++*this;
 return __tmp;
      }
      _Self&
      operator--() noexcept
      {
 if (_M_cur == _M_first)
   {
     _M_set_node(_M_node - 1);
     _M_cur = _M_last;
   }
 --_M_cur;
 return *this;
      }
      _Self
      operator--(int) noexcept
      {
 _Self __tmp = *this;
 --*this;
 return __tmp;
      }
      _Self&
      operator+=(difference_type __n) noexcept
      {
 const difference_type __offset = __n + (_M_cur - _M_first);
 if (__offset >= 0 && __offset < difference_type(_S_buffer_size()))
   _M_cur += __n;
 else
   {
     const difference_type __node_offset =
       __offset > 0 ? __offset / difference_type(_S_buffer_size())
                    : -difference_type((-__offset - 1)
           / _S_buffer_size()) - 1;
     _M_set_node(_M_node + __node_offset);
     _M_cur = _M_first + (__offset - __node_offset
     * difference_type(_S_buffer_size()));
   }
 return *this;
      }
      _Self
      operator+(difference_type __n) const noexcept
      {
 _Self __tmp = *this;
 return __tmp += __n;
      }
      _Self&
      operator-=(difference_type __n) noexcept
      { return *this += -__n; }
      _Self
      operator-(difference_type __n) const noexcept
      {
 _Self __tmp = *this;
 return __tmp -= __n;
      }
      reference
      operator[](difference_type __n) const noexcept
      { return *(*this + __n); }
      void
      _M_set_node(_Map_pointer __new_node) noexcept
      {
 _M_node = __new_node;
 _M_first = *__new_node;
 _M_last = _M_first + difference_type(_S_buffer_size());
      }
    };
  template<typename _Tp, typename _Ref, typename _Ptr>
    inline bool
    operator==(const _Deque_iterator<_Tp, _Ref, _Ptr>& __x,
        const _Deque_iterator<_Tp, _Ref, _Ptr>& __y) noexcept
    { return __x._M_cur == __y._M_cur; }
  template<typename _Tp, typename _RefL, typename _PtrL,
    typename _RefR, typename _PtrR>
    inline bool
    operator==(const _Deque_iterator<_Tp, _RefL, _PtrL>& __x,
        const _Deque_iterator<_Tp, _RefR, _PtrR>& __y) noexcept
    { return __x._M_cur == __y._M_cur; }
  template<typename _Tp, typename _Ref, typename _Ptr>
    inline bool
    operator!=(const _Deque_iterator<_Tp, _Ref, _Ptr>& __x,
        const _Deque_iterator<_Tp, _Ref, _Ptr>& __y) noexcept
    { return !(__x == __y); }
  template<typename _Tp, typename _RefL, typename _PtrL,
    typename _RefR, typename _PtrR>
    inline bool
    operator!=(const _Deque_iterator<_Tp, _RefL, _PtrL>& __x,
        const _Deque_iterator<_Tp, _RefR, _PtrR>& __y) noexcept
    { return !(__x == __y); }
  template<typename _Tp, typename _Ref, typename _Ptr>
    inline bool
    operator<(const _Deque_iterator<_Tp, _Ref, _Ptr>& __x,
       const _Deque_iterator<_Tp, _Ref, _Ptr>& __y) noexcept
    { return (__x._M_node == __y._M_node) ? (__x._M_cur < __y._M_cur)
                                          : (__x._M_node < __y._M_node); }
  template<typename _Tp, typename _RefL, typename _PtrL,
    typename _RefR, typename _PtrR>
    inline bool
    operator<(const _Deque_iterator<_Tp, _RefL, _PtrL>& __x,
       const _Deque_iterator<_Tp, _RefR, _PtrR>& __y) noexcept
    { return (__x._M_node == __y._M_node) ? (__x._M_cur < __y._M_cur)
                                   : (__x._M_node < __y._M_node); }
  template<typename _Tp, typename _Ref, typename _Ptr>
    inline bool
    operator>(const _Deque_iterator<_Tp, _Ref, _Ptr>& __x,
       const _Deque_iterator<_Tp, _Ref, _Ptr>& __y) noexcept
    { return __y < __x; }
  template<typename _Tp, typename _RefL, typename _PtrL,
    typename _RefR, typename _PtrR>
    inline bool
    operator>(const _Deque_iterator<_Tp, _RefL, _PtrL>& __x,
       const _Deque_iterator<_Tp, _RefR, _PtrR>& __y) noexcept
    { return __y < __x; }
  template<typename _Tp, typename _Ref, typename _Ptr>
    inline bool
    operator<=(const _Deque_iterator<_Tp, _Ref, _Ptr>& __x,
        const _Deque_iterator<_Tp, _Ref, _Ptr>& __y) noexcept
    { return !(__y < __x); }
  template<typename _Tp, typename _RefL, typename _PtrL,
    typename _RefR, typename _PtrR>
    inline bool
    operator<=(const _Deque_iterator<_Tp, _RefL, _PtrL>& __x,
        const _Deque_iterator<_Tp, _RefR, _PtrR>& __y) noexcept
    { return !(__y < __x); }
  template<typename _Tp, typename _Ref, typename _Ptr>
    inline bool
    operator>=(const _Deque_iterator<_Tp, _Ref, _Ptr>& __x,
        const _Deque_iterator<_Tp, _Ref, _Ptr>& __y) noexcept
    { return !(__x < __y); }
  template<typename _Tp, typename _RefL, typename _PtrL,
    typename _RefR, typename _PtrR>
    inline bool
    operator>=(const _Deque_iterator<_Tp, _RefL, _PtrL>& __x,
        const _Deque_iterator<_Tp, _RefR, _PtrR>& __y) noexcept
    { return !(__x < __y); }
  template<typename _Tp, typename _Ref, typename _Ptr>
    inline typename _Deque_iterator<_Tp, _Ref, _Ptr>::difference_type
    operator-(const _Deque_iterator<_Tp, _Ref, _Ptr>& __x,
       const _Deque_iterator<_Tp, _Ref, _Ptr>& __y) noexcept
    {
      return typename _Deque_iterator<_Tp, _Ref, _Ptr>::difference_type
 (_Deque_iterator<_Tp, _Ref, _Ptr>::_S_buffer_size())
 * (__x._M_node - __y._M_node - 1) + (__x._M_cur - __x._M_first)
 + (__y._M_last - __y._M_cur);
    }
  template<typename _Tp, typename _RefL, typename _PtrL,
    typename _RefR, typename _PtrR>
    inline typename _Deque_iterator<_Tp, _RefL, _PtrL>::difference_type
    operator-(const _Deque_iterator<_Tp, _RefL, _PtrL>& __x,
       const _Deque_iterator<_Tp, _RefR, _PtrR>& __y) noexcept
    {
      return typename _Deque_iterator<_Tp, _RefL, _PtrL>::difference_type
 (_Deque_iterator<_Tp, _RefL, _PtrL>::_S_buffer_size())
 * (__x._M_node - __y._M_node - 1) + (__x._M_cur - __x._M_first)
 + (__y._M_last - __y._M_cur);
    }
  template<typename _Tp, typename _Ref, typename _Ptr>
    inline _Deque_iterator<_Tp, _Ref, _Ptr>
    operator+(ptrdiff_t __n, const _Deque_iterator<_Tp, _Ref, _Ptr>& __x)
    noexcept
    { return __x + __n; }
  template<typename _Tp>
    void
    fill(const _Deque_iterator<_Tp, _Tp&, _Tp*>&,
  const _Deque_iterator<_Tp, _Tp&, _Tp*>&, const _Tp&);
  template<typename _Tp>
    _Deque_iterator<_Tp, _Tp&, _Tp*>
    copy(_Deque_iterator<_Tp, const _Tp&, const _Tp*>,
  _Deque_iterator<_Tp, const _Tp&, const _Tp*>,
  _Deque_iterator<_Tp, _Tp&, _Tp*>);
  template<typename _Tp>
    inline _Deque_iterator<_Tp, _Tp&, _Tp*>
    copy(_Deque_iterator<_Tp, _Tp&, _Tp*> __first,
  _Deque_iterator<_Tp, _Tp&, _Tp*> __last,
  _Deque_iterator<_Tp, _Tp&, _Tp*> __result)
    { return std::copy(_Deque_iterator<_Tp, const _Tp&, const _Tp*>(__first),
         _Deque_iterator<_Tp, const _Tp&, const _Tp*>(__last),
         __result); }
  template<typename _Tp>
    _Deque_iterator<_Tp, _Tp&, _Tp*>
    copy_backward(_Deque_iterator<_Tp, const _Tp&, const _Tp*>,
    _Deque_iterator<_Tp, const _Tp&, const _Tp*>,
    _Deque_iterator<_Tp, _Tp&, _Tp*>);
  template<typename _Tp>
    inline _Deque_iterator<_Tp, _Tp&, _Tp*>
    copy_backward(_Deque_iterator<_Tp, _Tp&, _Tp*> __first,
    _Deque_iterator<_Tp, _Tp&, _Tp*> __last,
    _Deque_iterator<_Tp, _Tp&, _Tp*> __result)
    { return std::copy_backward(_Deque_iterator<_Tp,
    const _Tp&, const _Tp*>(__first),
    _Deque_iterator<_Tp,
    const _Tp&, const _Tp*>(__last),
    __result); }
  template<typename _Tp>
    _Deque_iterator<_Tp, _Tp&, _Tp*>
    move(_Deque_iterator<_Tp, const _Tp&, const _Tp*>,
  _Deque_iterator<_Tp, const _Tp&, const _Tp*>,
  _Deque_iterator<_Tp, _Tp&, _Tp*>);
  template<typename _Tp>
    inline _Deque_iterator<_Tp, _Tp&, _Tp*>
    move(_Deque_iterator<_Tp, _Tp&, _Tp*> __first,
  _Deque_iterator<_Tp, _Tp&, _Tp*> __last,
  _Deque_iterator<_Tp, _Tp&, _Tp*> __result)
    { return std::move(_Deque_iterator<_Tp, const _Tp&, const _Tp*>(__first),
         _Deque_iterator<_Tp, const _Tp&, const _Tp*>(__last),
         __result); }
  template<typename _Tp>
    _Deque_iterator<_Tp, _Tp&, _Tp*>
    move_backward(_Deque_iterator<_Tp, const _Tp&, const _Tp*>,
    _Deque_iterator<_Tp, const _Tp&, const _Tp*>,
    _Deque_iterator<_Tp, _Tp&, _Tp*>);
  template<typename _Tp>
    inline _Deque_iterator<_Tp, _Tp&, _Tp*>
    move_backward(_Deque_iterator<_Tp, _Tp&, _Tp*> __first,
    _Deque_iterator<_Tp, _Tp&, _Tp*> __last,
    _Deque_iterator<_Tp, _Tp&, _Tp*> __result)
    { return std::move_backward(_Deque_iterator<_Tp,
    const _Tp&, const _Tp*>(__first),
    _Deque_iterator<_Tp,
    const _Tp&, const _Tp*>(__last),
    __result); }
  template<typename _Tp, typename _Alloc>
    class _Deque_base
    {
    public:
      typedef _Alloc allocator_type;
      allocator_type
      get_allocator() const noexcept
      { return allocator_type(_M_get_Tp_allocator()); }
      typedef _Deque_iterator<_Tp, _Tp&, _Tp*> iterator;
      typedef _Deque_iterator<_Tp, const _Tp&, const _Tp*> const_iterator;
      _Deque_base()
      : _M_impl()
      { _M_initialize_map(0); }
      _Deque_base(size_t __num_elements)
      : _M_impl()
      { _M_initialize_map(__num_elements); }
      _Deque_base(const allocator_type& __a, size_t __num_elements)
      : _M_impl(__a)
      { _M_initialize_map(__num_elements); }
      _Deque_base(const allocator_type& __a)
      : _M_impl(__a)
      { }
      _Deque_base(_Deque_base&& __x)
      : _M_impl(std::move(__x._M_get_Tp_allocator()))
      {
 _M_initialize_map(0);
 if (__x._M_impl._M_map)
   {
     std::swap(this->_M_impl._M_start, __x._M_impl._M_start);
     std::swap(this->_M_impl._M_finish, __x._M_impl._M_finish);
     std::swap(this->_M_impl._M_map, __x._M_impl._M_map);
     std::swap(this->_M_impl._M_map_size, __x._M_impl._M_map_size);
   }
      }
      ~_Deque_base() noexcept;
    protected:
      typedef typename _Alloc::template rebind<_Tp*>::other _Map_alloc_type;
      typedef typename _Alloc::template rebind<_Tp>::other _Tp_alloc_type;
      struct _Deque_impl
      : public _Tp_alloc_type
      {
 _Tp** _M_map;
 size_t _M_map_size;
 iterator _M_start;
 iterator _M_finish;
 _Deque_impl()
 : _Tp_alloc_type(), _M_map(0), _M_map_size(0),
   _M_start(), _M_finish()
 { }
 _Deque_impl(const _Tp_alloc_type& __a) noexcept
 : _Tp_alloc_type(__a), _M_map(0), _M_map_size(0),
   _M_start(), _M_finish()
 { }
 _Deque_impl(_Tp_alloc_type&& __a) noexcept
 : _Tp_alloc_type(std::move(__a)), _M_map(0), _M_map_size(0),
   _M_start(), _M_finish()
 { }
      };
      _Tp_alloc_type&
      _M_get_Tp_allocator() noexcept
      { return *static_cast<_Tp_alloc_type*>(&this->_M_impl); }
      const _Tp_alloc_type&
      _M_get_Tp_allocator() const noexcept
      { return *static_cast<const _Tp_alloc_type*>(&this->_M_impl); }
      _Map_alloc_type
      _M_get_map_allocator() const noexcept
      { return _Map_alloc_type(_M_get_Tp_allocator()); }
      _Tp*
      _M_allocate_node()
      {
 return _M_impl._Tp_alloc_type::allocate(__deque_buf_size(sizeof(_Tp)));
      }
      void
      _M_deallocate_node(_Tp* __p) noexcept
      {
 _M_impl._Tp_alloc_type::deallocate(__p, __deque_buf_size(sizeof(_Tp)));
      }
      _Tp**
      _M_allocate_map(size_t __n)
      { return _M_get_map_allocator().allocate(__n); }
      void
      _M_deallocate_map(_Tp** __p, size_t __n) noexcept
      { _M_get_map_allocator().deallocate(__p, __n); }
    protected:
      void _M_initialize_map(size_t);
      void _M_create_nodes(_Tp** __nstart, _Tp** __nfinish);
      void _M_destroy_nodes(_Tp** __nstart, _Tp** __nfinish) noexcept;
      enum { _S_initial_map_size = 8 };
      _Deque_impl _M_impl;
    };
  template<typename _Tp, typename _Alloc>
    _Deque_base<_Tp, _Alloc>::
    ~_Deque_base() noexcept
    {
      if (this->_M_impl._M_map)
 {
   _M_destroy_nodes(this->_M_impl._M_start._M_node,
      this->_M_impl._M_finish._M_node + 1);
   _M_deallocate_map(this->_M_impl._M_map, this->_M_impl._M_map_size);
 }
    }
  template<typename _Tp, typename _Alloc>
    void
    _Deque_base<_Tp, _Alloc>::
    _M_initialize_map(size_t __num_elements)
    {
      const size_t __num_nodes = (__num_elements/ __deque_buf_size(sizeof(_Tp))
      + 1);
      this->_M_impl._M_map_size = std::max((size_t) _S_initial_map_size,
        size_t(__num_nodes + 2));
      this->_M_impl._M_map = _M_allocate_map(this->_M_impl._M_map_size);
      _Tp** __nstart = (this->_M_impl._M_map
   + (this->_M_impl._M_map_size - __num_nodes) / 2);
      _Tp** __nfinish = __nstart + __num_nodes;
      try
 { _M_create_nodes(__nstart, __nfinish); }
      catch(...)
 {
   _M_deallocate_map(this->_M_impl._M_map, this->_M_impl._M_map_size);
   this->_M_impl._M_map = 0;
   this->_M_impl._M_map_size = 0;
   throw;
 }
      this->_M_impl._M_start._M_set_node(__nstart);
      this->_M_impl._M_finish._M_set_node(__nfinish - 1);
      this->_M_impl._M_start._M_cur = _M_impl._M_start._M_first;
      this->_M_impl._M_finish._M_cur = (this->_M_impl._M_finish._M_first
     + __num_elements
     % __deque_buf_size(sizeof(_Tp)));
    }
  template<typename _Tp, typename _Alloc>
    void
    _Deque_base<_Tp, _Alloc>::
    _M_create_nodes(_Tp** __nstart, _Tp** __nfinish)
    {
      _Tp** __cur;
      try
 {
   for (__cur = __nstart; __cur < __nfinish; ++__cur)
     *__cur = this->_M_allocate_node();
 }
      catch(...)
 {
   _M_destroy_nodes(__nstart, __cur);
   throw;
 }
    }
  template<typename _Tp, typename _Alloc>
    void
    _Deque_base<_Tp, _Alloc>::
    _M_destroy_nodes(_Tp** __nstart, _Tp** __nfinish) noexcept
    {
      for (_Tp** __n = __nstart; __n < __nfinish; ++__n)
 _M_deallocate_node(*__n);
    }
  template<typename _Tp, typename _Alloc = std::allocator<_Tp> >
    class deque : protected _Deque_base<_Tp, _Alloc>
    {
      typedef typename _Alloc::value_type _Alloc_value_type;
     
     
      typedef _Deque_base<_Tp, _Alloc> _Base;
      typedef typename _Base::_Tp_alloc_type _Tp_alloc_type;
    public:
      typedef _Tp value_type;
      typedef typename _Tp_alloc_type::pointer pointer;
      typedef typename _Tp_alloc_type::const_pointer const_pointer;
      typedef typename _Tp_alloc_type::reference reference;
      typedef typename _Tp_alloc_type::const_reference const_reference;
      typedef typename _Base::iterator iterator;
      typedef typename _Base::const_iterator const_iterator;
      typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
      typedef std::reverse_iterator<iterator> reverse_iterator;
      typedef size_t size_type;
      typedef ptrdiff_t difference_type;
      typedef _Alloc allocator_type;
    protected:
      typedef pointer* _Map_pointer;
      static size_t _S_buffer_size() noexcept
      { return __deque_buf_size(sizeof(_Tp)); }
      using _Base::_M_initialize_map;
      using _Base::_M_create_nodes;
      using _Base::_M_destroy_nodes;
      using _Base::_M_allocate_node;
      using _Base::_M_deallocate_node;
      using _Base::_M_allocate_map;
      using _Base::_M_deallocate_map;
      using _Base::_M_get_Tp_allocator;
      using _Base::_M_impl;
    public:
      deque() : _Base() { }
      explicit
      deque(const allocator_type& __a)
      : _Base(__a, 0) { }
      explicit
      deque(size_type __n)
      : _Base(__n)
      { _M_default_initialize(); }
      deque(size_type __n, const value_type& __value,
     const allocator_type& __a = allocator_type())
      : _Base(__a, __n)
      { _M_fill_initialize(__value); }
      deque(const deque& __x)
      : _Base(__x._M_get_Tp_allocator(), __x.size())
      { std::__uninitialized_copy_a(__x.begin(), __x.end(),
        this->_M_impl._M_start,
        _M_get_Tp_allocator()); }
      deque(deque&& __x)
      : _Base(std::move(__x)) { }
      deque(initializer_list<value_type> __l,
     const allocator_type& __a = allocator_type())
      : _Base(__a)
      {
 _M_range_initialize(__l.begin(), __l.end(),
       random_access_iterator_tag());
      }
      template<typename _InputIterator,
        typename = std::_RequireInputIter<_InputIterator>>
        deque(_InputIterator __first, _InputIterator __last,
       const allocator_type& __a = allocator_type())
 : _Base(__a)
        { _M_initialize_dispatch(__first, __last, __false_type()); }
      ~deque() noexcept
      { _M_destroy_data(begin(), end(), _M_get_Tp_allocator()); }
      deque&
      operator=(const deque& __x);
      deque&
      operator=(deque&& __x) noexcept
      {
 this->clear();
 this->swap(__x);
 return *this;
      }
      deque&
      operator=(initializer_list<value_type> __l)
      {
 this->assign(__l.begin(), __l.end());
 return *this;
      }
      void
      assign(size_type __n, const value_type& __val)
      { _M_fill_assign(__n, __val); }
      template<typename _InputIterator,
        typename = std::_RequireInputIter<_InputIterator>>
        void
        assign(_InputIterator __first, _InputIterator __last)
        { _M_assign_dispatch(__first, __last, __false_type()); }
      void
      assign(initializer_list<value_type> __l)
      { this->assign(__l.begin(), __l.end()); }
      allocator_type
      get_allocator() const noexcept
      { return _Base::get_allocator(); }
      iterator
      begin() noexcept
      { return this->_M_impl._M_start; }
      const_iterator
      begin() const noexcept
      { return this->_M_impl._M_start; }
      iterator
      end() noexcept
      { return this->_M_impl._M_finish; }
      const_iterator
      end() const noexcept
      { return this->_M_impl._M_finish; }
      reverse_iterator
      rbegin() noexcept
      { return reverse_iterator(this->_M_impl._M_finish); }
      const_reverse_iterator
      rbegin() const noexcept
      { return const_reverse_iterator(this->_M_impl._M_finish); }
      reverse_iterator
      rend() noexcept
      { return reverse_iterator(this->_M_impl._M_start); }
      const_reverse_iterator
      rend() const noexcept
      { return const_reverse_iterator(this->_M_impl._M_start); }
      const_iterator
      cbegin() const noexcept
      { return this->_M_impl._M_start; }
      const_iterator
      cend() const noexcept
      { return this->_M_impl._M_finish; }
      const_reverse_iterator
      crbegin() const noexcept
      { return const_reverse_iterator(this->_M_impl._M_finish); }
      const_reverse_iterator
      crend() const noexcept
      { return const_reverse_iterator(this->_M_impl._M_start); }
      size_type
      size() const noexcept
      { return this->_M_impl._M_finish - this->_M_impl._M_start; }
      size_type
      max_size() const noexcept
      { return _M_get_Tp_allocator().max_size(); }
      void
      resize(size_type __new_size)
      {
 const size_type __len = size();
 if (__new_size > __len)
   _M_default_append(__new_size - __len);
 else if (__new_size < __len)
   _M_erase_at_end(this->_M_impl._M_start
     + difference_type(__new_size));
      }
      void
      resize(size_type __new_size, const value_type& __x)
      {
 const size_type __len = size();
 if (__new_size > __len)
   insert(this->_M_impl._M_finish, __new_size - __len, __x);
 else if (__new_size < __len)
   _M_erase_at_end(this->_M_impl._M_start
     + difference_type(__new_size));
      }
      void
      shrink_to_fit() noexcept
      { _M_shrink_to_fit(); }
      bool
      empty() const noexcept
      { return this->_M_impl._M_finish == this->_M_impl._M_start; }
      reference
      operator[](size_type __n) noexcept
      { return this->_M_impl._M_start[difference_type(__n)]; }
      const_reference
      operator[](size_type __n) const noexcept
      { return this->_M_impl._M_start[difference_type(__n)]; }
    protected:
      void
      _M_range_check(size_type __n) const
      {
 if (__n >= this->size())
   __throw_out_of_range_fmt(("deque::_M_range_check: __n " "(which is %zu)>= this->size() " "(which is %zu)"),
       __n, this->size());
      }
    public:
      reference
      at(size_type __n)
      {
 _M_range_check(__n);
 return (*this)[__n];
      }
      const_reference
      at(size_type __n) const
      {
 _M_range_check(__n);
 return (*this)[__n];
      }
      reference
      front() noexcept
      { return *begin(); }
      const_reference
      front() const noexcept
      { return *begin(); }
      reference
      back() noexcept
      {
 iterator __tmp = end();
 --__tmp;
 return *__tmp;
      }
      const_reference
      back() const noexcept
      {
 const_iterator __tmp = end();
 --__tmp;
 return *__tmp;
      }
      void
      push_front(const value_type& __x)
      {
 if (this->_M_impl._M_start._M_cur != this->_M_impl._M_start._M_first)
   {
     this->_M_impl.construct(this->_M_impl._M_start._M_cur - 1, __x);
     --this->_M_impl._M_start._M_cur;
   }
 else
   _M_push_front_aux(__x);
      }
      void
      push_front(value_type&& __x)
      { emplace_front(std::move(__x)); }
      template<typename... _Args>
        void
        emplace_front(_Args&&... __args);
      void
      push_back(const value_type& __x)
      {
 if (this->_M_impl._M_finish._M_cur
     != this->_M_impl._M_finish._M_last - 1)
   {
     this->_M_impl.construct(this->_M_impl._M_finish._M_cur, __x);
     ++this->_M_impl._M_finish._M_cur;
   }
 else
   _M_push_back_aux(__x);
      }
      void
      push_back(value_type&& __x)
      { emplace_back(std::move(__x)); }
      template<typename... _Args>
        void
        emplace_back(_Args&&... __args);
      void
      pop_front() noexcept
      {
 if (this->_M_impl._M_start._M_cur
     != this->_M_impl._M_start._M_last - 1)
   {
     this->_M_impl.destroy(this->_M_impl._M_start._M_cur);
     ++this->_M_impl._M_start._M_cur;
   }
 else
   _M_pop_front_aux();
      }
      void
      pop_back() noexcept
      {
 if (this->_M_impl._M_finish._M_cur
     != this->_M_impl._M_finish._M_first)
   {
     --this->_M_impl._M_finish._M_cur;
     this->_M_impl.destroy(this->_M_impl._M_finish._M_cur);
   }
 else
   _M_pop_back_aux();
      }
      template<typename... _Args>
        iterator
        emplace(const_iterator __position, _Args&&... __args);
      iterator
      insert(const_iterator __position, const value_type& __x);
      iterator
      insert(const_iterator __position, value_type&& __x)
      { return emplace(__position, std::move(__x)); }
      iterator
      insert(const_iterator __p, initializer_list<value_type> __l)
      { return this->insert(__p, __l.begin(), __l.end()); }
      iterator
      insert(const_iterator __position, size_type __n, const value_type& __x)
      {
 difference_type __offset = __position - cbegin();
 _M_fill_insert(__position._M_const_cast(), __n, __x);
 return begin() + __offset;
      }
      template<typename _InputIterator,
        typename = std::_RequireInputIter<_InputIterator>>
        iterator
        insert(const_iterator __position, _InputIterator __first,
        _InputIterator __last)
        {
   difference_type __offset = __position - cbegin();
   _M_insert_dispatch(__position._M_const_cast(),
        __first, __last, __false_type());
   return begin() + __offset;
 }
      iterator
      erase(const_iterator __position)
      { return _M_erase(__position._M_const_cast()); }
      iterator
      erase(const_iterator __first, const_iterator __last)
      { return _M_erase(__first._M_const_cast(), __last._M_const_cast()); }
      void
      swap(deque& __x) noexcept
      {
 std::swap(this->_M_impl._M_start, __x._M_impl._M_start);
 std::swap(this->_M_impl._M_finish, __x._M_impl._M_finish);
 std::swap(this->_M_impl._M_map, __x._M_impl._M_map);
 std::swap(this->_M_impl._M_map_size, __x._M_impl._M_map_size);
 std::__alloc_swap<_Tp_alloc_type>::_S_do_it(_M_get_Tp_allocator(),
          __x._M_get_Tp_allocator());
      }
      void
      clear() noexcept
      { _M_erase_at_end(begin()); }
    protected:
      template<typename _Integer>
        void
        _M_initialize_dispatch(_Integer __n, _Integer __x, __true_type)
        {
   _M_initialize_map(static_cast<size_type>(__n));
   _M_fill_initialize(__x);
 }
      template<typename _InputIterator>
        void
        _M_initialize_dispatch(_InputIterator __first, _InputIterator __last,
          __false_type)
        {
   typedef typename std::iterator_traits<_InputIterator>::
     iterator_category _IterCategory;
   _M_range_initialize(__first, __last, _IterCategory());
 }
      template<typename _InputIterator>
        void
        _M_range_initialize(_InputIterator __first, _InputIterator __last,
       std::input_iterator_tag);
      template<typename _ForwardIterator>
        void
        _M_range_initialize(_ForwardIterator __first, _ForwardIterator __last,
       std::forward_iterator_tag);
      void
      _M_fill_initialize(const value_type& __value);
      void
      _M_default_initialize();
      template<typename _Integer>
        void
        _M_assign_dispatch(_Integer __n, _Integer __val, __true_type)
        { _M_fill_assign(__n, __val); }
      template<typename _InputIterator>
        void
        _M_assign_dispatch(_InputIterator __first, _InputIterator __last,
      __false_type)
        {
   typedef typename std::iterator_traits<_InputIterator>::
     iterator_category _IterCategory;
   _M_assign_aux(__first, __last, _IterCategory());
 }
      template<typename _InputIterator>
        void
        _M_assign_aux(_InputIterator __first, _InputIterator __last,
        std::input_iterator_tag);
      template<typename _ForwardIterator>
        void
        _M_assign_aux(_ForwardIterator __first, _ForwardIterator __last,
        std::forward_iterator_tag)
        {
   const size_type __len = std::distance(__first, __last);
   if (__len > size())
     {
       _ForwardIterator __mid = __first;
       std::advance(__mid, size());
       std::copy(__first, __mid, begin());
       insert(end(), __mid, __last);
     }
   else
     _M_erase_at_end(std::copy(__first, __last, begin()));
 }
      void
      _M_fill_assign(size_type __n, const value_type& __val)
      {
 if (__n > size())
   {
     std::fill(begin(), end(), __val);
     insert(end(), __n - size(), __val);
   }
 else
   {
     _M_erase_at_end(begin() + difference_type(__n));
     std::fill(begin(), end(), __val);
   }
      }
      template<typename... _Args>
        void _M_push_back_aux(_Args&&... __args);
      template<typename... _Args>
        void _M_push_front_aux(_Args&&... __args);
      void _M_pop_back_aux();
      void _M_pop_front_aux();
      template<typename _Integer>
        void
        _M_insert_dispatch(iterator __pos,
      _Integer __n, _Integer __x, __true_type)
        { _M_fill_insert(__pos, __n, __x); }
      template<typename _InputIterator>
        void
        _M_insert_dispatch(iterator __pos,
      _InputIterator __first, _InputIterator __last,
      __false_type)
        {
   typedef typename std::iterator_traits<_InputIterator>::
     iterator_category _IterCategory;
          _M_range_insert_aux(__pos, __first, __last, _IterCategory());
 }
      template<typename _InputIterator>
        void
        _M_range_insert_aux(iterator __pos, _InputIterator __first,
       _InputIterator __last, std::input_iterator_tag);
      template<typename _ForwardIterator>
        void
        _M_range_insert_aux(iterator __pos, _ForwardIterator __first,
       _ForwardIterator __last, std::forward_iterator_tag);
      void
      _M_fill_insert(iterator __pos, size_type __n, const value_type& __x);
      template<typename... _Args>
        iterator
        _M_insert_aux(iterator __pos, _Args&&... __args);
      void
      _M_insert_aux(iterator __pos, size_type __n, const value_type& __x);
      template<typename _ForwardIterator>
        void
        _M_insert_aux(iterator __pos,
        _ForwardIterator __first, _ForwardIterator __last,
        size_type __n);
      void
      _M_destroy_data_aux(iterator __first, iterator __last);
      template<typename _Alloc1>
        void
        _M_destroy_data(iterator __first, iterator __last, const _Alloc1&)
        { _M_destroy_data_aux(__first, __last); }
      void
      _M_destroy_data(iterator __first, iterator __last,
        const std::allocator<_Tp>&)
      {
 if (!__has_trivial_destructor(value_type))
   _M_destroy_data_aux(__first, __last);
      }
      void
      _M_erase_at_begin(iterator __pos)
      {
 _M_destroy_data(begin(), __pos, _M_get_Tp_allocator());
 _M_destroy_nodes(this->_M_impl._M_start._M_node, __pos._M_node);
 this->_M_impl._M_start = __pos;
      }
      void
      _M_erase_at_end(iterator __pos)
      {
 _M_destroy_data(__pos, end(), _M_get_Tp_allocator());
 _M_destroy_nodes(__pos._M_node + 1,
    this->_M_impl._M_finish._M_node + 1);
 this->_M_impl._M_finish = __pos;
      }
      iterator
      _M_erase(iterator __pos);
      iterator
      _M_erase(iterator __first, iterator __last);
      void
      _M_default_append(size_type __n);
      bool
      _M_shrink_to_fit();
      iterator
      _M_reserve_elements_at_front(size_type __n)
      {
 const size_type __vacancies = this->_M_impl._M_start._M_cur
                               - this->_M_impl._M_start._M_first;
 if (__n > __vacancies)
   _M_new_elements_at_front(__n - __vacancies);
 return this->_M_impl._M_start - difference_type(__n);
      }
      iterator
      _M_reserve_elements_at_back(size_type __n)
      {
 const size_type __vacancies = (this->_M_impl._M_finish._M_last
           - this->_M_impl._M_finish._M_cur) - 1;
 if (__n > __vacancies)
   _M_new_elements_at_back(__n - __vacancies);
 return this->_M_impl._M_finish + difference_type(__n);
      }
      void
      _M_new_elements_at_front(size_type __new_elements);
      void
      _M_new_elements_at_back(size_type __new_elements);
      void
      _M_reserve_map_at_back(size_type __nodes_to_add = 1)
      {
 if (__nodes_to_add + 1 > this->_M_impl._M_map_size
     - (this->_M_impl._M_finish._M_node - this->_M_impl._M_map))
   _M_reallocate_map(__nodes_to_add, false);
      }
      void
      _M_reserve_map_at_front(size_type __nodes_to_add = 1)
      {
 if (__nodes_to_add > size_type(this->_M_impl._M_start._M_node
           - this->_M_impl._M_map))
   _M_reallocate_map(__nodes_to_add, true);
      }
      void
      _M_reallocate_map(size_type __nodes_to_add, bool __add_at_front);
    };
  template<typename _Tp, typename _Alloc>
    inline bool
    operator==(const deque<_Tp, _Alloc>& __x,
                         const deque<_Tp, _Alloc>& __y)
    { return __x.size() == __y.size()
             && std::equal(__x.begin(), __x.end(), __y.begin()); }
  template<typename _Tp, typename _Alloc>
    inline bool
    operator<(const deque<_Tp, _Alloc>& __x,
       const deque<_Tp, _Alloc>& __y)
    { return std::lexicographical_compare(__x.begin(), __x.end(),
       __y.begin(), __y.end()); }
  template<typename _Tp, typename _Alloc>
    inline bool
    operator!=(const deque<_Tp, _Alloc>& __x,
        const deque<_Tp, _Alloc>& __y)
    { return !(__x == __y); }
  template<typename _Tp, typename _Alloc>
    inline bool
    operator>(const deque<_Tp, _Alloc>& __x,
       const deque<_Tp, _Alloc>& __y)
    { return __y < __x; }
  template<typename _Tp, typename _Alloc>
    inline bool
    operator<=(const deque<_Tp, _Alloc>& __x,
        const deque<_Tp, _Alloc>& __y)
    { return !(__y < __x); }
  template<typename _Tp, typename _Alloc>
    inline bool
    operator>=(const deque<_Tp, _Alloc>& __x,
        const deque<_Tp, _Alloc>& __y)
    { return !(__x < __y); }
  template<typename _Tp, typename _Alloc>
    inline void
    swap(deque<_Tp,_Alloc>& __x, deque<_Tp,_Alloc>& __y)
    { __x.swap(__y); }

}
namespace std __attribute__ ((__visibility__ ("default")))
{

  template <typename _Tp, typename _Alloc>
    void
    deque<_Tp, _Alloc>::
    _M_default_initialize()
    {
      _Map_pointer __cur;
      try
        {
          for (__cur = this->_M_impl._M_start._M_node;
        __cur < this->_M_impl._M_finish._M_node;
        ++__cur)
            std::__uninitialized_default_a(*__cur, *__cur + _S_buffer_size(),
        _M_get_Tp_allocator());
          std::__uninitialized_default_a(this->_M_impl._M_finish._M_first,
      this->_M_impl._M_finish._M_cur,
      _M_get_Tp_allocator());
        }
      catch(...)
        {
          std::_Destroy(this->_M_impl._M_start, iterator(*__cur, __cur),
   _M_get_Tp_allocator());
          throw;
        }
    }
  template <typename _Tp, typename _Alloc>
    deque<_Tp, _Alloc>&
    deque<_Tp, _Alloc>::
    operator=(const deque& __x)
    {
      const size_type __len = size();
      if (&__x != this)
 {
   if (__len >= __x.size())
     _M_erase_at_end(std::copy(__x.begin(), __x.end(),
          this->_M_impl._M_start));
   else
     {
       const_iterator __mid = __x.begin() + difference_type(__len);
       std::copy(__x.begin(), __mid, this->_M_impl._M_start);
       insert(this->_M_impl._M_finish, __mid, __x.end());
     }
 }
      return *this;
    }
  template<typename _Tp, typename _Alloc>
    template<typename... _Args>
      void
      deque<_Tp, _Alloc>::
      emplace_front(_Args&&... __args)
      {
 if (this->_M_impl._M_start._M_cur != this->_M_impl._M_start._M_first)
   {
     this->_M_impl.construct(this->_M_impl._M_start._M_cur - 1,
        std::forward<_Args>(__args)...);
     --this->_M_impl._M_start._M_cur;
   }
 else
   _M_push_front_aux(std::forward<_Args>(__args)...);
      }
  template<typename _Tp, typename _Alloc>
    template<typename... _Args>
      void
      deque<_Tp, _Alloc>::
      emplace_back(_Args&&... __args)
      {
 if (this->_M_impl._M_finish._M_cur
     != this->_M_impl._M_finish._M_last - 1)
   {
     this->_M_impl.construct(this->_M_impl._M_finish._M_cur,
        std::forward<_Args>(__args)...);
     ++this->_M_impl._M_finish._M_cur;
   }
 else
   _M_push_back_aux(std::forward<_Args>(__args)...);
      }
  template<typename _Tp, typename _Alloc>
    template<typename... _Args>
      typename deque<_Tp, _Alloc>::iterator
      deque<_Tp, _Alloc>::
      emplace(const_iterator __position, _Args&&... __args)
      {
 if (__position._M_cur == this->_M_impl._M_start._M_cur)
   {
     emplace_front(std::forward<_Args>(__args)...);
     return this->_M_impl._M_start;
   }
 else if (__position._M_cur == this->_M_impl._M_finish._M_cur)
   {
     emplace_back(std::forward<_Args>(__args)...);
     iterator __tmp = this->_M_impl._M_finish;
     --__tmp;
     return __tmp;
   }
 else
   return _M_insert_aux(__position._M_const_cast(),
          std::forward<_Args>(__args)...);
      }
  template <typename _Tp, typename _Alloc>
    typename deque<_Tp, _Alloc>::iterator
    deque<_Tp, _Alloc>::
    insert(const_iterator __position, const value_type& __x)
    {
      if (__position._M_cur == this->_M_impl._M_start._M_cur)
 {
   push_front(__x);
   return this->_M_impl._M_start;
 }
      else if (__position._M_cur == this->_M_impl._M_finish._M_cur)
 {
   push_back(__x);
   iterator __tmp = this->_M_impl._M_finish;
   --__tmp;
   return __tmp;
 }
      else
 return _M_insert_aux(__position._M_const_cast(), __x);
   }
  template <typename _Tp, typename _Alloc>
    typename deque<_Tp, _Alloc>::iterator
    deque<_Tp, _Alloc>::
    _M_erase(iterator __position)
    {
      iterator __next = __position;
      ++__next;
      const difference_type __index = __position - begin();
      if (static_cast<size_type>(__index) < (size() >> 1))
 {
   if (__position != begin())
     std::move_backward(begin(), __position, __next);
   pop_front();
 }
      else
 {
   if (__next != end())
     std::move(__next, end(), __position);
   pop_back();
 }
      return begin() + __index;
    }
  template <typename _Tp, typename _Alloc>
    typename deque<_Tp, _Alloc>::iterator
    deque<_Tp, _Alloc>::
    _M_erase(iterator __first, iterator __last)
    {
      if (__first == __last)
 return __first;
      else if (__first == begin() && __last == end())
 {
   clear();
   return end();
 }
      else
 {
   const difference_type __n = __last - __first;
   const difference_type __elems_before = __first - begin();
   if (static_cast<size_type>(__elems_before) <= (size() - __n) / 2)
     {
       if (__first != begin())
  std::move_backward(begin(), __first, __last);
       _M_erase_at_begin(begin() + __n);
     }
   else
     {
       if (__last != end())
  std::move(__last, end(), __first);
       _M_erase_at_end(end() - __n);
     }
   return begin() + __elems_before;
 }
    }
  template <typename _Tp, class _Alloc>
    template <typename _InputIterator>
      void
      deque<_Tp, _Alloc>::
      _M_assign_aux(_InputIterator __first, _InputIterator __last,
      std::input_iterator_tag)
      {
        iterator __cur = begin();
        for (; __first != __last && __cur != end(); ++__cur, ++__first)
          *__cur = *__first;
        if (__first == __last)
          _M_erase_at_end(__cur);
        else
          insert(end(), __first, __last);
      }
  template <typename _Tp, typename _Alloc>
    void
    deque<_Tp, _Alloc>::
    _M_fill_insert(iterator __pos, size_type __n, const value_type& __x)
    {
      if (__pos._M_cur == this->_M_impl._M_start._M_cur)
 {
   iterator __new_start = _M_reserve_elements_at_front(__n);
   try
     {
       std::__uninitialized_fill_a(__new_start, this->_M_impl._M_start,
       __x, _M_get_Tp_allocator());
       this->_M_impl._M_start = __new_start;
     }
   catch(...)
     {
       _M_destroy_nodes(__new_start._M_node,
          this->_M_impl._M_start._M_node);
       throw;
     }
 }
      else if (__pos._M_cur == this->_M_impl._M_finish._M_cur)
 {
   iterator __new_finish = _M_reserve_elements_at_back(__n);
   try
     {
       std::__uninitialized_fill_a(this->_M_impl._M_finish,
       __new_finish, __x,
       _M_get_Tp_allocator());
       this->_M_impl._M_finish = __new_finish;
     }
   catch(...)
     {
       _M_destroy_nodes(this->_M_impl._M_finish._M_node + 1,
          __new_finish._M_node + 1);
       throw;
     }
 }
      else
        _M_insert_aux(__pos, __n, __x);
    }
  template <typename _Tp, typename _Alloc>
    void
    deque<_Tp, _Alloc>::
    _M_default_append(size_type __n)
    {
      if (__n)
 {
   iterator __new_finish = _M_reserve_elements_at_back(__n);
   try
     {
       std::__uninitialized_default_a(this->_M_impl._M_finish,
          __new_finish,
          _M_get_Tp_allocator());
       this->_M_impl._M_finish = __new_finish;
     }
   catch(...)
     {
       _M_destroy_nodes(this->_M_impl._M_finish._M_node + 1,
          __new_finish._M_node + 1);
       throw;
     }
 }
    }
  template <typename _Tp, typename _Alloc>
    bool
    deque<_Tp, _Alloc>::
    _M_shrink_to_fit()
    {
      const difference_type __front_capacity
 = (this->_M_impl._M_start._M_cur - this->_M_impl._M_start._M_first);
      if (__front_capacity == 0)
 return false;
      const difference_type __back_capacity
 = (this->_M_impl._M_finish._M_last - this->_M_impl._M_finish._M_cur);
      if (__front_capacity + __back_capacity < _S_buffer_size())
 return false;
      return std::__shrink_to_fit_aux<deque>::_S_do_it(*this);
    }
  template <typename _Tp, typename _Alloc>
    void
    deque<_Tp, _Alloc>::
    _M_fill_initialize(const value_type& __value)
    {
      _Map_pointer __cur;
      try
        {
          for (__cur = this->_M_impl._M_start._M_node;
        __cur < this->_M_impl._M_finish._M_node;
        ++__cur)
            std::__uninitialized_fill_a(*__cur, *__cur + _S_buffer_size(),
     __value, _M_get_Tp_allocator());
          std::__uninitialized_fill_a(this->_M_impl._M_finish._M_first,
          this->_M_impl._M_finish._M_cur,
          __value, _M_get_Tp_allocator());
        }
      catch(...)
        {
          std::_Destroy(this->_M_impl._M_start, iterator(*__cur, __cur),
   _M_get_Tp_allocator());
          throw;
        }
    }
  template <typename _Tp, typename _Alloc>
    template <typename _InputIterator>
      void
      deque<_Tp, _Alloc>::
      _M_range_initialize(_InputIterator __first, _InputIterator __last,
                          std::input_iterator_tag)
      {
        this->_M_initialize_map(0);
        try
          {
            for (; __first != __last; ++__first)
       emplace_back(*__first);
          }
        catch(...)
          {
            clear();
            throw;
          }
      }
  template <typename _Tp, typename _Alloc>
    template <typename _ForwardIterator>
      void
      deque<_Tp, _Alloc>::
      _M_range_initialize(_ForwardIterator __first, _ForwardIterator __last,
                          std::forward_iterator_tag)
      {
        const size_type __n = std::distance(__first, __last);
        this->_M_initialize_map(__n);
        _Map_pointer __cur_node;
        try
          {
            for (__cur_node = this->_M_impl._M_start._M_node;
                 __cur_node < this->_M_impl._M_finish._M_node;
                 ++__cur_node)
       {
  _ForwardIterator __mid = __first;
  std::advance(__mid, _S_buffer_size());
  std::__uninitialized_copy_a(__first, __mid, *__cur_node,
         _M_get_Tp_allocator());
  __first = __mid;
       }
            std::__uninitialized_copy_a(__first, __last,
     this->_M_impl._M_finish._M_first,
     _M_get_Tp_allocator());
          }
        catch(...)
          {
            std::_Destroy(this->_M_impl._M_start,
     iterator(*__cur_node, __cur_node),
     _M_get_Tp_allocator());
            throw;
          }
      }
  template<typename _Tp, typename _Alloc>
    template<typename... _Args>
      void
      deque<_Tp, _Alloc>::
      _M_push_back_aux(_Args&&... __args)
      {
 _M_reserve_map_at_back();
 *(this->_M_impl._M_finish._M_node + 1) = this->_M_allocate_node();
 try
   {
     this->_M_impl.construct(this->_M_impl._M_finish._M_cur,
        std::forward<_Args>(__args)...);
     this->_M_impl._M_finish._M_set_node(this->_M_impl._M_finish._M_node
      + 1);
     this->_M_impl._M_finish._M_cur = this->_M_impl._M_finish._M_first;
   }
 catch(...)
   {
     _M_deallocate_node(*(this->_M_impl._M_finish._M_node + 1));
     throw;
   }
      }
  template<typename _Tp, typename _Alloc>
    template<typename... _Args>
      void
      deque<_Tp, _Alloc>::
      _M_push_front_aux(_Args&&... __args)
      {
 _M_reserve_map_at_front();
 *(this->_M_impl._M_start._M_node - 1) = this->_M_allocate_node();
 try
   {
     this->_M_impl._M_start._M_set_node(this->_M_impl._M_start._M_node
            - 1);
     this->_M_impl._M_start._M_cur = this->_M_impl._M_start._M_last - 1;
     this->_M_impl.construct(this->_M_impl._M_start._M_cur,
        std::forward<_Args>(__args)...);
   }
 catch(...)
   {
     ++this->_M_impl._M_start;
     _M_deallocate_node(*(this->_M_impl._M_start._M_node - 1));
     throw;
   }
      }
  template <typename _Tp, typename _Alloc>
    void deque<_Tp, _Alloc>::
    _M_pop_back_aux()
    {
      _M_deallocate_node(this->_M_impl._M_finish._M_first);
      this->_M_impl._M_finish._M_set_node(this->_M_impl._M_finish._M_node - 1);
      this->_M_impl._M_finish._M_cur = this->_M_impl._M_finish._M_last - 1;
      this->_M_impl.destroy(this->_M_impl._M_finish._M_cur);
    }
  template <typename _Tp, typename _Alloc>
    void deque<_Tp, _Alloc>::
    _M_pop_front_aux()
    {
      this->_M_impl.destroy(this->_M_impl._M_start._M_cur);
      _M_deallocate_node(this->_M_impl._M_start._M_first);
      this->_M_impl._M_start._M_set_node(this->_M_impl._M_start._M_node + 1);
      this->_M_impl._M_start._M_cur = this->_M_impl._M_start._M_first;
    }
  template <typename _Tp, typename _Alloc>
    template <typename _InputIterator>
      void
      deque<_Tp, _Alloc>::
      _M_range_insert_aux(iterator __pos,
                          _InputIterator __first, _InputIterator __last,
                          std::input_iterator_tag)
      { std::copy(__first, __last, std::inserter(*this, __pos)); }
  template <typename _Tp, typename _Alloc>
    template <typename _ForwardIterator>
      void
      deque<_Tp, _Alloc>::
      _M_range_insert_aux(iterator __pos,
                          _ForwardIterator __first, _ForwardIterator __last,
                          std::forward_iterator_tag)
      {
        const size_type __n = std::distance(__first, __last);
        if (__pos._M_cur == this->_M_impl._M_start._M_cur)
   {
     iterator __new_start = _M_reserve_elements_at_front(__n);
     try
       {
  std::__uninitialized_copy_a(__first, __last, __new_start,
         _M_get_Tp_allocator());
  this->_M_impl._M_start = __new_start;
       }
     catch(...)
       {
  _M_destroy_nodes(__new_start._M_node,
     this->_M_impl._M_start._M_node);
  throw;
       }
   }
        else if (__pos._M_cur == this->_M_impl._M_finish._M_cur)
   {
     iterator __new_finish = _M_reserve_elements_at_back(__n);
     try
       {
  std::__uninitialized_copy_a(__first, __last,
         this->_M_impl._M_finish,
         _M_get_Tp_allocator());
  this->_M_impl._M_finish = __new_finish;
       }
     catch(...)
       {
  _M_destroy_nodes(this->_M_impl._M_finish._M_node + 1,
     __new_finish._M_node + 1);
  throw;
       }
   }
        else
          _M_insert_aux(__pos, __first, __last, __n);
      }
  template<typename _Tp, typename _Alloc>
    template<typename... _Args>
      typename deque<_Tp, _Alloc>::iterator
      deque<_Tp, _Alloc>::
      _M_insert_aux(iterator __pos, _Args&&... __args)
      {
 value_type __x_copy(std::forward<_Args>(__args)...);
 difference_type __index = __pos - this->_M_impl._M_start;
 if (static_cast<size_type>(__index) < size() / 2)
   {
     push_front(std::move(front()));
     iterator __front1 = this->_M_impl._M_start;
     ++__front1;
     iterator __front2 = __front1;
     ++__front2;
     __pos = this->_M_impl._M_start + __index;
     iterator __pos1 = __pos;
     ++__pos1;
     std::move(__front2, __pos1, __front1);
   }
 else
   {
     push_back(std::move(back()));
     iterator __back1 = this->_M_impl._M_finish;
     --__back1;
     iterator __back2 = __back1;
     --__back2;
     __pos = this->_M_impl._M_start + __index;
     std::move_backward(__pos, __back2, __back1);
   }
 *__pos = std::move(__x_copy);
 return __pos;
      }
  template <typename _Tp, typename _Alloc>
    void
    deque<_Tp, _Alloc>::
    _M_insert_aux(iterator __pos, size_type __n, const value_type& __x)
    {
      const difference_type __elems_before = __pos - this->_M_impl._M_start;
      const size_type __length = this->size();
      value_type __x_copy = __x;
      if (__elems_before < difference_type(__length / 2))
 {
   iterator __new_start = _M_reserve_elements_at_front(__n);
   iterator __old_start = this->_M_impl._M_start;
   __pos = this->_M_impl._M_start + __elems_before;
   try
     {
       if (__elems_before >= difference_type(__n))
  {
    iterator __start_n = (this->_M_impl._M_start
     + difference_type(__n));
    std::__uninitialized_move_a(this->_M_impl._M_start,
           __start_n, __new_start,
           _M_get_Tp_allocator());
    this->_M_impl._M_start = __new_start;
    std::move(__start_n, __pos, __old_start);
    std::fill(__pos - difference_type(__n), __pos, __x_copy);
  }
       else
  {
    std::__uninitialized_move_fill(this->_M_impl._M_start,
       __pos, __new_start,
       this->_M_impl._M_start,
       __x_copy,
       _M_get_Tp_allocator());
    this->_M_impl._M_start = __new_start;
    std::fill(__old_start, __pos, __x_copy);
  }
     }
   catch(...)
     {
       _M_destroy_nodes(__new_start._M_node,
          this->_M_impl._M_start._M_node);
       throw;
     }
 }
      else
 {
   iterator __new_finish = _M_reserve_elements_at_back(__n);
   iterator __old_finish = this->_M_impl._M_finish;
   const difference_type __elems_after =
     difference_type(__length) - __elems_before;
   __pos = this->_M_impl._M_finish - __elems_after;
   try
     {
       if (__elems_after > difference_type(__n))
  {
    iterator __finish_n = (this->_M_impl._M_finish
      - difference_type(__n));
    std::__uninitialized_move_a(__finish_n,
           this->_M_impl._M_finish,
           this->_M_impl._M_finish,
           _M_get_Tp_allocator());
    this->_M_impl._M_finish = __new_finish;
    std::move_backward(__pos, __finish_n, __old_finish);
    std::fill(__pos, __pos + difference_type(__n), __x_copy);
  }
       else
  {
    std::__uninitialized_fill_move(this->_M_impl._M_finish,
       __pos + difference_type(__n),
       __x_copy, __pos,
       this->_M_impl._M_finish,
       _M_get_Tp_allocator());
    this->_M_impl._M_finish = __new_finish;
    std::fill(__pos, __old_finish, __x_copy);
  }
     }
   catch(...)
     {
       _M_destroy_nodes(this->_M_impl._M_finish._M_node + 1,
          __new_finish._M_node + 1);
       throw;
     }
 }
    }
  template <typename _Tp, typename _Alloc>
    template <typename _ForwardIterator>
      void
      deque<_Tp, _Alloc>::
      _M_insert_aux(iterator __pos,
                    _ForwardIterator __first, _ForwardIterator __last,
                    size_type __n)
      {
        const difference_type __elemsbefore = __pos - this->_M_impl._M_start;
        const size_type __length = size();
        if (static_cast<size_type>(__elemsbefore) < __length / 2)
   {
     iterator __new_start = _M_reserve_elements_at_front(__n);
     iterator __old_start = this->_M_impl._M_start;
     __pos = this->_M_impl._M_start + __elemsbefore;
     try
       {
  if (__elemsbefore >= difference_type(__n))
    {
      iterator __start_n = (this->_M_impl._M_start
       + difference_type(__n));
      std::__uninitialized_move_a(this->_M_impl._M_start,
      __start_n, __new_start,
      _M_get_Tp_allocator());
      this->_M_impl._M_start = __new_start;
      std::move(__start_n, __pos, __old_start);
      std::copy(__first, __last, __pos - difference_type(__n));
    }
  else
    {
      _ForwardIterator __mid = __first;
      std::advance(__mid, difference_type(__n) - __elemsbefore);
      std::__uninitialized_move_copy(this->_M_impl._M_start,
         __pos, __first, __mid,
         __new_start,
         _M_get_Tp_allocator());
      this->_M_impl._M_start = __new_start;
      std::copy(__mid, __last, __old_start);
    }
       }
     catch(...)
       {
  _M_destroy_nodes(__new_start._M_node,
     this->_M_impl._M_start._M_node);
  throw;
       }
   }
        else
        {
          iterator __new_finish = _M_reserve_elements_at_back(__n);
          iterator __old_finish = this->_M_impl._M_finish;
          const difference_type __elemsafter =
            difference_type(__length) - __elemsbefore;
          __pos = this->_M_impl._M_finish - __elemsafter;
          try
            {
              if (__elemsafter > difference_type(__n))
  {
    iterator __finish_n = (this->_M_impl._M_finish
      - difference_type(__n));
    std::__uninitialized_move_a(__finish_n,
           this->_M_impl._M_finish,
           this->_M_impl._M_finish,
           _M_get_Tp_allocator());
    this->_M_impl._M_finish = __new_finish;
    std::move_backward(__pos, __finish_n, __old_finish);
    std::copy(__first, __last, __pos);
  }
              else
  {
    _ForwardIterator __mid = __first;
    std::advance(__mid, __elemsafter);
    std::__uninitialized_copy_move(__mid, __last, __pos,
       this->_M_impl._M_finish,
       this->_M_impl._M_finish,
       _M_get_Tp_allocator());
    this->_M_impl._M_finish = __new_finish;
    std::copy(__first, __mid, __pos);
  }
            }
          catch(...)
            {
              _M_destroy_nodes(this->_M_impl._M_finish._M_node + 1,
          __new_finish._M_node + 1);
              throw;
            }
        }
      }
   template<typename _Tp, typename _Alloc>
     void
     deque<_Tp, _Alloc>::
     _M_destroy_data_aux(iterator __first, iterator __last)
     {
       for (_Map_pointer __node = __first._M_node + 1;
     __node < __last._M_node; ++__node)
  std::_Destroy(*__node, *__node + _S_buffer_size(),
         _M_get_Tp_allocator());
       if (__first._M_node != __last._M_node)
  {
    std::_Destroy(__first._M_cur, __first._M_last,
    _M_get_Tp_allocator());
    std::_Destroy(__last._M_first, __last._M_cur,
    _M_get_Tp_allocator());
  }
       else
  std::_Destroy(__first._M_cur, __last._M_cur,
         _M_get_Tp_allocator());
     }
  template <typename _Tp, typename _Alloc>
    void
    deque<_Tp, _Alloc>::
    _M_new_elements_at_front(size_type __new_elems)
    {
      if (this->max_size() - this->size() < __new_elems)
 __throw_length_error(("deque::_M_new_elements_at_front"));
      const size_type __new_nodes = ((__new_elems + _S_buffer_size() - 1)
         / _S_buffer_size());
      _M_reserve_map_at_front(__new_nodes);
      size_type __i;
      try
        {
          for (__i = 1; __i <= __new_nodes; ++__i)
            *(this->_M_impl._M_start._M_node - __i) = this->_M_allocate_node();
        }
      catch(...)
        {
          for (size_type __j = 1; __j < __i; ++__j)
            _M_deallocate_node(*(this->_M_impl._M_start._M_node - __j));
          throw;
        }
    }
  template <typename _Tp, typename _Alloc>
    void
    deque<_Tp, _Alloc>::
    _M_new_elements_at_back(size_type __new_elems)
    {
      if (this->max_size() - this->size() < __new_elems)
 __throw_length_error(("deque::_M_new_elements_at_back"));
      const size_type __new_nodes = ((__new_elems + _S_buffer_size() - 1)
         / _S_buffer_size());
      _M_reserve_map_at_back(__new_nodes);
      size_type __i;
      try
        {
          for (__i = 1; __i <= __new_nodes; ++__i)
            *(this->_M_impl._M_finish._M_node + __i) = this->_M_allocate_node();
        }
      catch(...)
        {
          for (size_type __j = 1; __j < __i; ++__j)
            _M_deallocate_node(*(this->_M_impl._M_finish._M_node + __j));
          throw;
        }
    }
  template <typename _Tp, typename _Alloc>
    void
    deque<_Tp, _Alloc>::
    _M_reallocate_map(size_type __nodes_to_add, bool __add_at_front)
    {
      const size_type __old_num_nodes
 = this->_M_impl._M_finish._M_node - this->_M_impl._M_start._M_node + 1;
      const size_type __new_num_nodes = __old_num_nodes + __nodes_to_add;
      _Map_pointer __new_nstart;
      if (this->_M_impl._M_map_size > 2 * __new_num_nodes)
 {
   __new_nstart = this->_M_impl._M_map + (this->_M_impl._M_map_size
      - __new_num_nodes) / 2
                  + (__add_at_front ? __nodes_to_add : 0);
   if (__new_nstart < this->_M_impl._M_start._M_node)
     std::copy(this->_M_impl._M_start._M_node,
        this->_M_impl._M_finish._M_node + 1,
        __new_nstart);
   else
     std::copy_backward(this->_M_impl._M_start._M_node,
          this->_M_impl._M_finish._M_node + 1,
          __new_nstart + __old_num_nodes);
 }
      else
 {
   size_type __new_map_size = this->_M_impl._M_map_size
                              + std::max(this->_M_impl._M_map_size,
      __nodes_to_add) + 2;
   _Map_pointer __new_map = this->_M_allocate_map(__new_map_size);
   __new_nstart = __new_map + (__new_map_size - __new_num_nodes) / 2
                  + (__add_at_front ? __nodes_to_add : 0);
   std::copy(this->_M_impl._M_start._M_node,
      this->_M_impl._M_finish._M_node + 1,
      __new_nstart);
   _M_deallocate_map(this->_M_impl._M_map, this->_M_impl._M_map_size);
   this->_M_impl._M_map = __new_map;
   this->_M_impl._M_map_size = __new_map_size;
 }
      this->_M_impl._M_start._M_set_node(__new_nstart);
      this->_M_impl._M_finish._M_set_node(__new_nstart + __old_num_nodes - 1);
    }
  template<typename _Tp>
    void
    fill(const _Deque_iterator<_Tp, _Tp&, _Tp*>& __first,
  const _Deque_iterator<_Tp, _Tp&, _Tp*>& __last, const _Tp& __value)
    {
      typedef typename _Deque_iterator<_Tp, _Tp&, _Tp*>::_Self _Self;
      for (typename _Self::_Map_pointer __node = __first._M_node + 1;
           __node < __last._M_node; ++__node)
 std::fill(*__node, *__node + _Self::_S_buffer_size(), __value);
      if (__first._M_node != __last._M_node)
 {
   std::fill(__first._M_cur, __first._M_last, __value);
   std::fill(__last._M_first, __last._M_cur, __value);
 }
      else
 std::fill(__first._M_cur, __last._M_cur, __value);
    }
  template<typename _Tp>
    _Deque_iterator<_Tp, _Tp&, _Tp*>
    copy(_Deque_iterator<_Tp, const _Tp&, const _Tp*> __first,
  _Deque_iterator<_Tp, const _Tp&, const _Tp*> __last,
  _Deque_iterator<_Tp, _Tp&, _Tp*> __result)
    {
      typedef typename _Deque_iterator<_Tp, _Tp&, _Tp*>::_Self _Self;
      typedef typename _Self::difference_type difference_type;
      difference_type __len = __last - __first;
      while (__len > 0)
 {
   const difference_type __clen
     = std::min(__len, std::min(__first._M_last - __first._M_cur,
           __result._M_last - __result._M_cur));
   std::copy(__first._M_cur, __first._M_cur + __clen, __result._M_cur);
   __first += __clen;
   __result += __clen;
   __len -= __clen;
 }
      return __result;
    }
  template<typename _Tp>
    _Deque_iterator<_Tp, _Tp&, _Tp*>
    copy_backward(_Deque_iterator<_Tp, const _Tp&, const _Tp*> __first,
    _Deque_iterator<_Tp, const _Tp&, const _Tp*> __last,
    _Deque_iterator<_Tp, _Tp&, _Tp*> __result)
    {
      typedef typename _Deque_iterator<_Tp, _Tp&, _Tp*>::_Self _Self;
      typedef typename _Self::difference_type difference_type;
      difference_type __len = __last - __first;
      while (__len > 0)
 {
   difference_type __llen = __last._M_cur - __last._M_first;
   _Tp* __lend = __last._M_cur;
   difference_type __rlen = __result._M_cur - __result._M_first;
   _Tp* __rend = __result._M_cur;
   if (!__llen)
     {
       __llen = _Self::_S_buffer_size();
       __lend = *(__last._M_node - 1) + __llen;
     }
   if (!__rlen)
     {
       __rlen = _Self::_S_buffer_size();
       __rend = *(__result._M_node - 1) + __rlen;
     }
   const difference_type __clen = std::min(__len,
        std::min(__llen, __rlen));
   std::copy_backward(__lend - __clen, __lend, __rend);
   __last -= __clen;
   __result -= __clen;
   __len -= __clen;
 }
      return __result;
    }
  template<typename _Tp>
    _Deque_iterator<_Tp, _Tp&, _Tp*>
    move(_Deque_iterator<_Tp, const _Tp&, const _Tp*> __first,
  _Deque_iterator<_Tp, const _Tp&, const _Tp*> __last,
  _Deque_iterator<_Tp, _Tp&, _Tp*> __result)
    {
      typedef typename _Deque_iterator<_Tp, _Tp&, _Tp*>::_Self _Self;
      typedef typename _Self::difference_type difference_type;
      difference_type __len = __last - __first;
      while (__len > 0)
 {
   const difference_type __clen
     = std::min(__len, std::min(__first._M_last - __first._M_cur,
           __result._M_last - __result._M_cur));
   std::move(__first._M_cur, __first._M_cur + __clen, __result._M_cur);
   __first += __clen;
   __result += __clen;
   __len -= __clen;
 }
      return __result;
    }
  template<typename _Tp>
    _Deque_iterator<_Tp, _Tp&, _Tp*>
    move_backward(_Deque_iterator<_Tp, const _Tp&, const _Tp*> __first,
    _Deque_iterator<_Tp, const _Tp&, const _Tp*> __last,
    _Deque_iterator<_Tp, _Tp&, _Tp*> __result)
    {
      typedef typename _Deque_iterator<_Tp, _Tp&, _Tp*>::_Self _Self;
      typedef typename _Self::difference_type difference_type;
      difference_type __len = __last - __first;
      while (__len > 0)
 {
   difference_type __llen = __last._M_cur - __last._M_first;
   _Tp* __lend = __last._M_cur;
   difference_type __rlen = __result._M_cur - __result._M_first;
   _Tp* __rend = __result._M_cur;
   if (!__llen)
     {
       __llen = _Self::_S_buffer_size();
       __lend = *(__last._M_node - 1) + __llen;
     }
   if (!__rlen)
     {
       __rlen = _Self::_S_buffer_size();
       __rend = *(__result._M_node - 1) + __rlen;
     }
   const difference_type __clen = std::min(__len,
        std::min(__llen, __rlen));
   std::move_backward(__lend - __clen, __lend, __rend);
   __last -= __clen;
   __result -= __clen;
   __len -= __clen;
 }
      return __result;
    }

}
namespace std __attribute__ ((__visibility__ ("default")))
{

  struct allocator_arg_t { };
  constexpr allocator_arg_t allocator_arg = allocator_arg_t();
template<typename _Tp> class __has_allocator_type_helper { template<typename _Up> struct _Wrap_type { }; template<typename _Up> static true_type __test(_Wrap_type<typename _Up::allocator_type>*); template<typename _Up> static false_type __test(...); public: typedef decltype(__test<_Tp>(0)) type; }; template<typename _Tp> struct __has_allocator_type : public __has_allocator_type_helper <typename remove_cv<_Tp>::type>::type { };
  template<typename _Tp, typename _Alloc,
    bool = __has_allocator_type<_Tp>::value>
    struct __uses_allocator_helper
    : public false_type { };
  template<typename _Tp, typename _Alloc>
    struct __uses_allocator_helper<_Tp, _Alloc, true>
    : public integral_constant<bool, is_convertible<_Alloc,
         typename _Tp::allocator_type>::value>
    { };
  template<typename _Tp, typename _Alloc>
    struct uses_allocator
    : public integral_constant<bool,
          __uses_allocator_helper<_Tp, _Alloc>::value>
    { };
  template<typename _Tp, typename _Alloc, typename... _Args>
    struct __uses_allocator_arg
    : is_constructible<_Tp, _Alloc, _Args...>
    { static_assert( uses_allocator<_Tp, _Alloc>::value, "uses allocator" ); };
  struct __uses_alloc_base { };
  struct __uses_alloc0 : __uses_alloc_base
  { struct _Anything { _Anything(...) { } } _M_a; };
  template<typename _Alloc>
    struct __uses_alloc1 : __uses_alloc_base { const _Alloc* _M_a; };
  template<typename _Alloc>
    struct __uses_alloc2 : __uses_alloc_base { const _Alloc* _M_a; };
  template<bool, typename _Alloc, typename... _Args>
    struct __uses_alloc;
  template<typename _Tp, typename _Alloc, typename... _Args>
    struct __uses_alloc<true, _Tp, _Alloc, _Args...>
    : conditional<
        is_constructible<_Tp, allocator_arg_t, _Alloc, _Args...>::value,
        __uses_alloc1<_Alloc>,
        __uses_alloc2<_Alloc>>::type
    { };
  template<typename _Tp, typename _Alloc, typename... _Args>
    struct __uses_alloc<false, _Tp, _Alloc, _Args...>
    : __uses_alloc0 { };
  template<typename _Tp, typename _Alloc, typename... _Args>
    struct __uses_alloc_impl
    : __uses_alloc<uses_allocator<_Tp, _Alloc>::value, _Tp, _Alloc, _Args...>
    { };
  template<typename _Tp, typename _Alloc, typename... _Args>
    __uses_alloc_impl<_Tp, _Alloc, _Args...>
    __use_alloc(const _Alloc& __a)
    {
      __uses_alloc_impl<_Tp, _Alloc, _Args...> __ret;
      __ret._M_a = &__a;
      return __ret;
    }

}
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename _Tp, typename _Sequence = deque<_Tp> >
    class stack
    {
      typedef typename _Sequence::value_type _Sequence_value_type;
     
     
     
      template<typename _Tp1, typename _Seq1>
        friend bool
        operator==(const stack<_Tp1, _Seq1>&, const stack<_Tp1, _Seq1>&);
      template<typename _Tp1, typename _Seq1>
        friend bool
        operator<(const stack<_Tp1, _Seq1>&, const stack<_Tp1, _Seq1>&);
    public:
      typedef typename _Sequence::value_type value_type;
      typedef typename _Sequence::reference reference;
      typedef typename _Sequence::const_reference const_reference;
      typedef typename _Sequence::size_type size_type;
      typedef _Sequence container_type;
    protected:
      _Sequence c;
    public:
      explicit
      stack(const _Sequence& __c)
      : c(__c) { }
      explicit
      stack(_Sequence&& __c = _Sequence())
      : c(std::move(__c)) { }
      bool
      empty() const
      { return c.empty(); }
      size_type
      size() const
      { return c.size(); }
      reference
      top()
      {
 ;
 return c.back();
      }
      const_reference
      top() const
      {
 ;
 return c.back();
      }
      void
      push(const value_type& __x)
      { c.push_back(__x); }
      void
      push(value_type&& __x)
      { c.push_back(std::move(__x)); }
      template<typename... _Args>
        void
        emplace(_Args&&... __args)
 { c.emplace_back(std::forward<_Args>(__args)...); }
      void
      pop()
      {
 ;
 c.pop_back();
      }
      void
      swap(stack& __s)
      noexcept(noexcept(swap(c, __s.c)))
      {
 using std::swap;
 swap(c, __s.c);
      }
    };
  template<typename _Tp, typename _Seq>
    inline bool
    operator==(const stack<_Tp, _Seq>& __x, const stack<_Tp, _Seq>& __y)
    { return __x.c == __y.c; }
  template<typename _Tp, typename _Seq>
    inline bool
    operator<(const stack<_Tp, _Seq>& __x, const stack<_Tp, _Seq>& __y)
    { return __x.c < __y.c; }
  template<typename _Tp, typename _Seq>
    inline bool
    operator!=(const stack<_Tp, _Seq>& __x, const stack<_Tp, _Seq>& __y)
    { return !(__x == __y); }
  template<typename _Tp, typename _Seq>
    inline bool
    operator>(const stack<_Tp, _Seq>& __x, const stack<_Tp, _Seq>& __y)
    { return __y < __x; }
  template<typename _Tp, typename _Seq>
    inline bool
    operator<=(const stack<_Tp, _Seq>& __x, const stack<_Tp, _Seq>& __y)
    { return !(__y < __x); }
  template<typename _Tp, typename _Seq>
    inline bool
    operator>=(const stack<_Tp, _Seq>& __x, const stack<_Tp, _Seq>& __y)
    { return !(__x < __y); }
  template<typename _Tp, typename _Seq>
    inline void
    swap(stack<_Tp, _Seq>& __x, stack<_Tp, _Seq>& __y)
    noexcept(noexcept(__x.swap(__y)))
    { __x.swap(__y); }
  template<typename _Tp, typename _Seq, typename _Alloc>
    struct uses_allocator<stack<_Tp, _Seq>, _Alloc>
    : public uses_allocator<_Seq, _Alloc>::type { };

}
       
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename _Tp, typename _Alloc>
    struct _Vector_base
    {
      typedef typename __gnu_cxx::__alloc_traits<_Alloc>::template
        rebind<_Tp>::other _Tp_alloc_type;
      typedef typename __gnu_cxx::__alloc_traits<_Tp_alloc_type>::pointer
        pointer;
      struct _Vector_impl
      : public _Tp_alloc_type
      {
 pointer _M_start;
 pointer _M_finish;
 pointer _M_end_of_storage;
 _Vector_impl()
 : _Tp_alloc_type(), _M_start(0), _M_finish(0), _M_end_of_storage(0)
 { }
 _Vector_impl(_Tp_alloc_type const& __a) noexcept
 : _Tp_alloc_type(__a), _M_start(0), _M_finish(0), _M_end_of_storage(0)
 { }
 _Vector_impl(_Tp_alloc_type&& __a) noexcept
 : _Tp_alloc_type(std::move(__a)),
   _M_start(0), _M_finish(0), _M_end_of_storage(0)
 { }
 void _M_swap_data(_Vector_impl& __x) noexcept
 {
   std::swap(_M_start, __x._M_start);
   std::swap(_M_finish, __x._M_finish);
   std::swap(_M_end_of_storage, __x._M_end_of_storage);
 }
      };
    public:
      typedef _Alloc allocator_type;
      _Tp_alloc_type&
      _M_get_Tp_allocator() noexcept
      { return *static_cast<_Tp_alloc_type*>(&this->_M_impl); }
      const _Tp_alloc_type&
      _M_get_Tp_allocator() const noexcept
      { return *static_cast<const _Tp_alloc_type*>(&this->_M_impl); }
      allocator_type
      get_allocator() const noexcept
      { return allocator_type(_M_get_Tp_allocator()); }
      _Vector_base()
      : _M_impl() { }
      _Vector_base(const allocator_type& __a) noexcept
      : _M_impl(__a) { }
      _Vector_base(size_t __n)
      : _M_impl()
      { _M_create_storage(__n); }
      _Vector_base(size_t __n, const allocator_type& __a)
      : _M_impl(__a)
      { _M_create_storage(__n); }
      _Vector_base(_Tp_alloc_type&& __a) noexcept
      : _M_impl(std::move(__a)) { }
      _Vector_base(_Vector_base&& __x) noexcept
      : _M_impl(std::move(__x._M_get_Tp_allocator()))
      { this->_M_impl._M_swap_data(__x._M_impl); }
      _Vector_base(_Vector_base&& __x, const allocator_type& __a)
      : _M_impl(__a)
      {
 if (__x.get_allocator() == __a)
   this->_M_impl._M_swap_data(__x._M_impl);
 else
   {
     size_t __n = __x._M_impl._M_finish - __x._M_impl._M_start;
     _M_create_storage(__n);
   }
      }
      ~_Vector_base() noexcept
      { _M_deallocate(this->_M_impl._M_start, this->_M_impl._M_end_of_storage
        - this->_M_impl._M_start); }
    public:
      _Vector_impl _M_impl;
      pointer
      _M_allocate(size_t __n)
      {
 typedef __gnu_cxx::__alloc_traits<_Tp_alloc_type> _Tr;
 return __n != 0 ? _Tr::allocate(_M_impl, __n) : 0;
      }
      void
      _M_deallocate(pointer __p, size_t __n)
      {
 typedef __gnu_cxx::__alloc_traits<_Tp_alloc_type> _Tr;
 if (__p)
   _Tr::deallocate(_M_impl, __p, __n);
      }
    private:
      void
      _M_create_storage(size_t __n)
      {
 this->_M_impl._M_start = this->_M_allocate(__n);
 this->_M_impl._M_finish = this->_M_impl._M_start;
 this->_M_impl._M_end_of_storage = this->_M_impl._M_start + __n;
      }
    };
  template<typename _Tp, typename _Alloc = std::allocator<_Tp> >
    class vector : protected _Vector_base<_Tp, _Alloc>
    {
      typedef typename _Alloc::value_type _Alloc_value_type;
     
     
      typedef _Vector_base<_Tp, _Alloc> _Base;
      typedef typename _Base::_Tp_alloc_type _Tp_alloc_type;
      typedef __gnu_cxx::__alloc_traits<_Tp_alloc_type> _Alloc_traits;
    public:
      typedef _Tp value_type;
      typedef typename _Base::pointer pointer;
      typedef typename _Alloc_traits::const_pointer const_pointer;
      typedef typename _Alloc_traits::reference reference;
      typedef typename _Alloc_traits::const_reference const_reference;
      typedef __gnu_cxx::__normal_iterator<pointer, vector> iterator;
      typedef __gnu_cxx::__normal_iterator<const_pointer, vector>
      const_iterator;
      typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
      typedef std::reverse_iterator<iterator> reverse_iterator;
      typedef size_t size_type;
      typedef ptrdiff_t difference_type;
      typedef _Alloc allocator_type;
    protected:
      using _Base::_M_allocate;
      using _Base::_M_deallocate;
      using _Base::_M_impl;
      using _Base::_M_get_Tp_allocator;
    public:
      vector()
      noexcept(is_nothrow_default_constructible<_Alloc>::value)
      : _Base() { }
      explicit
      vector(const allocator_type& __a) noexcept
      : _Base(__a) { }
      explicit
      vector(size_type __n, const allocator_type& __a = allocator_type())
      : _Base(__n, __a)
      { _M_default_initialize(__n); }
      vector(size_type __n, const value_type& __value,
      const allocator_type& __a = allocator_type())
      : _Base(__n, __a)
      { _M_fill_initialize(__n, __value); }
      vector(const vector& __x)
      : _Base(__x.size(),
        _Alloc_traits::_S_select_on_copy(__x._M_get_Tp_allocator()))
      { this->_M_impl._M_finish =
   std::__uninitialized_copy_a(__x.begin(), __x.end(),
          this->_M_impl._M_start,
          _M_get_Tp_allocator());
      }
      vector(vector&& __x) noexcept
      : _Base(std::move(__x)) { }
      vector(const vector& __x, const allocator_type& __a)
      : _Base(__x.size(), __a)
      { this->_M_impl._M_finish =
   std::__uninitialized_copy_a(__x.begin(), __x.end(),
          this->_M_impl._M_start,
          _M_get_Tp_allocator());
      }
      vector(vector&& __rv, const allocator_type& __m)
      noexcept(_Alloc_traits::_S_always_equal())
      : _Base(std::move(__rv), __m)
      {
 if (__rv.get_allocator() != __m)
   {
     this->_M_impl._M_finish =
       std::__uninitialized_move_a(__rv.begin(), __rv.end(),
       this->_M_impl._M_start,
       _M_get_Tp_allocator());
     __rv.clear();
   }
      }
      vector(initializer_list<value_type> __l,
      const allocator_type& __a = allocator_type())
      : _Base(__a)
      {
 _M_range_initialize(__l.begin(), __l.end(),
       random_access_iterator_tag());
      }
      template<typename _InputIterator,
        typename = std::_RequireInputIter<_InputIterator>>
        vector(_InputIterator __first, _InputIterator __last,
        const allocator_type& __a = allocator_type())
 : _Base(__a)
        { _M_initialize_dispatch(__first, __last, __false_type()); }
      ~vector() noexcept
      { std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
        _M_get_Tp_allocator()); }
      vector&
      operator=(const vector& __x);
      vector&
      operator=(vector&& __x) noexcept(_Alloc_traits::_S_nothrow_move())
      {
        constexpr bool __move_storage =
          _Alloc_traits::_S_propagate_on_move_assign()
          || _Alloc_traits::_S_always_equal();
        _M_move_assign(std::move(__x),
                       integral_constant<bool, __move_storage>());
 return *this;
      }
      vector&
      operator=(initializer_list<value_type> __l)
      {
 this->assign(__l.begin(), __l.end());
 return *this;
      }
      void
      assign(size_type __n, const value_type& __val)
      { _M_fill_assign(__n, __val); }
      template<typename _InputIterator,
        typename = std::_RequireInputIter<_InputIterator>>
        void
        assign(_InputIterator __first, _InputIterator __last)
        { _M_assign_dispatch(__first, __last, __false_type()); }
      void
      assign(initializer_list<value_type> __l)
      { this->assign(__l.begin(), __l.end()); }
      using _Base::get_allocator;
      iterator
      begin() noexcept
      { return iterator(this->_M_impl._M_start); }
      const_iterator
      begin() const noexcept
      { return const_iterator(this->_M_impl._M_start); }
      iterator
      end() noexcept
      { return iterator(this->_M_impl._M_finish); }
      const_iterator
      end() const noexcept
      { return const_iterator(this->_M_impl._M_finish); }
      reverse_iterator
      rbegin() noexcept
      { return reverse_iterator(end()); }
      const_reverse_iterator
      rbegin() const noexcept
      { return const_reverse_iterator(end()); }
      reverse_iterator
      rend() noexcept
      { return reverse_iterator(begin()); }
      const_reverse_iterator
      rend() const noexcept
      { return const_reverse_iterator(begin()); }
      const_iterator
      cbegin() const noexcept
      { return const_iterator(this->_M_impl._M_start); }
      const_iterator
      cend() const noexcept
      { return const_iterator(this->_M_impl._M_finish); }
      const_reverse_iterator
      crbegin() const noexcept
      { return const_reverse_iterator(end()); }
      const_reverse_iterator
      crend() const noexcept
      { return const_reverse_iterator(begin()); }
      size_type
      size() const noexcept
      { return size_type(this->_M_impl._M_finish - this->_M_impl._M_start); }
      size_type
      max_size() const noexcept
      { return _Alloc_traits::max_size(_M_get_Tp_allocator()); }
      void
      resize(size_type __new_size)
      {
 if (__new_size > size())
   _M_default_append(__new_size - size());
 else if (__new_size < size())
   _M_erase_at_end(this->_M_impl._M_start + __new_size);
      }
      void
      resize(size_type __new_size, const value_type& __x)
      {
 if (__new_size > size())
   insert(end(), __new_size - size(), __x);
 else if (__new_size < size())
   _M_erase_at_end(this->_M_impl._M_start + __new_size);
      }
      void
      shrink_to_fit()
      { _M_shrink_to_fit(); }
      size_type
      capacity() const noexcept
      { return size_type(this->_M_impl._M_end_of_storage
    - this->_M_impl._M_start); }
      bool
      empty() const noexcept
      { return begin() == end(); }
      void
      reserve(size_type __n);
      reference
      operator[](size_type __n) noexcept
      { return *(this->_M_impl._M_start + __n); }
      const_reference
      operator[](size_type __n) const noexcept
      { return *(this->_M_impl._M_start + __n); }
    protected:
      void
      _M_range_check(size_type __n) const
      {
 if (__n >= this->size())
   __throw_out_of_range_fmt(("vector::_M_range_check: __n " "(which is %zu) >= this->size() " "(which is %zu)"),
       __n, this->size());
      }
    public:
      reference
      at(size_type __n)
      {
 _M_range_check(__n);
 return (*this)[__n];
      }
      const_reference
      at(size_type __n) const
      {
 _M_range_check(__n);
 return (*this)[__n];
      }
      reference
      front() noexcept
      { return *begin(); }
      const_reference
      front() const noexcept
      { return *begin(); }
      reference
      back() noexcept
      { return *(end() - 1); }
      const_reference
      back() const noexcept
      { return *(end() - 1); }
      _Tp*
      data() noexcept
      { return _M_data_ptr(this->_M_impl._M_start); }
      const _Tp*
      data() const noexcept
      { return _M_data_ptr(this->_M_impl._M_start); }
      void
      push_back(const value_type& __x)
      {
 if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage)
   {
     _Alloc_traits::construct(this->_M_impl, this->_M_impl._M_finish,
                              __x);
     ++this->_M_impl._M_finish;
   }
 else
   _M_emplace_back_aux(__x);
      }
      void
      push_back(value_type&& __x)
      { emplace_back(std::move(__x)); }
      template<typename... _Args>
        void
        emplace_back(_Args&&... __args);
      void
      pop_back() noexcept
      {
 --this->_M_impl._M_finish;
 _Alloc_traits::destroy(this->_M_impl, this->_M_impl._M_finish);
      }
      template<typename... _Args>
        iterator
        emplace(const_iterator __position, _Args&&... __args);
      iterator
      insert(const_iterator __position, const value_type& __x);
      iterator
      insert(const_iterator __position, value_type&& __x)
      { return emplace(__position, std::move(__x)); }
      iterator
      insert(const_iterator __position, initializer_list<value_type> __l)
      { return this->insert(__position, __l.begin(), __l.end()); }
      iterator
      insert(const_iterator __position, size_type __n, const value_type& __x)
      {
 difference_type __offset = __position - cbegin();
 _M_fill_insert(begin() + __offset, __n, __x);
 return begin() + __offset;
      }
      template<typename _InputIterator,
        typename = std::_RequireInputIter<_InputIterator>>
        iterator
        insert(const_iterator __position, _InputIterator __first,
        _InputIterator __last)
        {
   difference_type __offset = __position - cbegin();
   _M_insert_dispatch(begin() + __offset,
        __first, __last, __false_type());
   return begin() + __offset;
 }
      iterator
      erase(const_iterator __position)
      { return _M_erase(begin() + (__position - cbegin())); }
      iterator
      erase(const_iterator __first, const_iterator __last)
      {
 const auto __beg = begin();
 const auto __cbeg = cbegin();
 return _M_erase(__beg + (__first - __cbeg), __beg + (__last - __cbeg));
      }
      void
      swap(vector& __x)
      noexcept(_Alloc_traits::_S_nothrow_swap())
      {
 this->_M_impl._M_swap_data(__x._M_impl);
 _Alloc_traits::_S_on_swap(_M_get_Tp_allocator(),
                           __x._M_get_Tp_allocator());
      }
      void
      clear() noexcept
      { _M_erase_at_end(this->_M_impl._M_start); }
    protected:
      template<typename _ForwardIterator>
        pointer
        _M_allocate_and_copy(size_type __n,
        _ForwardIterator __first, _ForwardIterator __last)
        {
   pointer __result = this->_M_allocate(__n);
   try
     {
       std::__uninitialized_copy_a(__first, __last, __result,
       _M_get_Tp_allocator());
       return __result;
     }
   catch(...)
     {
       _M_deallocate(__result, __n);
       throw;
     }
 }
      template<typename _Integer>
        void
        _M_initialize_dispatch(_Integer __n, _Integer __value, __true_type)
        {
   this->_M_impl._M_start = _M_allocate(static_cast<size_type>(__n));
   this->_M_impl._M_end_of_storage =
     this->_M_impl._M_start + static_cast<size_type>(__n);
   _M_fill_initialize(static_cast<size_type>(__n), __value);
 }
      template<typename _InputIterator>
        void
        _M_initialize_dispatch(_InputIterator __first, _InputIterator __last,
          __false_type)
        {
   typedef typename std::iterator_traits<_InputIterator>::
     iterator_category _IterCategory;
   _M_range_initialize(__first, __last, _IterCategory());
 }
      template<typename _InputIterator>
        void
        _M_range_initialize(_InputIterator __first,
       _InputIterator __last, std::input_iterator_tag)
        {
   for (; __first != __last; ++__first)
     emplace_back(*__first);
 }
      template<typename _ForwardIterator>
        void
        _M_range_initialize(_ForwardIterator __first,
       _ForwardIterator __last, std::forward_iterator_tag)
        {
   const size_type __n = std::distance(__first, __last);
   this->_M_impl._M_start = this->_M_allocate(__n);
   this->_M_impl._M_end_of_storage = this->_M_impl._M_start + __n;
   this->_M_impl._M_finish =
     std::__uninitialized_copy_a(__first, __last,
     this->_M_impl._M_start,
     _M_get_Tp_allocator());
 }
      void
      _M_fill_initialize(size_type __n, const value_type& __value)
      {
 std::__uninitialized_fill_n_a(this->_M_impl._M_start, __n, __value,
          _M_get_Tp_allocator());
 this->_M_impl._M_finish = this->_M_impl._M_end_of_storage;
      }
      void
      _M_default_initialize(size_type __n)
      {
 std::__uninitialized_default_n_a(this->_M_impl._M_start, __n,
      _M_get_Tp_allocator());
 this->_M_impl._M_finish = this->_M_impl._M_end_of_storage;
      }
      template<typename _Integer>
        void
        _M_assign_dispatch(_Integer __n, _Integer __val, __true_type)
        { _M_fill_assign(__n, __val); }
      template<typename _InputIterator>
        void
        _M_assign_dispatch(_InputIterator __first, _InputIterator __last,
      __false_type)
        {
   typedef typename std::iterator_traits<_InputIterator>::
     iterator_category _IterCategory;
   _M_assign_aux(__first, __last, _IterCategory());
 }
      template<typename _InputIterator>
        void
        _M_assign_aux(_InputIterator __first, _InputIterator __last,
        std::input_iterator_tag);
      template<typename _ForwardIterator>
        void
        _M_assign_aux(_ForwardIterator __first, _ForwardIterator __last,
        std::forward_iterator_tag);
      void
      _M_fill_assign(size_type __n, const value_type& __val);
      template<typename _Integer>
        void
        _M_insert_dispatch(iterator __pos, _Integer __n, _Integer __val,
      __true_type)
        { _M_fill_insert(__pos, __n, __val); }
      template<typename _InputIterator>
        void
        _M_insert_dispatch(iterator __pos, _InputIterator __first,
      _InputIterator __last, __false_type)
        {
   typedef typename std::iterator_traits<_InputIterator>::
     iterator_category _IterCategory;
   _M_range_insert(__pos, __first, __last, _IterCategory());
 }
      template<typename _InputIterator>
        void
        _M_range_insert(iterator __pos, _InputIterator __first,
   _InputIterator __last, std::input_iterator_tag);
      template<typename _ForwardIterator>
        void
        _M_range_insert(iterator __pos, _ForwardIterator __first,
   _ForwardIterator __last, std::forward_iterator_tag);
      void
      _M_fill_insert(iterator __pos, size_type __n, const value_type& __x);
      void
      _M_default_append(size_type __n);
      bool
      _M_shrink_to_fit();
      template<typename... _Args>
        void
        _M_insert_aux(iterator __position, _Args&&... __args);
      template<typename... _Args>
        void
        _M_emplace_back_aux(_Args&&... __args);
      size_type
      _M_check_len(size_type __n, const char* __s) const
      {
 if (max_size() - size() < __n)
   __throw_length_error((__s));
 const size_type __len = size() + std::max(size(), __n);
 return (__len < size() || __len > max_size()) ? max_size() : __len;
      }
      void
      _M_erase_at_end(pointer __pos) noexcept
      {
 std::_Destroy(__pos, this->_M_impl._M_finish, _M_get_Tp_allocator());
 this->_M_impl._M_finish = __pos;
      }
      iterator
      _M_erase(iterator __position);
      iterator
      _M_erase(iterator __first, iterator __last);
    private:
      void
      _M_move_assign(vector&& __x, std::true_type) noexcept
      {
 vector __tmp(get_allocator());
 this->_M_impl._M_swap_data(__tmp._M_impl);
 this->_M_impl._M_swap_data(__x._M_impl);
 std::__alloc_on_move(_M_get_Tp_allocator(), __x._M_get_Tp_allocator());
      }
      void
      _M_move_assign(vector&& __x, std::false_type)
      {
 if (__x._M_get_Tp_allocator() == this->_M_get_Tp_allocator())
   _M_move_assign(std::move(__x), std::true_type());
 else
   {
     this->assign(std::__make_move_if_noexcept_iterator(__x.begin()),
    std::__make_move_if_noexcept_iterator(__x.end()));
     __x.clear();
   }
      }
      template<typename _Up>
 _Up*
 _M_data_ptr(_Up* __ptr) const
 { return __ptr; }
      template<typename _Ptr>
 typename std::pointer_traits<_Ptr>::element_type*
 _M_data_ptr(_Ptr __ptr) const
 { return empty() ? nullptr : std::__addressof(*__ptr); }
    };
  template<typename _Tp, typename _Alloc>
    inline bool
    operator==(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
    { return (__x.size() == __y.size()
       && std::equal(__x.begin(), __x.end(), __y.begin())); }
  template<typename _Tp, typename _Alloc>
    inline bool
    operator<(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
    { return std::lexicographical_compare(__x.begin(), __x.end(),
       __y.begin(), __y.end()); }
  template<typename _Tp, typename _Alloc>
    inline bool
    operator!=(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
    { return !(__x == __y); }
  template<typename _Tp, typename _Alloc>
    inline bool
    operator>(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
    { return __y < __x; }
  template<typename _Tp, typename _Alloc>
    inline bool
    operator<=(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
    { return !(__y < __x); }
  template<typename _Tp, typename _Alloc>
    inline bool
    operator>=(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
    { return !(__x < __y); }
  template<typename _Tp, typename _Alloc>
    inline void
    swap(vector<_Tp, _Alloc>& __x, vector<_Tp, _Alloc>& __y)
    { __x.swap(__y); }

}
namespace std __attribute__ ((__visibility__ ("default")))
{

  typedef unsigned long _Bit_type;
  enum { _S_word_bit = int(8 * sizeof(_Bit_type)) };
  struct _Bit_reference
  {
    _Bit_type * _M_p;
    _Bit_type _M_mask;
    _Bit_reference(_Bit_type * __x, _Bit_type __y)
    : _M_p(__x), _M_mask(__y) { }
    _Bit_reference() noexcept : _M_p(0), _M_mask(0) { }
    operator bool() const noexcept
    { return !!(*_M_p & _M_mask); }
    _Bit_reference&
    operator=(bool __x) noexcept
    {
      if (__x)
 *_M_p |= _M_mask;
      else
 *_M_p &= ~_M_mask;
      return *this;
    }
    _Bit_reference&
    operator=(const _Bit_reference& __x) noexcept
    { return *this = bool(__x); }
    bool
    operator==(const _Bit_reference& __x) const
    { return bool(*this) == bool(__x); }
    bool
    operator<(const _Bit_reference& __x) const
    { return !bool(*this) && bool(__x); }
    void
    flip() noexcept
    { *_M_p ^= _M_mask; }
  };
  inline void
  swap(_Bit_reference __x, _Bit_reference __y) noexcept
  {
    bool __tmp = __x;
    __x = __y;
    __y = __tmp;
  }
  inline void
  swap(_Bit_reference __x, bool& __y) noexcept
  {
    bool __tmp = __x;
    __x = __y;
    __y = __tmp;
  }
  inline void
  swap(bool& __x, _Bit_reference __y) noexcept
  {
    bool __tmp = __x;
    __x = __y;
    __y = __tmp;
  }
  struct _Bit_iterator_base
  : public std::iterator<std::random_access_iterator_tag, bool>
  {
    _Bit_type * _M_p;
    unsigned int _M_offset;
    _Bit_iterator_base(_Bit_type * __x, unsigned int __y)
    : _M_p(__x), _M_offset(__y) { }
    void
    _M_bump_up()
    {
      if (_M_offset++ == int(_S_word_bit) - 1)
 {
   _M_offset = 0;
   ++_M_p;
 }
    }
    void
    _M_bump_down()
    {
      if (_M_offset-- == 0)
 {
   _M_offset = int(_S_word_bit) - 1;
   --_M_p;
 }
    }
    void
    _M_incr(ptrdiff_t __i)
    {
      difference_type __n = __i + _M_offset;
      _M_p += __n / int(_S_word_bit);
      __n = __n % int(_S_word_bit);
      if (__n < 0)
 {
   __n += int(_S_word_bit);
   --_M_p;
 }
      _M_offset = static_cast<unsigned int>(__n);
    }
    bool
    operator==(const _Bit_iterator_base& __i) const
    { return _M_p == __i._M_p && _M_offset == __i._M_offset; }
    bool
    operator<(const _Bit_iterator_base& __i) const
    {
      return _M_p < __i._M_p
      || (_M_p == __i._M_p && _M_offset < __i._M_offset);
    }
    bool
    operator!=(const _Bit_iterator_base& __i) const
    { return !(*this == __i); }
    bool
    operator>(const _Bit_iterator_base& __i) const
    { return __i < *this; }
    bool
    operator<=(const _Bit_iterator_base& __i) const
    { return !(__i < *this); }
    bool
    operator>=(const _Bit_iterator_base& __i) const
    { return !(*this < __i); }
  };
  inline ptrdiff_t
  operator-(const _Bit_iterator_base& __x, const _Bit_iterator_base& __y)
  {
    return (int(_S_word_bit) * (__x._M_p - __y._M_p)
     + __x._M_offset - __y._M_offset);
  }
  struct _Bit_iterator : public _Bit_iterator_base
  {
    typedef _Bit_reference reference;
    typedef _Bit_reference* pointer;
    typedef _Bit_iterator iterator;
    _Bit_iterator() : _Bit_iterator_base(0, 0) { }
    _Bit_iterator(_Bit_type * __x, unsigned int __y)
    : _Bit_iterator_base(__x, __y) { }
    iterator
    _M_const_cast() const
    { return *this; }
    reference
    operator*() const
    { return reference(_M_p, 1UL << _M_offset); }
    iterator&
    operator++()
    {
      _M_bump_up();
      return *this;
    }
    iterator
    operator++(int)
    {
      iterator __tmp = *this;
      _M_bump_up();
      return __tmp;
    }
    iterator&
    operator--()
    {
      _M_bump_down();
      return *this;
    }
    iterator
    operator--(int)
    {
      iterator __tmp = *this;
      _M_bump_down();
      return __tmp;
    }
    iterator&
    operator+=(difference_type __i)
    {
      _M_incr(__i);
      return *this;
    }
    iterator&
    operator-=(difference_type __i)
    {
      *this += -__i;
      return *this;
    }
    iterator
    operator+(difference_type __i) const
    {
      iterator __tmp = *this;
      return __tmp += __i;
    }
    iterator
    operator-(difference_type __i) const
    {
      iterator __tmp = *this;
      return __tmp -= __i;
    }
    reference
    operator[](difference_type __i) const
    { return *(*this + __i); }
  };
  inline _Bit_iterator
  operator+(ptrdiff_t __n, const _Bit_iterator& __x)
  { return __x + __n; }
  struct _Bit_const_iterator : public _Bit_iterator_base
  {
    typedef bool reference;
    typedef bool const_reference;
    typedef const bool* pointer;
    typedef _Bit_const_iterator const_iterator;
    _Bit_const_iterator() : _Bit_iterator_base(0, 0) { }
    _Bit_const_iterator(_Bit_type * __x, unsigned int __y)
    : _Bit_iterator_base(__x, __y) { }
    _Bit_const_iterator(const _Bit_iterator& __x)
    : _Bit_iterator_base(__x._M_p, __x._M_offset) { }
    _Bit_iterator
    _M_const_cast() const
    { return _Bit_iterator(_M_p, _M_offset); }
    const_reference
    operator*() const
    { return _Bit_reference(_M_p, 1UL << _M_offset); }
    const_iterator&
    operator++()
    {
      _M_bump_up();
      return *this;
    }
    const_iterator
    operator++(int)
    {
      const_iterator __tmp = *this;
      _M_bump_up();
      return __tmp;
    }
    const_iterator&
    operator--()
    {
      _M_bump_down();
      return *this;
    }
    const_iterator
    operator--(int)
    {
      const_iterator __tmp = *this;
      _M_bump_down();
      return __tmp;
    }
    const_iterator&
    operator+=(difference_type __i)
    {
      _M_incr(__i);
      return *this;
    }
    const_iterator&
    operator-=(difference_type __i)
    {
      *this += -__i;
      return *this;
    }
    const_iterator
    operator+(difference_type __i) const
    {
      const_iterator __tmp = *this;
      return __tmp += __i;
    }
    const_iterator
    operator-(difference_type __i) const
    {
      const_iterator __tmp = *this;
      return __tmp -= __i;
    }
    const_reference
    operator[](difference_type __i) const
    { return *(*this + __i); }
  };
  inline _Bit_const_iterator
  operator+(ptrdiff_t __n, const _Bit_const_iterator& __x)
  { return __x + __n; }
  inline void
  __fill_bvector(_Bit_iterator __first, _Bit_iterator __last, bool __x)
  {
    for (; __first != __last; ++__first)
      *__first = __x;
  }
  inline void
  fill(_Bit_iterator __first, _Bit_iterator __last, const bool& __x)
  {
    if (__first._M_p != __last._M_p)
      {
 std::fill(__first._M_p + 1, __last._M_p, __x ? ~0 : 0);
 __fill_bvector(__first, _Bit_iterator(__first._M_p + 1, 0), __x);
 __fill_bvector(_Bit_iterator(__last._M_p, 0), __last, __x);
      }
    else
      __fill_bvector(__first, __last, __x);
  }
  template<typename _Alloc>
    struct _Bvector_base
    {
      typedef typename _Alloc::template rebind<_Bit_type>::other
        _Bit_alloc_type;
      struct _Bvector_impl
      : public _Bit_alloc_type
      {
 _Bit_iterator _M_start;
 _Bit_iterator _M_finish;
 _Bit_type* _M_end_of_storage;
 _Bvector_impl()
 : _Bit_alloc_type(), _M_start(), _M_finish(), _M_end_of_storage(0)
 { }
 _Bvector_impl(const _Bit_alloc_type& __a)
 : _Bit_alloc_type(__a), _M_start(), _M_finish(), _M_end_of_storage(0)
 { }
 _Bvector_impl(_Bit_alloc_type&& __a)
 : _Bit_alloc_type(std::move(__a)), _M_start(), _M_finish(),
   _M_end_of_storage(0)
 { }
      };
    public:
      typedef _Alloc allocator_type;
      _Bit_alloc_type&
      _M_get_Bit_allocator() noexcept
      { return *static_cast<_Bit_alloc_type*>(&this->_M_impl); }
      const _Bit_alloc_type&
      _M_get_Bit_allocator() const noexcept
      { return *static_cast<const _Bit_alloc_type*>(&this->_M_impl); }
      allocator_type
      get_allocator() const noexcept
      { return allocator_type(_M_get_Bit_allocator()); }
      _Bvector_base()
      : _M_impl() { }
      _Bvector_base(const allocator_type& __a)
      : _M_impl(__a) { }
      _Bvector_base(_Bvector_base&& __x) noexcept
      : _M_impl(std::move(__x._M_get_Bit_allocator()))
      {
 this->_M_impl._M_start = __x._M_impl._M_start;
 this->_M_impl._M_finish = __x._M_impl._M_finish;
 this->_M_impl._M_end_of_storage = __x._M_impl._M_end_of_storage;
 __x._M_impl._M_start = _Bit_iterator();
 __x._M_impl._M_finish = _Bit_iterator();
 __x._M_impl._M_end_of_storage = 0;
      }
      ~_Bvector_base()
      { this->_M_deallocate(); }
    protected:
      _Bvector_impl _M_impl;
      _Bit_type*
      _M_allocate(size_t __n)
      { return _M_impl.allocate(_S_nword(__n)); }
      void
      _M_deallocate()
      {
 if (_M_impl._M_start._M_p)
   _M_impl.deallocate(_M_impl._M_start._M_p,
        _M_impl._M_end_of_storage - _M_impl._M_start._M_p);
      }
      static size_t
      _S_nword(size_t __n)
      { return (__n + int(_S_word_bit) - 1) / int(_S_word_bit); }
    };

}
namespace std __attribute__ ((__visibility__ ("default")))
{

template<typename _Alloc>
  class vector<bool, _Alloc> : protected _Bvector_base<_Alloc>
  {
    typedef _Bvector_base<_Alloc> _Base;
    template<typename> friend struct hash;
  public:
    typedef bool value_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef _Bit_reference reference;
    typedef bool const_reference;
    typedef _Bit_reference* pointer;
    typedef const bool* const_pointer;
    typedef _Bit_iterator iterator;
    typedef _Bit_const_iterator const_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef _Alloc allocator_type;
    allocator_type get_allocator() const
    { return _Base::get_allocator(); }
  protected:
    using _Base::_M_allocate;
    using _Base::_M_deallocate;
    using _Base::_S_nword;
    using _Base::_M_get_Bit_allocator;
  public:
    vector()
    : _Base() { }
    explicit
    vector(const allocator_type& __a)
    : _Base(__a) { }
    explicit
    vector(size_type __n, const allocator_type& __a = allocator_type())
    : vector(__n, false, __a)
    { }
    vector(size_type __n, const bool& __value,
    const allocator_type& __a = allocator_type())
    : _Base(__a)
    {
      _M_initialize(__n);
      std::fill(this->_M_impl._M_start._M_p, this->_M_impl._M_end_of_storage,
  __value ? ~0 : 0);
    }
    vector(const vector& __x)
    : _Base(__x._M_get_Bit_allocator())
    {
      _M_initialize(__x.size());
      _M_copy_aligned(__x.begin(), __x.end(), this->_M_impl._M_start);
    }
    vector(vector&& __x) noexcept
    : _Base(std::move(__x)) { }
    vector(initializer_list<bool> __l,
    const allocator_type& __a = allocator_type())
    : _Base(__a)
    {
      _M_initialize_range(__l.begin(), __l.end(),
     random_access_iterator_tag());
    }
    template<typename _InputIterator,
      typename = std::_RequireInputIter<_InputIterator>>
      vector(_InputIterator __first, _InputIterator __last,
      const allocator_type& __a = allocator_type())
      : _Base(__a)
      { _M_initialize_dispatch(__first, __last, __false_type()); }
    ~vector() noexcept { }
    vector&
    operator=(const vector& __x)
    {
      if (&__x == this)
 return *this;
      if (__x.size() > capacity())
 {
   this->_M_deallocate();
   _M_initialize(__x.size());
 }
      this->_M_impl._M_finish = _M_copy_aligned(__x.begin(), __x.end(),
      begin());
      return *this;
    }
    vector&
    operator=(vector&& __x)
    {
      this->clear();
      this->swap(__x);
      return *this;
    }
    vector&
    operator=(initializer_list<bool> __l)
    {
      this->assign (__l.begin(), __l.end());
      return *this;
    }
    void
    assign(size_type __n, const bool& __x)
    { _M_fill_assign(__n, __x); }
    template<typename _InputIterator,
      typename = std::_RequireInputIter<_InputIterator>>
      void
      assign(_InputIterator __first, _InputIterator __last)
      { _M_assign_dispatch(__first, __last, __false_type()); }
    void
    assign(initializer_list<bool> __l)
    { this->assign(__l.begin(), __l.end()); }
    iterator
    begin() noexcept
    { return this->_M_impl._M_start; }
    const_iterator
    begin() const noexcept
    { return this->_M_impl._M_start; }
    iterator
    end() noexcept
    { return this->_M_impl._M_finish; }
    const_iterator
    end() const noexcept
    { return this->_M_impl._M_finish; }
    reverse_iterator
    rbegin() noexcept
    { return reverse_iterator(end()); }
    const_reverse_iterator
    rbegin() const noexcept
    { return const_reverse_iterator(end()); }
    reverse_iterator
    rend() noexcept
    { return reverse_iterator(begin()); }
    const_reverse_iterator
    rend() const noexcept
    { return const_reverse_iterator(begin()); }
    const_iterator
    cbegin() const noexcept
    { return this->_M_impl._M_start; }
    const_iterator
    cend() const noexcept
    { return this->_M_impl._M_finish; }
    const_reverse_iterator
    crbegin() const noexcept
    { return const_reverse_iterator(end()); }
    const_reverse_iterator
    crend() const noexcept
    { return const_reverse_iterator(begin()); }
    size_type
    size() const noexcept
    { return size_type(end() - begin()); }
    size_type
    max_size() const noexcept
    {
      const size_type __isize =
 __gnu_cxx::__numeric_traits<difference_type>::__max
 - int(_S_word_bit) + 1;
      const size_type __asize = _M_get_Bit_allocator().max_size();
      return (__asize <= __isize / int(_S_word_bit)
       ? __asize * int(_S_word_bit) : __isize);
    }
    size_type
    capacity() const noexcept
    { return size_type(const_iterator(this->_M_impl._M_end_of_storage, 0)
         - begin()); }
    bool
    empty() const noexcept
    { return begin() == end(); }
    reference
    operator[](size_type __n)
    {
      return *iterator(this->_M_impl._M_start._M_p
         + __n / int(_S_word_bit), __n % int(_S_word_bit));
    }
    const_reference
    operator[](size_type __n) const
    {
      return *const_iterator(this->_M_impl._M_start._M_p
        + __n / int(_S_word_bit), __n % int(_S_word_bit));
    }
  protected:
    void
    _M_range_check(size_type __n) const
    {
      if (__n >= this->size())
 __throw_out_of_range_fmt(("vector<bool>::_M_range_check: __n " "(which is %zu) >= this->size() " "(which is %zu)"),
     __n, this->size());
    }
  public:
    reference
    at(size_type __n)
    { _M_range_check(__n); return (*this)[__n]; }
    const_reference
    at(size_type __n) const
    { _M_range_check(__n); return (*this)[__n]; }
    void
    reserve(size_type __n)
    {
      if (__n > max_size())
 __throw_length_error(("vector::reserve"));
      if (capacity() < __n)
 _M_reallocate(__n);
    }
    reference
    front()
    { return *begin(); }
    const_reference
    front() const
    { return *begin(); }
    reference
    back()
    { return *(end() - 1); }
    const_reference
    back() const
    { return *(end() - 1); }
    void
    data() noexcept { }
    void
    push_back(bool __x)
    {
      if (this->_M_impl._M_finish._M_p != this->_M_impl._M_end_of_storage)
        *this->_M_impl._M_finish++ = __x;
      else
        _M_insert_aux(end(), __x);
    }
    void
    swap(vector& __x)
    {
      std::swap(this->_M_impl._M_start, __x._M_impl._M_start);
      std::swap(this->_M_impl._M_finish, __x._M_impl._M_finish);
      std::swap(this->_M_impl._M_end_of_storage,
  __x._M_impl._M_end_of_storage);
      std::__alloc_swap<typename _Base::_Bit_alloc_type>::
 _S_do_it(_M_get_Bit_allocator(), __x._M_get_Bit_allocator());
    }
    static void
    swap(reference __x, reference __y) noexcept
    {
      bool __tmp = __x;
      __x = __y;
      __y = __tmp;
    }
    iterator
    insert(const_iterator __position, const bool& __x = bool())
    {
      const difference_type __n = __position - begin();
      if (this->_M_impl._M_finish._M_p != this->_M_impl._M_end_of_storage
   && __position == end())
        *this->_M_impl._M_finish++ = __x;
      else
        _M_insert_aux(__position._M_const_cast(), __x);
      return begin() + __n;
    }
    template<typename _InputIterator,
      typename = std::_RequireInputIter<_InputIterator>>
      iterator
      insert(const_iterator __position,
      _InputIterator __first, _InputIterator __last)
      {
 difference_type __offset = __position - cbegin();
 _M_insert_dispatch(__position._M_const_cast(),
      __first, __last, __false_type());
 return begin() + __offset;
      }
    iterator
    insert(const_iterator __position, size_type __n, const bool& __x)
    {
      difference_type __offset = __position - cbegin();
      _M_fill_insert(__position._M_const_cast(), __n, __x);
      return begin() + __offset;
    }
    iterator
    insert(const_iterator __p, initializer_list<bool> __l)
    { return this->insert(__p, __l.begin(), __l.end()); }
    void
    pop_back()
    { --this->_M_impl._M_finish; }
    iterator
    erase(const_iterator __position)
    { return _M_erase(__position._M_const_cast()); }
    iterator
    erase(const_iterator __first, const_iterator __last)
    { return _M_erase(__first._M_const_cast(), __last._M_const_cast()); }
    void
    resize(size_type __new_size, bool __x = bool())
    {
      if (__new_size < size())
        _M_erase_at_end(begin() + difference_type(__new_size));
      else
        insert(end(), __new_size - size(), __x);
    }
    void
    shrink_to_fit()
    { _M_shrink_to_fit(); }
    void
    flip() noexcept
    {
      for (_Bit_type * __p = this->_M_impl._M_start._M_p;
    __p != this->_M_impl._M_end_of_storage; ++__p)
        *__p = ~*__p;
    }
    void
    clear() noexcept
    { _M_erase_at_end(begin()); }
    template<typename... _Args>
      void
      emplace_back(_Args&&... __args)
      { push_back(bool(__args...)); }
    template<typename... _Args>
      iterator
      emplace(const_iterator __pos, _Args&&... __args)
      { return insert(__pos, bool(__args...)); }
  protected:
    iterator
    _M_copy_aligned(const_iterator __first, const_iterator __last,
      iterator __result)
    {
      _Bit_type* __q = std::copy(__first._M_p, __last._M_p, __result._M_p);
      return std::copy(const_iterator(__last._M_p, 0), __last,
         iterator(__q, 0));
    }
    void
    _M_initialize(size_type __n)
    {
      _Bit_type* __q = this->_M_allocate(__n);
      this->_M_impl._M_end_of_storage = __q + _S_nword(__n);
      this->_M_impl._M_start = iterator(__q, 0);
      this->_M_impl._M_finish = this->_M_impl._M_start + difference_type(__n);
    }
    void
    _M_reallocate(size_type __n);
    bool
    _M_shrink_to_fit();
    template<typename _Integer>
      void
      _M_initialize_dispatch(_Integer __n, _Integer __x, __true_type)
      {
 _M_initialize(static_cast<size_type>(__n));
 std::fill(this->_M_impl._M_start._M_p,
    this->_M_impl._M_end_of_storage, __x ? ~0 : 0);
      }
    template<typename _InputIterator>
      void
      _M_initialize_dispatch(_InputIterator __first, _InputIterator __last,
        __false_type)
      { _M_initialize_range(__first, __last,
       std::__iterator_category(__first)); }
    template<typename _InputIterator>
      void
      _M_initialize_range(_InputIterator __first, _InputIterator __last,
     std::input_iterator_tag)
      {
 for (; __first != __last; ++__first)
   push_back(*__first);
      }
    template<typename _ForwardIterator>
      void
      _M_initialize_range(_ForwardIterator __first, _ForwardIterator __last,
     std::forward_iterator_tag)
      {
 const size_type __n = std::distance(__first, __last);
 _M_initialize(__n);
 std::copy(__first, __last, this->_M_impl._M_start);
      }
    template<typename _Integer>
      void
      _M_assign_dispatch(_Integer __n, _Integer __val, __true_type)
      { _M_fill_assign(__n, __val); }
    template<class _InputIterator>
      void
      _M_assign_dispatch(_InputIterator __first, _InputIterator __last,
    __false_type)
      { _M_assign_aux(__first, __last, std::__iterator_category(__first)); }
    void
    _M_fill_assign(size_t __n, bool __x)
    {
      if (__n > size())
 {
   std::fill(this->_M_impl._M_start._M_p,
      this->_M_impl._M_end_of_storage, __x ? ~0 : 0);
   insert(end(), __n - size(), __x);
 }
      else
 {
   _M_erase_at_end(begin() + __n);
   std::fill(this->_M_impl._M_start._M_p,
      this->_M_impl._M_end_of_storage, __x ? ~0 : 0);
 }
    }
    template<typename _InputIterator>
      void
      _M_assign_aux(_InputIterator __first, _InputIterator __last,
      std::input_iterator_tag)
      {
 iterator __cur = begin();
 for (; __first != __last && __cur != end(); ++__cur, ++__first)
   *__cur = *__first;
 if (__first == __last)
   _M_erase_at_end(__cur);
 else
   insert(end(), __first, __last);
      }
    template<typename _ForwardIterator>
      void
      _M_assign_aux(_ForwardIterator __first, _ForwardIterator __last,
      std::forward_iterator_tag)
      {
 const size_type __len = std::distance(__first, __last);
 if (__len < size())
   _M_erase_at_end(std::copy(__first, __last, begin()));
 else
   {
     _ForwardIterator __mid = __first;
     std::advance(__mid, size());
     std::copy(__first, __mid, begin());
     insert(end(), __mid, __last);
   }
      }
    template<typename _Integer>
      void
      _M_insert_dispatch(iterator __pos, _Integer __n, _Integer __x,
    __true_type)
      { _M_fill_insert(__pos, __n, __x); }
    template<typename _InputIterator>
      void
      _M_insert_dispatch(iterator __pos,
    _InputIterator __first, _InputIterator __last,
    __false_type)
      { _M_insert_range(__pos, __first, __last,
   std::__iterator_category(__first)); }
    void
    _M_fill_insert(iterator __position, size_type __n, bool __x);
    template<typename _InputIterator>
      void
      _M_insert_range(iterator __pos, _InputIterator __first,
        _InputIterator __last, std::input_iterator_tag)
      {
 for (; __first != __last; ++__first)
   {
     __pos = insert(__pos, *__first);
     ++__pos;
   }
      }
    template<typename _ForwardIterator>
      void
      _M_insert_range(iterator __position, _ForwardIterator __first,
        _ForwardIterator __last, std::forward_iterator_tag);
    void
    _M_insert_aux(iterator __position, bool __x);
    size_type
    _M_check_len(size_type __n, const char* __s) const
    {
      if (max_size() - size() < __n)
 __throw_length_error((__s));
      const size_type __len = size() + std::max(size(), __n);
      return (__len < size() || __len > max_size()) ? max_size() : __len;
    }
    void
    _M_erase_at_end(iterator __pos)
    { this->_M_impl._M_finish = __pos; }
    iterator
    _M_erase(iterator __pos);
    iterator
    _M_erase(iterator __first, iterator __last);
  };

}
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename _Alloc>
    struct hash<std::vector<bool, _Alloc>>
    : public __hash_base<size_t, std::vector<bool, _Alloc>>
    {
      size_t
      operator()(const std::vector<bool, _Alloc>&) const noexcept;
    };

}
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename _Tp, typename _Alloc>
    void
    vector<_Tp, _Alloc>::
    reserve(size_type __n)
    {
      if (__n > this->max_size())
 __throw_length_error(("vector::reserve"));
      if (this->capacity() < __n)
 {
   const size_type __old_size = size();
   pointer __tmp = _M_allocate_and_copy(__n,
     std::__make_move_if_noexcept_iterator(this->_M_impl._M_start),
     std::__make_move_if_noexcept_iterator(this->_M_impl._M_finish));
   std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
   _M_get_Tp_allocator());
   _M_deallocate(this->_M_impl._M_start,
   this->_M_impl._M_end_of_storage
   - this->_M_impl._M_start);
   this->_M_impl._M_start = __tmp;
   this->_M_impl._M_finish = __tmp + __old_size;
   this->_M_impl._M_end_of_storage = this->_M_impl._M_start + __n;
 }
    }
  template<typename _Tp, typename _Alloc>
    template<typename... _Args>
      void
      vector<_Tp, _Alloc>::
      emplace_back(_Args&&... __args)
      {
 if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage)
   {
     _Alloc_traits::construct(this->_M_impl, this->_M_impl._M_finish,
         std::forward<_Args>(__args)...);
     ++this->_M_impl._M_finish;
   }
 else
   _M_emplace_back_aux(std::forward<_Args>(__args)...);
      }
  template<typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::iterator
    vector<_Tp, _Alloc>::
    insert(const_iterator __position, const value_type& __x)
    {
      const size_type __n = __position - begin();
      if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage
   && __position == end())
 {
   _Alloc_traits::construct(this->_M_impl, this->_M_impl._M_finish, __x);
   ++this->_M_impl._M_finish;
 }
      else
 {
   const auto __pos = begin() + (__position - cbegin());
   if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage)
     {
       _Tp __x_copy = __x;
       _M_insert_aux(__pos, std::move(__x_copy));
     }
   else
     _M_insert_aux(__pos, __x);
 }
      return iterator(this->_M_impl._M_start + __n);
    }
  template<typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::iterator
    vector<_Tp, _Alloc>::
    _M_erase(iterator __position)
    {
      if (__position + 1 != end())
 std::move(__position + 1, end(), __position);
      --this->_M_impl._M_finish;
      _Alloc_traits::destroy(this->_M_impl, this->_M_impl._M_finish);
      return __position;
    }
  template<typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::iterator
    vector<_Tp, _Alloc>::
    _M_erase(iterator __first, iterator __last)
    {
      if (__first != __last)
 {
   if (__last != end())
     std::move(__last, end(), __first);
   _M_erase_at_end(__first.base() + (end() - __last));
 }
      return __first;
    }
  template<typename _Tp, typename _Alloc>
    vector<_Tp, _Alloc>&
    vector<_Tp, _Alloc>::
    operator=(const vector<_Tp, _Alloc>& __x)
    {
      if (&__x != this)
 {
   if (_Alloc_traits::_S_propagate_on_copy_assign())
     {
       if (!_Alloc_traits::_S_always_equal()
           && _M_get_Tp_allocator() != __x._M_get_Tp_allocator())
         {
    this->clear();
    _M_deallocate(this->_M_impl._M_start,
    this->_M_impl._M_end_of_storage
    - this->_M_impl._M_start);
    this->_M_impl._M_start = nullptr;
    this->_M_impl._M_finish = nullptr;
    this->_M_impl._M_end_of_storage = nullptr;
  }
       std::__alloc_on_copy(_M_get_Tp_allocator(),
       __x._M_get_Tp_allocator());
     }
   const size_type __xlen = __x.size();
   if (__xlen > capacity())
     {
       pointer __tmp = _M_allocate_and_copy(__xlen, __x.begin(),
         __x.end());
       std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
       _M_get_Tp_allocator());
       _M_deallocate(this->_M_impl._M_start,
       this->_M_impl._M_end_of_storage
       - this->_M_impl._M_start);
       this->_M_impl._M_start = __tmp;
       this->_M_impl._M_end_of_storage = this->_M_impl._M_start + __xlen;
     }
   else if (size() >= __xlen)
     {
       std::_Destroy(std::copy(__x.begin(), __x.end(), begin()),
       end(), _M_get_Tp_allocator());
     }
   else
     {
       std::copy(__x._M_impl._M_start, __x._M_impl._M_start + size(),
   this->_M_impl._M_start);
       std::__uninitialized_copy_a(__x._M_impl._M_start + size(),
       __x._M_impl._M_finish,
       this->_M_impl._M_finish,
       _M_get_Tp_allocator());
     }
   this->_M_impl._M_finish = this->_M_impl._M_start + __xlen;
 }
      return *this;
    }
  template<typename _Tp, typename _Alloc>
    void
    vector<_Tp, _Alloc>::
    _M_fill_assign(size_t __n, const value_type& __val)
    {
      if (__n > capacity())
 {
   vector __tmp(__n, __val, _M_get_Tp_allocator());
   __tmp._M_impl._M_swap_data(this->_M_impl);
 }
      else if (__n > size())
 {
   std::fill(begin(), end(), __val);
   std::__uninitialized_fill_n_a(this->_M_impl._M_finish,
     __n - size(), __val,
     _M_get_Tp_allocator());
   this->_M_impl._M_finish += __n - size();
 }
      else
        _M_erase_at_end(std::fill_n(this->_M_impl._M_start, __n, __val));
    }
  template<typename _Tp, typename _Alloc>
    template<typename _InputIterator>
      void
      vector<_Tp, _Alloc>::
      _M_assign_aux(_InputIterator __first, _InputIterator __last,
      std::input_iterator_tag)
      {
 pointer __cur(this->_M_impl._M_start);
 for (; __first != __last && __cur != this->_M_impl._M_finish;
      ++__cur, ++__first)
   *__cur = *__first;
 if (__first == __last)
   _M_erase_at_end(__cur);
 else
   insert(end(), __first, __last);
      }
  template<typename _Tp, typename _Alloc>
    template<typename _ForwardIterator>
      void
      vector<_Tp, _Alloc>::
      _M_assign_aux(_ForwardIterator __first, _ForwardIterator __last,
      std::forward_iterator_tag)
      {
 const size_type __len = std::distance(__first, __last);
 if (__len > capacity())
   {
     pointer __tmp(_M_allocate_and_copy(__len, __first, __last));
     std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
     _M_get_Tp_allocator());
     _M_deallocate(this->_M_impl._M_start,
     this->_M_impl._M_end_of_storage
     - this->_M_impl._M_start);
     this->_M_impl._M_start = __tmp;
     this->_M_impl._M_finish = this->_M_impl._M_start + __len;
     this->_M_impl._M_end_of_storage = this->_M_impl._M_finish;
   }
 else if (size() >= __len)
   _M_erase_at_end(std::copy(__first, __last, this->_M_impl._M_start));
 else
   {
     _ForwardIterator __mid = __first;
     std::advance(__mid, size());
     std::copy(__first, __mid, this->_M_impl._M_start);
     this->_M_impl._M_finish =
       std::__uninitialized_copy_a(__mid, __last,
       this->_M_impl._M_finish,
       _M_get_Tp_allocator());
   }
      }
  template<typename _Tp, typename _Alloc>
    template<typename... _Args>
      typename vector<_Tp, _Alloc>::iterator
      vector<_Tp, _Alloc>::
      emplace(const_iterator __position, _Args&&... __args)
      {
 const size_type __n = __position - begin();
 if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage
     && __position == end())
   {
     _Alloc_traits::construct(this->_M_impl, this->_M_impl._M_finish,
         std::forward<_Args>(__args)...);
     ++this->_M_impl._M_finish;
   }
 else
   _M_insert_aux(begin() + (__position - cbegin()),
   std::forward<_Args>(__args)...);
 return iterator(this->_M_impl._M_start + __n);
      }
  template<typename _Tp, typename _Alloc>
    template<typename... _Args>
      void
      vector<_Tp, _Alloc>::
      _M_insert_aux(iterator __position, _Args&&... __args)
    {
      if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage)
 {
   _Alloc_traits::construct(this->_M_impl, this->_M_impl._M_finish,
              std::move(*(this->_M_impl._M_finish - 1)));
   ++this->_M_impl._M_finish;
   std::move_backward(__position.base(), this->_M_impl._M_finish - 2, this->_M_impl._M_finish - 1);
   *__position = _Tp(std::forward<_Args>(__args)...);
 }
      else
 {
   const size_type __len =
     _M_check_len(size_type(1), "vector::_M_insert_aux");
   const size_type __elems_before = __position - begin();
   pointer __new_start(this->_M_allocate(__len));
   pointer __new_finish(__new_start);
   try
     {
       _Alloc_traits::construct(this->_M_impl,
                         __new_start + __elems_before,
           std::forward<_Args>(__args)...);
       __new_finish = 0;
       __new_finish
  = std::__uninitialized_move_if_noexcept_a
  (this->_M_impl._M_start, __position.base(),
   __new_start, _M_get_Tp_allocator());
       ++__new_finish;
       __new_finish
  = std::__uninitialized_move_if_noexcept_a
  (__position.base(), this->_M_impl._M_finish,
   __new_finish, _M_get_Tp_allocator());
     }
          catch(...)
     {
       if (!__new_finish)
  _Alloc_traits::destroy(this->_M_impl,
                         __new_start + __elems_before);
       else
  std::_Destroy(__new_start, __new_finish, _M_get_Tp_allocator());
       _M_deallocate(__new_start, __len);
       throw;
     }
   std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
   _M_get_Tp_allocator());
   _M_deallocate(this->_M_impl._M_start,
   this->_M_impl._M_end_of_storage
   - this->_M_impl._M_start);
   this->_M_impl._M_start = __new_start;
   this->_M_impl._M_finish = __new_finish;
   this->_M_impl._M_end_of_storage = __new_start + __len;
 }
    }
  template<typename _Tp, typename _Alloc>
    template<typename... _Args>
      void
      vector<_Tp, _Alloc>::
      _M_emplace_back_aux(_Args&&... __args)
      {
 const size_type __len =
   _M_check_len(size_type(1), "vector::_M_emplace_back_aux");
 pointer __new_start(this->_M_allocate(__len));
 pointer __new_finish(__new_start);
 try
   {
     _Alloc_traits::construct(this->_M_impl, __new_start + size(),
         std::forward<_Args>(__args)...);
     __new_finish = 0;
     __new_finish
       = std::__uninitialized_move_if_noexcept_a
       (this->_M_impl._M_start, this->_M_impl._M_finish,
        __new_start, _M_get_Tp_allocator());
     ++__new_finish;
   }
 catch(...)
   {
     if (!__new_finish)
       _Alloc_traits::destroy(this->_M_impl, __new_start + size());
     else
       std::_Destroy(__new_start, __new_finish, _M_get_Tp_allocator());
     _M_deallocate(__new_start, __len);
     throw;
   }
 std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
        _M_get_Tp_allocator());
 _M_deallocate(this->_M_impl._M_start,
        this->_M_impl._M_end_of_storage
        - this->_M_impl._M_start);
 this->_M_impl._M_start = __new_start;
 this->_M_impl._M_finish = __new_finish;
 this->_M_impl._M_end_of_storage = __new_start + __len;
      }
  template<typename _Tp, typename _Alloc>
    void
    vector<_Tp, _Alloc>::
    _M_fill_insert(iterator __position, size_type __n, const value_type& __x)
    {
      if (__n != 0)
 {
   if (size_type(this->_M_impl._M_end_of_storage
   - this->_M_impl._M_finish) >= __n)
     {
       value_type __x_copy = __x;
       const size_type __elems_after = end() - __position;
       pointer __old_finish(this->_M_impl._M_finish);
       if (__elems_after > __n)
  {
    std::__uninitialized_move_a(this->_M_impl._M_finish - __n,
           this->_M_impl._M_finish,
           this->_M_impl._M_finish,
           _M_get_Tp_allocator());
    this->_M_impl._M_finish += __n;
    std::move_backward(__position.base(), __old_finish - __n, __old_finish);
    std::fill(__position.base(), __position.base() + __n,
       __x_copy);
  }
       else
  {
    std::__uninitialized_fill_n_a(this->_M_impl._M_finish,
      __n - __elems_after,
      __x_copy,
      _M_get_Tp_allocator());
    this->_M_impl._M_finish += __n - __elems_after;
    std::__uninitialized_move_a(__position.base(), __old_finish,
           this->_M_impl._M_finish,
           _M_get_Tp_allocator());
    this->_M_impl._M_finish += __elems_after;
    std::fill(__position.base(), __old_finish, __x_copy);
  }
     }
   else
     {
       const size_type __len =
  _M_check_len(__n, "vector::_M_fill_insert");
       const size_type __elems_before = __position - begin();
       pointer __new_start(this->_M_allocate(__len));
       pointer __new_finish(__new_start);
       try
  {
    std::__uninitialized_fill_n_a(__new_start + __elems_before,
      __n, __x,
      _M_get_Tp_allocator());
    __new_finish = 0;
    __new_finish
      = std::__uninitialized_move_if_noexcept_a
      (this->_M_impl._M_start, __position.base(),
       __new_start, _M_get_Tp_allocator());
    __new_finish += __n;
    __new_finish
      = std::__uninitialized_move_if_noexcept_a
      (__position.base(), this->_M_impl._M_finish,
       __new_finish, _M_get_Tp_allocator());
  }
       catch(...)
  {
    if (!__new_finish)
      std::_Destroy(__new_start + __elems_before,
      __new_start + __elems_before + __n,
      _M_get_Tp_allocator());
    else
      std::_Destroy(__new_start, __new_finish,
      _M_get_Tp_allocator());
    _M_deallocate(__new_start, __len);
    throw;
  }
       std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
       _M_get_Tp_allocator());
       _M_deallocate(this->_M_impl._M_start,
       this->_M_impl._M_end_of_storage
       - this->_M_impl._M_start);
       this->_M_impl._M_start = __new_start;
       this->_M_impl._M_finish = __new_finish;
       this->_M_impl._M_end_of_storage = __new_start + __len;
     }
 }
    }
  template<typename _Tp, typename _Alloc>
    void
    vector<_Tp, _Alloc>::
    _M_default_append(size_type __n)
    {
      if (__n != 0)
 {
   if (size_type(this->_M_impl._M_end_of_storage
   - this->_M_impl._M_finish) >= __n)
     {
       std::__uninitialized_default_n_a(this->_M_impl._M_finish,
            __n, _M_get_Tp_allocator());
       this->_M_impl._M_finish += __n;
     }
   else
     {
       const size_type __len =
  _M_check_len(__n, "vector::_M_default_append");
       const size_type __old_size = this->size();
       pointer __new_start(this->_M_allocate(__len));
       pointer __new_finish(__new_start);
       try
  {
    __new_finish
      = std::__uninitialized_move_if_noexcept_a
      (this->_M_impl._M_start, this->_M_impl._M_finish,
       __new_start, _M_get_Tp_allocator());
    std::__uninitialized_default_n_a(__new_finish, __n,
         _M_get_Tp_allocator());
    __new_finish += __n;
  }
       catch(...)
  {
    std::_Destroy(__new_start, __new_finish,
    _M_get_Tp_allocator());
    _M_deallocate(__new_start, __len);
    throw;
  }
       std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
       _M_get_Tp_allocator());
       _M_deallocate(this->_M_impl._M_start,
       this->_M_impl._M_end_of_storage
       - this->_M_impl._M_start);
       this->_M_impl._M_start = __new_start;
       this->_M_impl._M_finish = __new_finish;
       this->_M_impl._M_end_of_storage = __new_start + __len;
     }
 }
    }
  template<typename _Tp, typename _Alloc>
    bool
    vector<_Tp, _Alloc>::
    _M_shrink_to_fit()
    {
      if (capacity() == size())
 return false;
      return std::__shrink_to_fit_aux<vector>::_S_do_it(*this);
    }
  template<typename _Tp, typename _Alloc>
    template<typename _InputIterator>
      void
      vector<_Tp, _Alloc>::
      _M_range_insert(iterator __pos, _InputIterator __first,
        _InputIterator __last, std::input_iterator_tag)
      {
 for (; __first != __last; ++__first)
   {
     __pos = insert(__pos, *__first);
     ++__pos;
   }
      }
  template<typename _Tp, typename _Alloc>
    template<typename _ForwardIterator>
      void
      vector<_Tp, _Alloc>::
      _M_range_insert(iterator __position, _ForwardIterator __first,
        _ForwardIterator __last, std::forward_iterator_tag)
      {
 if (__first != __last)
   {
     const size_type __n = std::distance(__first, __last);
     if (size_type(this->_M_impl._M_end_of_storage
     - this->_M_impl._M_finish) >= __n)
       {
  const size_type __elems_after = end() - __position;
  pointer __old_finish(this->_M_impl._M_finish);
  if (__elems_after > __n)
    {
      std::__uninitialized_move_a(this->_M_impl._M_finish - __n,
      this->_M_impl._M_finish,
      this->_M_impl._M_finish,
      _M_get_Tp_allocator());
      this->_M_impl._M_finish += __n;
      std::move_backward(__position.base(), __old_finish - __n, __old_finish);
      std::copy(__first, __last, __position);
    }
  else
    {
      _ForwardIterator __mid = __first;
      std::advance(__mid, __elems_after);
      std::__uninitialized_copy_a(__mid, __last,
      this->_M_impl._M_finish,
      _M_get_Tp_allocator());
      this->_M_impl._M_finish += __n - __elems_after;
      std::__uninitialized_move_a(__position.base(),
      __old_finish,
      this->_M_impl._M_finish,
      _M_get_Tp_allocator());
      this->_M_impl._M_finish += __elems_after;
      std::copy(__first, __mid, __position);
    }
       }
     else
       {
  const size_type __len =
    _M_check_len(__n, "vector::_M_range_insert");
  pointer __new_start(this->_M_allocate(__len));
  pointer __new_finish(__new_start);
  try
    {
      __new_finish
        = std::__uninitialized_move_if_noexcept_a
        (this->_M_impl._M_start, __position.base(),
         __new_start, _M_get_Tp_allocator());
      __new_finish
        = std::__uninitialized_copy_a(__first, __last,
          __new_finish,
          _M_get_Tp_allocator());
      __new_finish
        = std::__uninitialized_move_if_noexcept_a
        (__position.base(), this->_M_impl._M_finish,
         __new_finish, _M_get_Tp_allocator());
    }
  catch(...)
    {
      std::_Destroy(__new_start, __new_finish,
      _M_get_Tp_allocator());
      _M_deallocate(__new_start, __len);
      throw;
    }
  std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
         _M_get_Tp_allocator());
  _M_deallocate(this->_M_impl._M_start,
         this->_M_impl._M_end_of_storage
         - this->_M_impl._M_start);
  this->_M_impl._M_start = __new_start;
  this->_M_impl._M_finish = __new_finish;
  this->_M_impl._M_end_of_storage = __new_start + __len;
       }
   }
      }
  template<typename _Alloc>
    void
    vector<bool, _Alloc>::
    _M_reallocate(size_type __n)
    {
      _Bit_type* __q = this->_M_allocate(__n);
      this->_M_impl._M_finish = _M_copy_aligned(begin(), end(),
      iterator(__q, 0));
      this->_M_deallocate();
      this->_M_impl._M_start = iterator(__q, 0);
      this->_M_impl._M_end_of_storage = __q + _S_nword(__n);
    }
  template<typename _Alloc>
    void
    vector<bool, _Alloc>::
    _M_fill_insert(iterator __position, size_type __n, bool __x)
    {
      if (__n == 0)
 return;
      if (capacity() - size() >= __n)
 {
   std::copy_backward(__position, end(),
        this->_M_impl._M_finish + difference_type(__n));
   std::fill(__position, __position + difference_type(__n), __x);
   this->_M_impl._M_finish += difference_type(__n);
 }
      else
 {
   const size_type __len =
     _M_check_len(__n, "vector<bool>::_M_fill_insert");
   _Bit_type * __q = this->_M_allocate(__len);
   iterator __i = _M_copy_aligned(begin(), __position,
      iterator(__q, 0));
   std::fill(__i, __i + difference_type(__n), __x);
   this->_M_impl._M_finish = std::copy(__position, end(),
           __i + difference_type(__n));
   this->_M_deallocate();
   this->_M_impl._M_end_of_storage = __q + _S_nword(__len);
   this->_M_impl._M_start = iterator(__q, 0);
 }
    }
  template<typename _Alloc>
    template<typename _ForwardIterator>
      void
      vector<bool, _Alloc>::
      _M_insert_range(iterator __position, _ForwardIterator __first,
        _ForwardIterator __last, std::forward_iterator_tag)
      {
 if (__first != __last)
   {
     size_type __n = std::distance(__first, __last);
     if (capacity() - size() >= __n)
       {
  std::copy_backward(__position, end(),
       this->_M_impl._M_finish
       + difference_type(__n));
  std::copy(__first, __last, __position);
  this->_M_impl._M_finish += difference_type(__n);
       }
     else
       {
  const size_type __len =
    _M_check_len(__n, "vector<bool>::_M_insert_range");
  _Bit_type * __q = this->_M_allocate(__len);
  iterator __i = _M_copy_aligned(begin(), __position,
            iterator(__q, 0));
  __i = std::copy(__first, __last, __i);
  this->_M_impl._M_finish = std::copy(__position, end(), __i);
  this->_M_deallocate();
  this->_M_impl._M_end_of_storage = __q + _S_nword(__len);
  this->_M_impl._M_start = iterator(__q, 0);
       }
   }
      }
  template<typename _Alloc>
    void
    vector<bool, _Alloc>::
    _M_insert_aux(iterator __position, bool __x)
    {
      if (this->_M_impl._M_finish._M_p != this->_M_impl._M_end_of_storage)
 {
   std::copy_backward(__position, this->_M_impl._M_finish,
        this->_M_impl._M_finish + 1);
   *__position = __x;
   ++this->_M_impl._M_finish;
 }
      else
 {
   const size_type __len =
     _M_check_len(size_type(1), "vector<bool>::_M_insert_aux");
   _Bit_type * __q = this->_M_allocate(__len);
   iterator __i = _M_copy_aligned(begin(), __position,
      iterator(__q, 0));
   *__i++ = __x;
   this->_M_impl._M_finish = std::copy(__position, end(), __i);
   this->_M_deallocate();
   this->_M_impl._M_end_of_storage = __q + _S_nword(__len);
   this->_M_impl._M_start = iterator(__q, 0);
 }
    }
  template<typename _Alloc>
    typename vector<bool, _Alloc>::iterator
    vector<bool, _Alloc>::
    _M_erase(iterator __position)
    {
      if (__position + 1 != end())
        std::copy(__position + 1, end(), __position);
      --this->_M_impl._M_finish;
      return __position;
    }
  template<typename _Alloc>
    typename vector<bool, _Alloc>::iterator
    vector<bool, _Alloc>::
    _M_erase(iterator __first, iterator __last)
    {
      if (__first != __last)
 _M_erase_at_end(std::copy(__last, end(), __first));
      return __first;
    }
  template<typename _Alloc>
    bool
    vector<bool, _Alloc>::
    _M_shrink_to_fit()
    {
      if (capacity() - size() < int(_S_word_bit))
 return false;
      try
 {
   _M_reallocate(size());
   return true;
 }
      catch(...)
 { return false; }
    }

}
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename _Alloc>
    size_t
    hash<std::vector<bool, _Alloc>>::
    operator()(const std::vector<bool, _Alloc>& __b) const noexcept
    {
      size_t __hash = 0;
      using std::_S_word_bit;
      using std::_Bit_type;
      const size_t __words = __b.size() / _S_word_bit;
      if (__words)
 {
   const size_t __clength = __words * sizeof(_Bit_type);
   __hash = std::_Hash_impl::hash(__b._M_impl._M_start._M_p, __clength);
 }
      const size_t __extrabits = __b.size() % _S_word_bit;
      if (__extrabits)
 {
   _Bit_type __hiword = *__b._M_impl._M_finish._M_p;
   __hiword &= ~((~static_cast<_Bit_type>(0)) << __extrabits);
   const size_t __clength
     = (__extrabits + 8 - 1) / 8;
   if (__words)
     __hash = std::_Hash_impl::hash(&__hiword, __clength, __hash);
   else
     __hash = std::_Hash_impl::hash(&__hiword, __clength);
 }
      return __hash;
    }

}
       
       
#pragma GCC visibility push(default)
extern "C++" {
namespace __cxxabiv1
{
  class __class_type_info;
}
namespace std
{
  class type_info
  {
  public:
    virtual ~type_info();
    const char* name() const noexcept
    { return __name[0] == '*' ? __name + 1 : __name; }
    bool before(const type_info& __arg) const noexcept
    { return (__name[0] == '*' && __arg.__name[0] == '*')
 ? __name < __arg.__name
 : __builtin_strcmp (__name, __arg.__name) < 0; }
    bool operator==(const type_info& __arg) const noexcept
    {
      return ((__name == __arg.__name)
       || (__name[0] != '*' &&
    __builtin_strcmp (__name, __arg.__name) == 0));
    }
    bool operator!=(const type_info& __arg) const noexcept
    { return !operator==(__arg); }
    size_t hash_code() const noexcept
    {
      return _Hash_bytes(name(), __builtin_strlen(name()),
    static_cast<size_t>(0xc70f6907UL));
    }
    virtual bool __is_pointer_p() const;
    virtual bool __is_function_p() const;
    virtual bool __do_catch(const type_info *__thr_type, void **__thr_obj,
       unsigned __outer) const;
    virtual bool __do_upcast(const __cxxabiv1::__class_type_info *__target,
        void **__obj_ptr) const;
  protected:
    const char *__name;
    explicit type_info(const char *__n): __name(__n) { }
  private:
    type_info& operator=(const type_info&);
    type_info(const type_info&);
  };
  class bad_cast : public exception
  {
  public:
    bad_cast() noexcept { }
    virtual ~bad_cast() noexcept;
    virtual const char* what() const noexcept;
  };
  class bad_typeid : public exception
  {
  public:
    bad_typeid () noexcept { }
    virtual ~bad_typeid() noexcept;
    virtual const char* what() const noexcept;
  };
}
}
#pragma GCC visibility pop
       
       
       
namespace std __attribute__ ((__visibility__ ("default")))
{

  class logic_error : public exception
  {
    string _M_msg;
  public:
    explicit
    logic_error(const string& __arg);
    virtual ~logic_error() noexcept;
    virtual const char*
    what() const noexcept;
  };
  class domain_error : public logic_error
  {
  public:
    explicit domain_error(const string& __arg);
    virtual ~domain_error() noexcept;
  };
  class invalid_argument : public logic_error
  {
  public:
    explicit invalid_argument(const string& __arg);
    virtual ~invalid_argument() noexcept;
  };
  class length_error : public logic_error
  {
  public:
    explicit length_error(const string& __arg);
    virtual ~length_error() noexcept;
  };
  class out_of_range : public logic_error
  {
  public:
    explicit out_of_range(const string& __arg);
    virtual ~out_of_range() noexcept;
  };
  class runtime_error : public exception
  {
    string _M_msg;
  public:
    explicit
    runtime_error(const string& __arg);
    virtual ~runtime_error() noexcept;
    virtual const char*
    what() const noexcept;
  };
  class range_error : public runtime_error
  {
  public:
    explicit range_error(const string& __arg);
    virtual ~range_error() noexcept;
  };
  class overflow_error : public runtime_error
  {
  public:
    explicit overflow_error(const string& __arg);
    virtual ~overflow_error() noexcept;
  };
  class underflow_error : public runtime_error
  {
  public:
    explicit underflow_error(const string& __arg);
    virtual ~underflow_error() noexcept;
  };

}
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename _Tp, std::size_t _Nm>
    struct __array_traits
    {
      typedef _Tp _Type[_Nm];
      static constexpr _Tp&
      _S_ref(const _Type& __t, std::size_t __n) noexcept
      { return const_cast<_Tp&>(__t[__n]); }
    };
 template<typename _Tp>
   struct __array_traits<_Tp, 0>
   {
     struct _Type { };
     static constexpr _Tp&
     _S_ref(const _Type&, std::size_t) noexcept
     { return *static_cast<_Tp*>(nullptr); }
   };
  template<typename _Tp, std::size_t _Nm>
    struct array
    {
      typedef _Tp value_type;
      typedef value_type* pointer;
      typedef const value_type* const_pointer;
      typedef value_type& reference;
      typedef const value_type& const_reference;
      typedef value_type* iterator;
      typedef const value_type* const_iterator;
      typedef std::size_t size_type;
      typedef std::ptrdiff_t difference_type;
      typedef std::reverse_iterator<iterator> reverse_iterator;
      typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
      typedef std::__array_traits<_Tp, _Nm> _AT_Type;
      typename _AT_Type::_Type _M_elems;
      void
      fill(const value_type& __u)
      { std::fill_n(begin(), size(), __u); }
      void
      swap(array& __other)
      noexcept(noexcept(swap(std::declval<_Tp&>(), std::declval<_Tp&>())))
      { std::swap_ranges(begin(), end(), __other.begin()); }
      iterator
      begin() noexcept
      { return iterator(data()); }
      const_iterator
      begin() const noexcept
      { return const_iterator(data()); }
      iterator
      end() noexcept
      { return iterator(data() + _Nm); }
      const_iterator
      end() const noexcept
      { return const_iterator(data() + _Nm); }
      reverse_iterator
      rbegin() noexcept
      { return reverse_iterator(end()); }
      const_reverse_iterator
      rbegin() const noexcept
      { return const_reverse_iterator(end()); }
      reverse_iterator
      rend() noexcept
      { return reverse_iterator(begin()); }
      const_reverse_iterator
      rend() const noexcept
      { return const_reverse_iterator(begin()); }
      const_iterator
      cbegin() const noexcept
      { return const_iterator(data()); }
      const_iterator
      cend() const noexcept
      { return const_iterator(data() + _Nm); }
      const_reverse_iterator
      crbegin() const noexcept
      { return const_reverse_iterator(end()); }
      const_reverse_iterator
      crend() const noexcept
      { return const_reverse_iterator(begin()); }
      constexpr size_type
      size() const noexcept { return _Nm; }
      constexpr size_type
      max_size() const noexcept { return _Nm; }
      constexpr bool
      empty() const noexcept { return size() == 0; }
      reference
      operator[](size_type __n) noexcept
      { return _AT_Type::_S_ref(_M_elems, __n); }
      constexpr const_reference
      operator[](size_type __n) const noexcept
      { return _AT_Type::_S_ref(_M_elems, __n); }
      reference
      at(size_type __n)
      {
 if (__n >= _Nm)
   std::__throw_out_of_range_fmt(("array::at: __n (which is %zu) " ">= _Nm (which is %zu)"),
     __n, _Nm);
 return _AT_Type::_S_ref(_M_elems, __n);
      }
      constexpr const_reference
      at(size_type __n) const
      {
 return __n < _Nm ? _AT_Type::_S_ref(_M_elems, __n)
   : (std::__throw_out_of_range_fmt(("array::at: __n (which is %zu) " ">= _Nm (which is %zu)"),
        __n, _Nm),
      _AT_Type::_S_ref(_M_elems, 0));
      }
      reference
      front() noexcept
      { return *begin(); }
      constexpr const_reference
      front() const noexcept
      { return _AT_Type::_S_ref(_M_elems, 0); }
      reference
      back() noexcept
      { return _Nm ? *(end() - 1) : *end(); }
      constexpr const_reference
      back() const noexcept
      {
 return _Nm ? _AT_Type::_S_ref(_M_elems, _Nm - 1)
             : _AT_Type::_S_ref(_M_elems, 0);
      }
      pointer
      data() noexcept
      { return std::__addressof(_AT_Type::_S_ref(_M_elems, 0)); }
      const_pointer
      data() const noexcept
      { return std::__addressof(_AT_Type::_S_ref(_M_elems, 0)); }
    };
  template<typename _Tp, std::size_t _Nm>
    inline bool
    operator==(const array<_Tp, _Nm>& __one, const array<_Tp, _Nm>& __two)
    { return std::equal(__one.begin(), __one.end(), __two.begin()); }
  template<typename _Tp, std::size_t _Nm>
    inline bool
    operator!=(const array<_Tp, _Nm>& __one, const array<_Tp, _Nm>& __two)
    { return !(__one == __two); }
  template<typename _Tp, std::size_t _Nm>
    inline bool
    operator<(const array<_Tp, _Nm>& __a, const array<_Tp, _Nm>& __b)
    {
      return std::lexicographical_compare(__a.begin(), __a.end(),
       __b.begin(), __b.end());
    }
  template<typename _Tp, std::size_t _Nm>
    inline bool
    operator>(const array<_Tp, _Nm>& __one, const array<_Tp, _Nm>& __two)
    { return __two < __one; }
  template<typename _Tp, std::size_t _Nm>
    inline bool
    operator<=(const array<_Tp, _Nm>& __one, const array<_Tp, _Nm>& __two)
    { return !(__one > __two); }
  template<typename _Tp, std::size_t _Nm>
    inline bool
    operator>=(const array<_Tp, _Nm>& __one, const array<_Tp, _Nm>& __two)
    { return !(__one < __two); }
  template<typename _Tp, std::size_t _Nm>
    inline void
    swap(array<_Tp, _Nm>& __one, array<_Tp, _Nm>& __two)
    noexcept(noexcept(__one.swap(__two)))
    { __one.swap(__two); }
  template<std::size_t _Int, typename _Tp, std::size_t _Nm>
    constexpr _Tp&
    get(array<_Tp, _Nm>& __arr) noexcept
    {
      static_assert(_Int < _Nm, "index is out of bounds");
      return std::__array_traits<_Tp, _Nm>::
 _S_ref(__arr._M_elems, _Int);
    }
  template<std::size_t _Int, typename _Tp, std::size_t _Nm>
    constexpr _Tp&&
    get(array<_Tp, _Nm>&& __arr) noexcept
    {
      static_assert(_Int < _Nm, "index is out of bounds");
      return std::move(get<_Int>(__arr));
    }
  template<std::size_t _Int, typename _Tp, std::size_t _Nm>
    constexpr const _Tp&
    get(const array<_Tp, _Nm>& __arr) noexcept
    {
      static_assert(_Int < _Nm, "index is out of bounds");
      return std::__array_traits<_Tp, _Nm>::
 _S_ref(__arr._M_elems, _Int);
    }

}
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename _Tp>
    class tuple_size;
  template<typename _Tp, std::size_t _Nm>
    struct tuple_size<std::array<_Tp, _Nm>>
    : public integral_constant<std::size_t, _Nm> { };
  template<std::size_t _Int, typename _Tp>
    class tuple_element;
  template<std::size_t _Int, typename _Tp, std::size_t _Nm>
    struct tuple_element<_Int, std::array<_Tp, _Nm>>
    {
      static_assert(_Int < _Nm, "index is out of bounds");
      typedef _Tp type;
    };

}
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename _Tp>
    struct __add_c_ref
    { typedef const _Tp& type; };
  template<typename _Tp>
    struct __add_c_ref<_Tp&>
    { typedef _Tp& type; };
  template<typename _Tp>
    struct __add_ref
    { typedef _Tp& type; };
  template<typename _Tp>
    struct __add_ref<_Tp&>
    { typedef _Tp& type; };
  template<typename _Tp>
    struct __add_r_ref
    { typedef _Tp&& type; };
  template<typename _Tp>
    struct __add_r_ref<_Tp&>
    { typedef _Tp& type; };
  template<std::size_t _Idx, typename _Head, bool _IsEmptyNotFinal>
    struct _Head_base;
  template<std::size_t _Idx, typename _Head>
    struct _Head_base<_Idx, _Head, true>
    : public _Head
    {
      constexpr _Head_base()
      : _Head() { }
      constexpr _Head_base(const _Head& __h)
      : _Head(__h) { }
      template<typename _UHead, typename = typename
        enable_if<!is_convertible<_UHead,
                                  __uses_alloc_base>::value>::type>
        constexpr _Head_base(_UHead&& __h)
 : _Head(std::forward<_UHead>(__h)) { }
      _Head_base(__uses_alloc0)
      : _Head() { }
      template<typename _Alloc>
 _Head_base(__uses_alloc1<_Alloc> __a)
 : _Head(allocator_arg, *__a._M_a) { }
      template<typename _Alloc>
 _Head_base(__uses_alloc2<_Alloc> __a)
 : _Head(*__a._M_a) { }
      template<typename _UHead>
 _Head_base(__uses_alloc0, _UHead&& __uhead)
 : _Head(std::forward<_UHead>(__uhead)) { }
      template<typename _Alloc, typename _UHead>
 _Head_base(__uses_alloc1<_Alloc> __a, _UHead&& __uhead)
 : _Head(allocator_arg, *__a._M_a, std::forward<_UHead>(__uhead)) { }
      template<typename _Alloc, typename _UHead>
 _Head_base(__uses_alloc2<_Alloc> __a, _UHead&& __uhead)
 : _Head(std::forward<_UHead>(__uhead), *__a._M_a) { }
      static constexpr _Head&
      _M_head(_Head_base& __b) noexcept { return __b; }
      static constexpr const _Head&
      _M_head(const _Head_base& __b) noexcept { return __b; }
    };
  template<std::size_t _Idx, typename _Head>
    struct _Head_base<_Idx, _Head, false>
    {
      constexpr _Head_base()
      : _M_head_impl() { }
      constexpr _Head_base(const _Head& __h)
      : _M_head_impl(__h) { }
      template<typename _UHead, typename = typename
        enable_if<!is_convertible<_UHead,
                                  __uses_alloc_base>::value>::type>
        constexpr _Head_base(_UHead&& __h)
 : _M_head_impl(std::forward<_UHead>(__h)) { }
      _Head_base(__uses_alloc0)
      : _M_head_impl() { }
      template<typename _Alloc>
 _Head_base(__uses_alloc1<_Alloc> __a)
 : _M_head_impl(allocator_arg, *__a._M_a) { }
      template<typename _Alloc>
 _Head_base(__uses_alloc2<_Alloc> __a)
 : _M_head_impl(*__a._M_a) { }
      template<typename _UHead>
 _Head_base(__uses_alloc0, _UHead&& __uhead)
 : _M_head_impl(std::forward<_UHead>(__uhead)) { }
      template<typename _Alloc, typename _UHead>
 _Head_base(__uses_alloc1<_Alloc> __a, _UHead&& __uhead)
 : _M_head_impl(allocator_arg, *__a._M_a, std::forward<_UHead>(__uhead))
 { }
      template<typename _Alloc, typename _UHead>
 _Head_base(__uses_alloc2<_Alloc> __a, _UHead&& __uhead)
 : _M_head_impl(std::forward<_UHead>(__uhead), *__a._M_a) { }
      static constexpr _Head&
      _M_head(_Head_base& __b) noexcept { return __b._M_head_impl; }
      static constexpr const _Head&
      _M_head(const _Head_base& __b) noexcept { return __b._M_head_impl; }
      _Head _M_head_impl;
    };
  template<std::size_t _Idx, typename... _Elements>
    struct _Tuple_impl;
  template<std::size_t _Idx>
    struct _Tuple_impl<_Idx>
    {
      template<std::size_t, typename...> friend class _Tuple_impl;
      _Tuple_impl() = default;
      template<typename _Alloc>
        _Tuple_impl(allocator_arg_t, const _Alloc&) { }
      template<typename _Alloc>
        _Tuple_impl(allocator_arg_t, const _Alloc&, const _Tuple_impl&) { }
      template<typename _Alloc>
        _Tuple_impl(allocator_arg_t, const _Alloc&, _Tuple_impl&&) { }
    protected:
      void _M_swap(_Tuple_impl&) noexcept { }
    };
  template<typename _Tp>
    struct __is_empty_non_tuple : is_empty<_Tp> { };
  template<typename _El0, typename... _El>
    struct __is_empty_non_tuple<tuple<_El0, _El...>> : false_type { };
  template<typename _Tp>
    using __empty_not_final
    = typename conditional<__is_final(_Tp), false_type,
      __is_empty_non_tuple<_Tp>>::type;
  template<std::size_t _Idx, typename _Head, typename... _Tail>
    struct _Tuple_impl<_Idx, _Head, _Tail...>
    : public _Tuple_impl<_Idx + 1, _Tail...>,
      private _Head_base<_Idx, _Head, __empty_not_final<_Head>::value>
    {
      template<std::size_t, typename...> friend class _Tuple_impl;
      typedef _Tuple_impl<_Idx + 1, _Tail...> _Inherited;
      typedef _Head_base<_Idx, _Head, __empty_not_final<_Head>::value> _Base;
      static constexpr _Head&
      _M_head(_Tuple_impl& __t) noexcept { return _Base::_M_head(__t); }
      static constexpr const _Head&
      _M_head(const _Tuple_impl& __t) noexcept { return _Base::_M_head(__t); }
      static constexpr _Inherited&
      _M_tail(_Tuple_impl& __t) noexcept { return __t; }
      static constexpr const _Inherited&
      _M_tail(const _Tuple_impl& __t) noexcept { return __t; }
      constexpr _Tuple_impl()
      : _Inherited(), _Base() { }
      explicit
      constexpr _Tuple_impl(const _Head& __head, const _Tail&... __tail)
      : _Inherited(__tail...), _Base(__head) { }
      template<typename _UHead, typename... _UTail, typename = typename
               enable_if<sizeof...(_Tail) == sizeof...(_UTail)>::type>
        explicit
        constexpr _Tuple_impl(_UHead&& __head, _UTail&&... __tail)
 : _Inherited(std::forward<_UTail>(__tail)...),
   _Base(std::forward<_UHead>(__head)) { }
      constexpr _Tuple_impl(const _Tuple_impl&) = default;
      constexpr
      _Tuple_impl(_Tuple_impl&& __in)
      noexcept(__and_<is_nothrow_move_constructible<_Head>,
               is_nothrow_move_constructible<_Inherited>>::value)
      : _Inherited(std::move(_M_tail(__in))),
 _Base(std::forward<_Head>(_M_head(__in))) { }
      template<typename... _UElements>
        constexpr _Tuple_impl(const _Tuple_impl<_Idx, _UElements...>& __in)
 : _Inherited(_Tuple_impl<_Idx, _UElements...>::_M_tail(__in)),
   _Base(_Tuple_impl<_Idx, _UElements...>::_M_head(__in)) { }
      template<typename _UHead, typename... _UTails>
        constexpr _Tuple_impl(_Tuple_impl<_Idx, _UHead, _UTails...>&& __in)
 : _Inherited(std::move
       (_Tuple_impl<_Idx, _UHead, _UTails...>::_M_tail(__in))),
   _Base(std::forward<_UHead>
  (_Tuple_impl<_Idx, _UHead, _UTails...>::_M_head(__in))) { }
      template<typename _Alloc>
 _Tuple_impl(allocator_arg_t __tag, const _Alloc& __a)
 : _Inherited(__tag, __a),
          _Base(__use_alloc<_Head>(__a)) { }
      template<typename _Alloc>
 _Tuple_impl(allocator_arg_t __tag, const _Alloc& __a,
      const _Head& __head, const _Tail&... __tail)
 : _Inherited(__tag, __a, __tail...),
          _Base(__use_alloc<_Head, _Alloc, _Head>(__a), __head) { }
      template<typename _Alloc, typename _UHead, typename... _UTail,
               typename = typename enable_if<sizeof...(_Tail)
          == sizeof...(_UTail)>::type>
 _Tuple_impl(allocator_arg_t __tag, const _Alloc& __a,
             _UHead&& __head, _UTail&&... __tail)
 : _Inherited(__tag, __a, std::forward<_UTail>(__tail)...),
          _Base(__use_alloc<_Head, _Alloc, _UHead>(__a),
         std::forward<_UHead>(__head)) { }
      template<typename _Alloc>
        _Tuple_impl(allocator_arg_t __tag, const _Alloc& __a,
             const _Tuple_impl& __in)
 : _Inherited(__tag, __a, _M_tail(__in)),
          _Base(__use_alloc<_Head, _Alloc, _Head>(__a), _M_head(__in)) { }
      template<typename _Alloc>
 _Tuple_impl(allocator_arg_t __tag, const _Alloc& __a,
             _Tuple_impl&& __in)
 : _Inherited(__tag, __a, std::move(_M_tail(__in))),
   _Base(__use_alloc<_Head, _Alloc, _Head>(__a),
         std::forward<_Head>(_M_head(__in))) { }
      template<typename _Alloc, typename... _UElements>
 _Tuple_impl(allocator_arg_t __tag, const _Alloc& __a,
             const _Tuple_impl<_Idx, _UElements...>& __in)
 : _Inherited(__tag, __a,
       _Tuple_impl<_Idx, _UElements...>::_M_tail(__in)),
   _Base(__use_alloc<_Head, _Alloc, _Head>(__a),
  _Tuple_impl<_Idx, _UElements...>::_M_head(__in)) { }
      template<typename _Alloc, typename _UHead, typename... _UTails>
 _Tuple_impl(allocator_arg_t __tag, const _Alloc& __a,
             _Tuple_impl<_Idx, _UHead, _UTails...>&& __in)
 : _Inherited(__tag, __a, std::move
       (_Tuple_impl<_Idx, _UHead, _UTails...>::_M_tail(__in))),
   _Base(__use_alloc<_Head, _Alloc, _UHead>(__a),
                std::forward<_UHead>
  (_Tuple_impl<_Idx, _UHead, _UTails...>::_M_head(__in))) { }
      _Tuple_impl&
      operator=(const _Tuple_impl& __in)
      {
 _M_head(*this) = _M_head(__in);
 _M_tail(*this) = _M_tail(__in);
 return *this;
      }
      _Tuple_impl&
      operator=(_Tuple_impl&& __in)
      noexcept(__and_<is_nothrow_move_assignable<_Head>,
               is_nothrow_move_assignable<_Inherited>>::value)
      {
 _M_head(*this) = std::forward<_Head>(_M_head(__in));
 _M_tail(*this) = std::move(_M_tail(__in));
 return *this;
      }
      template<typename... _UElements>
        _Tuple_impl&
        operator=(const _Tuple_impl<_Idx, _UElements...>& __in)
        {
   _M_head(*this) = _Tuple_impl<_Idx, _UElements...>::_M_head(__in);
   _M_tail(*this) = _Tuple_impl<_Idx, _UElements...>::_M_tail(__in);
   return *this;
 }
      template<typename _UHead, typename... _UTails>
        _Tuple_impl&
        operator=(_Tuple_impl<_Idx, _UHead, _UTails...>&& __in)
        {
   _M_head(*this) = std::forward<_UHead>
     (_Tuple_impl<_Idx, _UHead, _UTails...>::_M_head(__in));
   _M_tail(*this) = std::move
     (_Tuple_impl<_Idx, _UHead, _UTails...>::_M_tail(__in));
   return *this;
 }
    protected:
      void
      _M_swap(_Tuple_impl& __in)
      noexcept(noexcept(swap(std::declval<_Head&>(),
        std::declval<_Head&>()))
        && noexcept(_M_tail(__in)._M_swap(_M_tail(__in))))
      {
 using std::swap;
 swap(_M_head(*this), _M_head(__in));
 _Inherited::_M_swap(_M_tail(__in));
      }
    };
  template<typename... _Elements>
    class tuple : public _Tuple_impl<0, _Elements...>
    {
      typedef _Tuple_impl<0, _Elements...> _Inherited;
    public:
      constexpr tuple()
      : _Inherited() { }
      explicit
      constexpr tuple(const _Elements&... __elements)
      : _Inherited(__elements...) { }
      template<typename... _UElements, typename = typename
        enable_if<__and_<is_convertible<_UElements,
     _Elements>...>::value>::type>
 explicit
        constexpr tuple(_UElements&&... __elements)
 : _Inherited(std::forward<_UElements>(__elements)...) { }
      constexpr tuple(const tuple&) = default;
      constexpr tuple(tuple&&) = default;
      template<typename... _UElements, typename = typename
        enable_if<__and_<is_convertible<const _UElements&,
     _Elements>...>::value>::type>
        constexpr tuple(const tuple<_UElements...>& __in)
        : _Inherited(static_cast<const _Tuple_impl<0, _UElements...>&>(__in))
        { }
      template<typename... _UElements, typename = typename
        enable_if<__and_<is_convertible<_UElements,
     _Elements>...>::value>::type>
        constexpr tuple(tuple<_UElements...>&& __in)
        : _Inherited(static_cast<_Tuple_impl<0, _UElements...>&&>(__in)) { }
      template<typename _Alloc>
 tuple(allocator_arg_t __tag, const _Alloc& __a)
 : _Inherited(__tag, __a) { }
      template<typename _Alloc>
 tuple(allocator_arg_t __tag, const _Alloc& __a,
       const _Elements&... __elements)
 : _Inherited(__tag, __a, __elements...) { }
      template<typename _Alloc, typename... _UElements, typename = typename
        enable_if<sizeof...(_UElements)
    == sizeof...(_Elements)>::type>
 tuple(allocator_arg_t __tag, const _Alloc& __a,
       _UElements&&... __elements)
 : _Inherited(__tag, __a, std::forward<_UElements>(__elements)...)
        { }
      template<typename _Alloc>
 tuple(allocator_arg_t __tag, const _Alloc& __a, const tuple& __in)
 : _Inherited(__tag, __a, static_cast<const _Inherited&>(__in)) { }
      template<typename _Alloc>
 tuple(allocator_arg_t __tag, const _Alloc& __a, tuple&& __in)
 : _Inherited(__tag, __a, static_cast<_Inherited&&>(__in)) { }
      template<typename _Alloc, typename... _UElements, typename = typename
        enable_if<sizeof...(_UElements)
    == sizeof...(_Elements)>::type>
 tuple(allocator_arg_t __tag, const _Alloc& __a,
       const tuple<_UElements...>& __in)
 : _Inherited(__tag, __a,
              static_cast<const _Tuple_impl<0, _UElements...>&>(__in))
 { }
      template<typename _Alloc, typename... _UElements, typename = typename
        enable_if<sizeof...(_UElements)
    == sizeof...(_Elements)>::type>
 tuple(allocator_arg_t __tag, const _Alloc& __a,
       tuple<_UElements...>&& __in)
 : _Inherited(__tag, __a,
              static_cast<_Tuple_impl<0, _UElements...>&&>(__in))
 { }
      tuple&
      operator=(const tuple& __in)
      {
 static_cast<_Inherited&>(*this) = __in;
 return *this;
      }
      tuple&
      operator=(tuple&& __in)
      noexcept(is_nothrow_move_assignable<_Inherited>::value)
      {
 static_cast<_Inherited&>(*this) = std::move(__in);
 return *this;
      }
      template<typename... _UElements, typename = typename
        enable_if<sizeof...(_UElements)
    == sizeof...(_Elements)>::type>
        tuple&
        operator=(const tuple<_UElements...>& __in)
        {
   static_cast<_Inherited&>(*this) = __in;
   return *this;
 }
      template<typename... _UElements, typename = typename
        enable_if<sizeof...(_UElements)
    == sizeof...(_Elements)>::type>
        tuple&
        operator=(tuple<_UElements...>&& __in)
        {
   static_cast<_Inherited&>(*this) = std::move(__in);
   return *this;
 }
      void
      swap(tuple& __in)
      noexcept(noexcept(__in._M_swap(__in)))
      { _Inherited::_M_swap(__in); }
    };
  template<>
    class tuple<>
    {
    public:
      void swap(tuple&) noexcept { }
    };
  template<typename _T1, typename _T2>
    class tuple<_T1, _T2> : public _Tuple_impl<0, _T1, _T2>
    {
      typedef _Tuple_impl<0, _T1, _T2> _Inherited;
    public:
      constexpr tuple()
      : _Inherited() { }
      explicit
      constexpr tuple(const _T1& __a1, const _T2& __a2)
      : _Inherited(__a1, __a2) { }
      template<typename _U1, typename _U2, typename = typename
        enable_if<__and_<is_convertible<_U1, _T1>,
    is_convertible<_U2, _T2>>::value>::type>
        explicit
        constexpr tuple(_U1&& __a1, _U2&& __a2)
 : _Inherited(std::forward<_U1>(__a1), std::forward<_U2>(__a2)) { }
      constexpr tuple(const tuple&) = default;
      constexpr tuple(tuple&&) = default;
      template<typename _U1, typename _U2, typename = typename
 enable_if<__and_<is_convertible<const _U1&, _T1>,
    is_convertible<const _U2&, _T2>>::value>::type>
        constexpr tuple(const tuple<_U1, _U2>& __in)
 : _Inherited(static_cast<const _Tuple_impl<0, _U1, _U2>&>(__in)) { }
      template<typename _U1, typename _U2, typename = typename
        enable_if<__and_<is_convertible<_U1, _T1>,
    is_convertible<_U2, _T2>>::value>::type>
        constexpr tuple(tuple<_U1, _U2>&& __in)
 : _Inherited(static_cast<_Tuple_impl<0, _U1, _U2>&&>(__in)) { }
      template<typename _U1, typename _U2, typename = typename
 enable_if<__and_<is_convertible<const _U1&, _T1>,
    is_convertible<const _U2&, _T2>>::value>::type>
        constexpr tuple(const pair<_U1, _U2>& __in)
 : _Inherited(__in.first, __in.second) { }
      template<typename _U1, typename _U2, typename = typename
        enable_if<__and_<is_convertible<_U1, _T1>,
    is_convertible<_U2, _T2>>::value>::type>
        constexpr tuple(pair<_U1, _U2>&& __in)
 : _Inherited(std::forward<_U1>(__in.first),
       std::forward<_U2>(__in.second)) { }
      template<typename _Alloc>
 tuple(allocator_arg_t __tag, const _Alloc& __a)
 : _Inherited(__tag, __a) { }
      template<typename _Alloc>
 tuple(allocator_arg_t __tag, const _Alloc& __a,
       const _T1& __a1, const _T2& __a2)
 : _Inherited(__tag, __a, __a1, __a2) { }
      template<typename _Alloc, typename _U1, typename _U2>
 tuple(allocator_arg_t __tag, const _Alloc& __a, _U1&& __a1, _U2&& __a2)
 : _Inherited(__tag, __a, std::forward<_U1>(__a1),
              std::forward<_U2>(__a2)) { }
      template<typename _Alloc>
 tuple(allocator_arg_t __tag, const _Alloc& __a, const tuple& __in)
 : _Inherited(__tag, __a, static_cast<const _Inherited&>(__in)) { }
      template<typename _Alloc>
 tuple(allocator_arg_t __tag, const _Alloc& __a, tuple&& __in)
 : _Inherited(__tag, __a, static_cast<_Inherited&&>(__in)) { }
      template<typename _Alloc, typename _U1, typename _U2>
 tuple(allocator_arg_t __tag, const _Alloc& __a,
       const tuple<_U1, _U2>& __in)
 : _Inherited(__tag, __a,
              static_cast<const _Tuple_impl<0, _U1, _U2>&>(__in))
 { }
      template<typename _Alloc, typename _U1, typename _U2>
 tuple(allocator_arg_t __tag, const _Alloc& __a, tuple<_U1, _U2>&& __in)
 : _Inherited(__tag, __a, static_cast<_Tuple_impl<0, _U1, _U2>&&>(__in))
 { }
      template<typename _Alloc, typename _U1, typename _U2>
        tuple(allocator_arg_t __tag, const _Alloc& __a,
       const pair<_U1, _U2>& __in)
 : _Inherited(__tag, __a, __in.first, __in.second) { }
      template<typename _Alloc, typename _U1, typename _U2>
        tuple(allocator_arg_t __tag, const _Alloc& __a, pair<_U1, _U2>&& __in)
 : _Inherited(__tag, __a, std::forward<_U1>(__in.first),
       std::forward<_U2>(__in.second)) { }
      tuple&
      operator=(const tuple& __in)
      {
 static_cast<_Inherited&>(*this) = __in;
 return *this;
      }
      tuple&
      operator=(tuple&& __in)
      noexcept(is_nothrow_move_assignable<_Inherited>::value)
      {
 static_cast<_Inherited&>(*this) = std::move(__in);
 return *this;
      }
      template<typename _U1, typename _U2>
        tuple&
        operator=(const tuple<_U1, _U2>& __in)
        {
   static_cast<_Inherited&>(*this) = __in;
   return *this;
 }
      template<typename _U1, typename _U2>
        tuple&
        operator=(tuple<_U1, _U2>&& __in)
        {
   static_cast<_Inherited&>(*this) = std::move(__in);
   return *this;
 }
      template<typename _U1, typename _U2>
        tuple&
        operator=(const pair<_U1, _U2>& __in)
        {
   this->_M_head(*this) = __in.first;
   this->_M_tail(*this)._M_head(*this) = __in.second;
   return *this;
 }
      template<typename _U1, typename _U2>
        tuple&
        operator=(pair<_U1, _U2>&& __in)
        {
   this->_M_head(*this) = std::forward<_U1>(__in.first);
   this->_M_tail(*this)._M_head(*this) = std::forward<_U2>(__in.second);
   return *this;
 }
      void
      swap(tuple& __in)
      noexcept(noexcept(__in._M_swap(__in)))
      { _Inherited::_M_swap(__in); }
    };
  template<std::size_t __i, typename _Tp>
    struct tuple_element;
  template<std::size_t __i, typename _Head, typename... _Tail>
    struct tuple_element<__i, tuple<_Head, _Tail...> >
    : tuple_element<__i - 1, tuple<_Tail...> > { };
  template<typename _Head, typename... _Tail>
    struct tuple_element<0, tuple<_Head, _Tail...> >
    {
      typedef _Head type;
    };
  template<std::size_t __i, typename _Tp>
    struct tuple_element<__i, const _Tp>
    {
      typedef typename
      add_const<typename tuple_element<__i, _Tp>::type>::type type;
    };
  template<std::size_t __i, typename _Tp>
    struct tuple_element<__i, volatile _Tp>
    {
      typedef typename
      add_volatile<typename tuple_element<__i, _Tp>::type>::type type;
    };
  template<std::size_t __i, typename _Tp>
    struct tuple_element<__i, const volatile _Tp>
    {
      typedef typename
      add_cv<typename tuple_element<__i, _Tp>::type>::type type;
    };
  template<typename _Tp>
    struct tuple_size;
  template<typename _Tp>
    struct tuple_size<const _Tp>
    : public integral_constant<size_t, tuple_size<_Tp>::value> { };
  template<typename _Tp>
    struct tuple_size<volatile _Tp>
    : public integral_constant<size_t, tuple_size<_Tp>::value> { };
  template<typename _Tp>
    struct tuple_size<const volatile _Tp>
    : public integral_constant<size_t, tuple_size<_Tp>::value> { };
  template<typename... _Elements>
    struct tuple_size<tuple<_Elements...>>
    : public integral_constant<std::size_t, sizeof...(_Elements)> { };
  template<std::size_t __i, typename _Head, typename... _Tail>
    constexpr typename __add_ref<_Head>::type
    __get_helper(_Tuple_impl<__i, _Head, _Tail...>& __t) noexcept
    { return _Tuple_impl<__i, _Head, _Tail...>::_M_head(__t); }
  template<std::size_t __i, typename _Head, typename... _Tail>
    constexpr typename __add_c_ref<_Head>::type
    __get_helper(const _Tuple_impl<__i, _Head, _Tail...>& __t) noexcept
    { return _Tuple_impl<__i, _Head, _Tail...>::_M_head(__t); }
  template<std::size_t __i, typename... _Elements>
    constexpr typename __add_ref<
                      typename tuple_element<__i, tuple<_Elements...>>::type
                    >::type
    get(tuple<_Elements...>& __t) noexcept
    { return std::__get_helper<__i>(__t); }
  template<std::size_t __i, typename... _Elements>
    constexpr typename __add_c_ref<
                      typename tuple_element<__i, tuple<_Elements...>>::type
                    >::type
    get(const tuple<_Elements...>& __t) noexcept
    { return std::__get_helper<__i>(__t); }
  template<std::size_t __i, typename... _Elements>
    constexpr typename __add_r_ref<
                      typename tuple_element<__i, tuple<_Elements...>>::type
                    >::type
    get(tuple<_Elements...>&& __t) noexcept
    { return std::forward<typename tuple_element<__i,
 tuple<_Elements...>>::type&&>(get<__i>(__t)); }
  template<std::size_t __check_equal_size, std::size_t __i, std::size_t __j,
    typename _Tp, typename _Up>
    struct __tuple_compare;
  template<std::size_t __i, std::size_t __j, typename _Tp, typename _Up>
    struct __tuple_compare<0, __i, __j, _Tp, _Up>
    {
      static constexpr bool
      __eq(const _Tp& __t, const _Up& __u)
      {
 return (get<__i>(__t) == get<__i>(__u) &&
  __tuple_compare<0, __i + 1, __j, _Tp, _Up>::__eq(__t, __u));
      }
      static constexpr bool
      __less(const _Tp& __t, const _Up& __u)
      {
 return ((get<__i>(__t) < get<__i>(__u))
  || !(get<__i>(__u) < get<__i>(__t)) &&
  __tuple_compare<0, __i + 1, __j, _Tp, _Up>::__less(__t, __u));
      }
    };
  template<std::size_t __i, typename _Tp, typename _Up>
    struct __tuple_compare<0, __i, __i, _Tp, _Up>
    {
      static constexpr bool
      __eq(const _Tp&, const _Up&) { return true; }
      static constexpr bool
      __less(const _Tp&, const _Up&) { return false; }
    };
  template<typename... _TElements, typename... _UElements>
    constexpr bool
    operator==(const tuple<_TElements...>& __t,
        const tuple<_UElements...>& __u)
    {
      typedef tuple<_TElements...> _Tp;
      typedef tuple<_UElements...> _Up;
      return bool(__tuple_compare<tuple_size<_Tp>::value - tuple_size<_Up>::value,
       0, tuple_size<_Tp>::value, _Tp, _Up>::__eq(__t, __u));
    }
  template<typename... _TElements, typename... _UElements>
    constexpr bool
    operator<(const tuple<_TElements...>& __t,
       const tuple<_UElements...>& __u)
    {
      typedef tuple<_TElements...> _Tp;
      typedef tuple<_UElements...> _Up;
      return bool(__tuple_compare<tuple_size<_Tp>::value - tuple_size<_Up>::value,
       0, tuple_size<_Tp>::value, _Tp, _Up>::__less(__t, __u));
    }
  template<typename... _TElements, typename... _UElements>
    constexpr bool
    operator!=(const tuple<_TElements...>& __t,
        const tuple<_UElements...>& __u)
    { return !(__t == __u); }
  template<typename... _TElements, typename... _UElements>
    constexpr bool
    operator>(const tuple<_TElements...>& __t,
       const tuple<_UElements...>& __u)
    { return __u < __t; }
  template<typename... _TElements, typename... _UElements>
    constexpr bool
    operator<=(const tuple<_TElements...>& __t,
        const tuple<_UElements...>& __u)
    { return !(__u < __t); }
  template<typename... _TElements, typename... _UElements>
    constexpr bool
    operator>=(const tuple<_TElements...>& __t,
        const tuple<_UElements...>& __u)
    { return !(__t < __u); }
  template<typename... _Elements>
    constexpr tuple<typename __decay_and_strip<_Elements>::__type...>
    make_tuple(_Elements&&... __args)
    {
      typedef tuple<typename __decay_and_strip<_Elements>::__type...>
 __result_type;
      return __result_type(std::forward<_Elements>(__args)...);
    }
  template<typename... _Elements>
    tuple<_Elements&&...>
    forward_as_tuple(_Elements&&... __args) noexcept
    { return tuple<_Elements&&...>(std::forward<_Elements>(__args)...); }
  template<typename>
    struct __is_tuple_like_impl : false_type
    { };
  template<typename... _Tps>
    struct __is_tuple_like_impl<tuple<_Tps...>> : true_type
    { };
  template<typename _T1, typename _T2>
    struct __is_tuple_like_impl<pair<_T1, _T2>> : true_type
    { };
  template<typename _Tp, std::size_t _Nm>
    struct __is_tuple_like_impl<array<_Tp, _Nm>> : true_type
    { };
  template<typename _Tp>
    struct __is_tuple_like
    : public __is_tuple_like_impl<typename std::remove_cv
            <typename std::remove_reference<_Tp>::type>::type>::type
    { };
  template<std::size_t, typename, typename, std::size_t>
    struct __make_tuple_impl;
  template<std::size_t _Idx, typename _Tuple, typename... _Tp,
           std::size_t _Nm>
    struct __make_tuple_impl<_Idx, tuple<_Tp...>, _Tuple, _Nm>
    {
      typedef typename __make_tuple_impl<_Idx + 1, tuple<_Tp...,
 typename std::tuple_element<_Idx, _Tuple>::type>, _Tuple, _Nm>::__type
      __type;
    };
  template<std::size_t _Nm, typename _Tuple, typename... _Tp>
    struct __make_tuple_impl<_Nm, tuple<_Tp...>, _Tuple, _Nm>
    {
      typedef tuple<_Tp...> __type;
    };
  template<typename _Tuple>
    struct __do_make_tuple
    : public __make_tuple_impl<0, tuple<>, _Tuple,
                               std::tuple_size<_Tuple>::value>
    { };
  template<typename _Tuple>
    struct __make_tuple
    : public __do_make_tuple<typename std::remove_cv
            <typename std::remove_reference<_Tuple>::type>::type>
    { };
  template<typename...>
    struct __combine_tuples;
  template<>
    struct __combine_tuples<>
    {
      typedef tuple<> __type;
    };
  template<typename... _Ts>
    struct __combine_tuples<tuple<_Ts...>>
    {
      typedef tuple<_Ts...> __type;
    };
  template<typename... _T1s, typename... _T2s, typename... _Rem>
    struct __combine_tuples<tuple<_T1s...>, tuple<_T2s...>, _Rem...>
    {
      typedef typename __combine_tuples<tuple<_T1s..., _T2s...>,
     _Rem...>::__type __type;
    };
  template<typename... _Tpls>
    struct __tuple_cat_result
    {
      typedef typename __combine_tuples
        <typename __make_tuple<_Tpls>::__type...>::__type __type;
    };
  template<typename...>
    struct __make_1st_indices;
  template<>
    struct __make_1st_indices<>
    {
      typedef std::_Index_tuple<> __type;
    };
  template<typename _Tp, typename... _Tpls>
    struct __make_1st_indices<_Tp, _Tpls...>
    {
      typedef typename std::_Build_index_tuple<std::tuple_size<
 typename std::remove_reference<_Tp>::type>::value>::__type __type;
    };
  template<typename _Ret, typename _Indices, typename... _Tpls>
    struct __tuple_concater;
  template<typename _Ret, std::size_t... _Is, typename _Tp, typename... _Tpls>
    struct __tuple_concater<_Ret, std::_Index_tuple<_Is...>, _Tp, _Tpls...>
    {
      template<typename... _Us>
        static constexpr _Ret
        _S_do(_Tp&& __tp, _Tpls&&... __tps, _Us&&... __us)
        {
   typedef typename __make_1st_indices<_Tpls...>::__type __idx;
   typedef __tuple_concater<_Ret, __idx, _Tpls...> __next;
   return __next::_S_do(std::forward<_Tpls>(__tps)...,
          std::forward<_Us>(__us)...,
          std::get<_Is>(std::forward<_Tp>(__tp))...);
 }
    };
  template<typename _Ret>
    struct __tuple_concater<_Ret, std::_Index_tuple<>>
    {
      template<typename... _Us>
 static constexpr _Ret
 _S_do(_Us&&... __us)
        {
   return _Ret(std::forward<_Us>(__us)...);
 }
    };
  template<typename... _Tpls, typename = typename
           enable_if<__and_<__is_tuple_like<_Tpls>...>::value>::type>
    constexpr auto
    tuple_cat(_Tpls&&... __tpls)
    -> typename __tuple_cat_result<_Tpls...>::__type
    {
      typedef typename __tuple_cat_result<_Tpls...>::__type __ret;
      typedef typename __make_1st_indices<_Tpls...>::__type __idx;
      typedef __tuple_concater<__ret, __idx, _Tpls...> __concater;
      return __concater::_S_do(std::forward<_Tpls>(__tpls)...);
    }
  template<typename... _Elements>
    inline tuple<_Elements&...>
    tie(_Elements&... __args) noexcept
    { return tuple<_Elements&...>(__args...); }
  template<typename... _Elements>
    inline void
    swap(tuple<_Elements...>& __x, tuple<_Elements...>& __y)
    noexcept(noexcept(__x.swap(__y)))
    { __x.swap(__y); }
  struct _Swallow_assign
  {
    template<class _Tp>
      const _Swallow_assign&
      operator=(const _Tp&) const
      { return *this; }
  };
  const _Swallow_assign ignore{};
  template<typename... _Types, typename _Alloc>
    struct uses_allocator<tuple<_Types...>, _Alloc> : true_type { };
  template<class _T1, class _T2>
    template<typename... _Args1, typename... _Args2>
      inline
      pair<_T1, _T2>::
      pair(piecewise_construct_t,
    tuple<_Args1...> __first, tuple<_Args2...> __second)
      : pair(__first, __second,
      typename _Build_index_tuple<sizeof...(_Args1)>::__type(),
      typename _Build_index_tuple<sizeof...(_Args2)>::__type())
      { }
  template<class _T1, class _T2>
    template<typename... _Args1, std::size_t... _Indexes1,
             typename... _Args2, std::size_t... _Indexes2>
      inline
      pair<_T1, _T2>::
      pair(tuple<_Args1...>& __tuple1, tuple<_Args2...>& __tuple2,
    _Index_tuple<_Indexes1...>, _Index_tuple<_Indexes2...>)
      : first(std::forward<_Args1>(std::get<_Indexes1>(__tuple1))...),
        second(std::forward<_Args2>(std::get<_Indexes2>(__tuple2))...)
      { }

}
namespace std __attribute__ ((__visibility__ ("default")))
{

  template<typename _MemberPointer>
    class _Mem_fn;
  template<typename _Tp, typename _Class>
    _Mem_fn<_Tp _Class::*>
    mem_fn(_Tp _Class::*) noexcept;
template<typename _Tp> class __has_result_type_helper { template<typename _Up> struct _Wrap_type { }; template<typename _Up> static true_type __test(_Wrap_type<typename _Up::result_type>*); template<typename _Up> static false_type __test(...); public: typedef decltype(__test<_Tp>(0)) type; }; template<typename _Tp> struct __has_result_type : public __has_result_type_helper <typename remove_cv<_Tp>::type>::type { };
  template<bool _Has_result_type, typename _Functor>
    struct _Maybe_get_result_type
    { };
  template<typename _Functor>
    struct _Maybe_get_result_type<true, _Functor>
    { typedef typename _Functor::result_type result_type; };
  template<typename _Functor>
    struct _Weak_result_type_impl
    : _Maybe_get_result_type<__has_result_type<_Functor>::value, _Functor>
    { };
  template<typename _Res, typename... _ArgTypes>
    struct _Weak_result_type_impl<_Res(_ArgTypes...)>
    { typedef _Res result_type; };
  template<typename _Res, typename... _ArgTypes>
    struct _Weak_result_type_impl<_Res(_ArgTypes......)>
    { typedef _Res result_type; };
  template<typename _Res, typename... _ArgTypes>
    struct _Weak_result_type_impl<_Res(_ArgTypes...) const>
    { typedef _Res result_type; };
  template<typename _Res, typename... _ArgTypes>
    struct _Weak_result_type_impl<_Res(_ArgTypes......) const>
    { typedef _Res result_type; };
  template<typename _Res, typename... _ArgTypes>
    struct _Weak_result_type_impl<_Res(_ArgTypes...) volatile>
    { typedef _Res result_type; };
  template<typename _Res, typename... _ArgTypes>
    struct _Weak_result_type_impl<_Res(_ArgTypes......) volatile>
    { typedef _Res result_type; };
  template<typename _Res, typename... _ArgTypes>
    struct _Weak_result_type_impl<_Res(_ArgTypes...) const volatile>
    { typedef _Res result_type; };
  template<typename _Res, typename... _ArgTypes>
    struct _Weak_result_type_impl<_Res(_ArgTypes......) const volatile>
    { typedef _Res result_type; };
  template<typename _Res, typename... _ArgTypes>
    struct _Weak_result_type_impl<_Res(&)(_ArgTypes...)>
    { typedef _Res result_type; };
  template<typename _Res, typename... _ArgTypes>
    struct _Weak_result_type_impl<_Res(&)(_ArgTypes......)>
    { typedef _Res result_type; };
  template<typename _Res, typename... _ArgTypes>
    struct _Weak_result_type_impl<_Res(*)(_ArgTypes...)>
    { typedef _Res result_type; };
  template<typename _Res, typename... _ArgTypes>
    struct _Weak_result_type_impl<_Res(*)(_ArgTypes......)>
    { typedef _Res result_type; };
  template<typename _Res, typename _Class, typename... _ArgTypes>
    struct _Weak_result_type_impl<_Res (_Class::*)(_ArgTypes...)>
    { typedef _Res result_type; };
  template<typename _Res, typename _Class, typename... _ArgTypes>
    struct _Weak_result_type_impl<_Res (_Class::*)(_ArgTypes......)>
    { typedef _Res result_type; };
  template<typename _Res, typename _Class, typename... _ArgTypes>
    struct _Weak_result_type_impl<_Res (_Class::*)(_ArgTypes...) const>
    { typedef _Res result_type; };
  template<typename _Res, typename _Class, typename... _ArgTypes>
    struct _Weak_result_type_impl<_Res (_Class::*)(_ArgTypes......) const>
    { typedef _Res result_type; };
  template<typename _Res, typename _Class, typename... _ArgTypes>
    struct _Weak_result_type_impl<_Res (_Class::*)(_ArgTypes...) volatile>
    { typedef _Res result_type; };
  template<typename _Res, typename _Class, typename... _ArgTypes>
    struct _Weak_result_type_impl<_Res (_Class::*)(_ArgTypes......) volatile>
    { typedef _Res result_type; };
  template<typename _Res, typename _Class, typename... _ArgTypes>
    struct _Weak_result_type_impl<_Res (_Class::*)(_ArgTypes...)
      const volatile>
    { typedef _Res result_type; };
  template<typename _Res, typename _Class, typename... _ArgTypes>
    struct _Weak_result_type_impl<_Res (_Class::*)(_ArgTypes......)
      const volatile>
    { typedef _Res result_type; };
  template<typename _Functor>
    struct _Weak_result_type
    : _Weak_result_type_impl<typename remove_cv<_Functor>::type>
    { };
  template<typename _Functor, typename... _Args>
    inline
    typename enable_if<
      (!is_member_pointer<_Functor>::value
       && !is_function<_Functor>::value
       && !is_function<typename remove_pointer<_Functor>::type>::value),
      typename result_of<_Functor&(_Args&&...)>::type
    >::type
    __invoke(_Functor& __f, _Args&&... __args)
    {
      return __f(std::forward<_Args>(__args)...);
    }
  template<typename _Functor, typename... _Args>
    inline
    typename enable_if<
             (is_member_pointer<_Functor>::value
              && !is_function<_Functor>::value
              && !is_function<typename remove_pointer<_Functor>::type>::value),
             typename result_of<_Functor(_Args&&...)>::type
           >::type
    __invoke(_Functor& __f, _Args&&... __args)
    {
      return std::mem_fn(__f)(std::forward<_Args>(__args)...);
    }
  template<typename _Functor, typename... _Args>
    inline
    typename enable_if<
      (is_pointer<_Functor>::value
       && is_function<typename remove_pointer<_Functor>::type>::value),
      typename result_of<_Functor(_Args&&...)>::type
    >::type
    __invoke(_Functor __f, _Args&&... __args)
    {
      return __f(std::forward<_Args>(__args)...);
    }
  template<bool _Unary, bool _Binary, typename _Tp>
    struct _Reference_wrapper_base_impl;
  template<typename _Tp>
    struct _Reference_wrapper_base_impl<false, false, _Tp>
    : _Weak_result_type<_Tp>
    { };
  template<typename _Tp>
    struct _Reference_wrapper_base_impl<true, false, _Tp>
    : _Weak_result_type<_Tp>
    {
      typedef typename _Tp::argument_type argument_type;
    };
  template<typename _Tp>
    struct _Reference_wrapper_base_impl<false, true, _Tp>
    : _Weak_result_type<_Tp>
    {
      typedef typename _Tp::first_argument_type first_argument_type;
      typedef typename _Tp::second_argument_type second_argument_type;
    };
   template<typename _Tp>
    struct _Reference_wrapper_base_impl<true, true, _Tp>
    : _Weak_result_type<_Tp>
    {
      typedef typename _Tp::argument_type argument_type;
      typedef typename _Tp::first_argument_type first_argument_type;
      typedef typename _Tp::second_argument_type second_argument_type;
    };
  template<typename _Tp> class __has_argument_type_helper { template<typename _Up> struct _Wrap_type { }; template<typename _Up> static true_type __test(_Wrap_type<typename _Up::argument_type>*); template<typename _Up> static false_type __test(...); public: typedef decltype(__test<_Tp>(0)) type; }; template<typename _Tp> struct __has_argument_type : public __has_argument_type_helper <typename remove_cv<_Tp>::type>::type { };
  template<typename _Tp> class __has_first_argument_type_helper { template<typename _Up> struct _Wrap_type { }; template<typename _Up> static true_type __test(_Wrap_type<typename _Up::first_argument_type>*); template<typename _Up> static false_type __test(...); public: typedef decltype(__test<_Tp>(0)) type; }; template<typename _Tp> struct __has_first_argument_type : public __has_first_argument_type_helper <typename remove_cv<_Tp>::type>::type { };
  template<typename _Tp> class __has_second_argument_type_helper { template<typename _Up> struct _Wrap_type { }; template<typename _Up> static true_type __test(_Wrap_type<typename _Up::second_argument_type>*); template<typename _Up> static false_type __test(...); public: typedef decltype(__test<_Tp>(0)) type; }; template<typename _Tp> struct __has_second_argument_type : public __has_second_argument_type_helper <typename remove_cv<_Tp>::type>::type { };
  template<typename _Tp>
    struct _Reference_wrapper_base
    : _Reference_wrapper_base_impl<
      __has_argument_type<_Tp>::value,
      __has_first_argument_type<_Tp>::value
      && __has_second_argument_type<_Tp>::value,
      _Tp>
    { };
  template<typename _Res, typename _T1>
    struct _Reference_wrapper_base<_Res(_T1)>
    : unary_function<_T1, _Res>
    { };
  template<typename _Res, typename _T1>
    struct _Reference_wrapper_base<_Res(_T1) const>
    : unary_function<_T1, _Res>
    { };
  template<typename _Res, typename _T1>
    struct _Reference_wrapper_base<_Res(_T1) volatile>
    : unary_function<_T1, _Res>
    { };
  template<typename _Res, typename _T1>
    struct _Reference_wrapper_base<_Res(_T1) const volatile>
    : unary_function<_T1, _Res>
    { };
  template<typename _Res, typename _T1, typename _T2>
    struct _Reference_wrapper_base<_Res(_T1, _T2)>
    : binary_function<_T1, _T2, _Res>
    { };
  template<typename _Res, typename _T1, typename _T2>
    struct _Reference_wrapper_base<_Res(_T1, _T2) const>
    : binary_function<_T1, _T2, _Res>
    { };
  template<typename _Res, typename _T1, typename _T2>
    struct _Reference_wrapper_base<_Res(_T1, _T2) volatile>
    : binary_function<_T1, _T2, _Res>
    { };
  template<typename _Res, typename _T1, typename _T2>
    struct _Reference_wrapper_base<_Res(_T1, _T2) const volatile>
    : binary_function<_T1, _T2, _Res>
    { };
  template<typename _Res, typename _T1>
    struct _Reference_wrapper_base<_Res(*)(_T1)>
    : unary_function<_T1, _Res>
    { };
  template<typename _Res, typename _T1, typename _T2>
    struct _Reference_wrapper_base<_Res(*)(_T1, _T2)>
    : binary_function<_T1, _T2, _Res>
    { };
  template<typename _Res, typename _T1>
    struct _Reference_wrapper_base<_Res (_T1::*)()>
    : unary_function<_T1*, _Res>
    { };
  template<typename _Res, typename _T1, typename _T2>
    struct _Reference_wrapper_base<_Res (_T1::*)(_T2)>
    : binary_function<_T1*, _T2, _Res>
    { };
  template<typename _Res, typename _T1>
    struct _Reference_wrapper_base<_Res (_T1::*)() const>
    : unary_function<const _T1*, _Res>
    { };
  template<typename _Res, typename _T1, typename _T2>
    struct _Reference_wrapper_base<_Res (_T1::*)(_T2) const>
    : binary_function<const _T1*, _T2, _Res>
    { };
  template<typename _Res, typename _T1>
    struct _Reference_wrapper_base<_Res (_T1::*)() volatile>
    : unary_function<volatile _T1*, _Res>
    { };
  template<typename _Res, typename _T1, typename _T2>
    struct _Reference_wrapper_base<_Res (_T1::*)(_T2) volatile>
    : binary_function<volatile _T1*, _T2, _Res>
    { };
  template<typename _Res, typename _T1>
    struct _Reference_wrapper_base<_Res (_T1::*)() const volatile>
    : unary_function<const volatile _T1*, _Res>
    { };
  template<typename _Res, typename _T1, typename _T2>
    struct _Reference_wrapper_base<_Res (_T1::*)(_T2) const volatile>
    : binary_function<const volatile _T1*, _T2, _Res>
    { };
  template<typename _Tp>
    class reference_wrapper
    : public _Reference_wrapper_base<typename remove_cv<_Tp>::type>
    {
      _Tp* _M_data;
    public:
      typedef _Tp type;
      reference_wrapper(_Tp& __indata) noexcept
      : _M_data(std::__addressof(__indata))
      { }
      reference_wrapper(_Tp&&) = delete;
      reference_wrapper(const reference_wrapper<_Tp>& __inref) noexcept
      : _M_data(__inref._M_data)
      { }
      reference_wrapper&
      operator=(const reference_wrapper<_Tp>& __inref) noexcept
      {
 _M_data = __inref._M_data;
 return *this;
      }
      operator _Tp&() const noexcept
      { return this->get(); }
      _Tp&
      get() const noexcept
      { return *_M_data; }
      template<typename... _Args>
 typename result_of<_Tp&(_Args&&...)>::type
 operator()(_Args&&... __args) const
 {
   return __invoke(get(), std::forward<_Args>(__args)...);
 }
    };
  template<typename _Tp>
    inline reference_wrapper<_Tp>
    ref(_Tp& __t) noexcept
    { return reference_wrapper<_Tp>(__t); }
  template<typename _Tp>
    inline reference_wrapper<const _Tp>
    cref(const _Tp& __t) noexcept
    { return reference_wrapper<const _Tp>(__t); }
  template<typename _Tp>
    void ref(const _Tp&&) = delete;
  template<typename _Tp>
    void cref(const _Tp&&) = delete;
  template<typename _Tp>
    inline reference_wrapper<_Tp>
    ref(reference_wrapper<_Tp> __t) noexcept
    { return ref(__t.get()); }
  template<typename _Tp>
    inline reference_wrapper<const _Tp>
    cref(reference_wrapper<_Tp> __t) noexcept
    { return cref(__t.get()); }
  template<typename... _Types>
    struct _Pack : integral_constant<size_t, sizeof...(_Types)>
    { };
  template<typename _From, typename _To, bool = _From::value == _To::value>
    struct _AllConvertible : false_type
    { };
  template<typename... _From, typename... _To>
    struct _AllConvertible<_Pack<_From...>, _Pack<_To...>, true>
    : __and_<is_convertible<_From, _To>...>
    { };
  template<typename _Tp1, typename _Tp2>
    using _NotSame = __not_<is_same<typename std::decay<_Tp1>::type,
        typename std::decay<_Tp2>::type>>;
  template<typename _Res, typename... _ArgTypes>
    struct _Maybe_unary_or_binary_function { };
  template<typename _Res, typename _T1>
    struct _Maybe_unary_or_binary_function<_Res, _T1>
    : std::unary_function<_T1, _Res> { };
  template<typename _Res, typename _T1, typename _T2>
    struct _Maybe_unary_or_binary_function<_Res, _T1, _T2>
    : std::binary_function<_T1, _T2, _Res> { };
  template<typename _Res, typename _Class, typename... _ArgTypes>
    class _Mem_fn<_Res (_Class::*)(_ArgTypes...)>
    : public _Maybe_unary_or_binary_function<_Res, _Class*, _ArgTypes...>
    {
      typedef _Res (_Class::*_Functor)(_ArgTypes...);
      template<typename _Tp, typename... _Args>
 _Res
 _M_call(_Tp&& __object, const volatile _Class *,
  _Args&&... __args) const
 {
   return (std::forward<_Tp>(__object).*__pmf)
     (std::forward<_Args>(__args)...);
 }
      template<typename _Tp, typename... _Args>
 _Res
 _M_call(_Tp&& __ptr, const volatile void *, _Args&&... __args) const
 { return ((*__ptr).*__pmf)(std::forward<_Args>(__args)...); }
      template<typename... _Args>
 using _RequireValidArgs
   = _Require<_AllConvertible<_Pack<_Args...>, _Pack<_ArgTypes...>>>;
      template<typename _Tp, typename... _Args>
 using _RequireValidArgs2
   = _Require<_NotSame<_Class, _Tp>, _NotSame<_Class*, _Tp>,
       _AllConvertible<_Pack<_Args...>, _Pack<_ArgTypes...>>>;
      template<typename _Tp, typename... _Args>
 using _RequireValidArgs3
   = _Require<is_base_of<_Class, _Tp>,
       _AllConvertible<_Pack<_Args...>, _Pack<_ArgTypes...>>>;
    public:
      typedef _Res result_type;
      explicit _Mem_fn(_Functor __pmf) : __pmf(__pmf) { }
      template<typename... _Args, typename _Req = _RequireValidArgs<_Args...>>
 _Res
 operator()(_Class& __object, _Args&&... __args) const
 { return (__object.*__pmf)(std::forward<_Args>(__args)...); }
      template<typename... _Args, typename _Req = _RequireValidArgs<_Args...>>
 _Res
 operator()(_Class&& __object, _Args&&... __args) const
 {
   return (std::move(__object).*__pmf)(std::forward<_Args>(__args)...);
 }
      template<typename... _Args, typename _Req = _RequireValidArgs<_Args...>>
 _Res
 operator()(_Class* __object, _Args&&... __args) const
 { return (__object->*__pmf)(std::forward<_Args>(__args)...); }
      template<typename _Tp, typename... _Args,
        typename _Req = _RequireValidArgs2<_Tp, _Args...>>
 _Res
 operator()(_Tp&& __object, _Args&&... __args) const
 {
   return _M_call(std::forward<_Tp>(__object), &__object,
       std::forward<_Args>(__args)...);
 }
      template<typename _Tp, typename... _Args,
        typename _Req = _RequireValidArgs3<_Tp, _Args...>>
 _Res
 operator()(reference_wrapper<_Tp> __ref, _Args&&... __args) const
 { return operator()(__ref.get(), std::forward<_Args>(__args)...); }
    private:
      _Functor __pmf;
    };
  template<typename _Res, typename _Class, typename... _ArgTypes>
    class _Mem_fn<_Res (_Class::*)(_ArgTypes...) const>
    : public _Maybe_unary_or_binary_function<_Res, const _Class*,
          _ArgTypes...>
    {
      typedef _Res (_Class::*_Functor)(_ArgTypes...) const;
      template<typename _Tp, typename... _Args>
 _Res
 _M_call(_Tp&& __object, const volatile _Class *,
  _Args&&... __args) const
 {
   return (std::forward<_Tp>(__object).*__pmf)
     (std::forward<_Args>(__args)...);
 }
      template<typename _Tp, typename... _Args>
 _Res
 _M_call(_Tp&& __ptr, const volatile void *, _Args&&... __args) const
 { return ((*__ptr).*__pmf)(std::forward<_Args>(__args)...); }
      template<typename... _Args>
 using _RequireValidArgs
   = _Require<_AllConvertible<_Pack<_Args...>, _Pack<_ArgTypes...>>>;
      template<typename _Tp, typename... _Args>
 using _RequireValidArgs2
   = _Require<_NotSame<_Class, _Tp>, _NotSame<const _Class*, _Tp>,
       _AllConvertible<_Pack<_Args...>, _Pack<_ArgTypes...>>>;
      template<typename _Tp, typename... _Args>
 using _RequireValidArgs3
   = _Require<is_base_of<_Class, _Tp>,
       _AllConvertible<_Pack<_Args...>, _Pack<_ArgTypes...>>>;
    public:
      typedef _Res result_type;
      explicit _Mem_fn(_Functor __pmf) : __pmf(__pmf) { }
      template<typename... _Args, typename _Req = _RequireValidArgs<_Args...>>
 _Res
 operator()(const _Class& __object, _Args&&... __args) const
 { return (__object.*__pmf)(std::forward<_Args>(__args)...); }
      template<typename... _Args, typename _Req = _RequireValidArgs<_Args...>>
 _Res
 operator()(const _Class&& __object, _Args&&... __args) const
 {
   return (std::move(__object).*__pmf)(std::forward<_Args>(__args)...);
 }
      template<typename... _Args, typename _Req = _RequireValidArgs<_Args...>>
 _Res
 operator()(const _Class* __object, _Args&&... __args) const
 { return (__object->*__pmf)(std::forward<_Args>(__args)...); }
      template<typename _Tp, typename... _Args,
        typename _Req = _RequireValidArgs2<_Tp, _Args...>>
 _Res operator()(_Tp&& __object, _Args&&... __args) const
 {
   return _M_call(std::forward<_Tp>(__object), &__object,
       std::forward<_Args>(__args)...);
 }
      template<typename _Tp, typename... _Args,
        typename _Req = _RequireValidArgs3<_Tp, _Args...>>
 _Res
 operator()(reference_wrapper<_Tp> __ref, _Args&&... __args) const
 { return operator()(__ref.get(), std::forward<_Args>(__args)...); }
    private:
      _Functor __pmf;
    };
  template<typename _Res, typename _Class, typename... _ArgTypes>
    class _Mem_fn<_Res (_Class::*)(_ArgTypes...) volatile>
    : public _Maybe_unary_or_binary_function<_Res, volatile _Class*,
          _ArgTypes...>
    {
      typedef _Res (_Class::*_Functor)(_ArgTypes...) volatile;
      template<typename _Tp, typename... _Args>
 _Res
 _M_call(_Tp&& __object, const volatile _Class *,
  _Args&&... __args) const
 {
   return (std::forward<_Tp>(__object).*__pmf)
     (std::forward<_Args>(__args)...);
 }
      template<typename _Tp, typename... _Args>
 _Res
 _M_call(_Tp&& __ptr, const volatile void *, _Args&&... __args) const
 { return ((*__ptr).*__pmf)(std::forward<_Args>(__args)...); }
      template<typename... _Args>
 using _RequireValidArgs
   = _Require<_AllConvertible<_Pack<_Args...>, _Pack<_ArgTypes...>>>;
      template<typename _Tp, typename... _Args>
 using _RequireValidArgs2
   = _Require<_NotSame<_Class, _Tp>, _NotSame<volatile _Class*, _Tp>,
       _AllConvertible<_Pack<_Args...>, _Pack<_ArgTypes...>>>;
      template<typename _Tp, typename... _Args>
 using _RequireValidArgs3
   = _Require<is_base_of<_Class, _Tp>,
       _AllConvertible<_Pack<_Args...>, _Pack<_ArgTypes...>>>;
    public:
      typedef _Res result_type;
      explicit _Mem_fn(_Functor __pmf) : __pmf(__pmf) { }
      template<typename... _Args, typename _Req = _RequireValidArgs<_Args...>>
 _Res
 operator()(volatile _Class& __object, _Args&&... __args) const
 { return (__object.*__pmf)(std::forward<_Args>(__args)...); }
      template<typename... _Args, typename _Req = _RequireValidArgs<_Args...>>
 _Res
 operator()(volatile _Class&& __object, _Args&&... __args) const
 {
   return (std::move(__object).*__pmf)(std::forward<_Args>(__args)...);
 }
      template<typename... _Args, typename _Req = _RequireValidArgs<_Args...>>
 _Res
 operator()(volatile _Class* __object, _Args&&... __args) const
 { return (__object->*__pmf)(std::forward<_Args>(__args)...); }
      template<typename _Tp, typename... _Args,
        typename _Req = _RequireValidArgs2<_Tp, _Args...>>
 _Res
 operator()(_Tp&& __object, _Args&&... __args) const
 {
   return _M_call(std::forward<_Tp>(__object), &__object,
       std::forward<_Args>(__args)...);
 }
      template<typename _Tp, typename... _Args,
        typename _Req = _RequireValidArgs3<_Tp, _Args...>>
 _Res
 operator()(reference_wrapper<_Tp> __ref, _Args&&... __args) const
 { return operator()(__ref.get(), std::forward<_Args>(__args)...); }
    private:
      _Functor __pmf;
    };
  template<typename _Res, typename _Class, typename... _ArgTypes>
    class _Mem_fn<_Res (_Class::*)(_ArgTypes...) const volatile>
    : public _Maybe_unary_or_binary_function<_Res, const volatile _Class*,
          _ArgTypes...>
    {
      typedef _Res (_Class::*_Functor)(_ArgTypes...) const volatile;
      template<typename _Tp, typename... _Args>
 _Res
 _M_call(_Tp&& __object, const volatile _Class *,
  _Args&&... __args) const
 {
   return (std::forward<_Tp>(__object).*__pmf)
     (std::forward<_Args>(__args)...);
 }
      template<typename _Tp, typename... _Args>
 _Res
 _M_call(_Tp&& __ptr, const volatile void *, _Args&&... __args) const
 { return ((*__ptr).*__pmf)(std::forward<_Args>(__args)...); }
      template<typename... _Args>
 using _RequireValidArgs
   = _Require<_AllConvertible<_Pack<_Args...>, _Pack<_ArgTypes...>>>;
      template<typename _Tp, typename... _Args>
 using _RequireValidArgs2
   = _Require<_NotSame<_Class, _Tp>,
       _NotSame<const volatile _Class*, _Tp>,
       _AllConvertible<_Pack<_Args...>, _Pack<_ArgTypes...>>>;
      template<typename _Tp, typename... _Args>
 using _RequireValidArgs3
   = _Require<is_base_of<_Class, _Tp>,
       _AllConvertible<_Pack<_Args...>, _Pack<_ArgTypes...>>>;
    public:
      typedef _Res result_type;
      explicit _Mem_fn(_Functor __pmf) : __pmf(__pmf) { }
      template<typename... _Args, typename _Req = _RequireValidArgs<_Args...>>
 _Res
 operator()(const volatile _Class& __object, _Args&&... __args) const
 { return (__object.*__pmf)(std::forward<_Args>(__args)...); }
      template<typename... _Args, typename _Req = _RequireValidArgs<_Args...>>
 _Res
 operator()(const volatile _Class&& __object, _Args&&... __args) const
 {
   return (std::move(__object).*__pmf)(std::forward<_Args>(__args)...);
 }
      template<typename... _Args, typename _Req = _RequireValidArgs<_Args...>>
 _Res
 operator()(const volatile _Class* __object, _Args&&... __args) const
 { return (__object->*__pmf)(std::forward<_Args>(__args)...); }
      template<typename _Tp, typename... _Args,
        typename _Req = _RequireValidArgs2<_Tp, _Args...>>
 _Res operator()(_Tp&& __object, _Args&&... __args) const
 {
   return _M_call(std::forward<_Tp>(__object), &__object,
       std::forward<_Args>(__args)...);
 }
      template<typename _Tp, typename... _Args,
        typename _Req = _RequireValidArgs3<_Tp, _Args...>>
 _Res
 operator()(reference_wrapper<_Tp> __ref, _Args&&... __args) const
 { return operator()(__ref.get(), std::forward<_Args>(__args)...); }
    private:
      _Functor __pmf;
    };
  template<typename _Tp, bool>
    struct _Mem_fn_const_or_non
    {
      typedef const _Tp& type;
    };
  template<typename _Tp>
    struct _Mem_fn_const_or_non<_Tp, false>
    {
      typedef _Tp& type;
    };
  template<typename _Res, typename _Class>
    class _Mem_fn<_Res _Class::*>
    {
      using __pm_type = _Res _Class::*;
      template<typename _Tp>
 auto
 _M_call(_Tp&& __object, const _Class *) const noexcept
 -> decltype(std::forward<_Tp>(__object).*std::declval<__pm_type&>())
 { return std::forward<_Tp>(__object).*__pm; }
      template<typename _Tp, typename _Up>
 auto
 _M_call(_Tp&& __object, _Up * const *) const noexcept
 -> decltype((*std::forward<_Tp>(__object)).*std::declval<__pm_type&>())
 { return (*std::forward<_Tp>(__object)).*__pm; }
      template<typename _Tp>
 auto
 _M_call(_Tp&& __ptr, const volatile void*) const
 noexcept(noexcept((*__ptr).*std::declval<__pm_type&>()))
 -> decltype((*__ptr).*std::declval<__pm_type&>())
 { return (*__ptr).*__pm; }
    public:
      explicit
      _Mem_fn(_Res _Class::*__pm) noexcept : __pm(__pm) { }
      _Res&
      operator()(_Class& __object) const noexcept
      { return __object.*__pm; }
      const _Res&
      operator()(const _Class& __object) const noexcept
      { return __object.*__pm; }
      _Res&&
      operator()(_Class&& __object) const noexcept
      { return std::forward<_Class>(__object).*__pm; }
      const _Res&&
      operator()(const _Class&& __object) const noexcept
      { return std::forward<const _Class>(__object).*__pm; }
      _Res&
      operator()(_Class* __object) const noexcept
      { return __object->*__pm; }
      const _Res&
      operator()(const _Class* __object) const noexcept
      { return __object->*__pm; }
      template<typename _Tp, typename _Req = _Require<_NotSame<_Class*, _Tp>>>
 auto
 operator()(_Tp&& __unknown) const
 noexcept(noexcept(std::declval<_Mem_fn*>()->_M_call
     (std::forward<_Tp>(__unknown), &__unknown)))
 -> decltype(this->_M_call(std::forward<_Tp>(__unknown), &__unknown))
 { return _M_call(std::forward<_Tp>(__unknown), &__unknown); }
      template<typename _Tp, typename _Req = _Require<is_base_of<_Class, _Tp>>>
 auto
 operator()(reference_wrapper<_Tp> __ref) const
 noexcept(noexcept(std::declval<_Mem_fn&>()(__ref.get())))
 -> decltype((*this)(__ref.get()))
 { return (*this)(__ref.get()); }
    private:
      _Res _Class::*__pm;
    };
  template<typename _Tp, typename _Class>
    inline _Mem_fn<_Tp _Class::*>
    mem_fn(_Tp _Class::* __pm) noexcept
    {
      return _Mem_fn<_Tp _Class::*>(__pm);
    }
  template<typename _Tp>
    struct is_bind_expression
    : public false_type { };
  template<typename _Tp>
    struct is_placeholder
    : public integral_constant<int, 0>
    { };
  template<int _Num> struct _Placeholder { };
 
  namespace placeholders
  {
 
    extern const _Placeholder<1> _1;
    extern const _Placeholder<2> _2;
    extern const _Placeholder<3> _3;
    extern const _Placeholder<4> _4;
    extern const _Placeholder<5> _5;
    extern const _Placeholder<6> _6;
    extern const _Placeholder<7> _7;
    extern const _Placeholder<8> _8;
    extern const _Placeholder<9> _9;
    extern const _Placeholder<10> _10;
    extern const _Placeholder<11> _11;
    extern const _Placeholder<12> _12;
    extern const _Placeholder<13> _13;
    extern const _Placeholder<14> _14;
    extern const _Placeholder<15> _15;
    extern const _Placeholder<16> _16;
    extern const _Placeholder<17> _17;
    extern const _Placeholder<18> _18;
    extern const _Placeholder<19> _19;
    extern const _Placeholder<20> _20;
    extern const _Placeholder<21> _21;
    extern const _Placeholder<22> _22;
    extern const _Placeholder<23> _23;
    extern const _Placeholder<24> _24;
    extern const _Placeholder<25> _25;
    extern const _Placeholder<26> _26;
    extern const _Placeholder<27> _27;
    extern const _Placeholder<28> _28;
    extern const _Placeholder<29> _29;
 
  }
 
  template<int _Num>
    struct is_placeholder<_Placeholder<_Num> >
    : public integral_constant<int, _Num>
    { };
  template<int _Num>
    struct is_placeholder<const _Placeholder<_Num> >
    : public integral_constant<int, _Num>
    { };
  struct _No_tuple_element;
  template<std::size_t __i, typename _Tuple, bool _IsSafe>
    struct _Safe_tuple_element_impl
    : tuple_element<__i, _Tuple> { };
  template<std::size_t __i, typename _Tuple>
    struct _Safe_tuple_element_impl<__i, _Tuple, false>
    {
      typedef _No_tuple_element type;
    };
 template<std::size_t __i, typename _Tuple>
   struct _Safe_tuple_element
   : _Safe_tuple_element_impl<__i, _Tuple,
         (__i < tuple_size<_Tuple>::value)>
   { };
  template<typename _Arg,
    bool _IsBindExp = is_bind_expression<_Arg>::value,
    bool _IsPlaceholder = (is_placeholder<_Arg>::value > 0)>
    class _Mu;
  template<typename _Tp>
    class _Mu<reference_wrapper<_Tp>, false, false>
    {
    public:
      typedef _Tp& result_type;
      template<typename _CVRef, typename _Tuple>
 result_type
 operator()(_CVRef& __arg, _Tuple&) const volatile
 { return __arg.get(); }
    };
  template<typename _Arg>
    class _Mu<_Arg, true, false>
    {
    public:
      template<typename _CVArg, typename... _Args>
 auto
 operator()(_CVArg& __arg,
     tuple<_Args...>& __tuple) const volatile
 -> decltype(__arg(declval<_Args>()...))
 {
   typedef typename _Build_index_tuple<sizeof...(_Args)>::__type
     _Indexes;
   return this->__call(__arg, __tuple, _Indexes());
 }
    private:
      template<typename _CVArg, typename... _Args, std::size_t... _Indexes>
 auto
 __call(_CVArg& __arg, tuple<_Args...>& __tuple,
        const _Index_tuple<_Indexes...>&) const volatile
 -> decltype(__arg(declval<_Args>()...))
 {
   return __arg(std::forward<_Args>(get<_Indexes>(__tuple))...);
 }
    };
  template<typename _Arg>
    class _Mu<_Arg, false, true>
    {
    public:
      template<typename _Signature> class result;
      template<typename _CVMu, typename _CVArg, typename _Tuple>
 class result<_CVMu(_CVArg, _Tuple)>
 {
   typedef typename _Safe_tuple_element<(is_placeholder<_Arg>::value
      - 1), _Tuple>::type
     __base_type;
 public:
   typedef typename add_rvalue_reference<__base_type>::type type;
 };
      template<typename _Tuple>
 typename result<_Mu(_Arg, _Tuple)>::type
 operator()(const volatile _Arg&, _Tuple& __tuple) const volatile
 {
   return std::forward<typename result<_Mu(_Arg, _Tuple)>::type>(
       ::std::get<(is_placeholder<_Arg>::value - 1)>(__tuple));
 }
    };
  template<typename _Arg>
    class _Mu<_Arg, false, false>
    {
    public:
      template<typename _Signature> struct result;
      template<typename _CVMu, typename _CVArg, typename _Tuple>
 struct result<_CVMu(_CVArg, _Tuple)>
 {
   typedef typename add_lvalue_reference<_CVArg>::type type;
 };
      template<typename _CVArg, typename _Tuple>
 _CVArg&&
 operator()(_CVArg&& __arg, _Tuple&) const volatile
 { return std::forward<_CVArg>(__arg); }
    };
  template<typename _Tp>
    struct _Maybe_wrap_member_pointer
    {
      typedef _Tp type;
      static const _Tp&
      __do_wrap(const _Tp& __x)
      { return __x; }
      static _Tp&&
      __do_wrap(_Tp&& __x)
      { return static_cast<_Tp&&>(__x); }
    };
  template<typename _Tp, typename _Class>
    struct _Maybe_wrap_member_pointer<_Tp _Class::*>
    {
      typedef _Mem_fn<_Tp _Class::*> type;
      static type
      __do_wrap(_Tp _Class::* __pm)
      { return type(__pm); }
    };
  template<>
    struct _Maybe_wrap_member_pointer<void>
    {
      typedef void type;
    };
  template<std::size_t _Ind, typename... _Tp>
    inline auto
    __volget(volatile tuple<_Tp...>& __tuple)
    -> typename tuple_element<_Ind, tuple<_Tp...>>::type volatile&
    { return std::get<_Ind>(const_cast<tuple<_Tp...>&>(__tuple)); }
  template<std::size_t _Ind, typename... _Tp>
    inline auto
    __volget(const volatile tuple<_Tp...>& __tuple)
    -> typename tuple_element<_Ind, tuple<_Tp...>>::type const volatile&
    { return std::get<_Ind>(const_cast<const tuple<_Tp...>&>(__tuple)); }
  template<typename _Signature>
    struct _Bind;
   template<typename _Functor, typename... _Bound_args>
    class _Bind<_Functor(_Bound_args...)>
    : public _Weak_result_type<_Functor>
    {
      typedef _Bind __self_type;
      typedef typename _Build_index_tuple<sizeof...(_Bound_args)>::__type
 _Bound_indexes;
      _Functor _M_f;
      tuple<_Bound_args...> _M_bound_args;
      template<typename _Result, typename... _Args, std::size_t... _Indexes>
 _Result
 __call(tuple<_Args...>&& __args, _Index_tuple<_Indexes...>)
 {
   return _M_f(_Mu<_Bound_args>()
        (get<_Indexes>(_M_bound_args), __args)...);
 }
      template<typename _Result, typename... _Args, std::size_t... _Indexes>
 _Result
 __call_c(tuple<_Args...>&& __args, _Index_tuple<_Indexes...>) const
 {
   return _M_f(_Mu<_Bound_args>()
        (get<_Indexes>(_M_bound_args), __args)...);
 }
      template<typename _Result, typename... _Args, std::size_t... _Indexes>
 _Result
 __call_v(tuple<_Args...>&& __args,
   _Index_tuple<_Indexes...>) volatile
 {
   return _M_f(_Mu<_Bound_args>()
        (__volget<_Indexes>(_M_bound_args), __args)...);
 }
      template<typename _Result, typename... _Args, std::size_t... _Indexes>
 _Result
 __call_c_v(tuple<_Args...>&& __args,
     _Index_tuple<_Indexes...>) const volatile
 {
   return _M_f(_Mu<_Bound_args>()
        (__volget<_Indexes>(_M_bound_args), __args)...);
 }
     public:
      template<typename... _Args>
 explicit _Bind(const _Functor& __f, _Args&&... __args)
 : _M_f(__f), _M_bound_args(std::forward<_Args>(__args)...)
 { }
      template<typename... _Args>
 explicit _Bind(_Functor&& __f, _Args&&... __args)
 : _M_f(std::move(__f)), _M_bound_args(std::forward<_Args>(__args)...)
 { }
      _Bind(const _Bind&) = default;
      _Bind(_Bind&& __b)
      : _M_f(std::move(__b._M_f)), _M_bound_args(std::move(__b._M_bound_args))
      { }
      template<typename... _Args, typename _Result
 = decltype( std::declval<_Functor>()(
       _Mu<_Bound_args>()( std::declval<_Bound_args&>(),
      std::declval<tuple<_Args...>&>() )... ) )>
 _Result
 operator()(_Args&&... __args)
 {
   return this->__call<_Result>(
       std::forward_as_tuple(std::forward<_Args>(__args)...),
       _Bound_indexes());
 }
      template<typename... _Args, typename _Result
 = decltype( std::declval<typename enable_if<(sizeof...(_Args) >= 0),
         typename add_const<_Functor>::type>::type>()(
       _Mu<_Bound_args>()( std::declval<const _Bound_args&>(),
      std::declval<tuple<_Args...>&>() )... ) )>
 _Result
 operator()(_Args&&... __args) const
 {
   return this->__call_c<_Result>(
       std::forward_as_tuple(std::forward<_Args>(__args)...),
       _Bound_indexes());
 }
      template<typename... _Args, typename _Result
 = decltype( std::declval<typename enable_if<(sizeof...(_Args) >= 0),
                       typename add_volatile<_Functor>::type>::type>()(
       _Mu<_Bound_args>()( std::declval<volatile _Bound_args&>(),
      std::declval<tuple<_Args...>&>() )... ) )>
 _Result
 operator()(_Args&&... __args) volatile
 {
   return this->__call_v<_Result>(
       std::forward_as_tuple(std::forward<_Args>(__args)...),
       _Bound_indexes());
 }
      template<typename... _Args, typename _Result
 = decltype( std::declval<typename enable_if<(sizeof...(_Args) >= 0),
                       typename add_cv<_Functor>::type>::type>()(
       _Mu<_Bound_args>()( std::declval<const volatile _Bound_args&>(),
      std::declval<tuple<_Args...>&>() )... ) )>
 _Result
 operator()(_Args&&... __args) const volatile
 {
   return this->__call_c_v<_Result>(
       std::forward_as_tuple(std::forward<_Args>(__args)...),
       _Bound_indexes());
 }
    };
  template<typename _Result, typename _Signature>
    struct _Bind_result;
  template<typename _Result, typename _Functor, typename... _Bound_args>
    class _Bind_result<_Result, _Functor(_Bound_args...)>
    {
      typedef _Bind_result __self_type;
      typedef typename _Build_index_tuple<sizeof...(_Bound_args)>::__type
 _Bound_indexes;
      _Functor _M_f;
      tuple<_Bound_args...> _M_bound_args;
      template<typename _Res>
 struct __enable_if_void : enable_if<is_void<_Res>::value, int> { };
      template<typename _Res>
 struct __disable_if_void : enable_if<!is_void<_Res>::value, int> { };
      template<typename _Res, typename... _Args, std::size_t... _Indexes>
 _Result
 __call(tuple<_Args...>&& __args, _Index_tuple<_Indexes...>,
     typename __disable_if_void<_Res>::type = 0)
 {
   return _M_f(_Mu<_Bound_args>()
        (get<_Indexes>(_M_bound_args), __args)...);
 }
      template<typename _Res, typename... _Args, std::size_t... _Indexes>
 void
 __call(tuple<_Args...>&& __args, _Index_tuple<_Indexes...>,
     typename __enable_if_void<_Res>::type = 0)
 {
   _M_f(_Mu<_Bound_args>()
        (get<_Indexes>(_M_bound_args), __args)...);
 }
      template<typename _Res, typename... _Args, std::size_t... _Indexes>
 _Result
 __call(tuple<_Args...>&& __args, _Index_tuple<_Indexes...>,
     typename __disable_if_void<_Res>::type = 0) const
 {
   return _M_f(_Mu<_Bound_args>()
        (get<_Indexes>(_M_bound_args), __args)...);
 }
      template<typename _Res, typename... _Args, std::size_t... _Indexes>
 void
 __call(tuple<_Args...>&& __args, _Index_tuple<_Indexes...>,
     typename __enable_if_void<_Res>::type = 0) const
 {
   _M_f(_Mu<_Bound_args>()
        (get<_Indexes>(_M_bound_args), __args)...);
 }
      template<typename _Res, typename... _Args, std::size_t... _Indexes>
 _Result
 __call(tuple<_Args...>&& __args, _Index_tuple<_Indexes...>,
     typename __disable_if_void<_Res>::type = 0) volatile
 {
   return _M_f(_Mu<_Bound_args>()
        (__volget<_Indexes>(_M_bound_args), __args)...);
 }
      template<typename _Res, typename... _Args, std::size_t... _Indexes>
 void
 __call(tuple<_Args...>&& __args, _Index_tuple<_Indexes...>,
     typename __enable_if_void<_Res>::type = 0) volatile
 {
   _M_f(_Mu<_Bound_args>()
        (__volget<_Indexes>(_M_bound_args), __args)...);
 }
      template<typename _Res, typename... _Args, std::size_t... _Indexes>
 _Result
 __call(tuple<_Args...>&& __args, _Index_tuple<_Indexes...>,
     typename __disable_if_void<_Res>::type = 0) const volatile
 {
   return _M_f(_Mu<_Bound_args>()
        (__volget<_Indexes>(_M_bound_args), __args)...);
 }
      template<typename _Res, typename... _Args, std::size_t... _Indexes>
 void
 __call(tuple<_Args...>&& __args,
        _Index_tuple<_Indexes...>,
     typename __enable_if_void<_Res>::type = 0) const volatile
 {
   _M_f(_Mu<_Bound_args>()
        (__volget<_Indexes>(_M_bound_args), __args)...);
 }
    public:
      typedef _Result result_type;
      template<typename... _Args>
 explicit _Bind_result(const _Functor& __f, _Args&&... __args)
 : _M_f(__f), _M_bound_args(std::forward<_Args>(__args)...)
 { }
      template<typename... _Args>
 explicit _Bind_result(_Functor&& __f, _Args&&... __args)
 : _M_f(std::move(__f)), _M_bound_args(std::forward<_Args>(__args)...)
 { }
      _Bind_result(const _Bind_result&) = default;
      _Bind_result(_Bind_result&& __b)
      : _M_f(std::move(__b._M_f)), _M_bound_args(std::move(__b._M_bound_args))
      { }
      template<typename... _Args>
 result_type
 operator()(_Args&&... __args)
 {
   return this->__call<_Result>(
       std::forward_as_tuple(std::forward<_Args>(__args)...),
       _Bound_indexes());
 }
      template<typename... _Args>
 result_type
 operator()(_Args&&... __args) const
 {
   return this->__call<_Result>(
       std::forward_as_tuple(std::forward<_Args>(__args)...),
       _Bound_indexes());
 }
      template<typename... _Args>
 result_type
 operator()(_Args&&... __args) volatile
 {
   return this->__call<_Result>(
       std::forward_as_tuple(std::forward<_Args>(__args)...),
       _Bound_indexes());
 }
      template<typename... _Args>
 result_type
 operator()(_Args&&... __args) const volatile
 {
   return this->__call<_Result>(
       std::forward_as_tuple(std::forward<_Args>(__args)...),
       _Bound_indexes());
 }
    };
  template<typename _Signature>
    struct is_bind_expression<_Bind<_Signature> >
    : public true_type { };
  template<typename _Signature>
    struct is_bind_expression<const _Bind<_Signature> >
    : public true_type { };
  template<typename _Signature>
    struct is_bind_expression<volatile _Bind<_Signature> >
    : public true_type { };
  template<typename _Signature>
    struct is_bind_expression<const volatile _Bind<_Signature>>
    : public true_type { };
  template<typename _Result, typename _Signature>
    struct is_bind_expression<_Bind_result<_Result, _Signature>>
    : public true_type { };
  template<typename _Result, typename _Signature>
    struct is_bind_expression<const _Bind_result<_Result, _Signature>>
    : public true_type { };
  template<typename _Result, typename _Signature>
    struct is_bind_expression<volatile _Bind_result<_Result, _Signature>>
    : public true_type { };
  template<typename _Result, typename _Signature>
    struct is_bind_expression<const volatile _Bind_result<_Result, _Signature>>
    : public true_type { };
  template<typename _Tp, typename _Tp2 = typename decay<_Tp>::type>
    using __is_socketlike = __or_<is_integral<_Tp2>, is_enum<_Tp2>>;
  template<bool _SocketLike, typename _Func, typename... _BoundArgs>
    struct _Bind_helper
    {
      typedef _Maybe_wrap_member_pointer<typename decay<_Func>::type>
 __maybe_type;
      typedef typename __maybe_type::type __func_type;
      typedef _Bind<__func_type(typename decay<_BoundArgs>::type...)> type;
    };
  template<typename _Func, typename... _BoundArgs>
    struct _Bind_helper<true, _Func, _BoundArgs...>
    { };
  template<typename _Func, typename... _BoundArgs>
    inline typename
    _Bind_helper<__is_socketlike<_Func>::value, _Func, _BoundArgs...>::type
    bind(_Func&& __f, _BoundArgs&&... __args)
    {
      typedef _Bind_helper<false, _Func, _BoundArgs...> __helper_type;
      typedef typename __helper_type::__maybe_type __maybe_type;
      typedef typename __helper_type::type __result_type;
      return __result_type(__maybe_type::__do_wrap(std::forward<_Func>(__f)),
      std::forward<_BoundArgs>(__args)...);
    }
  template<typename _Result, typename _Func, typename... _BoundArgs>
    struct _Bindres_helper
    {
      typedef _Maybe_wrap_member_pointer<typename decay<_Func>::type>
 __maybe_type;
      typedef typename __maybe_type::type __functor_type;
      typedef _Bind_result<_Result,
      __functor_type(typename decay<_BoundArgs>::type...)>
 type;
    };
  template<typename _Result, typename _Func, typename... _BoundArgs>
    inline
    typename _Bindres_helper<_Result, _Func, _BoundArgs...>::type
    bind(_Func&& __f, _BoundArgs&&... __args)
    {
      typedef _Bindres_helper<_Result, _Func, _BoundArgs...> __helper_type;
      typedef typename __helper_type::__maybe_type __maybe_type;
      typedef typename __helper_type::type __result_type;
      return __result_type(__maybe_type::__do_wrap(std::forward<_Func>(__f)),
      std::forward<_BoundArgs>(__args)...);
    }
  template<typename _Signature>
    struct _Bind_simple;
  template<typename _Callable, typename... _Args>
    struct _Bind_simple<_Callable(_Args...)>
    {
      typedef typename result_of<_Callable(_Args...)>::type result_type;
      template<typename... _Args2, typename = typename
               enable_if< sizeof...(_Args) == sizeof...(_Args2)>::type>
        explicit
        _Bind_simple(const _Callable& __callable, _Args2&&... __args)
        : _M_bound(__callable, std::forward<_Args2>(__args)...)
        { }
      template<typename... _Args2, typename = typename
               enable_if< sizeof...(_Args) == sizeof...(_Args2)>::type>
        explicit
        _Bind_simple(_Callable&& __callable, _Args2&&... __args)
        : _M_bound(std::move(__callable), std::forward<_Args2>(__args)...)
        { }
      _Bind_simple(const _Bind_simple&) = default;
      _Bind_simple(_Bind_simple&&) = default;
      result_type
      operator()()
      {
        typedef typename _Build_index_tuple<sizeof...(_Args)>::__type _Indices;
        return _M_invoke(_Indices());
      }
    private:
      template<std::size_t... _Indices>
        typename result_of<_Callable(_Args...)>::type
        _M_invoke(_Index_tuple<_Indices...>)
        {
          return std::forward<_Callable>(std::get<0>(_M_bound))(
              std::forward<_Args>(std::get<_Indices+1>(_M_bound))...);
        }
      std::tuple<_Callable, _Args...> _M_bound;
    };
  template<typename _Func, typename... _BoundArgs>
    struct _Bind_simple_helper
    {
      typedef _Maybe_wrap_member_pointer<typename decay<_Func>::type>
        __maybe_type;
      typedef typename __maybe_type::type __func_type;
      typedef _Bind_simple<__func_type(typename decay<_BoundArgs>::type...)>
        __type;
    };
  template<typename _Callable, typename... _Args>
    typename _Bind_simple_helper<_Callable, _Args...>::__type
    __bind_simple(_Callable&& __callable, _Args&&... __args)
    {
      typedef _Bind_simple_helper<_Callable, _Args...> __helper_type;
      typedef typename __helper_type::__maybe_type __maybe_type;
      typedef typename __helper_type::__type __result_type;
      return __result_type(
          __maybe_type::__do_wrap( std::forward<_Callable>(__callable)),
          std::forward<_Args>(__args)...);
    }
  class bad_function_call : public std::exception
  {
  public:
    virtual ~bad_function_call() noexcept;
    const char* what() const noexcept;
  };
  template<typename _Tp>
    struct __is_location_invariant
    : integral_constant<bool, (is_pointer<_Tp>::value
          || is_member_pointer<_Tp>::value)>
    { };
  class _Undefined_class;
  union _Nocopy_types
  {
    void* _M_object;
    const void* _M_const_object;
    void (*_M_function_pointer)();
    void (_Undefined_class::*_M_member_pointer)();
  };
  union _Any_data
  {
    void* _M_access() { return &_M_pod_data[0]; }
    const void* _M_access() const { return &_M_pod_data[0]; }
    template<typename _Tp>
      _Tp&
      _M_access()
      { return *static_cast<_Tp*>(_M_access()); }
    template<typename _Tp>
      const _Tp&
      _M_access() const
      { return *static_cast<const _Tp*>(_M_access()); }
    _Nocopy_types _M_unused;
    char _M_pod_data[sizeof(_Nocopy_types)];
  };
  enum _Manager_operation
  {
    __get_type_info,
    __get_functor_ptr,
    __clone_functor,
    __destroy_functor
  };
  template<typename _Tp>
    struct _Simple_type_wrapper
    {
      _Simple_type_wrapper(_Tp __value) : __value(__value) { }
      _Tp __value;
    };
  template<typename _Tp>
    struct __is_location_invariant<_Simple_type_wrapper<_Tp> >
    : __is_location_invariant<_Tp>
    { };
  template<typename _Functor>
    inline _Functor&
    __callable_functor(_Functor& __f)
    { return __f; }
  template<typename _Member, typename _Class>
    inline _Mem_fn<_Member _Class::*>
    __callable_functor(_Member _Class::* &__p)
    { return std::mem_fn(__p); }
  template<typename _Member, typename _Class>
    inline _Mem_fn<_Member _Class::*>
    __callable_functor(_Member _Class::* const &__p)
    { return std::mem_fn(__p); }
  template<typename _Member, typename _Class>
    inline _Mem_fn<_Member _Class::*>
    __callable_functor(_Member _Class::* volatile &__p)
    { return std::mem_fn(__p); }
  template<typename _Member, typename _Class>
    inline _Mem_fn<_Member _Class::*>
    __callable_functor(_Member _Class::* const volatile &__p)
    { return std::mem_fn(__p); }
  template<typename _Signature>
    class function;
  class _Function_base
  {
  public:
    static const std::size_t _M_max_size = sizeof(_Nocopy_types);
    static const std::size_t _M_max_align = __alignof__(_Nocopy_types);
    template<typename _Functor>
      class _Base_manager
      {
      protected:
 static const bool __stored_locally =
 (__is_location_invariant<_Functor>::value
  && sizeof(_Functor) <= _M_max_size
  && __alignof__(_Functor) <= _M_max_align
  && (_M_max_align % __alignof__(_Functor) == 0));
 typedef integral_constant<bool, __stored_locally> _Local_storage;
 static _Functor*
 _M_get_pointer(const _Any_data& __source)
 {
   const _Functor* __ptr =
     __stored_locally? std::__addressof(__source._M_access<_Functor>())
                                 : __source._M_access<_Functor*>();
   return const_cast<_Functor*>(__ptr);
 }
 static void
 _M_clone(_Any_data& __dest, const _Any_data& __source, true_type)
 {
   new (__dest._M_access()) _Functor(__source._M_access<_Functor>());
 }
 static void
 _M_clone(_Any_data& __dest, const _Any_data& __source, false_type)
 {
   __dest._M_access<_Functor*>() =
     new _Functor(*__source._M_access<_Functor*>());
 }
 static void
 _M_destroy(_Any_data& __victim, true_type)
 {
   __victim._M_access<_Functor>().~_Functor();
 }
 static void
 _M_destroy(_Any_data& __victim, false_type)
 {
   delete __victim._M_access<_Functor*>();
 }
      public:
 static bool
 _M_manager(_Any_data& __dest, const _Any_data& __source,
     _Manager_operation __op)
 {
   switch (__op)
     {
     case __get_type_info:
       __dest._M_access<const type_info*>() = &typeid(_Functor);
       break;
     case __get_functor_ptr:
       __dest._M_access<_Functor*>() = _M_get_pointer(__source);
       break;
     case __clone_functor:
       _M_clone(__dest, __source, _Local_storage());
       break;
     case __destroy_functor:
       _M_destroy(__dest, _Local_storage());
       break;
     }
   return false;
 }
 static void
 _M_init_functor(_Any_data& __functor, _Functor&& __f)
 { _M_init_functor(__functor, std::move(__f), _Local_storage()); }
 template<typename _Signature>
   static bool
   _M_not_empty_function(const function<_Signature>& __f)
   { return static_cast<bool>(__f); }
 template<typename _Tp>
   static bool
   _M_not_empty_function(_Tp* const& __fp)
   { return __fp; }
 template<typename _Class, typename _Tp>
   static bool
   _M_not_empty_function(_Tp _Class::* const& __mp)
   { return __mp; }
 template<typename _Tp>
   static bool
   _M_not_empty_function(const _Tp&)
   { return true; }
      private:
 static void
 _M_init_functor(_Any_data& __functor, _Functor&& __f, true_type)
 { new (__functor._M_access()) _Functor(std::move(__f)); }
 static void
 _M_init_functor(_Any_data& __functor, _Functor&& __f, false_type)
 { __functor._M_access<_Functor*>() = new _Functor(std::move(__f)); }
      };
    template<typename _Functor>
      class _Ref_manager : public _Base_manager<_Functor*>
      {
 typedef _Function_base::_Base_manager<_Functor*> _Base;
      public:
 static bool
 _M_manager(_Any_data& __dest, const _Any_data& __source,
     _Manager_operation __op)
 {
   switch (__op)
     {
     case __get_type_info:
       __dest._M_access<const type_info*>() = &typeid(_Functor);
       break;
     case __get_functor_ptr:
       __dest._M_access<_Functor*>() = *_Base::_M_get_pointer(__source);
       return is_const<_Functor>::value;
       break;
     default:
       _Base::_M_manager(__dest, __source, __op);
     }
   return false;
 }
 static void
 _M_init_functor(_Any_data& __functor, reference_wrapper<_Functor> __f)
 {
   _Base::_M_init_functor(__functor, std::__addressof(__f.get()));
 }
      };
    _Function_base() : _M_manager(0) { }
    ~_Function_base()
    {
      if (_M_manager)
 _M_manager(_M_functor, _M_functor, __destroy_functor);
    }
    bool _M_empty() const { return !_M_manager; }
    typedef bool (*_Manager_type)(_Any_data&, const _Any_data&,
      _Manager_operation);
    _Any_data _M_functor;
    _Manager_type _M_manager;
  };
  template<typename _Signature, typename _Functor>
    class _Function_handler;
  template<typename _Res, typename _Functor, typename... _ArgTypes>
    class _Function_handler<_Res(_ArgTypes...), _Functor>
    : public _Function_base::_Base_manager<_Functor>
    {
      typedef _Function_base::_Base_manager<_Functor> _Base;
    public:
      static _Res
      _M_invoke(const _Any_data& __functor, _ArgTypes... __args)
      {
 return (*_Base::_M_get_pointer(__functor))(
     std::forward<_ArgTypes>(__args)...);
      }
    };
  template<typename _Functor, typename... _ArgTypes>
    class _Function_handler<void(_ArgTypes...), _Functor>
    : public _Function_base::_Base_manager<_Functor>
    {
      typedef _Function_base::_Base_manager<_Functor> _Base;
     public:
      static void
      _M_invoke(const _Any_data& __functor, _ArgTypes... __args)
      {
 (*_Base::_M_get_pointer(__functor))(
     std::forward<_ArgTypes>(__args)...);
      }
    };
  template<typename _Res, typename _Functor, typename... _ArgTypes>
    class _Function_handler<_Res(_ArgTypes...), reference_wrapper<_Functor> >
    : public _Function_base::_Ref_manager<_Functor>
    {
      typedef _Function_base::_Ref_manager<_Functor> _Base;
     public:
      static _Res
      _M_invoke(const _Any_data& __functor, _ArgTypes... __args)
      {
 return __callable_functor(**_Base::_M_get_pointer(__functor))(
       std::forward<_ArgTypes>(__args)...);
      }
    };
  template<typename _Functor, typename... _ArgTypes>
    class _Function_handler<void(_ArgTypes...), reference_wrapper<_Functor> >
    : public _Function_base::_Ref_manager<_Functor>
    {
      typedef _Function_base::_Ref_manager<_Functor> _Base;
     public:
      static void
      _M_invoke(const _Any_data& __functor, _ArgTypes... __args)
      {
 __callable_functor(**_Base::_M_get_pointer(__functor))(
     std::forward<_ArgTypes>(__args)...);
      }
    };
  template<typename _Class, typename _Member, typename _Res,
    typename... _ArgTypes>
    class _Function_handler<_Res(_ArgTypes...), _Member _Class::*>
    : public _Function_handler<void(_ArgTypes...), _Member _Class::*>
    {
      typedef _Function_handler<void(_ArgTypes...), _Member _Class::*>
 _Base;
     public:
      static _Res
      _M_invoke(const _Any_data& __functor, _ArgTypes... __args)
      {
 return std::mem_fn(_Base::_M_get_pointer(__functor)->__value)(
     std::forward<_ArgTypes>(__args)...);
      }
    };
  template<typename _Class, typename _Member, typename... _ArgTypes>
    class _Function_handler<void(_ArgTypes...), _Member _Class::*>
    : public _Function_base::_Base_manager<
   _Simple_type_wrapper< _Member _Class::* > >
    {
      typedef _Member _Class::* _Functor;
      typedef _Simple_type_wrapper<_Functor> _Wrapper;
      typedef _Function_base::_Base_manager<_Wrapper> _Base;
    public:
      static bool
      _M_manager(_Any_data& __dest, const _Any_data& __source,
   _Manager_operation __op)
      {
 switch (__op)
   {
   case __get_type_info:
     __dest._M_access<const type_info*>() = &typeid(_Functor);
     break;
   case __get_functor_ptr:
     __dest._M_access<_Functor*>() =
       &_Base::_M_get_pointer(__source)->__value;
     break;
   default:
     _Base::_M_manager(__dest, __source, __op);
   }
 return false;
      }
      static void
      _M_invoke(const _Any_data& __functor, _ArgTypes... __args)
      {
 std::mem_fn(_Base::_M_get_pointer(__functor)->__value)(
     std::forward<_ArgTypes>(__args)...);
      }
    };
  template<typename _From, typename _To>
    using __check_func_return_type
      = __or_<is_void<_To>, is_convertible<_From, _To>>;
  template<typename _Res, typename... _ArgTypes>
    class function<_Res(_ArgTypes...)>
    : public _Maybe_unary_or_binary_function<_Res, _ArgTypes...>,
      private _Function_base
    {
      typedef _Res _Signature_type(_ArgTypes...);
      template<typename _Functor>
 using _Invoke = decltype(__callable_functor(std::declval<_Functor&>())
     (std::declval<_ArgTypes>()...) );
      template<typename _Tp>
 using _NotSelf = __not_<is_same<_Tp, function>>;
      template<typename _Functor>
 using _Callable
   = __and_<_NotSelf<_Functor>,
     __check_func_return_type<_Invoke<_Functor>, _Res>>;
      template<typename _Cond, typename _Tp>
 using _Requires = typename enable_if<_Cond::value, _Tp>::type;
    public:
      typedef _Res result_type;
      function() noexcept
      : _Function_base() { }
      function(nullptr_t) noexcept
      : _Function_base() { }
      function(const function& __x);
      function(function&& __x) : _Function_base()
      {
 __x.swap(*this);
      }
      template<typename _Functor,
        typename = _Requires<_Callable<_Functor>, void>>
 function(_Functor);
      function&
      operator=(const function& __x)
      {
 function(__x).swap(*this);
 return *this;
      }
      function&
      operator=(function&& __x)
      {
 function(std::move(__x)).swap(*this);
 return *this;
      }
      function&
      operator=(nullptr_t)
      {
 if (_M_manager)
   {
     _M_manager(_M_functor, _M_functor, __destroy_functor);
     _M_manager = 0;
     _M_invoker = 0;
   }
 return *this;
      }
      template<typename _Functor>
 _Requires<_Callable<typename decay<_Functor>::type>, function&>
 operator=(_Functor&& __f)
 {
   function(std::forward<_Functor>(__f)).swap(*this);
   return *this;
 }
      template<typename _Functor>
 function&
 operator=(reference_wrapper<_Functor> __f) noexcept
 {
   function(__f).swap(*this);
   return *this;
 }
      void swap(function& __x)
      {
 std::swap(_M_functor, __x._M_functor);
 std::swap(_M_manager, __x._M_manager);
 std::swap(_M_invoker, __x._M_invoker);
      }
      explicit operator bool() const noexcept
      { return !_M_empty(); }
      _Res operator()(_ArgTypes... __args) const;
      const type_info& target_type() const noexcept;
      template<typename _Functor> _Functor* target() noexcept;
      template<typename _Functor> const _Functor* target() const noexcept;
    private:
      typedef _Res (*_Invoker_type)(const _Any_data&, _ArgTypes...);
      _Invoker_type _M_invoker;
  };
  template<typename _Res, typename... _ArgTypes>
    function<_Res(_ArgTypes...)>::
    function(const function& __x)
    : _Function_base()
    {
      if (static_cast<bool>(__x))
 {
   _M_invoker = __x._M_invoker;
   _M_manager = __x._M_manager;
   __x._M_manager(_M_functor, __x._M_functor, __clone_functor);
 }
    }
  template<typename _Res, typename... _ArgTypes>
    template<typename _Functor, typename>
      function<_Res(_ArgTypes...)>::
      function(_Functor __f)
      : _Function_base()
      {
 typedef _Function_handler<_Signature_type, _Functor> _My_handler;
 if (_My_handler::_M_not_empty_function(__f))
   {
     _My_handler::_M_init_functor(_M_functor, std::move(__f));
     _M_invoker = &_My_handler::_M_invoke;
     _M_manager = &_My_handler::_M_manager;
   }
      }
  template<typename _Res, typename... _ArgTypes>
    _Res
    function<_Res(_ArgTypes...)>::
    operator()(_ArgTypes... __args) const
    {
      if (_M_empty())
 __throw_bad_function_call();
      return _M_invoker(_M_functor, std::forward<_ArgTypes>(__args)...);
    }
  template<typename _Res, typename... _ArgTypes>
    const type_info&
    function<_Res(_ArgTypes...)>::
    target_type() const noexcept
    {
      if (_M_manager)
 {
   _Any_data __typeinfo_result;
   _M_manager(__typeinfo_result, _M_functor, __get_type_info);
   return *__typeinfo_result._M_access<const type_info*>();
 }
      else
 return typeid(void);
    }
  template<typename _Res, typename... _ArgTypes>
    template<typename _Functor>
      _Functor*
      function<_Res(_ArgTypes...)>::
      target() noexcept
      {
 if (typeid(_Functor) == target_type() && _M_manager)
   {
     _Any_data __ptr;
     if (_M_manager(__ptr, _M_functor, __get_functor_ptr)
  && !is_const<_Functor>::value)
       return 0;
     else
       return __ptr._M_access<_Functor*>();
   }
 else
   return 0;
      }
  template<typename _Res, typename... _ArgTypes>
    template<typename _Functor>
      const _Functor*
      function<_Res(_ArgTypes...)>::
      target() const noexcept
      {
 if (typeid(_Functor) == target_type() && _M_manager)
   {
     _Any_data __ptr;
     _M_manager(__ptr, _M_functor, __get_functor_ptr);
     return __ptr._M_access<const _Functor*>();
   }
 else
   return 0;
      }
  template<typename _Res, typename... _Args>
    inline bool
    operator==(const function<_Res(_Args...)>& __f, nullptr_t) noexcept
    { return !static_cast<bool>(__f); }
  template<typename _Res, typename... _Args>
    inline bool
    operator==(nullptr_t, const function<_Res(_Args...)>& __f) noexcept
    { return !static_cast<bool>(__f); }
  template<typename _Res, typename... _Args>
    inline bool
    operator!=(const function<_Res(_Args...)>& __f, nullptr_t) noexcept
    { return static_cast<bool>(__f); }
  template<typename _Res, typename... _Args>
    inline bool
    operator!=(nullptr_t, const function<_Res(_Args...)>& __f) noexcept
    { return static_cast<bool>(__f); }
  template<typename _Res, typename... _Args>
    inline void
    swap(function<_Res(_Args...)>& __x, function<_Res(_Args...)>& __y)
    { __x.swap(__y); }

}
using namespace rapidjson;
int main(int argc, char **argv) {
    Document jsondoc;
    Document::AllocatorType& allocator = jsondoc.GetAllocator();
    Value top_obj(kObjectType);
    jsondoc.AddMember(Value("manifest", allocator).Move(),
                      top_obj, allocator);
    std::stack<std::reference_wrapper<Value>> obj_stack;
    obj_stack.push(top_obj);
    obj_stack.top().get().AddMember(Value("submanifest", allocator).Move(),
                                    Value().Move(), allocator);
}
