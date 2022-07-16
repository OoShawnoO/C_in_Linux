# 动态库的制作以及使用

动态库的命名规则：

- ```Linux : libxxx.so```

- ```Windows : libxxx.dll```

动态库的制作:

- 使用``gcc``获得与位置无关的代码

  ``` gcc -c -fpic a.c b.c```

- ``gcc`` 获得动态库

  ```gcc -shared a.o b.o -o libxxx.so```

动态库使用:

- 动态库是在内存中被使用的，所以需要将动态库加载到内存中
- 搜索路径 ```DT_RPATH段、环境变量LD_LIBRARY_PATH、/etc/ld.so.cache、/lib/、/usr/lib```
- 将动态库所在文件夹添加至``LD_LIBRARY_PATH`` 在``~/.bashrc``中添加``export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:文件夹路径``

