	.file	"__init_utils.c"
# GNU C17 (Ubuntu 11.4.0-1ubuntu1~22.04) version 11.4.0 (x86_64-linux-gnu)
#	compiled by GNU C version 11.4.0, GMP version 6.2.1, MPFR version 4.1.0, MPC version 1.2.1, isl version isl-0.24-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed: -mtune=generic -march=x86-64 -O3 -fasynchronous-unwind-tables -fstack-protector-strong -fstack-clash-protection -fcf-protection
	.text
	.p2align 4
	.globl	parse_type_scene
	.type	parse_type_scene, @function
parse_type_scene:
.LFB53:
	.cfi_startproc
	endbr64	
	pushq	%r12	#
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movq	%rdi, %r12	# tmp126, all
	pushq	%rbp	#
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rsi, %rbp	# tmp127, s
	subq	$8, %rsp	#,
	.cfi_def_cfa_offset 32
# srcs/parsing/__init_utils.c:5: 	if (**s == 'A' && ft_iswhitespace(*((*s) + 1)))
	movq	(%rsi), %rdx	# *s_48(D), _1
# srcs/parsing/__init_utils.c:5: 	if (**s == 'A' && ft_iswhitespace(*((*s) + 1)))
	movzbl	(%rdx), %eax	# *_1, _2
# srcs/parsing/__init_utils.c:5: 	if (**s == 'A' && ft_iswhitespace(*((*s) + 1)))
	cmpb	$65, %al	#, _2
	je	.L20	#,
# srcs/parsing/__init_utils.c:7: 	else if (**s == 'C' && ft_iswhitespace(*((*s) + 1)))
	cmpb	$67, %al	#, _2
	je	.L21	#,
.L4:
# srcs/parsing/__init_utils.c:9: 	else if (**s == 'L' && ft_iswhitespace(*((*s) + 1)))
	cmpb	$76, %al	#, _2
	je	.L22	#,
.L6:
# srcs/parsing/__init_utils.c:11: 	else if (**s == 's' && *((*s) + 1) == 'p' && ft_iswhitespace(*((*s) + 2)))
	cmpb	$115, %al	#, _2
	je	.L23	#,
.L8:
# srcs/parsing/__init_utils.c:13: 	else if (**s == 'p' && *((*s) + 1) == 'l' && ft_iswhitespace(*((*s) + 2)))
	cmpb	$112, %al	#, _2
	je	.L24	#,
.L11:
# srcs/parsing/__init_utils.c:15: 	else if (**s == 'c' && *((*s) + 1) == 'y' && ft_iswhitespace(*((*s) + 2)))
	cmpb	$99, %al	#, _2
	jne	.L13	#,
# srcs/parsing/__init_utils.c:15: 	else if (**s == 'c' && *((*s) + 1) == 'y' && ft_iswhitespace(*((*s) + 2)))
	cmpb	$121, 1(%rdx)	#, MEM[(char *)prephitmp_94 + 1B]
	je	.L25	#,
.L13:
# srcs/parsing/__init_utils.c:18: }
	addq	$8, %rsp	#,
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	movl	$3, %eax	#,
	popq	%rbp	#
	.cfi_def_cfa_offset 16
	popq	%r12	#
	.cfi_def_cfa_offset 8
	ret	
	.p2align 4,,10
	.p2align 3
.L24:
	.cfi_restore_state
# srcs/parsing/__init_utils.c:13: 	else if (**s == 'p' && *((*s) + 1) == 'l' && ft_iswhitespace(*((*s) + 2)))
	cmpb	$108, 1(%rdx)	#, MEM[(char *)prephitmp_89 + 1B]
	jne	.L13	#,
# srcs/parsing/__init_utils.c:13: 	else if (**s == 'p' && *((*s) + 1) == 'l' && ft_iswhitespace(*((*s) + 2)))
	movsbl	2(%rdx), %edi	# MEM[(char *)prephitmp_89 + 2B], MEM[(char *)prephitmp_89 + 2B]
	call	ft_iswhitespace@PLT	#
# srcs/parsing/__init_utils.c:13: 	else if (**s == 'p' && *((*s) + 1) == 'l' && ft_iswhitespace(*((*s) + 2)))
	testl	%eax, %eax	# tmp132
	jne	.L14	#,
# srcs/parsing/__init_utils.c:15: 	else if (**s == 'c' && *((*s) + 1) == 'y' && ft_iswhitespace(*((*s) + 2)))
	movq	0(%rbp), %rdx	# *s_48(D), _1
# srcs/parsing/__init_utils.c:15: 	else if (**s == 'c' && *((*s) + 1) == 'y' && ft_iswhitespace(*((*s) + 2)))
	movzbl	(%rdx), %eax	# *pretmp_93, _2
	jmp	.L11	#
	.p2align 4,,10
	.p2align 3
.L23:
# srcs/parsing/__init_utils.c:11: 	else if (**s == 's' && *((*s) + 1) == 'p' && ft_iswhitespace(*((*s) + 2)))
	cmpb	$112, 1(%rdx)	#, MEM[(char *)prephitmp_84 + 1B]
	jne	.L13	#,
# srcs/parsing/__init_utils.c:11: 	else if (**s == 's' && *((*s) + 1) == 'p' && ft_iswhitespace(*((*s) + 2)))
	movsbl	2(%rdx), %edi	# MEM[(char *)prephitmp_84 + 2B], MEM[(char *)prephitmp_84 + 2B]
	call	ft_iswhitespace@PLT	#
# srcs/parsing/__init_utils.c:11: 	else if (**s == 's' && *((*s) + 1) == 'p' && ft_iswhitespace(*((*s) + 2)))
	testl	%eax, %eax	# tmp131
	jne	.L10	#,
# srcs/parsing/__init_utils.c:13: 	else if (**s == 'p' && *((*s) + 1) == 'l' && ft_iswhitespace(*((*s) + 2)))
	movq	0(%rbp), %rdx	# *s_48(D), _1
# srcs/parsing/__init_utils.c:13: 	else if (**s == 'p' && *((*s) + 1) == 'l' && ft_iswhitespace(*((*s) + 2)))
	movzbl	(%rdx), %eax	# *pretmp_88, _2
	jmp	.L8	#
	.p2align 4,,10
	.p2align 3
.L20:
# srcs/parsing/__init_utils.c:5: 	if (**s == 'A' && ft_iswhitespace(*((*s) + 1)))
	movsbl	1(%rdx), %edi	# MEM[(char *)_1 + 1B], MEM[(char *)_1 + 1B]
	call	ft_iswhitespace@PLT	#
# srcs/parsing/__init_utils.c:5: 	if (**s == 'A' && ft_iswhitespace(*((*s) + 1)))
	testl	%eax, %eax	# tmp128
	jne	.L3	#,
# srcs/parsing/__init_utils.c:7: 	else if (**s == 'C' && ft_iswhitespace(*((*s) + 1)))
	movq	0(%rbp), %rdx	# *s_48(D), _1
# srcs/parsing/__init_utils.c:7: 	else if (**s == 'C' && ft_iswhitespace(*((*s) + 1)))
	movzbl	(%rdx), %eax	# *pretmp_71, _2
# srcs/parsing/__init_utils.c:7: 	else if (**s == 'C' && ft_iswhitespace(*((*s) + 1)))
	cmpb	$67, %al	#, _2
	jne	.L4	#,
	.p2align 4,,10
	.p2align 3
.L21:
# srcs/parsing/__init_utils.c:7: 	else if (**s == 'C' && ft_iswhitespace(*((*s) + 1)))
	movsbl	1(%rdx), %edi	# MEM[(char *)prephitmp_74 + 1B], MEM[(char *)prephitmp_74 + 1B]
	call	ft_iswhitespace@PLT	#
# srcs/parsing/__init_utils.c:7: 	else if (**s == 'C' && ft_iswhitespace(*((*s) + 1)))
	testl	%eax, %eax	# tmp129
	jne	.L5	#,
# srcs/parsing/__init_utils.c:9: 	else if (**s == 'L' && ft_iswhitespace(*((*s) + 1)))
	movq	0(%rbp), %rdx	# *s_48(D), _1
# srcs/parsing/__init_utils.c:9: 	else if (**s == 'L' && ft_iswhitespace(*((*s) + 1)))
	movzbl	(%rdx), %eax	# *pretmp_78, _2
# srcs/parsing/__init_utils.c:9: 	else if (**s == 'L' && ft_iswhitespace(*((*s) + 1)))
	cmpb	$76, %al	#, _2
	jne	.L6	#,
	.p2align 4,,10
	.p2align 3
.L22:
# srcs/parsing/__init_utils.c:9: 	else if (**s == 'L' && ft_iswhitespace(*((*s) + 1)))
	movsbl	1(%rdx), %edi	# MEM[(char *)prephitmp_79 + 1B], MEM[(char *)prephitmp_79 + 1B]
	call	ft_iswhitespace@PLT	#
# srcs/parsing/__init_utils.c:9: 	else if (**s == 'L' && ft_iswhitespace(*((*s) + 1)))
	testl	%eax, %eax	# tmp130
	jne	.L7	#,
# srcs/parsing/__init_utils.c:11: 	else if (**s == 's' && *((*s) + 1) == 'p' && ft_iswhitespace(*((*s) + 2)))
	movq	0(%rbp), %rdx	# *s_48(D), _1
# srcs/parsing/__init_utils.c:11: 	else if (**s == 's' && *((*s) + 1) == 'p' && ft_iswhitespace(*((*s) + 2)))
	movzbl	(%rdx), %eax	# *pretmp_83, _2
	jmp	.L6	#
	.p2align 4,,10
	.p2align 3
.L25:
# srcs/parsing/__init_utils.c:15: 	else if (**s == 'c' && *((*s) + 1) == 'y' && ft_iswhitespace(*((*s) + 2)))
	movsbl	2(%rdx), %edi	# MEM[(char *)prephitmp_94 + 2B], MEM[(char *)prephitmp_94 + 2B]
	call	ft_iswhitespace@PLT	#
# srcs/parsing/__init_utils.c:15: 	else if (**s == 'c' && *((*s) + 1) == 'y' && ft_iswhitespace(*((*s) + 2)))
	testl	%eax, %eax	# tmp133
	je	.L13	#,
# srcs/parsing/__init_utils.c:18: }
	addq	$8, %rsp	#,
	.cfi_remember_state
	.cfi_def_cfa_offset 24
# srcs/parsing/__init_utils.c:16: 		return (get_cylinder(&all->cylinders, s));
	leaq	112(%r12), %rdi	#, tmp124
	movq	%rbp, %rsi	# s,
