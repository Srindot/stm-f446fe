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
# -mcpu=cortex-m4: Specify the CPU core
# -mthumb: Use the Thumb-2 instruction set
# -Wall: Enable all warnings
# -g: Generate debug information
# -O0: No optimization (best for debugging)
CPU      = -mcpu=cortex-m4
FPU      = -mfpu=fpv4-sp-d16 -mfloat-abi=hard
MCU      = $(CPU) -mthumb $(FPU)
CFLAGS   = $(MCU) -Wall -g -O0 -std=c11
CFLAGS  += -I.
ASFLAGS  = $(MCU) -Wall -g

# --- Linker Flags ---
LDFLAGS  = $(MCU) -T$(LINKER_SCRIPT) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -nostartfiles

# --- Build Rules ---

# Default target
all: $(BUILD_DIR)/$(TARGET).elf

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

# Flash the code to the target using openocd
flash: all
	@echo "Flashing to target..."
	openocd -f board/st_nucleo_f4.cfg \
	        -c "program $(BUILD_DIR)/$(TARGET).elf verify reset exit"

.PHONY: all clean flash
