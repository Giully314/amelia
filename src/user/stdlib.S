// src/user/stdlib.S

#include <amelia/kernel/syscall.h>

.global page_malloc
page_malloc:
    mov w8, #SYS_MALLOC_NUMBER
    svc #0
    ret

.global exit
exit:
    mov w8, #SYS_EXIT_NUMBER
    svc #0
    ret