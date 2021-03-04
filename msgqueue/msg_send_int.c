#include <My_head.h>
typedef struct msgbuf{
    long mtype;
    char mtext[128];
}msg;
int main(int argc,char *argv[])
{ //  ARGS_CHECK(argc,2);
    int i;
    scanf("%d",&i);
    int j=300;
    msg M;
    M.mtype=1;
    memcpy(M.mtext,&j,sizeof(j));
    int ret=msgsnd(i,&M,sizeof(j),0);
    ERROR_CHECK(ret,-1,"msgsnd");
    return 0;
}

