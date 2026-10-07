// src/amelia_kernelmain.cppm
// PURPOSE:
// DESCRIPTION:

export module amelia.entry.kernel_main;

import amelia.peripherals.uart1;


export {
    extern "C" { 
        void kernel_main() {

            amelia::peripherals::MiniUart::init();
            const static char buffer[] = "ciao";
            amelia::peripherals::MiniUart::write(buffer, sizeof(buffer));
            while (true) {}
        }
    }
}