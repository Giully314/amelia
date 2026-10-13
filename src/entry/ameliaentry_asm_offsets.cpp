// src/entry/ameliaentry_asm_offsets.cpp
// PURPOSE: Export C++ struct sizes and offsets as constants usable from assembly files.
// DESCRIPTION:
//  This file is never linked. It is only compiled to assembly (-S) at build time and the lines emitted by
//  DEFINE are turned by gen_asm_offsets.cmake into `#define NAME value` in `ameliaentry_asm_offsets.h`.
//  The "i" constraint forces the compiler to evaluate the expression at compile time.
//  This is the same technique used by Linux (asm-offsets).

#include <stddef.h>

#include "ameliaentry_exception_frame.hpp"

#define DEFINE(sym, val) asm volatile("\n.ascii \"->" #sym " %0\"" : : "i"(val))

void asm_offsets() {
    DEFINE(S_EXCEPTION_FRAME_SIZE, sizeof(ExceptionFrame));
    DEFINE(S_EXCEPTION_FRAME_SP, offsetof(ExceptionFrame, sp));
}
