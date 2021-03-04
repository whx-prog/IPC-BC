#include <My_head.h>
struct msgbuf {
    long mtype;
    char mtext[128];
};
int main(int argc,char *argv[])
{ //  ARGS_CHECK(argc,2);
    int i;
    scanf("%d",&i);
    struct msgbuf msg;
    msg.mtype=2;
    strcpy(msg.mtext,"nihao");
    int ret=msgsnd(i,&msg,strlen(msg.mtext),0);
    ERROR_CHECK(ret,-1,"msgsnd");
    return 0;
}

