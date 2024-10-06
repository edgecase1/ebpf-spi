.PHONY: all

block.bpf.o: block.bpf.c vmlinux.h
	clang -O2 -g -target bpf -I. -D __TARGET_ARCH_aarch64 -D__BPF_TRACING__ -c block.bpf.c -o block.bpf.o

link: link.c
	clang -g -O2 -lbpf -lelf link.c -o link

vmlinux.h:
	bpftool btf dump file /sys/kernel/btf/vmlinux format c > vmlinux.h


