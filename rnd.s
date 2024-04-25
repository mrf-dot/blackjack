	.file	"rnd.c"
	.text
	.local	seeds
	.comm	seeds,32,32
	.globl	srnd
	.type	srnd, @function
srnd:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	-24(%rbp), %rax
	movl	$1, %edx
	movl	$8, %esi
	movq	%rax, %rdi
	call	getrandom@PLT
	cmpq	$-1, %rax
	jne	.L2
	movl	$1, %eax
	jmp	.L6
.L2:
	movl	$0, -28(%rbp)
	jmp	.L4
.L5:
	movq	-24(%rbp), %rax
	movabsq	$-7046029254386353131, %rdx
	addq	%rdx, %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	shrq	$30, %rax
	xorq	-16(%rbp), %rax
	movabsq	$-4658895280553007687, %rdx
	imulq	%rdx, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	shrq	$27, %rax
	xorq	-16(%rbp), %rax
	movabsq	$-7723592293110705685, %rdx
	imulq	%rdx, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	shrq	$31, %rax
	xorq	-16(%rbp), %rax
	movl	-28(%rbp), %edx
	movslq	%edx, %rdx
	leaq	0(,%rdx,8), %rcx
	leaq	seeds(%rip), %rdx
	movq	%rax, (%rcx,%rdx)
	addl	$1, -28(%rbp)
.L4:
	cmpl	$3, -28(%rbp)
	jle	.L5
	movl	$0, %eax
.L6:
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L7
	call	__stack_chk_fail@PLT
.L7:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	srnd, .-srnd
	.globl	rnd
	.type	rnd, @function
rnd:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	8+seeds(%rip), %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	rolq	$7, %rax
	movq	%rax, %rdx
	movq	%rdx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	movq	%rax, -16(%rbp)
	movq	8+seeds(%rip), %rax
	salq	$17, %rax
	movq	%rax, -8(%rbp)
	movq	16+seeds(%rip), %rdx
	movq	seeds(%rip), %rax
	xorq	%rdx, %rax
	movq	%rax, 16+seeds(%rip)
	movq	24+seeds(%rip), %rdx
	movq	8+seeds(%rip), %rax
	xorq	%rdx, %rax
	movq	%rax, 24+seeds(%rip)
	movq	8+seeds(%rip), %rdx
	movq	16+seeds(%rip), %rax
	xorq	%rdx, %rax
	movq	%rax, 8+seeds(%rip)
	movq	seeds(%rip), %rdx
	movq	24+seeds(%rip), %rax
	xorq	%rdx, %rax
	movq	%rax, seeds(%rip)
	movq	16+seeds(%rip), %rax
	xorq	-8(%rbp), %rax
	movq	%rax, 16+seeds(%rip)
	movq	24+seeds(%rip), %rax
	rorq	$19, %rax
	movq	%rax, 24+seeds(%rip)
	movq	-16(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	rnd, .-rnd
	.globl	rndint
	.type	rndint, @function
rndint:
.LFB8:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$8, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	$0, %eax
	call	rnd
	movl	-8(%rbp), %edx
	subl	-4(%rbp), %edx
	movslq	%edx, %rcx
	movl	$0, %edx
	divq	%rcx
	movq	%rdx, %rax
	movl	%eax, %edx
	movl	-4(%rbp), %eax
	addl	%edx, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	rndint, .-rndint
	.globl	shuffle
	.type	shuffle, @function
shuffle:
.LFB9:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	-28(%rbp), %eax
	subl	$1, %eax
	movl	%eax, -12(%rbp)
	jmp	.L13
.L14:
	movl	-12(%rbp), %eax
	addl	$1, %eax
	movl	%eax, %esi
	movl	$0, %edi
	call	rndint
	movl	%eax, -8(%rbp)
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, -4(%rbp)
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	-12(%rbp), %edx
	movslq	%edx, %rdx
	leaq	0(,%rdx,4), %rcx
	movq	-24(%rbp), %rdx
	addq	%rcx, %rdx
	movl	(%rax), %eax
	movl	%eax, (%rdx)
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rax, %rdx
	movl	-4(%rbp), %eax
	movl	%eax, (%rdx)
	subl	$1, -12(%rbp)
.L13:
	cmpl	$0, -12(%rbp)
	jg	.L14
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	shuffle, .-shuffle
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