# srcs/parsing/__init_utils.c:18: }
	popq	%rbp	#
	.cfi_def_cfa_offset 16
	popq	%r12	#
	.cfi_def_cfa_offset 8
# srcs/parsing/__init_utils.c:16: 		return (get_cylinder(&all->cylinders, s));
	jmp	get_cylinder@PLT	#
	.p2align 4,,10
	.p2align 3
.L3:
	.cfi_restore_state
# srcs/parsing/__init_utils.c:18: }
	addq	$8, %rsp	#,
	.cfi_remember_state
	.cfi_def_cfa_offset 24
# srcs/parsing/__init_utils.c:6: 		return (get_ambient_light(&all->ambient_light, s));
	movq	%rbp, %rsi	# s,
	movq	%r12, %rdi	# all,
# srcs/parsing/__init_utils.c:18: }
	popq	%rbp	#
	.cfi_def_cfa_offset 16
	popq	%r12	#
	.cfi_def_cfa_offset 8
# srcs/parsing/__init_utils.c:6: 		return (get_ambient_light(&all->ambient_light, s));
	jmp	get_ambient_light@PLT	#
	.p2align 4,,10
	.p2align 3
.L10:
	.cfi_restore_state
# srcs/parsing/__init_utils.c:18: }
	addq	$8, %rsp	#,
	.cfi_remember_state
	.cfi_def_cfa_offset 24
# srcs/parsing/__init_utils.c:12: 		return (get_sphere(&all->spheres, s));
	leaq	96(%r12), %rdi	#, tmp120
	movq	%rbp, %rsi	# s,
# srcs/parsing/__init_utils.c:18: }
	popq	%rbp	#
	.cfi_def_cfa_offset 16
	popq	%r12	#
	.cfi_def_cfa_offset 8
# srcs/parsing/__init_utils.c:12: 		return (get_sphere(&all->spheres, s));
	jmp	get_sphere@PLT	#
	.p2align 4,,10
	.p2align 3
.L14:
	.cfi_restore_state
# srcs/parsing/__init_utils.c:18: }
	addq	$8, %rsp	#,
	.cfi_remember_state
	.cfi_def_cfa_offset 24
# srcs/parsing/__init_utils.c:14: 		return (get_plane(&all->planes, s));
	leaq	104(%r12), %rdi	#, tmp122
	movq	%rbp, %rsi	# s,
# srcs/parsing/__init_utils.c:18: }
	popq	%rbp	#
	.cfi_def_cfa_offset 16
	popq	%r12	#
	.cfi_def_cfa_offset 8
# srcs/parsing/__init_utils.c:14: 		return (get_plane(&all->planes, s));
	jmp	get_plane@PLT	#
	.p2align 4,,10
	.p2align 3
.L5:
	.cfi_restore_state
# srcs/parsing/__init_utils.c:18: }
	addq	$8, %rsp	#,
	.cfi_remember_state
	.cfi_def_cfa_offset 24
# srcs/parsing/__init_utils.c:8: 		return (get_camera(&all->camera, s));
	leaq	24(%r12), %rdi	#, tmp116
	movq	%rbp, %rsi	# s,
# srcs/parsing/__init_utils.c:18: }
	popq	%rbp	#
	.cfi_def_cfa_offset 16
	popq	%r12	#
	.cfi_def_cfa_offset 8
# srcs/parsing/__init_utils.c:8: 		return (get_camera(&all->camera, s));
	jmp	get_camera@PLT	#
	.p2align 4,,10
	.p2align 3
.L7:
	.cfi_restore_state
# srcs/parsing/__init_utils.c:18: }
	addq	$8, %rsp	#,
	.cfi_def_cfa_offset 24
# srcs/parsing/__init_utils.c:10: 		return (get_light(&all->lights, s));
	leaq	88(%r12), %rdi	#, tmp118
	movq	%rbp, %rsi	# s,
# srcs/parsing/__init_utils.c:18: }
	popq	%rbp	#
	.cfi_def_cfa_offset 16
	popq	%r12	#
	.cfi_def_cfa_offset 8
# srcs/parsing/__init_utils.c:10: 		return (get_light(&all->lights, s));
	jmp	get_light@PLT	#
	.cfi_endproc
.LFE53:
	.size	parse_type_scene, .-parse_type_scene
	.p2align 4
	.globl	parse_type_objs
	.type	parse_type_objs, @function
parse_type_objs:
.LFB54:
	.cfi_startproc
	endbr64	
	pushq	%r12	#
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movq	%rdi, %r12	# tmp173, object
	pushq	%rbp	#
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rsi, %rbp	# tmp174, s
	subq	$8, %rsp	#,
	.cfi_def_cfa_offset 32
# srcs/parsing/__init_utils.c:22: 	if (**s == 'o' && ft_iswhitespace(*((*s) + 1)))
	movq	(%rsi), %rdx	# *s_65(D), _1
# srcs/parsing/__init_utils.c:22: 	if (**s == 'o' && ft_iswhitespace(*((*s) + 1)))
	movzbl	(%rdx), %eax	# *_1, _2
# srcs/parsing/__init_utils.c:22: 	if (**s == 'o' && ft_iswhitespace(*((*s) + 1)))
	cmpb	$111, %al	#, _2
	je	.L46	#,
# srcs/parsing/__init_utils.c:24: 	else if (**s == 'v' && ft_iswhitespace(*((*s) + 1)))
	cmpb	$118, %al	#, _2
	je	.L47	#,
.L33:
# srcs/parsing/__init_utils.c:30: 	else if (**s == 'f' && ft_iswhitespace(*((*s) + 1)))
	cmpb	$102, %al	#, _2
	je	.L48	#,
# srcs/parsing/__init_utils.c:32: 	else if (**s == 's' && ft_iswhitespace(*((*s) + 1)))
	cmpb	$115, %al	#, _2
	je	.L49	#,
.L39:
# srcs/parsing/__init_utils.c:39: }
	addq	$8, %rsp	#,
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	movl	$3, %eax	#,
	popq	%rbp	#
	.cfi_def_cfa_offset 16
	popq	%r12	#
	.cfi_def_cfa_offset 8
	ret	
	.p2align 4,,10
	.p2align 3
.L49:
	.cfi_restore_state
# srcs/parsing/__init_utils.c:32: 	else if (**s == 's' && ft_iswhitespace(*((*s) + 1)))
	movsbl	1(%rdx), %edi	# MEM[(char *)prephitmp_110 + 1B], MEM[(char *)prephitmp_110 + 1B]
	call	ft_iswhitespace@PLT	#
# srcs/parsing/__init_utils.c:32: 	else if (**s == 's' && ft_iswhitespace(*((*s) + 1)))
	testl	%eax, %eax	# tmp180
	je	.L39	#,
# srcs/parsing/__init_utils.c:39: }
	addq	$8, %rsp	#,
	.cfi_remember_state
	.cfi_def_cfa_offset 24
# srcs/parsing/__init_utils.c:33: 		return (get_smoothing(&object->curr_smoothing, s));
	leaq	176(%r12), %rdi	#, tmp171
	movq	%rbp, %rsi	# s,
# srcs/parsing/__init_utils.c:39: }
	popq	%rbp	#
	.cfi_def_cfa_offset 16
	popq	%r12	#
	.cfi_def_cfa_offset 8
# srcs/parsing/__init_utils.c:33: 		return (get_smoothing(&object->curr_smoothing, s));
	jmp	get_smoothing@PLT	#
	.p2align 4,,10
	.p2align 3
.L46:
	.cfi_restore_state
# srcs/parsing/__init_utils.c:22: 	if (**s == 'o' && ft_iswhitespace(*((*s) + 1)))
	movsbl	1(%rdx), %edi	# MEM[(char *)_1 + 1B], MEM[(char *)_1 + 1B]
	call	ft_iswhitespace@PLT	#
# srcs/parsing/__init_utils.c:22: 	if (**s == 'o' && ft_iswhitespace(*((*s) + 1)))
	testl	%eax, %eax	# tmp175
	jne	.L28	#,
# srcs/parsing/__init_utils.c:24: 	else if (**s == 'v' && ft_iswhitespace(*((*s) + 1)))
	movq	0(%rbp), %rdx	# *s_65(D), _1
# srcs/parsing/__init_utils.c:24: 	else if (**s == 'v' && ft_iswhitespace(*((*s) + 1)))
	movzbl	(%rdx), %eax	# *pretmp_59, _2
# srcs/parsing/__init_utils.c:24: 	else if (**s == 'v' && ft_iswhitespace(*((*s) + 1)))
	cmpb	$118, %al	#, _2
	jne	.L33	#,
	.p2align 4,,10
	.p2align 3
.L47:
# srcs/parsing/__init_utils.c:24: 	else if (**s == 'v' && ft_iswhitespace(*((*s) + 1)))
	movsbl	1(%rdx), %edi	# MEM[(char *)prephitmp_87 + 1B], MEM[(char *)prephitmp_87 + 1B]
	call	ft_iswhitespace@PLT	#
# srcs/parsing/__init_utils.c:24: 	else if (**s == 'v' && ft_iswhitespace(*((*s) + 1)))
	testl	%eax, %eax	# tmp176
	jne	.L50	#,
# srcs/parsing/__init_utils.c:26: 	else if (**s == 'v' && *((*s) + 1) == 't' && ft_iswhitespace(*((*s) + 2)))
	movq	0(%rbp), %rdx	# *s_65(D), _1
# srcs/parsing/__init_utils.c:26: 	else if (**s == 'v' && *((*s) + 1) == 't' && ft_iswhitespace(*((*s) + 2)))
	movzbl	(%rdx), %eax	# *_17, _2
# srcs/parsing/__init_utils.c:26: 	else if (**s == 'v' && *((*s) + 1) == 't' && ft_iswhitespace(*((*s) + 2)))
	cmpb	$118, %al	#, _2
	jne	.L33	#,
# srcs/parsing/__init_utils.c:26: 	else if (**s == 'v' && *((*s) + 1) == 't' && ft_iswhitespace(*((*s) + 2)))
	movzbl	1(%rdx), %eax	# MEM[(char *)_17 + 1B], _19
# srcs/parsing/__init_utils.c:26: 	else if (**s == 'v' && *((*s) + 1) == 't' && ft_iswhitespace(*((*s) + 2)))
	cmpb	$116, %al	#, _19
	je	.L51	#,
.L31:
# srcs/parsing/__init_utils.c:28: 	else if (**s == 'v' && *((*s) + 1) == 'n' && ft_iswhitespace(*((*s) + 2)))
	cmpb	$110, %al	#, _19
	jne	.L39	#,
