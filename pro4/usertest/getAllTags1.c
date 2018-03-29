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
 int fd = open("ls", O_RDWR);
 tagFile(fd, "type", "utility", 7);
 tagFile(fd, "type", "xmanxma", 7);
 tagFile(fd, "type", "yeildxxx", 8);
 tagFile(fd, "language", "English", 7);
 tagFile(fd, "language", "Java", 4);
 tagFile(fd, "school", "Stanford", 8);
 tagFile(fd, "school", "MIT", 3);
 tagFile(fd, "Game", "NBA", 3);
 tagFile(fd, "Game", "CUBA", 4);
 close(fd);

  fd = open("ls", O_RDONLY);
  char buf0[8];
  char buf1[4];
  char buf2[3];
  char buf3[4];
  getFileTag(fd, "type", buf0, 8);
  printf(1, "buf0 = %s\n", buf0);
  getFileTag(fd, "language", buf1, 4);
  printf(1, "buf1 = %s\n", buf1);
  getFileTag(fd, "school", buf2, 3);
  printf(1, "buf2 = %s\n", buf2);
  getFileTag(fd, "Game", buf3, 4);
  printf(1, "buf3 = %s\n", buf3);
  close(fd);
 // char results[5];
 // int cnt = getFilesByTag("Game", "CUBA", 4, results, 5);
 // printf(1, "cnt = %d\n", cnt);
 // printf(1, "results = %s\n", results);
 fd = open("ls", O_RDONLY);

 struct Key keys[16];
 int numTags = getAllTags(fd, keys, 16);
 if(numTags < 0){
   exit();
 }
  
 printf(1, "numTags = %d\n", numTags);
 assert(numTags == 4);

 if(numTags > 16){
   numTags = 16;
 }
 char buffer[18];
 int i;
 printf(1, "Here is a list of this file's tags:\n");
 for(i = 0; i < numTags; i++){
     printf(1, "key %d is %s :\n", i, keys[i].key);
   int res = getFileTag(fd, keys[i].key, buffer, 18);
   if(res > 0){
     printf(1, "%s: %s\n", keys[i].key, buffer);
   }
 }
 close(fd);
 printf(1, "getAllTags test passed\n");
 exit();
}
