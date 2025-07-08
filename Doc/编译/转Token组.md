**转Token组**

## 变量的声明
修饰符 -> 类型关键字 -> 变量名
```super
int a
int b
const int c
static const int d
unsigned int e
long int f
long long int g
unsigned long long int h
static unsigned long long int i
int* p
```

## 变量的定义
修饰符 -> 类型关键字 -> 变量名 -> = -> 值
```super
int a = 0
int b = 0
const int c = 0
static const int d = 0
unsigned int e = 0
long int f = 0
long long int g = 0
unsigned long long int h = 0
static unsigned long long int i = 0
int* p = nullptr
int** pp = &p
int* ppp = &a
```

## 功能的声明
修饰符 -> 返回类型 -> 功能名 -> ()
```super
void fn()
int fn1()
static int fn2()
static int* fn2()
```

## 功能的定义
修饰符 -> 返回类型 -> 功能名 -> () -> {}
```super
void fn() {}
int fn1() {}
static int fn2() {}
static int* fn2() {}
```

## 自定义类型的声明
类型 -> 新类型名
```super
typedef const long int int_long
typedef int* int_ptr
```