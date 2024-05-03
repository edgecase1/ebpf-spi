.PHONY: all load unload trace link

all: spyspi.bpf.o link
	echo "all"

spyspi.bpf.o: spyspi.bpf.c
	clang -g -O2 -target bpf -D__TARGET_ARCH_x86_64 -I . -c spyspi.bpf.c -o spyspi.bpf.o

load: 
	bpftool prog load spyspi.bpf.o /sys/fs/bpf/spyspi autoattach

unload: 
	rm /sys/fs/bpf/spyspi

trace:
	cat /sys/kernel/tracing/trace_pipe

link: link.c
	clang -g -O2 -lbpf -lelf link.c -o link
	



