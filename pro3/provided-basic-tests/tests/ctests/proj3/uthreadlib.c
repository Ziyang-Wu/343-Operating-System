#include "types.h"
#include "user.h"
#include "x86.h"

#define PGSIZE 4096

// BEGIN: Creates a new thread by first allocating a page-aligned user stack, then calling the clone syscall.  Returns the pid of the new thread.
int
thread_create(void (*start_routine)(void*), void* arg)
{
  void *stack = malloc(2 * PGSIZE);
  if ((uint)stack % PGSIZE != 0) stack += PGSIZE - (uint)stack % PGSIZE;
  return clone(start_routine, arg, stack);
}
// END: Creates a new thread by first allocating a page-aligned user stack, then calling the clone syscall.  Returns the pid of the new thread.

// BEGIN: Calls join to wait for the thread specified by pid to complete.  Cleans up the completed thread's user stack.
int
thread_join(int pid)
{
  int ustack;
  if ((ustack = find_ustack(pid)) < 0) return -1;
  free((void*)ustack);
  return join(pid);
}
// END: Calls join to wait for the thread specified by pid to complete.  Cleans up the completed thread's user stack.

// BEGIN: Acquires the lock pointed to by lock.  If the lock is already held, spin until it becomes available.
void lock_acquire(lock_t* lock)
{
  while(xchg(lock, 1) != 0) ;
}
// END: Acquires the lock pointed to by lock.  If the lock is already held, spin until it becomes available.

// BEGIN: Release the lock pointed to by lock.
void lock_release(lock_t* lock)
{
  xchg(lock, 0);
}
// END: Release the lock pointed to by lock.

// BEGIN: Initialize the lock pointed to by lock.
void lock_init(lock_t* lock)
{
  *lock = 0;
}
// END: Initialize the lock pointed to by lock.