INCLUDE_DIR := include
SRC_DIR = src 
BUILD_DIR := build

CC := clang
CFLAGS := -I$(INCLUDE_DIR) -MMD -std=c23
CFLAGS += -Wall -Werror -nostdlib -nostartfiles -mgeneral-regs-only

AS := as 
ASFLAGS := -MMD -c

LD = ld
# LDFLAGS := -lSystem -syslibroot `xcrun -sdk macosx --show-sdk-path` 
# LDFLAGS += -arch arm64

# hardware directory
HD := src/hardware
# kernel directory
K := src/kernel


C_FILES = $(wildcard $(SRC_DIR)/*.c)
C_FILES += $(wildcard $(HD)/*.c)
C_FILES += $(wildcard $(K)/*.c)
ASM_FILES = $(wildcard $(SRC_DIR)/*.s)
ASM_FILES += $(wildcard $(HD)/*.s)
ASM_FILES += $(wildcard $(K)/*.s)
OBJ_FILES = $(C_FILES: &(SRC_DIR)/%.c=$(BUILD_DIR)/%_c.o)
OBJ_FILES += $(C_FILES: &(SRC_DIR)/%.s=$(BUILD_DIR)/%_s.o)
DEP_FILES = $(OBJ_FILES:%.o=%.d)
-include $(DEP_FILES)

H_OBJ = \
	$HD/init.o 

.PHONY: all clean

all: kernel8.img

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c	
	mkdir -p  $(@D)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.s
	$(AS) -o $@ $< $(ASFLAGS)


# 8 denotes armv8. Is a name convention for telling to boot in 64bit mode.
kernel8.img: $(SRC_DIR)/boot.ld $(OBJ_FILES)
	$(LD) -T $(SRC_DIR)/boot.ld -o $(BUILD_DIR)/kernel8.elf $(OBJ_FILES)
	llvm-objcopy $(BUILD_DIR)/kernel8.elf -O binary kernel8.img

clean:
	rm -rf $(BUILD_DIR)/*.o *.img main 
