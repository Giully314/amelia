# Intro
Amelia is an operating system developed for learning purposes.  
For more informations about the design and implementation, check the `doc` directory.

# Resources
## Articles
[Raspberry pi os](https://s-matyukevich.github.io/raspberry-pi-os/)  
[Raspberry pi bare metal](https://github.com/bztsrc/raspi3-tutorial/)  
[AArch64 Interrupt handling](https://krinkinmu.github.io/2021/01/10/aarch64-interrupt-handling.html)  
[From 0 to main, bare metal C](https://interrupt.memfault.com/blog/zero-to-main-1)  
[Building an operating system for raspberry pi](https://jsandler18.github.io/)  

## Books 
Structured Computer Organization by Tanenbaum, Austin  
Computer organization and architecture Design for performance by William Stallings  
Operating Systems Concepts by Silberschatz, Galvin, Gagne  
Operating Systems: Three Easy Pieces  
Modern operating systems by Tanenbaum, Bos  

## Raspberry pi boot sequence 
https://raspberrypi.stackexchange.com/questions/10442/what-is-the-boot-sequence  
https://github.com/DieterReuter/workshop-raspberrypi-64bit-os/blob/master/part1-bootloader.md   

## Manuals
[bcm2837 manual](https://cs140e.sergio.bz/docs/BCM2837-ARM-Peripherals.pdf)
[bcm2836 peripherals](https://datasheets.raspberrypi.com/bcm2836/bcm2836-peripherals.pdf)
[ARM v8 manual](https://developer.arm.com/documentation/ddi0487/ca/)  

## QEMU 
With -kernel option, if you pass a .img the kernel will be loaded as a "Linux kernel"
where https://www.kernel.org/doc/Documentation/arm64/booting.txt must 
be meet. This 
also means that only the primary cpu will be started and the multi-core must be 
enabled by code. If you want to avoid this, pass the .elf kernel and qemu will
start to execute for all the cpu at the entry point.  
https://stackoverflow.com/questions/58420670/qemu-bios-vs-kernel-vs-device-loader-file