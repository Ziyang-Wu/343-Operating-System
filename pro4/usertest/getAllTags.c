#include "types.h"
#include "user.h"
// make sure that struct Key is included via either types.h or user.h above

#define O_RDONLY 0x000
#define O_WRONLY 0x001
#define O_RDWR 0x002
#define O_CREATE 0x200

int ppid;

#define assert(x) if (x) {} else { \
   printf(1, "%s: %d ", __FILE__, __LINE__); \
   printf(1, "assert failed (%s)\n", # x); \
   printf(1, "TEST FAILED\n"); \
   kill(ppid); \
   exit(); \
}

int
main(int argc, char *argv[])
{
    ppid = getpid();
    char * key[3];
    char * vals[3];
    int fd = open("ls", O_RDWR);
    int res;
    int len = 8;
    key[0] = "type1";
    vals[0] = "utility1";
    res = tagFile(fd, key[0], vals[0], len);  
    assert(res > 0);
    key[1] = "type2";
    vals[1] = "utility2";
    res = tagFile(fd, key[1], vals[1], len);  
    assert(res > 0);
    key[2] = "type3";
    vals[2] = "utility3";
    res = tagFile(fd, key[2], vals[2], len);  
    assert(res > 0);
    
    fd = open("ls", O_RDONLY);
    char buf0[8];
    char buf1[8];
    char buf2[8];
  
    getFileTag(fd, "type1", buf0, 8);
    printf(1, "buf0 = %s\n", buf0);
    getFileTag(fd, "type2", buf1, 8);
    printf(1, "buf1 = %s\n", buf1);
    getFileTag(fd, "type3", buf2, 8);
    printf(1, "buf2 = %s\n", buf2);

    close(fd);
    
    fd = open("ls", O_RDONLY);
    struct Key keys[3];
    int numTags = getAllTags(fd, keys, 3);
    printf(1, "numTags = %d\n", numTags);
    assert(numTags == 3);
    int i, j;
    // const char * buffer_val;
    for(i = 0; i < numTags; i++){
        char buffer[8];
        char * expected_val = vals[i];
        int len = getFileTag(fd, keys[i].key, buffer, 8);
        printf(1,"len = %d\n", len);
        assert(len > 8);
        for (j = 0; j < len; j++) {
            char v_actual = buffer[j];
            printf(1,"actual: %s\n", v_actual);
            printf(1,"expected: %s\n\n", expected_val[j]);
            assert(v_actual == expected_val[j]);
        }
    }
    close(fd);
    printf(1, "getAllTags test passed\n");
    exit();
}
