; ModuleID = 'test.ll'
source_filename = "5.functions.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@0 = private unnamed_addr constant [15 x i8] c"add_2: start \0A\00", align 1
@timeSpent = private unnamed_addr constant [22 x i8] c"add_2: timespent %ld\0A\00", align 1
@1 = private unnamed_addr constant [15 x i8] c"add_3: start \0A\00", align 1
@timeSpent.1 = private unnamed_addr constant [22 x i8] c"add_3: timespent %ld\0A\00", align 1
@2 = private unnamed_addr constant [19 x i8] c"slow_func: start \0A\00", align 1
@timeSpent.2 = private unnamed_addr constant [26 x i8] c"slow_func: timespent %ld\0A\00", align 1
@3 = private unnamed_addr constant [14 x i8] c"main: start \0A\00", align 1
@timeSpent.3 = private unnamed_addr constant [21 x i8] c"main: timespent %ld\0A\00", align 1

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @add_2(i32 %a, i32 %b) #0 {
entry:
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @0, i32 0, i32 0))
  %clock = call i64 (...) @clock()
  %a.addr = alloca i32, align 4
  %b.addr = alloca i32, align 4
  %temp = alloca i32, align 4
  store i32 %a, i32* %a.addr, align 4
  store i32 %b, i32* %b.addr, align 4
  %0 = load i32, i32* %a.addr, align 4
  %1 = load i32, i32* %b.addr, align 4
  %add = add nsw i32 %0, %1
  store i32 %add, i32* %temp, align 4
  %2 = load i32, i32* %temp, align 4
  %clock1 = call i64 (...) @clock()
  %timeSpent = sub i64 %clock1, %clock
  %printf2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([22 x i8], [22 x i8]* @timeSpent, i32 0, i32 0), i64 %timeSpent)
  ret i32 %2
}

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @add_3(i32 %a, i32 %b, i32 %c) #0 {
entry:
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @1, i32 0, i32 0))
  %clock = call i64 (...) @clock()
  %a.addr = alloca i32, align 4
  %b.addr = alloca i32, align 4
  %c.addr = alloca i32, align 4
  %temp = alloca i32, align 4
  store i32 %a, i32* %a.addr, align 4
  store i32 %b, i32* %b.addr, align 4
  store i32 %c, i32* %c.addr, align 4
  %0 = load i32, i32* %a.addr, align 4
  %1 = load i32, i32* %b.addr, align 4
  %add = add nsw i32 %0, %1
  %2 = load i32, i32* %c.addr, align 4
  %add1 = add nsw i32 %add, %2
  store i32 %add1, i32* %temp, align 4
  %3 = load i32, i32* %temp, align 4
  %clock1 = call i64 (...) @clock()
  %timeSpent = sub i64 %clock1, %clock
  %printf2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([22 x i8], [22 x i8]* @timeSpent.1, i32 0, i32 0), i64 %timeSpent)
  ret i32 %3
}

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @slow_func() #0 {
entry:
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @2, i32 0, i32 0))
  %clock = call i64 (...) @clock()
  %a = alloca i32, align 4
  %i = alloca i32, align 4
  store i32 0, i32* %a, align 4
  store i32 0, i32* %i, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %i, align 4
  %cmp = icmp slt i32 %0, 999999
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %1 = load i32, i32* %a, align 4
  %2 = load i32, i32* %i, align 4
  %3 = load i32, i32* %a, align 4
  %4 = load i32, i32* %i, align 4
  %sub = sub nsw i32 %3, %4
  %mul = mul nsw i32 %2, %sub
  %add = add nsw i32 %1, %mul
  store i32 %add, i32* %a, align 4
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %5 = load i32, i32* %i, align 4
  %inc = add nsw i32 %5, 1
  store i32 %inc, i32* %i, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %6 = load i32, i32* %a, align 4
  %clock1 = call i64 (...) @clock()
  %timeSpent = sub i64 %clock1, %clock
  %printf2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([26 x i8], [26 x i8]* @timeSpent.2, i32 0, i32 0), i64 %timeSpent)
  ret i32 %6
}

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main(i32 %argc, i8** %argv) #0 {
entry:
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @3, i32 0, i32 0))
  %clock = call i64 (...) @clock()
  %retval = alloca i32, align 4
  %argc.addr = alloca i32, align 4
  %argv.addr = alloca i8**, align 8
  %s = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  store i32 %argc, i32* %argc.addr, align 4
  store i8** %argv, i8*** %argv.addr, align 8
  store i32 0, i32* %s, align 4
  %0 = load i32, i32* %s, align 4
  %call = call i32 @add_2(i32 2, i32 3)
  %add = add nsw i32 %0, %call
  store i32 %add, i32* %s, align 4
  %1 = load i32, i32* %s, align 4
  %call1 = call i32 @add_3(i32 4, i32 5, i32 6)
  %add2 = add nsw i32 %1, %call1
  store i32 %add2, i32* %s, align 4
  %call3 = call i32 @slow_func()
  store i32 %call3, i32* %s, align 4
  %clock1 = call i64 (...) @clock()
  %timeSpent = sub i64 %clock1, %clock
  %printf2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @timeSpent.3, i32 0, i32 0), i64 %timeSpent)
  ret i32 0
}

declare i32 @printf(i8*, ...)

declare i64 @clock(...)

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 11.0.0 (https://github.com/llvm/llvm-project.git 0bc2eab6f5cd522eb83b2b862ce8a2651c97ee59)"}
