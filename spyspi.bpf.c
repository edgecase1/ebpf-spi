////#include "vmlinux.h"


//#include <linux/types.h>
//#include <linux/compiler_types.h>
//


#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include <stdbool.h>

//#include <linux/spi/spi.h>
//#include <linux/device.h>

struct device {
	void *kobj;
	void *parent;
	void *p;
	char *init_name;
};

struct spi_device {    // linux/spi/spi.h
  struct device dev;   // linux/device.h
  void *master;	       // struct spi_master	
  unsigned max_speed_hz;		       // 
  unsigned int chip_select; //u8
};

struct spi_set_cs_args
{
    unsigned short common_type;
    unsigned char common_flags;
    unsigned char common_preempt_count;
    int common_pid;
    
    int bus_num;
    int chip_select;
    unsigned long mode;
    bool enable;
};


struct spi_transfer_start_args
{
    unsigned short common_type;
    unsigned char common_flags;
    unsigned char common_preempt_count;
    int common_pid;
    
    int bus_num;
    int chip_select;
    struct spi_transfer * xfer;
    int len;
    unsigned int rx_buf[4];
    unsigned int tx_buf[4];
};

char LICENSE[] SEC("license") = "GPL";


SEC("raw_tracepoint/spi/spi_controller_idle")
int idle22(struct spi_controller_args *ctx)
{
    bpf_printk("SPI idle!\n");
    return 0;
}

SEC("raw_tracepoint/spi/spi_controller_busy")
int busy22(struct bpf_raw_tracepoint_args *ctx)
{
    bpf_printk("SPI busy!\n");
    return 0;
}

SEC("tracepoint/spi/spi_transfer_start")
int transferstart22(struct spi_transfer_start_args *ctx) //struct spi_message *msg, struct spi_transfer *xfer)
{
    char tx[4];
    bpf_printk("SPI msg start! bus=%d cs=%d xfer=%x", ctx->bus_num, ctx->chip_select, ctx->xfer);
    //bpf_probe_read(&tx, 4, ctx->tx_buf);
    //bpf_printk("payload='%x'", tx);

    return 0;
}

SEC("raw_tracepoint/spi/spi_message_submit")
int submit22(struct spi_message *msg, struct spi_transfer *xfer)
{
    bpf_printk("SPI msg submit!\n");
    return 0;
}

//SEC("raw_tracepoint/spi/spi_set_cs")
SEC("tracepoint/spi/spi_set_cs")
//int spisetcs22(struct spi_device *spi, bool enable)
//int spisetcs22(struct bpf_raw_tracepoint_args *ctx) 
int spisetcs22(struct spi_set_cs_args *ctx) 
{
    //bpf_probe_read(&myspi, sizeof(struct spi_device), (const void *)spi);
    //bpf_probe_read(&myspi, sizeof(struct spi_device), (const void *)spi);
    //bpf_probe_read(&max_speed_hz, sizeof(unsigned int), (const void *)spi->max_speed_hz);
    //bpf_printk("max hz %u", myspi.max_speed_hz); //((struct device)spi->dev).init_name); //.init_name);
    //bpf_printk("chip select %x", spi->chip_select); //((struct device)spi->dev).init_name); //.init_name);
    //bpf_printk("device %s", dev->init_name); //((struct device)spi->dev).init_name); //.init_name);
    bpf_printk("spi_set_cs bus=%d mode=%lu enable=%d\n", ctx->bus_num, ctx->mode, ctx->enable); //((struct device)spi->dev).init_name); //.init_name);
    return 0;
}
