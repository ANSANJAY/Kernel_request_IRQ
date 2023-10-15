Interrupt Flags
================

IRQF NOBALANCING
-----------------

	Flag to exclude this interrupt from IRQ balancing.
	The purpose of IRQ balancing is to distribute hardware interrupts across processors on a multiprocessor system in order to increase performance

	Setting this flag forbids to set any CPU affinity for the requested interrupt handler.
