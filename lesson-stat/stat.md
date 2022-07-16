# 文件Stat

```C
int stat(const char *pathname,struct stat *statbuf);
headers:
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <unistd.h>
params:
	pathname : 文件名称 ;
	statbuf : 文件相关信息结构体 ;
return:
	success : 0 ;
	failed : -1 [errno];

struct stat{
    dev_t st_dev; //文件设备编号
    ino_t st_ino; //节点
    mode_t st_mode; //文件类型以及权限
    nlink_t st_nlink; //文件硬链接数
    uid_t st_uid; //用户ID
    gid_t st_gid; //用户组ID
    dev_t st_rdev;	//设备文件的设备编号
    off_t st_size; //文件字节数
    blksize_t st_blksize; //块大小
    blkcnt_t st_blocks;	//块数
    time_t	st_atime; //最后一次访问时间
    time_t st_mtime; //最后一次修改时间
    time_t st_ctime; //最后一次改变时间
}

int lstat(const char *pathname,struct stat *statbuf);
headers:
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <unistd.h>
params:
	pathname : 本链接文件名称 ;
	statbuf : 文件相关信息结构体 ;
return:
	success : 0 ;
	failed : -1 [errno];

struct stat{
    dev_t st_dev; //文件设备编号
    ino_t st_ino; //节点
    mode_t st_mode; //文件类型以及权限
    nlink_t st_nlink; //文件硬链接数
    uid_t st_uid; //用户ID
    gid_t st_gid; //用户组ID
    dev_t st_rdev;	//设备文件的设备编号
    off_t st_size; //文件字节数
    blksize_t st_blksize; //块大小
    blkcnt_t st_blocks;	//块数
    time_t	st_atime; //最后一次访问时间
    time_t st_mtime; //最后一次修改时间
    time_t st_ctime; //最后一次改变时间
}
```

