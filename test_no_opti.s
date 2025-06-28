	.file	"__init_utils.c"
# GNU C17 (Ubuntu 11.4.0-1ubuntu1~22.04) version 11.4.0 (x86_64-linux-gnu)
#	compiled by GNU C version 11.4.0, GMP version 6.2.1, MPFR version 4.1.0, MPC version 1.2.1, isl version isl-0.24-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed: -mtune=generic -march=x86-64 -fasynchronous-unwind-tables -fstack-protector-strong -fstack-clash-protection -fcf-protection
	.text
	.globl	parse_type_scene
	.type	parse_type_scene, @function
parse_type_scene:
.LFB6:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# all, all
	movq	%rsi, -16(%rbp)	# s, s
# srcs/parsing/__init_utils.c:5: 	if (**s == 'A' && ft_iswhitespace(*((*s) + 1)))
	movq	-16(%rbp), %rax	# s, tmp141
	movq	(%rax), %rax	# *s_67(D), _1
# srcs/parsing/__init_utils.c:5: 	if (**s == 'A' && ft_iswhitespace(*((*s) + 1)))
	movzbl	(%rax), %eax	# *_1, _2
# srcs/parsing/__init_utils.c:5: 	if (**s == 'A' && ft_iswhitespace(*((*s) + 1)))
	cmpb	$65, %al	#, _2
	jne	.L2	#,
# srcs/parsing/__init_utils.c:5: 	if (**s == 'A' && ft_iswhitespace(*((*s) + 1)))
	movq	-16(%rbp), %rax	# s, tmp142
	movq	(%rax), %rax	# *s_67(D), _3
# srcs/parsing/__init_utils.c:5: 	if (**s == 'A' && ft_iswhitespace(*((*s) + 1)))
	addq	$1, %rax	#, _4
# srcs/parsing/__init_utils.c:5: 	if (**s == 'A' && ft_iswhitespace(*((*s) + 1)))
	movzbl	(%rax), %eax	# *_4, _5
# srcs/parsing/__init_utils.c:5: 	if (**s == 'A' && ft_iswhitespace(*((*s) + 1)))
	movsbl	%al, %eax	# _5, _6
	movl	%eax, %edi	# _6,
	call	ft_iswhitespace@PLT	#
# srcs/parsing/__init_utils.c:5: 	if (**s == 'A' && ft_iswhitespace(*((*s) + 1)))
	testl	%eax, %eax	# _7
	je	.L2	#,
# srcs/parsing/__init_utils.c:6: 		return (get_ambient_light(&all->ambient_light, s));
	movq	-8(%rbp), %rax	# all, _8
	movq	-16(%rbp), %rdx	# s, tmp143
	movq	%rdx, %rsi	# tmp143,
	movq	%rax, %rdi	# _8,
	call	get_ambient_light@PLT	#
	jmp	.L3	#
.L2:
# srcs/parsing/__init_utils.c:7: 	else if (**s == 'C' && ft_iswhitespace(*((*s) + 1)))
	movq	-16(%rbp), %rax	# s, tmp144
	movq	(%rax), %rax	# *s_67(D), _9
# srcs/parsing/__init_utils.c:7: 	else if (**s == 'C' && ft_iswhitespace(*((*s) + 1)))
	movzbl	(%rax), %eax	# *_9, _10
# srcs/parsing/__init_utils.c:7: 	else if (**s == 'C' && ft_iswhitespace(*((*s) + 1)))
	cmpb	$67, %al	#, _10
	jne	.L4	#,
# srcs/parsing/__init_utils.c:7: 	else if (**s == 'C' && ft_iswhitespace(*((*s) + 1)))
	movq	-16(%rbp), %rax	# s, tmp145
	movq	(%rax), %rax	# *s_67(D), _11
# srcs/parsing/__init_utils.c:7: 	else if (**s == 'C' && ft_iswhitespace(*((*s) + 1)))
	addq	$1, %rax	#, _12
# srcs/parsing/__init_utils.c:7: 	else if (**s == 'C' && ft_iswhitespace(*((*s) + 1)))
	movzbl	(%rax), %eax	# *_12, _13
# srcs/parsing/__init_utils.c:7: 	else if (**s == 'C' && ft_iswhitespace(*((*s) + 1)))
	movsbl	%al, %eax	# _13, _14
	movl	%eax, %edi	# _14,
	call	ft_iswhitespace@PLT	#
# srcs/parsing/__init_utils.c:7: 	else if (**s == 'C' && ft_iswhitespace(*((*s) + 1)))
	testl	%eax, %eax	# _15
	je	.L4	#,
# srcs/parsing/__init_utils.c:8: 		return (get_camera(&all->camera, s));
	movq	-8(%rbp), %rax	# all, tmp146
	leaq	24(%rax), %rdx	#, _16
	movq	-16(%rbp), %rax	# s, tmp147
	movq	%rax, %rsi	# tmp147,
	movq	%rdx, %rdi	# _16,
	call	get_camera@PLT	#
	jmp	.L3	#
.L4:
# srcs/parsing/__init_utils.c:9: 	else if (**s == 'L' && ft_iswhitespace(*((*s) + 1)))
	movq	-16(%rbp), %rax	# s, tmp148
	movq	(%rax), %rax	# *s_67(D), _17
# srcs/parsing/__init_utils.c:9: 	else if (**s == 'L' && ft_iswhitespace(*((*s) + 1)))
	movzbl	(%rax), %eax	# *_17, _18
# srcs/parsing/__init_utils.c:9: 	else if (**s == 'L' && ft_iswhitespace(*((*s) + 1)))
	cmpb	$76, %al	#, _18
	jne	.L5	#,
# srcs/parsing/__init_utils.c:9: 	else if (**s == 'L' && ft_iswhitespace(*((*s) + 1)))
	movq	-16(%rbp), %rax	# s, tmp149
	movq	(%rax), %rax	# *s_67(D), _19
# srcs/parsing/__init_utils.c:9: 	else if (**s == 'L' && ft_iswhitespace(*((*s) + 1)))
	addq	$1, %rax	#, _20
# srcs/parsing/__init_utils.c:9: 	else if (**s == 'L' && ft_iswhitespace(*((*s) + 1)))
	movzbl	(%rax), %eax	# *_20, _21
# srcs/parsing/__init_utils.c:9: 	else if (**s == 'L' && ft_iswhitespace(*((*s) + 1)))
	movsbl	%al, %eax	# _21, _22
	movl	%eax, %edi	# _22,
	call	ft_iswhitespace@PLT	#
# srcs/parsing/__init_utils.c:9: 	else if (**s == 'L' && ft_iswhitespace(*((*s) + 1)))
	testl	%eax, %eax	# _23
	je	.L5	#,
# srcs/parsing/__init_utils.c:10: 		return (get_light(&all->lights, s));
	movq	-8(%rbp), %rax	# all, tmp150
	leaq	88(%rax), %rdx	#, _24
	movq	-16(%rbp), %rax	# s, tmp151
	movq	%rax, %rsi	# tmp151,
	movq	%rdx, %rdi	# _24,
	call	get_light@PLT	#
	jmp	.L3	#
.L5:
# srcs/parsing/__init_utils.c:11: 	else if (**s == 's' && *((*s) + 1) == 'p' && ft_iswhitespace(*((*s) + 2)))
	movq	-16(%rbp), %rax	# s, tmp152
	movq	(%rax), %rax	# *s_67(D), _25
# srcs/parsing/__init_utils.c:11: 	else if (**s == 's' && *((*s) + 1) == 'p' && ft_iswhitespace(*((*s) + 2)))
	movzbl	(%rax), %eax	# *_25, _26
# srcs/parsing/__init_utils.c:11: 	else if (**s == 's' && *((*s) + 1) == 'p' && ft_iswhitespace(*((*s) + 2)))
	cmpb	$115, %al	#, _26
	jne	.L6	#,
# srcs/parsing/__init_utils.c:11: 	else if (**s == 's' && *((*s) + 1) == 'p' && ft_iswhitespace(*((*s) + 2)))
	movq	-16(%rbp), %rax	# s, tmp153
	movq	(%rax), %rax	# *s_67(D), _27
# srcs/parsing/__init_utils.c:11: 	else if (**s == 's' && *((*s) + 1) == 'p' && ft_iswhitespace(*((*s) + 2)))
	addq	$1, %rax	#, _28
# srcs/parsing/__init_utils.c:11: 	else if (**s == 's' && *((*s) + 1) == 'p' && ft_iswhitespace(*((*s) + 2)))
	movzbl	(%rax), %eax	# *_28, _29
# srcs/parsing/__init_utils.c:11: 	else if (**s == 's' && *((*s) + 1) == 'p' && ft_iswhitespace(*((*s) + 2)))
	cmpb	$112, %al	#, _29
	jne	.L6	#,
