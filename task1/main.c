// Main C code for built in LED Code

#define RCC_BASE 0x40023800
#define RCC_AHB1ENR (*(volatile unsigned int *)(RCC_BASE + 0x30))

#define GPIO_BASE 0x40020000
#define GPIOA_MODER (*(volatile unsigned int *)(GPIO_BASE + 0x0))
#define GPIOA_ODR (*(volatile unsigned int *)(GPIO_BASE + 0x14))

void SystemInit(void) {
  // This function is called by the startup assembly code before main().
  // We leave it empty because we are configuring our own hardware.
}

void _init(void) {
  // Dummy function to satisfy the C standard library initialization.
}

int main() {
  RCC_AHB1ENR |= (1 << 0);

  GPIOA_MODER &= ~(3 << 10);

  GPIOA_MODER |= (1 << 10);

  while (1) {
    GPIOA_ODR ^= (1 << 5);
  }

  return 0;
}
