#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/stat.h>


#define BUFFERSIZE 4096

#define COPYMODE 0644

void print_error(char *,char *);

int main(int argc,char *argv[])
{
    int in_fd,out_fd,n_chars;
    char buf[BUFFERSIZE];
    struct stat stat_file;
    int ret,mode;
    
    if (argc != 3) {
        fprintf(stderr,"usage: %s 源 目的\n",*argv);
        exit(1);
    }
    if( (in_fd = open(argv[1],O_RDONLY)) == -1){
        print_error("不能打开:",argv[1]);
    }
    // 获取原文件的属性
    ret = fstat(in_fd,&stat_file);
     
    if( (out_fd = creat(argv[2],stat_file.st_mode)) == -1){
        print_error("不能创建:",argv[2]);
    }
    
    while ((n_chars = read(in_fd,buf,BUFFERSIZE)) > 0) {
        if ( write(out_fd,buf,n_chars) != n_chars) {
            print_error("写入出错：",argv[2]);
        }
    }

    if (n_chars == -1) {
        print_error("读取出错：",argv[1]);
    }
    
    
    close(in_fd);
    close(out_fd);
   return 0;
}


void print_error(char *s1,char *s2)
{
    
    fprintf(stderr,"错误：%s\n",s1);
    perror(s2);
    exit(1);
}
