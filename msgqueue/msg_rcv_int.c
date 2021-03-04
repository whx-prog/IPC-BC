#include <My_head.h>
typedef struct msgbuf{
    long mtype;
    char mtext[128];
}msg;
int main(int argc,char *argv[])
{ //  ARGS_CHECK(argc,2);
    int i;
    scanf("%d",&i);
    msg M;
    int ret=msgrcv(i,&M,sizeof(M.mtext),1,0);
    ERROR_CHECK(ret,-1,"msgrcv");
    memcpy(&i,M.mtext,sizeof(i));
    printf("mtype=%ld,mtext=%d\n",M.mtype,i);
    return 0;
}

