#include "vmlinux.h"
//#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
//#include <linux/spi/spi.h>

char LICENSE[] SEC("license") = "GPL";

struct spi_controller_args {
   uint16_t common_type;
	uint8_t common_flags;
	uint8_t common_preempt_count;
	int32_t common_pid;
	int bus_num;
};

SEC("tracepoint/spi/spi_controller_idle")
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

SEC("raw_tracepoint/spi/spi_message_start")
int msgstart22(struct spi_message *msg, struct spi_transfer *xfer)
{
    bpf_printk("SPI msg start!\n");
    return 0;
}
