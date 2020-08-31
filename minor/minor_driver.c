#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>		// file_operations 포인터 함수
#include <linux/uaccess.h>	// copy_to_user()
#include <linux/slab.h>		// kmalloc()

#define MAJOR_DEV_NAME  "major_dev"
#define MAJOR_DEV_NUM   200

static int minor1_open(struct inode *inode, struct file *file)
{
   printk("minor1_open\n");

   return 0;
}

static ssize_t minor1_read(struct file *file, char *buf, size_t count, loff_t *f_pos)
{
   char *buff;
   int err;

   buff = kmalloc(count, GFP_KERNEL);

   if(buff == NULL)
   {
      printk("kmalloc error\n");

      return 0;
   }

   sprintf(buff, "KERNEL DATA");

   err = copy_to_user(buf, buff, count);

   if(err != 0)
   {
      printk("copy_to_user error\n");

      kfree(buff);

      return err;
   }

   printk("minor1_read -> count: %d, f_pos: %lld\n", count, *f_pos);

   kfree(buff);

   return 0;
}

static int minor1_close(struct inode *inode, struct file *file)
{
   printk("minor1_close\n");

   return 0;
}

struct file_operations minor1_fops = {
.owner = THIS_MODULE,
.open = minor1_open,
.read = minor1_read,
.release = minor1_close,
};

static int minor2_open(struct inode *inode, struct file *file)
{
   printk("minor2_open\n");

   return 0;
}

static ssize_t minor2_write(struct file *file, const char *buf, size_t count, loff_t *f_pos)
{
   char *buff;
   int err;

   buff = kmalloc(count, GFP_KERNEL);

   if(buff == NULL)
   {
      printk("kmalloc error\n");

      return 0;
   }

   err = copy_from_user(buff, buf, count);

   if(err != 0)
   {
      printk("copy_from_user error\n");

      kfree(buff);

      return err;
   }

   printk("minor2_write -> buff: %s, count: %d, f_pos: %lld\n", buff, count, *f_pos);

   kfree(buff);

   return 0;
}
static int minor2_close(struct inode *inode, struct file *file)
{
   printk("minor2_close\n");

   return 0;
}

struct file_operations minor2_fops = {
.owner = THIS_MODULE,
.open = minor2_open,
.write = minor2_write,
.release = minor2_close,
};

static int major_open(struct inode *inode, struct file *file)
{
   printk("major_open\n");

   switch(MINOR(inode->i_rdev))
   {
      case 1:
         file->f_op = &minor1_fops;
         break;
      case 2:
         file->f_op = &minor2_fops;
         break;
      default:
         return -ENXIO;
   }

   if(file->f_op && file->f_op->open)
   {
      return file->f_op->open(inode, file);
   }

   return 0;
}

struct file_operations major_fops = {
.owner = THIS_MODULE,
.open = major_open,
};

int minor_init(void)
{
   int err;

   printk("minor_init\n");

   err = register_chrdev(MAJOR_DEV_NUM, MAJOR_DEV_NAME, &major_fops);

   if(err < 0)
   {
      printk("register_chrdev error\n");

      return err;
   }

   return 0;
}

void minor_exit(void)
{
   printk("minor_exit\n");

   unregister_chrdev(MAJOR_DEV_NUM, MAJOR_DEV_NAME);
}

module_init(minor_init);
module_exit(minor_exit);

MODULE_AUTHOR("icjk1003@gmail.com");
MODULE_LICENSE("GPL");
