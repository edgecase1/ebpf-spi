
#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include <linux/spi/spi.h>

char LICENSE[] SEC("license") = "GPL";

SEC("tracepoint/spi/spi_controller_idle")
int idle22(struct spi_controller *ctlr)
{
    bpf_printk("SPI idle!\n");
    return 0;
}

SEC("tracepoint/spi/spi_controller_busy")
int busy22(struct spi_controller *ctlr)
{
    bpf_printk("SPI busy!\n");
    return 0;
}

SEC("tracepoint/spi/spi_message_start")
int msgstart22(struct spi_message *msg, struct spi_transfer *xfer)
{
    bpf_printk("SPI msg start!\n");
    return 0;
}
