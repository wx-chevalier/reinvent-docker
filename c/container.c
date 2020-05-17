#define _GNU_SOURCE
#include <errno.h>
#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static char child_stack[1024 * 1024];

int child_main(void *arg) {
  unshare(CLONE_NEWNS);
  umount2("/proc", MNT_DETACH);

  /* Pivot root */
  mount("./rootfs", "./rootfs", "bind", MS_BIND | MS_REC, "");
  mkdir("./rootfs/oldrootfs", 0755);
  syscall(SYS_pivot_root, "./rootfs", "./rootfs/oldrootfs");
  chdir("/");
  umount2("/oldrootfs", MNT_DETACH);
  rmdir("/oldrootfs");

  /* Re-mount procfs */
  mount("proc", "/proc", "proc", 0, NULL);
  mount("sysfs", "/sys", "sysfs", 0, NULL);
  mount("none", "/tmp", "tmpfs", 0, NULL);
  mount("none", "/dev", "tmpfs", MS_NOSUID | MS_STRICTATIME, NULL);

  sethostname("example", 7);
  system("ip link set veth1 up");

  char ip_addr_add[4096];
  snprintf(ip_addr_add, sizeof(ip_addr_add),
           "ip addr add 172.16.0.101/24 dev veth1");
  system(ip_addr_add);
  system("route add default gw 172.16.0.100 veth1");

  char **argv = (char **)arg;
  execvp(argv[0], argv);
  return 0;
}

int main(int argc, char *argv[]) {
  system("ip link add veth0 type veth peer name veth1");
  system("ip link set veth0 up");
  system("brctl addif br0 veth0");
  int flags =
      CLONE_NEWNS | CLONE_NEWUTS | CLONE_NEWPID | CLONE_NEWIPC | CLONE_NEWNET;
  int pid = clone(child_main, child_stack + sizeof(child_stack),
                  flags | SIGCHLD, argv + 1);
  if (pid < 0) {
    fprintf(stderr, "clone failed: %d\n", errno);
    return 1;
  }
  char ip_link_set[4096];
  snprintf(ip_link_set, sizeof(ip_link_set) - 1, "ip link set veth1 netns %d",
           pid);
  system(ip_link_set);
  waitpid(pid, NULL, 0);
  return 0;
}
