#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void solve(int fd){
    int buf,p[2],prime=0;
    if(read(fd,&buf,sizeof(int))!=0){
        prime=buf;
        printf("prime %d\n",prime);
        pipe(p);
        if(fork()==0){
            close(fd);
            close(p[1]);
            solve(p[0]);
        }else{
            while(read(fd,&buf,sizeof(int))!=0){
                if(buf%prime!=0){
                    write(p[1],&buf,sizeof(int));
                }
            }
            close(p[1]);
            wait((int*)0);    
        }
    }
    
}

int main(int argc,char *argv[]){
    int p[2];
    pipe(p);
    for(int i=2;i<=35;i++){
        write(p[1],&i,sizeof(int));
    }
    close(p[1]);
    solve(p[0]);
    exit(0);
}