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