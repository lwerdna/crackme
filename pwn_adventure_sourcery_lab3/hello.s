# build with:
# 
# as ./hello.S -o hello.o
.intel_syntax noprefix

.text                           # section declaration
			                          # we must export the entry point to the ELF linker or
.global _start              # loader. They conventionally recognize _start as their
			                          # entry point. Use ld -e foo to override the default.
_start:

                                # write our string to stdout

	  mov    $len,%rdx           # third argument: message length
	  mov    $msg,%rsi           # second argument: pointer to message to write
	  mov    $1,%rdi             # first argument: file handle (stdout)
	  mov    $1,%rax             # system call number (sys_write)
	  syscall

                                # and exit

	  movl    $0,%ebx             # first argument: exit code
	  movl    $1,%eax             # system call number (sys_exit)
	  int     $0x80               # call kernel

.data                           # section declaration

msg:
	.ascii    "Hello, Kworld!\n"   # our dear string
	len = . - msg                 # length of our dear string
