#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>

/*
 ls -l 实现
*/


int main(int argc,char* argv[]){
    /* argc 自带 文件名称和可执行文件名称路径*/
    if(argc<2){
        printf("%s filename\n",argv[0]);
        return -1;
    }

    struct stat st;
    int ret = stat(argv[1],&st);
    if(ret == -1){
        perror("stat");
        return -1;
    }
    
    char perms[11] = {0};
    switch(st.st_mode & S_IFMT){
        case S_IFLNK:{perms[0] = 'l';break;}
        case S_IFDIR:{perms[0] = 'd';break;}
        case S_IFREG:{perms[0] = '-';break;}
        case S_IFBLK:{perms[0] = 'b';break;}
        case S_IFCHR:{perms[0] = 'c';break;}
        case S_IFSOCK:{perms[0] = 's';break;}
        case S_IFIFO:{perms[0] = 'p';break;}
        default:{perms[0] = '?';break;}
    }

    perms[1] = st.st_mode & S_IRUSR?'r':'-';
    perms[2] = st.st_mode & S_IWUSR?'w':'-';
    perms[3] = st.st_mode & S_IXUSR?'x':'-';
    perms[4] = st.st_mode & S_IXGRP?'x':'-';
    perms[5] = st.st_mode & S_IXGRP?'x':'-';
    perms[6] = st.st_mode & S_IXGRP?'x':'-';
    perms[7] = st.st_mode & S_IROTH?'x':'-';
    perms[8] = st.st_mode & S_IWOTH?'x':'-';
    perms[9] = st.st_mode & S_IXOTH?'x':'-';

    int linknum = st.st_nlink;

    char* fileuser = getpwuid(st.st_uid)->pw_name;

    char* group = getgrgid(st.st_gid)->gr_name;

    long int filesize = st.st_size;

    char *time = ctime(&st.st_mtime);

    char mtime[512] = {0};
    strncpy(mtime,time,strlen(time)-1);

    char buff[1024];
    
    sprintf(buff,"%s %d %s %s %ld %s %s",perms,linknum,fileuser,group,filesize,mtime,argv[1]);

    printf("%s\n",buff);

    return 0;
}