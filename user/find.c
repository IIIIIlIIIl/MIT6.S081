#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  buf[strlen(p)]='\0';
  return buf;
}

void solve(char *path,char *name){
    int fd;
    char buf[512],*p;
    struct stat st;
    struct dirent de;
    if((fd=open(path,0))<0){
        fprintf(2,"find: cannot open %s\n",path);
        exit(1);
    }
    if(fstat(fd,&st)<0){
        fprintf(2,"find: cannot stat %s\n",path);
        close(fd);
        exit(1);
    }
    strcpy(buf,path);
    p=buf+strlen(buf);
    *p++='/';
    switch(st.type){
        case T_FILE:
            // printf("%s %s %s\n",path,fmtname(path),name);
            if(strcmp(fmtname(path),name)==0){
                printf("%s\n",path);
            }
            break;
        case T_DIR:
            while(read(fd,&de,sizeof(de))==sizeof(de)){
                if(de.inum==0)continue;
                memmove(p,de.name,DIRSIZ);
                p[DIRSIZ]=0;
                if(strcmp(p,".")==0||strcmp(p,"..")==0)continue;
                solve(buf,name);
            }
        break;
    }
    close(fd);
}

int main(int argc,char *argv[]){
    if(argc<3){
        fprintf(2,"Usage: find <dir> <name>\n");
        exit(1);
    }
    solve(argv[1],argv[2]);
    exit(0);
}