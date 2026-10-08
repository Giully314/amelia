// src/amelia_kernelmain.cppm
// PURPOSE:
// DESCRIPTION:

export module amelia.entry.kernel_main;

import amelia.peripherals.uart1;
import amelia.print.printf;
import amelia.utils;


export {
    extern "C" {
        
        void putc(void *p, char c) {
            amelia::peripherals::MiniUart::write(c);
        }

        void kernel_init() {
            amelia::peripherals::MiniUart::init();
            amelia::init_printf(0, putc);
            const static char buffer[] = "hello from amelia kernel init!";
            amelia::tfp_printf("%s with exception level %d\n", buffer, amelia::get_el());
        }

        void kernel_main() {
            const static char buffer[] = "hello from amelia kernel main!";
            amelia::tfp_printf("%s with exception level %d\n", buffer, amelia::get_el());
            while (true) {}
        }
    }
}