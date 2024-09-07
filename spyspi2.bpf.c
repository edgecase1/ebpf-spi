#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>

struct spi_transfer_start_args {
    unsigned short common_type;
    unsigned char common_flags;
    unsigned char common_preempt_count;
    int common_pid;

    int bus_num;
    int chip_select;
    struct spi_transfer *xfer;
    int len;
    unsigned int rx_buf;
    unsigned int tx_buf;
};

SEC("tracepoint/spi/spi_transfer_start")
int transfer_start(struct spi_transfer_start_args *ctx) {

    unsigned int tx_offset = ctx->tx_buf & 0xFFFF;
    unsigned int tx_length = ctx->tx_buf >> 16;
    char tx_buffer[256] = {};

    bpf_printk("tx_buf: %d", ctx->tx_buf);
    bpf_printk("tx_length: %u", tx_length);

    if (tx_length > sizeof(tx_buffer)) {
        tx_length = sizeof(tx_buffer);
    }

    bpf_probe_read(&tx_buffer, tx_length, (void *)((char *)ctx + tx_offset));
    bpf_printk("tx_buf content: %s\n", tx_buffer);

    return 0;
}

char _license[] SEC("license") = "GPL";
