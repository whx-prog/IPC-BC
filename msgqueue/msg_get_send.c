#include <My_head.h>
struct msgbuf{
    long mtype;
    char mtext[128];
};
int main(int argc,char *argv[])
{ //  ARGS_CHECK(argc,2);
    int msgid=msgget(666,IPC_CREAT|0600);
    ERROR_CHECK(msgid,-1,"msgget");
    struct msgbuf M;
    M.mtype=1;
    strcpy(M.mtext,"hello");
    int ret=msgsnd(msgid,&M,strlen(M.mtext),0);
    ERROR_CHECK(ret,-1,"msgsnd");
    return 0;
}

