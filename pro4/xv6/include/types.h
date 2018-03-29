#ifndef _TYPES_H_
#define _TYPES_H_

// Type definitions

typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;
typedef uint pde_t;
#ifndef NULL
#define NULL (0)
#endif


#ifndef _KEY_H_
#define _KEY_H_
struct Key {
    char key[10];  // at most 10 bytes for key
};
#endif // _KEY_H_

#endif //_TYPES_H_
