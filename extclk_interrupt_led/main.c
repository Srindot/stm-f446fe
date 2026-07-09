// Main C code for built in LED Code

#define RCC_BASE 0x40023800
#define RCC_AHB1ENR (*(volatile unsigned int *)(RCC_BASE + 0x30))
#define RCC_CR (*(volatile unsigned int *)(RCC_BASE + 0x00))
#define RCC_CFGR (*(volatile unsigned int *)(RCC_BASE + 0x08))

#define GPIO_BASE 0x40020000
#define GPIOA_MODER (*(volatile unsigned int *)(GPIO_BASE + 0x0))
#define GPIOA_ODR (*(volatile unsigned int *)(GPIO_BASE + 0x14))

// Sys Tick
#define SYS_TICK 0xE000E010
#define SYS_CONTROL (*(volatile unsigned int *)(SYS_TICK + 0x00))
#define SYS_LOAD (*(volatile unsigned int *)(SYS_TICK + 0x04))
#define SYS_VAL (*(volatile unsigned int *)(SYS_TICK + 0x08))

void SystemInit(void) {
  // Function Call for the Linker Script
  //
}

void _init(void) {
  // Dummy function to satisfy the C standard library initialization.
}

void SysTick_Handler(void) { GPIOA_ODR ^= (1 << 5); }

int main() {

  // Turn on the external crystal oscillator
  RCC_CR |= (1 << 16);

  // Wait for the Crystal to stablize
  while ((RCC_CR & (1 << 17)) == 0) {
    // wait
  }

  RCC_CFGR |= (1 << 0);

  while ((RCC_CFGR & (1 << 2)) == 0) {
    // wait
  }

  // LED Registers
  RCC_AHB1ENR |= (1 << 0);

  GPIOA_MODER &= ~(3 << 10);

  GPIOA_MODER |= (1 << 10);

  GPIOA_ODR ^= (1 << 5);

  // SYS TICKS REGISTERS
  SYS_LOAD = 1000000 - 1;
  SYS_VAL = 0;

  SYS_CONTROL = (1 << 0) | (1 << 1) | (1 << 2);
  while (1) {
  }

  return 0;
}
