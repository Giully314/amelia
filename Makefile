INCLUDE_DIR := include
SRC_DIR = src
BUILD_DIR := build

CC := clang
CFLAGS := -c -I$(INCLUDE_DIR) -MMD --target=aarch64-elf -ffreestanding  
CFLAGS += -mcpu=cortex-a53+nosimd
CFLAGS += -Wall -nostdlib -O2 -std=c23

LINKER_SCRIPT := src/kernel.ld
LD = ld.lld
LDFLAGS := -T $(LINKER_SCRIPT) -m aarch64elf -nostdlib 

HD := $(SRC_DIR)/hardware
PERIPHERALS_DIR := $(SRC_DIR)/peripherals
UART_DIR := $(PERIPHERALS_DIR)/uart
TIMER_DIR := $(PERIPHERALS_DIR)/timer
K := $(SRC_DIR)/kernel
MEMORY_DIR = $(SRC_DIR)/memory
DS_DIR = $(SRC_DIR)/ds
ALGORITHMS_DIR = $(SRC_DIR)/algorithms

$(info Running makefile)

C_FILES = $(wildcard $(SRC_DIR)/*.c)
C_FILES += $(wildcard $(PERIPHERALS_DIR)/*.c)
C_FILES += $(wildcard $(HD)/*.c)
C_FILES += $(wildcard $(K)/*.c)
C_FILES += $(wildcard $(UART_DIR)/*.c)
C_FILES += $(wildcard $(TIMER_DIR)/*.c)
C_FILES += $(wildcard $(MEMORY_DIR)/*.c)
C_FILES += $(wildcard $(DS_DIR)/*.c)
C_FILES += $(wildcard $(ALGORITHMS_DIR)/*.c)

ASM_FILES = $(wildcard $(SRC_DIR)/*.S)
ASM_FILES += $(wildcard $(PERIPHERALS_DIR)/*.S)
ASM_FILES += $(wildcard $(UART_DIR)/*.S)
ASM_FILES += $(wildcard $(TIMER_DIR)/*.S)
ASM_FILES += $(wildcard $(K)/*.S)
ASM_FILES += $(wildcard $(HD)/*.S)
ASM_FILES += $(wildcard $(MEMORY_DIR)/*.S)
ASM_FILES += $(wildcard $(DS_DIR)/*.S)
ASM_FILES += $(wildcard $(ALGORITHMS_DIR)/*.S)


OBJ_FILES = $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%_c.o)
OBJ_FILES += $(ASM_FILES:$(SRC_DIR)/%.S=$(BUILD_DIR)/%_s.o)

DEP_FILES := $(OBJ_FILES:%.o=%.d)
-include $(DEP_FILES)

$(info    C_FILES is $(C_FILES))
$(info    ASM_FILES is $(ASM_FILES))
$(info    OBJ_FILES is $(OBJ_FILES))

all: kernel8.img

$(BUILD_DIR)/%_c.o: $(SRC_DIR)/%.c
	mkdir -p  $(@D)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BUILD_DIR)/%_s.o: $(SRC_DIR)/%.S
	mkdir -p  $(@D)
	$(CC) $< -o $@ $(CFLAGS)


# 8 denotes armv8. Is a name convention for telling to boot in 64bit mode.
kernel8.img: $(LINKER_SCRIPT) $(OBJ_FILES)
	$(LD) $(LDFLAGS) -o $(BUILD_DIR)/kernel8.elf $(OBJ_FILES)
	llvm-objcopy -O binary $(BUILD_DIR)/kernel8.elf kernel8.img

qemu-debug-run: kernel8.img
	qemu-system-aarch64 -M raspi3b -d trace:bcm2835_systmr* -serial null -serial stdio -kernel build/kernel8.elf

# -serial pty for another terminal
qemu-run: kernel8.img
	qemu-system-aarch64 -M raspi3b -serial null -serial stdio -kernel build/kernel8.elf


qemu-uart-run: kernel8.img
	qemu-system-aarch64 -M raspi3b -serial stdio -kernel build/kernel8.elf

qemu-clean-run: clean qemu-run

clean:
	rm -rf $(BUILD_DIR) *.img