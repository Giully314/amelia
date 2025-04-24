#include <amelia/hardware/hardware_utils.hpp>
#include <amelia/peripherals/irq.hpp>
#include <amelia/peripherals/mini_uart.hpp>
#include <amelia/peripherals/system_timer.hpp>
#include <amelia/printf.hpp>
#include <amelia/types.hpp>

extern amelia::u32 kernel_img_end;

namespace amelia {

void putc(void *p, char c) {
    MiniUART::send((amelia::byte)c);
}

auto kernel_main(u64 processor_id) -> void {
    // Initialize hardware resources.
    MiniUART::init();
    // For debug purposes.
    init_printf(0, amelia::putc);

    SystemTimer::init();
    IRQController::enable_all_devices();
    IRQController::unmask();

    printf("kernel main start with EL %d\n", get_el());
    printf("End of kernel image: %x\n", kernel_img_end);
    while(true) {
        // printf("waiting\n");
        // MiniUART::send_string("waiting\n");
        delay(100000000);
    }
}
} // namespace amelia

extern "C" {
auto kernel_entry_point(amelia::u64 processor_id) -> void {
    amelia::kernel_main(processor_id);
}

} // extern "C"