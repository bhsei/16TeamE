#include <sys/stat.h>
#include <sys/types.h>
#include<stdio.h>
#include<stdlib.h>

// int mkdir(const char *pathname, mode_t mode);
int main(int argc,char *argv[])
{
    int ret;
    if((ret = mkdir(argv[1],0775)) // �½�һ��Ŀ¼Ĭ��Ȩ����775
       ==  -1){
        printf("创建目录失败！\n");
        exit(1);
   }
   return 0;
}
