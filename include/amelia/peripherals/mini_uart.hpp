// amelia/peripherals/mini_uart.h
// PURPOSE: Implement basics for mini UART (universal async receiver-transmitter).
//
// DESCRIPTION:
//  The Universal Asynchoronous Receiver-Transmitter is protocol for devices which
//  uses async communication.
//  https://en.wikipedia.org/wiki/Universal_asynchronous_receiver-transmitter
//  The mini UART implementation has smaller FIFO, no control flow and it is more prone to lose
//  data at higher baudrate with respect to the PL011 (UART).
//

#pragma once

#include <amelia/types.hpp>

namespace amelia {

struct MiniUART {
public:
    // Initialize UART section.
    static auto init() -> void;

    // Enable interrupts (transmit and receive) for mini uart.
    static auto enable_irq() -> void;

    // Disable interrupts for mini uart.
    static auto disable_irq() -> void;

    // Handle an interrupt request from mini uart.
    static auto handle_irq() -> void;

    // Send a byte.
    static auto send(byte c) -> void;

    // Receive a byte.
    static auto recv() -> byte;

    // Send a string.
    // Precondition: the string must be null terminated.
    static auto send_string(const char *msg) -> void;
};

} // namespace amelia
