	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 13, 0
	.globl	_inssort                        ; -- Begin function inssort
	.p2align	2
_inssort:                               ; @inssort
	.cfi_startproc
; %bb.0:                                ; %entry
Lloh0:
	adrp	x9, _A@GOTPAGE
	mov	x8, #4607182418800017408        ; =0x3ff0000000000000
	fmov	d0, #10.00000000
	mov	w10, #80                        ; =0x50
	fmov	d1, #-1.00000000
	fmov	d2, #1.00000000
Lloh1:
	ldr	x9, [x9, _A@GOTPAGEOFF]
	mov	x11, #4621819117588971520       ; =0x4024000000000000
	str	x8, [sp, #-32]!
	.cfi_def_cfa_offset 32
	b	LBB0_3
LBB0_1:                                 ; %endloop6
                                        ;   in Loop: Header=BB0_3 Depth=1
	ldr	d3, [sp, #16]
	fcmp	d3, d2
	b.eq	LBB0_10
	b.vs	LBB0_10
LBB0_2:                                 ; %mergeblock27
                                        ;   in Loop: Header=BB0_3 Depth=1
	ldr	d3, [sp]
	fadd	d3, d3, d2
	str	d3, [sp]
LBB0_3:                                 ; %cond
                                        ; =>This Loop Header: Depth=1
                                        ;     Child Loop BB0_7 Depth 2
	ldr	d3, [sp]
	fcmp	d3, d0
	b.ge	LBB0_11
; %bb.4:                                ; %loop
                                        ;   in Loop: Header=BB0_3 Depth=1
	ldr	d3, [sp]
	str	x8, [sp, #16]
	fcvt	s4, d3
	fadd	d3, d3, d1
	fcvtzs	w12, s4
	smull	x12, w12, w10
	ldr	d4, [x9, x12]
	str	d4, [sp, #8]
	b	LBB0_7
LBB0_5:                                 ; %falseblock
                                        ;   in Loop: Header=BB0_7 Depth=2
	ldr	d3, [sp, #24]
	str	x11, [sp, #16]
	fadd	d3, d3, d2
	fcvt	s3, d3
	fcvtzs	w12, s3
	ldr	d3, [sp, #8]
	smull	x12, w12, w10
	str	d3, [x9, x12]
LBB0_6:                                 ; %mergeblock
                                        ;   in Loop: Header=BB0_7 Depth=2
	ldp	d4, d3, [sp, #16]
	fsub	d3, d3, d4
LBB0_7:                                 ; %cond4
                                        ;   Parent Loop BB0_3 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	str	d3, [sp, #24]
	ldr	d3, [sp, #24]
	fcmp	d3, d1
	b.ls	LBB0_1
; %bb.8:                                ; %loop5
                                        ;   in Loop: Header=BB0_7 Depth=2
	ldr	d3, [sp, #24]
	ldr	d4, [sp, #8]
	fcvt	s3, d3
	fcvtzs	w12, s3
	smull	x12, w12, w10
	ldr	d3, [x9, x12]
	fcmp	d4, d3
	b.ge	LBB0_5
; %bb.9:                                ; %trueblock
                                        ;   in Loop: Header=BB0_7 Depth=2
	ldr	d3, [sp, #24]
	fadd	d4, d3, d2
	fcvt	s3, d3
	fcvt	s4, d4
	fcvtzs	w12, s3
	smull	x12, w12, w10
	fcvtzs	w13, s4
	smull	x13, w13, w10
	ldr	d3, [x9, x12]
	str	d3, [x9, x13]
	b	LBB0_6
LBB0_10:                                ; %trueblock24
                                        ;   in Loop: Header=BB0_3 Depth=1
	ldr	d3, [sp, #8]
	str	d3, [x9]
	b	LBB0_2
LBB0_11:                                ; %endloop
	movi	d0, #0000000000000000
	add	sp, sp, #32
	ret
	.loh AdrpLdrGot	Lloh0, Lloh1
	.cfi_endproc
                                        ; -- End function
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:                                ; %entry
	sub	sp, sp, #80
	stp	d9, d8, [sp, #32]               ; 16-byte Folded Spill
	stp	x20, x19, [sp, #48]             ; 16-byte Folded Spill
	stp	x29, x30, [sp, #64]             ; 16-byte Folded Spill
	.cfi_def_cfa_offset 80
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	.cfi_offset b8, -40
	.cfi_offset b9, -48
	bl	_timek
	str	d0, [sp, #8]
	bl	_randinit
Lloh2:
	adrp	x19, _A@GOTPAGE
	fmov	d8, #10.00000000
	mov	w20, #80                        ; =0x50
	fmov	d9, #1.00000000
Lloh3:
	ldr	x19, [x19, _A@GOTPAGEOFF]
	str	xzr, [sp, #16]
LBB1_1:                                 ; %cond
                                        ; =>This Inner Loop Header: Depth=1
	ldr	d0, [sp, #16]
	fcmp	d0, d8
	b.ge	LBB1_3
; %bb.2:                                ; %loop
                                        ;   in Loop: Header=BB1_1 Depth=1
	bl	_randk
	ldr	d1, [sp, #16]
	fcvt	s1, d1
	fcvtzs	w8, s1
	movi	d1, #0000000000000000
	smull	x8, w8, w20
	str	d0, [x19, x8]
	bl	_printval
	ldr	d0, [sp, #16]
	fadd	d0, d0, d9
	str	d0, [sp, #16]
	b	LBB1_1
LBB1_3:                                 ; %endloop
	movi	d0, #0000000000000000
	fmov	d1, #1.00000000
	fmov	d8, #1.00000000
	bl	_printval
	bl	_inssort
	fmov	d9, #10.00000000
	mov	w20, #80                        ; =0x50
	str	xzr, [sp, #24]
LBB1_4:                                 ; %cond12
                                        ; =>This Inner Loop Header: Depth=1
	ldr	d0, [sp, #24]
	fcmp	d0, d9
	b.ge	LBB1_6
; %bb.5:                                ; %loop13
                                        ;   in Loop: Header=BB1_4 Depth=1
	ldr	d0, [sp, #24]
	movi	d1, #0000000000000000
	fcvt	s0, d0
	fcvtzs	w8, s0
	smull	x8, w8, w20
	ldr	d0, [x19, x8]
	bl	_printval
	ldr	d0, [sp, #24]
	fadd	d0, d0, d8
	str	d0, [sp, #24]
	b	LBB1_4
LBB1_6:                                 ; %endloop14
	ldp	x29, x30, [sp, #64]             ; 16-byte Folded Reload
	movi	d0, #0000000000000000
	ldp	x20, x19, [sp, #48]             ; 16-byte Folded Reload
	ldp	d9, d8, [sp, #32]               ; 16-byte Folded Reload
	add	sp, sp, #80
	ret
	.loh AdrpLdrGot	Lloh2, Lloh3
	.cfi_endproc
                                        ; -- End function
	.comm	_A,80,4                         ; @A
.subsections_via_symbols