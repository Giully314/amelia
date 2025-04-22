// src/peripherals/mini_uart.cpp

// clang-format off
#include <amelia/peripherals/mini_uart.hpp>
// clang-format on

#include <amelia/hardware/hardware_utils.hpp>
#include <amelia/peripherals/aux.hpp>
#include <amelia/peripherals/gpio.hpp>

namespace amelia {
auto MiniUART::init() -> void {
    u32 selector;

    // This set the gpio14 to alternate function 5 txd1 (transimit data) and gpio15
    // to alternate function 5 rxd (read data).
    // The GPFSEL1 register controls the functionalities of the pins 10-19.
    // See page 102 of the board manual.
    selector = mem_read32(GPFSEL1);
    selector &= ~(7 << 12); // clean gpio 14
    selector |= 2 << 12;    // set alt5 for gpio 14
    selector &= ~(7 << 15); // clean gpio15
    selector |= 2 << 15;    // set alt5 for gpio 15
    mem_write32(GPFSEL1, selector);

    // This set the gpio to neither pull-up/pull-down.
    // Page 101 of the manual.
    mem_write32(GPPUD, 0);
    delay(150);
    mem_write32(GPPUDCLK0, (1 << 14) | (1 << 15));
    delay(150);
    mem_write32(GPPUDCLK0, 0);

    // Exercise 1.1.
    const u32 system_clock_freq = 250; // 250 Mhz
    // Bits/sec (equivalent to baud rate only if 2 symbols are used in the system, in this case 0 and 1).
    const u32 baudrate = 115200;
    const u32 baudrate_reg = ((system_clock_freq / (baudrate * 8)) - 1) & 0xff;

    // Initialize mini UART.
    mem_write32(AUX_ENABLES, 1);                // Enable mini uart (enable register access).
    mem_write32(AUX_MU_CNTL_REG, 0);            // Disable auto cflow control and disable receiver and transmitter for initialization.
    mem_write32(AUX_MU_IER_REG, 0);             // Disable receive and transmit interrupts (temporary).
    mem_write32(AUX_MU_LCR_REG, 0b10000011);    // Enable 8 bit mode and disable DLAB.
    mem_write32(AUX_MU_MCR_REG, 0);             // Set RTS line to be always high.
    mem_write32(AUX_MU_BAUD_REG, baudrate_reg); // Set baud rate register value (270 corresponds to 115200 bits/s, check manual for the computation)
    mem_write32(AUX_MU_CNTL_REG, 3);            // Enable transmitter and receiver.
}

auto MiniUART::send(byte c) -> void {
    // This check if the bit 5 of the data status reg is set, so it can
    // accept atleast one byte to be sent.
    while(!(mem_read32(AUX_MU_LSR_REG) & 0x20));
    mem_write32(AUX_MU_IO_REG, c);
}

auto MiniUART::recv() -> byte {
    // This check if the first bit of the data status reg is set, so it means
    // that the FIFO buffer has at least one byte that can be read.
    while(!(mem_read32(AUX_MU_LSR_REG) & 0x01));
    // Note that the data to be read are in the 8 bits of the register.
    return (byte)(mem_read32(AUX_MU_IO_REG) & 0xff);
}

auto MiniUART::send_string(const char *msg) -> void {
    for(int i = 0; msg[i] != '\0'; ++i) {
        MiniUART::send(msg[i]);
    }
}

auto MiniUART::enable_irq() -> void {
    mem_write32(AUX_MU_IER_REG, 0b1110);
}

auto MiniUART::disable_irq() -> void {
    mem_write32(AUX_MU_IER_REG, 0xffffff00);
}

auto MiniUART::handle_irq() -> void {
    // char c = mini_uart_recv();
    // printf("Some data are being sent.\r\n");
}
} // namespace amelia