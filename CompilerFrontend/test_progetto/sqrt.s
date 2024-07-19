	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 13, 0
	.globl	_err                            ; -- Begin function err
	.p2align	2
_err:                                   ; @err
	.cfi_startproc
; %bb.0:                                ; %entry
	fcmp	d0, d1
	stp	d0, d1, [sp, #-16]!
	.cfi_def_cfa_offset 16
	b.ge	LBB0_2
; %bb.1:                                ; %trueblock
	ldp	d1, d0, [sp]
	b	LBB0_3
LBB0_2:                                 ; %falseblock
	ldp	d0, d1, [sp]
LBB0_3:                                 ; %mergeblock
	fsub	d0, d0, d1
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_iterate                        ; -- Begin function iterate
	.p2align	2
_iterate:                               ; @iterate
	.cfi_startproc
; %bb.0:                                ; %entry
	sub	sp, sp, #64
	stp	d9, d8, [sp, #32]               ; 16-byte Folded Spill
	stp	x29, x30, [sp, #48]             ; 16-byte Folded Spill
	.cfi_def_cfa_offset 64
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset b8, -24
	.cfi_offset b9, -32
	mov	x8, #17197                      ; =0x432d
	fmul	d2, d1, d1
	movk	x8, #60188, lsl #16
	fmov	d8, #2.00000000
	movk	x8, #14050, lsl #32
	stp	d0, d1, [sp]
	movk	x8, #16154, lsl #48
	str	d2, [sp, #24]
	str	x8, [sp, #16]
LBB1_1:                                 ; %cond
                                        ; =>This Inner Loop Header: Depth=1
	ldp	d9, d0, [sp, #16]
	ldr	d1, [sp]
	bl	_err
	fcmp	d9, d0
	ldr	d0, [sp, #8]
	b.ge	LBB1_3
; %bb.2:                                ; %loop
                                        ;   in Loop: Header=BB1_1 Depth=1
	ldp	d2, d1, [sp]
	fdiv	d2, d2, d1
	fmul	d0, d1, d0
	str	d0, [sp, #24]
	fadd	d2, d1, d2
	fdiv	d2, d2, d8
	str	d2, [sp, #8]
	b	LBB1_1
LBB1_3:                                 ; %endloop
	ldp	x29, x30, [sp, #48]             ; 16-byte Folded Reload
	ldp	d9, d8, [sp, #32]               ; 16-byte Folded Reload
	add	sp, sp, #64
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
	b.eq	LBB2_5
	b.vs	LBB2_5
; %bb.1:                                ; %falseblock
	ldr	d0, [sp, #8]
	fmov	d1, #1.00000000
	fcmp	d0, d1
	b.ge	LBB2_3
; %bb.2:                                ; %trueblock4
	fsub	d1, d1, d0
	b	LBB2_4
LBB2_3:                                 ; %falseblock7
	fmov	d1, #2.00000000
	fdiv	d1, d0, d1
LBB2_4:                                 ; %mergeblock
	bl	_iterate
LBB2_5:                                 ; %mergeblock11
	ldp	x29, x30, [sp, #16]             ; 16-byte Folded Reload
	add	sp, sp, #32
	ret
	.cfi_endproc
                                        ; -- End function
.subsections_via_symbols
