#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/delay.h>

#define SHARED_IRQ 12
static int irq = SHARED_IRQ, my_dev_id, irq_counter = 0;
module_param(irq, int, S_IRUGO);

static irqreturn_t my_interrupt(int irq, void *dev_id)
{
	return IRQ_NONE;	/* we return IRQ_NONE because we are just observing */
}

static int __init my_init(void)
{
	int ret;
	ret =  (request_irq
	    (irq, my_interrupt, IRQF_PROBE_SHARED, "my_interrupt", &my_dev_id)); 
	
	if (ret != 0)
	{
	
		pr_info("Failed to reserve irq %d, ret:%d\n", irq, ret);
		return -1;
	}
	pr_info("Successfully loading ISR handler\n");
	return 0;
}

static void __exit my_exit(void)
{
	synchronize_irq(irq);
	free_irq(irq, &my_dev_id);
	pr_info("Successfully unloading,  irq_counter = %d\n", irq_counter);
}

MODULE_LICENSE("GPL");
module_init(my_init);
module_exit(my_exit);
