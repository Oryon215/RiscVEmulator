
#include "../../headers/cpu.h"
//all syscall includes
#include <syscall.h>
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
#include <linux/aio_abi.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <sys/eventfd.h>
#include <linux/ioprio.h>
long sys_ni_syscall(void)
{
    return -ENOSYS;
}

void Syscall_Table(State* s){
    printf("Syscall executed. Syscall number:%d\n", s->general_purpose[a7]);
   switch(s->general_purpose[a7])
        {
        case 0:
            s->general_purpose[a7] = syscall(SYS_io_setup, (aio_context_t)s->general_purpose[a0]);
            break;
        case 1:
            s->general_purpose[a7] = syscall(SYS_io_destroy, (aio_context_t)s->general_purpose[a0]);
            break;
        case 2:
            s->general_purpose[a7] = syscall(SYS_io_submit, (aio_context_t)s->general_purpose[a0]);
            break;
        case 3:
            s->general_purpose[a7] = syscall(SYS_io_cancel, (aio_context_t)s->general_purpose[a0]);
            break;
        case 4:
            s->general_purpose[a7] = syscall(SYS_io_getevents, (aio_context_t)s->general_purpose[a0]);
            break;
        case 5:
            s->general_purpose[a7] = setxattr((const char*)&s->memory[s->general_purpose[a0]], (const char*)&s->memory[s->general_purpose[a1]], (const void*)&s->memory[s->general_purpose[a2]], (size_t)s->general_purpose[a3], (int)s->general_purpose[a4]);
            break;
        case 6:
            s->general_purpose[a7] = lsetxattr((const char*)&s->memory[s->general_purpose[a0]], (const char*)&s->memory[s->general_purpose[a1]], (const void*)&s->memory[s->general_purpose[a2]], (size_t)s->general_purpose[a3], (int)s->general_purpose[a4]);
            break;
        case 7:
            s->general_purpose[a7] = fsetxattr((int)s->general_purpose[a0], (const char*)&s->memory[s->general_purpose[a1]], (const void*)&s->memory[s->general_purpose[a2]], (size_t)s->general_purpose[a3], (int)s->general_purpose[a4]);
            break;
        case 8:
            s->general_purpose[a7] = getxattr((const char*)&s->memory[s->general_purpose[a0]], (const char*)&s->memory[s->general_purpose[a1]], (void*)&s->memory[s->general_purpose[a2]], (size_t)s->general_purpose[a3]);
            break;
        case 9:
            s->general_purpose[a7] = lgetxattr((const char*)&s->memory[s->general_purpose[a0]], (const char*)&s->memory[s->general_purpose[a1]], (void*)&s->memory[s->general_purpose[a2]], (size_t)s->general_purpose[a3]);
            break;
        case 10:
            s->general_purpose[a7] = fgetxattr((int)s->general_purpose[a0], (const char*)&s->memory[s->general_purpose[a1]], (void*)&s->memory[s->general_purpose[a2]], (size_t)s->general_purpose[a3]);
            break;
        case 11:
            s->general_purpose[a7] = listxattr((const char*)&s->memory[s->general_purpose[a0]], (char*)&s->memory[s->general_purpose[a1]], (size_t)s->general_purpose[a2]);
            break;
        case 12:
            s->general_purpose[a7] = llistxattr((const char*)&s->memory[s->general_purpose[a0]], (char*)&s->memory[s->general_purpose[a1]], (size_t)s->general_purpose[a2]);
            break;
        case 13:
            s->general_purpose[a7] = flistxattr((int)s->general_purpose[a0], (char*)&s->memory[s->general_purpose[a1]], (size_t)s->general_purpose[a2]);
            break;
        case 14:
            s->general_purpose[a7] = removexattr((const char*)&s->memory[s->general_purpose[a0]], (const char*)&s->memory[s->general_purpose[a1]]);
            break;
        case 15:
            s->general_purpose[a7] = lremovexattr((const char*)&s->memory[s->general_purpose[a0]], (const char*)&s->memory[s->general_purpose[a1]]);
            break;
        case 16:
            s->general_purpose[a7] = fremovexattr((int)s->general_purpose[a0], (const char*)&s->memory[s->general_purpose[a1]]);
            break;
        case 17:
            char* st = getcwd((char*)s->general_purpose[a0], (size_t)s->general_purpose[a1]);
            s->general_purpose[a7] = (int)AddMemory(s, st);
            break;
        case 18:
            s->general_purpose[a7] = syscall(SYS_lookup_dcookie, (uint64_t)s->general_purpose[a0], (char*)&s->memory[s->general_purpose[a1]]);
            break;
        case 19:
            s->general_purpose[a7] = eventfd((unsigned int)s->general_purpose[a0], (int)s->general_purpose[a1]);
            break;
        case 20:
            s->general_purpose[a7] = epoll_create1((int)s->general_purpose[a0]);
            break;
        case 21:
            s->general_purpose[a7] = epoll_ctl((int)s->general_purpose[a0], (int)s->general_purpose[a1], (int)s->general_purpose[a2], (struct epoll_event*)&s->memory[s->general_purpose[a3]]);
            break;
        case 22:
            s->general_purpose[a7] = epoll_pwait((int)s->general_purpose[a0], (struct epoll_event*)&s->memory[s->general_purpose[a1]], (int)s->general_purpose[a2], (int)s->general_purpose[a3], (const sigset_t*)&s->memory[s->general_purpose[a4]]);
            break;
        case 23:
            s->general_purpose[a7] = dup((unsigned int)s->general_purpose[a0]);
            break;
        case 24:
            s->general_purpose[a7] = dup3((unsigned int)s->general_purpose[a0], (unsigned int)s->general_purpose[a1], (int)s->general_purpose[a2]);
            break;
        case 25:
            s->general_purpose[a7] = fcntl64((unsigned int)s->general_purpose[a0], (unsigned int)s->general_purpose[a1], (unsigned long)s->general_purpose[a2]);
            break;
        case 26:
            s->general_purpose[a7] = inotify_init1((int)s->general_purpose[a0]);
            break;
        case 27:
            s->general_purpose[a7] = inotify_add_watch((int)s->general_purpose[a0], (const char*)&s->memory[s->general_purpose[a1]], (uint32_t)s->general_purpose[a2]);
            break;
        case 28:
            s->general_purpose[a7] = inotify_rm_watch((int)s->general_purpose[a0], (__s32)s->general_purpose[a1]);
            break;
        case 29:
            s->general_purpose[a7] = ioctl((unsigned int)s->general_purpose[a0], (unsigned int)s->general_purpose[a1], (unsigned long)s->general_purpose[a2]);
            break;
        case 30:
            s->general_purpose[a7] = syscall(SYS_ioprio_set, (int)s->general_purpose[a0], (int)s->general_purpose[a1]);
            break;
        case 31:
            s->general_purpose[a7] = syscall(SYS_ioprio_get, (int)s->general_purpose[a0], (int)s->general_purpose[a1]);
            break;
        case 32:
            s->general_purpose[a7] = flock((unsigned int)s->general_purpose[a0], (unsigned int)s->general_purpose[a1]);
            break;
        case 33:
            s->general_purpose[a7] = mknodat((int)s->general_purpose[a0], (const char*)&s->memory[s->general_purpose[a1]], (mode_t)s->general_purpose[a2], (unsigned)s->general_purpose[a3]);
            break;
        case 34:
            s->general_purpose[a7] = mkdirat((int)s->general_purpose[a0], (const char*)&s->memory[s->general_purpose[a1]], (mode_t)s->general_purpose[a2]);
            break;
        case 35:
            s->general_purpose[a7] = unlinkat((int)s->general_purpose[a0], (const char*)&s->memory[s->general_purpose[a1]], (int)s->general_purpose[a2]);
            break;
        case 36:
            s->general_purpose[a7] = symlinkat((const char*)&s->memory[s->general_purpose[a0]], (int)s->general_purpose[a1], (const char*)&s->memory[s->general_purpose[a2]]);
            break;
        case 37:
            s->general_purpose[a7] = unlinkat((int)s->general_purpose[a0], (const char*)&s->memory[s->general_purpose[a1]], (int)s->general_purpose[a2]);
            break;
        case 38:
            s->general_purpose[a7] = renameat((int)s->general_purpose[a0], (const char*)&s->memory[s->general_purpose[a1]], (int)s->general_purpose[a2], (const char*)&s->memory[s->general_purpose[a3]]);
            break;
        case 39:
            s->general_purpose[a7] = umount((char*)&s->memory[s->general_purpose[a0]], (int)s->general_purpose[a1]);
            break;
        case 40:
            s->general_purpose[a7] = umount((char*)&s->memory[s->general_purpose[a0]], (int)s->general_purpose[a1]);
            break;
        case 41:
            s->general_purpose[a7] = pivot_root((const char*)&s->memory[s->general_purpose[a0]], (const char*)&s->memory[s->general_purpose[a1]]);
            break;
        case 42:
            s->general_purpose[a7] = sys_ni_syscall();
            break;
        case 43:
            s->general_purpose[a7] = statfs64((const char*)&s->memory[s->general_purpose[a0]], (size_t)s->general_purpose[a1], (struct statfs64*)&s->memory[s->general_purpose[a2]]);
            break;
        case 44:
            s->general_purpose[a7] = fstatfs64((unsigned int)s->general_purpose[a0], (size_t)s->general_purpose[a1], (struct statfs64*)&s->memory[s->general_purpose[a2]]);
            break;
        case 45:
            s->general_purpose[a7] = truncate64((const char*)&s->memory[s->general_purpose[a0]], (loff_t)s->general_purpose[a1]);
            break;
        case 46:
            s->general_purpose[a7] = ftruncate64((unsigned int)s->general_purpose[a0], (loff_t)s->general_purpose[a1]);
            break;
        case 47:
            s->general_purpose[a7] = fallocate((int)s->general_purpose[a0], (int)s->general_purpose[a1], (loff_t)s->general_purpose[a2], (loff_t)s->general_purpose[a3]);
            break;
        case 48:
            s->general_purpose[a7] = faccessat((int)s->general_purpose[a0], (const char*)&s->memory[s->general_purpose[a1]], (int)s->general_purpose[a2], (int)s->general_purpose[a3]);
            break;
        case 49:
            s->general_purpose[a7] = chdir((const char*)&s->memory[s->general_purpose[a0]]);
            break;
        case 50:
            s->general_purpose[a7] = fchdir((unsigned int)s->general_purpose[a0]);
            break;
        case 51:
            s->general_purpose[a7] = chroot((const char*)&s->memory[s->general_purpose[a0]]);
            break;
        case 52:
            s->general_purpose[a7] = fchmod((unsigned int)s->general_purpose[a0], (mode_t)s->general_purpose[a1]);
            break;
        case 53:
            s->general_purpose[a7] = fchmodat((int)s->general_purpose[a0], (const char*)&s->memory[s->general_purpose[a1]], (mode_t)s->general_purpose[a2], (int)s->general_purpose[a3]);
            break;
        case 54:
            s->general_purpose[a7] = fchownat((int)s->general_purpose[a0], (const char*)&s->memory[s->general_purpose[a1]], (uid_t)s->general_purpose[a2], (gid_t)s->general_purpose[a3], (int)s->general_purpose[a4]);
            break;
        case 55:
            s->general_purpose[a7] = fchown((unsigned int)s->general_purpose[a0], (uid_t)s->general_purpose[a1], (gid_t)s->general_purpose[a2]);
            break;
        case 56:
            s->general_purpose[a7] = openat((int)s->general_purpose[a0], (const char*)&s->memory[s->general_purpose[a1]], (int)s->general_purpose[a2]);
            break;
        case 57:
            //s->general_purpose[a7] = close((int)s->general_purpose[a0]);
            break;
        case 58:
            s->general_purpose[a7] = vhangup();
            break;
        case 59:
            s->general_purpose[a7] = pipe2((int*)&s->memory[s->general_purpose[a0]], (int)s->general_purpose[a1]);
            break;
        case 60:
            s->general_purpose[a7] = quotactl((unsigned int)s->general_purpose[a0], (const char*)&s->memory[s->general_purpose[a1]], (id_t)s->general_purpose[a2], (void*)&s->memory[s->general_purpose[a3]]);
            break;
        case 61:
            s->general_purpose[a7] = getdents64((unsigned int)s->general_purpose[a0], (struct linux_dirent64*)&s->memory[s->general_purpose[a1]], (unsigned int)s->general_purpose[a2]);
            break;
        case 62:
            s->general_purpose[a7] = syscall(SYS__llseek, (unsigned int)s->general_purpose[a0], (unsigned long)s->general_purpose[a1], (unsigned long)s->general_purpose[a2], (loff_t*)&s->memory[s->general_purpose[a3]], (unsigned int)s->general_purpose[a4]);
            break;
        case 63:
            s->general_purpose[a7] = read((unsigned int)s->general_purpose[a0], (char*)&s->memory[s->general_purpose[a1]], (size_t)s->general_purpose[a2]);
            break;
        case 64:
            s->general_purpose[a7] = write((unsigned int)s->general_purpose[a0], (const char*)&s->memory[s->general_purpose[a1]], (size_t)s->general_purpose[a2]);
            break;
        case 65:
            s->general_purpose[a7] = readv((unsigned long)s->general_purpose[a0], (const struct iovec*)&s->memory[s->general_purpose[a1]], (unsigned long)s->general_purpose[a2]);
            break;
        case 66:
            s->general_purpose[a7] = writev((unsigned long)s->general_purpose[a0], (const struct iovec*)&s->memory[s->general_purpose[a1]], (unsigned long)s->general_purpose[a2]);
            break;
        case 67:
            s->general_purpose[a7] = pread64((unsigned int)s->general_purpose[a0], (char*)&s->memory[s->general_purpose[a1]], (size_t)s->general_purpose[a2], (loff_t)s->general_purpose[a3]);
            break;
        case 68:
            s->general_purpose[a7] = pwrite64((unsigned int)s->general_purpose[a0], (const char*)&s->memory[s->general_purpose[a1]], (size_t)s->general_purpose[a2], (loff_t)s->general_purpose[a3]);
            break;
        case 69:
            s->general_purpose[a7] = preadv((unsigned long)s->general_purpose[a0], (const struct iovec*)&s->memory[s->general_purpose[a1]], (unsigned long)s->general_purpose[a2], (unsigned long)s->general_purpose[a3]);
            break;
        case 70:
            s->general_purpose[a7] = pwritev((unsigned long)s->general_purpose[a0], (const struct iovec*)&s->memory[s->general_purpose[a1]], (unsigned long)s->general_purpose[a2], (unsigned long)s->general_purpose[a3]);
            break;
        case 71:
            s->general_purpose[a7] = sendfile64((int)s->general_purpose[a0], (int)s->general_purpose[a1], (loff_t*)&s->memory[s->general_purpose[a2]], (size_t)s->general_purpose[a3]);
            break;
        case 72:
            // pselect6_time32 not implemented
            sys_ni_syscall();
            break;
        case 73:
            // ppoll_time32 not implemented
            sys_ni_syscall();
            break;
        case 74:
            s->general_purpose[a7] = signalfd((int)s->general_purpose[a0], (const sigset_t*)s->general_purpose[a1], (int)s->general_purpose[a2]);
            break;
        case 75:
            s->general_purpose[a7] = vmsplice((int)s->general_purpose[a0], (const struct iovec*)&s->memory[s->general_purpose[a1]], (unsigned long)s->general_purpose[a2], (unsigned int)s->general_purpose[a3]);
            break;
        case 76:
            s->general_purpose[a7] = vmsplice((int)s->general_purpose[a0], (const struct iovec*)&s->memory[s->general_purpose[a1]], (unsigned long)s->general_purpose[a2], (unsigned int)s->general_purpose[a3]);
            break;
        case 77:
            s->general_purpose[a7] = tee((int)s->general_purpose[a0], (int)s->general_purpose[a1], (size_t)s->general_purpose[a2], (unsigned int)s->general_purpose[a3]);
            break;
        case 78:
            s->general_purpose[a7] = readlinkat((int)s->general_purpose[a0], (const char*)&s->memory[s->general_purpose[a1]], (char*)&s->memory[s->general_purpose[a2]], (int)s->general_purpose[a3]);
            break;
        case 79:
            s->general_purpose[a7] = fstatat((int)s->general_purpose[a0], (const char*)&s->memory[s->general_purpose[a1]], (struct stat *restrict)&s->memory[s->general_purpose[a2]], (int)s->general_purpose[a3]);
            break;
        case 80:
            s->general_purpose[a7] = fstat((int)s->general_purpose[a0], (struct stat*)&s->memory[s->general_purpose[a1]]);
            break;
        case 81:
            sync();
            break;
        case 82:
            s->general_purpose[a7] = fsync((unsigned int)s->general_purpose[a0]);
            break;
        case 83:
            s->general_purpose[a7] = fdatasync((unsigned int)s->general_purpose[a0]);
            break;
        case 84:
            s->general_purpose[a7] = sync_file_range((int)s->general_purpose[a0], (loff_t)s->general_purpose[a1], (loff_t)s->general_purpose[a2], (unsigned int)s->general_purpose[a3]);
            break;
        case 85:
            s->general_purpose[a7] = timerfd_create((int)s->general_purpose[a0], (int)s->general_purpose[a1]);
            break;
        case 411:
            s->general_purpose[a7] = timerfd_settime((int)s->general_purpose[a0], (int)s->general_purpose[a1], (const struct __kernel_itimerspec*)&s->memory[s->general_purpose[a2]], (struct __kernel_itimerspec*)&s->memory[s->general_purpose[a3]]);
            break;
        case 410:
            s->general_purpose[a7] = timerfd_gettime((int)s->general_purpose[a0], (struct __kernel_itimerspec*)&s->memory[s->general_purpose[a1]]);
            break;
        case 412:
            s->general_purpose[a7] = utimensat((int)s->general_purpose[a0], (const char*)&s->memory[s->general_purpose[a1]], (struct __kernel_timespec*)&s->memory[s->general_purpose[a2]], (int)s->general_purpose[a3]);
            break;
        case 89:
            s->general_purpose[a7] = acct((const char*)&s->memory[s->general_purpose[a0]]);
            break;
        case 90:
            s->general_purpose[a7] = capget((cap_user_header_t)s->general_purpose[a0], (cap_user_data_t)s->general_purpose[a1]);
            break;
        case 91:
            s->general_purpose[a7] = capset((cap_user_header_t)s->general_purpose[a0], (const cap_user_data_t)s->general_purpose[a1]);
            break;
        case 92:
            s->general_purpose[a7] = personality((unsigned int)s->general_purpose[a0]);
            break;
        case 93:
            printf("Program status: finished.");
            exit((int)s->general_purpose[a0]);
        case 94:
            s->general_purpose[a7] = syscall(SYS_exit_group, (int)s->general_purpose[a0]);
            break;
        case 95:
            s->general_purpose[a7] = waitid((int)s->general_purpose[a0], (pid_t)s->general_purpose[a1], (struct siginfo*)&s->memory[s->general_purpose[a2]], (int)s->general_purpose[a3]);
            break;
        case 96:
            s->general_purpose[a7] = syscall(SYS_set_tid_address, (int*)&s->memory[s->general_purpose[a0]]);
            break;
        case 97:
            s->general_purpose[a7] = unshare((unsigned long)s->general_purpose[a0]);
            break;
        case 422:
            s->general_purpose[a7] = syscall(SYS_futex, (uint32_t*)&s->memory[s->general_purpose[a0]], (int)s->general_purpose[a1], (uint32_t)s->general_purpose[a2], (uint32_t*)&s->memory[s->general_purpose[a2]], (uint32_t*)&s->memory[s->general_purpose[a3]], (uint32_t)s->memory[s->general_purpose[a4]]);
            break;
        case 99:
            //set_robust_list undefined
			sys_ni_syscall();
            break;
        case 100:
        {
            //get_robust_list undefined
			sys_ni_syscall();
            break;
        }
        case 101:
            s->general_purpose[a7] = nanosleep((struct __kernel_timespec*)&s->memory[s->general_purpose[a0]], (struct __kernel_timespec*)&s->memory[s->general_purpose[a1]]);
            break;
        case 102:
            s->general_purpose[a7] = getitimer((int)s->general_purpose[a0], (struct __kernel_old_itimerval*)&s->memory[s->general_purpose[a1]]);
            break;
        case 103:
            s->general_purpose[a7] = setitimer((int)s->general_purpose[a0], (struct __kernel_old_itimerval*)&s->memory[s->general_purpose[a1]], (struct __kernel_old_itimerval*)&s->memory[s->general_purpose[a2]]);
            break;
        case 104:
            s->general_purpose[a7] = syscall(SYS_kexec_load, (unsigned long)s->general_purpose[a0], (unsigned long)s->general_purpose[a1], (struct kexec_segment*)&s->memory[s->general_purpose[a1]], (unsigned long)s->general_purpose[a2]);
            break;
        case 105:
            s->general_purpose[a7] = syscall(SYS_init_module, (void*)s->general_purpose[a1], (unsigned long)s->general_purpose[a2], (const char*)&s->memory[s->general_purpose[a3]]);
            break;
        case 106:
            s->general_purpose[a7] = delete_module((const char*)&s->memory[s->general_purpose[a0]], (unsigned int)s->general_purpose[a1]);
            break;
        case 107:
            s->general_purpose[a7] = timer_create((clockid_t)s->general_purpose[a0], (struct sigevent* restrict)&s->memory[s->general_purpose[a1]], (timer_t restrict*)&s->memory[s->general_purpose[a2]]);
            break;
        case 408:
            //timer_gettime undefined
			sys_ni_syscall();
            break;
        case 109:
            //timer_getoverrun undefined
			sys_ni_syscall();
            break;
        case 409:
            //timer_settime undefined
			sys_ni_syscall();
            break;
        case 111:
            //timer_delete undefined
			sys_ni_syscall();
            break;
        case 404:
            s->general_purpose[a7] = clock_settime((clockid_t)s->general_purpose[a0], (const struct __kernel_timespec*)&s->memory[s->general_purpose[a1]]);
            break;
        case 403:
            s->general_purpose[a7] = clock_gettime((clockid_t)s->general_purpose[a0], (struct __kernel_timespec*)&s->memory[s->general_purpose[a1]]);
            break;
        case 406:
            s->general_purpose[a7] = clock_getres((clockid_t)s->general_purpose[a0], (struct __kernel_timespec*)&s->memory[s->general_purpose[a1]]);
            break;
        case 407:
            s->general_purpose[a7] = clock_nanosleep((clockid_t)s->general_purpose[a0], (int)s->general_purpose[a1], (const struct __kernel_timespec*)&s->memory[s->general_purpose[a2]], (struct __kernel_timespec*)&s->memory[s->general_purpose[a3]]);
            break;
        case 116:
            s->general_purpose[a7] = syslog((int)s->general_purpose[a0], (char*)&s->memory[s->general_purpose[a1]], (int)s->general_purpose[a2]);
            break;
        case 117:
            s->general_purpose[a7] = ptrace((long)s->general_purpose[a0], (long)s->general_purpose[a1], (unsigned long)s->general_purpose[a2], (unsigned long)s->general_purpose[a3]);
            break;
        case 118:
            s->general_purpose[a7] = sched_setparam((pid_t)s->general_purpose[a0], (struct sched_param*)&s->memory[s->general_purpose[a1]]);
            break;
        case 119:
            s->general_purpose[a7] = sched_setscheduler((pid_t)s->general_purpose[a0], (int)s->general_purpose[a1], (struct sched_param*)&s->memory[s->general_purpose[a2]]);
            break;
        case 120:
            s->general_purpose[a7] = sched_getscheduler((pid_t)s->general_purpose[a0]);
            break;
        case 121:
            s->general_purpose[a7] = sched_getparam((pid_t)s->general_purpose[a0], (struct sched_param*)&s->memory[s->general_purpose[a1]]);
            break;
        case 122:
            s->general_purpose[a7] = sched_setaffinity((pid_t)s->general_purpose[a0], (unsigned int)s->general_purpose[a1], (unsigned long*)&s->memory[s->general_purpose[a2]]);
            break;
        case 123:
            s->general_purpose[a7] = sched_getaffinity((pid_t)s->general_purpose[a0], (unsigned int)s->general_purpose[a1], (unsigned long*)&s->memory[s->general_purpose[a2]]);
            break;
        case 124:
            s->general_purpose[a7] = sched_yield();
            break;
        case 125:
            s->general_purpose[a7] = sched_get_priority_max((int)s->general_purpose[a0]);
            break;
        case 126:
            s->general_purpose[a7] = sched_get_priority_min((int)s->general_purpose[a0]);
            break;
        case 423:
            s->general_purpose[a7] = sched_rr_get_interval((pid_t)s->general_purpose[a0], (struct __kernel_timespec*)&s->memory[s->general_purpose[a1]]);
            break;
        case 128:
            //restart_Syscall_undefined
			sys_ni_syscall();
            sys_ni_syscall();
            break;
        case 129:
            s->general_purpose[a7] = kill((pid_t)s->general_purpose[a0], (int)s->general_purpose[a1]);
            break;
        case 130:
            s->general_purpose[a7] = syscall(SYS_tkill, (pid_t)s->general_purpose[a0], (int)s->general_purpose[a1]);
            break;
        case 131:
            s->general_purpose[a7] = tgkill((pid_t)s->general_purpose[a0], (pid_t)s->general_purpose[a1], (int)s->general_purpose[a2]);
            break;
        case 132:
            //sigaltstack undefined
            sys_ni_syscall();
            break;
        case 133:
            s->general_purpose[a7] = sigsuspend((const sigset_t*)s->general_purpose[a0]);
            break;
        case 134:
            //rt_sigaction undefined
			sys_ni_syscall();
            break;
        case 135:
            //rt_sigprocmask undefined
			sys_ni_syscall();
            break;
        case 136:
            //rt_sigpending undefined
			sys_ni_syscall();
            break;
        case 137:
            //rt_sigtimedwait_time32 undefined
			sys_ni_syscall();
            break;
        case 138:
            //rt_sigqueueinfo undefined
			sys_ni_syscall();
            break;
        case 140:
            s->general_purpose[a7] = setpriority((int)s->general_purpose[a0], (int)s->general_purpose[a1], (int)s->general_purpose[a2]);
            break;
        case 141:
            s->general_purpose[a7] = getpriority((int)s->general_purpose[a0], (int)s->general_purpose[a1]);
            break;
        case 142:
            s->general_purpose[a7] = reboot((int)s->general_purpose[a0], (int)s->general_purpose[a1], (unsigned int)s->general_purpose[a2], (void*)&s->memory[s->general_purpose[a3]]);
            break;
        case 143:
            s->general_purpose[a7] = setregid((gid_t)s->general_purpose[a0], (gid_t)s->general_purpose[a1]);
            break;
        case 144:
            s->general_purpose[a7] = setgid((gid_t)s->general_purpose[a0]);
            break;
        case 145:
            s->general_purpose[a7] = setreuid((uid_t)s->general_purpose[a0], (uid_t)s->general_purpose[a1]);
            break;
        case 146:
            s->general_purpose[a7] = setuid((uid_t)s->general_purpose[a0]);
            break;
        case 147:
            s->general_purpose[a7] = setresuid((uid_t)s->general_purpose[a0], (uid_t)s->general_purpose[a1], (uid_t)s->general_purpose[a2]);
            break;
        case 148:
            s->general_purpose[a7] = getresuid((uid_t*)&s->memory[s->general_purpose[a0]], (uid_t*)&s->memory[s->general_purpose[a1]], (uid_t*)&s->memory[s->general_purpose[a2]]);
            break;
        case 149:
            s->general_purpose[a7] = setresgid((gid_t)s->general_purpose[a0], (gid_t)s->general_purpose[a1], (gid_t)s->general_purpose[a2]);
            break;
        case 150:
            s->general_purpose[a7] = getresgid((gid_t*)&s->memory[s->general_purpose[a0]], (gid_t*)&s->memory[s->general_purpose[a1]], (gid_t*)&s->memory[s->general_purpose[a2]]);
            break;
        case 151:
            s->general_purpose[a7] = setfsuid((uid_t)s->general_purpose[a0]);
            break;
        case 152:
            s->general_purpose[a7] = setfsgid((gid_t)s->general_purpose[a0]);
            break;
        case 153:
            s->general_purpose[a7] = times((struct tms*)&s->memory[s->general_purpose[a0]]);
            break;
        case 154:
            s->general_purpose[a7] = setpgid((pid_t)s->general_purpose[a0], (pid_t)s->general_purpose[a1]);
            break;
        case 155:
            s->general_purpose[a7] = getpgid((pid_t)s->general_purpose[a0]);
            break;
        case 156:
            s->general_purpose[a7] = getsid((pid_t)s->general_purpose[a0]);
            break;
        case 157:
            s->general_purpose[a7] = setsid();
            break;
        case 158:
            s->general_purpose[a7] = getgroups((int)s->general_purpose[a0], (gid_t*)&s->memory[s->general_purpose[a1]]);
            break;
        case 159:
            s->general_purpose[a7] = setgroups((int)s->general_purpose[a0], (gid_t*)&s->memory[s->general_purpose[a1]]);
            break;
        case 160:
            //newuname undefined
			sys_ni_syscall();
            break;
        case 161:
            s->general_purpose[a7] = sethostname((char*)&s->memory[s->general_purpose[a0]], (int)s->general_purpose[a1]);
            break;
        case 162:
            s->general_purpose[a7] = setdomainname((char*)&s->memory[s->general_purpose[a0]], (int)s->general_purpose[a1]);
            break;
        case 163:
            s->general_purpose[a7] = getrlimit((unsigned int)s->general_purpose[a0], (struct rlimit*)&s->memory[s->general_purpose[a1]]);
            break;
        case 164:
            s->general_purpose[a7] = setrlimit((unsigned int)s->general_purpose[a0], (struct rlimit*)&s->memory[s->general_purpose[a1]]);
            break;
        case 165:
            s->general_purpose[a7] = getrusage((int)s->general_purpose[a0], (struct rusage*)&s->memory[s->general_purpose[a1]]);
            break;
        case 166:
            s->general_purpose[a7] = umask((int)s->general_purpose[a0]);
            break;
        case 167:
            s->general_purpose[a7] = prctl((int)s->general_purpose[a0], (unsigned long)s->general_purpose[a1], (unsigned long)s->general_purpose[a2], (unsigned long)s->general_purpose[a3], (unsigned long)s->general_purpose[a4]);
            break;
        case 168:
            s->general_purpose[a7] = getcpu((unsigned*)&s->memory[s->general_purpose[a0]], (unsigned*)&s->memory[s->general_purpose[a1]], (struct getcpu_cache*)&s->memory[s->general_purpose[a2]]);
            break;
        case 169:
            s->general_purpose[a7] = gettimeofday((struct __kernel_old_timeval*)&s->memory[s->general_purpose[a0]], (struct timezone*)&s->memory[s->general_purpose[a1]]);
            break;
        case 170:
            s->general_purpose[a7] = settimeofday((struct __kernel_old_timeval*)&s->memory[s->general_purpose[a0]], (struct timezone*)&s->memory[s->general_purpose[a1]]);
            break;
        case 171:
            s->general_purpose[a7] = adjtimex((struct __kernel_timex*)&s->memory[s->general_purpose[a0]]);
            break;
        case 172:
            s->general_purpose[a7] = getpid();
            break;
        case 173:
            s->general_purpose[a7] = getppid();
            break;
        case 174:
            s->general_purpose[a7] = getuid();
            break;
        case 175:
            s->general_purpose[a7] = geteuid();
            break;
        case 176:
            s->general_purpose[a7] = getgid();
            break;
        case 177:
            s->general_purpose[a7] = getegid();
            break;
        case 178:
            s->general_purpose[a7] = gettid();
            break;
        case 179:
            s->general_purpose[a7] = sysinfo((struct sysinfo*)&s->memory[s->general_purpose[a0]]);
            break;
        case 180:
            //mq_open undefined
			sys_ni_syscall();
            break;
        case 181:
            //mq_unlink undefined
			sys_ni_syscall();
            break;
        case 418:
            //mq_timedsend undefined
			sys_ni_syscall();
            break;
        case 419:
            //mq_timedreceive undefined
			sys_ni_syscall();
            break;
        case 184:
            //mq_notify undefined
			sys_ni_syscall();
            break;
        case 185:
            //mq_getsetattr undefined
			sys_ni_syscall();
            break;
        case 186:
            s->general_purpose[a7] = msgget((key_t)s->general_purpose[a0], (int)s->general_purpose[a1]);
            break;
        case 187:
            //old_msgctl undefined
			sys_ni_syscall();
            break;
        case 188:
            s->general_purpose[a7] = msgrcv((int)s->general_purpose[a0], (struct msgbuf*)&s->memory[s->general_purpose[a1]], (size_t)s->general_purpose[a2], (long)s->general_purpose[a3], (int)s->general_purpose[a4]);
            break;
        case 189:
            s->general_purpose[a7] = msgsnd((int)s->general_purpose[a0], (struct msgbuf*)&s->memory[s->general_purpose[a1]], (size_t)s->general_purpose[a2], (int)s->general_purpose[a3]);
            break;
        case 190:
            s->general_purpose[a7] = semget((key_t)s->general_purpose[a0], (int)s->general_purpose[a1], (int)s->general_purpose[a2]);
            break;
        case 191:
            s->general_purpose[a7] = semctl((int)s->general_purpose[a0], (int)s->general_purpose[a1], (int)s->general_purpose[a2], (unsigned long)s->general_purpose[a3]);
            break;
        case 420:
            s->general_purpose[a7] = semtimedop((int)s->general_purpose[a0], (struct sembuf*)&s->memory[s->general_purpose[a1]], (unsigned)s->general_purpose[a2], (const struct __kernel_timespec*)&s->memory[s->general_purpose[a3]]);
            break;
        case 193:
            s->general_purpose[a7] = semop((int)s->general_purpose[a0], (struct sembuf*)&s->memory[s->general_purpose[a1]], (unsigned)s->general_purpose[a2]);
            break;
        case 194:
            //shmget undefined
            sys_ni_syscall();
            break;
        case 195:
            //old_shmctl undefined
			sys_ni_syscall();
            break;
        case 196:
            s->general_purpose[a7] = shmat((int)s->general_purpose[a0], (char*)&s->memory[s->general_purpose[a1]], (int)s->general_purpose[a2]);
            break;
        case 197:
            s->general_purpose[a7] = shmdt((char*)&s->memory[s->general_purpose[a0]]);
            break;
        case 198:
            s->general_purpose[a7] = socket((int)s->general_purpose[a0], (int)s->general_purpose[a1], (int)s->general_purpose[a2]);
            break;
        case 199:
            s->general_purpose[a7] = socketpair((int)s->general_purpose[a0], (int)s->general_purpose[a1], (int)s->general_purpose[a2], (int*)&s->memory[s->general_purpose[a3]]);
            break;
        case 200:
            //bind undefined
			sys_ni_syscall();
            break;
        case 201:
            s->general_purpose[a7] = listen((int)s->general_purpose[a0], (int)s->general_purpose[a1]);
            break;
        case 202:
            s->general_purpose[a7] = accept((int)s->general_purpose[a0], (struct sockaddr*)&s->memory[s->general_purpose[a1]], (int*)&s->memory[s->general_purpose[a2]]);
            break;
        case 203:
            s->general_purpose[a7] = connect((int)s->general_purpose[a0], (struct sockaddr*)&s->memory[s->general_purpose[a1]], (int)s->general_purpose[a2]);
            break;
        case 204:
            s->general_purpose[a7] = getsockname((int)s->general_purpose[a0], (struct sockaddr*)&s->memory[s->general_purpose[a1]], (int*)&s->memory[s->general_purpose[a2]]);
            break;
        case 205:
            s->general_purpose[a7] = getpeername((int)s->general_purpose[a0], (struct sockaddr*)&s->memory[s->general_purpose[a1]], (int*)&s->memory[s->general_purpose[a2]]);
            break;
        case 206:
            s->general_purpose[a7] = sendto((int)s->general_purpose[a0], (void*)&s->memory[s->general_purpose[a1]], (size_t)s->general_purpose[a2], (unsigned)s->general_purpose[a3], (struct sockaddr*)&s->memory[s->general_purpose[a4]], (int)s->general_purpose[a5]);
            break;
        case 207:
            s->general_purpose[a7] = recvfrom((int)s->general_purpose[a0], (void*)&s->memory[s->general_purpose[a1]], (size_t)s->general_purpose[a2], (unsigned)s->general_purpose[a3], (struct sockaddr*)&s->memory[s->general_purpose[a4]], (int*)&s->memory[s->general_purpose[a5]]);
            break;
        case 208:
            s->general_purpose[a7] = setsockopt((int)s->general_purpose[a0], (int)s->general_purpose[a1], (int)s->general_purpose[a2], (char*)&s->memory[s->general_purpose[a3]], (int)s->general_purpose[a4]);
            break;
        case 209:
            s->general_purpose[a7] = getsockopt((int)s->general_purpose[a0], (int)s->general_purpose[a1], (int)s->general_purpose[a2], (char*)&s->memory[s->general_purpose[a3]], (int*)&s->memory[s->general_purpose[a4]]);
            break;
        case 210:
            s->general_purpose[a7] = shutdown((int)s->general_purpose[a0], (int)s->general_purpose[a1]);
            break;
        case 211:
            s->general_purpose[a7] = sendmsg((int)s->general_purpose[a0], (struct user_msghdr*)&s->memory[s->general_purpose[a1]], (unsigned)s->general_purpose[a2]);
            break;
        case 212:
            s->general_purpose[a7] = recvmsg((int)s->general_purpose[a0], (struct user_msghdr*)&s->memory[s->general_purpose[a1]], (unsigned)s->general_purpose[a2]);
            break;
        case 213:
            s->general_purpose[a7] = readahead((int)s->general_purpose[a0], (loff_t)s->general_purpose[a1], (size_t)s->general_purpose[a2]);
            break;
        case 214:
            s->general_purpose[a7] = BRK(s, (unsigned int)s->general_purpose[a0]);
            break;
        case 215:
            s->general_purpose[a7] = MUNMAP(s, (unsigned int)s->general_purpose[a0], (size_t)s->general_purpose[a1]);
            break;
        case 216:
            //mremap undefined
            sys_ni_syscall();
            break;
        case 217:
            //add_key undefined
			sys_ni_syscall();
            break;
        case 218:
            //request_key undefined
			sys_ni_syscall();
            break;
        case 219:
            //keyctl undefined
			sys_ni_syscall();
            break;
        case 220:
            //clone undefined
			sys_ni_syscall();
            break;
        case 221:
            //execve undefined
			sys_ni_syscall();
            break;
        case 222:
			s->general_purpose[a7] = MMAP(s, (void*)&s->memory[s->general_purpose[a0]], (size_t)s->general_purpose[a1], (int)s->general_purpose[a2], (int)s->general_purpose[a3], (int)s->general_purpose[a4], (off_t)s->general_purpose[a5]);
            break;
        case 223:
            //fadvise64_64 undefined
			sys_ni_syscall();
            break;
        case 224:
            s->general_purpose[a7] = swapon((const char*)&s->memory[s->general_purpose[a0]], (int)s->general_purpose[a1]);
            break;
        case 225:
            s->general_purpose[a7] = swapoff((const char*)&s->memory[s->general_purpose[a0]]);
            break;
        case 226:
            //mprotect undefined
            sys_ni_syscall();
            break;
        case 227:
            //msync undefined
            sys_ni_syscall();
            break;
        case 228:
            //mlock undefined
            sys_ni_syscall();
            break;
        case 229:
            //munlock undefined
            sys_ni_syscall();
            break;
        case 230:
            //mlockall undefined
            sys_ni_syscall();
            break;
        case 231:
            //munlockall undefined
            sys_ni_syscall();
            break;
        case 232:
            //mincore undefined
            sys_ni_syscall();
            break;
        case 233:
            //madvise undefined
			sys_ni_syscall();
            break;
        case 234:
            //remapfilepages undefined
            break;
        case 235:
            //mbind undefined
			sys_ni_syscall();
            break;
        case 236:
            //get_mempolicy undefined
			sys_ni_syscall();
            break;
        case 237:
            //set_mempolicy undefined
			sys_ni_syscall();
            break;
        case 238:
            //migrate_pages undefined
			sys_ni_syscall();
            break;
        case 239:
            //move_pages undefined
			sys_ni_syscall();
            break;
        case 240:
            //rt_tgsigqueueinfo undefined
			sys_ni_syscall();
            break;
        case 241:
            //perf_event_open undefined
			sys_ni_syscall();
            break;
        case 242:
            s->general_purpose[a7] = accept4((int)s->general_purpose[a0], (struct sockaddr*)&s->memory[s->general_purpose[a1]], (int*)&s->memory[s->general_purpose[a2]], (int)s->general_purpose[a3]);
            break;
        case 243:
            //recvmmsg_time32 undefined
			sys_ni_syscall();
            break;
        case 260:
            s->general_purpose[a7] = wait4((pid_t)s->general_purpose[a0], (int*)&s->memory[s->general_purpose[a1]], (int)s->general_purpose[a2], (struct rusage*)&s->memory[s->general_purpose[a3]]);
            break;
        case 261:
            s->general_purpose[a7] = prlimit64((pid_t)s->general_purpose[a0], (unsigned int)s->general_purpose[a1], (const struct rlimit64*)&s->memory[s->general_purpose[a2]], (struct rlimit64*)&s->memory[s->general_purpose[a3]]);
            break;
        case 262:
            s->general_purpose[a7] = fanotify_init((unsigned int)s->general_purpose[a0], (unsigned int)s->general_purpose[a1]);
            break;
        case 263:
            s->general_purpose[a7] = fanotify_mark((int)s->general_purpose[a0], (unsigned int)s->general_purpose[a1], (uint64_t)s->general_purpose[a2], (int)s->general_purpose[a3], (const char*)&s->memory[s->general_purpose[a4]]);
            break;
        case 264:
            s->general_purpose[a7] = name_to_handle_at((int)s->general_purpose[a0], (const char*)&s->memory[s->general_purpose[a1]], (struct file_handle*)&s->memory[s->general_purpose[a2]], (int*)&s->memory[s->general_purpose[a3]], (int)s->general_purpose[a4]);
            break;
        case 265:
            s->general_purpose[a7] = open_by_handle_at((int)s->general_purpose[a0], (struct file_handle*)&s->memory[s->general_purpose[a1]], (int)s->general_purpose[a2]);
            break;
        case 405:
            s->general_purpose[a7] = clock_adjtime((clockid_t)s->general_purpose[a0], (struct __kernel_timex*)&s->memory[s->general_purpose[a1]]);
            break;
        case 267:
            s->general_purpose[a7] = syncfs((int)s->general_purpose[a0]);
            break;
        case 268:
            s->general_purpose[a7] = setns((int)s->general_purpose[a0], (int)s->general_purpose[a1]);
            break;
        case 269:
            s->general_purpose[a7] = sendmmsg((int)s->general_purpose[a0], (struct mmsghdr*)&s->memory[s->general_purpose[a1]], (unsigned int)s->general_purpose[a2], (unsigned)s->general_purpose[a3]);
            break;
        case 270:
            s->general_purpose[a7] = process_vm_readv((pid_t)s->general_purpose[a0], (const struct iovec*)&s->memory[s->general_purpose[a1]], (unsigned long)s->general_purpose[a2], (const struct iovec*)&s->memory[s->general_purpose[a3]], (unsigned long)s->general_purpose[a4], (unsigned long)s->general_purpose[a5]);
            break;
        case 271:
            s->general_purpose[a7] = process_vm_writev((pid_t)s->general_purpose[a0], (const struct iovec*)&s->memory[s->general_purpose[a1]], (unsigned long)s->general_purpose[a2], (const struct iovec*)&s->memory[s->general_purpose[a3]], (unsigned long)s->general_purpose[a4], (unsigned long)s->general_purpose[a5]);
            break;
        case 272:
            //kcmp undefined
			sys_ni_syscall();
            break;
        case 273:
            //finit_module undefined
			sys_ni_syscall();
            break;
        case 274:
            //sched_setattr undefined
			sys_ni_syscall();
            break;
        case 275:
            //sched_getattr undefined
			sys_ni_syscall();
            break;
        case 276:
            s->general_purpose[a7] = renameat2((int)s->general_purpose[a0], (const char*)&s->memory[s->general_purpose[a1]], (int)s->general_purpose[a2], (const char*)&s->memory[s->general_purpose[a3]], (unsigned int)s->general_purpose[a4]);
            break;
        case 277:
            //seccomp undefined
			sys_ni_syscall();
            break;
        case 278:
            s->general_purpose[a7] = getrandom((char*)&s->memory[s->general_purpose[a0]], (size_t)s->general_purpose[a1], (unsigned int)s->general_purpose[a2]);
            break;
        case 279:
            s->general_purpose[a7] = memfd_create((const char*)&s->memory[s->general_purpose[a0]], (unsigned int)s->general_purpose[a1]);
            break;
        case 280:
            //bpf undefined
			sys_ni_syscall();
            break;
        case 281:
            //execveat undefined
			sys_ni_syscall();
            break;
        case 282:
            //userfaultfd undefined
			sys_ni_syscall();
            break;
        case 283:
            //membarrier undefined
			sys_ni_syscall();
            break;
        case 284:
            //mlock2 undefined
            sys_ni_syscall();
            break;
        case 285:
            s->general_purpose[a7] = copy_file_range((int)s->general_purpose[a0], (loff_t*)&s->memory[s->general_purpose[a1]], (int)s->general_purpose[a2], (loff_t*)&s->memory[s->general_purpose[a3]], (size_t)s->general_purpose[a4], (unsigned int)s->general_purpose[a5]);
            break;
        case 286:
            s->general_purpose[a7] = preadv2((unsigned long)s->general_purpose[a0], (const struct iovec*)&s->memory[s->general_purpose[a1]], (unsigned long)s->general_purpose[a2], (unsigned long)s->general_purpose[a3], (unsigned long)s->general_purpose[a4]);
            break;
        case 287:
            s->general_purpose[a7] = pwritev2((unsigned long)s->general_purpose[a0], (const struct iovec*)&s->memory[s->general_purpose[a1]], (unsigned long)s->general_purpose[a2], (unsigned long)s->general_purpose[a3], (unsigned long)s->general_purpose[a4]);
            break;
        case 288:
            //pkey_mprotect undefined
            sys_ni_syscall();
            break;
        case 289:
            //pkey_alloc undefined
            sys_ni_syscall();
            break;
        case 290:
            //pkey_free undefined
            break;
        case 291:
            s->general_purpose[a7] = statx((int)s->general_purpose[a0], (const char*)&s->memory[s->general_purpose[a1]], (unsigned)s->general_purpose[a2], (unsigned)s->general_purpose[a3], (struct statx*)&s->memory[s->general_purpose[a4]]);
            break;
        case 416:
            //io_pgetevents undefined
			sys_ni_syscall();
            break;
        case 293:
            //rseq undefined
			sys_ni_syscall();
            break;
        case 294:
            //kexec_file_load undefined
			sys_ni_syscall();
            break;
        case 424:
            //pidfd_send_signal undefined
			sys_ni_syscall();
            break;
        case 425:
            //io_uring_setup undefined
			sys_ni_syscall();
            break;
        case 426:
            //io_uring_enter undefined
			sys_ni_syscall();
            break;
        case 427:
            //io_uring_register undefined
			sys_ni_syscall();
            break;
        case 428:
            //open_tree undefined
			sys_ni_syscall();
            break;
        case 429:
            //move_mount undefined
			sys_ni_syscall();
            break;
        case 430:
            //fsopen undefined
			sys_ni_syscall();
            break;
        case 431:
            //fsconfig undefined
			sys_ni_syscall();
            break;
        case 432:
            //fsmount undefined
			sys_ni_syscall();
            break;
        case 433:
            //fspick undefined
			sys_ni_syscall();
            break;
        case 434:
            //pidfd_open undefined
			sys_ni_syscall();
            break;
        case 435:
            //clone3 undefined
			sys_ni_syscall();
            break;
        case 436:
            //close_range undefined
			sys_ni_syscall();
            break;
        case 437:
            //openat2 undefined
			sys_ni_syscall();
            break;
        case 438:
            //pidfd_getfd undefined
			sys_ni_syscall();
            break;
        case 439:
            //faccessat2 undefined
			sys_ni_syscall();
            break;
        case 440:
            //process_madvise undefined
			sys_ni_syscall();
            break;
    }
}




