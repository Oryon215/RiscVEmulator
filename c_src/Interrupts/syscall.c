#include "../../headers/cpu.h"
//all syscall includes
#include <sys/stat.h>
#include <sys/sysinfo.h>
#include <linux/futex.h>
#include <sys/random.h>
#include <sys/ioctl.h>
#include <sys/sem.h>
#include <sys/klog.h>
#include <sys/personality.h>
#include <sys/times.h>
#include <sys/timerfd.h>
#include <linux/bpf.h>
#include <sys/prctl.h>
#include <sys/sendfile.h>
#include <linux/kcmp.h>
#include <linux/capability.h>
#include <sys/xattr.h>
#include <keyutils.h>
#include <linux/membarrier.h>
#include <sys/inotify.h>
#include <liburing.h>
#include <sys/ptrace.h>
#include <signal.h>
#include <sys/vfs.h>
#include <sys/wait.h>
#include <sys/fsuid.h>
#include <linux/aio_abi.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <sys/syscall.h>
#include <sys/quota.h>
#include <sys/signalfd.h>
#include <sys/mman.h>
#include <sys/file.h>
#include <linux/perf_event.h>
#include <stdio.h>
#include <linux/kexec.h>
#include <sys/uio.h>
#include <linux/reboot.h>
#include <linux/seccomp.h>
#include <sys/fanotify.h>
#include <sys/msg.h>
#include <sys/eventfd.h>
#include <linux/module.h>
#include <sys/swap.h>
#include <mqueue.h>
#include <sys/epoll.h>
#include <sys/shm.h>
#include <sys/timex.h>
#include <sched.h>



