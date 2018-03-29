# 343-Operating-System
Projects about adding features to xv6

# Pro1: Implemented the 'ps' shell command in xv6.

# Pro3： Implemented threads in xv6. 

Added two system calls --clone() and join(), and also implemented a user library that would allow a developer to make good use of the operating system's threads.  This user library includes wrapper functions for creating and joining threads.  It also includes synchronization-related functions which will make it easier to write thread-safe programs.(Theses functions are put in the user/uthreadlib.c)

# Pro4: Created three new syscalls that will allow files in the xv6 file system to be tagged with key-value pairs. 

As an example, you might have an essay for your history class saved as a file in xv6.  You could tag this file as "class": "History 101".  In this example, the key is "class" and the value is "History 101". The syscalls added in this project are tagFile, getFileTag, and removeFileTag.
