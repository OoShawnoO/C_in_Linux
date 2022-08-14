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

int pthread_cancel(pthread_t thread);
取消一个线程 终止某个线程的运行，但不是立即终止，而是当子线程执行到一个取消点，线程才会终止;
取消点: 可以粗略的理解为 从用户区到内核区的切换位置;

int pthread_attr_init(pthread_attr_t *attr);
初始化线程属性;

int pthread_attr_destroy(pthread_attr_t *attr);
释放线程属性的资源;

int pthread_attr_getdetachstate(const pthread_attr_t *attr,int *detachstate);
获取线程分离的状态属性;

int pthread_attr_setdetachstate(pthread_attr_t *attr,int detachstate)
设置线程分离的状态属性;
```

# 线程同步

```c
互斥量 mutex  pthread_mutex_t ;
int pthread_mutex_init(pthread_mutex_t *restrict mutex,const pthread_mutexattr_t *restrcit attr);
初始化互斥量;
params:
	mutex : 需要初始化的互斥量;
	attr : 互斥量相关的属性	;
	restrict 关键字 被其修饰的指针不能由另外的指针进行操作;

int pthread_mutex_destroy(pthread_mutex_t *mutex);
释放互斥量的资源;

int pthread_mutex_lock(pthread_mutex_t *mutex);
加锁 阻塞的 如果有一个线程加锁，则其他线程阻塞;

int pthread_mutex_trylock(pthread_mutex_t *mutex);
尝试加锁 加锁失败直接返回;

int pthread_mutex_unlock(phtread_mutex_t *mutex);
解锁;

读写锁 pthread_rwlock_t	;
int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock,const pthread_rwlockattr_t *restrict attr);

int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);

int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);

int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock);

int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);

int pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock);

int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);

条件变量 pthread_cond_t		;
int pthread_cont_init(pthread_cond_t *restrict cond,const pthread_condattr_t *restrict attr);

int pthread_cond_destroy(pthread_cond_t *cond);

int pthread_cond_wait(pthread_cond_t *restrict cond,pthread_mutex_t *restrict mutex);
等待 阻塞 阻塞时会对互斥锁进行解锁，不阻塞时会重新加锁;
int pthread_cond_timewait(pthread_cond_t *restrict cond,pthread_mutex_t *restrict mutex,const struct timespec *restrict abstime);
等待 相应时间后 就不阻塞了;
int pthread_cond_signal(pthread_cond_t *cond);
唤醒一个或多个等待的线程;
int pthread_cond_broadcast(pthread_cond_t *cond);
唤醒所有等待的线程;

信号量 sem_t;
int sem_init(sem_t *sem,int pshared,unsigned int value);
params:
	sem : 要初始化的信号量;
	pshared : 0 在线程中 , !0 在进程中;
	value : 信号量的值;
int sem_destroy(sem_t *sem);

int sem_wait(sem_t *sem);
信号量加锁 信号量 -1
int sem_trywait(sem_t *sem);

int sem_timewait(sem_t *sem,const struct timespec *abs_timeout);

int sem_post(sem_t *sem);
信号量解锁 信号量+1
int sem_getvalue(sem_t *sem,int *sval);
```

