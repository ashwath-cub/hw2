
#include<linux/kernel.h>
#include<linux/slab.h>
#include<linux/syscalls.h>
#include<linux/types.h>
#include<linux/gfp.h>
#include<uapi/asm-generic/errno-base.h>     //modified this file to add my own returns that more accurately represent the answer.

#define INT32_SIZE 4

asmlinkage long sys_custom_call(int32_t *us_buffer, size_t size)
{
    uint32_t index, index2;
    int32_t* ks_buffer=NULL;
    int32_t max, temp;
 
    printk(KERN_INFO "A call to sys_custom_call has been made\n");
    
    if(us_buffer==NULL)
    {
         printk(KERN_ALERT "Received null from user.\n");
	 return EINVAL;
    }
    

    ks_buffer = (int32_t*)kmalloc(INT32_SIZE*size, GFP_KERNEL);
    

    if(ks_buffer==NULL)
    {
         printk(KERN_ALERT "Call to kmalloc_array failed-returned NULL.\n");
	 return EKMALLOC;
    }

    printk(KERN_INFO "Dynamically allocated a buffer of size:%lu bytes in kernel space\n", INT32_SIZE*size);

    if(copy_from_user(ks_buffer, us_buffer, INT32_SIZE*size)!=0)
    {
   	 printk(KERN_ALERT "Failed to copy data from user space.\n" );
         return ECOPYU;
    }
 
    printk(KERN_INFO "Initiating a sort on the buffer\n");
    /*this is probably bubble-sort*/
    for(index=0; index<size; index++)
    {    
         
         /*initialise max to the first element in the kernel buffer*/
         max=*(ks_buffer+index);
         /*the array is sorted step by step with every iteration*/
         for(index2=index; index2<size; index2++)
         {
              if(max<*(ks_buffer+index2))
              {
                   /*define new max and swap*/
		   max=*(ks_buffer+index2);
                   temp=*(ks_buffer+index);
                   *(ks_buffer+index)=*(ks_buffer+index2);
                   *(ks_buffer+index2)=temp;
              }
         }
    }
    printk(KERN_INFO "Finished sorting successfully.\n");

    /*copy back to user space*/
    if(copy_to_user(us_buffer, ks_buffer, INT32_SIZE*size)!=0)
    {
	 printk(KERN_ALERT "Failed to copy data back to user space.\n");
         return ECOPYK;
    }
    kfree(ks_buffer); 

    printk(KERN_INFO "sys_custom_call exits successfully.\n");

    return 0;
}
