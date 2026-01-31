# Makefile for TM4C123GXL Tiva C Launchpad
# Uses ARM GCC toolchain for direct compilation

# Toolchain
PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc
AS = $(PREFIX)as
LD = $(PREFIX)ld
OBJCOPY = $(PREFIX)objcopy
SIZE = $(PREFIX)size

# Project name
TARGET = blink

# Directories
SRC_DIR = src
BUILD_DIR = build
INC_DIR = inc

# Source files
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/startup.c \
       $(SRC_DIR)/system.c

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Compiler flags
CFLAGS = -mcpu=cortex-m4 \
         -mthumb \
         -mfloat-abi=hard \
         -mfpu=fpv4-sp-d16 \
         -O2 \
         -Wall \
         -Wextra \
         -ffunction-sections \
         -fdata-sections \
         -g \
         -I$(INC_DIR) \
         -DTARGET_IS_TM4C123_RB1

# Linker flags
LDFLAGS = -T$(SRC_DIR)/tm4c123gh6pm.ld \
          -nostartfiles \
          -Wl,--gc-sections \
          -Wl,-Map=$(BUILD_DIR)/$(TARGET).map

# Default target
all: $(BUILD_DIR)/$(TARGET).bin

# Create build directory
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Compile C files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link
$(BUILD_DIR)/$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS)
	$(SIZE) $@

# Create binary
$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -O binary $< $@

# Clean
clean:
	@rm -rf $(BUILD_DIR)

# Flash using OpenOCD (if installed)
flash: $(BUILD_DIR)/$(TARGET).bin
	@echo "Flashing $(TARGET).bin to TM4C123GXL..."
	openocd -f interface/ti-icdi.cfg -f target/tm4c123.cfg -c "program $(BUILD_DIR)/$(TARGET).bin verify reset exit"

# Flash using ELF file
flash-elf: $(BUILD_DIR)/$(TARGET).elf
	@echo "Flashing $(TARGET).elf to TM4C123GXL..."
	openocd -f interface/ti-icdi.cfg -f target/tm4c123.cfg -c "program $(BUILD_DIR)/$(TARGET).elf verify reset exit"

# Help
help:
	@echo "Available targets:"
	@echo "  all     - Build the project"
	@echo "  clean   - Remove build files"
	@echo "  flash   - Flash to board (requires OpenOCD)"
	@echo "  help    - Show this help"

.PHONY: all clean flash help
