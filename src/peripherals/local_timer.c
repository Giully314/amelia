// src/peripherals/local_timer.c
#include <amelia/peripherals/local_timer.h>
#include <amelia/utils.h>
#include <amelia/printf.h>

static const unsigned int interval = 200000;

void local_timer_init() {
    // Set the time interval and enable it.
    put32(LOCAL_TIMER_CONTROL_STATUS, LOCAL_TIMER_VALUE | interval);
}

void local_timer_handle_irq() {
    // Clean interrupt pending bit.
    put32(LOCAL_TIMER_IRQ_CLEAR_RELOAD, LOCAL_TIMER_INTERRUPT_CLEAR);
    printf("Local timer interrupt.\r\n");
}