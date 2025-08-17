	.file	"utils_maths.c"
	.text
	.p2align 4
	.globl	vec_magnitude
	.type	vec_magnitude, @function
vec_magnitude:
.LFB53:
	.cfi_startproc
	endbr64
	movsd	(%rdi), %xmm1
	movsd	8(%rdi), %xmm2
	movsd	16(%rdi), %xmm0
	mulsd	%xmm2, %xmm2
	mulsd	%xmm1, %xmm1
	mulsd	%xmm0, %xmm0
	addsd	%xmm2, %xmm1
	addsd	%xmm1, %xmm0
	sqrtsd	%xmm0, %xmm0
	ret
	.cfi_endproc
.LFE53:
	.size	vec_magnitude, .-vec_magnitude
	.p2align 4
	.globl	add_vectors
	.type	add_vectors, @function
add_vectors:
.LFB54:
	.cfi_startproc
	endbr64
	movupd	(%rdi), %xmm0
	movupd	(%rsi), %xmm1
	movq	%rdx, %rax
	addpd	%xmm1, %xmm0
	movups	%xmm0, (%rdx)
	movsd	16(%rdi), %xmm0
	addsd	16(%rsi), %xmm0
	movsd	%xmm0, 16(%rdx)
	ret
	.cfi_endproc
.LFE54:
	.size	add_vectors, .-add_vectors
	.p2align 4
	.globl	sub_vectors
	.type	sub_vectors, @function
sub_vectors:
.LFB55:
	.cfi_startproc
	endbr64
	movupd	(%rdi), %xmm0
	movupd	(%rsi), %xmm1
	movq	%rdx, %rax
	subpd	%xmm1, %xmm0
	movups	%xmm0, (%rdx)
	movsd	16(%rdi), %xmm0
	subsd	16(%rsi), %xmm0
	movsd	%xmm0, 16(%rdx)
	ret
	.cfi_endproc
.LFE55:
	.size	sub_vectors, .-sub_vectors
	.p2align 4
	.globl	mul_vectors
	.type	mul_vectors, @function
mul_vectors:
.LFB56:
	.cfi_startproc
	endbr64
	movupd	(%rdi), %xmm0
	movupd	(%rsi), %xmm1
	movq	%rdx, %rax
	mulpd	%xmm1, %xmm0
	movups	%xmm0, (%rdx)
	movsd	16(%rdi), %xmm0
	mulsd	16(%rsi), %xmm0
	movsd	%xmm0, 16(%rdx)
	ret
	.cfi_endproc
.LFE56:
	.size	mul_vectors, .-mul_vectors
	.p2align 4
	.globl	div_vectors
	.type	div_vectors, @function
div_vectors:
.LFB57:
	.cfi_startproc
	endbr64
	movupd	(%rdi), %xmm0
	movupd	(%rsi), %xmm1
	movq	%rdx, %rax
	divpd	%xmm1, %xmm0
	movups	%xmm0, (%rdx)
	movsd	16(%rdi), %xmm0
	divsd	16(%rsi), %xmm0
	movsd	%xmm0, 16(%rdx)
	ret
	.cfi_endproc
.LFE57:
	.size	div_vectors, .-div_vectors
	.p2align 4
	.globl	scalar_multiplication
	.type	scalar_multiplication, @function
scalar_multiplication:
.LFB58:
	.cfi_startproc
	endbr64
	movupd	(%rdi), %xmm2
	movapd	%xmm0, %xmm1
	movq	%rsi, %rax
	unpcklpd	%xmm1, %xmm1
	mulpd	%xmm2, %xmm1
	movups	%xmm1, (%rsi)
	mulsd	16(%rdi), %xmm0
	movsd	%xmm0, 16(%rsi)
	ret
	.cfi_endproc
.LFE58:
	.size	scalar_multiplication, .-scalar_multiplication
	.p2align 4
	.globl	norm_vectors
	.type	norm_vectors, @function
norm_vectors:
.LFB59:
	.cfi_startproc
	endbr64
	movupd	(%rdi), %xmm1
	movapd	%xmm0, %xmm2
	movq	%rsi, %rax
	unpcklpd	%xmm2, %xmm2
	divpd	%xmm2, %xmm1
	movups	%xmm1, (%rsi)
	movsd	16(%rdi), %xmm1
	divsd	%xmm0, %xmm1
	movsd	%xmm1, 16(%rsi)
	ret
	.cfi_endproc
.LFE59:
	.size	norm_vectors, .-norm_vectors
	.p2align 4
	.globl	dot_product
	.type	dot_product, @function
dot_product:
.LFB60:
	.cfi_startproc
	endbr64
	movsd	(%rdi), %xmm0
	movsd	8(%rdi), %xmm1
	mulsd	(%rsi), %xmm0
	mulsd	8(%rsi), %xmm1
	addsd	%xmm1, %xmm0
	movsd	16(%rdi), %xmm1
	mulsd	16(%rsi), %xmm1
	addsd	%xmm1, %xmm0
	ret
	.cfi_endproc
.LFE60:
	.size	dot_product, .-dot_product
	.p2align 4
	.globl	get_angle
	.type	get_angle, @function
get_angle:
.LFB61:
	.cfi_startproc
	endbr64
	movapd	%xmm0, %xmm2
	movsd	8(%rdi), %xmm3
	movsd	(%rdi), %xmm0
	mulsd	8(%rsi), %xmm3
	mulsd	(%rsi), %xmm0
	mulsd	%xmm1, %xmm2
	addsd	%xmm3, %xmm0
	movsd	16(%rdi), %xmm3
	mulsd	16(%rsi), %xmm3
	addsd	%xmm3, %xmm0
	divsd	%xmm2, %xmm0
	jmp	acos@PLT
	.cfi_endproc
.LFE61:
	.size	get_angle, .-get_angle
	.p2align 4
	.globl	cross_product
	.type	cross_product, @function
cross_product:
.LFB62:
	.cfi_startproc
	endbr64
	movsd	16(%rsi), %xmm3
	movsd	16(%rdi), %xmm1
	movq	%rdx, %rax
	movsd	8(%rdi), %xmm0
	movsd	8(%rsi), %xmm2
	mulsd	%xmm3, %xmm0
	mulsd	%xmm1, %xmm2
	subsd	%xmm2, %xmm0
	movsd	%xmm0, (%rdx)
	movsd	(%rsi), %xmm2
	movsd	(%rdi), %xmm0
	mulsd	%xmm2, %xmm1
	mulsd	%xmm0, %xmm3
	subsd	%xmm3, %xmm1
	movsd	%xmm1, 8(%rdx)
	mulsd	8(%rsi), %xmm0
	mulsd	8(%rdi), %xmm2
	subsd	%xmm2, %xmm0
	movsd	%xmm0, 16(%rdx)
	ret
	.cfi_endproc
.LFE62:
	.size	cross_product, .-cross_product
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0"
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
