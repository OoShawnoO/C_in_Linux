# 文件属性函数

```C
int access(const char *pathname,int mode);
作用：判断是否有某个权限或文件是否存在 ;
headers:
	#include <unistd.h>
params:
	pathname ： 文件路径 ;
	mode : 权限 [R_OK 是否可读 \ W_OK 是否可写 \ X_OK 是否可执行 \ F_OK 是否存在] ;
return:
	success : 0 ;
	failed : -1 ;



int chmod(const char *filename,int mode);
作用: 修改文件权限
headers:
	#include <unistd.h>
	#include <sys/stat.h>
params:
	pathname ： 文件路径 ;
	mode : 需要修改的权限值 八进制 ;
return:
	success : 0 ;
	failed : -1 ;


int chown(const char *path,uid_t owner,gid_t group);
作用：修改拥有者 ;
headers:
	#include <unistd.h>
params:
	path : 路径 ;
	owner : 需要修改的拥有者的id	;
	group : 需要修改的拥有者组的id ;
return:
	success : 0 ;
	failed : -1 ;

int truncate(const char *path,off_t length);
作用 ： 缩减或拓展文件的大小 ;
headers:
	#include <unistd.h>
	#include <sys/types.h>
params:
	path : 路径 ;
	length : 最终文件的大小 ;
return:
	success : 0 ;
	failed : -1 ;
```