# srcs/parsing/__init_utils.c:11: 	else if (**s == 's' && *((*s) + 1) == 'p' && ft_iswhitespace(*((*s) + 2)))
	movq	-16(%rbp), %rax	# s, tmp154
	movq	(%rax), %rax	# *s_67(D), _30
# srcs/parsing/__init_utils.c:11: 	else if (**s == 's' && *((*s) + 1) == 'p' && ft_iswhitespace(*((*s) + 2)))
	addq	$2, %rax	#, _31
# srcs/parsing/__init_utils.c:11: 	else if (**s == 's' && *((*s) + 1) == 'p' && ft_iswhitespace(*((*s) + 2)))
	movzbl	(%rax), %eax	# *_31, _32
# srcs/parsing/__init_utils.c:11: 	else if (**s == 's' && *((*s) + 1) == 'p' && ft_iswhitespace(*((*s) + 2)))
	movsbl	%al, %eax	# _32, _33
	movl	%eax, %edi	# _33,
	call	ft_iswhitespace@PLT	#
# srcs/parsing/__init_utils.c:11: 	else if (**s == 's' && *((*s) + 1) == 'p' && ft_iswhitespace(*((*s) + 2)))
	testl	%eax, %eax	# _34
	je	.L6	#,
# srcs/parsing/__init_utils.c:12: 		return (get_sphere(&all->spheres, s));
	movq	-8(%rbp), %rax	# all, tmp155
	leaq	96(%rax), %rdx	#, _35
	movq	-16(%rbp), %rax	# s, tmp156
	movq	%rax, %rsi	# tmp156,
	movq	%rdx, %rdi	# _35,
	call	get_sphere@PLT	#
	jmp	.L3	#
.L6:
# srcs/parsing/__init_utils.c:13: 	else if (**s == 'p' && *((*s) + 1) == 'l' && ft_iswhitespace(*((*s) + 2)))
	movq	-16(%rbp), %rax	# s, tmp157
	movq	(%rax), %rax	# *s_67(D), _36
# srcs/parsing/__init_utils.c:13: 	else if (**s == 'p' && *((*s) + 1) == 'l' && ft_iswhitespace(*((*s) + 2)))
	movzbl	(%rax), %eax	# *_36, _37
# srcs/parsing/__init_utils.c:13: 	else if (**s == 'p' && *((*s) + 1) == 'l' && ft_iswhitespace(*((*s) + 2)))
	cmpb	$112, %al	#, _37
	jne	.L7	#,
# srcs/parsing/__init_utils.c:13: 	else if (**s == 'p' && *((*s) + 1) == 'l' && ft_iswhitespace(*((*s) + 2)))
	movq	-16(%rbp), %rax	# s, tmp158
	movq	(%rax), %rax	# *s_67(D), _38
# srcs/parsing/__init_utils.c:13: 	else if (**s == 'p' && *((*s) + 1) == 'l' && ft_iswhitespace(*((*s) + 2)))
	addq	$1, %rax	#, _39
# srcs/parsing/__init_utils.c:13: 	else if (**s == 'p' && *((*s) + 1) == 'l' && ft_iswhitespace(*((*s) + 2)))
	movzbl	(%rax), %eax	# *_39, _40
# srcs/parsing/__init_utils.c:13: 	else if (**s == 'p' && *((*s) + 1) == 'l' && ft_iswhitespace(*((*s) + 2)))
	cmpb	$108, %al	#, _40
	jne	.L7	#,
# srcs/parsing/__init_utils.c:13: 	else if (**s == 'p' && *((*s) + 1) == 'l' && ft_iswhitespace(*((*s) + 2)))
	movq	-16(%rbp), %rax	# s, tmp159
	movq	(%rax), %rax	# *s_67(D), _41
# srcs/parsing/__init_utils.c:13: 	else if (**s == 'p' && *((*s) + 1) == 'l' && ft_iswhitespace(*((*s) + 2)))
	addq	$2, %rax	#, _42
# srcs/parsing/__init_utils.c:13: 	else if (**s == 'p' && *((*s) + 1) == 'l' && ft_iswhitespace(*((*s) + 2)))
	movzbl	(%rax), %eax	# *_42, _43
# srcs/parsing/__init_utils.c:13: 	else if (**s == 'p' && *((*s) + 1) == 'l' && ft_iswhitespace(*((*s) + 2)))
	movsbl	%al, %eax	# _43, _44
	movl	%eax, %edi	# _44,
	call	ft_iswhitespace@PLT	#
# srcs/parsing/__init_utils.c:13: 	else if (**s == 'p' && *((*s) + 1) == 'l' && ft_iswhitespace(*((*s) + 2)))
	testl	%eax, %eax	# _45
	je	.L7	#,
# srcs/parsing/__init_utils.c:14: 		return (get_plane(&all->planes, s));
	movq	-8(%rbp), %rax	# all, tmp160
	leaq	104(%rax), %rdx	#, _46
	movq	-16(%rbp), %rax	# s, tmp161
	movq	%rax, %rsi	# tmp161,
	movq	%rdx, %rdi	# _46,
	call	get_plane@PLT	#
	jmp	.L3	#
.L7:
# srcs/parsing/__init_utils.c:15: 	else if (**s == 'c' && *((*s) + 1) == 'y' && ft_iswhitespace(*((*s) + 2)))
	movq	-16(%rbp), %rax	# s, tmp162
	movq	(%rax), %rax	# *s_67(D), _47
# srcs/parsing/__init_utils.c:15: 	else if (**s == 'c' && *((*s) + 1) == 'y' && ft_iswhitespace(*((*s) + 2)))
	movzbl	(%rax), %eax	# *_47, _48
# srcs/parsing/__init_utils.c:15: 	else if (**s == 'c' && *((*s) + 1) == 'y' && ft_iswhitespace(*((*s) + 2)))
	cmpb	$99, %al	#, _48
	jne	.L8	#,
# srcs/parsing/__init_utils.c:15: 	else if (**s == 'c' && *((*s) + 1) == 'y' && ft_iswhitespace(*((*s) + 2)))
	movq	-16(%rbp), %rax	# s, tmp163
	movq	(%rax), %rax	# *s_67(D), _49
# srcs/parsing/__init_utils.c:15: 	else if (**s == 'c' && *((*s) + 1) == 'y' && ft_iswhitespace(*((*s) + 2)))
	addq	$1, %rax	#, _50
# srcs/parsing/__init_utils.c:15: 	else if (**s == 'c' && *((*s) + 1) == 'y' && ft_iswhitespace(*((*s) + 2)))
	movzbl	(%rax), %eax	# *_50, _51
# srcs/parsing/__init_utils.c:15: 	else if (**s == 'c' && *((*s) + 1) == 'y' && ft_iswhitespace(*((*s) + 2)))
	cmpb	$121, %al	#, _51
	jne	.L8	#,
# srcs/parsing/__init_utils.c:15: 	else if (**s == 'c' && *((*s) + 1) == 'y' && ft_iswhitespace(*((*s) + 2)))
	movq	-16(%rbp), %rax	# s, tmp164
	movq	(%rax), %rax	# *s_67(D), _52
# srcs/parsing/__init_utils.c:15: 	else if (**s == 'c' && *((*s) + 1) == 'y' && ft_iswhitespace(*((*s) + 2)))
	addq	$2, %rax	#, _53
# srcs/parsing/__init_utils.c:15: 	else if (**s == 'c' && *((*s) + 1) == 'y' && ft_iswhitespace(*((*s) + 2)))
	movzbl	(%rax), %eax	# *_53, _54
# srcs/parsing/__init_utils.c:15: 	else if (**s == 'c' && *((*s) + 1) == 'y' && ft_iswhitespace(*((*s) + 2)))
	movsbl	%al, %eax	# _54, _55
	movl	%eax, %edi	# _55,
	call	ft_iswhitespace@PLT	#
# srcs/parsing/__init_utils.c:15: 	else if (**s == 'c' && *((*s) + 1) == 'y' && ft_iswhitespace(*((*s) + 2)))
	testl	%eax, %eax	# _56
	je	.L8	#,
# srcs/parsing/__init_utils.c:16: 		return (get_cylinder(&all->cylinders, s));
	movq	-8(%rbp), %rax	# all, tmp165
	leaq	112(%rax), %rdx	#, _57
	movq	-16(%rbp), %rax	# s, tmp166
	movq	%rax, %rsi	# tmp166,
	movq	%rdx, %rdi	# _57,
	call	get_cylinder@PLT	#
	jmp	.L3	#
.L8:
# srcs/parsing/__init_utils.c:17: 	return (3);
	movl	$3, %eax	#, _58
