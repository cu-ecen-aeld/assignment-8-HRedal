/**
 * @file aesdchar.c
 * @brief Functions and data related to the AESD char driver implementation
 *
 * Based on the implementation of the "scull" device driver, found in
 * Linux Device Drivers example code.
 *
 * @author Dan Walkes
 * @date 2019-10-22
 * @copyright Copyright (c) 2019
 *
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/printk.h>
#include <linux/types.h>
#include <linux/cdev.h>
#include <linux/fs.h> // file_operations
#include <linux/slab.h>
#include "aesdchar.h"
#include "aesd_seekto.h"

int aesd_major =   0; // use dynamic major
int aesd_minor =   0;

MODULE_AUTHOR("Hector Redal");
MODULE_LICENSE("Dual BSD/GPL");

struct aesd_dev aesd_device;

int aesd_open(struct inode *inode, struct file *filp)
{
    PDEBUG("open");

    filp->private_data = container_of(inode->i_cdev, struct aesd_dev, cdevM);
    return 0;
}

int aesd_release(struct inode *inode, struct file *fileP)
{
    PDEBUG("release");

    fileP->private_data = NULL;
    return 0;
}

ssize_t aesd_read(struct file*  filp, 
                  char __user*  buf,
                  size_t        count,
                  loff_t *      f_pos)
{
    ssize_t                         retval              = 0;
    struct aesd_buffer_entry*       theBufferEntry      = NULL;
    // struct aesd_circular_buffer*    theBuffer           = NULL;
    struct aesd_dev*                theAesdDev          = NULL;
    ssize_t                         theOffset           =   0;
    ssize_t                         theBytesNotCopied   = 0;

    PDEBUG("read %zu bytes with offset %lld",count,*f_pos);
    /**
     * TODO: handle read
     */
    if ((filp == NULL )    ||
        (buf == NULL)      ||
        (count == 0))
    {
        PDEBUG("Invalid arguments.");
        return -ERESTARTSYS;
    }

    theAesdDev = (struct aesd_dev*) filp->private_data;
    
    if (mutex_lock_interruptible(&theAesdDev->mutexM) != 0)
    {
        PDEBUG("Failed to get the lock exclusively.");
        return -EINTR;
    }

    
    theBufferEntry = aesd_circular_buffer_find_entry_offset_for_fpos(&(theAesdDev->bufferM),
                                                                     *f_pos,
                                                                     &theOffset);
    if (theBufferEntry == 0)
    {
        mutex_unlock(&theAesdDev->mutexM);
        return retval;
    }

    if (count > (theBufferEntry->size - theOffset))
    {
        count = theBufferEntry->size - theOffset;
    }

    theBytesNotCopied = copy_to_user(buf, (theBufferEntry->buffptr + theOffset), count);
    if(theBytesNotCopied != 0)
    {
        mutex_unlock(&theAesdDev->mutexM);
        return -EFAULT;
    }
    
    retval = count - theBytesNotCopied;
    *f_pos += retval;
    
    mutex_unlock(&theAesdDev->mutexM);

    return retval;
}

ssize_t aesd_write(struct file *filp, const char __user *buf, size_t count,
                loff_t *f_pos)
{
    ssize_t             retval              = -ENOMEM;
    const char*         theBufferEntry      = NULL;
    ssize_t             theBytesNotCopied   = 0;
    struct aesd_dev*    theAesdDev          = (struct aesd_dev*) filp->private_data;

    
    PDEBUG("write %zu bytes with offset %lld",count,*f_pos);
    /**
     * TODO: handle write
     */
    if ((filp == 0) ||
        (buf == 0)  ||
        (f_pos == 0))
    {
        return -ERESTARTSYS;
    }

    if (count == 0)
    {
        return 0;
    }

    if (mutex_lock_interruptible(&(theAesdDev->mutexM)))
    {
        // If lock fails, this is what is returned to return the same thing
        return -EINTR;
    }

    if (theAesdDev->entryM.size == 0)
    {
        theAesdDev->entryM.buffptr = kmalloc(count * sizeof(char), GFP_KERNEL);
    }
    else
    {
        theAesdDev->entryM.buffptr = krealloc(theAesdDev->entryM.buffptr,
                                              (theAesdDev->entryM.size + count) * sizeof(char),
                                              GFP_KERNEL);
    }

    if (theAesdDev->entryM.buffptr == NULL)
    {
        mutex_unlock(&(theAesdDev->mutexM));
        return retval;
    }

    theBytesNotCopied = copy_from_user((void *)(theAesdDev->entryM.buffptr + theAesdDev->entryM.size),
                                       buf,
                                       count);
    retval = count - theBytesNotCopied;
    theAesdDev->entryM.size += retval;

    if (memchr(theAesdDev->entryM.buffptr, '\n', theAesdDev->entryM.size))
    {
        theBufferEntry = aesd_circular_buffer_add_entry(&(theAesdDev->bufferM), &(theAesdDev->entryM));
        if (theBufferEntry == 0)
        {
            kfree(theBufferEntry);
        }
        theAesdDev->entryM.buffptr = NULL;
        theAesdDev->entryM.size = 0;
    }

    mutex_unlock(&theAesdDev->mutexM);

    
    return retval;
}

