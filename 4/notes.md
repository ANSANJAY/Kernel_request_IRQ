Interrupt Flags
==================

The third parameter, flags of request_irq can be either zero or a bit mask of one or more flags defined in
<linux/interrupt.h>


IRQF_SHARED informs the kernel that the interrupt can be shared with other devices.

If this flag is not set, then if there is already a handler associated with the requested interrupt, the request for interrupt will fail.


request_irq returns -EBUSY which means that the interrupt was already requested by another device driver.

On success it returns 0


