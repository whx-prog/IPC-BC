#include <My_head.h>

int main(int argc,char *argv[])
{ //  ARGS_CHECK(argc,2);
    int i;
   scanf("%d",&i);
   int ret=msgctl(i,IPC_RMID,NULL);
   ERROR_CHECK(ret,-1,"msgctl");
    return 0;
}

