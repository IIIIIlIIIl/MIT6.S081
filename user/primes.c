#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void solve(int fd,int length){
    int buf[length],p[2];
    read(fd,buf,sizeof(buf));
    close(fd);
    int prime=buf[0],number=0;
    printf("prime %d\n",prime);
    pipe(p);
    for(int i=0;i<length;i++){
        if(buf[i]%prime!=0)write(p[1],&buf[i],sizeof(int)),number++;
    }
    close(p[1]);
    if(number!=0){
        if(fork()==0){
            solve(p[0],number);
        }else{
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
    solve(p[0],34);
    exit(0);
}