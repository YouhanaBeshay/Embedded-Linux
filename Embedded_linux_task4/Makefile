CROSS_COMP = ~/x-tools/aarch64-rpi3-linux-gnu/bin/aarch64-rpi3-linux-gnu-
CC = $(CROSS_COMP)gcc
LD = $(CROSS_COMP)ld
AS = $(CROSS_COMP)as

LINKER_SCRIPT = linkerscript.ld
OBJCOPY = $(CROSS_COMP)objcopy

CFLAGS = -ffreestanding -nostdlib  -nostartfiles -Wall -Wextra -O0
LDFLAGS = -T ${LINKER_SCRIPT} -nostdlib
INCLUDES = -Iinc

TARGET = youhana_blinky
BUILD_DIR = build


SRC_DIR = src

C_SRCS =  ${wildcard $(SRC_DIR)/*.c}
ASM_SRCS = ${wildcard $(SRC_DIR)/*.s}

C_OBJS   = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(C_SRCS))
ASM_OBJS = $(patsubst $(SRC_DIR)/%.s, $(BUILD_DIR)/%.o, $(ASM_SRCS))
OBJS     = $(ASM_OBJS) $(C_OBJS)


.PHONY: all clean

all: $(BUILD_DIR)/$(TARGET).img

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# .c
$(BUILD_DIR)/%.o:  $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# .s
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.s | $(BUILD_DIR)
	$(AS) -c $< -o $@

# Link
$(BUILD_DIR)/$(TARGET).elf: $(OBJS) ${LINKER_SCRIPT}
	$(LD) $(LDFLAGS) $(OBJS) -o $@

# Image
$(BUILD_DIR)/$(TARGET).img: $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -O binary $< $@



clean:
	rm -rf $(BUILD_DIR)

