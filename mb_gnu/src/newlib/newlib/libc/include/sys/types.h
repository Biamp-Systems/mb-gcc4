/* unified sys/types.h: 
   start with sef's sysvi386 version.
   merge go32 version -- a few ifdefs.
   h8300hms, h8300xray, and sysvnecv70 disagree on the following types:

   typedef int gid_t;
   typedef int uid_t;
   typedef int dev_t;
   typedef int ino_t;
   typedef int mode_t;
   typedef int caddr_t;

   however, these aren't "reasonable" values, the sysvi386 ones make far 
   more sense, and should work sufficiently well (in particular, h8300 
   doesn't have a stat, and the necv70 doesn't matter.) -- eichin
 */

#ifndef _SYS_TYPES_H

#include <_ansi.h>

#ifndef __INTTYPES_DEFINED__
#define __INTTYPES_DEFINED__

#include <machine/_types.h>

#if defined(__rtems__) || defined(__XMK__)
/*
 *  The following section is RTEMS specific and is needed to more
 *  closely match the types defined in the BSD sys/types.h.
 *  This is needed to let the RTEMS/BSD TCP/IP stack compile.
 */

/* deprecated */
#if ___int8_t_defined
typedef __uint8_t	u_int8_t;
#endif
#if ___int16_t_defined
typedef __uint16_t	u_int16_t;
#endif 
#if ___int32_t_defined
typedef __uint32_t	u_int32_t;
#endif

#if ___int64_t_defined
typedef __uint64_t	u_int64_t;

/* deprecated */
typedef	__uint64_t	u_quad_t;
typedef	__int64_t	quad_t;
typedef	quad_t *	qaddr_t;
#endif

#endif

#endif /* ! __INTTYPES_DEFINED */

#ifndef __need_inttypes

#define _SYS_TYPES_H
#include <sys/_types.h>

#ifdef __i386__
#if defined (GO32) || defined (__MSDOS__)
#define __MS_types__
#endif
#endif

# include <stddef.h>
# include <machine/types.h>

/* To ensure the stat struct's layout doesn't change when sizeof(int), etc.
   changes, we assume sizeof short and long never change and have all types
   used to define struct stat use them and not int where possible.
   Where not possible, _ST_INTxx are used.  It would be preferable to not have
   such assumptions, but until the extra fluff is necessary, it's avoided.
   No 64 bit targets use stat yet.  What to do about them is postponed
   until necessary.  */
#ifdef __GNUC__
#define _ST_INT32 __attribute__ ((__mode__ (__SI__)))
#else
#define _ST_INT32
#endif

# ifndef	_POSIX_SOURCE

#  define	physadr		physadr_t
#  define	quad		quad_t

#ifndef _BSDTYPES_DEFINED
/* also defined in mingw/gmon.h and in w32api/winsock[2].h */
typedef	unsigned char	u_char;
typedef	unsigned short	u_short;
typedef	unsigned int	u_int;
typedef	unsigned long	u_long;
#define _BSDTYPES_DEFINED
#endif

typedef	unsigned short	ushort;		/* System V compatibility */
typedef	unsigned int	uint;		/* System V compatibility */
# endif	/*!_POSIX_SOURCE */

#ifndef __clock_t_defined
typedef _CLOCK_T_ clock_t;
#define __clock_t_defined
#endif

#ifndef __time_t_defined
typedef _TIME_T_ time_t;
#define __time_t_defined

/* Time Value Specification Structures, P1003.1b-1993, p. 261 */

struct timespec {
  time_t  tv_sec;   /* Seconds */
  long    tv_nsec;  /* Nanoseconds */
};

struct itimerspec {
  struct timespec  it_interval;  /* Timer period */
  struct timespec  it_value;     /* Timer expiration */
};
#endif

typedef	long	daddr_t;
typedef	char *	caddr_t;

#ifndef __CYGWIN__
#if defined(__MS_types__) || defined(__rtems__)
typedef	unsigned long	ino_t;
#else
#ifdef __sparc__
typedef	unsigned long	ino_t;
#else
typedef	unsigned short	ino_t;
#endif
#endif
#endif /*__CYGWIN__*/

#ifdef __MS_types__
typedef unsigned long vm_offset_t;
typedef unsigned long vm_size_t;

#define __BIT_TYPES_DEFINED__

