#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/types.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include <linux/slab.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Tarasyuk Yuriy");
MODULE_DESCRIPTION("AK2 Laboratory work 6 - Development of modules Linux Kernel part 1");


static unsigned int number = 1;

module_param(number, uint, S_IRUGO);

MODULE_PARM_DESC(number, "The number of 'Hello World!' outputs to the console ");

struct event_list {
    struct list_head list;
    ktime_t event_time;
};

static struct list_head event_list_head;

static LIST_HEAD(event_list_head);

void new_event(void);

static int __init hello_init(void)
{
    if (number == 0 || (number >= 5 && number <= 10)) {
        printk(KERN_WARNING "Number satisfies the limits - is 0 or from 5 to 10");  
    }

    if (number > 10) {
        printk(KERN_ERR "Number is too large > 10");
        return -EINVAL;
    }
  
    int i;
    for (i = 0; i < number; i++) {
        printk(KERN_EMERG "Hello, World!\n");
        new_event();
    }
  return 0;
}

static void __exit hello_exit(void) {
  struct event_list *md, *tmp;
  list_for_each_entry_safe(md, tmp, &event_list_head, list) {
    printk(KERN_EMERG "Time: %lld\n", md->event_time);
    list_del(&md->list);
    kfree(md);
  }
}

void new_event(void) {
    struct event_list *element = NULL;
    element = kmalloc(sizeof(struct event_list), GFP_KERNEL);
    element->event_time = ktime_get();
    list_add_tail(&element->list, &event_list_head);
}

module_init(hello_init);
module_exit(hello_exit);
