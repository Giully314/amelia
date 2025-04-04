// src/user/stdio.S

#include <amelia/kernel/syscall.h>

.global write
write:
    mov w8, #SYS_WRITE_NUMBER
    svc #0
    ret


