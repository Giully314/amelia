qemu-debug-run: 
	qemu-system-aarch64 -M raspi4b -d trace:bcm2835_systmr* -serial null -serial stdio -kernel build/kernel8.elf

# -serial pty for another terminal
qemu-run: 
	qemu-system-aarch64 -M raspi4b -serial null -serial stdio -kernel build/app/kernel8.elf


qemu-uart-run: 
	qemu-system-aarch64 -M raspi4b -serial stdio -kernel build/app/kernel8.elf