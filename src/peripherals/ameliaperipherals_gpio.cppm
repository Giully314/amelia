// src/peripherals/ameliaperipherals_gpio.cppm
// PUR


export module amelia.peripherlas.gpio;

import amelia.types;
import amelia.peripherals.regs;
import amelia.memory.mmio;

export namespace amelia {
namespace gpio {
    inline constexpr ptr_t base = peripherals::base + 0x00200000;
    inline constexpr ptr_t gpfsel0 =  base + 0x00;


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

} // namespace gpio
} // namespace amelia
