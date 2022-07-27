# 线程

```c
#include <pthread.h>

int pthread_create(pthread_t *thread,const pthread_attr_t *attr,void *(*start_routine)(void *),void *arg);
创建一个子线程;
params:
	thread : 传出参数，线程创建成功后，子线程的id被写到变量中;
	attr : 设置线程的属性一般使用默认值NULL	;
	start_routine : 函数指针,这个函数是子线程需要处理的逻辑代码;
	arg : 给第三个参数的函数提供的参数	;
return:
	success : 0;
	failed : 返回错误号,strerror(int errnum)查看错误信息;

void pthread_exit(void *retval);
终止一个线程，在哪个线程中调用就是终止哪个线程
```

