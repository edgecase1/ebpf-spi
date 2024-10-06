.PHONY: all load unload trace

spyspi2.bpf.o: spyspi2.bpf.c vmlinux
	clang -O2 -g -target bpf -I. -D __TARGET_ARCH_aarch64 -D__BPF_TRACING__ -c spyspi2.bpf.c -o spyspi2.bpf.o

link2: link2.c
	clang -g -O2 -lbpf -lelf link2.c -o link2

spyspi.bpf.o: spyspi.bpf.c vmlinux
	#clang -g -O2 -target bpf -D__TARGET_ARCH_x86_64 -I . -c spyspi.bpf.c -o spyspi.bpf.o
	clang -O2 -g -target bpf -I. -D __TARGET_ARCH_aarch64 -D__BPF_TRACING__ -c spyspi.bpf.c -o spyspi.bpf.o

load: 
	bpftool prog load spyspi.bpf.o /sys/fs/bpf/spyspi autoattach

vmlinux:
	bpftool btf dump file /sys/kernel/btf/vmlinux format c > vmlinux.h


unload: 
	rm /sys/fs/bpf/spyspi

trace:
	cat /sys/kernel/tracing/trace_pipe

link: link.c
	clang -g -O2 -lbpf -lelf link.c -o link
	



