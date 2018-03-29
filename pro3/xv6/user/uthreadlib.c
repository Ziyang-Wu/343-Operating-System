#include "types.h"
#include "user.h"
#include "x86.h"

#define PGSIZE 4096


int
thread_create(void (*start_routine)(void*), void* arg)
{
  void *stack = malloc(2 * PGSIZE);
  if ((uint)stack % PGSIZE != 0) stack += PGSIZE - (uint)stack % PGSIZE;
  return clone(start_routine, arg, stack);
}

int
thread_join(int pid)
{
  int ustack;
  if ((ustack = getstack(pid)) < 0) return -1;    //find ustack, see definition in proc.c
  free((void*)ustack);
  return join(pid);
}

void lock_acquire(lock_t* lock)
{
  while(xchg(lock, 1) != 0) ;
}

void lock_release(lock_t* lock)
{
  xchg(lock, 0);
}

void lock_init(lock_t* lock)
{
  *lock = 0;
}

