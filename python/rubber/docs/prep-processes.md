# Linux processes

A process is an operating system concept describing a task with a separate memory space and resources. In Linux, processes are created using the clone() system call, which clones an existing process to create a new process. The clone() call accepts various flags which tell Linux what resources to share/copy with the original process. Usually, the clone() system call is not used directly; instead we use POSIX calls (like fork()) which are implemented in glibc (userspace). In fact, most of the Linux and POSIX interfaces we use are implemented in glibc, not in the kernel.

The fork() call we know and love creates a process by calling clone() with a bunch of flags. Threads are created using the pthread_create() call.

Under the hood, both threads and processes are tasks and are represented by a struct called (surprise surprise) task_struct. task_struct has about 170 fields, and is around 1k size. Some notable fields are: `*user`, pid, tgid, `*files`, `*fs`, `*nsproxy`

- fs_struct `*fs` holds information on current root, working directory, umask, etc.
- pid struct maps processes to one or more tasks

# Processes - fork & exec

Traditionally `*nixs` created new processes by calling the following calls in order:

- fork() - Duplicate the current process, VM is copy-on-write
- exec() - Replace text/data/bss/stack with new program image

After calling exec(), the new process image starts executing from the entrypoint (main function) and the new command line arguments (argv) are passed to it.

- glibc’s fork() and pthread_create() both call clone() syscall
- clone() creates a new task_struct from parent controls resource sharing by flags (e.g. share VM, share/copy fd)
