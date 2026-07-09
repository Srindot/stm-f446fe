# ==============================================================================
# One-Shot Bare-Metal Makefile (STM32F446RE)
# ==============================================================================

# --- Toolchain ---
CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

# --- Build Configuration ---
BUILD_DIR = build
TARGET    = $(BUILD_DIR)/led_on

# --- Source & Linker Files ---
SRCS      = main.c startup_stm32f446xx.s
LDSCRIPT  = linker_script.ld

# --- Compiler & Linker Flags ---
CPU       = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16
CFLAGS    = $(CPU) -Wall -g -O0
LDFLAGS   = $(CPU) -T$(LDSCRIPT) -nostartfiles -Wl,-Map=$(TARGET).map

# ==============================================================================
# Build Rules
# ==============================================================================

all: $(TARGET).bin

# The One-Shot Command: Compile and link all sources directly into the .elf
$(TARGET).elf: $(SRCS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

# Extract raw binary for flashing
$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
