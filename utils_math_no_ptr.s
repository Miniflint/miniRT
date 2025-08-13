	.file	"utils_maths.c"
	.text
	.globl	vec_magnitude
	.type	vec_magnitude, @function
vec_magnitude:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movsd	(%rax), %xmm1
	movq	-8(%rbp), %rax
	movsd	(%rax), %xmm0
	mulsd	%xmm0, %xmm1
	movq	-8(%rbp), %rax
	movsd	8(%rax), %xmm2
	movq	-8(%rbp), %rax
	movsd	8(%rax), %xmm0
	mulsd	%xmm2, %xmm0
	addsd	%xmm0, %xmm1
	movq	-8(%rbp), %rax
	movsd	16(%rax), %xmm2
	movq	-8(%rbp), %rax
	movsd	16(%rax), %xmm0
	mulsd	%xmm2, %xmm0
	addsd	%xmm0, %xmm1
	movq	%xmm1, %rax
	movq	%rax, %xmm0
	call	sqrt@PLT
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	vec_magnitude, .-vec_magnitude
	.globl	add_vectors
	.type	add_vectors, @function
add_vectors:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-8(%rbp), %rax
	movsd	(%rax), %xmm1
	movq	-16(%rbp), %rax
	movsd	(%rax), %xmm0
	addsd	%xmm1, %xmm0
	movq	-24(%rbp), %rax
	movsd	%xmm0, (%rax)
	movq	-8(%rbp), %rax
	movsd	8(%rax), %xmm1
	movq	-16(%rbp), %rax
	movsd	8(%rax), %xmm0
	addsd	%xmm1, %xmm0
	movq	-24(%rbp), %rax
	movsd	%xmm0, 8(%rax)
	movq	-8(%rbp), %rax
	movsd	16(%rax), %xmm1
	movq	-16(%rbp), %rax
	movsd	16(%rax), %xmm0
	addsd	%xmm1, %xmm0
	movq	-24(%rbp), %rax
	movsd	%xmm0, 16(%rax)
	movq	-24(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	add_vectors, .-add_vectors
	.globl	sub_vectors
	.type	sub_vectors, @function
sub_vectors:
.LFB8:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-8(%rbp), %rax
	movsd	(%rax), %xmm0
	movq	-16(%rbp), %rax
	movsd	(%rax), %xmm1
	subsd	%xmm1, %xmm0
	movq	-24(%rbp), %rax
	movsd	%xmm0, (%rax)
	movq	-8(%rbp), %rax
	movsd	8(%rax), %xmm0
	movq	-16(%rbp), %rax
	movsd	8(%rax), %xmm1
	subsd	%xmm1, %xmm0
	movq	-24(%rbp), %rax
	movsd	%xmm0, 8(%rax)
	movq	-8(%rbp), %rax
	movsd	16(%rax), %xmm0
	movq	-16(%rbp), %rax
	movsd	16(%rax), %xmm1
	subsd	%xmm1, %xmm0
	movq	-24(%rbp), %rax
	movsd	%xmm0, 16(%rax)
	movq	-24(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	sub_vectors, .-sub_vectors
	.globl	mul_vectors
	.type	mul_vectors, @function
mul_vectors:
.LFB9:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-8(%rbp), %rax
	movsd	(%rax), %xmm1
	movq	-16(%rbp), %rax
	movsd	(%rax), %xmm0
	mulsd	%xmm1, %xmm0
	movq	-24(%rbp), %rax
	movsd	%xmm0, (%rax)
	movq	-8(%rbp), %rax
	movsd	8(%rax), %xmm1
	movq	-16(%rbp), %rax
	movsd	8(%rax), %xmm0
	mulsd	%xmm1, %xmm0
	movq	-24(%rbp), %rax
	movsd	%xmm0, 8(%rax)
	movq	-8(%rbp), %rax
	movsd	16(%rax), %xmm1
	movq	-16(%rbp), %rax
	movsd	16(%rax), %xmm0
	mulsd	%xmm1, %xmm0
	movq	-24(%rbp), %rax
	movsd	%xmm0, 16(%rax)
	movq	-24(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	mul_vectors, .-mul_vectors
	.globl	div_vectors
	.type	div_vectors, @function
div_vectors:
.LFB10:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-8(%rbp), %rax
	movsd	(%rax), %xmm0
	movq	-16(%rbp), %rax
	movsd	(%rax), %xmm1
	divsd	%xmm1, %xmm0
	movq	-24(%rbp), %rax
	movsd	%xmm0, (%rax)
	movq	-8(%rbp), %rax
	movsd	8(%rax), %xmm0
	movq	-16(%rbp), %rax
	movsd	8(%rax), %xmm1
	divsd	%xmm1, %xmm0
	movq	-24(%rbp), %rax
	movsd	%xmm0, 8(%rax)
	movq	-8(%rbp), %rax
	movsd	16(%rax), %xmm0
	movq	-16(%rbp), %rax
	movsd	16(%rax), %xmm1
	divsd	%xmm1, %xmm0
	movq	-24(%rbp), %rax
	movsd	%xmm0, 16(%rax)
	movq	-24(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	div_vectors, .-div_vectors
	.globl	scalar_multiplication
	.type	scalar_multiplication, @function
scalar_multiplication:
.LFB11:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movsd	%xmm0, -16(%rbp)
	movq	%rsi, -24(%rbp)
	movq	-8(%rbp), %rax
	movsd	(%rax), %xmm0
	mulsd	-16(%rbp), %xmm0
	movq	-24(%rbp), %rax
	movsd	%xmm0, (%rax)
	movq	-8(%rbp), %rax
	movsd	8(%rax), %xmm0
	mulsd	-16(%rbp), %xmm0
	movq	-24(%rbp), %rax
	movsd	%xmm0, 8(%rax)
	movq	-8(%rbp), %rax
	movsd	16(%rax), %xmm0
	mulsd	-16(%rbp), %xmm0
	movq	-24(%rbp), %rax
	movsd	%xmm0, 16(%rax)
	movq	-24(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	scalar_multiplication, .-scalar_multiplication
	.globl	norm_vectors
	.type	norm_vectors, @function
norm_vectors:
.LFB12:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movsd	%xmm0, -16(%rbp)
	movq	%rsi, -24(%rbp)
	movq	-8(%rbp), %rax
	movsd	(%rax), %xmm0
	divsd	-16(%rbp), %xmm0
	movq	-24(%rbp), %rax
	movsd	%xmm0, (%rax)
	movq	-8(%rbp), %rax
	movsd	8(%rax), %xmm0
	divsd	-16(%rbp), %xmm0
	movq	-24(%rbp), %rax
	movsd	%xmm0, 8(%rax)
	movq	-8(%rbp), %rax
	movsd	16(%rax), %xmm0
	divsd	-16(%rbp), %xmm0
	movq	-24(%rbp), %rax
	movsd	%xmm0, 16(%rax)
	movq	-24(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	norm_vectors, .-norm_vectors
	.globl	dot_product
	.type	dot_product, @function
dot_product:
.LFB13:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movsd	16(%rbp), %xmm1
	movsd	40(%rbp), %xmm0
	mulsd	%xmm0, %xmm1
	movsd	24(%rbp), %xmm2
	movsd	48(%rbp), %xmm0
	mulsd	%xmm2, %xmm0
	addsd	%xmm0, %xmm1
	movsd	32(%rbp), %xmm2
	movsd	56(%rbp), %xmm0
	mulsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	dot_product, .-dot_product
	.globl	get_angle
	.type	get_angle, @function
get_angle:
.LFB14:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movsd	%xmm0, -24(%rbp)
	movsd	%xmm1, -32(%rbp)
	movq	-16(%rbp), %rcx
	subq	$24, %rsp
	movq	%rsp, %rsi
	movq	(%rcx), %rax
	movq	8(%rcx), %rdx
	movq	%rax, (%rsi)
	movq	%rdx, 8(%rsi)
	movq	16(%rcx), %rax
	movq	%rax, 16(%rsi)
	movq	-8(%rbp), %rcx
	subq	$24, %rsp
	movq	%rsp, %rsi
	movq	(%rcx), %rax
	movq	8(%rcx), %rdx
	movq	%rax, (%rsi)
	movq	%rdx, 8(%rsi)
	movq	16(%rcx), %rax
	movq	%rax, 16(%rsi)
	call	dot_product
	addq	$48, %rsp
	movq	%xmm0, %rax
	movsd	-24(%rbp), %xmm0
	mulsd	-32(%rbp), %xmm0
	movq	%rax, %xmm2
	divsd	%xmm0, %xmm2
	movq	%xmm2, %rax
	movq	%rax, %xmm0
	call	acos@PLT
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE14:
	.size	get_angle, .-get_angle
	.globl	cross_product
	.type	cross_product, @function
cross_product:
.LFB15:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-8(%rbp), %rax
	movsd	8(%rax), %xmm1
	movq	-16(%rbp), %rax
	movsd	16(%rax), %xmm0
	mulsd	%xmm1, %xmm0
	movq	-8(%rbp), %rax
	movsd	16(%rax), %xmm2
	movq	-16(%rbp), %rax
	movsd	8(%rax), %xmm1
	mulsd	%xmm2, %xmm1
	subsd	%xmm1, %xmm0
	movq	-24(%rbp), %rax
	movsd	%xmm0, (%rax)
	movq	-8(%rbp), %rax
	movsd	16(%rax), %xmm1
	movq	-16(%rbp), %rax
	movsd	(%rax), %xmm0
	mulsd	%xmm1, %xmm0
	movq	-8(%rbp), %rax
	movsd	(%rax), %xmm2
	movq	-16(%rbp), %rax
	movsd	16(%rax), %xmm1
	mulsd	%xmm2, %xmm1
	subsd	%xmm1, %xmm0
	movq	-24(%rbp), %rax
	movsd	%xmm0, 8(%rax)
	movq	-8(%rbp), %rax
	movsd	(%rax), %xmm1
	movq	-16(%rbp), %rax
	movsd	8(%rax), %xmm0
	mulsd	%xmm1, %xmm0
	movq	-8(%rbp), %rax
	movsd	8(%rax), %xmm2
	movq	-16(%rbp), %rax
	movsd	(%rax), %xmm1
	mulsd	%xmm2, %xmm1
	subsd	%xmm1, %xmm0
	movq	-24(%rbp), %rax
	movsd	%xmm0, 16(%rax)
	movq	-24(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE15:
	.size	cross_product, .-cross_product
	.ident	"GCC: (Ubuntu 12.3.0-1ubuntu1~22.04) 12.3.0"
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