void Syscall_Table(State* s)
{

    switch(s->general_purpose[a0])
        {
        case 0:
            //io_setup undefined
            break;
        case 1:
            //io_destroy undefined
            break;
        case 2:
            //io_submit undefined
            break;
        case 3:
            //io_cancel undefined
            break;
        case 4:
            //io_getevents undefined
            break;
        case 5:
            s->general_purpose[a0] = setxattr((const char*)s->general_purpose[a0], (const char*)s->general_purpose[a1], (const void*)s->general_purpose[a2], (size_t)s->general_purpose[a3], (int)s->general_purpose[a4]);
            break;
        case 6:
            s->general_purpose[a0] = lsetxattr((const char*)s->general_purpose[a0], (const char*)s->general_purpose[a1], (const void*)s->general_purpose[a2], (size_t)s->general_purpose[a3], (int)s->general_purpose[a4]);
            break;
        case 7:
            s->general_purpose[a0] = fsetxattr((int)s->general_purpose[a0], (const char*)s->general_purpose[a1], (const void*)s->general_purpose[a2], (size_t)s->general_purpose[a3], (int)s->general_purpose[a4]);
            break;
        case 8:
            s->general_purpose[a0] = getxattr((const char*)s->general_purpose[a0], (const char*)s->general_purpose[a1], (void*)s->general_purpose[a2], (size_t)s->general_purpose[a3]);
            break;
        case 9:
            s->general_purpose[a0] = lgetxattr((const char*)s->general_purpose[a0], (const char*)s->general_purpose[a1], (void*)s->general_purpose[a2], (size_t)s->general_purpose[a3]);
            break;
        case 10:
            s->general_purpose[a0] = fgetxattr((int)s->general_purpose[a0], (const char*)s->general_purpose[a1], (void*)s->general_purpose[a2], (size_t)s->general_purpose[a3]);
            break;
        case 11:
            s->general_purpose[a0] = listxattr((const char*)s->general_purpose[a0], (char*)s->general_purpose[a1], (size_t)s->general_purpose[a2]);
            break;
        case 12:
            s->general_purpose[a0] = llistxattr((const char*)s->general_purpose[a0], (char*)s->general_purpose[a1], (size_t)s->general_purpose[a2]);
            break;
        case 13:
            s->general_purpose[a0] = flistxattr((int)s->general_purpose[a0], (char*)s->general_purpose[a1], (size_t)s->general_purpose[a2]);
            break;
        case 14:
            s->general_purpose[a0] = removexattr((const char*)s->general_purpose[a0], (const char*)s->general_purpose[a1]);
            break;
        case 15:
            s->general_purpose[a0] = lremovexattr((const char*)s->general_purpose[a0], (const char*)s->general_purpose[a1]);
            break;
        case 16:
            s->general_purpose[a0] = fremovexattr((int)s->general_purpose[a0], (const char*)s->general_purpose[a1]);
            break;
        case 17:
            // undefined
            break;
        case 18:
            //lookup_dcookie undefined
            break;
        case 19:
            //eventfd2 undefined
            break;
        case 20:
            s->general_purpose[a0] = epoll_create1((int)s->general_purpose[a0]);
            break;
        case 21:
            s->general_purpose[a0] = epoll_ctl((int)s->general_purpose[a0], (int)s->general_purpose[a1], (int)s->general_purpose[a2], (struct epoll_event*)s->general_purpose[a3]);
            break;
        case 22:
            s->general_purpose[a0] = epoll_pwait((int)s->general_purpose[a0], (struct epoll_event*)s->general_purpose[a1], (int)s->general_purpose[a2], (int)s->general_purpose[a3], (const sigset_t*)s->general_purpose[a4]);
            break;
        case 23:
            s->general_purpose[a0] = dup((unsigned int)s->general_purpose[a0]);
            break;
        case 24:
            s->general_purpose[a0] = dup3((unsigned int)s->general_purpose[a0], (unsigned int)s->general_purpose[a1], (int)s->general_purpose[a2]);
            break;
        case 25:
            s->general_purpose[a0] = fcntl64((unsigned int)s->general_purpose[a0], (unsigned int)s->general_purpose[a1], (unsigned long)s->general_purpose[a2]);
            break;
        case 26:
            s->general_purpose[a0] = inotify_init1((int)s->general_purpose[a0]);
            break;
        case 27:
            s->general_purpose[a0] = inotify_add_watch((int)s->general_purpose[a0], (const char*)s->general_purpose[a1], (uint32_t)s->general_purpose[a2]);
            break;
        case 28:
            s->general_purpose[a0] = inotify_rm_watch((int)s->general_purpose[a0], (__s32)s->general_purpose[a1]);
            break;
        case 29:
            s->general_purpose[a0] = ioctl((unsigned int)s->general_purpose[a0], (unsigned int)s->general_purpose[a1], (unsigned long)s->general_purpose[a2]);
            break;
        case 30:
            //ioprio_set undefined
            break;
        case 31:
            //ioprio_get undefined
            break;
        case 32:
            s->general_purpose[a0] = flock((unsigned int)s->general_purpose[a0], (unsigned int)s->general_purpose[a1]);
            break;
        case 33:
            s->general_purpose[a0] = mknodat((int)s->general_purpose[a0], (const char*)s->general_purpose[a1], (mode_t)s->general_purpose[a2], (unsigned)s->general_purpose[a3]);
            break;
        case 34:
            s->general_purpose[a0] = mkdirat((int)s->general_purpose[a0], (const char*)s->general_purpose[a1], (mode_t)s->general_purpose[a2]);
            break;
        case 35:
            s->general_purpose[a0] = unlinkat((int)s->general_purpose[a0], (const char*)s->general_purpose[a1], (int)s->general_purpose[a2]);
            break;
        case 36:
            s->general_purpose[a0] = symlinkat((const char*)s->general_purpose[a0], (int)s->general_purpose[a1], (const char*)s->general_purpose[a2]);
            break;
        case 37:
            s->general_purpose[a0] = unlinkat((int)s->general_purpose[a0], (const char*)s->general_purpose[a1], (int)s->general_purpose[a2]);
            break;
        case 38:
            s->general_purpose[a0] = renameat((int)s->general_purpose[a0], (const char*)s->general_purpose[a1], (int)s->general_purpose[a2], (const char*)s->general_purpose[a3]);
            break;
        case 39:
            s->general_purpose[a0] = umount((char*)s->general_purpose[a0], (int)s->general_purpose[a1]);
            break;
        case 40:
            s->general_purpose[a0] = umount((char*)s->general_purpose[a0], (int)s->general_purpose[a1]);
            break;
        case 41:
            s->general_purpose[a0] = pivot_root((const char*)s->general_purpose[a0], (const char*)s->general_purpose[a1]);
            break;
        case 42:
            // not implemented
            break;
        case 43:
            s->general_purpose[a0] = statfs64((const char*)s->general_purpose[a0], (size_t)s->general_purpose[a1], (struct statfs64*)s->general_purpose[a2]);
            break;
        case 44:
            s->general_purpose[a0] = fstatfs64((unsigned int)s->general_purpose[a0], (size_t)s->general_purpose[a1], (struct statfs64*)s->general_purpose[a2]);
            break;
        case 45:
            s->general_purpose[a0] = truncate64((const char*)s->general_purpose[a0], (loff_t)s->general_purpose[a1]);
            break;
        case 46:
            s->general_purpose[a0] = ftruncate64((unsigned int)s->general_purpose[a0], (loff_t)s->general_purpose[a1]);
            break;
        case 47:
            s->general_purpose[a0] = fallocate((int)s->general_purpose[a0], (int)s->general_purpose[a1], (loff_t)s->general_purpose[a2], (loff_t)s->general_purpose[a3]);
            break;
        case 48:
            //faccessat undefined
            break;
        case 49:
            s->general_purpose[a0] = chdir((const char*)s->general_purpose[a0]);
            break;
        case 50:
            s->general_purpose[a0] = fchdir((unsigned int)s->general_purpose[a0]);
            break;
        case 51:
            s->general_purpose[a0] = chroot((const char*)s->general_purpose[a0]);
            break;
        case 52:
            s->general_purpose[a0] = fchmod((unsigned int)s->general_purpose[a0], (mode_t)s->general_purpose[a1]);
            break;
        case 53:
            s->general_purpose[a0] = fchmodat((int)s->general_purpose[a0], (const char*)s->general_purpose[a1], (mode_t)s->general_purpose[a2], (int)s->general_purpose[a3]);
            break;
        case 54:
            s->general_purpose[a0] = fchownat((int)s->general_purpose[a0], (const char*)s->general_purpose[a1], (uid_t)s->general_purpose[a2], (gid_t)s->general_purpose[a3], (int)s->general_purpose[a4]);
            break;
        case 55:
            s->general_purpose[a0] = fchown((unsigned int)s->general_purpose[a0], (uid_t)s->general_purpose[a1], (gid_t)s->general_purpose[a2]);
            break;
        case 56:
            //openat undefined
            break;
        case 57:
            //close undefined
            break;
        case 58:
            s->general_purpose[a0] = vhangup();
            break;
        case 59:
            s->general_purpose[a0] = pipe2((int*)s->general_purpose[a0], (int)s->general_purpose[a1]);
            break;
        case 60:
            s->general_purpose[a0] = quotactl((unsigned int)s->general_purpose[a0], (const char*)s->general_purpose[a1], (id_t)s->general_purpose[a2], (void*)s->general_purpose[a3]);
            break;
        case 61:
            s->general_purpose[a0] = getdents64((unsigned int)s->general_purpose[a0], (struct linux_dirent64*)s->general_purpose[a1], (unsigned int)s->general_purpose[a2]);
            break;
        case 62:
            //llseek undefined
            break;
        case 63:
            s->general_purpose[a0] = read((unsigned int)s->general_purpose[a0], (char*)s->general_purpose[a1], (size_t)s->general_purpose[a2]);
            break;
        case 64:
            s->general_purpose[a0] = write((unsigned int)s->general_purpose[a0], (const char*)s->general_purpose[a1], (size_t)s->general_purpose[a2]);
            break;
        case 65:
            s->general_purpose[a0] = readv((unsigned long)s->general_purpose[a0], (const struct iovec*)s->general_purpose[a1], (unsigned long)s->general_purpose[a2]);
            break;
        case 66:
            s->general_purpose[a0] = writev((unsigned long)s->general_purpose[a0], (const struct iovec*)s->general_purpose[a1], (unsigned long)s->general_purpose[a2]);
            break;
        case 67:
            s->general_purpose[a0] = pread64((unsigned int)s->general_purpose[a0], (char*)s->general_purpose[a1], (size_t)s->general_purpose[a2], (loff_t)s->general_purpose[a3]);
            break;
        case 68:
            s->general_purpose[a0] = pwrite64((unsigned int)s->general_purpose[a0], (const char*)s->general_purpose[a1], (size_t)s->general_purpose[a2], (loff_t)s->general_purpose[a3]);
            break;
        case 69:
            s->general_purpose[a0] = preadv((unsigned long)s->general_purpose[a0], (const struct iovec*)s->general_purpose[a1], (unsigned long)s->general_purpose[a2], (unsigned long)s->general_purpose[a3]);
            break;
        case 70:
            s->general_purpose[a0] = pwritev((unsigned long)s->general_purpose[a0], (const struct iovec*)s->general_purpose[a1], (unsigned long)s->general_purpose[a2], (unsigned long)s->general_purpose[a3]);
            break;
        case 71:
            s->general_purpose[a0] = sendfile64((int)s->general_purpose[a0], (int)s->general_purpose[a1], (loff_t*)s->general_purpose[a2], (size_t)s->general_purpose[a3]);
            break;
        case 72:
            // not implemented
            break;
        case 73:
            // not implemented
            break;
        case 74:
            //signalfd4 undefined
            break;
        case 75:
            s->general_purpose[a0] = vmsplice((int)s->general_purpose[a0], (const struct iovec*)s->general_purpose[a1], (unsigned long)s->general_purpose[a2], (unsigned int)s->general_purpose[a3]);
            break;
        case 76:
            s->general_purpose[a0] = vmsplice((int)s->general_purpose[a0], (const struct iovec*)s->general_purpose[a1], (unsigned long)s->general_purpose[a2], (unsigned int)s->general_purpose[a3]);
            break;
        case 77:
            s->general_purpose[a0] = tee((int)s->general_purpose[a0], (int)s->general_purpose[a1], (size_t)s->general_purpose[a2], (unsigned int)s->general_purpose[a3]);
            break;
        case 78:
            s->general_purpose[a0] = readlinkat((int)s->general_purpose[a0], (const char*)s->general_purpose[a1], (char*)s->general_purpose[a2], (int)s->general_purpose[a3]);
            break;
        case 79:
            //newfstatat undefined
            break;
        case 80:
            //newfstat undefined
            break;
        case 81:
            sync();
            break;
        case 82:
            s->general_purpose[a0] = fsync((unsigned int)s->general_purpose[a0]);
            break;
        case 83:
            s->general_purpose[a0] = fdatasync((unsigned int)s->general_purpose[a0]);
            break;
        case 84:
            s->general_purpose[a0] = sync_file_range((int)s->general_purpose[a0], (loff_t)s->general_purpose[a1], (loff_t)s->general_purpose[a2], (unsigned int)s->general_purpose[a3]);
            break;
        case 85:
            s->general_purpose[a0] = timerfd_create((int)s->general_purpose[a0], (int)s->general_purpose[a1]);
            break;
        case 411:
            s->general_purpose[a0] = timerfd_settime((int)s->general_purpose[a0], (int)s->general_purpose[a1], (const struct __kernel_itimerspec*)s->general_purpose[a2], (struct __kernel_itimerspec*)s->general_purpose[a3]);
            break;
        case 410:
            s->general_purpose[a0] = timerfd_gettime((int)s->general_purpose[a0], (struct __kernel_itimerspec*)s->general_purpose[a1]);
            break;
        case 412:
            s->general_purpose[a0] = utimensat((int)s->general_purpose[a0], (const char*)s->general_purpose[a1], (struct __kernel_timespec*)s->general_purpose[a2], (int)s->general_purpose[a3]);
            break;
        case 89:
            s->general_purpose[a0] = acct((const char*)s->general_purpose[a0]);
            break;
        case 90:
            s->general_purpose[a0] = capget((cap_user_header_t)s->general_purpose[a0], (cap_user_data_t)s->general_purpose[a1]);
            break;
        case 91:
            s->general_purpose[a0] = capset((cap_user_header_t)s->general_purpose[a0], (const cap_user_data_t)s->general_purpose[a1]);
            break;
        case 92:
            s->general_purpose[a0] = personality((unsigned int)s->general_purpose[a0]);
            break;
        case 93:
            exit((int)s->general_purpose[a0]);
            break;
        case 94:
            //exit_group undefined
            break;
        case 95:
            s->general_purpose[a0] = waitid((int)s->general_purpose[a0], (pid_t)s->general_purpose[a1], (struct siginfo*)s->general_purpose[a2], (int)s->general_purpose[a3]);
            break;
        case 96:
            //set_tid_address undefined
            break;
        case 97:
            s->general_purpose[a0] = unshare((unsigned long)s->general_purpose[a0]);
            break;
        case 422:
            //futex undefined
            break;
        case 99:
            //set_robust_list undefined
            break;
        case 100:
            //get_robust_list undefined
            break;
        case 101:
            s->general_purpose[a0] = nanosleep((struct __kernel_timespec*)s->general_purpose[a0], (struct __kernel_timespec*)s->general_purpose[a1]);
            break;
        case 102:
            s->general_purpose[a0] = getitimer((int)s->general_purpose[a0], (struct __kernel_old_itimerval*)s->general_purpose[a1]);
            break;
        case 103:
            s->general_purpose[a0] = setitimer((int)s->general_purpose[a0], (struct __kernel_old_itimerval*)s->general_purpose[a1], (struct __kernel_old_itimerval*)s->general_purpose[a2]);
            break;
        case 104:
            //kexec_load undefined
            break;
        case 105:
            //init_module undefined
            break;
        case 106:
            s->general_purpose[a0] = delete_module((const char*)s->general_purpose[a0], (unsigned int)s->general_purpose[a1]);
            break;
        case 107:
            //timer_create undefined
            break;
        case 408:
            //timer_gettime undefined
            break;
        case 109:
            //timer_getoverrun undefined
            break;
        case 409:
            //timer_settime undefined
            break;
        case 111:
            //timer_delete undefined
            break;
        case 404:
            s->general_purpose[a0] = clock_settime((clockid_t)s->general_purpose[a0], (const struct __kernel_timespec*)s->general_purpose[a1]);
            break;
        case 403:
            s->general_purpose[a0] = clock_gettime((clockid_t)s->general_purpose[a0], (struct __kernel_timespec*)s->general_purpose[a1]);
            break;
        case 406:
            s->general_purpose[a0] = clock_getres((clockid_t)s->general_purpose[a0], (struct __kernel_timespec*)s->general_purpose[a1]);
            break;
        case 407:
            s->general_purpose[a0] = clock_nanosleep((clockid_t)s->general_purpose[a0], (int)s->general_purpose[a1], (const struct __kernel_timespec*)s->general_purpose[a2], (struct __kernel_timespec*)s->general_purpose[a3]);
            break;
        case 116:
            s->general_purpose[a0] = syslog((int)s->general_purpose[a0], (char*)s->general_purpose[a1], (int)s->general_purpose[a2]);
            break;
        case 117:
            s->general_purpose[a0] = ptrace((long)s->general_purpose[a0], (long)s->general_purpose[a1], (unsigned long)s->general_purpose[a2], (unsigned long)s->general_purpose[a3]);
            break;
        case 118:
            s->general_purpose[a0] = sched_setparam((pid_t)s->general_purpose[a0], (struct sched_param*)s->general_purpose[a1]);
            break;
        case 119:
            s->general_purpose[a0] = sched_setscheduler((pid_t)s->general_purpose[a0], (int)s->general_purpose[a1], (struct sched_param*)s->general_purpose[a2]);
            break;
        case 120:
            s->general_purpose[a0] = sched_getscheduler((pid_t)s->general_purpose[a0]);
            break;
        case 121:
            s->general_purpose[a0] = sched_getparam((pid_t)s->general_purpose[a0], (struct sched_param*)s->general_purpose[a1]);
            break;
        case 122:
            s->general_purpose[a0] = sched_setaffinity((pid_t)s->general_purpose[a0], (unsigned int)s->general_purpose[a1], (unsigned long*)s->general_purpose[a2]);
            break;
        case 123:
            s->general_purpose[a0] = sched_getaffinity((pid_t)s->general_purpose[a0], (unsigned int)s->general_purpose[a1], (unsigned long*)s->general_purpose[a2]);
            break;
        case 124:
            s->general_purpose[a0] = sched_yield();
            break;
        case 125:
            s->general_purpose[a0] = sched_get_priority_max((int)s->general_purpose[a0]);
            break;
        case 126:
            s->general_purpose[a0] = sched_get_priority_min((int)s->general_purpose[a0]);
            break;
        case 423:
            s->general_purpose[a0] = sched_rr_get_interval((pid_t)s->general_purpose[a0], (struct __kernel_timespec*)s->general_purpose[a1]);
            break;
        case 128:
            //restart_syscall undefined
            break;
        case 129:
            //kill undefined
            break;
        case 130:
            //tkill undefined
            break;
        case 131:
            s->general_purpose[a0] = tgkill((pid_t)s->general_purpose[a0], (pid_t)s->general_purpose[a1], (int)s->general_purpose[a2]);
            break;
        case 132:
            s->general_purpose[a0] = sigaltstack((const struct sigaltstack*)s->general_purpose[a0], (struct sigaltstack*)s->general_purpose[a1]);
            break;
        case 133:
            //rt_sigsuspend undefined
            break;
        case 134:
            //rt_sigaction undefined
            break;
        case 135:
            //rt_sigprocmask undefined
            break;
        case 136:
            //rt_sigpending undefined
            break;
        case 137:
            //rt_sigtimedwait_time32 undefined
            break;
        case 138:
            //rt_sigqueueinfo undefined
            break;
        case 140:
            s->general_purpose[a0] = setpriority((int)s->general_purpose[a0], (int)s->general_purpose[a1], (int)s->general_purpose[a2]);
            break;
        case 141:
            s->general_purpose[a0] = getpriority((int)s->general_purpose[a0], (int)s->general_purpose[a1]);
            break;
        case 142:
            s->general_purpose[a0] = reboot((int)s->general_purpose[a0], (int)s->general_purpose[a1], (unsigned int)s->general_purpose[a2], (void*)s->general_purpose[a3]);
            break;
        case 143:
            s->general_purpose[a0] = setregid((gid_t)s->general_purpose[a0], (gid_t)s->general_purpose[a1]);
            break;
        case 144:
            s->general_purpose[a0] = setgid((gid_t)s->general_purpose[a0]);
            break;
        case 145:
            s->general_purpose[a0] = setreuid((uid_t)s->general_purpose[a0], (uid_t)s->general_purpose[a1]);
            break;
        case 146:
            s->general_purpose[a0] = setuid((uid_t)s->general_purpose[a0]);
            break;
        case 147:
            s->general_purpose[a0] = setresuid((uid_t)s->general_purpose[a0], (uid_t)s->general_purpose[a1], (uid_t)s->general_purpose[a2]);
            break;
        case 148:
            s->general_purpose[a0] = getresuid((uid_t*)s->general_purpose[a0], (uid_t*)s->general_purpose[a1], (uid_t*)s->general_purpose[a2]);
            break;
        case 149:
            s->general_purpose[a0] = setresgid((gid_t)s->general_purpose[a0], (gid_t)s->general_purpose[a1], (gid_t)s->general_purpose[a2]);
            break;
        case 150:
            s->general_purpose[a0] = getresgid((gid_t*)s->general_purpose[a0], (gid_t*)s->general_purpose[a1], (gid_t*)s->general_purpose[a2]);
            break;
        case 151:
            s->general_purpose[a0] = setfsuid((uid_t)s->general_purpose[a0]);
            break;
        case 152:
            s->general_purpose[a0] = setfsgid((gid_t)s->general_purpose[a0]);
            break;
        case 153:
            s->general_purpose[a0] = times((struct tms*)s->general_purpose[a0]);
            break;
        case 154:
            s->general_purpose[a0] = setpgid((pid_t)s->general_purpose[a0], (pid_t)s->general_purpose[a1]);
            break;
        case 155:
            s->general_purpose[a0] = getpgid((pid_t)s->general_purpose[a0]);
            break;
        case 156:
            s->general_purpose[a0] = getsid((pid_t)s->general_purpose[a0]);
            break;
        case 157:
            s->general_purpose[a0] = setsid();
            break;
        case 158:
            s->general_purpose[a0] = getgroups((int)s->general_purpose[a0], (gid_t*)s->general_purpose[a1]);
            break;
        case 159:
            s->general_purpose[a0] = setgroups((int)s->general_purpose[a0], (gid_t*)s->general_purpose[a1]);
            break;
        case 160:
            //newuname undefined
            break;
        case 161:
            s->general_purpose[a0] = sethostname((char*)s->general_purpose[a0], (int)s->general_purpose[a1]);
            break;
        case 162:
            s->general_purpose[a0] = setdomainname((char*)s->general_purpose[a0], (int)s->general_purpose[a1]);
            break;
        case 163:
            s->general_purpose[a0] = getrlimit((unsigned int)s->general_purpose[a0], (struct rlimit*)s->general_purpose[a1]);
            break;
        case 164:
            s->general_purpose[a0] = setrlimit((unsigned int)s->general_purpose[a0], (struct rlimit*)s->general_purpose[a1]);
            break;
        case 165:
            s->general_purpose[a0] = getrusage((int)s->general_purpose[a0], (struct rusage*)s->general_purpose[a1]);
            break;
        case 166:
            s->general_purpose[a0] = umask((int)s->general_purpose[a0]);
            break;
        case 167:
            s->general_purpose[a0] = prctl((int)s->general_purpose[a0], (unsigned long)s->general_purpose[a1], (unsigned long)s->general_purpose[a2], (unsigned long)s->general_purpose[a3], (unsigned long)s->general_purpose[a4]);
            break;
        case 168:
            s->general_purpose[a0] = getcpu((unsigned*)s->general_purpose[a0], (unsigned*)s->general_purpose[a1], (struct getcpu_cache*)s->general_purpose[a2]);
            break;
        case 169:
            s->general_purpose[a0] = gettimeofday((struct __kernel_old_timeval*)s->general_purpose[a0], (struct timezone*)s->general_purpose[a1]);
            break;
        case 170:
            s->general_purpose[a0] = settimeofday((struct __kernel_old_timeval*)s->general_purpose[a0], (struct timezone*)s->general_purpose[a1]);
            break;
        case 171:
            s->general_purpose[a0] = adjtimex((struct __kernel_timex*)s->general_purpose[a0]);
            break;
        case 172:
            s->general_purpose[a0] = getpid();
            break;
        case 173:
            s->general_purpose[a0] = getppid();
            break;
        case 174:
            s->general_purpose[a0] = getuid();
            break;
        case 175:
            s->general_purpose[a0] = geteuid();
            break;
        case 176:
            s->general_purpose[a0] = getgid();
            break;
        case 177:
            s->general_purpose[a0] = getegid();
            break;
        case 178:
            s->general_purpose[a0] = gettid();
            break;
        case 179:
            s->general_purpose[a0] = sysinfo((struct sysinfo*)s->general_purpose[a0]);
            break;
        case 180:
            //mq_open undefined
            break;
        case 181:
            //mq_unlink undefined
            break;
        case 418:
            //mq_timedsend undefined
            break;
        case 419:
            //mq_timedreceive undefined
            break;
        case 184:
            //mq_notify undefined
            break;
        case 185:
            //mq_getsetattr undefined
            break;
        case 186:
            s->general_purpose[a0] = msgget((key_t)s->general_purpose[a0], (int)s->general_purpose[a1]);
            break;
        case 187:
            //old_msgctl undefined
            break;
        case 188:
            s->general_purpose[a0] = msgrcv((int)s->general_purpose[a0], (struct msgbuf*)s->general_purpose[a1], (size_t)s->general_purpose[a2], (long)s->general_purpose[a3], (int)s->general_purpose[a4]);
            break;
        case 189:
            s->general_purpose[a0] = msgsnd((int)s->general_purpose[a0], (struct msgbuf*)s->general_purpose[a1], (size_t)s->general_purpose[a2], (int)s->general_purpose[a3]);
            break;
        case 190:
            s->general_purpose[a0] = semget((key_t)s->general_purpose[a0], (int)s->general_purpose[a1], (int)s->general_purpose[a2]);
            break;
        case 191:
            s->general_purpose[a0] = semctl((int)s->general_purpose[a0], (int)s->general_purpose[a1], (int)s->general_purpose[a2], (unsigned long)s->general_purpose[a3]);
            break;
        case 420:
            s->general_purpose[a0] = semtimedop((int)s->general_purpose[a0], (struct sembuf*)s->general_purpose[a1], (unsigned)s->general_purpose[a2], (const struct __kernel_timespec*)s->general_purpose[a3]);
            break;
        case 193:
            s->general_purpose[a0] = semop((int)s->general_purpose[a0], (struct sembuf*)s->general_purpose[a1], (unsigned)s->general_purpose[a2]);
            break;
        case 194:
            s->general_purpose[a0] = shmget((key_t)s->general_purpose[a0], (size_t)s->general_purpose[a1], (int)s->general_purpose[a2]);
            break;
        case 195:
            //old_shmctl undefined
            break;
        case 196:
            s->general_purpose[a0] = shmat((int)s->general_purpose[a0], (char*)s->general_purpose[a1], (int)s->general_purpose[a2]);
            break;
        case 197:
            s->general_purpose[a0] = shmdt((char*)s->general_purpose[a0]);
            break;
        case 198:
            s->general_purpose[a0] = socket((int)s->general_purpose[a0], (int)s->general_purpose[a1], (int)s->general_purpose[a2]);
            break;
        case 199:
            s->general_purpose[a0] = socketpair((int)s->general_purpose[a0], (int)s->general_purpose[a1], (int)s->general_purpose[a2], (int*)s->general_purpose[a3]);
            break;
        case 200:
            //bind undefined
            break;
        case 201:
            s->general_purpose[a0] = listen((int)s->general_purpose[a0], (int)s->general_purpose[a1]);
            break;
        case 202:
            s->general_purpose[a0] = accept((int)s->general_purpose[a0], (struct sockaddr*)s->general_purpose[a1], (int*)s->general_purpose[a2]);
            break;
        case 203:
            s->general_purpose[a0] = connect((int)s->general_purpose[a0], (struct sockaddr*)s->general_purpose[a1], (int)s->general_purpose[a2]);
            break;
        case 204:
            s->general_purpose[a0] = getsockname((int)s->general_purpose[a0], (struct sockaddr*)s->general_purpose[a1], (int*)s->general_purpose[a2]);
            break;
        case 205:
            s->general_purpose[a0] = getpeername((int)s->general_purpose[a0], (struct sockaddr*)s->general_purpose[a1], (int*)s->general_purpose[a2]);
            break;
        case 206:
            s->general_purpose[a0] = sendto((int)s->general_purpose[a0], (void*)s->general_purpose[a1], (size_t)s->general_purpose[a2], (unsigned)s->general_purpose[a3], (struct sockaddr*)s->general_purpose[a4], (int)s->general_purpose[a5]);
            break;
        case 207:
            s->general_purpose[a0] = recvfrom((int)s->general_purpose[a0], (void*)s->general_purpose[a1], (size_t)s->general_purpose[a2], (unsigned)s->general_purpose[a3], (struct sockaddr*)s->general_purpose[a4], (int*)s->general_purpose[a5]);
            break;
        case 208:
            s->general_purpose[a0] = setsockopt((int)s->general_purpose[a0], (int)s->general_purpose[a1], (int)s->general_purpose[a2], (char*)s->general_purpose[a3], (int)s->general_purpose[a4]);
            break;
        case 209:
            s->general_purpose[a0] = getsockopt((int)s->general_purpose[a0], (int)s->general_purpose[a1], (int)s->general_purpose[a2], (char*)s->general_purpose[a3], (int*)s->general_purpose[a4]);
            break;
        case 210:
            s->general_purpose[a0] = shutdown((int)s->general_purpose[a0], (int)s->general_purpose[a1]);
            break;
        case 211:
            s->general_purpose[a0] = sendmsg((int)s->general_purpose[a0], (struct user_msghdr*)s->general_purpose[a1], (unsigned)s->general_purpose[a2]);
            break;
        case 212:
            s->general_purpose[a0] = recvmsg((int)s->general_purpose[a0], (struct user_msghdr*)s->general_purpose[a1], (unsigned)s->general_purpose[a2]);
            break;
        case 213:
            s->general_purpose[a0] = readahead((int)s->general_purpose[a0], (loff_t)s->general_purpose[a1], (size_t)s->general_purpose[a2]);
            break;
        case 214:
            s->general_purpose[a0] = brk((unsigned long)s->general_purpose[a0]);
            break;
        case 215:
            s->general_purpose[a0] = munmap((unsigned long)s->general_purpose[a0], (size_t)s->general_purpose[a1]);
            break;
        case 216:
            s->general_purpose[a0] = mremap((unsigned long)s->general_purpose[a0], (unsigned long)s->general_purpose[a1], (unsigned long)s->general_purpose[a2], (unsigned long)s->general_purpose[a3], (unsigned long)s->general_purpose[a4]);
            break;
        case 217:
            //add_key undefined
            break;
        case 218:
            //request_key undefined
            break;
        case 219:
            //keyctl undefined
            break;
        case 220:
            //clone undefined
            break;
        case 221:
            //execve undefined
            break;
        case 222:
            //old_mmap undefined
            break;
        case 223:
            //fadvise64_64 undefined
            break;
        case 224:
            s->general_purpose[a0] = swapon((const char*)s->general_purpose[a0], (int)s->general_purpose[a1]);
            break;
        case 225:
            s->general_purpose[a0] = swapoff((const char*)s->general_purpose[a0]);
            break;
        case 226:
            s->general_purpose[a0] = mprotect((unsigned long)s->general_purpose[a0], (size_t)s->general_purpose[a1], (unsigned long)s->general_purpose[a2]);
            break;
        case 227:
            s->general_purpose[a0] = msync((unsigned long)s->general_purpose[a0], (size_t)s->general_purpose[a1], (int)s->general_purpose[a2]);
            break;
        case 228:
            s->general_purpose[a0] = mlock((unsigned long)s->general_purpose[a0], (size_t)s->general_purpose[a1]);
            break;
        case 229:
            s->general_purpose[a0] = munlock((unsigned long)s->general_purpose[a0], (size_t)s->general_purpose[a1]);
            break;
        case 230:
            s->general_purpose[a0] = mlockall((int)s->general_purpose[a0]);
            break;
        case 231:
            s->general_purpose[a0] = munlockall();
            break;
        case 232:
            s->general_purpose[a0] = mincore((unsigned long)s->general_purpose[a0], (size_t)s->general_purpose[a1], (unsigned char*)s->general_purpose[a2]);
            break;
        case 233:
            //madvise undefined
            break;
        case 234:
            s->general_purpose[a0] = remap_file_pages((unsigned long)s->general_purpose[a0], (unsigned long)s->general_purpose[a1], (unsigned long)s->general_purpose[a2], (unsigned long)s->general_purpose[a3], (unsigned long)s->general_purpose[a4]);
            break;
        case 235:
            //mbind undefined
            break;
        case 236:
            //get_mempolicy undefined
            break;
        case 237:
            //set_mempolicy undefined
            break;
        case 238:
            //migrate_pages undefined
            break;
        case 239:
            //move_pages undefined
            break;
        case 240:
            //rt_tgsigqueueinfo undefined
            break;
        case 241:
            //perf_event_open undefined
            break;
        case 242:
            s->general_purpose[a0] = accept4((int)s->general_purpose[a0], (struct sockaddr*)s->general_purpose[a1], (int*)s->general_purpose[a2], (int)s->general_purpose[a3]);
            break;
        case 243:
            //recvmmsg_time32 undefined
            break;
        case 260:
            s->general_purpose[a0] = wait4((pid_t)s->general_purpose[a0], (int*)s->general_purpose[a1], (int)s->general_purpose[a2], (struct rusage*)s->general_purpose[a3]);
            break;
        case 261:
            s->general_purpose[a0] = prlimit64((pid_t)s->general_purpose[a0], (unsigned int)s->general_purpose[a1], (const struct rlimit64*)s->general_purpose[a2], (struct rlimit64*)s->general_purpose[a3]);
            break;
        case 262:
            s->general_purpose[a0] = fanotify_init((unsigned int)s->general_purpose[a0], (unsigned int)s->general_purpose[a1]);
            break;
        case 263:
            s->general_purpose[a0] = fanotify_mark((int)s->general_purpose[a0], (unsigned int)s->general_purpose[a1], (uint64_t)s->general_purpose[a2], (int)s->general_purpose[a3], (const char*)s->general_purpose[a4]);
            break;
        case 264:
            s->general_purpose[a0] = name_to_handle_at((int)s->general_purpose[a0], (const char*)s->general_purpose[a1], (struct file_handle*)s->general_purpose[a2], (int*)s->general_purpose[a3], (int)s->general_purpose[a4]);
            break;
        case 265:
            s->general_purpose[a0] = open_by_handle_at((int)s->general_purpose[a0], (struct file_handle*)s->general_purpose[a1], (int)s->general_purpose[a2]);
            break;
        case 405:
            s->general_purpose[a0] = clock_adjtime((clockid_t)s->general_purpose[a0], (struct __kernel_timex*)s->general_purpose[a1]);
            break;
        case 267:
            s->general_purpose[a0] = syncfs((int)s->general_purpose[a0]);
            break;
        case 268:
            s->general_purpose[a0] = setns((int)s->general_purpose[a0], (int)s->general_purpose[a1]);
            break;
        case 269:
            s->general_purpose[a0] = sendmmsg((int)s->general_purpose[a0], (struct mmsghdr*)s->general_purpose[a1], (unsigned int)s->general_purpose[a2], (unsigned)s->general_purpose[a3]);
            break;
        case 270:
            s->general_purpose[a0] = process_vm_readv((pid_t)s->general_purpose[a0], (const struct iovec*)s->general_purpose[a1], (unsigned long)s->general_purpose[a2], (const struct iovec*)s->general_purpose[a3], (unsigned long)s->general_purpose[a4], (unsigned long)s->general_purpose[a5]);
            break;
        case 271:
            s->general_purpose[a0] = process_vm_writev((pid_t)s->general_purpose[a0], (const struct iovec*)s->general_purpose[a1], (unsigned long)s->general_purpose[a2], (const struct iovec*)s->general_purpose[a3], (unsigned long)s->general_purpose[a4], (unsigned long)s->general_purpose[a5]);
            break;
        case 272:
            //kcmp undefined
            break;
        case 273:
            //finit_module undefined
            break;
        case 274:
            //sched_setattr undefined
            break;
        case 275:
            //sched_getattr undefined
            break;
        case 276:
            s->general_purpose[a0] = renameat2((int)s->general_purpose[a0], (const char*)s->general_purpose[a1], (int)s->general_purpose[a2], (const char*)s->general_purpose[a3], (unsigned int)s->general_purpose[a4]);
            break;
        case 277:
            //seccomp undefined
            break;
        case 278:
            s->general_purpose[a0] = getrandom((char*)s->general_purpose[a0], (size_t)s->general_purpose[a1], (unsigned int)s->general_purpose[a2]);
            break;
        case 279:
            s->general_purpose[a0] = memfd_create((const char*)s->general_purpose[a0], (unsigned int)s->general_purpose[a1]);
            break;
        case 280:
            //bpf undefined
            break;
        case 281:
            //execveat undefined
            break;
        case 282:
            //userfaultfd undefined
            break;
        case 283:
            //membarrier undefined
            break;
        case 284:
            s->general_purpose[a0] = mlock2((unsigned long)s->general_purpose[a0], (size_t)s->general_purpose[a1], (int)s->general_purpose[a2]);
            break;
        case 285:
            s->general_purpose[a0] = copy_file_range((int)s->general_purpose[a0], (loff_t*)s->general_purpose[a1], (int)s->general_purpose[a2], (loff_t*)s->general_purpose[a3], (size_t)s->general_purpose[a4], (unsigned int)s->general_purpose[a5]);
            break;
        case 286:
            s->general_purpose[a0] = preadv2((unsigned long)s->general_purpose[a0], (const struct iovec*)s->general_purpose[a1], (unsigned long)s->general_purpose[a2], (unsigned long)s->general_purpose[a3], (unsigned long)s->general_purpose[a4]);
            break;
        case 287:
            s->general_purpose[a0] = pwritev2((unsigned long)s->general_purpose[a0], (const struct iovec*)s->general_purpose[a1], (unsigned long)s->general_purpose[a2], (unsigned long)s->general_purpose[a3], (unsigned long)s->general_purpose[a4]);
            break;
        case 288:
            s->general_purpose[a0] = pkey_mprotect((unsigned long)s->general_purpose[a0], (size_t)s->general_purpose[a1], (unsigned long)s->general_purpose[a2], (int)s->general_purpose[a3]);
            break;
        case 289:
            s->general_purpose[a0] = pkey_alloc((unsigned long)s->general_purpose[a0], (unsigned long)s->general_purpose[a1]);
            break;
        case 290:
            s->general_purpose[a0] = pkey_free((int)s->general_purpose[a0]);
            break;
        case 291:
            s->general_purpose[a0] = statx((int)s->general_purpose[a0], (const char*)s->general_purpose[a1], (unsigned)s->general_purpose[a2], (unsigned)s->general_purpose[a3], (struct statx*)s->general_purpose[a4]);
            break;
        case 416:
            //io_pgetevents undefined
            break;
        case 293:
            //rseq undefined
            break;
        case 294:
            //kexec_file_load undefined
            break;
        case 424:
            //pidfd_send_signal undefined
            break;
        case 425:
            //io_uring_setup undefined
            break;
        case 426:
            //io_uring_enter undefined
            break;
        case 427:
            //io_uring_register undefined
            break;
        case 428:
            //open_tree undefined
            break;
        case 429:
            //move_mount undefined
            break;
        case 430:
            //fsopen undefined
            break;
        case 431:
            //fsconfig undefined
            break;
        case 432:
            //fsmount undefined
            break;
        case 433:
            //fspick undefined
            break;
        case 434:
            //pidfd_open undefined
            break;
        case 435:
            //clone3 undefined
            break;
        case 436:
            //close_range undefined
            break;
        case 437:
            //openat2 undefined
            break;
        case 438:
            //pidfd_getfd undefined
            break;
        case 439:
            //faccessat2 undefined
            break;
        case 440:
            //process_madvise undefined
            break;
    }
}