# srcs/parsing/__init_utils.c:28: 	else if (**s == 'v' && *((*s) + 1) == 'n' && ft_iswhitespace(*((*s) + 2)))
	movsbl	2(%rdx), %edi	# MEM[(char *)_97 + 2B], MEM[(char *)_97 + 2B]
	call	ft_iswhitespace@PLT	#
# srcs/parsing/__init_utils.c:28: 	else if (**s == 'v' && *((*s) + 1) == 'n' && ft_iswhitespace(*((*s) + 2)))
	testl	%eax, %eax	# tmp178
	jne	.L35	#,
# srcs/parsing/__init_utils.c:30: 	else if (**s == 'f' && ft_iswhitespace(*((*s) + 1)))
	movq	0(%rbp), %rdx	# *s_65(D), _1
# srcs/parsing/__init_utils.c:30: 	else if (**s == 'f' && ft_iswhitespace(*((*s) + 1)))
	movzbl	(%rdx), %eax	# *pretmp_104, _2
	jmp	.L33	#
	.p2align 4,,10
	.p2align 3
.L48:
# srcs/parsing/__init_utils.c:30: 	else if (**s == 'f' && ft_iswhitespace(*((*s) + 1)))
	movsbl	1(%rdx), %edi	# MEM[(char *)prephitmp_105 + 1B], MEM[(char *)prephitmp_105 + 1B]
	call	ft_iswhitespace@PLT	#
# srcs/parsing/__init_utils.c:30: 	else if (**s == 'f' && ft_iswhitespace(*((*s) + 1)))
	testl	%eax, %eax	# tmp179
	jne	.L37	#,
# srcs/parsing/__init_utils.c:32: 	else if (**s == 's' && ft_iswhitespace(*((*s) + 1)))
	movq	0(%rbp), %rdx	# *s_65(D), _1
# srcs/parsing/__init_utils.c:32: 	else if (**s == 's' && ft_iswhitespace(*((*s) + 1)))
	movzbl	(%rdx), %eax	# *pretmp_109, _2
# srcs/parsing/__init_utils.c:32: 	else if (**s == 's' && ft_iswhitespace(*((*s) + 1)))
	cmpb	$115, %al	#, _2
	jne	.L39	#,
	jmp	.L49	#
	.p2align 4,,10
	.p2align 3
.L51:
# srcs/parsing/__init_utils.c:26: 	else if (**s == 'v' && *((*s) + 1) == 't' && ft_iswhitespace(*((*s) + 2)))
	movsbl	2(%rdx), %edi	# MEM[(char *)_17 + 2B], MEM[(char *)_17 + 2B]
	call	ft_iswhitespace@PLT	#
# srcs/parsing/__init_utils.c:26: 	else if (**s == 'v' && *((*s) + 1) == 't' && ft_iswhitespace(*((*s) + 2)))
	testl	%eax, %eax	# tmp177
	jne	.L52	#,
# srcs/parsing/__init_utils.c:28: 	else if (**s == 'v' && *((*s) + 1) == 'n' && ft_iswhitespace(*((*s) + 2)))
	movq	0(%rbp), %rdx	# *s_65(D), _1
# srcs/parsing/__init_utils.c:28: 	else if (**s == 'v' && *((*s) + 1) == 'n' && ft_iswhitespace(*((*s) + 2)))
	movzbl	(%rdx), %eax	# *_28, _2
# srcs/parsing/__init_utils.c:28: 	else if (**s == 'v' && *((*s) + 1) == 'n' && ft_iswhitespace(*((*s) + 2)))
	cmpb	$118, %al	#, _2
	jne	.L33	#,
# srcs/parsing/__init_utils.c:28: 	else if (**s == 'v' && *((*s) + 1) == 'n' && ft_iswhitespace(*((*s) + 2)))
	movzbl	1(%rdx), %eax	# MEM[(char *)_28 + 1B], _19
	jmp	.L31	#
	.p2align 4,,10
	.p2align 3
.L28:
# srcs/parsing/__init_utils.c:39: }
	addq	$8, %rsp	#,
	.cfi_remember_state
	.cfi_def_cfa_offset 24
# srcs/parsing/__init_utils.c:23: 		return (get_name(object->name, s));
	movq	%rbp, %rsi	# s,
	movq	%r12, %rdi	# object,
# srcs/parsing/__init_utils.c:39: }
	popq	%rbp	#
	.cfi_def_cfa_offset 16
	popq	%r12	#
	.cfi_def_cfa_offset 8
# srcs/parsing/__init_utils.c:23: 		return (get_name(object->name, s));
	jmp	get_name@PLT	#
	.p2align 4,,10
	.p2align 3
.L35:
	.cfi_restore_state
# srcs/parsing/__init_utils.c:29: 		return (get_vertices(&(object->vn[object->i_vertice[I_VN]]), s, 2, &(object->i_vertice[I_VN])));
	movq	216(%r12), %rax	# object_67(D)->i_vertice[2], object_67(D)->i_vertice[2]
# srcs/parsing/__init_utils.c:29: 		return (get_vertices(&(object->vn[object->i_vertice[I_VN]]), s, 2, &(object->i_vertice[I_VN])));
	leaq	216(%r12), %rcx	#, tmp150
# srcs/parsing/__init_utils.c:29: 		return (get_vertices(&(object->vn[object->i_vertice[I_VN]]), s, 2, &(object->i_vertice[I_VN])));
	leaq	(%rax,%rax,2), %rdx	#, tmp154
# srcs/parsing/__init_utils.c:29: 		return (get_vertices(&(object->vn[object->i_vertice[I_VN]]), s, 2, &(object->i_vertice[I_VN])));
	movq	152(%r12), %rax	# object_67(D)->vn, object_67(D)->vn
.L45:
# srcs/parsing/__init_utils.c:27: 		return (get_vertices(&(object->vt[object->i_vertice[I_VT]]), s, 2, &(object->i_vertice[I_VT])));
	leaq	(%rax,%rdx,8), %rdi	#, tmp147
# srcs/parsing/__init_utils.c:27: 		return (get_vertices(&(object->vt[object->i_vertice[I_VT]]), s, 2, &(object->i_vertice[I_VT])));
	movl	$2, %edx	#,
.L44:
# srcs/parsing/__init_utils.c:39: }
	addq	$8, %rsp	#,
	.cfi_remember_state
	.cfi_def_cfa_offset 24
# srcs/parsing/__init_utils.c:27: 		return (get_vertices(&(object->vt[object->i_vertice[I_VT]]), s, 2, &(object->i_vertice[I_VT])));
	movq	%rbp, %rsi	# s,
# srcs/parsing/__init_utils.c:39: }
	popq	%rbp	#
	.cfi_def_cfa_offset 16
	popq	%r12	#
	.cfi_def_cfa_offset 8
# srcs/parsing/__init_utils.c:27: 		return (get_vertices(&(object->vt[object->i_vertice[I_VT]]), s, 2, &(object->i_vertice[I_VT])));
	jmp	get_vertices@PLT	#
	.p2align 4,,10
	.p2align 3
.L50:
	.cfi_restore_state
# srcs/parsing/__init_utils.c:25: 		return (get_vertices(&(object->vertices[object->i_vertice[I_V]]), s, 1, &(object->i_vertice[I_V])));
	movq	200(%r12), %rax	# object_67(D)->i_vertice[0], object_67(D)->i_vertice[0]
# srcs/parsing/__init_utils.c:25: 		return (get_vertices(&(object->vertices[object->i_vertice[I_V]]), s, 1, &(object->i_vertice[I_V])));
	leaq	200(%r12), %rcx	#, tmp132
# srcs/parsing/__init_utils.c:25: 		return (get_vertices(&(object->vertices[object->i_vertice[I_V]]), s, 1, &(object->i_vertice[I_V])));
	leaq	(%rax,%rax,2), %rdx	#, tmp136
# srcs/parsing/__init_utils.c:25: 		return (get_vertices(&(object->vertices[object->i_vertice[I_V]]), s, 1, &(object->i_vertice[I_V])));
	movq	136(%r12), %rax	# object_67(D)->vertices, object_67(D)->vertices
	leaq	(%rax,%rdx,8), %rdi	#, tmp138
	movl	$1, %edx	#,
	jmp	.L44	#
	.p2align 4,,10
	.p2align 3
.L37:
# srcs/parsing/__init_utils.c:31: 		return (get_faces(&(object->faces[object->indexes[I_FACES]]), s, object->curr_smoothing, &(object->indexes[I_FACES])));
	movq	184(%r12), %rax	# object_67(D)->indexes[0], object_67(D)->indexes[0]
# srcs/parsing/__init_utils.c:31: 		return (get_faces(&(object->faces[object->indexes[I_FACES]]), s, object->curr_smoothing, &(object->indexes[I_FACES])));
	leaq	184(%r12), %rcx	#, tmp159
	movzbl	176(%r12), %edx	# object_67(D)->curr_smoothing, object_67(D)->curr_smoothing
# srcs/parsing/__init_utils.c:31: 		return (get_faces(&(object->faces[object->indexes[I_FACES]]), s, object->curr_smoothing, &(object->indexes[I_FACES])));
	leaq	(%rax,%rax,2), %rsi	#, tmp164
	leaq	(%rax,%rsi,4), %rdi	#, tmp166
# srcs/parsing/__init_utils.c:31: 		return (get_faces(&(object->faces[object->indexes[I_FACES]]), s, object->curr_smoothing, &(object->indexes[I_FACES])));
	movq	%rbp, %rsi	# s,
# srcs/parsing/__init_utils.c:31: 		return (get_faces(&(object->faces[object->indexes[I_FACES]]), s, object->curr_smoothing, &(object->indexes[I_FACES])));
	salq	$4, %rdi	#, tmp167
# srcs/parsing/__init_utils.c:31: 		return (get_faces(&(object->faces[object->indexes[I_FACES]]), s, object->curr_smoothing, &(object->indexes[I_FACES])));
	addq	160(%r12), %rdi	# object_67(D)->faces, tmp168
# srcs/parsing/__init_utils.c:39: }
	addq	$8, %rsp	#,
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp	#
	.cfi_def_cfa_offset 16
	popq	%r12	#
	.cfi_def_cfa_offset 8
# srcs/parsing/__init_utils.c:31: 		return (get_faces(&(object->faces[object->indexes[I_FACES]]), s, object->curr_smoothing, &(object->indexes[I_FACES])));
	jmp	get_faces@PLT	#
	.p2align 4,,10
	.p2align 3
.L52:
	.cfi_restore_state