.L3:
# srcs/parsing/__init_utils.c:18: }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE6:
	.size	parse_type_scene, .-parse_type_scene
	.globl	parse_type_objs
	.type	parse_type_objs, @function
parse_type_objs:
.LFB7:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# object, object
	movq	%rsi, -16(%rbp)	# s, s
# srcs/parsing/__init_utils.c:22: 	if (**s == 'o' && ft_iswhitespace(*((*s) + 1)))
	movq	-16(%rbp), %rax	# s, tmp156
	movq	(%rax), %rax	# *s_82(D), _1
# srcs/parsing/__init_utils.c:22: 	if (**s == 'o' && ft_iswhitespace(*((*s) + 1)))
	movzbl	(%rax), %eax	# *_1, _2
# srcs/parsing/__init_utils.c:22: 	if (**s == 'o' && ft_iswhitespace(*((*s) + 1)))
	cmpb	$111, %al	#, _2
	jne	.L10	#,
# srcs/parsing/__init_utils.c:22: 	if (**s == 'o' && ft_iswhitespace(*((*s) + 1)))
	movq	-16(%rbp), %rax	# s, tmp157
	movq	(%rax), %rax	# *s_82(D), _3
# srcs/parsing/__init_utils.c:22: 	if (**s == 'o' && ft_iswhitespace(*((*s) + 1)))
	addq	$1, %rax	#, _4
# srcs/parsing/__init_utils.c:22: 	if (**s == 'o' && ft_iswhitespace(*((*s) + 1)))
	movzbl	(%rax), %eax	# *_4, _5
# srcs/parsing/__init_utils.c:22: 	if (**s == 'o' && ft_iswhitespace(*((*s) + 1)))
	movsbl	%al, %eax	# _5, _6
	movl	%eax, %edi	# _6,
	call	ft_iswhitespace@PLT	#
# srcs/parsing/__init_utils.c:22: 	if (**s == 'o' && ft_iswhitespace(*((*s) + 1)))
	testl	%eax, %eax	# _7
	je	.L10	#,
# srcs/parsing/__init_utils.c:23: 		return (get_name(object->name, s));
	movq	-8(%rbp), %rax	# object, _8
# srcs/parsing/__init_utils.c:23: 		return (get_name(object->name, s));
	movq	-16(%rbp), %rdx	# s, tmp158
	movq	%rdx, %rsi	# tmp158,
	movq	%rax, %rdi	# _8,
	call	get_name@PLT	#
	jmp	.L11	#
.L10:
# srcs/parsing/__init_utils.c:24: 	else if (**s == 'v' && ft_iswhitespace(*((*s) + 1)))
	movq	-16(%rbp), %rax	# s, tmp159
	movq	(%rax), %rax	# *s_82(D), _9
# srcs/parsing/__init_utils.c:24: 	else if (**s == 'v' && ft_iswhitespace(*((*s) + 1)))
	movzbl	(%rax), %eax	# *_9, _10
# srcs/parsing/__init_utils.c:24: 	else if (**s == 'v' && ft_iswhitespace(*((*s) + 1)))
	cmpb	$118, %al	#, _10
	jne	.L12	#,
# srcs/parsing/__init_utils.c:24: 	else if (**s == 'v' && ft_iswhitespace(*((*s) + 1)))
	movq	-16(%rbp), %rax	# s, tmp160
	movq	(%rax), %rax	# *s_82(D), _11
# srcs/parsing/__init_utils.c:24: 	else if (**s == 'v' && ft_iswhitespace(*((*s) + 1)))
	addq	$1, %rax	#, _12
# srcs/parsing/__init_utils.c:24: 	else if (**s == 'v' && ft_iswhitespace(*((*s) + 1)))
	movzbl	(%rax), %eax	# *_12, _13
# srcs/parsing/__init_utils.c:24: 	else if (**s == 'v' && ft_iswhitespace(*((*s) + 1)))
	movsbl	%al, %eax	# _13, _14
	movl	%eax, %edi	# _14,
	call	ft_iswhitespace@PLT	#
# srcs/parsing/__init_utils.c:24: 	else if (**s == 'v' && ft_iswhitespace(*((*s) + 1)))
	testl	%eax, %eax	# _15
	je	.L12	#,
# srcs/parsing/__init_utils.c:25: 		return (get_vertices(&(object->vertices[object->i_vertice[I_V]]), s, 1, &(object->i_vertice[I_V])));
	movq	-8(%rbp), %rax	# object, tmp161
	leaq	200(%rax), %rdx	#, _16
# srcs/parsing/__init_utils.c:25: 		return (get_vertices(&(object->vertices[object->i_vertice[I_V]]), s, 1, &(object->i_vertice[I_V])));
	movq	-8(%rbp), %rax	# object, tmp162
	movq	136(%rax), %rsi	# object_84(D)->vertices, _17
# srcs/parsing/__init_utils.c:25: 		return (get_vertices(&(object->vertices[object->i_vertice[I_V]]), s, 1, &(object->i_vertice[I_V])));
	movq	-8(%rbp), %rax	# object, tmp163
	movq	200(%rax), %rcx	# object_84(D)->i_vertice[0], _18
# srcs/parsing/__init_utils.c:25: 		return (get_vertices(&(object->vertices[object->i_vertice[I_V]]), s, 1, &(object->i_vertice[I_V])));
	movq	%rcx, %rax	# _18, tmp164
	addq	%rax, %rax	# tmp164
	addq	%rcx, %rax	# _18, tmp164
	salq	$3, %rax	#, tmp165
# srcs/parsing/__init_utils.c:25: 		return (get_vertices(&(object->vertices[object->i_vertice[I_V]]), s, 1, &(object->i_vertice[I_V])));
	leaq	(%rsi,%rax), %rdi	#, _20
	movq	-16(%rbp), %rax	# s, tmp166
	movq	%rdx, %rcx	# _16,
	movl	$1, %edx	#,
	movq	%rax, %rsi	# tmp166,
	call	get_vertices@PLT	#
	jmp	.L11	#
.L12:
# srcs/parsing/__init_utils.c:26: 	else if (**s == 'v' && *((*s) + 1) == 't' && ft_iswhitespace(*((*s) + 2)))
	movq	-16(%rbp), %rax	# s, tmp167
	movq	(%rax), %rax	# *s_82(D), _21
# srcs/parsing/__init_utils.c:26: 	else if (**s == 'v' && *((*s) + 1) == 't' && ft_iswhitespace(*((*s) + 2)))
	movzbl	(%rax), %eax	# *_21, _22
# srcs/parsing/__init_utils.c:26: 	else if (**s == 'v' && *((*s) + 1) == 't' && ft_iswhitespace(*((*s) + 2)))
	cmpb	$118, %al	#, _22
	jne	.L13	#,
# srcs/parsing/__init_utils.c:26: 	else if (**s == 'v' && *((*s) + 1) == 't' && ft_iswhitespace(*((*s) + 2)))
	movq	-16(%rbp), %rax	# s, tmp168
	movq	(%rax), %rax	# *s_82(D), _23
# srcs/parsing/__init_utils.c:26: 	else if (**s == 'v' && *((*s) + 1) == 't' && ft_iswhitespace(*((*s) + 2)))
	addq	$1, %rax	#, _24
# srcs/parsing/__init_utils.c:26: 	else if (**s == 'v' && *((*s) + 1) == 't' && ft_iswhitespace(*((*s) + 2)))
	movzbl	(%rax), %eax	# *_24, _25
# srcs/parsing/__init_utils.c:26: 	else if (**s == 'v' && *((*s) + 1) == 't' && ft_iswhitespace(*((*s) + 2)))
	cmpb	$116, %al	#, _25
	jne	.L13	#,
# srcs/parsing/__init_utils.c:26: 	else if (**s == 'v' && *((*s) + 1) == 't' && ft_iswhitespace(*((*s) + 2)))
	movq	-16(%rbp), %rax	# s, tmp169
	movq	(%rax), %rax	# *s_82(D), _26
# srcs/parsing/__init_utils.c:26: 	else if (**s == 'v' && *((*s) + 1) == 't' && ft_iswhitespace(*((*s) + 2)))
	addq	$2, %rax	#, _27
# srcs/parsing/__init_utils.c:26: 	else if (**s == 'v' && *((*s) + 1) == 't' && ft_iswhitespace(*((*s) + 2)))
	movzbl	(%rax), %eax	# *_27, _28
# srcs/parsing/__init_utils.c:26: 	else if (**s == 'v' && *((*s) + 1) == 't' && ft_iswhitespace(*((*s) + 2)))
	movsbl	%al, %eax	# _28, _29
	movl	%eax, %edi	# _29,
	call	ft_iswhitespace@PLT	#
# srcs/parsing/__init_utils.c:26: 	else if (**s == 'v' && *((*s) + 1) == 't' && ft_iswhitespace(*((*s) + 2)))
	testl	%eax, %eax	# _30
	je	.L13	#,
