#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc,char *argv[]){
    int ptc[2],ctp[2];
    char buf[1];
    pipe(ptc);
    pipe(ctp);
    if(fork()==0){
        read(ptc[0],buf,1);
        printf("%d: received ping\n",getpid());
        write(ctp[1],"a",1);
        exit(0);
    }else{
        write(ptc[1],"a",1);
        wait((int*)0);
        read(ctp[0],buf,1);
        printf("%d: received pong\n",getpid());
        exit(0);
    }
}