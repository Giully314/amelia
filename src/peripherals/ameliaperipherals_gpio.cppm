// src/peripherals/ameliaperipherals_gpio.cppm
// PURPOSE: Define the GPIO (general purpose IO) hardware.
//
// DESCRIPTION:
//         
// IMPLEMENTATION DETAILS:
//  The reason I use structs and not enum for the registers and other stuff is because we need the value directly to be used as a number
//  and doing the conversion from enum to number is just boilerplate and make the code harder to be read.


export module amelia.peripherals.gpio;

import amelia.types;
import amelia.peripherals.regs;
import amelia.memory.mmio;

export namespace amelia {
namespace gpio {

    /// Contains the GPIO registers.
    struct Register {
        inline static constexpr ptr_t base = peripherals::base + 0x00200000;
        inline static constexpr ptr_t gpsel0 =  base + 0x00;
        inline static constexpr ptr_t gpset0 = base + 0x1c;
        inline static constexpr ptr_t gpclr0 = base + 0x28;
        inline static constexpr ptr_t pup_pdn_cntrl_reg0 = base + 0xe4;
    };

    /// Function values.
    struct Function {
        inline static constexpr ptr_t alt5 = 2;
    };

    /// Pull value can be low or high.
    struct Pull {
        inline static constexpr u32 low = 0;
        inline static constexpr u32 high = 1;
    };



    /// Write a `value` to `pin_number` in the register starting at `base` address.
    auto write(const u32 pin_number, const u32 value, const u32 base, const u32 field_size) -> bool {
        constexpr u32 gpio_max_pin = 58;
        const u32 field_mask = (1 << field_size) - 1;

        if (pin_number > gpio_max_pin) return false;
        if (value > field_mask) return false;

        const u32 num_fields = 32 / field_size;
        const u32 reg = base + ((pin_number / num_fields) * 4);
        const u32 shift = (pin_number % num_fields) * field_size;

        u32 current_value = memory::mmio_read(reg);
        current_value &= ~(field_mask << shift);
        current_value |= value << shift;
        memory::mmio_write(reg, current_value);

        return true;
    }

    /// Write to register gpset0 a value of 1 bit.
    auto set(const u32 pin_number, const u32 value) -> bool {
        return write(pin_number, value, Register::gpset0, 1);
    }

    /// Write to register gpclr0 a value of 1 bit.
    auto clear(const u32 pin_number, const u32 value) -> bool {
        return write(pin_number, value, Register::gpclr0, 1);
    }

    /// Write to register pup_pdn_cntrl_reg0 a value of 2 bits.
    auto pull(const u32 pin_number, const u32 value) -> bool {
        return write(pin_number, value, Register::pup_pdn_cntrl_reg0, 2);
    }

    /// Write to register gpset0 a value of 3 bits.
    auto function(const u32 pin_number, const u32 value) -> bool {
        return write(pin_number, value, Register::gpsel0, 3);
    }


    /// Use the pin number as a alt5 function.
    auto use_as_alt5(const u32 pin_number) -> void {
        pull(pin_number, Pull::low);
        function(pin_number, Function::alt5);
    }

} // namespace gpio
} // namespace amelia
