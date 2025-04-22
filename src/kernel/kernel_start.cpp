#include <amelia/hardware/hardware_utils.hpp>
#include <amelia/peripherals/mini_uart.hpp>
#include <amelia/printf.hpp>
#include <amelia/types.hpp>

namespace amelia {

void putc(void *p, char c) {
    MiniUART::send((amelia::byte)c);
}

auto kernel_main(u64 processor_id) -> void {
    MiniUART::init();
    init_printf(0, amelia::putc);
    printf("kernel main start with EL %d\n", get_el());
    MiniUART::send_string("kernel main start\n");
    while(true) {
        printf("waiting\n");
        // MiniUART::send_string("waiting\n");
        delay(10000000);
    }
}
} // namespace amelia

extern "C" {
auto kernel_entry_point(amelia::u64 processor_id) -> void {
    amelia::kernel_main(processor_id);
}

} // extern "C"