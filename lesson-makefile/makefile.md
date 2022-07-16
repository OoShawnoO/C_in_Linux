# Makefile 写法

Makefile作用: 自动化编译

写法规范:

```makefile
目标...:依赖...
	Shell命令
	...
-------------------------------
app:main.c a.c b.c
	gcc main.c a.c b.c -o app

-------------------------------
app:main.o a.o b.o
	gcc main.o a.o b.o -o app

main.o:main.c
	gcc -c main.c -o main.o

a.o:a.c
	gcc -c a.c -o a.o
	
b.o:b.c
	gcc -c b.c -o a.o

#可以只重新编译更新的文件
--------------------------------
自定义变量：
	变量名=变量值  var=hello
预定义变量：
	AR : 归档维护程序的名称，默认值为ar
	CC : C编译器的名称，默认值是cc
	CXX : C++编译器的名称，默认值是g++
	$@ : 目标的完整名称
	$< : 第一个依赖文件的名称
	$^ : 所有的依赖文件
获取变量的方法:
	$变量名
---------------------------------
上述makefile 可以写成如下

src = main.o a.o b.o
target = app

$(target) = $(src)
	$(CC) -c $< -o $(target)

%.o:%.c
	$(CC) -c $<-o $@
	
src的另一种写法
src = $(wildcard ./*.c)
objs $(patsubst %.c, %.o,$(src))

$(target) = $(objs)
	$(CC) -c $(objs) -o $(target)
	
clean:
	rm $(objs) -f
#使用make clean 可以删除编译出来的*.o文件

```

