#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <bpf/libbpf.h>
//#include <bpf/str_error.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/resource.h>
//#include <linux/printk.h>
#define pr_warn printk

static void bump_memlock_rlimit(void)
{
	struct rlimit rlim_new = {
		.rlim_cur	= RLIM_INFINITY,
		.rlim_max	= RLIM_INFINITY,
	};

	if (setrlimit(RLIMIT_MEMLOCK, &rlim_new)) {
		fprintf(stderr, "Failed to increase RLIMIT_MEMLOCK limit!\n");
		exit(1);
	}
}

char *libbpf_strerror_r(int err, char *dst, int len)
{
	int ret = strerror_r(err < 0 ? -err : err, dst, len);
	if (ret)
		snprintf(dst, len, "ERROR: strerror_r(%d)=%d", err, ret);
	return dst;
}

int main(int argc, char **argv)
{
    struct bpf_link *link_fd = NULL;
    struct bpf_program *prog = NULL;
    struct bpf_object *obj = NULL;
    int cgroup_fd;
    char* errmsg;

    bump_memlock_rlimit();

    obj = bpf_object__open_file("./spyspi2.bpf.o", NULL);
    if (libbpf_get_error(obj)) {
        fprintf(stderr, "ERROR: opening BPF object file failed\n");
        return 0;
    }

    /* load BPF program */
    if (bpf_object__load(obj))
    {
        fprintf(stderr, "ERROR: loading BPF object file failed\n");
	goto cleanup;
    }

    prog = bpf_object__find_program_by_name(obj, "msgstart22"); 
    //alternative: prog = bpf_object__next_program(obj, NULL);
    if (!prog) {
        fprintf(stderr, "ERROR: finding a prog in obj file failed\n");
        goto cleanup;
    }


    /* Attach bpf program */
    link_fd = bpf_program__attach_tracepoint(prog, "spi", "spi_message_start");
    if(!link_fd)
    {
    	fprintf(stderr, "ERROR: attaching\n");
    	goto cleanup;
    }
    
    system("/bin/sh");

cleanup:
        bpf_link__destroy(link_fd);
	bpf_object__close(obj);
	return 0;
}
