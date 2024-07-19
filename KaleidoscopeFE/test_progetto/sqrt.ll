define double @err(double %a, double %b) {
entry:
  %b2 = alloca double, align 8
  %a1 = alloca double, align 8
  store double %a, ptr %a1, align 8
  store double %b, ptr %b2, align 8
  %a3 = load double, ptr %a1, align 8
  %b4 = load double, ptr %b2, align 8
  %lttest = fcmp ult double %a3, %b4
  br i1 %lttest, label %trueblock, label %falseblock

trueblock:                                        ; preds = %entry
  %b5 = load double, ptr %b2, align 8
  %a6 = load double, ptr %a1, align 8
  %subres = fsub double %b5, %a6
  br label %mergeblock

falseblock:                                       ; preds = %entry
  %a7 = load double, ptr %a1, align 8
  %b8 = load double, ptr %b2, align 8
  %subres9 = fsub double %a7, %b8
  br label %mergeblock

mergeblock:                                       ; preds = %falseblock, %trueblock
  %0 = phi double [ %subres, %trueblock ], [ %subres9, %falseblock ]
  ret double %0
}

define double @iterate(double %y, double %x) {
entry:
  %z = alloca double, align 8
  %eps = alloca double, align 8
  %x2 = alloca double, align 8
  %y1 = alloca double, align 8
  store double %y, ptr %y1, align 8
  store double %x, ptr %x2, align 8
  store double 1.000000e-04, ptr %eps, align 8
  br label %init

init:                                             ; preds = %entry
  %x3 = load double, ptr %x2, align 8
  %x4 = load double, ptr %x2, align 8
  %mulres = fmul double %x3, %x4
  store double %mulres, ptr %z, align 8
  br label %cond

cond:                                             ; preds = %loop, %init
  %eps5 = load double, ptr %eps, align 8
  %z6 = load double, ptr %z, align 8
  %y7 = load double, ptr %y1, align 8
  %calltmp = call double @err(double %z6, double %y7)
  %lttest = fcmp ult double %eps5, %calltmp
  br i1 %lttest, label %loop, label %endloop

loop:                                             ; preds = %cond
  %x8 = load double, ptr %x2, align 8
  %x9 = load double, ptr %x2, align 8
  %mulres10 = fmul double %x8, %x9
  store double %mulres10, ptr %z, align 8
  %x11 = load double, ptr %x2, align 8
  %y12 = load double, ptr %y1, align 8
  %x13 = load double, ptr %x2, align 8
  %addres = fdiv double %y12, %x13
  %addres14 = fadd double %x11, %addres
  %addres15 = fdiv double %addres14, 2.000000e+00
  store double %addres15, ptr %x2, align 8
  br label %cond

endloop:                                          ; preds = %cond
  %0 = phi double [ 0.000000e+00, %cond ]
  %x16 = load double, ptr %x2, align 8
  ret double %x16
}

define double @sqrt(double %y) {
entry:
  %y1 = alloca double, align 8
  store double %y, ptr %y1, align 8
  %y2 = load double, ptr %y1, align 8
  %eqtest = fcmp ueq double %y2, 1.000000e+00
  br i1 %eqtest, label %trueblock, label %falseblock

trueblock:                                        ; preds = %entry
  br label %mergeblock11

falseblock:                                       ; preds = %entry
  %y3 = load double, ptr %y1, align 8
  %lttest = fcmp ult double %y3, 1.000000e+00
  br i1 %lttest, label %trueblock4, label %falseblock7

trueblock4:                                       ; preds = %falseblock
  %y5 = load double, ptr %y1, align 8
  %y6 = load double, ptr %y1, align 8
  %subres = fsub double 1.000000e+00, %y6
  %calltmp = call double @iterate(double %y5, double %subres)
  br label %mergeblock

falseblock7:                                      ; preds = %falseblock
  %y8 = load double, ptr %y1, align 8
  %y9 = load double, ptr %y1, align 8
  %addres = fdiv double %y9, 2.000000e+00
  %calltmp10 = call double @iterate(double %y8, double %addres)
  br label %mergeblock

mergeblock:                                       ; preds = %falseblock7, %trueblock4
  %0 = phi double [ %calltmp, %trueblock4 ], [ %calltmp10, %falseblock7 ]
  br label %mergeblock11

mergeblock11:                                     ; preds = %mergeblock, %trueblock
  %1 = phi double [ 1.000000e+00, %trueblock ], [ %0, %mergeblock ]
  ret double %1
}
