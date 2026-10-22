// src/amelia_kernelmain.cppm
// PURPOSE:
// DESCRIPTION:

export module amelia.entry.kernel_main;

import amelia.peripherals.uart1;
import amelia.print.printf;
import amelia.utils;
import amelia.exceptions.irq;
import amelia.types;
import amelia.peripherals.system_timer;
import amelia.exceptions.gic;

export {
    extern "C" {
        
        void putc([[maybe_unused]] void *p, char c) {
            amelia::peripherals::MiniUart::write(c);
        }

        // This function is called at EL2 so there could be problem initializing system resources at this level
        // if we setup only el1 stuff. For example in the irq_vector_init we set only the address vector to the 
        // el1 register, so an exception inside this function would cause nowhere to go.
        void kernel_init() {
            amelia::peripherals::MiniUart::init();
            amelia::init_printf(0, putc);
            
            auto gic = amelia::exceptions::GIC();
            gic.enable();
            
            amelia::peripherals::SystemTimer::init();
            amelia::irq_enable();

            const static char buffer[] = "hello from amelia kernel init!";
            amelia::tfp_printf("%s with exception level %d\n", buffer, amelia::get_el());
        }

        void kernel_main(amelia::u64 core_id) {
            const static char buffer[] = "hello from amelia kernel main!";
            amelia::tfp_printf("%s executing from core %d with exception level %d\n", buffer, core_id, amelia::get_el());
            while (true) {
                amelia::delay(1'000'000'000);
                amelia::tfp_printf("Sleeping...\n");
            }
        }
    }
}