# srcs/parsing/__init_utils.c:27: 		return (get_vertices(&(object->vt[object->i_vertice[I_VT]]), s, 2, &(object->i_vertice[I_VT])));
	movq	-8(%rbp), %rax	# object, tmp170
	leaq	208(%rax), %rdx	#, _31
# srcs/parsing/__init_utils.c:27: 		return (get_vertices(&(object->vt[object->i_vertice[I_VT]]), s, 2, &(object->i_vertice[I_VT])));
	movq	-8(%rbp), %rax	# object, tmp171
	movq	144(%rax), %rsi	# object_84(D)->vt, _32
# srcs/parsing/__init_utils.c:27: 		return (get_vertices(&(object->vt[object->i_vertice[I_VT]]), s, 2, &(object->i_vertice[I_VT])));
	movq	-8(%rbp), %rax	# object, tmp172
	movq	208(%rax), %rcx	# object_84(D)->i_vertice[1], _33
# srcs/parsing/__init_utils.c:27: 		return (get_vertices(&(object->vt[object->i_vertice[I_VT]]), s, 2, &(object->i_vertice[I_VT])));
	movq	%rcx, %rax	# _33, tmp173
	addq	%rax, %rax	# tmp173
	addq	%rcx, %rax	# _33, tmp173
	salq	$3, %rax	#, tmp174
# srcs/parsing/__init_utils.c:27: 		return (get_vertices(&(object->vt[object->i_vertice[I_VT]]), s, 2, &(object->i_vertice[I_VT])));
	leaq	(%rsi,%rax), %rdi	#, _35
# srcs/parsing/__init_utils.c:27: 		return (get_vertices(&(object->vt[object->i_vertice[I_VT]]), s, 2, &(object->i_vertice[I_VT])));
	movq	-16(%rbp), %rax	# s, tmp175
	movq	%rdx, %rcx	# _31,
	movl	$2, %edx	#,
	movq	%rax, %rsi	# tmp175,
	call	get_vertices@PLT	#
	jmp	.L11	#
.L13:
# srcs/parsing/__init_utils.c:28: 	else if (**s == 'v' && *((*s) + 1) == 'n' && ft_iswhitespace(*((*s) + 2)))
	movq	-16(%rbp), %rax	# s, tmp176
	movq	(%rax), %rax	# *s_82(D), _36
# srcs/parsing/__init_utils.c:28: 	else if (**s == 'v' && *((*s) + 1) == 'n' && ft_iswhitespace(*((*s) + 2)))
	movzbl	(%rax), %eax	# *_36, _37
# srcs/parsing/__init_utils.c:28: 	else if (**s == 'v' && *((*s) + 1) == 'n' && ft_iswhitespace(*((*s) + 2)))
	cmpb	$118, %al	#, _37
	jne	.L14	#,
# srcs/parsing/__init_utils.c:28: 	else if (**s == 'v' && *((*s) + 1) == 'n' && ft_iswhitespace(*((*s) + 2)))
	movq	-16(%rbp), %rax	# s, tmp177
	movq	(%rax), %rax	# *s_82(D), _38
# srcs/parsing/__init_utils.c:28: 	else if (**s == 'v' && *((*s) + 1) == 'n' && ft_iswhitespace(*((*s) + 2)))
	addq	$1, %rax	#, _39
# srcs/parsing/__init_utils.c:28: 	else if (**s == 'v' && *((*s) + 1) == 'n' && ft_iswhitespace(*((*s) + 2)))
	movzbl	(%rax), %eax	# *_39, _40
# srcs/parsing/__init_utils.c:28: 	else if (**s == 'v' && *((*s) + 1) == 'n' && ft_iswhitespace(*((*s) + 2)))
	cmpb	$110, %al	#, _40
	jne	.L14	#,
# srcs/parsing/__init_utils.c:28: 	else if (**s == 'v' && *((*s) + 1) == 'n' && ft_iswhitespace(*((*s) + 2)))
	movq	-16(%rbp), %rax	# s, tmp178
	movq	(%rax), %rax	# *s_82(D), _41
# srcs/parsing/__init_utils.c:28: 	else if (**s == 'v' && *((*s) + 1) == 'n' && ft_iswhitespace(*((*s) + 2)))
	addq	$2, %rax	#, _42
# srcs/parsing/__init_utils.c:28: 	else if (**s == 'v' && *((*s) + 1) == 'n' && ft_iswhitespace(*((*s) + 2)))
	movzbl	(%rax), %eax	# *_42, _43
# srcs/parsing/__init_utils.c:28: 	else if (**s == 'v' && *((*s) + 1) == 'n' && ft_iswhitespace(*((*s) + 2)))
	movsbl	%al, %eax	# _43, _44
	movl	%eax, %edi	# _44,
	call	ft_iswhitespace@PLT	#
# srcs/parsing/__init_utils.c:28: 	else if (**s == 'v' && *((*s) + 1) == 'n' && ft_iswhitespace(*((*s) + 2)))
	testl	%eax, %eax	# _45
	je	.L14	#,
# srcs/parsing/__init_utils.c:29: 		return (get_vertices(&(object->vn[object->i_vertice[I_VN]]), s, 2, &(object->i_vertice[I_VN])));
	movq	-8(%rbp), %rax	# object, tmp179
	leaq	216(%rax), %rdx	#, _46
# srcs/parsing/__init_utils.c:29: 		return (get_vertices(&(object->vn[object->i_vertice[I_VN]]), s, 2, &(object->i_vertice[I_VN])));
	movq	-8(%rbp), %rax	# object, tmp180
	movq	152(%rax), %rsi	# object_84(D)->vn, _47
# srcs/parsing/__init_utils.c:29: 		return (get_vertices(&(object->vn[object->i_vertice[I_VN]]), s, 2, &(object->i_vertice[I_VN])));
	movq	-8(%rbp), %rax	# object, tmp181
	movq	216(%rax), %rcx	# object_84(D)->i_vertice[2], _48
# srcs/parsing/__init_utils.c:29: 		return (get_vertices(&(object->vn[object->i_vertice[I_VN]]), s, 2, &(object->i_vertice[I_VN])));
	movq	%rcx, %rax	# _48, tmp182
	addq	%rax, %rax	# tmp182
	addq	%rcx, %rax	# _48, tmp182
	salq	$3, %rax	#, tmp183
# srcs/parsing/__init_utils.c:29: 		return (get_vertices(&(object->vn[object->i_vertice[I_VN]]), s, 2, &(object->i_vertice[I_VN])));
	leaq	(%rsi,%rax), %rdi	#, _50
# srcs/parsing/__init_utils.c:29: 		return (get_vertices(&(object->vn[object->i_vertice[I_VN]]), s, 2, &(object->i_vertice[I_VN])));
	movq	-16(%rbp), %rax	# s, tmp184
	movq	%rdx, %rcx	# _46,
	movl	$2, %edx	#,
	movq	%rax, %rsi	# tmp184,
	call	get_vertices@PLT	#
	jmp	.L11	#
.L14:
# srcs/parsing/__init_utils.c:30: 	else if (**s == 'f' && ft_iswhitespace(*((*s) + 1)))
	movq	-16(%rbp), %rax	# s, tmp185
	movq	(%rax), %rax	# *s_82(D), _51
# srcs/parsing/__init_utils.c:30: 	else if (**s == 'f' && ft_iswhitespace(*((*s) + 1)))
	movzbl	(%rax), %eax	# *_51, _52
# srcs/parsing/__init_utils.c:30: 	else if (**s == 'f' && ft_iswhitespace(*((*s) + 1)))
	cmpb	$102, %al	#, _52
	jne	.L15	#,
# srcs/parsing/__init_utils.c:30: 	else if (**s == 'f' && ft_iswhitespace(*((*s) + 1)))
	movq	-16(%rbp), %rax	# s, tmp186
	movq	(%rax), %rax	# *s_82(D), _53
# srcs/parsing/__init_utils.c:30: 	else if (**s == 'f' && ft_iswhitespace(*((*s) + 1)))
	addq	$1, %rax	#, _54
# srcs/parsing/__init_utils.c:30: 	else if (**s == 'f' && ft_iswhitespace(*((*s) + 1)))
	movzbl	(%rax), %eax	# *_54, _55
# srcs/parsing/__init_utils.c:30: 	else if (**s == 'f' && ft_iswhitespace(*((*s) + 1)))
	movsbl	%al, %eax	# _55, _56
	movl	%eax, %edi	# _56,
	call	ft_iswhitespace@PLT	#
# srcs/parsing/__init_utils.c:30: 	else if (**s == 'f' && ft_iswhitespace(*((*s) + 1)))
	testl	%eax, %eax	# _57
	je	.L15	#,
