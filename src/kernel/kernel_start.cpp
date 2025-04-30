#include <amelia/ds/dl_list.hpp>
#include <amelia/hardware/hardware_utils.hpp>
#include <amelia/memory/page_allocator.hpp>
#include <amelia/memory/pool_allocator.hpp>
#include <amelia/peripherals/irq.hpp>
#include <amelia/peripherals/mini_uart.hpp>
#include <amelia/peripherals/system_timer.hpp>
#include <amelia/printf.hpp>
#include <amelia/types.hpp>

extern amelia::u32 kernel_img_begin;
extern amelia::u32 kernel_img_end;
extern amelia::u32 mem_beg;
extern amelia::u32 kernel_boot;

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
    printf("kernel image: %x\n%x\n%x\n", &kernel_img_begin, &kernel_img_end, &kernel_boot);

    PageAllocator pg_alloc;
    auto block = pg_alloc.allocate();
    PoolAllocator pool_alloc{block, 24, 8};

    printf("block start: %x\n", block.data);

    auto obj1 = pool_alloc.allocate();
    auto obj2 = pool_alloc.allocate();
    auto obj3 = pool_alloc.allocate();
    printf("obj1 start: %x\n", obj1.data);
    printf("obj2 start: %x\n", obj2.data);
    printf("obj3 start: %x\n", obj3.data);

    DLList<i64, PoolAllocator> list{pool_alloc};

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