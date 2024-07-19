	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 13, 0
	.globl	_fibo                           ; -- Begin function fibo
	.p2align	2
_fibo:                                  ; @fibo
	.cfi_startproc
; %bb.0:                                ; %entry
	sub	sp, sp, #48
	.cfi_def_cfa_offset 48
	mov	x8, #4607182418800017408        ; =0x3ff0000000000000
	fmov	d1, #1.00000000
	str	d0, [sp, #8]
	stp	xzr, x8, [sp, #16]
	str	x8, [sp, #32]
LBB0_1:                                 ; %cond
                                        ; =>This Inner Loop Header: Depth=1
	ldr	d0, [sp, #32]
	ldr	d2, [sp, #8]
	fcmp	d0, d2
	b.ge	LBB0_3
; %bb.2:                                ; %loop
                                        ;   in Loop: Header=BB0_1 Depth=1
	ldp	d2, d0, [sp, #16]
	ldr	d3, [sp, #32]
	fadd	d2, d2, d0
	fadd	d3, d3, d1
	stp	d3, d0, [sp, #32]
	stp	d0, d2, [sp, #16]
	b	LBB0_1
LBB0_3:                                 ; %endloop
	ldr	d0, [sp, #24]
	add	sp, sp, #48
	ret
	.cfi_endproc
                                        ; -- End function
.subsections_via_symbols