# srcs/parsing/__init_utils.c:31: 		return (get_faces(&(object->faces[object->indexes[I_FACES]]), s, object->curr_smoothing, &(object->indexes[I_FACES])));
	movq	-8(%rbp), %rax	# object, tmp187
	leaq	184(%rax), %rcx	#, _58
# srcs/parsing/__init_utils.c:31: 		return (get_faces(&(object->faces[object->indexes[I_FACES]]), s, object->curr_smoothing, &(object->indexes[I_FACES])));
	movq	-8(%rbp), %rax	# object, tmp188
	movzbl	176(%rax), %eax	# object_84(D)->curr_smoothing, _59
# srcs/parsing/__init_utils.c:31: 		return (get_faces(&(object->faces[object->indexes[I_FACES]]), s, object->curr_smoothing, &(object->indexes[I_FACES])));
	movzbl	%al, %esi	# _59, _60
# srcs/parsing/__init_utils.c:31: 		return (get_faces(&(object->faces[object->indexes[I_FACES]]), s, object->curr_smoothing, &(object->indexes[I_FACES])));
	movq	-8(%rbp), %rax	# object, tmp189
	movq	160(%rax), %rdi	# object_84(D)->faces, _61
# srcs/parsing/__init_utils.c:31: 		return (get_faces(&(object->faces[object->indexes[I_FACES]]), s, object->curr_smoothing, &(object->indexes[I_FACES])));
	movq	-8(%rbp), %rax	# object, tmp190
	movq	184(%rax), %rdx	# object_84(D)->indexes[0], _62
# srcs/parsing/__init_utils.c:31: 		return (get_faces(&(object->faces[object->indexes[I_FACES]]), s, object->curr_smoothing, &(object->indexes[I_FACES])));
	movq	%rdx, %rax	# _62, tmp191
	addq	%rax, %rax	# tmp191
	addq	%rdx, %rax	# _62, tmp191
	salq	$2, %rax	#, tmp191
	addq	%rdx, %rax	# _62, tmp191
	salq	$4, %rax	#, tmp192
# srcs/parsing/__init_utils.c:31: 		return (get_faces(&(object->faces[object->indexes[I_FACES]]), s, object->curr_smoothing, &(object->indexes[I_FACES])));
	addq	%rax, %rdi	# _63, _64
	movq	-16(%rbp), %rax	# s, tmp193
	movl	%esi, %edx	# _60,
	movq	%rax, %rsi	# tmp193,
	call	get_faces@PLT	#
	jmp	.L11	#
.L15:
# srcs/parsing/__init_utils.c:32: 	else if (**s == 's' && ft_iswhitespace(*((*s) + 1)))
	movq	-16(%rbp), %rax	# s, tmp194
	movq	(%rax), %rax	# *s_82(D), _65
# srcs/parsing/__init_utils.c:32: 	else if (**s == 's' && ft_iswhitespace(*((*s) + 1)))
	movzbl	(%rax), %eax	# *_65, _66
# srcs/parsing/__init_utils.c:32: 	else if (**s == 's' && ft_iswhitespace(*((*s) + 1)))
	cmpb	$115, %al	#, _66
	jne	.L16	#,
# srcs/parsing/__init_utils.c:32: 	else if (**s == 's' && ft_iswhitespace(*((*s) + 1)))
	movq	-16(%rbp), %rax	# s, tmp195
	movq	(%rax), %rax	# *s_82(D), _67
# srcs/parsing/__init_utils.c:32: 	else if (**s == 's' && ft_iswhitespace(*((*s) + 1)))
	addq	$1, %rax	#, _68
# srcs/parsing/__init_utils.c:32: 	else if (**s == 's' && ft_iswhitespace(*((*s) + 1)))
	movzbl	(%rax), %eax	# *_68, _69
# srcs/parsing/__init_utils.c:32: 	else if (**s == 's' && ft_iswhitespace(*((*s) + 1)))
	movsbl	%al, %eax	# _69, _70
	movl	%eax, %edi	# _70,
	call	ft_iswhitespace@PLT	#
# srcs/parsing/__init_utils.c:32: 	else if (**s == 's' && ft_iswhitespace(*((*s) + 1)))
	testl	%eax, %eax	# _71
	je	.L16	#,
# srcs/parsing/__init_utils.c:33: 		return (get_smoothing(&object->curr_smoothing, s));
	movq	-8(%rbp), %rax	# object, tmp196
	leaq	176(%rax), %rdx	#, _72
	movq	-16(%rbp), %rax	# s, tmp197
	movq	%rax, %rsi	# tmp197,
	movq	%rdx, %rdi	# _72,
	call	get_smoothing@PLT	#
	jmp	.L11	#
.L16:
# srcs/parsing/__init_utils.c:38: 	return (3);
	movl	$3, %eax	#, _73
.L11:
# srcs/parsing/__init_utils.c:39: }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE7:
	.size	parse_type_objs, .-parse_type_objs
	.globl	print_all_structs
	.type	print_all_structs, @function
print_all_structs:
.LFB8:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# all, all
# srcs/parsing/__init_utils.c:43: 	print_ac(&all->ambient_light, &all->camera);
	movq	-8(%rbp), %rax	# all, tmp88
	leaq	24(%rax), %rdx	#, _1
	movq	-8(%rbp), %rax	# all, _2
	movq	%rdx, %rsi	# _1,
	movq	%rax, %rdi	# _2,
	call	print_ac@PLT	#
# srcs/parsing/__init_utils.c:44: 	print_l(all->lights, 0);
	movq	-8(%rbp), %rax	# all, tmp89
	movq	88(%rax), %rax	# all_7(D)->lights, _3
	movl	$0, %esi	#,
	movq	%rax, %rdi	# _3,
	call	print_l@PLT	#
# srcs/parsing/__init_utils.c:45: 	print_sp(all->spheres, 0);
	movq	-8(%rbp), %rax	# all, tmp90
	movq	96(%rax), %rax	# all_7(D)->spheres, _4
	movl	$0, %esi	#,
	movq	%rax, %rdi	# _4,
	call	print_sp@PLT	#
# srcs/parsing/__init_utils.c:46: 	print_pl(all->planes, 0);
	movq	-8(%rbp), %rax	# all, tmp91
	movq	104(%rax), %rax	# all_7(D)->planes, _5
	movl	$0, %esi	#,
	movq	%rax, %rdi	# _5,
	call	print_pl@PLT	#
# srcs/parsing/__init_utils.c:47: 	print_cy(all->cylinders, 0);
	movq	-8(%rbp), %rax	# all, tmp92
	movq	112(%rax), %rax	# all_7(D)->cylinders, _6
	movl	$0, %esi	#,
	movq	%rax, %rdi	# _6,
	call	print_cy@PLT	#
# srcs/parsing/__init_utils.c:48: }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE8:
	.size	print_all_structs, .-print_all_structs
	.section	.rodata
	.align 8
.LC0:
	.string	"Error:\nUnwanted character: ['%c'] \t\t\t\t\nin line: [%lu]\n"
	.text
	.globl	__set_values_scene
	.type	__set_values_scene, @function
__set_values_scene:
.LFB9:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$32, %rsp	#,
	movq	%rdi, -24(%rbp)	# all, all
	movq	%rsi, -32(%rbp)	# s, s
# srcs/parsing/__init_utils.c:54: 	skip_whitespace_hashtag(s, &(__get_all()->line_count));
	call	__get_all@PLT	#
# srcs/parsing/__init_utils.c:54: 	skip_whitespace_hashtag(s, &(__get_all()->line_count));
	leaq	152(%rax), %rdx	#, _2
	movq	-32(%rbp), %rax	# s, tmp93
	movq	%rdx, %rsi	# _2,
	movq	%rax, %rdi	# tmp93,
	call	skip_whitespace_hashtag@PLT	#
# srcs/parsing/__init_utils.c:55: 	err = 0;
	movl	$0, -4(%rbp)	#, err
# srcs/parsing/__init_utils.c:56: 	while (err != 2 && *s && **s)
	jmp	.L19	#
.L23:
# srcs/parsing/__init_utils.c:58: 		err = parse_type_scene(all, s);
	movq	-32(%rbp), %rdx	# s, tmp94
	movq	-24(%rbp), %rax	# all, tmp95
	movq	%rdx, %rsi	# tmp94,
	movq	%rax, %rdi	# tmp95,
	call	parse_type_scene	#
	movl	%eax, -4(%rbp)	# tmp96, err
# srcs/parsing/__init_utils.c:59: 		if (err == 1)
	cmpl	$1, -4(%rbp)	#, err
	jne	.L20	#,
# srcs/parsing/__init_utils.c:60: 			return (err);
	movl	-4(%rbp), %eax	# err, _11
	jmp	.L21	#
