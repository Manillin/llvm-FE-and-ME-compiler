	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 13, 0
	.globl	_randk                          ; -- Begin function randk
	.p2align	2
_randk:                                 ; @randk
	.cfi_startproc
; %bb.0:                                ; %entry
	sub	sp, sp, #64
	stp	d9, d8, [sp, #16]               ; 16-byte Folded Spill
	stp	x20, x19, [sp, #32]             ; 16-byte Folded Spill
	stp	x29, x30, [sp, #48]             ; 16-byte Folded Spill
	.cfi_def_cfa_offset 64
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	.cfi_offset b8, -40
	.cfi_offset b9, -48
Lloh0:
	adrp	x8, _a@GOTPAGE
Lloh1:
	adrp	x19, _seed@GOTPAGE
Lloh2:
	adrp	x20, _m@GOTPAGE
Lloh3:
	ldr	x8, [x8, _a@GOTPAGEOFF]
Lloh4:
	ldr	x19, [x19, _seed@GOTPAGEOFF]
Lloh5:
	ldr	d0, [x8]
	ldr	d1, [x19]
Lloh6:
	ldr	x20, [x20, _m@GOTPAGEOFF]
	fmul	d8, d0, d1
	ldr	d9, [x20]
	fdiv	d0, d8, d9
	str	d8, [sp, #8]
	bl	_floor
	fmul	d0, d9, d0
	ldp	x29, x30, [sp, #48]             ; 16-byte Folded Reload
	fsub	d1, d8, d0
	ldr	d0, [x20]
	ldp	d9, d8, [sp, #16]               ; 16-byte Folded Reload
	str	d1, [x19]
	fdiv	d0, d1, d0
	ldp	x20, x19, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #64
	ret
	.loh AdrpLdrGot	Lloh2, Lloh6
	.loh AdrpLdrGot	Lloh1, Lloh4
	.loh AdrpLdrGotLdr	Lloh0, Lloh3, Lloh5
	.cfi_endproc
                                        ; -- End function
	.globl	_randinit                       ; -- Begin function randinit
	.p2align	2
_randinit:                              ; @randinit
	.cfi_startproc
; %bb.0:                                ; %entry
	sub	sp, sp, #48
	stp	d9, d8, [sp, #16]               ; 16-byte Folded Spill
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	.cfi_def_cfa_offset 48
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset b8, -24
	.cfi_offset b9, -32
	mov	x8, #281474972516352            ; =0xffffffc00000
	fmov	d8, d0
	movk	x8, #16863, lsl #48
Lloh7:
	adrp	x9, _m@GOTPAGE
Lloh8:
	adrp	x10, _a@GOTPAGE
	mov	x11, #141012366262272           ; =0x804000000000
	movk	x11, #16592, lsl #48
	fmov	d9, x8
Lloh9:
	ldr	x9, [x9, _m@GOTPAGEOFF]
Lloh10:
	ldr	x10, [x10, _a@GOTPAGEOFF]
	str	d8, [sp, #8]
	fdiv	d0, d0, d9
Lloh11:
	str	x8, [x9]
Lloh12:
	str	x11, [x10]
	bl	_floor
	fmov	d1, d0
Lloh13:
	adrp	x8, _seed@GOTPAGE
	movi	d0, #0000000000000000
Lloh14:
	ldr	x8, [x8, _seed@GOTPAGEOFF]
	fmul	d1, d1, d9
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	fsub	d1, d8, d1
	ldp	d9, d8, [sp, #16]               ; 16-byte Folded Reload
Lloh15:
	str	d1, [x8]
	add	sp, sp, #48
	ret
	.loh AdrpLdrGotStr	Lloh13, Lloh14, Lloh15
	.loh AdrpLdrGotStr	Lloh8, Lloh10, Lloh12
	.loh AdrpLdrGotStr	Lloh7, Lloh9, Lloh11
	.cfi_endproc
                                        ; -- End function
	.comm	_seed,8,3                       ; @seed
	.comm	_a,8,3                          ; @a
	.comm	_m,8,3                          ; @m
.subsections_via_symbols
