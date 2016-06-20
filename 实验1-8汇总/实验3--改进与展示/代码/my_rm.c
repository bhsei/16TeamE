#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void print_error(char *,char *);


int main(int argc ,char *argv[])
{

  int ret;
  if(argc != 2){
     // print_error("参数个数不对",argv[0]);
     printf("参数个数不对,需要2个参数\n");
     exit(1);
  }

  if((ret = unlink(argv[1])) != 0){
     print_error("删除失败",argv[1]);
  }
  printf("删除成功！\n");
  return 0;
}


void print_error(char *s1,char *s2)
{
    
    fprintf(stderr,"错误：%s\n",s1);
    perror(s2);
    exit(1);
}
