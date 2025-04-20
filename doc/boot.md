# Overview
For boot step here is intended the first instruction executed by the CPU in the file 
boot.S. For the "real" boot sequence of the raspberry pi, check [this](https://raspberrypi.stackexchange.com/questions/10442/what-is-the-boot-sequence), [this](https://raspberrypi.stackexchange.com/questions/1200/what-happens-during-the-boot-process) and [this](https://github.com/DieterReuter/workshop-raspberrypi-64bit-os/blob/master/part1-bootloader.md).      
In this initial part of the OS (we use only one core while the others are in idle 
spinning) we start in [EL3](https://developer.arm.com/documentation/102412/0103/Privilege-and-Exception-levels/Exception-levels) and execute some setup statement
for EL2 and EL1.  
We then jump to kernel init to initialize hardware systems like UART, 
interrupts (check interrupts.md for more informations about this), bss memory and 
setup the stack for the kernel main function.


## Kernel init
The kernel init block is responsible to initialize basic hardware resources 
like: 
* the mini uart (or uart) serial interface
* printf debugging function 
* system timer and local timer
* interrupts (vector table, enable the controller, initialize each interrupt device)
* scheduler
* physical page allocator