// src/entry/ameliaentry_exception_frame.hpp
// PURPOSE: Define the layout of the register frame saved on the stack at exception entry.
// DESCRIPTION:
//  C++ only. The assembly code can't see this struct: its size and field offsets are exported to the
//  assembler through the generated header `ameliaentry_asm_offsets.h` (see ameliaentry_asm_offsets.cpp).

#pragma once

#include <stdint.h>


struct ExceptionFrame {
    uint64_t regs[31]; // x0-x30
    uint64_t padding;
    // uint64_t sp;
    // uint64_t elr_el1;
    // uint64_t spsr_el1;
};

static_assert(sizeof(ExceptionFrame) % 16 == 0, "the stack pointer must stay 16 bytes aligned");
