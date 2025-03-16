// src/peripherals/timer.c
#include <amelia/peripherals/timer.h>
#include <amelia/utils.h>
#include <amelia/printf.h>

// Set the interrupt interval.
const unsigned int interval = 200000;

unsigned int current_value = 0;

// Initialize the timer by setting one of the compare register for 
// interrupt detection.
void timer_init() {
    // Set the first timer interrupt to be after `interval` from current value.
    current_value = get32(SYSTEM_TIMER_CLO);
    current_value += interval;
    put32(SYSTEM_TIMER_C1, current_value);
}

// Handler for a timer interrupt.
void timer_handle_irq() {
    current_value += interval;
    put32(SYSTEM_TIMER_C1, current_value);
    put32(SYSTEM_TIMER_CS, SYSTEM_TIMER_CS_M1);
    printf("Timer interrupt received\r\n");
}