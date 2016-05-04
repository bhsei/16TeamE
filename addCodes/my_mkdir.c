#include <sys/stat.h>
#include <sys/types.h>
#include<stdio.h>
#include<stdlib.h>

// int mkdir(const char *pathname, mode_t mode);
int main(int argc,char *argv[])
{
    int ret;
    if((ret = mkdir(argv[1],0775)) // 新建一个目录默认权限是775
       ==  -1){
        printf("鍒涘缓鐩綍澶辫触锛乗n");
        exit(1);
   }
   return 0;
}
