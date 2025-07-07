; 定义全局字符串 "hello\n"
@.str = private unnamed_addr constant [7 x i8] c"hello\0A\00"

; 定义全局字符串 "pause"
@.pause = private unnamed_addr constant [6 x i8] c"pause\00"

; 定义 WriteConsoleA 的外部声明
declare i32 @WriteConsoleA(i32, i8*, i32, i32*, i32) nounwind

; 定义 GetStdHandle 的外部声明
declare i32 @GetStdHandle(i32) nounwind

; 定义 system 的外部声明
declare i32 @system(i8*) nounwind

; 定义 main 函数
define i32 @main() {
entry:
    ; 获取标准输出句柄
    %stdout = call i32 @GetStdHandle(i32 -11)

    ; 准备字符串和长度
    %str = getelementptr [7 x i8], [7 x i8]* @.str, i32 0, i32 0
    %len = alloca i32
    store i32 6, i32* %len

    ; 调用 WriteConsoleA
    call i32 @WriteConsoleA(i32 %stdout, i8* %str, i32 6, i32* %len, i32 0)

    ; 调用 system("pause")
    %pause = getelementptr [6 x i8], [6 x i8]* @.pause, i32 0, i32 0
    call i32 @system(i8* %pause)

    ret i32 0
}