.L20:
# srcs/parsing/__init_utils.c:61: 		else if (err == 3)
	cmpl	$3, -4(%rbp)	#, err
	jne	.L19	#,
# srcs/parsing/__init_utils.c:62: 			return (printf("Error:\nUnwanted character: ['%c'] \
	movq	-24(%rbp), %rax	# all, tmp97
	movq	152(%rax), %rdx	# all_19(D)->line_count, _3
# srcs/parsing/__init_utils.c:63: 				\nin line: [%lu]\n", **s, all->line_count), 1);
	movq	-32(%rbp), %rax	# s, tmp98
	movq	(%rax), %rax	# *s_16(D), _4
# srcs/parsing/__init_utils.c:63: 				\nin line: [%lu]\n", **s, all->line_count), 1);
	movzbl	(%rax), %eax	# *_4, _5
# srcs/parsing/__init_utils.c:62: 			return (printf("Error:\nUnwanted character: ['%c'] \
	movsbl	%al, %eax	# _5, _6
	movl	%eax, %esi	# _6,
	leaq	.LC0(%rip), %rax	#, tmp99
	movq	%rax, %rdi	# tmp99,
	movl	$0, %eax	#,
	call	printf@PLT	#
# srcs/parsing/__init_utils.c:63: 				\nin line: [%lu]\n", **s, all->line_count), 1);
	movl	$1, %eax	#, _11
	jmp	.L21	#
.L19:
# srcs/parsing/__init_utils.c:56: 	while (err != 2 && *s && **s)
	cmpl	$2, -4(%rbp)	#, err
	je	.L22	#,
# srcs/parsing/__init_utils.c:56: 	while (err != 2 && *s && **s)
	movq	-32(%rbp), %rax	# s, tmp100
	movq	(%rax), %rax	# *s_16(D), _7
# srcs/parsing/__init_utils.c:56: 	while (err != 2 && *s && **s)
	testq	%rax, %rax	# _7
	je	.L22	#,
# srcs/parsing/__init_utils.c:56: 	while (err != 2 && *s && **s)
	movq	-32(%rbp), %rax	# s, tmp101
	movq	(%rax), %rax	# *s_16(D), _8
# srcs/parsing/__init_utils.c:56: 	while (err != 2 && *s && **s)
	movzbl	(%rax), %eax	# *_8, _9
# srcs/parsing/__init_utils.c:56: 	while (err != 2 && *s && **s)
	testb	%al, %al	# _9
	jne	.L23	#,
.L22:
# srcs/parsing/__init_utils.c:65: 	return (0);
	movl	$0, %eax	#, _11
.L21:
# srcs/parsing/__init_utils.c:66: }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE9:
	.size	__set_values_scene, .-__set_values_scene
	.section	.rodata
.LC1:
	.string	"malloc error - vertices"
	.align 8
.LC2:
	.string	"malloc error - vertices texture"
	.align 8
.LC3:
	.string	"malloc error - vertices normale"
.LC4:
	.string	"malloc error - faces"
.LC5:
	.string	"malloc error - points"
	.text
	.globl	__mallocate_objs_values
	.type	__mallocate_objs_values, @function
__mallocate_objs_values:
.LFB10:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# object, object
	movq	%rsi, -16(%rbp)	# s, s
# srcs/parsing/__init_utils.c:70: 	if (get_letters(object, s))
	movq	-16(%rbp), %rdx	# s, tmp115
	movq	-8(%rbp), %rax	# object, tmp116
	movq	%rdx, %rsi	# tmp115,
	movq	%rax, %rdi	# tmp116,
	call	get_letters@PLT	#
# srcs/parsing/__init_utils.c:70: 	if (get_letters(object, s))
	testl	%eax, %eax	# _1
	je	.L25	#,
# srcs/parsing/__init_utils.c:71: 		return (1);
	movl	$1, %eax	#, _32
	jmp	.L26	#
.L25:
# srcs/parsing/__init_utils.c:72: 	if (object->nb_vertices)
	movq	-8(%rbp), %rax	# object, tmp117
	movq	232(%rax), %rax	# object_40(D)->nb_vertices, _2
# srcs/parsing/__init_utils.c:72: 	if (object->nb_vertices)
	testq	%rax, %rax	# _2
	je	.L27	#,
# srcs/parsing/__init_utils.c:73: 		object->vertices = malloc(sizeof(t_vertice) * (object->nb_vertices));
	movq	-8(%rbp), %rax	# object, tmp118
	movq	232(%rax), %rdx	# object_40(D)->nb_vertices, _3
# srcs/parsing/__init_utils.c:73: 		object->vertices = malloc(sizeof(t_vertice) * (object->nb_vertices));
	movq	%rdx, %rax	# _3, tmp119
	addq	%rax, %rax	# tmp119
	addq	%rdx, %rax	# _3, tmp119
	salq	$3, %rax	#, tmp120
	movq	%rax, %rdi	# _4,
	call	malloc@PLT	#
	movq	%rax, %rdx	# tmp121, _5
# srcs/parsing/__init_utils.c:73: 		object->vertices = malloc(sizeof(t_vertice) * (object->nb_vertices));
	movq	-8(%rbp), %rax	# object, tmp122
	movq	%rdx, 136(%rax)	# _5, object_40(D)->vertices
.L27:
# srcs/parsing/__init_utils.c:74: 	if (object->nb_vertices && !object->vertices)
	movq	-8(%rbp), %rax	# object, tmp123
	movq	232(%rax), %rax	# object_40(D)->nb_vertices, _6
# srcs/parsing/__init_utils.c:74: 	if (object->nb_vertices && !object->vertices)
	testq	%rax, %rax	# _6
	je	.L28	#,
# srcs/parsing/__init_utils.c:74: 	if (object->nb_vertices && !object->vertices)
	movq	-8(%rbp), %rax	# object, tmp124
	movq	136(%rax), %rax	# object_40(D)->vertices, _7
# srcs/parsing/__init_utils.c:74: 	if (object->nb_vertices && !object->vertices)
	testq	%rax, %rax	# _7
	jne	.L28	#,
# srcs/parsing/__init_utils.c:75: 		return (printf("malloc error - vertices\n"), 1);
	leaq	.LC1(%rip), %rax	#, tmp125
	movq	%rax, %rdi	# tmp125,
	call	puts@PLT	#
# srcs/parsing/__init_utils.c:75: 		return (printf("malloc error - vertices\n"), 1);
	movl	$1, %eax	#, _32
	jmp	.L26	#
.L28:
# srcs/parsing/__init_utils.c:76: 	if (object->nb_vt)
	movq	-8(%rbp), %rax	# object, tmp126
	movq	240(%rax), %rax	# object_40(D)->nb_vt, _8
# srcs/parsing/__init_utils.c:76: 	if (object->nb_vt)
	testq	%rax, %rax	# _8
	je	.L29	#,
# srcs/parsing/__init_utils.c:77: 		object->vt = malloc(sizeof(t_vertice_t) * (object->nb_vt));
	movq	-8(%rbp), %rax	# object, tmp127
	movq	240(%rax), %rdx	# object_40(D)->nb_vt, _9
# srcs/parsing/__init_utils.c:77: 		object->vt = malloc(sizeof(t_vertice_t) * (object->nb_vt));
	movq	%rdx, %rax	# _9, tmp128
	addq	%rax, %rax	# tmp128
	addq	%rdx, %rax	# _9, tmp128
	salq	$3, %rax	#, tmp129
	movq	%rax, %rdi	# _10,
	call	malloc@PLT	#
	movq	%rax, %rdx	# tmp130, _11
# srcs/parsing/__init_utils.c:77: 		object->vt = malloc(sizeof(t_vertice_t) * (object->nb_vt));
	movq	-8(%rbp), %rax	# object, tmp131
	movq	%rdx, 144(%rax)	# _11, object_40(D)->vt
.L29:
# srcs/parsing/__init_utils.c:78: 	if (object->nb_vt && !object->vt)
	movq	-8(%rbp), %rax	# object, tmp132
	movq	240(%rax), %rax	# object_40(D)->nb_vt, _12
# srcs/parsing/__init_utils.c:78: 	if (object->nb_vt && !object->vt)
	testq	%rax, %rax	# _12
	je	.L30	#,
# srcs/parsing/__init_utils.c:78: 	if (object->nb_vt && !object->vt)
	movq	-8(%rbp), %rax	# object, tmp133
	movq	144(%rax), %rax	# object_40(D)->vt, _13
# srcs/parsing/__init_utils.c:78: 	if (object->nb_vt && !object->vt)
	testq	%rax, %rax	# _13
	jne	.L30	#,
# srcs/parsing/__init_utils.c:79: 		return (printf("malloc error - vertices texture\n"), 1);
	leaq	.LC2(%rip), %rax	#, tmp134
	movq	%rax, %rdi	# tmp134,
	call	puts@PLT	#
