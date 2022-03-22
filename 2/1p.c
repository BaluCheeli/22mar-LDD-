#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/moduleparam.h>

int myvalue,arr_myvalue[4];
char *myname;
int cb_myvalue;

module_param(myvalue,int,S_IRUSR|S_IWUSR);                 //INTEGER VALUE
module_param(myname,charp,S_IRUSR|S_IWUSR);                //STRING
module_param_array(arr_myvalue,int,NULL,S_IRUSR|S_IWUSR);  //ARRAY OF INTEGERS

#if 0
/*------------------------Module_param_cb()---------------------*/int notify_param(const char *val,const struct kernel_param *kp)
{
int res = param_set_int(val,kp);  //use helper for write variable
if(res==0)
{
printk(KERN_INFO "Call back Function called...\n");
printk(KERN_INFO "New value of cb_myvalue = %d \n",cb_myvalue);
return 0;
}
return -1;
}

const struct kernel_param_ops =
{
.set = &notify_param,    //use our setter ....
.get = &param_get_int,   //....and standard getter
};

module_param_cb(cb_myvalue,&my_param_ops,&cb_myvalue,S_IRUGO|S_IWUSR);
/*--------------------------------------------------------------*/
#endif

/*-----------------Module init function-------------------------*/

static int __init hello_world_init(void)
{
int i;
printk(KERN_INFO "myvalue = %d \n",myvalue);
printk(KERN_INFO "cb_myvalue = %d \n",cb_myvalue);
printk(KERN_INFO "myname = %s \n",myname);

for(i=0;i<(sizeof arr_myvalue/sizeof(int));i++)
{
printk(KERN_INFO "Arr_value[%d] = %d\n",i,arr_myvalue[i]);
}
printk(KERN_INFO "Kernel Module Inserted Succesfully....\n");
return 0;
}

/*---------------------Module Exit Function---------------------*/

static void __exit hello_world_exit(void)
{
printk(KERN_INFO "KErnel Module removed succesfully....\n");
}

module_init(hello_world_init);
module_exit(hello_world_exit);

MODULE_LICENSE("GPL");
MODULE_LICENSE("GPL v2");
MODULE_LICENSE("Dual BSD/GPL");

MODULE_AUTHOR("balu");
MODULE_DESCRIPTION("A Simple module param driver");
MODULE_VERSION("1:0.4");

