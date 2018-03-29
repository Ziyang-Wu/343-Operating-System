#include "types.h"
#include "stat.h"
#include "user.h"
#include "param.h"

// Memory allocator by Kernighan and Ritchie,
// The C programming Language, 2nd ed.  Section 8.7.

typedef long Align;  // for alignment to long boundary

union header {  // block header
  struct {
    union header *ptr; // next block, if on free list
    uint size;         // size of this block (in multiples of 8 bytes)
  } s;
  Align x;  // force alignment of blocks
};

typedef union header Header;

// global variables:
static Header base;   // the first free list node
static Header *freep; // start of the free list (head)

// put new block "ap" on the free list because we're done using it
void free(void *ap) {
  Header *bp = (Header*)ap - 1;  // the block header

  // Scan through the free list looking for the right place to insert.
  // Stop when we find a block p that is before the new block,
  // but the new block is before p's "right neighbor"
  Header *p;
  for(p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) {
    // There is a special case when the new block belongs at the start or end.
    // If the scan got to the block with the highest address,
    // and the new block is > the highest, or < the lowest
    if(p >= p->s.ptr && (bp > p || bp < p->s.ptr)) {
      break;  // block is at the start or end of the range
    }
  }
  // p will become the new block's "left neighbor" so insert after it,
  // but first check whether to coalesce.
  
  // if the end of the new block touches the right neighbor, coalesce-right
  if(bp + bp->s.size == p->s.ptr){
    bp->s.size += p->s.ptr->s.size;  // add the size of the right neighbor
    bp->s.ptr = p->s.ptr->s.ptr;     // point to the neighbor's neighbor
  }
  // if there is a gap to the right, just point to the right neighbor
  else bp->s.ptr = p->s.ptr;

  // if the end of left neighbor touches the new block's start, coalesce-left
  if(p + p->s.size == bp){
    p->s.size += bp->s.size;  // add the new block's size to the left neighbor
    p->s.ptr = bp->s.ptr;     // make the left neighbor point to the right neighbor
  }
  // if there is a gap to the left, the left neighbor points to the new block
  else p->s.ptr = bp;

  freep = p;  // change the start of the free list to point to the freed block
}

// minumum number of units to request
#define NALLOC 4096

// ask the OS for more memory
static Header* morecore(uint nu) {
  if(nu < NALLOC){  // never ask for just a tiny bit of memory
    nu = NALLOC;
  }
  // sbrk asks the OS to let us use more memory at the end of
  // the address space and returns a pointer to the beginning
  // of the new chunk
  char* p = sbrk(nu * sizeof(Header));
  // on failure, sbrk will return -1
  if(p == (char*)-1){
    return 0;
  }
  Header *hp = (Header*)p;  // cast the new memory as a Header*
  hp->s.size = nu;  // set up the new header
  free((void*)(hp + 1));  // add the new memory to the free list
  return freep;
}

// user program's general purpose storage allocator
void* malloc(uint nbytes) {
  Header *p, *prevp;

  // Round up allocation size to fit header size (8 bytes).
  // nunits is the size of the malloc, represented as a multiple of 8.
  uint nunits = (nbytes + sizeof(Header) - 1)/sizeof(Header) + 1;
  // if there is no free list yet, set up a list with one empty block
  if((prevp = freep) == 0){
    base.s.ptr = freep = prevp = &base;
    base.s.size = 0;
  }
  // scan through the free list
  for(p = prevp->s.ptr; ; prevp = p, p = p->s.ptr){
    // if it's big enough
    if(p->s.size >= nunits){
      // if exactly the right size, remove from the list
      if(p->s.size == nunits){
        prevp->s.ptr = p->s.ptr;
      }
      // split the free block by allocating the tail end
      else {
        p->s.size -= nunits;  // make the free block smaller

        // Modify our copy of the free block's header "p"
	// to make it represent the newly allocated block.
	p += p->s.size;
        p->s.size = nunits;
      }
      freep = prevp;  // change the start of the free list
                      // to implement the "next fit" policy
                      // (and a newly split block will be considered next)
      return (void*)(p + 1);  // allocated chunk, past the header
    }
    // if we looped around to list start again, no blocks are big enough
    if(p == freep) {
      // ask the OS for another chunk of free memory
      if((p = morecore(nunits)) == 0) {
        return 0;  // the memory allocation failed
      }
    }
  }
}
