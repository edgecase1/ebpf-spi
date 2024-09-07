/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 */

#include <linux/bpf.h>
#include <linux/version.h>
#include <bpf/bpf_helpers.h>

#define DEBUG 1

SEC("cgroup/dev")
int spifilter(struct bpf_cgroup_dev_ctx *ctx)
{
    short type = ctx->access_type & 0xFFFF;
    short access = ctx->access_type >> 16;

#ifdef DEBUG
    char fmt[] = "  %d:%d    \n";

    switch (type) {
    case BPF_DEVCG_DEV_BLOCK:
        fmt[0] = 'b';
        break;
    case BPF_DEVCG_DEV_CHAR:
        fmt[0] = 'c';
        break;
    default:
        fmt[0] = '?';
        break;
    }

    if (access & BPF_DEVCG_ACC_READ)
        fmt[8] = 'r';

    if (access & BPF_DEVCG_ACC_WRITE)
        fmt[9] = 'w';

    if (access & BPF_DEVCG_ACC_MKNOD)
        fmt[10] = 'm';

    bpf_trace_printk(fmt, sizeof(fmt), ctx->major, ctx->minor);
#endif

    if(ctx->major == 153 && // spi
       ctx->minor == 1 &&   // bus number
       (access & BPF_DEVCG_ACC_WRITE))
    {
            return 0; // block write
    }

    return 1;
}

char _license[] SEC("license") = "GPL";