typedef signed char int8_t;
typedef unsigned char u_int8_t;
typedef short int16_t;
typedef unsigned short u_int16_t;
typedef int int32_t;
typedef unsigned int u_int32_t;
typedef long long int64_t;
typedef unsigned long long u_int64_t;
typedef int32_t register_t;
#endif /* __MS_types__ */

/*
 * All these should be machine specific - right now they are all broken.
 * However, for all of Cygnus' embedded targets, we want them to all be
 * the same.  Otherwise things like sizeof (struct stat) might depend on
 * how the file was compiled (e.g. -mint16 vs -mint32, etc.).
 */

#if defined(__rtems__) || defined(__XMK__)
/* device numbers are 32-bit major and and 32-bit minor */
typedef unsigned long long dev_t;
#else
#ifndef __CYGWIN__
typedef	short	dev_t;
#endif
#endif

#ifndef __CYGWIN__	/* which defines these types in it's own types.h. */
typedef long		off_t;

typedef	unsigned short	uid_t;
typedef	unsigned short	gid_t;
#endif

#if defined(__XMK__)
typedef signed char pid_t;
#else
typedef int pid_t;
#endif

#ifndef __CYGWIN__
typedef	long key_t;
#endif
typedef _ssize_t ssize_t;

#ifndef __CYGWIN__
#ifdef __MS_types__
typedef	char *	addr_t;
typedef int mode_t;
#else
#if defined (__sparc__) && !defined (__sparc_v9__)
#ifdef __svr4__
typedef unsigned long mode_t;
#else
typedef unsigned short mode_t;
#endif
#else
typedef unsigned int mode_t _ST_INT32;
#endif
#endif /* ! __MS_types__ */
#endif /*__CYGWIN__*/

typedef unsigned short nlink_t;

/* We don't define fd_set and friends if we are compiling POSIX
   source, or if we have included (or may include as indicated
   by __USE_W32_SOCKETS) the W32api winsock[2].h header which
   defines Windows versions of them.   Note that a program which
   includes the W32api winsock[2].h header must know what it is doing;
   it must not call the cygwin32 select function.
*/
# if !(defined (_POSIX_SOURCE) || defined (_WINSOCK_H) || defined (__USE_W32_SOCKETS)) 
#  define _SYS_TYPES_FD_SET
#  define	NBBY	8		/* number of bits in a byte */
/*
 * Select uses bit masks of file descriptors in longs.
 * These macros manipulate such bit fields (the filesystem macros use chars).
 * FD_SETSIZE may be defined by the user, but the default here
 * should be >= NOFILE (param.h).
 */
#  ifndef	FD_SETSIZE
#	define	FD_SETSIZE	64
#  endif

typedef	long	fd_mask;
#  define	NFDBITS	(sizeof (fd_mask) * NBBY)	/* bits per mask */
#  ifndef	howmany
#	define	howmany(x,y)	(((x)+((y)-1))/(y))
#  endif

/* We use a macro for fd_set so that including Sockets.h afterwards
   can work.  */
typedef	struct _types_fd_set {
	fd_mask	fds_bits[howmany(FD_SETSIZE, NFDBITS)];
} _types_fd_set;

#define fd_set _types_fd_set

#  define	FD_SET(n, p)	((p)->fds_bits[(n)/NFDBITS] |= (1L << ((n) % NFDBITS)))
#  define	FD_CLR(n, p)	((p)->fds_bits[(n)/NFDBITS] &= ~(1L << ((n) % NFDBITS)))
#  define	FD_ISSET(n, p)	((p)->fds_bits[(n)/NFDBITS] & (1L << ((n) % NFDBITS)))
#  define	FD_ZERO(p)	(__extension__ (void)({ \
     size_t __i; \
     char *__tmp = (char *)p; \
     for (__i = 0; __i < sizeof (*(p)); ++__i) \
       *__tmp++ = 0; \
}))

# endif	/* !(defined (_POSIX_SOURCE) || defined (_WINSOCK_H) || defined (__USE_W32_SOCKETS)) */

#undef __MS_types__
#undef _ST_INT32


#ifndef __clockid_t_defined
typedef _CLOCKID_T_ clockid_t;
#define __clockid_t_defined
#endif

#ifndef __timer_t_defined
typedef _TIMER_T_ timer_t;
#define __timer_t_defined
#endif

typedef long useconds_t;

#include <sys/features.h>


/* Cygwin will probably never have full posix compliance due to little things
 * like an inability to set the stackaddress. Cygwin is also using void *  
 * pointers rather than structs to ensure maximum binary compatability with
 * previous releases.
 * This means that we don't use the types defined here, but rather in
 * <cygwin/types.h>
 */