# srcs/parsing/__init_utils.c:27: 		return (get_vertices(&(object->vt[object->i_vertice[I_VT]]), s, 2, &(object->i_vertice[I_VT])));
	movq	208(%r12), %rax	# object_67(D)->i_vertice[1], object_67(D)->i_vertice[1]
# srcs/parsing/__init_utils.c:27: 		return (get_vertices(&(object->vt[object->i_vertice[I_VT]]), s, 2, &(object->i_vertice[I_VT])));
	leaq	208(%r12), %rcx	#, tmp141
# srcs/parsing/__init_utils.c:27: 		return (get_vertices(&(object->vt[object->i_vertice[I_VT]]), s, 2, &(object->i_vertice[I_VT])));
	leaq	(%rax,%rax,2), %rdx	#, tmp145
# srcs/parsing/__init_utils.c:27: 		return (get_vertices(&(object->vt[object->i_vertice[I_VT]]), s, 2, &(object->i_vertice[I_VT])));
	movq	144(%r12), %rax	# object_67(D)->vt, object_67(D)->vt
	jmp	.L45	#
	.cfi_endproc
.LFE54:
	.size	parse_type_objs, .-parse_type_objs
	.p2align 4
	.globl	print_all_structs
	.type	print_all_structs, @function
print_all_structs:
.LFB55:
	.cfi_startproc
	endbr64	
	pushq	%rbx	#
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
# srcs/parsing/__init_utils.c:43: 	print_ac(&all->ambient_light, &all->camera);
	leaq	24(%rdi), %rsi	#, tmp89
# srcs/parsing/__init_utils.c:42: {
	movq	%rdi, %rbx	# tmp94, all
# srcs/parsing/__init_utils.c:43: 	print_ac(&all->ambient_light, &all->camera);
	call	print_ac@PLT	#
# srcs/parsing/__init_utils.c:44: 	print_l(all->lights, 0);
	movq	88(%rbx), %rdi	# all_7(D)->lights, all_7(D)->lights
	xorl	%esi, %esi	#
	call	print_l@PLT	#
# srcs/parsing/__init_utils.c:45: 	print_sp(all->spheres, 0);
	movq	96(%rbx), %rdi	# all_7(D)->spheres, all_7(D)->spheres
	xorl	%esi, %esi	#
	call	print_sp@PLT	#
# srcs/parsing/__init_utils.c:46: 	print_pl(all->planes, 0);
	movq	104(%rbx), %rdi	# all_7(D)->planes, all_7(D)->planes
	xorl	%esi, %esi	#
	call	print_pl@PLT	#
# srcs/parsing/__init_utils.c:47: 	print_cy(all->cylinders, 0);
	movq	112(%rbx), %rdi	# all_7(D)->cylinders, all_7(D)->cylinders
	xorl	%esi, %esi	#
# srcs/parsing/__init_utils.c:48: }
	popq	%rbx	#
	.cfi_def_cfa_offset 8
# srcs/parsing/__init_utils.c:47: 	print_cy(all->cylinders, 0);
	jmp	print_cy@PLT	#
	.cfi_endproc
.LFE55:
	.size	print_all_structs, .-print_all_structs
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"Error:\nUnwanted character: ['%c'] \t\t\t\t\nin line: [%lu]\n"
	.text
	.p2align 4
	.globl	__set_values_scene
	.type	__set_values_scene, @function
__set_values_scene:
.LFB56:
	.cfi_startproc
	endbr64	
	pushq	%r12	#
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp	#
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rdi, %rbp	# tmp139, all
	pushq	%rbx	#
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
# srcs/parsing/__init_utils.c:51: {
	movq	%rsi, %rbx	# tmp140, s
# srcs/parsing/__init_utils.c:16: 		return (get_cylinder(&all->cylinders, s));
	leaq	112(%rbp), %r12	#, tmp138
# srcs/parsing/__init_utils.c:54: 	skip_whitespace_hashtag(s, &(__get_all()->line_count));
	call	__get_all@PLT	#
# srcs/parsing/__init_utils.c:54: 	skip_whitespace_hashtag(s, &(__get_all()->line_count));
	movq	%rbx, %rdi	# s,
	leaq	152(%rax), %rsi	#, tmp120
	call	skip_whitespace_hashtag@PLT	#
	.p2align 4,,10
	.p2align 3
.L56:
# srcs/parsing/__init_utils.c:56: 	while (err != 2 && *s && **s)
	movq	(%rbx), %rax	# *s_15(D), _7
# srcs/parsing/__init_utils.c:56: 	while (err != 2 && *s && **s)
	testq	%rax, %rax	# _7
	je	.L72	#,
# srcs/parsing/__init_utils.c:56: 	while (err != 2 && *s && **s)
	movsbl	(%rax), %edx	# *_7,
# srcs/parsing/__init_utils.c:56: 	while (err != 2 && *s && **s)
	testb	%dl, %dl	# _8
	je	.L72	#,
# srcs/parsing/__init_utils.c:5: 	if (**s == 'A' && ft_iswhitespace(*((*s) + 1)))
	cmpb	$65, %dl	#, _8
	je	.L83	#,
# srcs/parsing/__init_utils.c:7: 	else if (**s == 'C' && ft_iswhitespace(*((*s) + 1)))
	cmpb	$67, %dl	#, _8
	je	.L84	#,
.L60:
# srcs/parsing/__init_utils.c:9: 	else if (**s == 'L' && ft_iswhitespace(*((*s) + 1)))
	cmpb	$76, %dl	#, _8
	je	.L85	#,
.L62:
# srcs/parsing/__init_utils.c:11: 	else if (**s == 's' && *((*s) + 1) == 'p' && ft_iswhitespace(*((*s) + 2)))
	cmpb	$115, %dl	#, _8
	je	.L86	#,
# srcs/parsing/__init_utils.c:13: 	else if (**s == 'p' && *((*s) + 1) == 'l' && ft_iswhitespace(*((*s) + 2)))
	cmpb	$112, %dl	#, _8
	je	.L87	#,
.L67:
# srcs/parsing/__init_utils.c:15: 	else if (**s == 'c' && *((*s) + 1) == 'y' && ft_iswhitespace(*((*s) + 2)))
	cmpb	$99, %dl	#, _8
	jne	.L65	#,
# srcs/parsing/__init_utils.c:15: 	else if (**s == 'c' && *((*s) + 1) == 'y' && ft_iswhitespace(*((*s) + 2)))
	cmpb	$121, 1(%rax)	#, MEM[(char *)prephitmp_112 + 1B]
	je	.L88	#,
.L65:
# /usr/include/x86_64-linux-gnu/bits/stdio2.h:112:   return __printf_chk (__USE_FORTIFY_LEVEL - 1, __fmt, __va_arg_pack ());
	movq	152(%rbp), %rcx	# all_17(D)->line_count, all_17(D)->line_count
	leaq	.LC0(%rip), %rsi	#, tmp136
	movl	$1, %edi	#,
	xorl	%eax, %eax	#
	call	__printf_chk@PLT	#
# srcs/parsing/__init_utils.c:63: 				\nin line: [%lu]\n", **s, all->line_count), 1);
	movl	$1, %eax	#, <retval>
.L55:
# srcs/parsing/__init_utils.c:66: }
	popq	%rbx	#
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp	#
	.cfi_def_cfa_offset 16
	popq	%r12	#
	.cfi_def_cfa_offset 8
	ret	
	.p2align 4,,10
	.p2align 3
.L86:
	.cfi_restore_state
# srcs/parsing/__init_utils.c:11: 	else if (**s == 's' && *((*s) + 1) == 'p' && ft_iswhitespace(*((*s) + 2)))
	cmpb	$112, 1(%rax)	#, MEM[(char *)prephitmp_100 + 1B]
	jne	.L65	#,
# srcs/parsing/__init_utils.c:11: 	else if (**s == 's' && *((*s) + 1) == 'p' && ft_iswhitespace(*((*s) + 2)))
	movsbl	2(%rax), %edi	# MEM[(char *)prephitmp_100 + 2B], MEM[(char *)prephitmp_100 + 2B]
	call	ft_iswhitespace@PLT	#
# srcs/parsing/__init_utils.c:11: 	else if (**s == 's' && *((*s) + 1) == 'p' && ft_iswhitespace(*((*s) + 2)))
	testl	%eax, %eax	# tmp148
	jne	.L66	#,
# srcs/parsing/__init_utils.c:13: 	else if (**s == 'p' && *((*s) + 1) == 'l' && ft_iswhitespace(*((*s) + 2)))
	movq	(%rbx), %rax	# *s_15(D), _7
# srcs/parsing/__init_utils.c:13: 	else if (**s == 'p' && *((*s) + 1) == 'l' && ft_iswhitespace(*((*s) + 2)))
	movsbl	(%rax), %edx	# *pretmp_95,
# srcs/parsing/__init_utils.c:13: 	else if (**s == 'p' && *((*s) + 1) == 'l' && ft_iswhitespace(*((*s) + 2)))
	cmpb	$112, %dl	#, _8
	jne	.L67	#,
	.p2align 4,,10
	.p2align 3
.L87:
# srcs/parsing/__init_utils.c:13: 	else if (**s == 'p' && *((*s) + 1) == 'l' && ft_iswhitespace(*((*s) + 2)))
	cmpb	$108, 1(%rax)	#, MEM[(char *)prephitmp_21 + 1B]
	jne	.L65	#,
# srcs/parsing/__init_utils.c:13: 	else if (**s == 'p' && *((*s) + 1) == 'l' && ft_iswhitespace(*((*s) + 2)))
	movsbl	2(%rax), %edi	# MEM[(char *)prephitmp_21 + 2B], MEM[(char *)prephitmp_21 + 2B]
	call	ft_iswhitespace@PLT	#
# srcs/parsing/__init_utils.c:13: 	else if (**s == 'p' && *((*s) + 1) == 'l' && ft_iswhitespace(*((*s) + 2)))
	testl	%eax, %eax	# tmp150
	jne	.L68	#,
# srcs/parsing/__init_utils.c:15: 	else if (**s == 'c' && *((*s) + 1) == 'y' && ft_iswhitespace(*((*s) + 2)))
	movq	(%rbx), %rax	# *s_15(D), _7
# srcs/parsing/__init_utils.c:15: 	else if (**s == 'c' && *((*s) + 1) == 'y' && ft_iswhitespace(*((*s) + 2)))
	movsbl	(%rax), %edx	# *pretmp_111,
	jmp	.L67	#
	.p2align 4,,10
	.p2align 3
.L83:
# srcs/parsing/__init_utils.c:5: 	if (**s == 'A' && ft_iswhitespace(*((*s) + 1)))
	movsbl	1(%rax), %edi	# MEM[(char *)_7 + 1B], MEM[(char *)_7 + 1B]
	call	ft_iswhitespace@PLT	#
