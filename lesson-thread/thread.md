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
终止一个线程，在哪个线程中调用就是终止哪个线程;

pthread_t pthread_self(void);
获取当前线程的id;

int pthread_equal(pthread_t t1,pthread t2);
比较线程id是否相等;

int pthread_join(pthread_t thread,void **retval);
和一个终止的线程进行链接;
回收子线程的资源，这个函数是一个阻塞函数，调用一次回收一个线程;
params:
	thread : 需要回收的子线程id	;
	retval : 子线程结束时返回的参数 使用二级指针可以操作该值	;
return:
	success : 0 ;
	failed : -1 errno;

int pthread_detach(pthread_t thread);
分离线程,被分离的线程在终止时，会自动地释放资源返回给系统;
params:
	thread : 要分离的线程的id 	;
return:
	success : 0 ;
	failed : -1 errno;

```