#if defined(_POSIX_THREADS) && !defined(__CYGWIN__) && !defined(_UCLIBC_PTHREADS)

#include <sys/sched.h>

/*
 *  2.5 Primitive System Data Types,  P1003.1c/D10, p. 19.
 */

#if defined(__XMK__)
typedef unsigned int pthread_t;          /* identify a thread */
#else
typedef __uint32_t pthread_t;            /* identify a thread */
#endif


/* P1003.1c/D10, p. 118-119 */
#define PTHREAD_SCOPE_PROCESS 0
#define PTHREAD_SCOPE_SYSTEM  1

/* P1003.1c/D10, p. 111 */
#define PTHREAD_INHERIT_SCHED  1      /* scheduling policy and associated */
                                      /*   attributes are inherited from */
                                      /*   the calling thread. */
#define PTHREAD_EXPLICIT_SCHED 2      /* set from provided attribute object */

/* P1003.1c/D10, p. 141 */
#define PTHREAD_CREATE_DETACHED 0
#define PTHREAD_CREATE_JOINABLE  1

#if defined(__XMK__)
/* The following defines are part of the X/Open System Interface (XSI). */

/* This type of mutex does not detect deadlock. A thread attempting to 
 * relock this mutex without first unlocking it shall deadlock. Attempting 
 * to unlock a mutex locked by a different thread results in undefined 
 * behavior.  Attempting to unlock an unlocked mutex results in undefined 
 * behavior. 
 */
#define PTHREAD_MUTEX_NORMAL  1

/* 
 * This type of mutex provides error checking. A thread attempting to 
 * relock this mutex without first unlocking it shall return with an error. 
 * A thread attempting to unlock a mutex which another thread has locked 
 * shall return with an error. A thread attempting to unlock an unlocked 
 * mutex shall return with an error. 
 */
#define PTHREAD_MUTEX_ERRORCHECK  2 

/* A thread attempting to relock this mutex without first unlocking it 
 * shall succeed in locking the mutex.  The relocking deadlock which can 
 * occur with mutexes of type PTHREAD_MUTEX_NORMAL cannot occur with this 
 * type of mutex.  Multiple locks of this mutex shall require the same 
 * number of unlocks to release the mutex before another thread can 
 * acquire the mutex. A thread attempting to unlock a mutex which another 
 * thread has locked shall return with an error.  A thread attempting to 
 * unlock an unlocked mutex shall return with an error. 
 */
#define PTHREAD_MUTEX_RECURSIVE  3

/* Attempting to recursively lock a mutex of this type results in 
 * undefined behavior. Attempting to unlock a mutex of this type which was 
 * not locked by the calling thread results in undefined behavior. 
 * Attempting to unlock a mutex of this type which is not locked results 
 * in undefined behavior. An implementation may map this mutex to one of 
 * the other mutex types.
 */
#define PTHREAD_MUTEX_DEFAULT  4 

#endif /* defined(__XMK__) */

#if defined(__XMK__)
typedef struct pthread_attr_s {
  int contentionscope;
  struct sched_param schedparam;
  int  detachstate;
  void *stackaddr;
  size_t stacksize;
} pthread_attr_t;

#define PTHREAD_STACK_MIN       200

#else

typedef struct {
  int is_initialized;
  void *stackaddr;
  int stacksize;
  int contentionscope;
  int inheritsched;
  int schedpolicy;
  struct sched_param schedparam;

  /* P1003.4b/D8, p. 54 adds cputime_clock_allowed attribute.  */
#if defined(_POSIX_THREAD_CPUTIME)
  int  cputime_clock_allowed;  /* see time.h */
#endif
  int  detachstate;

} pthread_attr_t;
#endif

#if defined(_POSIX_THREAD_PROCESS_SHARED)
/* NOTE: P1003.1c/D10, p. 81 defines following values for process_shared.  */

#define PTHREAD_PROCESS_PRIVATE 0 /* visible within only the creating process */
#define PTHREAD_PROCESS_SHARED  1 /* visible too all processes with access to */
                                  /*   the memory where the resource is */
                                  /*   located */
#endif

#if defined(_POSIX_THREAD_PRIO_PROTECT)
/* Mutexes */

/* Values for blocking protocol. */

#define PTHREAD_PRIO_NONE    0
#define PTHREAD_PRIO_INHERIT 1
#define PTHREAD_PRIO_PROTECT 2
#endif

