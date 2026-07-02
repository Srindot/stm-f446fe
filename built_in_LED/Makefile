# Makefile for STM32F446RE Bare-Metal Project

# --- Toolchain ---
PREFIX   = arm-none-eabi-
CC       = $(PREFIX)gcc
AS       = $(PREFIX)as
LD       = $(PREFIX)ld
OBJCOPY  = $(PREFIX)objcopy
GDB      = $(PREFIX)gdb

# --- Project Files ---
TARGET   = led_on
SRC_C    = main.c
SRC_S    = startup_stm32f446retx.s
LINKER_SCRIPT = linker.ld

# --- Build Directories ---
BUILD_DIR = build
OBJS_C    = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRC_C))
OBJS_S    = $(patsubst %.s,$(BUILD_DIR)/%.o,$(SRC_S))
OBJS      = $(OBJS_C) $(OBJS_S)

# --- Compiler Flags ---
CPU      = -mcpu=cortex-m4
FPU      = -mfpu=fpv4-sp-d16 -mfloat-abi=hard
MCU      = $(CPU) -mthumb $(FPU)
CFLAGS   = $(MCU) -Wall -g -O0 -std=c11
CFLAGS  += -I.
ASFLAGS  = $(MCU) -Wall -g

# --- Linker Flags ---
LDFLAGS  = $(MCU) -T$(LINKER_SCRIPT) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -nostartfiles

# --- Build Rules ---

# Default target now builds BOTH the .elf and the .bin
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin

# Rule to generate the raw binary file (.bin) from the (.elf)
$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
	@echo "Extracting raw binary: $@"
	$(OBJCOPY) -O binary $< $@

# Rule to build the final ELF file
$(BUILD_DIR)/$(TARGET).elf: $(OBJS)
	@echo "Linking..."
	$(CC) $(LDFLAGS) $(OBJS) -o $@
	@echo "Build finished: $@"

# Rule to compile C files
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@echo "Compiling C: $<"
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to assemble Assembly files
$(BUILD_DIR)/%.o: %.s
	@mkdir -p $(@D)
	@echo "Assembling: $<"
	$(CC) $(ASFLAGS) -c $< -o $@

# --- Utility Rules ---

# Clean the build directory
clean:
	@echo "Cleaning build files..."
	rm -rf $(BUILD_DIR)

# Flash the code to the target using st-flash
flash: all
	@echo "Flashing to target..."
	sudo st-flash write $(BUILD_DIR)/$(TARGET).bin 0x08000000

.PHONY: all clean flash
