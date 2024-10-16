#include <linux/module.h>
#include <linux/kfifo.h>
#include <linux/cdev.h>
#include <linux/seq_file.h>
#include <linux/proc_fs.h>

// struct from pchar -- multidev
struct pchar_dev {
    struct kfifo buf;   // device buffer in which data is written/read
    struct cdev cdev;   // char device structure for each device
    dev_t devno;        // major and minor number of the device (optional)
};
#define MAX 32

// device private structs
#define DEVCNT 4
static struct pchar_dev devices[DEVCNT];
static int major;
static int proc_cur;

static void* pchar_seq_start(struct seq_file *s, loff_t *pos) {
	if(proc_cur == DEVCNT)
		return NULL;
	printk(KERN_INFO "%s: pchar_seq_start() called. pos=%lld\n", THIS_MODULE->name, *pos);
	proc_cur = *pos;
	return &devices[proc_cur];
}

static void* pchar_seq_next(struct seq_file *s, void *v, loff_t *pos) {
	proc_cur++;
	*pos = proc_cur;
	printk(KERN_INFO "%s: pchar_seq_next() called. pos=%lld\n", THIS_MODULE->name, *pos);
	if(proc_cur == DEVCNT)
		return NULL;
	return &devices[proc_cur];
}

static void pchar_seq_stop(struct seq_file *s, void *v) {
	printk(KERN_INFO "%s: pchar_seq_stop() called.\n", THIS_MODULE->name);
}

static int pchar_seq_show(struct seq_file *s, void *v) {
	if(v != NULL) {
    	struct pchar_dev *temp = (struct pchar_dev *)v;
		seq_printf(s, "%s: dev=%d/%d\nkfifo size=%d\nkfifo len=%d\nkfifo avail=%d\n\n", 
            THIS_MODULE->name, MAJOR(temp->devno), MINOR(temp->devno),
            kfifo_size(&temp->buf), kfifo_len(&temp->buf), kfifo_avail(&temp->buf));
	}
	return 0;
}

static const struct seq_operations pchar_seq_ops = {
	.start = pchar_seq_start,
	.show  = pchar_seq_show
	.next  = pchar_seq_next,
	.stop  = pchar_seq_stop,
};

static int pchar_proc_open(struct inode *inode, struct file *file)
{
    proc_cur = 0; // start index    
	return seq_open(file, &pchar_seq_ops);
}

// if kernel > 5.6.0
static const struct proc_ops pchar_proc_ops = {
    .proc_open = pchar_proc_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

// if kernel < 5.6.0
/*
static const struct file_operations pchar_proc_ops = {
	.owner   = THIS_MODULE,
	.open    = pchar_proc_open,
	.read    = seq_read,
	.llseek  = seq_lseek,
	.release = seq_release
};
*/

// driver initialization
static __init int pchar_init(void) {
    int i, ret;
    char temp[32];
    struct proc_dir_entry *proc_entry;

    printk(KERN_INFO "%s: pchar_init() called.\n", THIS_MODULE->name);
    // allocate device fifo and initialize devno
    for(i=0; i<DEVCNT; i++) {
        devices[i].devno = MKDEV(major, i);
        ret = kfifo_alloc(&devices[i].buf, MAX, GFP_KERNEL);
        if(ret < 0) {
            printk(KERN_ERR "%s: kfifo_alloc() failed for device %d.\n", THIS_MODULE->name, i);
            return ret;
        }
    }
    printk(KERN_INFO "%s: kfifo_alloc() allocated fifos for %d devices.\n", THIS_MODULE->name, DEVCNT);

    // initialize kfifo with fixed values -- for demo
    strcpy(temp, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    kfifo_in(&devices[0].buf, temp, strlen(temp));

    strcpy(temp, "0123456789");
    kfifo_in(&devices[1].buf, temp, strlen(temp));

    strcpy(temp, "Desd @ Sunbeam");
    kfifo_in(&devices[2].buf, temp, strlen(temp));

    strcpy(temp, "Linux");
    kfifo_in(&devices[3].buf, temp, strlen(temp));

    // create proc entry
    proc_entry = proc_create("pchar", 0444, NULL, &pchar_proc_ops);
    if(IS_ERR(proc_entry)) {
        printk(KERN_ERR "%s: kfifo_alloc() failed for device %d.\n", THIS_MODULE->name, i);
        return -1;
    }
    printk(KERN_INFO "%s: proc_create() created proc entry.\n", THIS_MODULE->name);
    return 0;
}

// driver de-initialization
static __exit void pchar_exit(void) {
    int i;
    // delete proc entry
    remove_proc_entry("pchar", NULL);
    printk(KERN_INFO "%s: remove_proc_entry() removed proc entry.\n", THIS_MODULE->name);

    // free devices fifo
    for(i=DEVCNT-1; i>=0; i--)
        kfifo_free(&devices[i].buf);
    printk(KERN_INFO "%s: kfifo_free() released device fifo for %d devices.\n", THIS_MODULE->name, DEVCNT);
}

module_init(pchar_init);
module_exit(pchar_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("OMKAR KASHID");
MODULE_DESCRIPTION("Sequence file demo.");
