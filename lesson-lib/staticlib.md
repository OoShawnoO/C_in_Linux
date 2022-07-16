# 静态库的制作与使用

静态库的命名规范

- ```LInux : libxxx.a```
- ```Windows: libxxx.lib```

静态库的制作

```gcc`` 获得 *.o文件

将 *.o文件打包，使用ar工具

```ar rcs libxxx.a xxx.o xxx.o  .....```

静态库的使用

- 需要提供相应的头文件

- ```gcc main.c -o app -I include -L lib -l xxx ```