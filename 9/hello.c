#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/sched.h>
#include <asm/current.h>

static int irq1 = 12, dev_id;
static int irq2 = 1;

static irqreturn_t my_interrupt(int irq, void *dev_id)
{
	pr_info("irq:%d\t dev_id:%02x\n", irq, *(int *)dev_id);
	return IRQ_NONE;	/* we return IRQ_NONE because we are just observing */
}

static int __init my_init(void)
{
	dev_id = 0x1234;
	if (request_irq
	    (irq1, my_interrupt, IRQF_SHARED, "my_interrupt", &dev_id)) {
		pr_info("Failed to reserve irq %d\n", irq1);
		return -1;
	}
	if (request_irq
	    (irq2, my_interrupt, IRQF_SHARED, "my_interrupt", &dev_id)) {
		pr_info("Failed to reserve irq %d\n", irq1);
		return -1;
	}
	pr_info("Successfully loading ISR handler\n");
	return 0;
}

static void __exit my_exit(void)
{
	synchronize_irq(irq1);
	synchronize_irq(irq2);
	free_irq(irq1, &dev_id);
	free_irq(irq2, &dev_id);
}

MODULE_LICENSE("GPL");
module_init(my_init);
module_exit(my_exit);
