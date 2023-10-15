#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <linux/module.h>

#define MAX_IRQS 256

static int irqs[MAX_IRQS];
int dev = 1;

static irqreturn_t handler(int irq, void *dev)
{
//	pr_info("irq:%d\n", irq);
	return IRQ_NONE;
}


static int myinit(void)
{
	int ret, i;

	for (i = 0; i < MAX_IRQS; ++i) {
		ret = request_irq(
			i,
			handler,
			IRQF_SHARED,
			"myirqhandler0",
			&dev
		);
		irqs[i] = ret;
		if (ret == -EBUSY)
			pr_err("request_irq failed irq = %d ret = %d\n", i, ret);
	}
	return 0;
}

static void myexit(void)
{
	int i;

	for (i = 0; i < MAX_IRQS; ++i) {
		if (!irqs[i]) {
			free_irq(i, &dev);
		}
	}
}

module_init(myinit)
module_exit(myexit)
MODULE_LICENSE("GPL");