# srcs/parsing/__init_utils.c:79: 		return (printf("malloc error - vertices texture\n"), 1);
	movl	$1, %eax	#, _32
	jmp	.L26	#
.L30:
# srcs/parsing/__init_utils.c:80: 	if (object->nb_vn)
	movq	-8(%rbp), %rax	# object, tmp135
	movq	248(%rax), %rax	# object_40(D)->nb_vn, _14
# srcs/parsing/__init_utils.c:80: 	if (object->nb_vn)
	testq	%rax, %rax	# _14
	je	.L31	#,
# srcs/parsing/__init_utils.c:81: 		object->vn = malloc(sizeof(t_vertice_n) * (object->nb_vn));
	movq	-8(%rbp), %rax	# object, tmp136
	movq	248(%rax), %rdx	# object_40(D)->nb_vn, _15
# srcs/parsing/__init_utils.c:81: 		object->vn = malloc(sizeof(t_vertice_n) * (object->nb_vn));
	movq	%rdx, %rax	# _15, tmp137
	addq	%rax, %rax	# tmp137
	addq	%rdx, %rax	# _15, tmp137
	salq	$3, %rax	#, tmp138
	movq	%rax, %rdi	# _16,
	call	malloc@PLT	#
	movq	%rax, %rdx	# tmp139, _17
# srcs/parsing/__init_utils.c:81: 		object->vn = malloc(sizeof(t_vertice_n) * (object->nb_vn));
	movq	-8(%rbp), %rax	# object, tmp140
	movq	%rdx, 152(%rax)	# _17, object_40(D)->vn
.L31:
# srcs/parsing/__init_utils.c:82: 	if (object->nb_vn && !object->vn)
	movq	-8(%rbp), %rax	# object, tmp141
	movq	248(%rax), %rax	# object_40(D)->nb_vn, _18
# srcs/parsing/__init_utils.c:82: 	if (object->nb_vn && !object->vn)
	testq	%rax, %rax	# _18
	je	.L32	#,
# srcs/parsing/__init_utils.c:82: 	if (object->nb_vn && !object->vn)
	movq	-8(%rbp), %rax	# object, tmp142
	movq	152(%rax), %rax	# object_40(D)->vn, _19
# srcs/parsing/__init_utils.c:82: 	if (object->nb_vn && !object->vn)
	testq	%rax, %rax	# _19
	jne	.L32	#,
# srcs/parsing/__init_utils.c:83: 		return (printf("malloc error - vertices normale\n"), 1);
	leaq	.LC3(%rip), %rax	#, tmp143
	movq	%rax, %rdi	# tmp143,
	call	puts@PLT	#
# srcs/parsing/__init_utils.c:83: 		return (printf("malloc error - vertices normale\n"), 1);
	movl	$1, %eax	#, _32
	jmp	.L26	#
.L32:
# srcs/parsing/__init_utils.c:84: 	if (object->nb_faces)
	movq	-8(%rbp), %rax	# object, tmp144
	movq	256(%rax), %rax	# object_40(D)->nb_faces, _20
# srcs/parsing/__init_utils.c:84: 	if (object->nb_faces)
	testq	%rax, %rax	# _20
	je	.L33	#,
# srcs/parsing/__init_utils.c:85: 		object->faces = malloc(sizeof(t_face) * (object->nb_faces));
	movq	-8(%rbp), %rax	# object, tmp145
	movq	256(%rax), %rdx	# object_40(D)->nb_faces, _21
# srcs/parsing/__init_utils.c:85: 		object->faces = malloc(sizeof(t_face) * (object->nb_faces));
	movq	%rdx, %rax	# _21, tmp146
	addq	%rax, %rax	# tmp146
	addq	%rdx, %rax	# _21, tmp146
	salq	$2, %rax	#, tmp146
	addq	%rdx, %rax	# _21, tmp146
	salq	$4, %rax	#, tmp147
	movq	%rax, %rdi	# _22,
	call	malloc@PLT	#
	movq	%rax, %rdx	# tmp148, _23
# srcs/parsing/__init_utils.c:85: 		object->faces = malloc(sizeof(t_face) * (object->nb_faces));
	movq	-8(%rbp), %rax	# object, tmp149
	movq	%rdx, 160(%rax)	# _23, object_40(D)->faces
.L33:
# srcs/parsing/__init_utils.c:86: 	if (object->nb_faces && !object->faces)
	movq	-8(%rbp), %rax	# object, tmp150
	movq	256(%rax), %rax	# object_40(D)->nb_faces, _24
# srcs/parsing/__init_utils.c:86: 	if (object->nb_faces && !object->faces)
	testq	%rax, %rax	# _24
	je	.L34	#,
# srcs/parsing/__init_utils.c:86: 	if (object->nb_faces && !object->faces)
	movq	-8(%rbp), %rax	# object, tmp151
	movq	160(%rax), %rax	# object_40(D)->faces, _25
# srcs/parsing/__init_utils.c:86: 	if (object->nb_faces && !object->faces)
	testq	%rax, %rax	# _25
	jne	.L34	#,
# srcs/parsing/__init_utils.c:87: 		return (printf("malloc error - faces\n"), 1);
	leaq	.LC4(%rip), %rax	#, tmp152
	movq	%rax, %rdi	# tmp152,
	call	puts@PLT	#
# srcs/parsing/__init_utils.c:87: 		return (printf("malloc error - faces\n"), 1);
	movl	$1, %eax	#, _32
	jmp	.L26	#
.L34:
# srcs/parsing/__init_utils.c:88: 	if (object->nb_points)
	movq	-8(%rbp), %rax	# object, tmp153
	movq	264(%rax), %rax	# object_40(D)->nb_points, _26
# srcs/parsing/__init_utils.c:88: 	if (object->nb_points)
	testq	%rax, %rax	# _26
	je	.L35	#,
# srcs/parsing/__init_utils.c:89: 		object->points = malloc(sizeof(t_point) * (object->nb_points));
	movq	-8(%rbp), %rax	# object, tmp154
	movq	264(%rax), %rax	# object_40(D)->nb_points, _27
# srcs/parsing/__init_utils.c:89: 		object->points = malloc(sizeof(t_point) * (object->nb_points));
	salq	$5, %rax	#, _28
	movq	%rax, %rdi	# _28,
	call	malloc@PLT	#
	movq	%rax, %rdx	# tmp155, _29
# srcs/parsing/__init_utils.c:89: 		object->points = malloc(sizeof(t_point) * (object->nb_points));
	movq	-8(%rbp), %rax	# object, tmp156
	movq	%rdx, 168(%rax)	# _29, object_40(D)->points
.L35:
# srcs/parsing/__init_utils.c:90: 	if (object->nb_points && !object->points)
	movq	-8(%rbp), %rax	# object, tmp157
	movq	264(%rax), %rax	# object_40(D)->nb_points, _30
# srcs/parsing/__init_utils.c:90: 	if (object->nb_points && !object->points)
	testq	%rax, %rax	# _30
	je	.L36	#,
# srcs/parsing/__init_utils.c:90: 	if (object->nb_points && !object->points)
	movq	-8(%rbp), %rax	# object, tmp158
	movq	168(%rax), %rax	# object_40(D)->points, _31
# srcs/parsing/__init_utils.c:90: 	if (object->nb_points && !object->points)
	testq	%rax, %rax	# _31
	jne	.L36	#,
# srcs/parsing/__init_utils.c:91: 		return (printf("malloc error - points\n"), 1);
	leaq	.LC5(%rip), %rax	#, tmp159
	movq	%rax, %rdi	# tmp159,
	call	puts@PLT	#
# srcs/parsing/__init_utils.c:91: 		return (printf("malloc error - points\n"), 1);
	movl	$1, %eax	#, _32
	jmp	.L26	#
.L36:
# srcs/parsing/__init_utils.c:92: 	return (0);
	movl	$0, %eax	#, _32
.L26:
# srcs/parsing/__init_utils.c:93: }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE10:
	.size	__mallocate_objs_values, .-__mallocate_objs_values
	.section	.rodata
	.align 8
.LC7:
	.string	"get_object() returned %.9f seconds\n"
.LC8:
	.string	"v: %ld\n"
.LC9:
	.string	"vt: %ld\n"
.LC10:
	.string	"f: %ld\n"
	.text
	.globl	__set_values_objs
	.type	__set_values_objs, @function
__set_values_objs:
.LFB11:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$80, %rsp	#,
	movq	%rdi, -72(%rbp)	# object, object
	movq	%rsi, -80(%rbp)	# s, s
# srcs/parsing/__init_utils.c:96: {
	movq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp128
	movq	%rax, -8(%rbp)	# tmp128, D.5078
	xorl	%eax, %eax	# tmp128
