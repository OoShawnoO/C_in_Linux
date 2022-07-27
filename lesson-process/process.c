#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main(){
    
    pid_t ppid = getpid();
    pid_t pid = fork();
    if(pid != 0){
        while(1){
        printf("parent pid = %d\n",ppid);
        sleep(1);
    }
    return 0;
    }else{
        while(1){
            printf("son pid = %d\n",pid);
            sleep(1);
        }
    }
    
}