# gdb 使用

文件的编译：

```
gcc -g -Wall program.c -o program
```

gdb命令:

```
gdb [可执行程序] 开始调试
quit 退出调试

给程序设置参数/获取设置参数
set args 10 20
show args

GDB帮助
help

查看当前文件代码
list/l 默认位置显示
list/l 行号 从指定行显示
list/l 函数名 从指定函数显示

查看非当前文件代码
list/l 文件名:行号
list/l 文件名:函数名

设置显示的行数
show list/listsize
set  list/listsize 行数

设置断点
b/break 行号
b/break 函数名
b/break 文件名:行号
b/break 文件名:函数名

查看断点:
i/info b/break

删除断点
d/del/delete 断点编号

设置断点无效
dis/disable 断点编号

设置断点生效
ena/enable 断点编号

设置条件断点
b/break 断点编号 if i==5

显示变量的值
print var
```

