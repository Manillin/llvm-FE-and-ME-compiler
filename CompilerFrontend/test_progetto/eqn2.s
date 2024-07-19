	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 13, 0
	.globl	_eqn2                           ; -- Begin function eqn2
	.p2align	2
_eqn2:                                  ; @eqn2
	.cfi_startproc
; %bb.0:                                ; %entry
	sub	sp, sp, #112
	stp	x29, x30, [sp, #96]             ; 16-byte Folded Spill
	.cfi_def_cfa_offset 112
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	fmov	d3, #-4.00000000
	fmul	d4, d1, d1
	stp	d0, d1, [sp, #8]
	fmul	d3, d0, d3
	fmul	d3, d3, d2
	fadd	d3, d4, d3
	fcmp	d3, #0.0
	stp	d2, d3, [sp, #24]
	b.ge	LBB0_3
; %bb.1:                                ; %trueblock
	movi	d2, #0000000000000000
	fsub	d1, d2, d3
	fsqrt	d0, d1
	fcmp	d0, d0
	b.vs	LBB0_9
LBB0_2:                                 ; %trueblock.split
	ldp	d1, d3, [sp, #8]
	fadd	d1, d1, d1
	fdiv	d3, d3, d1
	fdiv	d1, d0, d1
	fsub	d3, d2, d3
	stp	d0, d3, [sp, #40]
	str	d1, [sp, #56]
	b	LBB0_7
LBB0_3:                                 ; %falseblock
	b.mi	LBB0_5
	b.gt	LBB0_5
; %bb.4:                                ; %trueblock25
	ldp	d0, d1, [sp, #8]
	movi	d2, #0000000000000000
	fadd	d0, d0, d0
	fdiv	d0, d1, d0
	movi	d1, #0000000000000000
	fsub	d0, d1, d0
	str	d0, [sp, #64]
	b	LBB0_8
LBB0_5:                                 ; %falseblock33
	ldr	d1, [sp, #32]
	fsqrt	d0, d1
	fcmp	d0, d0
	b.vs	LBB0_10
LBB0_6:                                 ; %falseblock33.split
	movi	d1, #0000000000000000
	ldr	d2, [sp, #16]
	fsub	d1, d1, d2
	ldr	d2, [sp, #8]
	fadd	d2, d2, d2
	fadd	d3, d1, d0
	fsub	d1, d1, d0
	fdiv	d3, d3, d2
	fdiv	d1, d1, d2
	fmov	d2, #1.00000000
	stp	d0, d3, [sp, #72]
	str	d1, [sp, #88]
LBB0_7:                                 ; %mergeblock54
	fmov	d0, d3
LBB0_8:                                 ; %mergeblock54
	bl	_printval
	ldp	x29, x30, [sp, #96]             ; 16-byte Folded Reload
	movi	d0, #0000000000000000
	add	sp, sp, #112
	ret
LBB0_9:                                 ; %call.sqrt
	fmov	d0, d1
	bl	_sqrt
	movi	d2, #0000000000000000
	b	LBB0_2
LBB0_10:                                ; %call.sqrt1
	fmov	d0, d1
	bl	_sqrt
	b	LBB0_6
	.cfi_endproc
                                        ; -- End function
.subsections_via_symbols
