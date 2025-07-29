/*
 * startup_stm32f446retx.s
 *
 * Startup file for STM32F446RE devices.
 * Handles Reset, sets up the vector table, and jumps to main().
 */

.syntax unified
.cpu cortex-m4
.thumb

.global g_pfnVectors
.global Default_Handler

/* Entry point of the application */
.section .isr_vector, "a", %progbits
g_pfnVectors:
  .word _estack            /* Top of Stack */
  .word Reset_Handler      /* Reset Handler */
  .word NMI_Handler        /* NMI Handler */
  .word HardFault_Handler  /* Hard Fault Handler */
  /* Add other vectors here if needed, otherwise use Default_Handler */
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0

/* Reset Handler */
.section .text.Reset_Handler
.weak Reset_Handler
.type Reset_Handler, %function
Reset_Handler:
  /* Call the C library startup code to initialize .data and .bss */
  bl SystemInit
  /* Call main */
  bl main
  /* Loop forever if main returns */
  b .

.size Reset_Handler, .-Reset_Handler

/* Dummy SystemInit to satisfy linker */
.section .text.SystemInit
.weak SystemInit
.type SystemInit, %function
SystemInit:
  bx lr
.size SystemInit, .-SystemInit


/* Default handler for interrupts */
.section .text.Default_Handler, "ax", %progbits
Default_Handler:
  b .
.size Default_Handler, .-Default_Handler

/* Weak aliases for other handlers */
.weak NMI_Handler
.thumb_set NMI_Handler,Default_Handler

.weak HardFault_Handler
.thumb_set HardFault_Handler,Default_Handler