# srcs/parsing/__init_utils.c:5: 	if (**s == 'A' && ft_iswhitespace(*((*s) + 1)))
	testl	%eax, %eax	# tmp142
	jne	.L58	#,
# srcs/parsing/__init_utils.c:7: 	else if (**s == 'C' && ft_iswhitespace(*((*s) + 1)))
	movq	(%rbx), %rax	# *s_15(D), _7
# srcs/parsing/__init_utils.c:7: 	else if (**s == 'C' && ft_iswhitespace(*((*s) + 1)))
	movsbl	(%rax), %edx	# *pretmp_109,
# srcs/parsing/__init_utils.c:7: 	else if (**s == 'C' && ft_iswhitespace(*((*s) + 1)))
	cmpb	$67, %dl	#, _8
	jne	.L60	#,
	.p2align 4,,10
	.p2align 3
.L84:
# srcs/parsing/__init_utils.c:7: 	else if (**s == 'C' && ft_iswhitespace(*((*s) + 1)))
	movsbl	1(%rax), %edi	# MEM[(char *)prephitmp_108 + 1B], MEM[(char *)prephitmp_108 + 1B]
	call	ft_iswhitespace@PLT	#
# srcs/parsing/__init_utils.c:7: 	else if (**s == 'C' && ft_iswhitespace(*((*s) + 1)))
	testl	%eax, %eax	# tmp144
	jne	.L61	#,
# srcs/parsing/__init_utils.c:9: 	else if (**s == 'L' && ft_iswhitespace(*((*s) + 1)))
	movq	(%rbx), %rax	# *s_15(D), _7
# srcs/parsing/__init_utils.c:9: 	else if (**s == 'L' && ft_iswhitespace(*((*s) + 1)))
	movsbl	(%rax), %edx	# *pretmp_96,
# srcs/parsing/__init_utils.c:9: 	else if (**s == 'L' && ft_iswhitespace(*((*s) + 1)))
	cmpb	$76, %dl	#, _8
	jne	.L62	#,
	.p2align 4,,10
	.p2align 3
.L85:
# srcs/parsing/__init_utils.c:9: 	else if (**s == 'L' && ft_iswhitespace(*((*s) + 1)))
	movsbl	1(%rax), %edi	# MEM[(char *)prephitmp_105 + 1B], MEM[(char *)prephitmp_105 + 1B]
	call	ft_iswhitespace@PLT	#
# srcs/parsing/__init_utils.c:9: 	else if (**s == 'L' && ft_iswhitespace(*((*s) + 1)))
	testl	%eax, %eax	# tmp146
	jne	.L63	#,
# srcs/parsing/__init_utils.c:11: 	else if (**s == 's' && *((*s) + 1) == 'p' && ft_iswhitespace(*((*s) + 2)))
	movq	(%rbx), %rax	# *s_15(D), _7
# srcs/parsing/__init_utils.c:11: 	else if (**s == 's' && *((*s) + 1) == 'p' && ft_iswhitespace(*((*s) + 2)))
	movsbl	(%rax), %edx	# *pretmp_101,
	jmp	.L62	#
	.p2align 4,,10
	.p2align 3
.L88:
# srcs/parsing/__init_utils.c:15: 	else if (**s == 'c' && *((*s) + 1) == 'y' && ft_iswhitespace(*((*s) + 2)))
	movsbl	2(%rax), %edi	# MEM[(char *)prephitmp_112 + 2B], MEM[(char *)prephitmp_112 + 2B]
	call	ft_iswhitespace@PLT	#
# srcs/parsing/__init_utils.c:15: 	else if (**s == 'c' && *((*s) + 1) == 'y' && ft_iswhitespace(*((*s) + 2)))
	testl	%eax, %eax	# tmp152
	jne	.L69	#,
.L82:
# srcs/parsing/__init_utils.c:63: 				\nin line: [%lu]\n", **s, all->line_count), 1);
	movq	(%rbx), %rax	# *s_15(D), *s_15(D)
	movsbl	(%rax), %edx	#* *s_15(D),
	jmp	.L65	#
	.p2align 4,,10
	.p2align 3
.L69:
# srcs/parsing/__init_utils.c:16: 		return (get_cylinder(&all->cylinders, s));
	movq	%rbx, %rsi	# s,
	movq	%r12, %rdi	# tmp138,
	call	get_cylinder@PLT	#
.L59:
# srcs/parsing/__init_utils.c:59: 		if (err == 1)
	cmpl	$1, %eax	#, <retval>
	je	.L55	#,
# srcs/parsing/__init_utils.c:61: 		else if (err == 3)
	cmpl	$3, %eax	#, <retval>
	je	.L82	#,
# srcs/parsing/__init_utils.c:56: 	while (err != 2 && *s && **s)
	cmpl	$2, %eax	#, <retval>
	jne	.L56	#,
.L72:
# srcs/parsing/__init_utils.c:66: }
	popq	%rbx	#
	.cfi_remember_state
	.cfi_def_cfa_offset 24
# srcs/parsing/__init_utils.c:65: 	return (0);
	xorl	%eax, %eax	# <retval>
# srcs/parsing/__init_utils.c:66: }
	popq	%rbp	#
	.cfi_def_cfa_offset 16
	popq	%r12	#
	.cfi_def_cfa_offset 8
	ret	
	.p2align 4,,10
	.p2align 3
.L58:
	.cfi_restore_state
# srcs/parsing/__init_utils.c:6: 		return (get_ambient_light(&all->ambient_light, s));
	movq	%rbx, %rsi	# s,
	movq	%rbp, %rdi	# all,
	call	get_ambient_light@PLT	#
	jmp	.L59	#
	.p2align 4,,10
	.p2align 3
.L61:
# srcs/parsing/__init_utils.c:8: 		return (get_camera(&all->camera, s));
	leaq	24(%rbp), %rdi	#, tmp123
	movq	%rbx, %rsi	# s,
	call	get_camera@PLT	#
	jmp	.L59	#
	.p2align 4,,10
	.p2align 3
.L63:
# srcs/parsing/__init_utils.c:10: 		return (get_light(&all->lights, s));
	leaq	88(%rbp), %rdi	#, tmp125
	movq	%rbx, %rsi	# s,
	call	get_light@PLT	#
	jmp	.L59	#
	.p2align 4,,10
	.p2align 3
.L66:
# srcs/parsing/__init_utils.c:12: 		return (get_sphere(&all->spheres, s));
	leaq	96(%rbp), %rdi	#, tmp127
	movq	%rbx, %rsi	# s,
	call	get_sphere@PLT	#
	jmp	.L59	#
	.p2align 4,,10
	.p2align 3
.L68:
# srcs/parsing/__init_utils.c:14: 		return (get_plane(&all->planes, s));
	leaq	104(%rbp), %rdi	#, tmp129
	movq	%rbx, %rsi	# s,
	call	get_plane@PLT	#
	jmp	.L59	#
	.cfi_endproc
.LFE56:
	.size	__set_values_scene, .-__set_values_scene
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC1:
	.string	"malloc error - vertices"
	.section	.rodata.str1.8
	.align 8
.LC2:
	.string	"malloc error - vertices texture"
	.align 8
.LC3:
	.string	"malloc error - vertices normale"
	.section	.rodata.str1.1
.LC4:
	.string	"malloc error - faces"
.LC5:
	.string	"malloc error - points"
	.text
	.p2align 4
	.globl	__mallocate_objs_values
	.type	__mallocate_objs_values, @function
__mallocate_objs_values:
.LFB57:
	.cfi_startproc
	endbr64	
	pushq	%r12	#
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
# srcs/parsing/__init_utils.c:71: 		return (1);
	movl	$1, %r12d	#, <retval>
# srcs/parsing/__init_utils.c:69: {
	pushq	%rbx	#
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movq	%rdi, %rbx	# tmp130, object
	subq	$8, %rsp	#,
	.cfi_def_cfa_offset 32
# srcs/parsing/__init_utils.c:70: 	if (get_letters(object, s))
	call	get_letters@PLT	#
# srcs/parsing/__init_utils.c:70: 	if (get_letters(object, s))
	testl	%eax, %eax	# <retval>
	jne	.L89	#,
	movl	%eax, %r12d	# tmp132, <retval>
# srcs/parsing/__init_utils.c:72: 	if (object->nb_vertices)
	movq	232(%rbx), %rax	# object_9(D)->nb_vertices, _2
# srcs/parsing/__init_utils.c:72: 	if (object->nb_vertices)
	testq	%rax, %rax	# _2
	jne	.L111	#,
.L91:
# srcs/parsing/__init_utils.c:76: 	if (object->nb_vt)
	movq	240(%rbx), %rax	# object_9(D)->nb_vt, _18
# srcs/parsing/__init_utils.c:76: 	if (object->nb_vt)
	testq	%rax, %rax	# _18
	jne	.L112	#,
.L92:
# srcs/parsing/__init_utils.c:80: 	if (object->nb_vn)
	movq	248(%rbx), %rax	# object_9(D)->nb_vn, _22
# srcs/parsing/__init_utils.c:80: 	if (object->nb_vn)
	testq	%rax, %rax	# _22
	jne	.L113	#,
.L93:
# srcs/parsing/__init_utils.c:84: 	if (object->nb_faces)
	movq	256(%rbx), %rax	# object_9(D)->nb_faces, _26
# srcs/parsing/__init_utils.c:84: 	if (object->nb_faces)
	testq	%rax, %rax	# _26
	jne	.L114	#,
.L94:
# srcs/parsing/__init_utils.c:88: 	if (object->nb_points)
	movq	264(%rbx), %rdi	# object_9(D)->nb_points, _30
# srcs/parsing/__init_utils.c:88: 	if (object->nb_points)
	testq	%rdi, %rdi	# _30
	jne	.L115	#,
.L89:
# srcs/parsing/__init_utils.c:93: }
	addq	$8, %rsp	#,
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	movl	%r12d, %eax	# <retval>,
	popq	%rbx	#
	.cfi_def_cfa_offset 16
	popq	%r12	#
	.cfi_def_cfa_offset 8
	ret	
	.p2align 4,,10
	.p2align 3
.L112:
	.cfi_restore_state
# srcs/parsing/__init_utils.c:77: 		object->vt = malloc(sizeof(t_vertice_t) * (object->nb_vt));
	leaq	(%rax,%rax,2), %rdi	#, tmp108
	salq	$3, %rdi	#, tmp109
	call	malloc@PLT	#
