#include <sys/stat.h>
#include <sys/types.h>
#include<stdio.h>
#include<stdlib.h>


void print_error(char *s1,char *s2);


int main(int argc,char *argv[])
{
    int ret;
    if((ret = rmdir(argv[1])) 
       ==  -1){
        //printf("删除目录失败！\n");
        print_error("删除目录失败",argv[1]);
        exit(1);
   }
   printf("成功删除目录！\n");
   return 0;
}



void print_error(char *s1,char *s2)
{
    
    fprintf(stderr,"错误：%s\n",s1);
    perror(s2);
    exit(1);
}
