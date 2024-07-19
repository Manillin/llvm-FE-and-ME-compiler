	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 13, 0
	.globl	_iterate                        ; -- Begin function iterate
	.p2align	2
_iterate:                               ; @iterate
	.cfi_startproc
; %bb.0:                                ; %entry
	mov	x8, #17197                      ; =0x432d
	fmul	d2, d1, d1
	movk	x8, #60188, lsl #16
	movk	x8, #14050, lsl #32
	movk	x8, #16154, lsl #48
	stp	d0, d1, [sp, #-32]!
	.cfi_def_cfa_offset 32
	fmov	d1, #2.00000000
	str	x8, [sp, #16]
	str	d2, [sp, #24]
LBB0_1:                                 ; %cond
                                        ; =>This Inner Loop Header: Depth=1
	ldp	d4, d0, [sp, #16]
	ldr	d2, [sp]
	fsub	d3, d0, d2
	fsub	d0, d2, d0
	fcmp	d4, d3
	fccmp	d4, d0, #8, ge
	ldr	d0, [sp, #8]
	b.ge	LBB0_3
; %bb.2:                                ; %loop
                                        ;   in Loop: Header=BB0_1 Depth=1
	ldp	d3, d2, [sp]
	fdiv	d3, d3, d2
	fmul	d0, d2, d0
	str	d0, [sp, #24]
	fadd	d3, d2, d3
	fdiv	d3, d3, d1
	str	d3, [sp, #8]
	b	LBB0_1
LBB0_3:                                 ; %endloop
	add	sp, sp, #32
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_sqrt                           ; -- Begin function sqrt
	.p2align	2
_sqrt:                                  ; @sqrt
	.cfi_startproc
; %bb.0:                                ; %entry
	sub	sp, sp, #32
	stp	x29, x30, [sp, #16]             ; 16-byte Folded Spill
	.cfi_def_cfa_offset 32
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	fmov	d1, d0
	fmov	d0, #1.00000000
	fcmp	d1, d0
	str	d1, [sp, #8]
	b.eq	LBB1_5
	b.vs	LBB1_5
; %bb.1:                                ; %falseblock
	ldr	d0, [sp, #8]
	fmov	d1, #1.00000000
	fcmp	d0, d1
	b.ge	LBB1_3
; %bb.2:                                ; %trueblock4
	fsub	d1, d1, d0
	b	LBB1_4
LBB1_3:                                 ; %falseblock7
	fmov	d1, #2.00000000
	fdiv	d1, d0, d1
LBB1_4:                                 ; %mergeblock
	bl	_iterate
LBB1_5:                                 ; %mergeblock11
	ldp	x29, x30, [sp, #16]             ; 16-byte Folded Reload
	add	sp, sp, #32
	ret
	.cfi_endproc
                                        ; -- End function
.subsections_via_symbols
