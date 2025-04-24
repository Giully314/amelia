// amelia/peripherals/irq_regs.hpp
// PURPOSE: Define registers and values for IRQ.
//
// DESCRIPTION:
//  This file implements register address, defined in the section 7 of the board
//  manual and in the bcm2836-peripherals manual, for interrupts.
//
#pragma once
#include <amelia/hardware/memory_config.hpp>

// Register for current pending interrupts.
#define IRQ_BASIC_PENDING_REG (PERIPHERALS_IRQ_START + 0x200)
#define IRQ_PENDING_REG1 (PERIPHERALS_IRQ_START + 0x204)
#define IRQ_PENDING_REG2 (PERIPHERALS_IRQ_START + 0x208)

#define IRQ_FIQ_CONTROL_REG (PERIPHERALS_IRQ_START + 0x20c)

#define IRQ_ENABLE_REG1 (PERIPHERALS_IRQ_START + 0x210)
#define IRQ_ENABLE_REG2 (PERIPHERALS_IRQ_START + 0x214)

// Local interrupts.
#define IRQ_ENABLE_BASIC_REG (PERIPHERALS_IRQ_START + 0x218)

#define IRQ_DISABLE_REG1 (PERIPHERALS_IRQ_START + 0x21c)
#define IRQ_DISABLE_REG2 (PERIPHERALS_IRQ_START + 0x220)

#define IRQ_DISABLE_BASIC_REG (PERIPHERALS_IRQ_START + 0x224)

// Register pending bits and meaning.
// These values refers to the table in section 7.5 of the peripherals manual.
#define IRQ_SYSTEM_TIMER_0 (1 << 0)
#define IRQ_SYSTEM_TIMER_1 (1 << 1)
#define IRQ_SYSTEM_TIMER_2 (1 << 2)
#define IRQ_SYSTEM_TIMER_3 (1 << 3)

// Auxiliary interrupt (mini uart).
#define IRQ_AUX (1 << 29)
