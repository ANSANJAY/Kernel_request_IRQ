/proc/irq
============

Starting with the 2.4 kernel, Linux has gained the ability to assign certain IRQs to specific processors (or groups of processors).  This is known as SMP IRQ affinity

The interrupt affinity value for a particular IRQ number is stored in the associated /proc/irq/IRQ_NUMBER/smp_affinity file, which can be viewed and modified by the root user. 

The value stored in this file is a hexadecimal bit-mask representing all CPU cores in the system
/proc/irq/irq_number/smp_affinity_list contains cpu list

Example: 

$ cat /proc/irq/1/smp_affinity

00000000,00000000,00000000,00000038

This mean keyboard interrupt can occur in CPU 3, 4, 5


Setting this value to 1, as follows, means that only CPU 0 can service this interrupt:

# echo 1 >/proc/irq/1/smp_affinity
# cat /proc/irq/1/smp_affinity
1

Commas can be used to delimit smp_affinity values for discrete 32-bit groups. This is required on systems with more than 32 cores. 

/proc/irq/default_smp_affinity specifies default affinity mask that applies to all non-active IRQs.

Once IRQ is allocated/activated its affinity bitmask will be set to the default mask

