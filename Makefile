.PHONY: all load unload trace

all: spyspi.bpf.o link spyspi2.bpf.o link2
	echo "all"

spyspi.bpf.o: spyspi.bpf.c vmlinux.h
	clang -g -O2 -target bpf -D__TARGET_ARCH_x86_64 -I . -c spyspi.bpf.c -o spyspi.bpf.o
#	clang -O2 -g -target bpf -I. -D __TARGET_ARCH_arm64 -D__BPF_TRACING__ -c spyspi.bpf.c -o spyspi.bpf.o

simplespi.bpf.o: simplespi.bpf.c vmlinux.h
	clang -g -O2 -target bpf -D__TARGET_ARCH_x86_64 -I . -c simplespi.bpf.c -o simplespi.bpf.o

spyspi2.bpf.o: spyspi2.bpf.c vmlinux.h
	clang -g -O2 -target bpf -D__TARGET_ARCH_x86_64 -I . -c spyspi2.bpf.c -o spyspi2.bpf.o

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
	
link2: link2.c
	clang -g -O2 -lbpf -lelf link2.c -o link2



