//mv功能的实现
#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc,char *argv[])
{
   int res;
   if(argc!=3)
   {
       printf("参数错误!\n");
       exit(1);
   }
   res = rename( argv[1], argv[2]);
   if (res == 0)
   {
       printf("成功!\n");
   }
   else
   {
       printf("失败!\n");
   }
   return 0;
}
