# Overview
Interrupts (or in ARM terminology, exceptions) are a mechanism implemented
at hardware level to interrupt the control flow and execute some special
procedures stored in a table called the exception vector table.  
We have 2 types of interrupts: local and global.  
Local interrupts are local to the single [PE](https://developer.arm.com/documentation/102404/0202/Common-architecture-terms) while the global
interrupts comes from outside. The interrupt controller handles which core 
should receive  a specific interrupt from the global ones; can also 
send interrupts between cores (mailboxes) and control the local timer and
the performance monitors interrupts (PMU). 
By default the global interrupts are sent to the first PE.  
The design of interrupts in `amelia` is the following: each peripheral that support
interrupts have 3 functions for enabling, disabling and handling the interrupt.  
Through the `irq.h` and `irq_regs.h` files we can enable the corresponding interrupt
via the global controller hardware.  

Interrupts can be raised by peripherals devices or by the core itself, in the 
last case we have a sync exception, usually done by a user process to signal a system
call to the OS. We need this mechanism because user processes are at EL0 (low 
priviliges) but the functionalities requested usually need EL1 to be executed.
The code that handles this can be found in exception_entry.S in the function 
el0_sync.

## Resources
Interrupt handling: https://krinkinmu.github.io/2021/01/10/aarch64-interrupt-handling.html  
Arm general handling of interrupts: https://developer.arm.com/documentation/ihi0048/a/Interrupt-Handling-and-Prioritization/General-handling-of-interrupts  
