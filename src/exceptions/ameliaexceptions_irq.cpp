import amelia.print.printf;
import amelia.exceptions.gic;
import amelia.types;
import amelia.peripherals.system_timer;

static const char *entry_error_messages[] = {
	"SYNC_INVALID_EL1t",   "IRQ_INVALID_EL1t",
	"FIQ_INVALID_EL1t",    "ERROR_INVALID_EL1T",

	"SYNC_INVALID_EL1h",   "IRQ_INVALID_EL1h",
	"FIQ_INVALID_EL1h",    "ERROR_INVALID_EL1h",

	"SYNC_INVALID_EL0_64", "IRQ_INVALID_EL0_64",
	"FIQ_INVALID_EL0_64",  "ERROR_INVALID_EL0_64",

	"SYNC_INVALID_EL0_32", "IRQ_INVALID_EL0_32",
	"FIQ_INVALID_EL0_32",  "ERROR_INVALID_EL0_32"
};

namespace amelia {
extern "C" {
	void show_invalid_entry_message(int type, unsigned long esr, unsigned long address) {
		amelia::tfp_printf("%s, ESR: %x, address: %x\r\n", entry_error_messages[type], esr,
			address);
	}


	auto handle_irq() -> void {
		auto gic = exceptions::GIC();
		u32 ack = gic.gicc_->iar;
		u32 irq = ack & 0x3ff;

		while (irq != 1023) { // 1023 means nothing left to handle.
			if (irq == 97) {
				peripherals::SystemTimer::handler();

				gic.gicc_->eoir = ack;
				ack = gic.gicc_->iar;
				irq = ack & 0x3ff;
			}
		}
	}
}
} // namespace amelia