# srcs/parsing/__init_utils.c:77: 		object->vt = malloc(sizeof(t_vertice_t) * (object->nb_vt));
	movq	%rax, 144(%rbx)	# tmp110, object_9(D)->vt
# srcs/parsing/__init_utils.c:78: 	if (object->nb_vt && !object->vt)
	testq	%rax, %rax	# tmp110
	jne	.L92	#,
# /usr/include/x86_64-linux-gnu/bits/stdio2.h:112:   return __printf_chk (__USE_FORTIFY_LEVEL - 1, __fmt, __va_arg_pack ());
	leaq	.LC2(%rip), %rdi	#, tmp111
# srcs/parsing/__init_utils.c:79: 		return (printf("malloc error - vertices texture\n"), 1);
	movl	$1, %r12d	#, <retval>
# /usr/include/x86_64-linux-gnu/bits/stdio2.h:112:   return __printf_chk (__USE_FORTIFY_LEVEL - 1, __fmt, __va_arg_pack ());
	call	puts@PLT	#
# srcs/parsing/__init_utils.c:79: 		return (printf("malloc error - vertices texture\n"), 1);
	jmp	.L89	#
	.p2align 4,,10
	.p2align 3
.L113:
# srcs/parsing/__init_utils.c:81: 		object->vn = malloc(sizeof(t_vertice_n) * (object->nb_vn));
	leaq	(%rax,%rax,2), %rdi	#, tmp114
	salq	$3, %rdi	#, tmp115
	call	malloc@PLT	#
# srcs/parsing/__init_utils.c:81: 		object->vn = malloc(sizeof(t_vertice_n) * (object->nb_vn));
	movq	%rax, 152(%rbx)	# tmp116, object_9(D)->vn
# srcs/parsing/__init_utils.c:82: 	if (object->nb_vn && !object->vn)
	testq	%rax, %rax	# tmp116
	jne	.L93	#,
# /usr/include/x86_64-linux-gnu/bits/stdio2.h:112:   return __printf_chk (__USE_FORTIFY_LEVEL - 1, __fmt, __va_arg_pack ());
	leaq	.LC3(%rip), %rdi	#, tmp117
# srcs/parsing/__init_utils.c:83: 		return (printf("malloc error - vertices normale\n"), 1);
	movl	$1, %r12d	#, <retval>
# /usr/include/x86_64-linux-gnu/bits/stdio2.h:112:   return __printf_chk (__USE_FORTIFY_LEVEL - 1, __fmt, __va_arg_pack ());
	call	puts@PLT	#
# srcs/parsing/__init_utils.c:83: 		return (printf("malloc error - vertices normale\n"), 1);
	jmp	.L89	#
	.p2align 4,,10
	.p2align 3
.L114:
# srcs/parsing/__init_utils.c:85: 		object->faces = malloc(sizeof(t_face) * (object->nb_faces));
	leaq	(%rax,%rax,2), %rdx	#, tmp120
	leaq	(%rax,%rdx,4), %rdi	#, tmp122
	salq	$4, %rdi	#, tmp123
	call	malloc@PLT	#
# srcs/parsing/__init_utils.c:85: 		object->faces = malloc(sizeof(t_face) * (object->nb_faces));
	movq	%rax, 160(%rbx)	# tmp124, object_9(D)->faces
# srcs/parsing/__init_utils.c:86: 	if (object->nb_faces && !object->faces)
	testq	%rax, %rax	# tmp124
	jne	.L94	#,
# /usr/include/x86_64-linux-gnu/bits/stdio2.h:112:   return __printf_chk (__USE_FORTIFY_LEVEL - 1, __fmt, __va_arg_pack ());
	leaq	.LC4(%rip), %rdi	#, tmp125
# srcs/parsing/__init_utils.c:87: 		return (printf("malloc error - faces\n"), 1);
	movl	$1, %r12d	#, <retval>
# /usr/include/x86_64-linux-gnu/bits/stdio2.h:112:   return __printf_chk (__USE_FORTIFY_LEVEL - 1, __fmt, __va_arg_pack ());
	call	puts@PLT	#
# srcs/parsing/__init_utils.c:87: 		return (printf("malloc error - faces\n"), 1);
	jmp	.L89	#
	.p2align 4,,10
	.p2align 3
.L111:
# srcs/parsing/__init_utils.c:73: 		object->vertices = malloc(sizeof(t_vertice) * (object->nb_vertices));
	leaq	(%rax,%rax,2), %rdi	#, tmp102
	salq	$3, %rdi	#, tmp103
	call	malloc@PLT	#
# srcs/parsing/__init_utils.c:73: 		object->vertices = malloc(sizeof(t_vertice) * (object->nb_vertices));
	movq	%rax, 136(%rbx)	# tmp104, object_9(D)->vertices
# srcs/parsing/__init_utils.c:74: 	if (object->nb_vertices && !object->vertices)
	testq	%rax, %rax	# tmp104
	jne	.L91	#,
# /usr/include/x86_64-linux-gnu/bits/stdio2.h:112:   return __printf_chk (__USE_FORTIFY_LEVEL - 1, __fmt, __va_arg_pack ());
	leaq	.LC1(%rip), %rdi	#, tmp105
# srcs/parsing/__init_utils.c:75: 		return (printf("malloc error - vertices\n"), 1);
	movl	$1, %r12d	#, <retval>
# /usr/include/x86_64-linux-gnu/bits/stdio2.h:112:   return __printf_chk (__USE_FORTIFY_LEVEL - 1, __fmt, __va_arg_pack ());
	call	puts@PLT	#
# srcs/parsing/__init_utils.c:75: 		return (printf("malloc error - vertices\n"), 1);
	jmp	.L89	#
	.p2align 4,,10
	.p2align 3
.L115:
# srcs/parsing/__init_utils.c:89: 		object->points = malloc(sizeof(t_point) * (object->nb_points));
	salq	$5, %rdi	#, tmp126
	call	malloc@PLT	#
# srcs/parsing/__init_utils.c:89: 		object->points = malloc(sizeof(t_point) * (object->nb_points));
	movq	%rax, 168(%rbx)	# tmp127, object_9(D)->points
# srcs/parsing/__init_utils.c:90: 	if (object->nb_points && !object->points)
	testq	%rax, %rax	# tmp127
	jne	.L89	#,
# /usr/include/x86_64-linux-gnu/bits/stdio2.h:112:   return __printf_chk (__USE_FORTIFY_LEVEL - 1, __fmt, __va_arg_pack ());
	leaq	.LC5(%rip), %rdi	#, tmp128
# srcs/parsing/__init_utils.c:91: 		return (printf("malloc error - points\n"), 1);
	movl	$1, %r12d	#, <retval>
# /usr/include/x86_64-linux-gnu/bits/stdio2.h:112:   return __printf_chk (__USE_FORTIFY_LEVEL - 1, __fmt, __va_arg_pack ());
	call	puts@PLT	#
# srcs/parsing/__init_utils.c:91: 		return (printf("malloc error - points\n"), 1);
	jmp	.L89	#
	.cfi_endproc
.LFE57:
	.size	__mallocate_objs_values, .-__mallocate_objs_values
	.section	.rodata.str1.8
	.align 8
.LC7:
	.string	"get_object() returned %.9f seconds\n"
	.section	.rodata.str1.1
.LC8:
	.string	"v: %ld\n"
.LC9:
	.string	"vt: %ld\n"
.LC10:
	.string	"f: %ld\n"
	.text
	.p2align 4
	.globl	__set_values_objs
	.type	__set_values_objs, @function
__set_values_objs:
.LFB58:
	.cfi_startproc
	endbr64	
	pushq	%r13	#
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12	#
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movq	%rdi, %r12	# tmp223, object
	pushq	%rbp	#
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	movq	%rsi, %rbp	# tmp224, s
# srcs/parsing/__init_utils.c:101: 	skip_whitespace_hashtag(s, &(object->line_count));
	leaq	224(%rdi), %rsi	#, tmp152
# srcs/parsing/__init_utils.c:33: 		return (get_smoothing(&object->curr_smoothing, s));
	leaq	176(%r12), %r13	#, tmp222
# srcs/parsing/__init_utils.c:96: {
	pushq	%rbx	#
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
# srcs/parsing/__init_utils.c:101: 	skip_whitespace_hashtag(s, &(object->line_count));
	movq	%rbp, %rdi	# s,
# srcs/parsing/__init_utils.c:96: {
	subq	$56, %rsp	#,
	.cfi_def_cfa_offset 96
# srcs/parsing/__init_utils.c:96: {
	movq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp237
	movq	%rax, 40(%rsp)	# tmp237, D.5739
	xorl	%eax, %eax	# tmp237
# srcs/parsing/__init_utils.c:101: 	skip_whitespace_hashtag(s, &(object->line_count));
	call	skip_whitespace_hashtag@PLT	#
# srcs/parsing/__init_utils.c:102: 	__mallocate_objs_values(object, *s);
	movq	0(%rbp), %rsi	# *s_26(D),
	movq	%r12, %rdi	# object,
	call	__mallocate_objs_values	#
# srcs/parsing/__init_utils.c:104: 	clock_gettime(CLOCK_MONOTONIC, &start);
	movq	%rsp, %rsi	#, tmp153
	movl	$1, %edi	#,
	call	clock_gettime@PLT	#
	.p2align 4,,10
	.p2align 3
.L132:
# srcs/parsing/__init_utils.c:22: 	if (**s == 'o' && ft_iswhitespace(*((*s) + 1)))
	movq	0(%rbp), %rax	# *s_26(D), _42
# srcs/parsing/__init_utils.c:22: 	if (**s == 'o' && ft_iswhitespace(*((*s) + 1)))
	movzbl	(%rax), %ebx	# *_42, _43
# srcs/parsing/__init_utils.c:22: 	if (**s == 'o' && ft_iswhitespace(*((*s) + 1)))
	cmpb	$111, %bl	#, _43
	je	.L141	#,
# srcs/parsing/__init_utils.c:24: 	else if (**s == 'v' && ft_iswhitespace(*((*s) + 1)))
	cmpb	$118, %bl	#, _43
	je	.L142	#,
.L124:
# srcs/parsing/__init_utils.c:30: 	else if (**s == 'f' && ft_iswhitespace(*((*s) + 1)))
	cmpb	$102, %bl	#, _43
	je	.L143	#,
.L127:
# srcs/parsing/__init_utils.c:32: 	else if (**s == 's' && ft_iswhitespace(*((*s) + 1)))
	cmpb	$115, %bl	#, _43
	je	.L144	#,
.L125:
# /usr/include/x86_64-linux-gnu/bits/stdio2.h:112:   return __printf_chk (__USE_FORTIFY_LEVEL - 1, __fmt, __va_arg_pack ());
	movq	224(%r12), %rcx	# object_24(D)->line_count, object_24(D)->line_count
