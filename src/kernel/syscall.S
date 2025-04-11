// src/kernel/syscall.S

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


.global sys_fork
sys_fork:
    // Save arguments
    mov x10, x0  // f
    mov x11, x1  // args
    mov x12, x2  // stack

    mov x0, x2 // pass stack to fork system call.
    mov x8, #SYS_FORK_NUMBER
    svc 0x0

    // If the return value is 0, it means we are in the parent process.
    // Otherwise it is the PID and so we start the thread.
    cmp x0, #0
    beq thread_start
    ret

thread_start:
    mov x29, 0

    mov x0, x11
    blr x10

    mov x8, #SYS_EXIT_NUMBER
    svc 0x0