loff_t aesd_llseek(struct file *fileP, loff_t offset, int whence) {
    struct aesd_dev*            theAesdDev  = fileP->private_data;
    loff_t                      retval      = -EINVAL;
    uint8_t                     index       = 0;
    struct aesd_buffer_entry*   entry       = NULL;
    loff_t                      total_size  = 0;
    PDEBUG("Attempting to adjust offset by: %lld", offset);

    if (fileP == NULL)
    {
      return retval;
    }

    if (mutex_lock_interruptible(&theAesdDev->mutexM)) 
    {
       PDEBUG("Failed to get the mutex.");
       retval = -ERESTARTSYS;
       return retval;
    }
    PDEBUG("Mutex got (locked).");
    
    AESD_CIRCULAR_BUFFER_FOREACH(entry, &theAesdDev->bufferM, index)
    {
       total_size += entry->size;
    }

    retval = fixed_size_llseek(fileP, offset, whence, total_size);

    mutex_unlock(&theAesdDev->mutexM);

    return retval;
}
long aesd_adjust_file_offset(struct file*   filp, 
                             unsigned int   cmd,
                             unsigned int   offset) {

    struct aesd_dev*    dev             = filp->private_data;
    int                 proposed_cmd    = (dev->bufferM.out_offs + cmd) % AESDCHAR_MAX_WRITE_OPERATIONS_SUPPORTED;
    int                 new_fpos        = 0;

    if (dev == NULL)
    {
        return -EINVAL;
    } 
    
    PDEBUG("cmd: %d offset: %d", cmd, offset);
    PDEBUG("current buffer: %d proposed buffer: %d", dev->bufferM.out_offs, proposed_cmd);

    PDEBUG("Locking mutex.");
    // Lock the mutex 
    if (mutex_lock_interruptible(&dev->mutexM)) {
        // Failed to acquire mutex
        PDEBUG("Failed to lock mutex");
        return -ERESTARTSYS; 
    }
    PDEBUG("Mutex locked");

    if (cmd > AESDCHAR_MAX_WRITE_OPERATIONS_SUPPORTED)
    {
        mutex_unlock(&dev->mutexM);
        return -EINVAL;
    }
    else if (dev->bufferM.entry[proposed_cmd].buffptr == NULL)
    {
        mutex_unlock(&dev->mutexM);
        return -EINVAL;
    }
    else if (dev->bufferM.entry[proposed_cmd].size < offset)
    {
        mutex_unlock(&dev->mutexM);
        return -EINVAL;
    }
    else {
        int index;
        for (index = 0; index < cmd; index++) { 
            int entry_index = (index + dev->bufferM.out_offs) % AESDCHAR_MAX_WRITE_OPERATIONS_SUPPORTED;
            new_fpos += dev->bufferM.entry[entry_index].size;
        }
        new_fpos += offset;
    }
    return new_fpos;
}

long aesd_ioctl(struct file*    filp, 
                unsigned int    cmd,
                unsigned long   arg) {
    long                retval = 0;
    struct aesd_seekto  seekto;

    switch(cmd) {
        case AESDCHAR_IOCSEEKTO:
            if (copy_from_user(&seekto, (const void __user *)arg, sizeof(seekto)) != 0) {
                retval = EFAULT;
            }
            else {
                retval = aesd_adjust_file_offset(filp, seekto.write_cmd, seekto.write_cmd_offset);
                filp->f_pos = retval;
            }
            break;
        default:
            // Invalid ioctl command
           retval = -ENOTTY;
           break; 
    }

    return retval;
}

struct file_operations aesd_fops = {
    .owner          = THIS_MODULE,
    .read           = aesd_read,
    .write          = aesd_write,
    .open           = aesd_open,
    .release        = aesd_release,
    .llseek         = aesd_llseek,
    .unlocked_ioctl = aesd_ioctl
};

static int aesd_setup_cdev(struct aesd_dev *dev)
{
    int err, devno = MKDEV(aesd_major, aesd_minor);

    cdev_init(&dev->cdevM, &aesd_fops);
    dev->cdevM.owner = THIS_MODULE;
    dev->cdevM.ops = &aesd_fops;
    err = cdev_add (&dev->cdevM, devno, 1);
    if (err) {
        printk(KERN_ERR "Error %d adding aesd cdev", err);
    }
    return err;
}

int aesd_init_module(void)
{
    dev_t dev      = 0;
    int   result   = 0;
    
    result = alloc_chrdev_region(&dev, aesd_minor, 1,
            "aesdchar");
    aesd_major = MAJOR(dev);
    if (result < 0) {
        printk(KERN_WARNING "Can't get major %d\n", aesd_major);
        return result;
    }
    memset(&aesd_device,0,sizeof(struct aesd_dev));

    /**
     * TODO: initialize the AESD specific portion of the device
     */
    mutex_init(&aesd_device.mutexM);
    aesd_circular_buffer_init(&aesd_device.bufferM);

    result = aesd_setup_cdev(&aesd_device);

    if( result ) {
        unregister_chrdev_region(dev, 1);
    }
    return result;

}

void aesd_cleanup_module(void)
{
    uint8_t                    theIndex;
    struct  aesd_buffer_entry* theEntry = NULL;

    dev_t   devno = MKDEV(aesd_major, aesd_minor);

    cdev_del(&aesd_device.cdevM);

    /**
     * TODO: cleanup AESD specific poritions here as necessary
     */
    AESD_CIRCULAR_BUFFER_FOREACH(theEntry, &aesd_device.bufferM, theIndex) 
    {
        kfree(theEntry->buffptr);
    }
    mutex_destroy(&aesd_device.mutexM);

    unregister_chrdev_region(devno, 1);
}

module_init(aesd_init_module);
module_exit(aesd_cleanup_module);