# srcs/parsing/__init_utils.c:111: 			return (printf("Error:\nUnwanted character: ['%c'] \
	movsbl	%bl, %edx	# _43, _43
# /usr/include/x86_64-linux-gnu/bits/stdio2.h:112:   return __printf_chk (__USE_FORTIFY_LEVEL - 1, __fmt, __va_arg_pack ());
	movl	$1, %edi	#,
	xorl	%eax, %eax	#
	leaq	.LC0(%rip), %rsi	#, tmp200
	call	__printf_chk@PLT	#
# srcs/parsing/__init_utils.c:112: 				\nin line: [%lu]\n", **s, object->line_count), 1);
	movl	$1, %eax	#, <retval>
.L116:
# srcs/parsing/__init_utils.c:151: }
	movq	40(%rsp), %rdx	# D.5739, tmp238
	subq	%fs:40, %rdx	# MEM[(<address-space-1> long unsigned int *)40B], tmp238
	jne	.L145	#,
	addq	$56, %rsp	#,
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	popq	%rbx	#
	.cfi_def_cfa_offset 32
	popq	%rbp	#
	.cfi_def_cfa_offset 24
	popq	%r12	#
	.cfi_def_cfa_offset 16
	popq	%r13	#
	.cfi_def_cfa_offset 8
	ret	
	.p2align 4,,10
	.p2align 3
.L144:
	.cfi_restore_state
# srcs/parsing/__init_utils.c:32: 	else if (**s == 's' && ft_iswhitespace(*((*s) + 1)))
	movsbl	1(%rax), %edi	# MEM[(char *)prephitmp_152 + 1B], MEM[(char *)prephitmp_152 + 1B]
	call	ft_iswhitespace@PLT	#
# srcs/parsing/__init_utils.c:32: 	else if (**s == 's' && ft_iswhitespace(*((*s) + 1)))
	testl	%eax, %eax	# tmp235
	jne	.L129	#,
.L140:
# srcs/parsing/__init_utils.c:112: 				\nin line: [%lu]\n", **s, object->line_count), 1);
	movq	0(%rbp), %rax	# *s_26(D), *s_26(D)
	movzbl	(%rax), %ebx	#* *s_26(D), _43
	jmp	.L125	#
	.p2align 4,,10
	.p2align 3
.L141:
# srcs/parsing/__init_utils.c:22: 	if (**s == 'o' && ft_iswhitespace(*((*s) + 1)))
	movsbl	1(%rax), %edi	# MEM[(char *)_42 + 1B], MEM[(char *)_42 + 1B]
	call	ft_iswhitespace@PLT	#
# srcs/parsing/__init_utils.c:22: 	if (**s == 'o' && ft_iswhitespace(*((*s) + 1)))
	testl	%eax, %eax	# tmp225
	jne	.L118	#,
# srcs/parsing/__init_utils.c:24: 	else if (**s == 'v' && ft_iswhitespace(*((*s) + 1)))
	movq	0(%rbp), %rax	# *s_26(D), _42
# srcs/parsing/__init_utils.c:24: 	else if (**s == 'v' && ft_iswhitespace(*((*s) + 1)))
	movzbl	(%rax), %ebx	# *pretmp_107, _43
# srcs/parsing/__init_utils.c:24: 	else if (**s == 'v' && ft_iswhitespace(*((*s) + 1)))
	cmpb	$118, %bl	#, _43
	jne	.L124	#,
	.p2align 4,,10
	.p2align 3
.L142:
# srcs/parsing/__init_utils.c:24: 	else if (**s == 'v' && ft_iswhitespace(*((*s) + 1)))
	movsbl	1(%rax), %edi	# MEM[(char *)prephitmp_131 + 1B], MEM[(char *)prephitmp_131 + 1B]
	call	ft_iswhitespace@PLT	#
# srcs/parsing/__init_utils.c:24: 	else if (**s == 'v' && ft_iswhitespace(*((*s) + 1)))
	testl	%eax, %eax	# tmp227
	jne	.L146	#,
# srcs/parsing/__init_utils.c:26: 	else if (**s == 'v' && *((*s) + 1) == 't' && ft_iswhitespace(*((*s) + 2)))
	movq	0(%rbp), %rax	# *s_26(D), _42
# srcs/parsing/__init_utils.c:26: 	else if (**s == 'v' && *((*s) + 1) == 't' && ft_iswhitespace(*((*s) + 2)))
	movzbl	(%rax), %ebx	# *_60, _43
# srcs/parsing/__init_utils.c:26: 	else if (**s == 'v' && *((*s) + 1) == 't' && ft_iswhitespace(*((*s) + 2)))
	cmpb	$118, %bl	#, _43
	jne	.L124	#,
# srcs/parsing/__init_utils.c:26: 	else if (**s == 'v' && *((*s) + 1) == 't' && ft_iswhitespace(*((*s) + 2)))
	movzbl	1(%rax), %edx	# MEM[(char *)_60 + 1B], _62
# srcs/parsing/__init_utils.c:26: 	else if (**s == 'v' && *((*s) + 1) == 't' && ft_iswhitespace(*((*s) + 2)))
	cmpb	$116, %dl	#, _62
	je	.L147	#,
.L122:
# srcs/parsing/__init_utils.c:28: 	else if (**s == 'v' && *((*s) + 1) == 'n' && ft_iswhitespace(*((*s) + 2)))
	cmpb	$110, %dl	#, _62
	jne	.L125	#,
# srcs/parsing/__init_utils.c:28: 	else if (**s == 'v' && *((*s) + 1) == 'n' && ft_iswhitespace(*((*s) + 2)))
	movsbl	2(%rax), %edi	# MEM[(char *)_140 + 2B], MEM[(char *)_140 + 2B]
	call	ft_iswhitespace@PLT	#
# srcs/parsing/__init_utils.c:28: 	else if (**s == 'v' && *((*s) + 1) == 'n' && ft_iswhitespace(*((*s) + 2)))
	testl	%eax, %eax	# tmp231
	jne	.L126	#,
# srcs/parsing/__init_utils.c:30: 	else if (**s == 'f' && ft_iswhitespace(*((*s) + 1)))
	movq	0(%rbp), %rax	# *s_26(D), _42
# srcs/parsing/__init_utils.c:30: 	else if (**s == 'f' && ft_iswhitespace(*((*s) + 1)))
	movzbl	(%rax), %ebx	# *pretmp_32, _43
# srcs/parsing/__init_utils.c:30: 	else if (**s == 'f' && ft_iswhitespace(*((*s) + 1)))
	cmpb	$102, %bl	#, _43
	jne	.L127	#,
	.p2align 4,,10
	.p2align 3
.L143:
# srcs/parsing/__init_utils.c:30: 	else if (**s == 'f' && ft_iswhitespace(*((*s) + 1)))
	movsbl	1(%rax), %edi	# MEM[(char *)prephitmp_147 + 1B], MEM[(char *)prephitmp_147 + 1B]
	call	ft_iswhitespace@PLT	#
# srcs/parsing/__init_utils.c:30: 	else if (**s == 'f' && ft_iswhitespace(*((*s) + 1)))
	testl	%eax, %eax	# tmp233
	jne	.L128	#,
# srcs/parsing/__init_utils.c:32: 	else if (**s == 's' && ft_iswhitespace(*((*s) + 1)))
	movq	0(%rbp), %rax	# *s_26(D), _42
# srcs/parsing/__init_utils.c:32: 	else if (**s == 's' && ft_iswhitespace(*((*s) + 1)))
	movzbl	(%rax), %ebx	# *pretmp_151, _43
	jmp	.L127	#
	.p2align 4,,10
	.p2align 3
.L129:
# srcs/parsing/__init_utils.c:33: 		return (get_smoothing(&object->curr_smoothing, s));
	movq	%rbp, %rsi	# s,
	movq	%r13, %rdi	# tmp222,
	call	get_smoothing@PLT	#
.L119:
# srcs/parsing/__init_utils.c:108: 		if (err == 1)
	cmpl	$1, %eax	#, <retval>
	je	.L116	#,
# srcs/parsing/__init_utils.c:110: 		else if (err == 3)
	cmpl	$3, %eax	#, <retval>
	je	.L140	#,
# srcs/parsing/__init_utils.c:105: 	while (err != 2)
	cmpl	$2, %eax	#, <retval>
	jne	.L132	#,
# srcs/parsing/__init_utils.c:114: 	clock_gettime(CLOCK_MONOTONIC, &end);
	leaq	16(%rsp), %rsi	#, tmp201
	movl	$1, %edi	#,
# /usr/include/x86_64-linux-gnu/bits/stdio2.h:112:   return __printf_chk (__USE_FORTIFY_LEVEL - 1, __fmt, __va_arg_pack ());
	leaq	.LC9(%rip), %rbp	#, tmp215
# srcs/parsing/__init_utils.c:114: 	clock_gettime(CLOCK_MONOTONIC, &end);
	call	clock_gettime@PLT	#
# srcs/parsing/__init_utils.c:116: 		+ (end.tv_nsec - start.tv_nsec) / 1e9;
	movq	24(%rsp), %rax	# end.tv_nsec, end.tv_nsec
# srcs/parsing/__init_utils.c:116: 		+ (end.tv_nsec - start.tv_nsec) / 1e9;
	pxor	%xmm0, %xmm0	# tmp204
# srcs/parsing/__init_utils.c:116: 		+ (end.tv_nsec - start.tv_nsec) / 1e9;
	subq	8(%rsp), %rax	# start.tv_nsec, tmp202
# srcs/parsing/__init_utils.c:116: 		+ (end.tv_nsec - start.tv_nsec) / 1e9;
	cvtsi2sdq	%rax, %xmm0	# tmp202, tmp204
# srcs/parsing/__init_utils.c:116: 		+ (end.tv_nsec - start.tv_nsec) / 1e9;
	pxor	%xmm1, %xmm1	# tmp209
# srcs/parsing/__init_utils.c:115: 	duration = (end.tv_sec - start.tv_sec)
	movq	16(%rsp), %rax	# end.tv_sec, end.tv_sec
	subq	(%rsp), %rax	# start.tv_sec, tmp207
# srcs/parsing/__init_utils.c:116: 		+ (end.tv_nsec - start.tv_nsec) / 1e9;
	cvtsi2sdq	%rax, %xmm1	# tmp207, tmp209
# /usr/include/x86_64-linux-gnu/bits/stdio2.h:112:   return __printf_chk (__USE_FORTIFY_LEVEL - 1, __fmt, __va_arg_pack ());
	movl	$1, %edi	#,
	movl	$1, %eax	#,
