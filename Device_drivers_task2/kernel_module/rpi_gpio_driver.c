#include <linux/init.h>
#include <linux/module.h>

#include <linux/mutex.h>

#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/cdev.h>   

// forward declaration ( per driver stuff )
static struct file_operations rpi_gpio_fops;
static dev_t rpi_gpio_devt;          /// major + base minor
static struct class *rpi_gpio_class; // appears in /sys/class/rpi_gpio



// ======================== per device stuff =====================================

struct rpi_gpio_drvdata
{
    void __iomem *gpio_base; // we be filled by device resources

    // created by driver per device:
    struct cdev cdev;
    struct device *dev;

    char gpio_current_char; // hold the gpio pin value
    struct mutex my_mutex;  // to protect the global variable (gpio_current_char)
};

// ========================  PROBE & REMOVE  ===============================
static int rpi_gpio_probe(struct platform_device *pdev)
{
    struct rpi_gpio_drvdata *drvdata;
    dev_t devno;
    u32 reg;

    // make the kernel allocate zeroed memory for the per device data
    // since it has "devm" it will be cleaned up when the device is removed
    drvdata = devm_kzalloc(&pdev->dev, sizeof(*drvdata), GFP_KERNEL);
    if (!drvdata)
        return -ENOMEM;

    mutex_init(&drvdata->my_mutex);
    drvdata->gpio_current_char = '0';

    // get the GPIO base address (same as using dev_get_platdata() )
    // but not genric void ptr but we access the IORESOURCE_MEM flag
    struct resource *res;

    res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
    if (!res)
        return -ENODEV;

    drvdata->gpio_base = devm_ioremap(&pdev->dev, res->start, resource_size(res));
    if (!drvdata->gpio_base)
        return -ENOMEM;

    // my logic -> setup the gpio 26 pin to output
    reg = ioread32(drvdata->gpio_base + 0x08);
    reg &= ~(7 << 18);
    reg |= (1 << 18);
    iowrite32(reg, drvdata->gpio_base + 0x08);

    // get the devno to use in cdev_add() -> usefull if we will do multiple instances
    devno = MKDEV(MAJOR(rpi_gpio_devt), 0);

    cdev_init(&drvdata->cdev, &rpi_gpio_fops);

    if (cdev_add(&drvdata->cdev, devno, 1))
        return -ENODEV;

    // Create /dev/rpi_gpio node
    drvdata->dev = device_create(rpi_gpio_class, &pdev->dev, devno,
                                 drvdata, "rpi_gpio");
    if (IS_ERR(drvdata->dev))
    {
        cdev_del(&drvdata->cdev);
        return PTR_ERR(drvdata->dev);
    }

    // store the drvdata(per device) in the platform device
    platform_set_drvdata(pdev, drvdata);
    return 0;
}

static int rpi_gpio_remove(struct platform_device *pdev)
{
    struct rpi_gpio_drvdata *drvdata = platform_get_drvdata(pdev);

    // kill the node and clean the sys
    device_destroy(rpi_gpio_class, drvdata->cdev.dev);

    // remove the device from kernel
    cdev_del(&drvdata->cdev);

    // devm_kzalloc, devm_platform_ioremap_resource auto-cleaned
    return 0;
}

// ========================  FILE OPERATIONS  ===============================


static int rpi_gpio_open(struct inode *inode, struct file *file)
{
    struct rpi_gpio_drvdata *drvdata;

    // get and cache the per device data using the indoe of the file
    // container_of() is a macro to handle the type casting
    drvdata = container_of(inode->i_cdev, struct rpi_gpio_drvdata, cdev);
    file->private_data = drvdata;
    return 0;
}



static ssize_t gpio_read(struct file *file, char __user *buf, size_t len, loff_t *ppos)
{
    // get the CACHED device data (we cahced it in open() )
    struct rpi_gpio_drvdata *drvdata = file->private_data;

    mutex_lock(&drvdata->my_mutex);
    if (*ppos != 0)
    {
        mutex_unlock(&drvdata->my_mutex);
        return 0;
    }

    if (copy_to_user(buf, &drvdata->gpio_current_char, 1))
    {
        mutex_unlock(&drvdata->my_mutex);
        return -EFAULT;
    }

    *ppos += 1; // protect against infinite loop by 'cat'

    printk(KERN_INFO "Someone read: %c from gpio pin\n", drvdata->gpio_current_char);

    mutex_unlock(&drvdata->my_mutex);
    return 1; // we only ever return 1 byte
}

static ssize_t gpio_write(struct file *file, const char __user *buf, size_t len, loff_t *ppos)
{
    // get the CACHED device data (we cahced it in open() )
    struct rpi_gpio_drvdata *drvdata = file->private_data;

    mutex_lock(&drvdata->my_mutex);
    // we only take first character and ignore the rest
    if (copy_from_user(&drvdata->gpio_current_char, buf, 1))
    {
        mutex_unlock(&drvdata->my_mutex);
        return -EFAULT;
    }
    // check that it is  0 or 1
    if (drvdata->gpio_current_char != '0' && drvdata->gpio_current_char != '1')
    {
        mutex_unlock(&drvdata->my_mutex);
        return -EINVAL;
    }

    if (drvdata->gpio_current_char == '0')
    {
        iowrite32(1 << 26, (drvdata->gpio_base + 0x28)); // clear bit
    }
    else
    {
        iowrite32(1 << 26, (drvdata->gpio_base + 0x1C)); // set bit
    }

    printk(KERN_INFO "wrote: %c\n", drvdata->gpio_current_char);
    mutex_unlock(&drvdata->my_mutex);
    return len; // return number of bytes taken by kernel (even if we only cared about first byte)
}

// ========================   DRIVER Stuff (not per Device) =========================

// becuase the major number and the class are per driver not per device


static struct file_operations rpi_gpio_fops = {
    .open = rpi_gpio_open,
    .read = gpio_read,
    .write = gpio_write,
};

static struct platform_driver rpi_gpio_driver = {
    .probe = rpi_gpio_probe,
    .remove = rpi_gpio_remove,
    .driver = {
        .name = "rpi-gpio",
    },
};

static int __init rpi_gpio_init(void)
{
    // 1 major number , 1 minor number
    alloc_chrdev_region(&rpi_gpio_devt, 0, 1, "rpi_gpio");

    rpi_gpio_class = class_create( "rpi_gpio");

    return platform_driver_register(&rpi_gpio_driver);
}

static void __exit rpi_gpio_exit(void)
{
    platform_driver_unregister(&rpi_gpio_driver);
    class_destroy(rpi_gpio_class);
    unregister_chrdev_region(rpi_gpio_devt, 1);
}
module_init(rpi_gpio_init);
module_exit(rpi_gpio_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Youhana Beshay");