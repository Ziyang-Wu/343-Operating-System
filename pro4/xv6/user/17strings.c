/* call tagFile to tag a file.  Call getFileTag to read the tag of that file. */
#include "types.h"
#include "user.h"

#define O_RDONLY  0x000
#define O_WRONLY  0x001
#define O_RDWR    0x002
#define O_CREATE  0x200

#undef NULL
#define NULL ((void*)0)

int ppid;
volatile int global = 1;

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
   printf(1, "fd of ls: %d\n", fd);
   int res0 = tagFile(fd, "M0", "CCCCCCCCCCCCCCCCC", 17);
   assert(res0 > 0);
   int res1 = tagFile(fd, "M1", "CCCCCCCCCCCCCCCCC", 17);
   assert(res1 > 0);
   int res2 = tagFile(fd, "M2", "CCCCCCCCCCCCCCCCC", 17);
   assert(res2 > 0);
   int res3 = tagFile(fd, "M3", "CCCCCCCCCCCCCCCCC", 17);
   assert(res3 > 0);
   int res4 = tagFile(fd, "M4", "CCCCCCCCCCCCCCCCC", 17);
   assert(res4 > 0);
   int res5 = tagFile(fd, "M5", "CCCCCCCCCCCCCCCCC", 17);
   assert(res5 > 0);
   int res6 = tagFile(fd, "M6", "CCCCCCCCCCCCCCCCC", 17);
   assert(res6 > 0);
   int res7 = tagFile(fd, "M5", "ME", 2); // M
   assert(res7 > 0);
   int res8 = tagFile(fd, "M8", "CCCCCCCCCCCCCCCCC", 17);
   assert(res8 > 0);
   int res9 = tagFile(fd, "M9", "CCCCCCCCCCCCCCCCC", 17);
   assert(res9 > 0);
   int res10 = tagFile(fd, "M8", "CE", 2);
   assert(res10 > 0);
   int res11 = tagFile(fd, "M11", "CCCCCCCCCCCCCCCCC", 17);
   assert(res11 > 0);
   int res12 = tagFile(fd, "M12", "CCCCCCCCCCCCCCCCC", 17);
   assert(res12 > 0);
   int res13 = tagFile(fd, "M13", "CCCCCCCCCCCCCCCCC", 17);
   assert(res13 > 0);
   int res14 = tagFile(fd, "M14", "CCCCCCCCCCCCCCCCC", 17);
   assert(res14 > 0);
   int res15 = tagFile(fd, "M15", "CCCCCCCCCCCCCCCCC", 17);
   assert(res15 > 0);
   int res16 = tagFile(fd, "M16", "CCCCCCCCCCCCCCCCC", 17);
   assert(res16 > 0);
   int res17 = tagFile(fd, "M17", "CCCCCCCCCCCCCCCCC", 17);
   assert(res17 > 0);
   int res18 = tagFile(fd, "M18", "CCCCCCCCCCCCCCCCC", 17);
   assert(res18 < 0);
   int res19 = tagFile(fd, "M19", "CCCCCCCCCCCCCCCCC", 17);
   assert(res19 < 0);
   int res20 = tagFile(fd, "M20", "CCCCCCCCCCCCCCCCC", 17);
   assert(res20 < 0);
   int res21 = tagFile(fd, "M21", "CCCCCCCCCCCCCCCCC", 17);
   assert(res21 < 0);

   char buf[17];
   int valueLength = getFileTag(fd, "M0", buf, 17);
   assert(valueLength == 17);

   char buf1[2];
   int valueLength1 = getFileTag(fd, "M8", buf1, 2);
   assert(valueLength1 == 2);

   close(fd);

   int i;
   char *val = "CCCCCCCCCCCCCCCCC";
   for(i = 0; i < 17; i++){
      char v_actual = buf[i];
      char v_expected = val[i];
      assert(v_actual == v_expected);
   }

   char *val1 = "CE";
   for(i = 0; i < 2; i++){
      char v_actual = buf1[i];
      char v_expected = val1[i];
      assert(v_actual == v_expected);
   }   

   printf(1, "TEST PASSED\n");
   exit();
}
