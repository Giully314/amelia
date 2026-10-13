// src/exceptions/ameliaexceptions_irq.cppm

export module amelia.exceptions.irq;


namespace amelia {
export extern "C" {
    void irq_enable();
    void irq_disable();
}
} // namespace amelia

