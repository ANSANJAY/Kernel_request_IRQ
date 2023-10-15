Return Value of Interrupt Handlers
===================================

Interrupt handlers return an irqreturn_t value.

IRQ_NONE            interrupt was not from this device or was not handled
IRQ_HANDLED         interrupt was handled by this device
