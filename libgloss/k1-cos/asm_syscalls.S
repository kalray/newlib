#include <hal/cos_scall_no.h>

#if defined(__native__)
#include "asm_syscalls_native.S"
#else

	.section .text, "ax", @progbits
	.align 4

#define SYSCALL_ENTRY(name) \
	.proc sc_##name		; \
	.global sc_##name   	; \
sc_##name:


SYSCALL_ENTRY(access)
	scall __NR_access
	;;
	ret
	;;
.endp

SYSCALL_ENTRY(chdir)
	scall __NR_chdir
	;;
	ret
	;;
.endp

SYSCALL_ENTRY(chmod)
	scall __NR_chmod
	;;
	ret
	;;
.endp

SYSCALL_ENTRY(close)
	scall __NR_close
	;;
	ret
	;;
.endp

SYSCALL_ENTRY(dup2)
	scall __NR_dup2
	;;
	ret
	;;
.endp

SYSCALL_ENTRY(dup)
	scall __NR_dup
	;;
	ret
	;;
.endp

SYSCALL_ENTRY(exit)
	scall __NR_exit
	;;
	ret
	;;
.endp

SYSCALL_ENTRY(fcntl)
	scall __NR_fcntl
	;;
	ret
	;;
.endp

SYSCALL_ENTRY(fstat)
	scall __NR_fstat
	;;
	ret
	;;
.endp

SYSCALL_ENTRY(gettimeofday)
	scall __NR_gettimeofday
	;;
	ret
	;;
.endp

SYSCALL_ENTRY(isatty)
	scall __NR_isatty
	;;
	ret
	;;
.endp

SYSCALL_ENTRY(link)
	scall __NR_link
	;;
	ret
	;;
.endp

SYSCALL_ENTRY(lseek)
	scall __NR_lseek
	;;
	ret
	;;
.endp

SYSCALL_ENTRY(mkdir)
	scall __NR_mkdir
	;;
	ret
	;;
.endp

SYSCALL_ENTRY(mkfifo)
	scall __NR_iss_mkfifo
	;;
	ret
	;;
.endp

SYSCALL_ENTRY(open)
	scall __NR_open
	;;
	ret
	;;
.endp

SYSCALL_ENTRY(read)
	scall __NR_read
	;;
	ret
	;;
.endp

SYSCALL_ENTRY(rmdir)
	scall __NR_rmdir
	;;
	ret
	;;
.endp

SYSCALL_ENTRY(stat)
	scall __NR_stat
	;;
	ret
	;;
.endp

SYSCALL_ENTRY(unlink)
	scall __NR_unlink
	;;
	ret
	;;
.endp

SYSCALL_ENTRY(write)
	scall __NR_write
	;;
	ret
	;;
.endp

#endif
