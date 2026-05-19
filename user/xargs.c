#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"

int main(int argc,char *argv[]){
    if(argc<2){
        fprintf(2,"Usage: xargs <cmd>\n");
        exit(1);
    }
    char *arg[MAXARG],buf[512];
    for(int i=0;i<argc;i++)arg[i]=argv[i];
    while(1){
        gets(buf,sizeof(buf));
        if(strlen(buf)==0)break;
        buf[strlen(buf)-1]='\0';
        arg[argc]=malloc(strlen(buf)+1);
        strcpy(arg[argc],buf);arg[argc][strlen(buf)]='\0';
        // printf("%s\n",arg[argc]);
        arg[argc+1]=0;
        if(fork()==0){
            exec(arg[1],arg+1);
            exit(0);
        }else{
            wait((int*)0);
            free(arg[argc]);
        }
    }
    exit(0);
}