# srcs/parsing/__init_utils.c:101: 	skip_whitespace_hashtag(s, &(object->line_count));
	movq	-72(%rbp), %rax	# object, tmp103
	leaq	224(%rax), %rdx	#, _1
	movq	-80(%rbp), %rax	# s, tmp104
	movq	%rdx, %rsi	# _1,
	movq	%rax, %rdi	# tmp104,
	call	skip_whitespace_hashtag@PLT	#
# srcs/parsing/__init_utils.c:102: 	__mallocate_objs_values(object, *s);
	movq	-80(%rbp), %rax	# s, tmp105
	movq	(%rax), %rdx	# *s_26(D), _2
	movq	-72(%rbp), %rax	# object, tmp106
	movq	%rdx, %rsi	# _2,
	movq	%rax, %rdi	# tmp106,
	call	__mallocate_objs_values	#
# srcs/parsing/__init_utils.c:103: 	err = 0;
	movl	$0, -60(%rbp)	#, err
# srcs/parsing/__init_utils.c:104: 	clock_gettime(CLOCK_MONOTONIC, &start);
	leaq	-48(%rbp), %rax	#, tmp107
	movq	%rax, %rsi	# tmp107,
	movl	$1, %edi	#,
	call	clock_gettime@PLT	#
# srcs/parsing/__init_utils.c:105: 	while (err != 2)
	jmp	.L38	#
.L41:
# srcs/parsing/__init_utils.c:107: 		err = parse_type_objs(object, s);
	movq	-80(%rbp), %rdx	# s, tmp108
	movq	-72(%rbp), %rax	# object, tmp109
	movq	%rdx, %rsi	# tmp108,
	movq	%rax, %rdi	# tmp109,
	call	parse_type_objs	#
	movl	%eax, -60(%rbp)	# tmp110, err
# srcs/parsing/__init_utils.c:108: 		if (err == 1)
	cmpl	$1, -60(%rbp)	#, err
	jne	.L39	#,
# srcs/parsing/__init_utils.c:109: 			return (err);
	movl	-60(%rbp), %eax	# err, _21
	jmp	.L42	#
.L39:
# srcs/parsing/__init_utils.c:110: 		else if (err == 3)
	cmpl	$3, -60(%rbp)	#, err
	jne	.L38	#,
# srcs/parsing/__init_utils.c:111: 			return (printf("Error:\nUnwanted character: ['%c'] \
	movq	-72(%rbp), %rax	# object, tmp111
	movq	224(%rax), %rdx	# object_24(D)->line_count, _3
# srcs/parsing/__init_utils.c:112: 				\nin line: [%lu]\n", **s, object->line_count), 1);
	movq	-80(%rbp), %rax	# s, tmp112
	movq	(%rax), %rax	# *s_26(D), _4
# srcs/parsing/__init_utils.c:112: 				\nin line: [%lu]\n", **s, object->line_count), 1);
	movzbl	(%rax), %eax	# *_4, _5
# srcs/parsing/__init_utils.c:111: 			return (printf("Error:\nUnwanted character: ['%c'] \
	movsbl	%al, %eax	# _5, _6
	movl	%eax, %esi	# _6,
	leaq	.LC0(%rip), %rax	#, tmp113
	movq	%rax, %rdi	# tmp113,
	movl	$0, %eax	#,
	call	printf@PLT	#
# srcs/parsing/__init_utils.c:112: 				\nin line: [%lu]\n", **s, object->line_count), 1);
	movl	$1, %eax	#, _21
	jmp	.L42	#
.L38:
# srcs/parsing/__init_utils.c:105: 	while (err != 2)
	cmpl	$2, -60(%rbp)	#, err
	jne	.L41	#,
# srcs/parsing/__init_utils.c:114: 	clock_gettime(CLOCK_MONOTONIC, &end);
	leaq	-32(%rbp), %rax	#, tmp114
	movq	%rax, %rsi	# tmp114,
	movl	$1, %edi	#,
	call	clock_gettime@PLT	#
# srcs/parsing/__init_utils.c:115: 	duration = (end.tv_sec - start.tv_sec)
	movq	-32(%rbp), %rax	# end.tv_sec, _7
# srcs/parsing/__init_utils.c:115: 	duration = (end.tv_sec - start.tv_sec)
	movq	-48(%rbp), %rdx	# start.tv_sec, _8
# srcs/parsing/__init_utils.c:115: 	duration = (end.tv_sec - start.tv_sec)
	subq	%rdx, %rax	# _8, _9
# srcs/parsing/__init_utils.c:116: 		+ (end.tv_nsec - start.tv_nsec) / 1e9;
	pxor	%xmm1, %xmm1	# _10
	cvtsi2sdq	%rax, %xmm1	# _9, _10
# srcs/parsing/__init_utils.c:116: 		+ (end.tv_nsec - start.tv_nsec) / 1e9;
	movq	-24(%rbp), %rax	# end.tv_nsec, _11
# srcs/parsing/__init_utils.c:116: 		+ (end.tv_nsec - start.tv_nsec) / 1e9;
	movq	-40(%rbp), %rdx	# start.tv_nsec, _12
# srcs/parsing/__init_utils.c:116: 		+ (end.tv_nsec - start.tv_nsec) / 1e9;
	subq	%rdx, %rax	# _12, _13
# srcs/parsing/__init_utils.c:116: 		+ (end.tv_nsec - start.tv_nsec) / 1e9;
	pxor	%xmm0, %xmm0	# _14
	cvtsi2sdq	%rax, %xmm0	# _13, _14
	movsd	.LC6(%rip), %xmm2	#, tmp115
	divsd	%xmm2, %xmm0	# tmp115, _15
# srcs/parsing/__init_utils.c:115: 	duration = (end.tv_sec - start.tv_sec)
	addsd	%xmm1, %xmm0	# _10, tmp116
	movsd	%xmm0, -56(%rbp)	# tmp116, duration
# srcs/parsing/__init_utils.c:117: 	printf("get_object() returned %.9f seconds\n", duration);
	movq	-56(%rbp), %rax	# duration, tmp117
	movq	%rax, %xmm0	# tmp117,
	leaq	.LC7(%rip), %rax	#, tmp118
	movq	%rax, %rdi	# tmp118,
	movl	$1, %eax	#,
	call	printf@PLT	#
# srcs/parsing/__init_utils.c:118: 	printf("v: %ld\n", object->i_vertice[0]);
	movq	-72(%rbp), %rax	# object, tmp119
	movq	200(%rax), %rax	# object_24(D)->i_vertice[0], _16
	movq	%rax, %rsi	# _16,
	leaq	.LC8(%rip), %rax	#, tmp120
	movq	%rax, %rdi	# tmp120,
	movl	$0, %eax	#,
	call	printf@PLT	#
# srcs/parsing/__init_utils.c:119: 	printf("vt: %ld\n", object->i_vertice[1]);
	movq	-72(%rbp), %rax	# object, tmp121
	movq	208(%rax), %rax	# object_24(D)->i_vertice[1], _17
	movq	%rax, %rsi	# _17,
	leaq	.LC9(%rip), %rax	#, tmp122
	movq	%rax, %rdi	# tmp122,
	movl	$0, %eax	#,
	call	printf@PLT	#
# srcs/parsing/__init_utils.c:120: 	printf("vt: %ld\n", object->i_vertice[2]);
	movq	-72(%rbp), %rax	# object, tmp123
	movq	216(%rax), %rax	# object_24(D)->i_vertice[2], _18
	movq	%rax, %rsi	# _18,
	leaq	.LC9(%rip), %rax	#, tmp124
	movq	%rax, %rdi	# tmp124,
	movl	$0, %eax	#,
	call	printf@PLT	#
# srcs/parsing/__init_utils.c:121: 	printf("f: %ld\n", object->indexes[0]);
	movq	-72(%rbp), %rax	# object, tmp125
	movq	184(%rax), %rax	# object_24(D)->indexes[0], _19
	movq	%rax, %rsi	# _19,
	leaq	.LC10(%rip), %rax	#, tmp126
	movq	%rax, %rdi	# tmp126,
	movl	$0, %eax	#,
	call	printf@PLT	#
# srcs/parsing/__init_utils.c:150: 	return (0);
	movl	$0, %eax	#, _21
.L42:
# srcs/parsing/__init_utils.c:151: }
	movq	-8(%rbp), %rdx	# D.5078, tmp129
	subq	%fs:40, %rdx	# MEM[(<address-space-1> long unsigned int *)40B], tmp129
	je	.L43	#,
# srcs/parsing/__init_utils.c:151: }
	call	__stack_chk_fail@PLT	#
.L43:
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE11:
	.size	__set_values_objs, .-__set_values_objs
	.section	.rodata
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
