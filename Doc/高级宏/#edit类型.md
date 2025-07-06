**#edit类型**


### base 所有 TOKEN 可以编辑的基本类型
- name 名字
- type 类型
- add_front 在前面添加 TOKEN
- add_back 在后面添加 TOKEN

### `<argv>*`传入的指针类型参数
- index 修改指针层级,设置为 0 则转为普通变量
```super
#define_pro test($ptr:int*)
{
	#edit($str, index, 2)
}
#define_pro test($ptr:int**)
{
	#edit($str, index, 1)
}

int* p = nullptr
int** p2 = nullptr
test#(p)
test2#(p2)

; 编译结果
int** p = nullptr
int* p2 = nullptr
```

## `<argv>`传入的参数
- value 修改变量初始值
```super
#define_pro test($str:string)
{
	#edit($str, value, "aa")
}

string str = "abc"
test#(str)

; 编译结果
string str = "aa"
```

### `string`传入的字符串变量
- size_front 修改字符串大小,从前面开始修改
```super
#define_pro test($str:string)
{
	#edit($str, size_front, 2)
}
#define_pro test2($str:string)
{
	#edit($str, size_front, 5, ' ')
}

string str = "abc"
string str2 = "abc"
test#(str)
test2#(str2)

; 编译结果
string str = "bc"
string str2 = "  abc"
```
- size_back 修改字符串大小,从后面开始修改
```super
#define_pro test($str:string)
{
	#edit($str, size_back, 2)
}
#define_pro test2($str:string)
{
	#edit($str, size_back, 5, 'a')
}

string str = "abc"
string str2 = "abc"
test#(str)
test2#(str2)

; 编译结果
string str = "ab"
string str2 = "abcaa"
```

