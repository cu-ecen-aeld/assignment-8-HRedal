/*
 * aesdchar.h
 *
 *  Created on: Oct 23, 2019
 *      Author: Dan Walkes
 */

#ifndef AESD_CHAR_DRIVER_AESDCHAR_H_
#define AESD_CHAR_DRIVER_AESDCHAR_H_

#define AESD_DEBUG 1  //Remove comment on this line to enable debug
#include "aesd-circular-buffer.h"

#undef PDEBUG             /* undef it, just in case */
#ifdef AESD_DEBUG
#  ifdef __KERNEL__
     /* This one if debugging is on, and kernel space */
#    define PDEBUG(fmt, args...) printk( KERN_DEBUG "aesdchar: " fmt, ## args)
#  else
     /* This one for user space */
#    define PDEBUG(fmt, args...) fprintf(stderr, fmt, ## args)
#  endif
#else
#  define PDEBUG(fmt, args...) /* not debugging: nothing */
#endif

struct aesd_dev
{
    /**
     * TODO: Add structure(s) and locks needed to complete assignment requirements
     */
    struct cdev                    cdevM;     /* Char device structure      */
    struct mutex                   mutexM;
    struct aesd_circular_buffer    bufferM;
    struct aesd_buffer_entry       entryM;
    size_t                         write_buffer_size; /* Amount of data currently stored in buffer*/
    size_t                         buff_size; //Total size of buff     
};



#endif /* AESD_CHAR_DRIVER_AESDCHAR_H_ */