# srcs/parsing/__init_utils.c:116: 		+ (end.tv_nsec - start.tv_nsec) / 1e9;
	divsd	.LC6(%rip), %xmm0	#, tmp205
# /usr/include/x86_64-linux-gnu/bits/stdio2.h:112:   return __printf_chk (__USE_FORTIFY_LEVEL - 1, __fmt, __va_arg_pack ());
	leaq	.LC7(%rip), %rsi	#, tmp211
# srcs/parsing/__init_utils.c:115: 	duration = (end.tv_sec - start.tv_sec)
	addsd	%xmm1, %xmm0	# tmp209, duration
# /usr/include/x86_64-linux-gnu/bits/stdio2.h:112:   return __printf_chk (__USE_FORTIFY_LEVEL - 1, __fmt, __va_arg_pack ());
	call	__printf_chk@PLT	#
	movq	200(%r12), %rdx	# object_24(D)->i_vertice[0], object_24(D)->i_vertice[0]
	leaq	.LC8(%rip), %rsi	#, tmp213
	xorl	%eax, %eax	#
	movl	$1, %edi	#,
	call	__printf_chk@PLT	#
	movq	%rbp, %rsi	# tmp215,
	movl	$1, %edi	#,
	xorl	%eax, %eax	#
	movq	208(%r12), %rdx	# object_24(D)->i_vertice[1], object_24(D)->i_vertice[1]
	call	__printf_chk@PLT	#
	movq	%rbp, %rsi	# tmp215,
	movl	$1, %edi	#,
	xorl	%eax, %eax	#
	movq	216(%r12), %rdx	# object_24(D)->i_vertice[2], object_24(D)->i_vertice[2]
	call	__printf_chk@PLT	#
	movq	184(%r12), %rdx	# object_24(D)->indexes[0], object_24(D)->indexes[0]
	leaq	.LC10(%rip), %rsi	#, tmp219
	xorl	%eax, %eax	#
	movl	$1, %edi	#,
	call	__printf_chk@PLT	#
# srcs/parsing/__init_utils.c:150: 	return (0);
	xorl	%eax, %eax	# <retval>
	jmp	.L116	#
	.p2align 4,,10
	.p2align 3
.L147:
# srcs/parsing/__init_utils.c:26: 	else if (**s == 'v' && *((*s) + 1) == 't' && ft_iswhitespace(*((*s) + 2)))
	movsbl	2(%rax), %edi	# MEM[(char *)_60 + 2B], MEM[(char *)_60 + 2B]
	call	ft_iswhitespace@PLT	#
# srcs/parsing/__init_utils.c:26: 	else if (**s == 'v' && *((*s) + 1) == 't' && ft_iswhitespace(*((*s) + 2)))
	testl	%eax, %eax	# tmp229
	jne	.L148	#,
# srcs/parsing/__init_utils.c:28: 	else if (**s == 'v' && *((*s) + 1) == 'n' && ft_iswhitespace(*((*s) + 2)))
	movq	0(%rbp), %rax	# *s_26(D), _42
# srcs/parsing/__init_utils.c:28: 	else if (**s == 'v' && *((*s) + 1) == 'n' && ft_iswhitespace(*((*s) + 2)))
	movzbl	(%rax), %edx	# *_72, _73
# srcs/parsing/__init_utils.c:28: 	else if (**s == 'v' && *((*s) + 1) == 'n' && ft_iswhitespace(*((*s) + 2)))
	cmpb	$118, %dl	#, _73
	jne	.L134	#,
# srcs/parsing/__init_utils.c:28: 	else if (**s == 'v' && *((*s) + 1) == 'n' && ft_iswhitespace(*((*s) + 2)))
	movzbl	1(%rax), %edx	# MEM[(char *)_72 + 1B], _62
	jmp	.L122	#
	.p2align 4,,10
	.p2align 3
.L118:
# srcs/parsing/__init_utils.c:23: 		return (get_name(object->name, s));
	movq	%rbp, %rsi	# s,
	movq	%r12, %rdi	# object,
	call	get_name@PLT	#
	jmp	.L119	#
	.p2align 4,,10
	.p2align 3
.L146:
# srcs/parsing/__init_utils.c:25: 		return (get_vertices(&(object->vertices[object->i_vertice[I_V]]), s, 1, &(object->i_vertice[I_V])));
	movq	200(%r12), %rax	# object_24(D)->i_vertice[0], object_24(D)->i_vertice[0]
# srcs/parsing/__init_utils.c:25: 		return (get_vertices(&(object->vertices[object->i_vertice[I_V]]), s, 1, &(object->i_vertice[I_V])));
	leaq	200(%r12), %rcx	#, tmp156
	movq	%rbp, %rsi	# s,
# srcs/parsing/__init_utils.c:25: 		return (get_vertices(&(object->vertices[object->i_vertice[I_V]]), s, 1, &(object->i_vertice[I_V])));
	leaq	(%rax,%rax,2), %rdx	#, tmp160
# srcs/parsing/__init_utils.c:25: 		return (get_vertices(&(object->vertices[object->i_vertice[I_V]]), s, 1, &(object->i_vertice[I_V])));
	movq	136(%r12), %rax	# object_24(D)->vertices, object_24(D)->vertices
	leaq	(%rax,%rdx,8), %rdi	#, tmp162
	movl	$1, %edx	#,
	call	get_vertices@PLT	#
	jmp	.L119	#
	.p2align 4,,10
	.p2align 3
.L128:
# srcs/parsing/__init_utils.c:31: 		return (get_faces(&(object->faces[object->indexes[I_FACES]]), s, object->curr_smoothing, &(object->indexes[I_FACES])));
	movq	184(%r12), %rax	# object_24(D)->indexes[0], object_24(D)->indexes[0]
# srcs/parsing/__init_utils.c:31: 		return (get_faces(&(object->faces[object->indexes[I_FACES]]), s, object->curr_smoothing, &(object->indexes[I_FACES])));
	leaq	184(%r12), %rcx	#, tmp183
	movzbl	176(%r12), %edx	# object_24(D)->curr_smoothing, object_24(D)->curr_smoothing
# srcs/parsing/__init_utils.c:31: 		return (get_faces(&(object->faces[object->indexes[I_FACES]]), s, object->curr_smoothing, &(object->indexes[I_FACES])));
	leaq	(%rax,%rax,2), %rsi	#, tmp188
	leaq	(%rax,%rsi,4), %rdi	#, tmp190
# srcs/parsing/__init_utils.c:31: 		return (get_faces(&(object->faces[object->indexes[I_FACES]]), s, object->curr_smoothing, &(object->indexes[I_FACES])));
	movq	%rbp, %rsi	# s,
# srcs/parsing/__init_utils.c:31: 		return (get_faces(&(object->faces[object->indexes[I_FACES]]), s, object->curr_smoothing, &(object->indexes[I_FACES])));
	salq	$4, %rdi	#, tmp191
# srcs/parsing/__init_utils.c:31: 		return (get_faces(&(object->faces[object->indexes[I_FACES]]), s, object->curr_smoothing, &(object->indexes[I_FACES])));
	addq	160(%r12), %rdi	# object_24(D)->faces, tmp192
	call	get_faces@PLT	#
	jmp	.L119	#
	.p2align 4,,10
	.p2align 3
.L148:
# srcs/parsing/__init_utils.c:27: 		return (get_vertices(&(object->vt[object->i_vertice[I_VT]]), s, 2, &(object->i_vertice[I_VT])));
	movq	208(%r12), %rax	# object_24(D)->i_vertice[1], object_24(D)->i_vertice[1]
# srcs/parsing/__init_utils.c:27: 		return (get_vertices(&(object->vt[object->i_vertice[I_VT]]), s, 2, &(object->i_vertice[I_VT])));
	leaq	208(%r12), %rcx	#, tmp165
	movq	%rbp, %rsi	# s,
# srcs/parsing/__init_utils.c:27: 		return (get_vertices(&(object->vt[object->i_vertice[I_VT]]), s, 2, &(object->i_vertice[I_VT])));
	leaq	(%rax,%rax,2), %rdx	#, tmp169
# srcs/parsing/__init_utils.c:27: 		return (get_vertices(&(object->vt[object->i_vertice[I_VT]]), s, 2, &(object->i_vertice[I_VT])));
	movq	144(%r12), %rax	# object_24(D)->vt, object_24(D)->vt
	leaq	(%rax,%rdx,8), %rdi	#, tmp171
# srcs/parsing/__init_utils.c:27: 		return (get_vertices(&(object->vt[object->i_vertice[I_VT]]), s, 2, &(object->i_vertice[I_VT])));
	movl	$2, %edx	#,
	call	get_vertices@PLT	#
	jmp	.L119	#
	.p2align 4,,10
	.p2align 3
.L126:
# srcs/parsing/__init_utils.c:29: 		return (get_vertices(&(object->vn[object->i_vertice[I_VN]]), s, 2, &(object->i_vertice[I_VN])));
	movq	216(%r12), %rax	# object_24(D)->i_vertice[2], object_24(D)->i_vertice[2]
# srcs/parsing/__init_utils.c:29: 		return (get_vertices(&(object->vn[object->i_vertice[I_VN]]), s, 2, &(object->i_vertice[I_VN])));
	leaq	216(%r12), %rcx	#, tmp174
	movq	%rbp, %rsi	# s,
# srcs/parsing/__init_utils.c:29: 		return (get_vertices(&(object->vn[object->i_vertice[I_VN]]), s, 2, &(object->i_vertice[I_VN])));
	leaq	(%rax,%rax,2), %rdx	#, tmp178
# srcs/parsing/__init_utils.c:29: 		return (get_vertices(&(object->vn[object->i_vertice[I_VN]]), s, 2, &(object->i_vertice[I_VN])));
	movq	152(%r12), %rax	# object_24(D)->vn, object_24(D)->vn
	leaq	(%rax,%rdx,8), %rdi	#, tmp180
# srcs/parsing/__init_utils.c:29: 		return (get_vertices(&(object->vn[object->i_vertice[I_VN]]), s, 2, &(object->i_vertice[I_VN])));
	movl	$2, %edx	#,
	call	get_vertices@PLT	#
	jmp	.L119	#
.L134:
	movl	%edx, %ebx	# _73, _43
	jmp	.L124	#
.L145:
# srcs/parsing/__init_utils.c:151: }
	call	__stack_chk_fail@PLT	#
	.cfi_endproc
.LFE58:
	.size	__set_values_objs, .-__set_values_objs
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC6:
	.long	0
	.long	1104006501
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
