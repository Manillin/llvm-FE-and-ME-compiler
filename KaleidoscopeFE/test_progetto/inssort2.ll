declare double @randinit(double)

declare double @randk()

declare double @timek()

declare double @printval(double, double)

@A = common global [10 x double] zeroinitializer
define double @inssort() {
entry:
  %j = alloca double, align 8
  %pivot = alloca double, align 8
  %i = alloca double, align 8
  br label %init

init:                                             ; preds = %entry
  store double 1.000000e+00, ptr %i, align 8
  br label %cond

cond:                                             ; preds = %endloop6, %init
  %i1 = load double, ptr %i, align 8
  %lttest = fcmp ult double %i1, 1.000000e+01
  br i1 %lttest, label %loop, label %endloop

loop:                                             ; preds = %cond
  %i2 = load double, ptr %i, align 8
  %0 = fptrunc double %i2 to float
  %1 = fptosi float %0 to i32
  %2 = getelementptr inbounds [10 x double], ptr @A, i32 %1
  %A = load double, ptr %2, align 8
  store double %A, ptr %pivot, align 8
  store double 0.000000e+00, ptr %j, align 8
  br label %init3

endloop:                                          ; preds = %cond
  %3 = phi double [ 0.000000e+00, %cond ]
  ret double %3

init3:                                            ; preds = %loop
  %i7 = load double, ptr %i, align 8
  %subres = fsub double %i7, 1.000000e+00
  store double %subres, ptr %j, align 8
  br label %cond4

cond4:                                            ; preds = %loop5, %init3
  %j8 = load double, ptr %j, align 8
  %lttest9 = fcmp ult double -1.000000e+00, %j8
  %pivot10 = load double, ptr %pivot, align 8
  %j11 = load double, ptr %j, align 8
  %4 = fptrunc double %j11 to float
  %5 = fptosi float %4 to i32
  %6 = getelementptr inbounds [10 x double], ptr @A, i32 %5
  %A12 = load double, ptr %6, align 8
  %lttest13 = fcmp ult double %pivot10, %A12
  %andres = select i1 %lttest9, i1 %lttest13, i1 false
  br i1 %andres, label %loop5, label %endloop6

loop5:                                            ; preds = %cond4
  %j14 = load double, ptr %j, align 8
  %7 = fptrunc double %j14 to float
  %8 = fptosi float %7 to i32
  %9 = getelementptr inbounds [10 x double], ptr @A, i32 %8
  %A15 = load double, ptr %9, align 8
  %j16 = load double, ptr %j, align 8
  %addres = fadd double %j16, 1.000000e+00
  %10 = fptrunc double %addres to float
  %11 = fptosi float %10 to i32
  %12 = getelementptr inbounds [10 x double], ptr @A, i32 %11
  store double %A15, ptr %12, align 8
  %j17 = load double, ptr %j, align 8
  %subres18 = fsub double %j17, 1.000000e+00
  store double %subres18, ptr %j, align 8
  br label %cond4

endloop6:                                         ; preds = %cond4
  %13 = phi double [ 0.000000e+00, %cond4 ]
  %pivot19 = load double, ptr %pivot, align 8
  %j20 = load double, ptr %j, align 8
  %addres21 = fadd double %j20, 1.000000e+00
  %14 = fptrunc double %addres21 to float
  %15 = fptosi float %14 to i32
  %16 = getelementptr inbounds [10 x double], ptr @A, i32 %15
  store double %pivot19, ptr %16, align 8
  %i22 = load double, ptr %i, align 8
  %addres23 = fadd double %i22, 1.000000e+00
  store double %addres23, ptr %i, align 8
  br label %cond
}

define double @main() {
entry:
  %i15 = alloca double, align 8
  %i = alloca double, align 8
  %seed = alloca double, align 8
  %calltmp = call double @timek()
  store double %calltmp, ptr %seed, align 8
  %seed1 = load double, ptr %seed, align 8
  %calltmp2 = call double @randinit(double %seed1)
  br label %init

init:                                             ; preds = %entry
  store double 0.000000e+00, ptr %i, align 8
  br label %cond

cond:                                             ; preds = %loop, %init
  %i3 = load double, ptr %i, align 8
  %lttest = fcmp ult double %i3, 1.000000e+01
  br i1 %lttest, label %loop, label %endloop

loop:                                             ; preds = %cond
  %calltmp4 = call double @randk()
  %i5 = load double, ptr %i, align 8
  %0 = fptrunc double %i5 to float
  %1 = fptosi float %0 to i32
  %2 = getelementptr inbounds [10 x double], ptr @A, i32 %1
  store double %calltmp4, ptr %2, align 8
  %i6 = load double, ptr %i, align 8
  %3 = fptrunc double %i6 to float
  %4 = fptosi float %3 to i32
  %5 = getelementptr inbounds [10 x double], ptr @A, i32 %4
  %A = load double, ptr %5, align 8
  %calltmp7 = call double @printval(double %A, double 0.000000e+00)
  %i8 = load double, ptr %i, align 8
  %addres = fadd double %i8, 1.000000e+00
  store double %addres, ptr %i, align 8
  br label %cond

endloop:                                          ; preds = %cond
  %6 = phi double [ 0.000000e+00, %cond ]
  %calltmp9 = call double @printval(double 0.000000e+00, double 1.000000e+00)
  %calltmp10 = call double @inssort()
  br label %init11

init11:                                           ; preds = %endloop
  store double 0.000000e+00, ptr %i15, align 8
  br label %cond12

cond12:                                           ; preds = %loop13, %init11
  %i16 = load double, ptr %i15, align 8
  %lttest17 = fcmp ult double %i16, 1.000000e+01
  br i1 %lttest17, label %loop13, label %endloop14

loop13:                                           ; preds = %cond12
  %i18 = load double, ptr %i15, align 8
  %7 = fptrunc double %i18 to float
  %8 = fptosi float %7 to i32
  %9 = getelementptr inbounds [10 x double], ptr @A, i32 %8
  %A19 = load double, ptr %9, align 8
  %calltmp20 = call double @printval(double %A19, double 0.000000e+00)
  %i21 = load double, ptr %i15, align 8
  %addres22 = fadd double %i21, 1.000000e+00
  store double %addres22, ptr %i15, align 8
  br label %cond12

endloop14:                                        ; preds = %cond12
  %10 = phi double [ 0.000000e+00, %cond12 ]
  ret double %10
}

