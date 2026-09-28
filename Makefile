qemu-debug-run: kernel8.img
	qemu -M raspi3b -d trace:bcm2835_systmr* -serial null -serial stdio -kernel build/kernel8.elf

# -serial pty for another terminal
qemu-run: kernel8.img
	qemu-system-aarch64 -M raspi3b -serial null -serial stdio -kernel build/kernel8.elf


qemu-uart-run: kernel8.img
	qemu-system-aarch64 -M raspi3b -serial stdio -kernel build/kernel8.elf