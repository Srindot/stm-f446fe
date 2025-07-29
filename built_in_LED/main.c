/**
 * main.c
 * * Bare-metal C code to turn on the user LED (PA5) on a
 * Nucleo-F446RE board.
 */

// Memory-mapped register addresses for STM32F446RE
// Found in the device reference manual.

// RCC (Reset and Clock Control) registers
#define RCC_BASE      0x40023800
#define RCC_AHB1ENR   (*(volatile unsigned int*)(RCC_BASE + 0x30))

// GPIOA (General Purpose I/O Port A) registers
#define GPIOA_BASE    0x40020000
#define GPIOA_MODER   (*(volatile unsigned int*)(GPIOA_BASE + 0x00))
#define GPIOA_ODR     (*(volatile unsigned int*)(GPIOA_BASE + 0x14))

int main(void) {
    // 1. Enable the clock for GPIOA in the RCC AHB1 peripheral clock enable register.
    //    The bit for GPIOA is the first bit (bit 0).
    //    We set the bit to 1 to enable it.
    RCC_AHB1ENR |= (1 << 0);

    // 2. Configure the GPIO pin PA5 as a General Purpose Output.
    //    The GPIOA_MODER register controls the mode for each pin. Two bits are used per pin.
    //    For PA5, we need to configure bits 11 and 10.
    //    - 00: Input (reset state)
    //    - 01: General purpose output mode
    //    - 10: Alternate function mode
    //    - 11: Analog mode
    //    We want to set it to '01'. First, we clear bits 11 and 10, then set bit 10.
    GPIOA_MODER &= ~(3 << 10); // Clear bits 11 & 10 (3 is binary 11)
    GPIOA_MODER |=  (1 << 10); // Set bit 10 to 1, making the mode '01'

    // 3. Turn the LED on.
    //    The GPIOA_ODR (Output Data Register) controls the output state.
    //    Setting the 5th bit (for PA5) to 1 will drive the pin HIGH.
    GPIOA_ODR |= (1 << 5);

    // 4. Loop forever.
    //    The program should not exit.
    while(1) {
        // Do nothing. The LED is on.
    }

    return 0; // This line is never reached.
}
