#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/timer.h>
#include<linux/jiffies.h>
#define TICK_RATE 250
#define REQD_TP 500
#define MS_IN_SEC 1000

MODULE_LICENSE("GPL");

MODULE_DESCRIPTION("A custom module that increments a variable every 500ms and logs it's value to the kernal log");

MODULE_AUTHOR("Ashwath Gundepally");

struct timer_list my_timer;

void handler(unsigned long data)
{
    static int count=0;
    count++;
    printk(KERN_INFO "Number of times the timer has expired %d\n", count);
    mod_timer(&my_timer, (jiffies + 125));
}

static int load_module(void)
{
    printk(KERN_INFO "A custom module has been loaded.\n");
    
    init_timer(&my_timer);
//    my_timer.expires=jiffies + REQD_TP/(MS_IN_SEC/TICK_RATE);
    my_timer.expires=jiffies + 125;
    my_timer.data=0;
    my_timer.function=handler;
    add_timer(&my_timer);
    
//    while(1);

    return 0;
}

static void remove_module(void)
{
    del_timer(&my_timer);
    printk(KERN_INFO "A custom module has been removed\n");
}

module_init(load_module);

module_exit(remove_module);


