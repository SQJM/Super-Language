**#get类型**


### base 所有 TOKEN 可以获取的基本类型
- name 名字
- type 类型
- front 获取前面的 TOKEN
- back 获取后面的 TOKEN

### `<argv>*`传入的指针类型参数
- index 指针层级 1:* 2:**

### `string`
- size 字符串大小
- value 如果字符串有初始值那么就会返回这个值,没有初始值就返回 null.动态赋值的不会参与编译时计算

### `struct|class|union|enum`传入的具有连续空间的键值对类型
- size 空间大小
- key_size 键 大小