#if defined(__XMK__)
typedef unsigned int pthread_mutex_t;    /* identify a mutex */

typedef struct {
  int type;
} pthread_mutexattr_t;

typedef __uint32_t pthread_mutex_t;      /* identify a mutex */

#else

typedef struct {
  int   is_initialized;
#if defined(_POSIX_THREAD_PROCESS_SHARED)
  int   process_shared;  /* allow mutex to be shared amongst processes */
#endif
#if defined(_POSIX_THREAD_PRIO_PROTECT)
  int   prio_ceiling;
  int   protocol;
#endif
  int   recursive;
} pthread_mutexattr_t;

typedef __uint32_t pthread_mutex_t;      /* identify a mutex */

#endif /* defined(__XMK__) */

/* Condition Variables */

typedef __uint32_t pthread_cond_t;       /* identify a condition variable */

typedef struct {
  int   is_initialized;
#if defined(_POSIX_THREAD_PROCESS_SHARED)
  int   process_shared;       /* allow this to be shared amongst processes */
#endif
} pthread_condattr_t;         /* a condition attribute object */

/* Keys */

typedef __uint32_t pthread_key_t;        /* thread-specific data keys */

typedef struct {
  int   is_initialized;  /* is this structure initialized? */
  int   init_executed;   /* has the initialization routine been run? */
} pthread_once_t;       /* dynamic package initialization */
#else
#if defined (__CYGWIN__)
#include <cygwin/types.h>
#else
#if defined(_UCLIBC_PTHREADS)

#include <sys/sched.h>

#define __LOCK_INITIALIZER { 0, 0 }

/* Thread identifiers */
typedef unsigned long int pthread_t;

/* Values for attributes.  */

enum
{
  PTHREAD_CREATE_JOINABLE,
  PTHREAD_CREATE_DETACHED
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
  PTHREAD_MUTEX_NORMAL,
  PTHREAD_MUTEX_RECURSIVE,
  PTHREAD_MUTEX_ERRORCHECK,
  PTHREAD_MUTEX_DEFAULT,
  PTHREAD_MUTEX_FAST_NP
};

enum
{
  PTHREAD_PROCESS_PRIVATE,
  PTHREAD_PROCESS_SHARED
};

/* Fast locks (not abstract because mutexes and conditions aren't abstract). */
struct _pthread_fastlock
{
  long int __status;   /* "Free" or "taken" or head of waiting list */
  int __spinlock;      /* Used by compare_and_swap emulation. Also,
                          adaptive SMP lock stores spin count here. */
};

/* Thread descriptors */
typedef struct _pthread_descr_struct *_pthread_descr;

/* Attributes for threads.  */
typedef struct __pthread_attr_s
{
  int __detachstate;
  int __schedpolicy;
  struct sched_param __schedparam;
  int __inheritsched;
  int __scope;
  size_t __guardsize;
  int __stackaddr_set;
  void *__stackaddr;
  size_t __stacksize;
} pthread_attr_t;

/* Mutexes (not abstract because of PTHREAD_MUTEX_INITIALIZER).  */
/* (The layout is unnatural to maintain binary compatibility
       with earlier releases of LinuxThreads.) */
typedef struct
{
  int __m_reserved;               /* Reserved for future use */
  int __m_count;                  /* Depth of recursive locking */
  _pthread_descr __m_owner;       /* Owner thread (if recursive or errcheck) */
  int __m_kind;                   /* Mutex kind: fast, recursive or errcheck */
  struct _pthread_fastlock __m_lock; /* Underlying fast lock */
} pthread_mutex_t;

/* Attribute for mutex.  */
typedef struct
{
  int __mutexkind;
} pthread_mutexattr_t;

/* Once-only execution */
typedef int pthread_once_t;

/* Conditions (not abstract because of PTHREAD_COND_INITIALIZER */
typedef struct
{
  struct _pthread_fastlock __c_lock; /* Protect against concurrent access */
  _pthread_descr __c_waiting;        /* Threads waiting on this condition */
} pthread_cond_t;

/* Attribute for conditionally variables.  */
typedef struct
{
  int __dummy;
} pthread_condattr_t;

typedef unsigned int pthread_key_t;        /* thread-specific data keys */

#endif /* defined(_UCLIBC_PTHREADS) */
#endif
#endif /* defined(_POSIX_THREADS) */

#endif  /* !__need_inttypes */

#undef __need_inttypes

#endif	/* _SYS_TYPES_H */
