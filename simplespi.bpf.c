
#include "vmlinux.h"
#include <bpf/bpf_helpers.h>

char LICENSE[] SEC("license") = "GPL";

SEC("tracepoint/spi/spi_transfer_start")
int transfer_start(struct trace_event_raw_spi_transfer *ctx)
{
    u32 rx = ctx->__data_loc_rx_buf;
    u32 tx = ctx->__data_loc_tx_buf;

    bpf_printk("rx - 0x%x, tx - 0x%x", rx, tx);
    return 0;
}
