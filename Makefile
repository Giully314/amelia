INCLUDE_DIR := include
SRC_DIR = src
BUILD_DIR := build

CC := clang
CFLAGS := -I$(INCLUDE_DIR) -MMD -std=c23 --target=aarch64-unknown-linux-gnu
CFLAGS += -Wall -nostdlib -nostartfiles -mgeneral-regs-only

AS := as
ASFLAGS := -c --target=aarch64-unknown-linux-gnu -I$(INCLUDE_DIR)

LINKER_SCRIPT := src/kernel.ld
LD = ld.lld
LDFLAGS := -T $(LINKER_SCRIPT)

HD := $(SRC_DIR)/hardware
PERIPHERALS_DIR := $(SRC_DIR)/peripherals
UART_DIR := $(SRC_DIR)/peripherals/uart
K := $(SRC_DIR)/kernel

$(info Running makefile)

C_FILES = $(wildcard $(SRC_DIR)/*.c)
# C_FILES += $(wildcard $(PERIPHERALS_DIR)/*.c)
# C_FILES += $(wildcard $(HD)/*.c)
C_FILES += $(wildcard $(K)/*.c)
C_FILES += $(wildcard $(UART_DIR)/*.c)
ASM_FILES = $(wildcard $(SRC_DIR)/*.S)
ASM_FILES += $(wildcard $(HD)/*.S)

OBJ_FILES = $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
OBJ_FILES += $(ASM_FILES:$(SRC_DIR)/%.S=$(BUILD_DIR)/%.o)

DEP_FILES := $(OBJ_FILES:%.o=%.d)
-include $(DEP_FILES)

$(info    C_FILES is $(C_FILES))
$(info    ASM_FILES is $(ASM_FILES))
$(info    OBJ_FILES is $(OBJ_FILES))

all: kernel8.img

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p  $(@D)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.S
	mkdir -p  $(@D)
	$(CC) $< -o $@ $(ASFLAGS)


# 8 denotes armv8. Is a name convention for telling to boot in 64bit mode.
kernel8.img: $(LINKER_SCRIPT) $(OBJ_FILES)
	$(LD) $(LDFLAGS) -o $(BUILD_DIR)/kernel8.elf $(OBJ_FILES)
	llvm-objcopy $(BUILD_DIR)/kernel8.elf -O binary kernel8.img

clean:
	rm -rf $(BUILD_DIR) *.img