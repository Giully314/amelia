// src/peripherals/ameliaperipherals_uart1.cppm
// PURPOSE: Support auxiliary peripheral uart1.
// DESCRIPTION:
// 

export module amelia.peripherals.uart1;

import amelia.types;
import amelia.peripherals.aux;
import amelia.peripherals.gpio;
import amelia.memory.mmio;

namespace amelia {
namespace peripherals {

export struct MiniUart {
    // This must match the clock in config.txt in the real rpi4.
    inline static constexpr u32 clock = 500'000'000;
    inline static constexpr u32 max_queue = 16 * 1024;

    /// Initialize the mini uart peripheral.
    static auto init() -> void {
        using namespace memory;
        
        // Enable uart1.
        mmio_write(aux::Register::enables, 1);
        mmio_write(aux::Register::mu_ier_reg, 0);
        mmio_write(aux::Register::mu_cntl_reg, 0);
        

        mmio_write(aux::Register::mu_lcr_reg, 3);
        
        mmio_write(aux::Register::mu_mcr_reg, 0);
        mmio_write(aux::Register::mu_ier_reg, 0);

        // Disable interrupts.
        mmio_write(aux::Register::mu_iir_reg, 0xc6);

        mmio_write(aux::Register::mu_baud_reg, aux_mu_baud(115200));
        
        gpio::use_as_alt5(14);
        gpio::use_as_alt5(15);

        // Enable RX/TX.
        mmio_write(aux::Register::mu_cntl_reg, 3); 
    }

    static auto is_write_by_ready() -> bool {
        // The 6 bit of the register signal if the transmit FIFO is empty and the transmitter is idle.
        // TODO: maybe we can use the 5 bit which is used if the FIFO can accept at least 1 byte to be transmitted.
        return memory::mmio_read(aux::Register::mu_lsr_reg) & 0x20;
    }

    
    static auto write(const u8 byte) -> void {
        while (!is_write_by_ready());
        memory::mmio_write(aux::Register::mu_io_reg, byte);
    }

    static auto write(const char *const buffer, const u64 size) -> void {
        for (u64 i = 0; i < size; ++i) {
            write(buffer[i]);
        }
        write('\r');
    }

    static auto read() -> u8;

private:
    constexpr static auto aux_mu_baud(const u32 baud) -> u32 {
        // TODO: possible underflow?
        return static_cast<u32>((clock / (baud * 8)) - 1);
    }
};

} // namespace peripherals
} // namespace amelia
